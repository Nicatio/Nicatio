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
	Size image = f.size();
	Size joint = fJoint.size();
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
		resize(etaK,etaKTemp,image);
		X = fJoint - etaKTemp;
	}

	pow(X,2.0,pixelDistToManifoldSquared);

	///// channel reduction is needed;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	gaussianDistanceWeights = pixelDistToManifoldSquared * oneOverSigmaROverSqrt2Square * -0.5;
	exp(gaussianDistanceWeights,gaussianDistanceWeights);
	psiSplat = gaussianDistanceWeights.mul(f);
	psiSplat.copyTo(psiSplat0);
	minPixelDistToManifoldSquared = min(minPixelDistToManifoldSquared,pixelDistToManifoldSquared);



}

void AdaptiveManifoldFilter::RFFilter(
		InputArray						_img,
		InputArray						_img0,
		OutputArray						_F,
		const double					sigmaS,
		const double					sigmaR,
		InputArray						_jointImage)
{
	Mat I = Mat(_img,CV_32FC1);
	Mat I0 = Mat(_img0,CV_32FC1);
	Mat J;
	if (!_jointImage) {
		J = I;
	} else {
		J = Mat(_jointImage,CV_32FC1);
		if (I.size() != J.size()) {std::cout<<"error"<<std::endl;break;}
	}



}


}


