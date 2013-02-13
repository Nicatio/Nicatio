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

void AdaptiveManifoldFilter::process(
		InputArray						_Fin,
		OutputArray						_Fout,
		const double					sigmaS,
		const double					sigmaR,
		InputArray						_FJoint,
		int 							_treeHeight,
		int 							_numPcaIterations)
{
	Mat Fin = _Fin.getMat();
	Mat FJoint;
	Fin.convertTo(Fin,CV_32FC3);
	Fin /= 255;
	sumWKiPsiBlur = Mat::zeros(Fin.size(),CV_32FC3);
	sumWKiPsiBlur0 = Mat::zeros(Fin.size(),CV_32FC1);
	minPixelDistToManifoldSquared = Mat::zeros(Fin.size(),CV_32FC1);
	minPixelDistToManifoldSquared += std::numeric_limits<double>::infinity();
	int treeHeight = _treeHeight;
	int numPcaIterations = _numPcaIterations;
	if(!treeHeight) {
		computeManifoldTreeHeight(sigmaS,sigmaR,treeHeight);
	}

	if(_FJoint.empty()) {
		Fin.copyTo(FJoint);
	} else {
		FJoint = _FJoint.getMat();
	}

	FJoint.convertTo(FJoint,CV_32FC3);


	if(!numPcaIterations) {
		numPcaIterations = 1;
	}

	treeNodesVisited = 0;

	Mat eta1;
	Mat cluster1;

	hFilter(FJoint,sigmaS,eta1);
	cluster1 = Mat::zeros(Fin.size(),CV_8UC1);
	add(cluster1,255,cluster1);

	int currentTreeLevel = 1;
	Mat empty;
	buildManifoldsAndPerformFiltering(Fin, FJoint, empty, eta1, cluster1, sigmaS, sigmaR, currentTreeLevel, treeHeight, numPcaIterations);

	Mat tildeGSplit[3],tildeG;
	Mat sumWKiPsiBlurSplit[3];

	split(sumWKiPsiBlur,sumWKiPsiBlurSplit);

	for (int i=0; i<3; i++){
		divide (sumWKiPsiBlurSplit[i],sumWKiPsiBlur0,tildeGSplit[i]);
	}
	merge (tildeGSplit,3,tildeG);


	//divide(sumWKiPsiBlur,sumWKiPsiBlur0,tildeG);

	Mat alpha;

	minPixelDistToManifoldSquared *= (-0.5) / (sigmaR * sigmaR);
	exp(minPixelDistToManifoldSquared,alpha);


	Mat tildeGvsFinDiff = tildeG - Fin;
	Mat tildeGvsFinDiffSplit[3];

	Mat __Fout, __FoutSplit[3];
	Mat FinSplit[3];

	split (Fin,FinSplit);

	split (tildeGvsFinDiff,tildeGvsFinDiffSplit);

	for (int i = 0; i<3; i++) {
		__FoutSplit[i] = FinSplit[i] + tildeGvsFinDiffSplit[i].mul(alpha);
	}

	merge (__FoutSplit,3,__Fout);

	_Fout.create(_Fin.size(),_Fin.type());
	Mat Fout = _Fout.getMat();
	__Fout *= 255;
	Mat ___Fout;
	__Fout.convertTo(___Fout,_Fin.type());


	___Fout.copyTo(Fout);


}

void AdaptiveManifoldFilter::computeManifoldTreeHeight(
		const double					sigmaS,
		const double					sigmaR,
		int&							Height)//,
		//int								K)
{
	double Hs = floor(log(sigmaS)/log(2.0))-1;
	double Lr = 1 - sigmaR;
	int temp = (int)ceil(Hs*Lr);
	Height = (2<temp)?temp:2;
}

void AdaptiveManifoldFilter::computeEigenvector(
		InputArray	 					_XX,
		int								numPCA_Iterations,
		InputArray						_randVec,
		OutputArray						_p)
{
	Mat X = _XX.getMat();
	_p.create(_randVec.size(),_randVec.type());
	Mat p = _p.getMat();
	Mat randVec = _randVec.getMat();

	int xch = X.channels();
	Mat t;// = Mat(X.size(),X.type());
	Mat __p;
	Mat XSplit[xch];
	Mat randVecSplit[xch];
	Mat dotsSplit[xch];
	Mat Xsum;
	Mat tSplit[xch];
	Mat dots;
	split(X,XSplit);
	split(randVec,randVecSplit);

	for (int i=0; i<numPCA_Iterations; i++){
		//multiply(X,randVec,dots);
		for (int j=0; j<xch; j++){
			dotsSplit[j] = XSplit[j]*randVecSplit[j];
		}
		merge(dotsSplit,3,dots);
		channelSum(dots,dots);
		split(t,tSplit);
		for (int j=0; j<xch; j++){
			tSplit[j] = dots.mul(XSplit[j]);
		}
		merge(tSplit,3,t);
		reduce (t,t,0,CV_REDUCE_SUM);
	}
	divide(t,norm(t),__p);
	//p = t / norm(t);
	__p.copyTo(p);

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
	float *ptr;


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
		resize(etaK,etaK,Size(0,0),1.0/df,1.0/df);
	} else {
		Mat etaKTemp;
		resize(etaK,etaKTemp,imageSize);
		X = fJoint - etaKTemp;
	}

	pow(X,2.0,pixelDistToManifoldSquared);

	channelSum(pixelDistToManifoldSquared,pixelDistToManifoldSquared);
	gaussianDistanceWeights = pixelDistToManifoldSquared * oneOverSigmaROverSqrt2Square * -0.5;
	exp(gaussianDistanceWeights,gaussianDistanceWeights);

	Mat fTemp[3];
	split(f,fTemp);

	fTemp[0] = fTemp[0].mul(gaussianDistanceWeights);
	fTemp[1] = fTemp[1].mul(gaussianDistanceWeights);
	fTemp[2] = fTemp[2].mul(gaussianDistanceWeights);

	merge(fTemp,3,psiSplat);

	gaussianDistanceWeights.copyTo(psiSplat0);

	minPixelDistToManifoldSquared = min(minPixelDistToManifoldSquared,pixelDistToManifoldSquared);

	Mat blurredProjectedValues;
	Mat wKiPsiBlurTemp;
	Mat wKiPsiBlurArr[4];
	Mat wKiPsiBlur,wKiPsiBlur0;
	Mat emptyMat;



	Mat psiSplatConcat;
	Mat psiSplatConcatTemp[2] = {psiSplat,psiSplat0};
	merge(psiSplatConcatTemp,2,psiSplatConcat);
	resize(psiSplatConcat,psiSplatConcat,Size(0,0),1.0/df,1.0/df);

	RFFilter(psiSplatConcat,wKiPsiBlurTemp,sigmaS/df,sigmaROverSqrt2,etaK);

	split(wKiPsiBlurTemp,wKiPsiBlurArr);
	merge(wKiPsiBlurArr,3,wKiPsiBlur);
	wKiPsiBlurArr[3].copyTo(wKiPsiBlur0);



	Mat wKi;
	gaussianDistanceWeights.copyTo(wKi);

	Mat wKiArr[3] = {wKi,wKi,wKi};
	Mat wKiMerge;

	merge(wKiArr,3,wKiMerge);



	resize(wKiPsiBlur,wKiPsiBlur,imageSize);
	resize(wKiPsiBlur0,wKiPsiBlur0,imageSize);



	sumWKiPsiBlur += wKiMerge.mul(wKiPsiBlur);
	sumWKiPsiBlur0 += wKi.mul(wKiPsiBlur0);

	treeNodesVisited++;

	if (currentTreeLevel < treeHeight) {
		X = X.reshape( 3,imageSize.width*imageSize.height);

		int xch = X.channels();
		Mat randvecArr[xch];

		for (int i=0; i<xch; i++) {
			randvecArr[i] = Mat(1,1,CV_32FC1);
			randu(randvecArr[i],Scalar(-0.5),Scalar(0.5));
		}

		Mat randvec(1,1,CV_32FC3);
		int fromto[] = {0,0,1,1,2,2};
		mixChannels (&randvec,1,randvecArr,3,fromto,3);

		Mat v1;
		computeEigenvector(X,numPcaIterations,randvec,v1);

		Mat Xsplit[xch];
		Mat v1split[xch];
		Mat dotsplit[xch];
		Mat dot;

		split (X,Xsplit);
		split (v1,v1split);

		for (int i=0; i<xch; i++){
			dotsplit[i] = Xsplit[i]*v1split[i];
		}


		merge (dotsplit,3,dot);
		channelSum(dot,dot);
		dot = dot.reshape(0,jointSize.height);

		Mat _clusterMinus, clusterMinus;
		Mat _clusterPlus,  clusterPlus;
		compare(dot,0,_clusterMinus,CMP_LT);
		compare(dot,0,_clusterPlus,CMP_GE);
		_clusterMinus /= 255;
		_clusterPlus /=  255;


		bitwise_and(_clusterMinus,clusterK,_clusterMinus);
		bitwise_and(_clusterPlus,clusterK,_clusterPlus);


		_clusterMinus.convertTo(clusterMinus,CV_32FC1);
		_clusterPlus.convertTo(clusterPlus,CV_32FC1);


		Mat theta = 1 - wKi;
		int fJointChannel = fJoint.channels();

		Mat _etaMinus = clusterMinus.mul(theta);
		Mat etaMinus;

		Mat fJointSplit[fJointChannel];
		Mat etaMinusSplit[fJointChannel];

		split(fJoint,fJointSplit);

		for (int i=0; i<fJointChannel; i++) {
			etaMinusSplit[i] = _etaMinus.mul(fJointSplit[i]);
		}

		merge(etaMinusSplit,3,etaMinus);

		resize(_etaMinus,_etaMinus,Size(0,0),1.0/df,1.0/df);
		resize(etaMinus,etaMinus,Size(0,0),1.0/df,1.0/df);

		hFilter(_etaMinus, sigmaS/df, _etaMinus);
		hFilter( etaMinus, sigmaS/df,  etaMinus);

		split(etaMinus, etaMinusSplit);

		for (int i=0; i<fJointChannel; i++) {
			divide(etaMinusSplit[i],_etaMinus,etaMinusSplit[i]);
		}

		merge(etaMinusSplit,3,etaMinus);

		Mat _etaPlus = clusterPlus.mul(theta);
		Mat etaPlus;
		Mat etaPlusSplit[fJointChannel];

		for (int i=0; i<fJointChannel; i++) {
			etaPlusSplit[i] = _etaPlus.mul(fJointSplit[i]);
		}

		merge(etaPlusSplit,3,etaPlus);

		resize(_etaPlus,_etaPlus,Size(0,0),1.0/df,1.0/df);
		resize(etaPlus,etaPlus,Size(0,0),1.0/df,1.0/df);

		hFilter(_etaPlus, sigmaS/df, _etaPlus);
		hFilter( etaPlus, sigmaS/df,  etaPlus);

		split(etaPlus, etaPlusSplit);

		for (int i=0; i<fJointChannel; i++) {
			divide(etaPlusSplit[i],_etaPlus,etaPlusSplit[i]);
		}

		merge(etaPlusSplit,3,etaPlus);

		buildManifoldsAndPerformFiltering(f,fJoint,f,etaMinus,_clusterMinus,sigmaS,sigmaR,currentTreeLevel+1,treeHeight,numPcaIterations);
		buildManifoldsAndPerformFiltering(f,fJoint,f,etaPlus, _clusterPlus, sigmaS,sigmaR,currentTreeLevel+1,treeHeight,numPcaIterations);
	}

}

void AdaptiveManifoldFilter::RFFilter(
		InputArray						_img,
		OutputArray						_F,
		const double					sigmaS,
		const double					sigmaR,
		InputArray						_jointImage)
{
	Mat I = _img.getMat();


	Mat J;
	if (_jointImage.empty()) {
		I.copyTo(J);
	} else {
		J = _jointImage.getMat();
		if (I.size() != J.size()) {std::cout<<"error"<<std::endl;return;}
	}

	Mat dlcdx;
	Mat dlcdy;
	float KernelRaw[2] = {1.0f, -1.0f};
	Mat dxKernel = Mat(1,2,CV_32F,KernelRaw);
	Mat dyKernel = Mat(2,1,CV_32F,KernelRaw);

	filter2D(J,dlcdx,-1,dxKernel);
	filter2D(J,dlcdy,-1,dyKernel);

	pow(dlcdx,2.0,dlcdx);
	pow(dlcdy,2.0,dlcdy);

	channelSum(dlcdx,dlcdx);
	channelSum(dlcdy,dlcdy);

	dlcdx.col(0) *= 0;
	dlcdy.row(0) *= 0;



	double sigmaH = sigmaS;
	double sigmaHoverSigmaSsquare = (sigmaH*sigmaH/(sigmaS*sigmaS));
	double sigmaHoverSigmaRsquare = (sigmaH*sigmaH/(sigmaR*sigmaR));
	Mat dHdx = sigmaHoverSigmaSsquare + sigmaHoverSigmaRsquare*dlcdx;
	Mat dVdy = sigmaHoverSigmaSsquare + sigmaHoverSigmaRsquare*dlcdy;

	pow(dHdx,0.5,dHdx);
	pow(dVdy,0.5,dVdy);

	transpose(dVdy,dVdy);

	int N = 1;
	Mat F; I.copyTo(F);

	for (int i=0; i<N; i++)
	{
		double sigmaHi = sigmaH * sqrt(3) * pow(2.0, (N -i -1)) / sqrt(pow(4.0,N)-1);
		TransformedDomainRecursiveFilter_Horizontal (F,dHdx,sigmaHi,F,1);
		transpose(F,F);
		TransformedDomainRecursiveFilter_Horizontal (F,dVdy,sigmaHi,F,1);
		transpose(F,F);
	}
	F.convertTo(F,_img.type());
	_F.create(_img.size(),_img.type());
	Mat __F = _F.getMat();
	F.copyTo(__F);
}

void AdaptiveManifoldFilter::TransformedDomainRecursiveFilter_Horizontal(
		InputArray						_Fin,
		InputArray						_dHdx,
		const double					sigma,
		OutputArray						_Fout,
		const int						secondPhaseShift)
{
	double a = exp(-sqrt(2.0)/sigma);
	Mat _F = _Fin.getMat();
	Mat F;
	Mat _V = _dHdx.getMat();
	Mat __V,V;
	_F.copyTo(F);
	_V.copyTo(__V);
	_Fout.create(F.size(),F.type());//if (_Fout.empty())
	Mat Fout = _Fout.getMat();
	int Fchannel = F.channels();
	int Vrow = __V.rows;
	int Vcol = __V.cols;
	int Vchannel = __V.channels();
	float *ptrV;

	if (Fchannel != Vchannel) {
		Mat temp[Fchannel];
		for (int i=0; i<Fchannel; i++){
			temp[i] = __V;
		}
		merge(temp,Fchannel,V);
		Vchannel = V.channels();
	} else {
		__V.copyTo(V);
	}

	int VcolTimesChannel = Vcol*Vchannel;

	ptrV = (float*)V.data;
	for (int j = 0; j<Vrow; j++) {
		for (int i = 0; i<VcolTimesChannel; i++,ptrV++) {
			*(ptrV) = pow (a,*(ptrV));
		}
	}

	for (int i = 1; i<Vcol ; i++){
		F.col(i) += V.col(i).mul(F.col(i-1)-F.col(i));
	}

	if (secondPhaseShift) {
		for (int i = (Vcol-2); i>=0 ; i--){
			F.col(i) += V.col(i+1).mul(F.col(i+1)-F.col(i));
		}
	} else {
		for (int i = (Vcol-2); i>=0 ; i--){
			F.col(i) += V.col(i).mul(F.col(i+1)-F.col(i));
		}
	}

	F.copyTo(Fout);

}

void AdaptiveManifoldFilter::hFilter(
		InputArray						_Fin,
		const double					sigma,
		OutputArray						_Fout)
{

	Mat Fin = _Fin.getMat();
	_Fout.create(Fin.size(),Fin.type());
	Mat Fout,FoutTemp;
	Fout = _Fout.getMat();
	Fout.copyTo(FoutTemp);

	Mat FinOnes = Mat::zeros(Fin.size(),CV_32FC1);
	add(FinOnes,1,FinOnes);
	TransformedDomainRecursiveFilter_Horizontal(Fin,FinOnes,sigma,FoutTemp);

	transpose(FoutTemp,FoutTemp);
	transpose(FinOnes,FinOnes);

	TransformedDomainRecursiveFilter_Horizontal(FoutTemp,FinOnes,sigma,FoutTemp);
	transpose(FoutTemp,FoutTemp);

	FoutTemp.copyTo(Fout);
}

void AdaptiveManifoldFilter::channelSum(
		InputArray						_Fin,
		OutputArray						_Fout)
{
	Mat Fin = _Fin.getMat();
	Mat CloneFin; Fin.copyTo(CloneFin);
	_Fout.create(Fin.size(),CV_32FC1);
	Mat Fout = _Fout.getMat();
	Mat Temp[3];
	split(CloneFin,Temp);
	add(Temp[0],Temp[1],Fout);
	add(Fout,Temp[2],Fout);
}

}



