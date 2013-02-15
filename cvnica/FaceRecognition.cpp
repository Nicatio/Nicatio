/*
 * FaceRecognition.cpp
 *
 *  Created on: 2013. 2. 15.
 *      Author: HDSP
 */


#include "FaceRecognition.h"
using namespace cv;

namespace cvNica {

FaceRecognition::FaceRecognition(void)
{
	setUseOptimized(true);
	setNumThreads(8);
}

FaceRecognition::FaceRecognition(
		int								imagesPerSubject,
		vector<Mat>						referenceImage)
{
	setUseOptimized(true);
	setNumThreads(8);
	nSubject = referenceImage.size();
	if (nSubject%imagesPerSubject==0) {
		refImage = referenceImage;
		nImagesPerSubject = imagesPerSubject;
	} else {
		std::cout<<"Error: invalid imagesPerSubject or number of subjects."<<std::endl;
	}
}

FaceRecognition::~FaceRecognition(void)
{
}

void FaceRecognition::DirectoryRegister(
		string							dir)
{
	DirectoryLocation = dir;
}

void FaceRecognition::Enroll(
		vector<Mat>						referenceImage)
{
	refImage = referenceImage;
	nSubject = refImage.size();
}

void FaceRecognition::Recognition(
		vector<string>					files,
		int								criterion)
{
	_Recognition(refImage,files,criterion);
}

void FaceRecognition::Recognition(
		string							dir,
		string							type,
		int								criterion)
{
	DirectoryLocation = dir;
	vector<string> files = vector<string>();
	if(nicatio::getdirType(dir,type,files,0)){
		cout<< "Error: Invalid file location \n" <<endl;
	}
	_Recognition(refImage,files,criterion);
}


double FaceRecognition::getScore(
		Mat								inputA,
		Mat								inputB,
		int								searchRadius,
		int								criterion)
{
	int upper, lower;
	upper = searchRadius>>1;
	lower = (searchRadius%2)? (-upper):(-upper+1);

	if(inputA.type() != inputB.type()) return -1;
	if(inputA.size() != inputB.size()) return -1;
	// based on offset of the reference image

	Mat Asum,Asqsum;
	Mat Bsum,Bsqsum;

	integral(inputA,Asum,Asqsum);
	integral(inputB,Bsum,Bsqsum);

	if (criterion == METHOD_CORR){
		for (int i=lower; i<=upper; i++) {
			for (int j=lower; j<=upper; j++) {


			}
		}
	}

}

void FaceRecognition::_Recognition(
		vector<Mat>						referenceImage,
		vector<string>					files,
		int								criterion)
{
	int nFiles = files.size();
	RecognitionResult = Mat(nSubject,nFiles,CV_32FC1);
	RecognitionPositionX = Mat(nSubject,nFiles,CV_8UC1);
	RecognitionPositionY = Mat(nSubject,nFiles,CV_8UC1);

	for (unsigned int i = 0; i < nFiles; i++) {
		cout << files[i] << endl;
		Mat testImage;
		testImage = imread( DirectoryLocation+"\\"+files[i], -1 );

		for (unsigned int j = 0; j < nSubject; j++){

		}
	}
}




}
