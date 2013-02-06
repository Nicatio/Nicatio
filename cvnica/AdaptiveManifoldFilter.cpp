/*
 * AdaptiveManifoldFilter.cpp
 *
 *  Created on: 2013. 2. 1.
 *      Author: HDSP
 */

#include "AdaptiveManifoldFilter.h"
#define floorToPowerOfTwo(r) pow(2.0,floor(log(r)/log(2.0)))


using namespace cv;

namespace cvNica {

AdaptiveManifoldFilter::AdaptiveManifoldFilter(void)
{
	setUseOptimized(true);
	setNumThreads(8);
	treeNodesVisited=0;
}


AdaptiveManifoldFilter::~AdaptiveManifoldFilter(void)
{
}

void AdaptiveManifoldFilter::computeEigenvector(
		InputArray	 					_XX,
		int								numPCA_Iterations,
		InputArray						_randVec,
		OutputArray						_p)
{
	Mat X = _XX.getMat();
	_p.create(X.size(),X.type());
	Mat p = _p.getMat();
	Mat dots,t;// = Mat(X.size(),X.type());
	for (int i=0; i<numPCA_Iterations; i++){
		multiply(X,_randVec,dots);
		reduce(dots,dots,1,CV_REDUCE_SUM);
		t = dots.mul(X);
		reduce(t,t,0,CV_REDUCE_SUM);
	}
	p = t / norm(t);
}

void AdaptiveManifoldFilter::buildManifoldsAndPerformFiltering(
		InputArray						_f,
		InputArray						_fJoint,
		OutputArray						_fOut,
		InputArray						_etaK,
		InputArray						_clusterK,
		const double					sigmaS,
		const double					sigmaR,
		const int 						currentTreeLevel,
		const int 						treeHeight,
		const int 						numPcaIterations)
{
	Mat f = _f.getMat();
	Mat fJoint = _fJoint.getMat();
	Mat etaK = _etaK.getMat();
	Mat clusterK = _clusterK.getMat();
	_fOut.create(f.size(),f.type());
	Mat fOut = _fOut.getMat();


	double sigmaROverSqrt2 = sigmaR/sqrt(2);
	double oneOverSigmaROverSqrt2Square = 1/sigmaROverSqrt2/sigmaROverSqrt2;
	double df = min(sigmaS/4.0,256*sigmaR);
	df = floorToPowerOfTwo(df);
	df = max(1.0,df);
	Size imageSize = f.size();
	Size jointSize = fJoint.size();
	int dRimage = f.channels();
	int dRjoint = fJoint.channels();
	Mat X;
	Mat pixelDistToManifoldSquared;
	Mat gaussianDistanceWeights;
	Mat psiSplat;
	Mat psiSplat0;
	if (etaK.rows == fJoint.rows){
		X = fJoint - etaK;
		resize(etaK,etaK,Size(0,0),1/df,1/df);
	} else {
		Mat etaKTemp;
		resize(etaK,etaKTemp,imageSize);
		X = fJoint - etaKTemp;
	}

	pow(X,2.0,pixelDistToManifoldSquared);

	///// channel reduction is needed;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	gaussianDistanceWeights = pixelDistToManifoldSquared * oneOverSigmaROverSqrt2Square * -0.5;
	exp(gaussianDistanceWeights,gaussianDistanceWeights);
	psiSplat = gaussianDistanceWeights.mul(f);
	psiSplat.copyTo(psiSplat0);
	minPixelDistToManifoldSquared = min(minPixelDistToManifoldSquared,pixelDistToManifoldSquared);
	Mat blurredProjectedValues;
	Mat wKiPsiBlur,wKiPsiBlur0;
	RFFilter(psiSplat,psiSplat0,wKiPsiBlur,sigmaS/df,sigmaROverSqrt2,etaK);
	RFFilter(psiSplat,psiSplat0,wKiPsiBlur0,sigmaS/df,sigmaROverSqrt2,etaK);//???
	Mat wKi = gaussianDistanceWeights;


	resize(wKiPsiBlur,wKiPsiBlur,imageSize);
	resize(wKiPsiBlur0,wKiPsiBlur0,imageSize);
	sumWKiPsiBlur += wKi.mul(wKiPsiBlur);
	sumWKiPsiBlur0 += wKi.mul(wKiPsiBlur0);

	treeNodesVisited++;

	if (currentTreeLevel < treeHeight) {
		X.reshape( imageSize.height*imageSize.width,dRjoint);

		Mat zeros = Mat::zeros(1,imageSize.height, CV_8UC1);
		Mat ones =  Mat::ones(1,imageSize.height, CV_8UC1);
		Mat randvec;
		randu(randvec,zeros,ones);
		Mat v1;
		computeEigenvector(X,numPcaIterations,randvec,v1);
		Mat dot= X*v1.t();
		dot.reshape(jointSize.height,jointSize.width);
		Mat clusterMinus;
		Mat clusterPlus;
		compare(dot,0,clusterMinus,CMP_LT);
		compare(dot,0,clusterPlus,CMP_GE);

		bitwise_and(clusterMinus,clusterK,clusterMinus);
		bitwise_and(clusterPlus,clusterK,clusterPlus);

		Mat theta = 1 - wKi;

		Mat _etaMinus = clusterMinus.mul(theta);
		Mat etaMinus = _etaMinus.mul(fJoint);

		hFilter(_etaMinus, sigmaS/df, _etaMinus);
		hFilter( etaMinus, sigmaS/df,  etaMinus);

		divide(etaMinus,_etaMinus,etaMinus);

		Mat _etaPlus = clusterPlus.mul(theta);
		Mat etaPlus = _etaPlus.mul(fJoint);

		hFilter(_etaPlus, sigmaS/df, _etaPlus);
		hFilter( etaPlus, sigmaS/df,  etaPlus);

		divide(etaPlus,_etaPlus,etaPlus);

		buildManifoldsAndPerformFiltering(f,fJoint,f,etaMinus,clusterMinus,sigmaS,sigmaR,currentTreeLevel+1,treeHeight,numPcaIterations);
		buildManifoldsAndPerformFiltering(f,fJoint,f,etaPlus, clusterPlus, sigmaS,sigmaR,currentTreeLevel+1,treeHeight,numPcaIterations);



	}

}

void AdaptiveManifoldFilter::RFFilter(
		InputArray						_img,
		InputArray						_img0,
		OutputArray						_F,
		const double					sigmaS,
		const double					sigmaR,
		InputArray						_jointImage)
{
	Mat I = _img.getMat();
	Mat I0 = _img0.getMat();
	Mat J;
	if (_jointImage.empty()) {
		J = I;
	} else {
		J = _jointImage.getMat();
		if (I.size() != J.size()) {std::cout<<"error"<<std::endl;return;}
	}

	I.convertTo(I,CV_32F);
	I0.convertTo(I0,CV_32F);
	J.convertTo(J,CV_32F);

	Mat dlcdx;
	Mat dlcdy;
	Mat dxKernel = Mat(1,2,CV_32F);
	Mat dyKernel = Mat(2,1,CV_32F);
	dxKernel.data[0] = -1; dxKernel.data[1] = 1;
	dyKernel.data[0] = -1; dyKernel.data[1] = 1;

	filter2D(J,dlcdx,-1,dxKernel);
	filter2D(J,dlcdy,-1,dyKernel);

	pow(dlcdx,2.0,dlcdx);
	pow(dlcdy,2.0,dlcdy);

	// insert zero padding here

	double sigmaH = sigmaS;
	double sigmaHoverSigmaSsquare = pow(sigmaH/sigmaS,2.0);
	Mat dHdx = sigmaHoverSigmaSsquare + sigmaHoverSigmaSsquare*dlcdx;
	Mat dVdy = sigmaHoverSigmaSsquare + sigmaHoverSigmaSsquare*dlcdy;

	dVdy = dVdy.t();

	int N = 1;
	Mat F = I;

	for (int i=0; i<N; i++)
	{
		double sigmaHi = sigmaH * sqrt(3) * pow(2.0, (N -i -1)) / sqrt(pow(4.0,N)-1);
		TransformedDomainRecursiveFilter_Horizontal (F,dHdx,sigmaHi,F);
		F = F.t();
		TransformedDomainRecursiveFilter_Horizontal (F,dVdy,sigmaHi,F);
		F = F.t();
	}

	F.convertTo(F,_img.type());

}

void AdaptiveManifoldFilter::TransformedDomainRecursiveFilter_Horizontal(
		InputArray						_Fin,
		InputArray						_dHdx,
		const double					sigma,
		OutputArray						_Fout)
{
	double a = exp(-sqrt(2.0)/sigma);
	Mat F = _Fin.getMat();
	Mat V = Mat(_dHdx.size(),_dHdx.type());
	int Vrow = V.rows;
	int Vcol = V.cols;
	float *ptrV = (float*)V.data;

	for (int j = 0; j<Vrow; j++) {
		for (int i = 0; i<Vcol; i++,ptrV++) {
			*(ptrV) = pow (a,*(ptrV));
		}
	}

	for (int i = 1; i<Vcol ; i++){
		F.col(i) += V.col(i).mul(F.col(i-1)-F.col(i));
	}
	for (int i = Vcol-1; i>=0 ; i--){
			F.col(i) += V.col(i).mul(F.col(i+1)-F.col(i));
	}
}

void AdaptiveManifoldFilter::hFilter(
		InputArray						_Fin,
		const double					sigma,
		OutputArray						_Fout)
{
	Mat Fin = _Fin.getMat();
	Mat Fout = _Fout.getMat();
	Mat FinOnes = Mat::ones(Fin.size(),CV_8UC1);
	TransformedDomainRecursiveFilter_Horizontal(Fin,FinOnes,sigma,Fout);
	Fout = Fout.t();
	FinOnes = FinOnes.t();
	TransformedDomainRecursiveFilter_Horizontal(Fout,FinOnes,sigma,Fout);
	Fout = Fout.t();
}



}



