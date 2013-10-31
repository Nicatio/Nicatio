/*
 * FaceRecognition.cpp
 *
 *  Created on: 2013. 2. 15.
 *      Author: Nicatio
 */


#include "FaceRecognition.h"
using namespace cv;

namespace cvNica {

FaceRecognition::FaceRecognition(
		int								refImagesPerSubject,
		int								refImageorder,
		int								testImageorder,
		vector<Mat>						referenceImage)
{
	setUseOptimized(true);
	setNumThreads(8);
	nRefImageOrder = refImageorder;
	nTestImageOrder = testImageorder;
	nSubject = referenceImage.size();
	nCorrect = 0;
	nFiles = 0;
	nBadImages = 0;
	if (nSubject%refImagesPerSubject==0) {
		refImage = referenceImage;
		nRefImagesPerSubject = refImagesPerSubject;
		nSearchRadius = 5;
	} else {
		std::cout<<"Error: invalid imagesPerSubject or number of subjects."<<std::endl;
	}
}

FaceRecognition::FaceRecognition(
		string							dir,
		string							referenceInfoFileLocation,
		string							databaseType)
{

	setUseOptimized(true);
	setNumThreads(8);

	if (databaseType == "integrated") bDatabaseType = 0;
	else if (databaseType == "separated") bDatabaseType = 1;
	else bDatabaseType = -1;

	nSubject = 0;
	nRefImagesPerSubject = 0;
	nTestImageOrder = 0;
	nRefImageOrder = 0;
	nSearchRadius = 5;
	nCorrect = 0;
	nFiles = 0;
	nBadImages = 0;
	ifstream read(referenceInfoFileLocation.c_str(), ifstream::in);
	if (read.bad()) {
		std::cout<<"Error: invalid imagesPerSubject or number of subjects."<<std::endl;
	} else {
		for (;;) {
			string str;
			getline(read,str);
			if(str.c_str()[0]=='*') continue;
			else if(str.c_str()[0]=='#') break;
			else {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(str,"=");
				if(tokens.size()<2) continue;
				if(tokens[0] == "n") istringstream (tokens[1]) >> nSubject;
				if(tokens[0] == "r") istringstream (tokens[1]) >> nRefImagesPerSubject;
				if(tokens[0] == "to") istringstream (tokens[1]) >> nTestImageOrder;
				if(tokens[0] == "ro") istringstream (tokens[1]) >> nRefImageOrder;
			}
		}
		Mat aveImg;
		refImage.resize(nSubject * nRefImagesPerSubject);
		int i;
		for (i=0;;i++) {
			string str;
			getline(read,str);
			if(str=="") break;
			vector<string> tokens = nicatio::StringTokenizer::getTokens(str,"\n\r");
			imread( dir+"/"+tokens[0], -1 ).copyTo(refImage[i]);
			if (i==0){
				aveImg=Mat::zeros(refImage[i].size(),CV_32FC1);
			}
			Mat temp; refImage[i].convertTo(temp,CV_32FC1);
			aveImg += temp;
			cout<<"complete: "<<i<<endl;
		}
		aveImg/=nSubject*nRefImagesPerSubject;
		Mat aveImg2; aveImg.convertTo(aveImg2,CV_8UC1);
		imwrite("aveimg.bmp",aveImg2);
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
		int								DBname,
		int								criterion)
{
	_Recognition(refImage,files,DBname,criterion);
}

//void FaceRecognition::Recognition(
//		string							dir,
//		string							type,
//		int								DBname,
//		int								criterion,
//		int								startAngle,
//		int								endAngle)
//{
//	DirectoryLocation = dir;
//	vector<string> files = vector<string>();
//	if(nicatio::getdirType(dir,type,files,0)){
//		cout<< "Error: Invalid file location \n" <<endl;
//	}
//	_Recognition(refImage,files,DBname,criterion,startAngle,endAngle);
//}

void FaceRecognition::Recognition(
		string							dir,
		string							type,
		int								DBname,
		int								criterion,
		int								startAngle,
		int								endAngle,
		int								startX,
		int								startY,
		int								endX,
		int								endY)
{
	DirectoryLocation = dir;
	vector<string> files = vector<string>();
	if(nicatio::getdirType(dir,type,files,0)){
		cout<< "Error: Invalid file location \n" <<endl;
	}
	_Recognition(refImage,files,DBname,criterion,startAngle,endAngle,startX,startY,endX,endY);
}


void FaceRecognition::getScoreTestImageBased(
		const vector<Mat>				inputA,
		const Mat						inputB,
		const int						nFileIndex,
		const int						searchRadius,
		const int						criterion)
{

	int nTotalReferenceImages = inputA.size();
	int upper, lower;
	upper = searchRadius>>1;
	lower = (searchRadius%2)? (-upper):(-upper+1);
	float max=-2;
	ushort maxSubjectIndex = 0;
	Mat inputB32; inputB.convertTo(inputB32,CV_32F);
	Mat inputBB32; multiply (inputB32,inputB32,inputBB32);

	int w = inputA[0].size().width;
	int h = inputA[0].size().height;

	int sRsize = searchRadius*searchRadius;
	int *a__ = (int*)malloc(sRsize*6*sizeof(int));
	float *inputB_ = (float*)malloc(sRsize*2*sizeof(float));
	int *ptr_a_ = a__;
	int *ptr_b_ = a__+sRsize;
	int *ptr_c_ = ptr_b_+sRsize;
	int *ptr_d_ = ptr_c_+sRsize;
	int *ptr__a = ptr_d_+sRsize;
	int *ptr__b = ptr__a+sRsize;
	float *ptr_inputB_ = inputB_;
	float *ptr_inputBB_ = inputB_+sRsize;
	char *ptr_rpx = &(RecognitionPositionX.at<char>(nFileIndex,0));
	char *ptr_rpy = &(RecognitionPositionY.at<char>(nFileIndex,0));
	float *ptr_rs = &(RecognitionScore.at<float>(nFileIndex,0));

	for (int i=lower; i<=upper; i++) {
		for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {

			if(i<0) { 	*(ptr_a_) = -i;		*(ptr__a) = 0;		*(ptr_c_) = w+i; }
			else 	{	*(ptr_a_) = 0; 		*(ptr__a) = i;		*(ptr_c_) = w-i; }
			if(j<0) {	*(ptr_b_) = -j;		*(ptr__b) = 0;		*(ptr_d_) = h+j; }
			else 	{	*(ptr_b_) = 0;		*(ptr__b) = j;		*(ptr_d_) = h-j; }

			Mat inputBCrop=inputB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
			Mat inputBBCrop=inputBB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
			Mat multResult(*(ptr_c_),*(ptr_d_),CV_32F);

			*(ptr_inputBB_) = sum(inputBBCrop)[0];
			*(ptr_inputB_) = sum(inputBCrop)[0];
		}
	}


	if (criterion == METHOD_CORR){
		for (int j = 0; j < nTotalReferenceImages; j++,ptr_rpx++,ptr_rpy++,ptr_rs++){
			float maxCorrCoef = -1;
			int posX = 0;
			int posY = 0;

			if(inputA[j].type() != inputB.type()) return;
			if(inputA[j].size() != inputB.size()) return;
			// based on offset of the reference image

			ptr_a_ = a__;
			ptr_b_ = a__+sRsize;
			ptr_c_ = ptr_b_+sRsize;
			ptr_d_ = ptr_c_+sRsize;
			ptr__a = ptr_d_+sRsize;
			ptr__b = ptr__a+sRsize;
			ptr_inputB_ = inputB_;
			ptr_inputBB_ = inputB_+sRsize;


			Mat inputA32; inputA[j].convertTo(inputA32,CV_32F);
			Mat inputAA32; multiply (inputA32,inputA32,inputAA32);


			for (int i=lower; i<=upper; i++) {
				for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {
					float Asq,Bsq,Ms;
					float As,Bs;

					int a_=*(ptr_a_),b_=*(ptr_b_),c_=*(ptr_c_),d_=*(ptr_d_);
					int _a=*(ptr__a),_b=*(ptr__b);

					Mat inputACrop=inputA32(Rect (a_,b_,c_,d_));
					Mat inputBCrop=inputB32(Rect (_a,_b,c_,d_));
					Mat inputAACrop=inputAA32(Rect (a_,b_,c_,d_));
					Mat multResult(c_,d_,CV_32F);
					multiply (inputACrop,inputBCrop,multResult);

					Ms = sum(multResult)[0];
					Asq = sum(inputAACrop)[0];
					Bsq = *(ptr_inputBB_);
					As = sum(inputACrop)[0];
					Bs = *(ptr_inputB_);

					int s = c_*d_;

					float refSigma = sqrt((double)s*Asq-(double)As*As);
					float tesSigma = sqrt((double)s*Bsq-(double)Bs*Bs);
					float corrCoef = ((double)s*Ms - (double)As*Bs)/(refSigma*tesSigma);
					if (refSigma*tesSigma == 0) continue;
					if (maxCorrCoef < corrCoef) {
						maxCorrCoef = corrCoef;
						posX = i;
						posY = j;
					}
				}
			}

			*(ptr_rpx) = posX;
			*(ptr_rpy) = posY;
			*(ptr_rs)  = maxCorrCoef;
			if (maxCorrCoef>max) {
				max = maxCorrCoef;
				maxSubjectIndex = j;
			}
		}

		RecognitionResult.at<ushort>(nFileIndex,0) = maxSubjectIndex;
	} else if (criterion == METHOD_L2NORM){
		max=1e100;
		for (int j = 0; j < nTotalReferenceImages; j++,ptr_rpx++,ptr_rpy++,ptr_rs++){
			float maxCorrCoef = 1e100;
			int posX = 0;
			int posY = 0;

			if(inputA[j].type() != inputB.type()) return;
			if(inputA[j].size() != inputB.size()) return;
			// based on offset of the reference image

			ptr_a_ = a__;
			ptr_b_ = a__+sRsize;
			ptr_c_ = ptr_b_+sRsize;
			ptr_d_ = ptr_c_+sRsize;
			ptr__a = ptr_d_+sRsize;
			ptr__b = ptr__a+sRsize;
			ptr_inputB_ = inputB_;
			ptr_inputBB_ = inputB_+sRsize;


			Mat inputA32; inputA[j].convertTo(inputA32,CV_32F);


			for (int i=lower; i<=upper; i++) {
				for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {
					float Asq,Bsq,Ms;
					float As,Bs;

					int a_=*(ptr_a_),b_=*(ptr_b_),c_=*(ptr_c_),d_=*(ptr_d_);
					int _a=*(ptr__a),_b=*(ptr__b);

					Mat inputACrop=inputA32(Rect (a_,b_,c_,d_));
					Mat inputBCrop=inputB32(Rect (_a,_b,c_,d_));
					Mat diff = inputACrop-inputBCrop;
					Mat multResult(c_,d_,CV_32F);
					multiply (diff,diff,multResult);

					Ms = sum(multResult)[0];

					if (maxCorrCoef > Ms) {
						maxCorrCoef = Ms;
						posX = i;
						posY = j;
					}
				}
			}

			*(ptr_rpx) = posX;
			*(ptr_rpy) = posY;
			*(ptr_rs)  = maxCorrCoef;
			if (maxCorrCoef<max) {
				max = maxCorrCoef;
				maxSubjectIndex = j;
			}
		}

		RecognitionResult.at<ushort>(nFileIndex,0) = maxSubjectIndex;
	}
}


void FaceRecognition::getScoreTestImageBasedWeight(
		const vector<Mat>				inputA,
		const Mat						inputB,
		const int						nFileIndex,
		const int						searchRadius,
		const int						criterion)
{

	int nTotalReferenceImages = inputA.size();
	int upper, lower;
	upper = searchRadius>>1;
	lower = (searchRadius%2)? (-upper):(-upper+1);
	float max=-2;
	ushort maxSubjectIndex = 0;

	Mat t_ = imread("faceindexweight12eye.bmp",-1);
	Mat t;
	t_.convertTo(t,CV_32F);
	Mat inputB32_, inputB32; inputB.convertTo(inputB32_,CV_32F);
	multiply (inputB32_,t,inputB32);
	Mat inputBB32_,inputBB32; multiply (inputB32_,inputB32_,inputBB32_);
	multiply (inputBB32_,t,inputBB32);



	int w = inputA[0].size().width;
	int h = inputA[0].size().height;

	int sRsize = searchRadius*searchRadius;
	int *a__ = (int*)malloc(sRsize*6*sizeof(int));
	float *inputB_ = (float*)malloc(sRsize*2*sizeof(float));
	int *ptr_a_ = a__;
	int *ptr_b_ = a__+sRsize;
	int *ptr_c_ = ptr_b_+sRsize;
	int *ptr_d_ = ptr_c_+sRsize;
	int *ptr__a = ptr_d_+sRsize;
	int *ptr__b = ptr__a+sRsize;
	float *ptr_inputB_ = inputB_;
	float *ptr_inputBB_ = inputB_+sRsize;
	char *ptr_rpx = &(RecognitionPositionX.at<char>(nFileIndex,0));
	char *ptr_rpy = &(RecognitionPositionY.at<char>(nFileIndex,0));
	float *ptr_rs = &(RecognitionScore.at<float>(nFileIndex,0));

	for (int i=lower; i<=upper; i++) {
		for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {

			if(i<0) { 	*(ptr_a_) = -i;		*(ptr__a) = 0;		*(ptr_c_) = w+i; }
			else 	{	*(ptr_a_) = 0; 		*(ptr__a) = i;		*(ptr_c_) = w-i; }
			if(j<0) {	*(ptr_b_) = -j;		*(ptr__b) = 0;		*(ptr_d_) = h+j; }
			else 	{	*(ptr_b_) = 0;		*(ptr__b) = j;		*(ptr_d_) = h-j; }

			Mat inputBCrop=inputB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
			Mat inputBBCrop=inputBB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));

			*(ptr_inputBB_) = sum(inputBBCrop)[0];
			*(ptr_inputB_) = sum(inputBCrop)[0];
		}
	}


	if (criterion == METHOD_CORR){
		for (int k = 0; k < nTotalReferenceImages; k++,ptr_rpx++,ptr_rpy++,ptr_rs++){
			float maxCorrCoef = -1;
			int posX = 0;
			int posY = 0;

			if(inputA[k].type() != inputB.type()) return;
			if(inputA[k].size() != inputB.size()) return;
			// based on offset of the reference image

			ptr_a_ = a__;
			ptr_b_ = a__+sRsize;
			ptr_c_ = ptr_b_+sRsize;
			ptr_d_ = ptr_c_+sRsize;
			ptr__a = ptr_d_+sRsize;
			ptr__b = ptr__a+sRsize;
			ptr_inputB_ = inputB_;
			ptr_inputBB_ = inputB_+sRsize;


			Mat inputA32; inputA[k].convertTo(inputA32,CV_32F);
			Mat inputAA32; multiply (inputA32,inputA32,inputAA32);


			for (int i=lower; i<=upper; i++) {
				for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {
					float Asq,Bsq,Ms;
					float As,Bs;

					int a_=*(ptr_a_),b_=*(ptr_b_),c_=*(ptr_c_),d_=*(ptr_d_);
					int _a=*(ptr__a),_b=*(ptr__b);

					Mat inputACrop_=inputA32(Rect (a_,b_,c_,d_));
					Mat inputAACrop_=inputAA32(Rect (a_,b_,c_,d_));
					//Mat tCrop=t(Rect (a_,b_,c_,d_));
					Mat tCrop=t(Rect (_a,_b,c_,d_));
					Mat inputACrop;
					multiply (inputACrop_,tCrop,inputACrop);
					Mat inputAACrop;
					multiply (inputAACrop_,tCrop,inputAACrop);

					Mat inputBCrop=inputB32_(Rect (_a,_b,c_,d_));

					Mat multResult_(c_,d_,CV_32F);
					Mat multResult(c_,d_,CV_32F);
					multiply (inputACrop_,inputBCrop,multResult_);
					multiply (multResult_,tCrop,multResult);


					Ms = sum(multResult)[0];
					Asq = sum(inputAACrop)[0];
					Bsq = *(ptr_inputBB_);
					As = sum(inputACrop)[0];
					Bs = *(ptr_inputB_);

					int s = sum(tCrop)[0];

					float refSigma = sqrt((double)s*Asq-(double)As*As);
					float tesSigma = sqrt((double)s*Bsq-(double)Bs*Bs);
					float corrCoef = ((double)s*Ms - (double)As*Bs)/(refSigma*tesSigma);
					if (refSigma*tesSigma == 0) continue;
					if (maxCorrCoef < corrCoef) {
						maxCorrCoef = corrCoef;
						posX = i;
						posY = j;
					}
				}
			}

			*(ptr_rpx) = posX;
			*(ptr_rpy) = posY;
			*(ptr_rs)  = maxCorrCoef;
			if (maxCorrCoef>max) {
				max = maxCorrCoef;
				maxSubjectIndex = k;
			}
		}

		RecognitionResult.at<ushort>(nFileIndex,0) = maxSubjectIndex;
	}
}

void FaceRecognition::getScoreTestImageBasedCrop(
		const vector<Mat>				inputA,
		const Mat						inputB,
		const int						nFileIndex,
		const int						searchRadius,
		const int						criterion,
		int								startX,
		int								startY,
		int								endX,
		int								endY)
{

	int nTotalReferenceImages = inputA.size();
	int upper, lower;
	upper = searchRadius>>1;
	lower = (searchRadius%2)? (-upper):(-upper+1);
	float max=-2;
	ushort maxSubjectIndex = 0;
	Mat inputB32; inputB.convertTo(inputB32,CV_32F);
	Mat inputBB32; multiply (inputB32,inputB32,inputBB32);

	int w = endX-startX+1;//inputA[0].size().width;
	int h = endY-startY+1;//inputA[0].size().height;
	int tW = inputA[0].size().width-1;
	int tH = inputA[0].size().height-1;
	int sRsize = searchRadius*searchRadius;
	int *a__ = (int*)malloc(sRsize*6*sizeof(int));
	float *inputB_ = (float*)malloc(sRsize*2*sizeof(float));
	int *ptr_a_ = a__;
	int *ptr_b_ = a__+sRsize;
	int *ptr_c_ = ptr_b_+sRsize;
	int *ptr_d_ = ptr_c_+sRsize;
	int *ptr__a = ptr_d_+sRsize;
	int *ptr__b = ptr__a+sRsize;
	float *ptr_inputB_ = inputB_;
	float *ptr_inputBB_ = inputB_+sRsize;
	char *ptr_rpx = &(RecognitionPositionX.at<char>(nFileIndex,0));
	char *ptr_rpy = &(RecognitionPositionY.at<char>(nFileIndex,0));
	float *ptr_rs = &(RecognitionScore.at<float>(nFileIndex,0));

	for (int i=lower; i<=upper; i++) {
		for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {

//			*(ptr_a_) = startX+i;	*(ptr__a) = startX;
//			*(ptr_b_) = startY+j;	*(ptr__b) = startY;
//			*(ptr_c_) = w;			*(ptr_d_) = h;
//
//			int tempEndX = endX+i;
//			int tempEndY = endY+j;
//
//			if (*(ptr_a_)<0) {	*(ptr_a_) = 0; *(ptr_c_) = w+i;}
//			if (*(ptr_b_)<0) {	*(ptr_b_) = 0; *(ptr_d_) = h+j;}
//			if (tempEndX>tW) {	*(ptr_c_) = w-i;}
//			if (tempEndY>tH) {	*(ptr_d_) = h-j;}

			if(i<0) { 	*(ptr_a_) = startX-i;	*(ptr__a) = startX;		*(ptr_c_) = w+i; }
			else 	{	*(ptr_a_) = startX; 	*(ptr__a) = startX+i;	*(ptr_c_) = w-i; }
			if(j<0) {	*(ptr_b_) = startY-j;	*(ptr__b) = startY;		*(ptr_d_) = h+j; }
			else 	{	*(ptr_b_) = startY;		*(ptr__b) = startY+j;	*(ptr_d_) = h-j; }

			Mat inputBCrop=inputB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
			Mat inputBBCrop=inputBB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
			//Mat multResult(*(ptr_c_),*(ptr_d_),CV_32F);

			*(ptr_inputBB_) = sum(inputBBCrop)[0];
			*(ptr_inputB_) = sum(inputBCrop)[0];
		}
	}


	if (criterion == METHOD_CORR){
		for (int j = 0; j < nTotalReferenceImages; j++,ptr_rpx++,ptr_rpy++,ptr_rs++){
			float maxCorrCoef = -1;
			int posX = 0;
			int posY = 0;

			if(inputA[j].type() != inputB.type()) return;
			if(inputA[j].size() != inputB.size()) return;
			// based on offset of the reference image

			ptr_a_ = a__;
			ptr_b_ = a__+sRsize;
			ptr_c_ = ptr_b_+sRsize;
			ptr_d_ = ptr_c_+sRsize;
			ptr__a = ptr_d_+sRsize;
			ptr__b = ptr__a+sRsize;
			ptr_inputB_ = inputB_;
			ptr_inputBB_ = inputB_+sRsize;


			Mat inputA32; inputA[j].convertTo(inputA32,CV_32F);
			Mat inputAA32; multiply (inputA32,inputA32,inputAA32);


			for (int i=lower; i<=upper; i++) {
				for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {
					float Asq,Bsq,Ms;
					float As,Bs;

					int a_=*(ptr_a_),b_=*(ptr_b_),c_=*(ptr_c_),d_=*(ptr_d_);
					int _a=*(ptr__a),_b=*(ptr__b);

					Mat inputACrop=inputA32(Rect (a_,b_,c_,d_));
					Mat inputBCrop=inputB32(Rect (_a,_b,c_,d_));
					Mat inputAACrop=inputAA32(Rect (a_,b_,c_,d_));
					Mat multResult(c_,d_,CV_32F);
					multiply (inputACrop,inputBCrop,multResult);

					Ms = sum(multResult)[0];
					Asq = sum(inputAACrop)[0];
					Bsq = *(ptr_inputBB_);
					As = sum(inputACrop)[0];
					Bs = *(ptr_inputB_);

					int s = c_*d_;

					float refSigma = sqrt((double)s*Asq-(double)As*As);
					float tesSigma = sqrt((double)s*Bsq-(double)Bs*Bs);
					float corrCoef = ((double)s*Ms - (double)As*Bs)/(refSigma*tesSigma);
					if (refSigma*tesSigma == 0) continue;
					if (maxCorrCoef < corrCoef) {
						maxCorrCoef = corrCoef;
						posX = i;
						posY = j;
					}
				}
			}

			*(ptr_rpx) = posX;
			*(ptr_rpy) = posY;
			*(ptr_rs)  = maxCorrCoef;
			if (maxCorrCoef>max) {
				max = maxCorrCoef;
				maxSubjectIndex = j;
			}
		}

		RecognitionResult.at<ushort>(nFileIndex,0) = maxSubjectIndex;
	}
}


void FaceRecognition::getScoreTestImageBasedRotation(
		const vector<Mat>				inputA,
		const Mat						_inputB,
		const int						nFileIndex,
		const int						searchRadius,
		const int						criterion,
		const int						startAngle,
		const int						endAngle)
{
	int nTotalReferenceImages = inputA.size();
	int upper, lower;
	upper = searchRadius>>1;
	lower = (searchRadius%2)? (-upper):(-upper+1);
	float max=-2;
	ushort maxSubjectIndex = 0;

	if (criterion == METHOD_CORR){
		char *ptr_rpx = &(RecognitionPositionX.at<char>(nFileIndex,0));
		char *ptr_rpy = &(RecognitionPositionY.at<char>(nFileIndex,0));
		float *ptr_rs = &(RecognitionScore.at<float>(nFileIndex,0));
		for (int j = 0; j < nTotalReferenceImages; j++,ptr_rpx++,ptr_rpy++,ptr_rs++){
			float maxCorrCoef = -1;
			int posX = 0;
			int posY = 0;
			int posAngle = 0;
			for (int angle = startAngle; angle < endAngle; angle++){
				Mat inputB = cvNica::rotateImage(_inputB, angle, 1);
				Mat inputB32; inputB.convertTo(inputB32,CV_32F);
				Mat inputBB32; multiply (inputB32,inputB32,inputBB32);

				int w = inputA[0].size().width;
				int h = inputA[0].size().height;

				int sRsize = searchRadius*searchRadius;
				int *a__ = (int*)malloc(sRsize*6*sizeof(int));
				float *inputB_ = (float*)malloc(sRsize*2*sizeof(float));
				int *ptr_a_ = a__;
				int *ptr_b_ = a__+sRsize;
				int *ptr_c_ = ptr_b_+sRsize;
				int *ptr_d_ = ptr_c_+sRsize;
				int *ptr__a = ptr_d_+sRsize;
				int *ptr__b = ptr__a+sRsize;
				float *ptr_inputB_ = inputB_;
				float *ptr_inputBB_ = inputB_+sRsize;


				for (int i=lower; i<=upper; i++) {
					for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {

						if(i<0) { 	*(ptr_a_) = -i;		*(ptr__a) = 0;		*(ptr_c_) = w+i; }
						else 	{	*(ptr_a_) = 0; 		*(ptr__a) = i;		*(ptr_c_) = w-i; }
						if(j<0) {	*(ptr_b_) = -j;		*(ptr__b) = 0;		*(ptr_d_) = h+j; }
						else 	{	*(ptr_b_) = 0;		*(ptr__b) = j;		*(ptr_d_) = h-j; }

						Mat inputBCrop=inputB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
						Mat inputBBCrop=inputBB32(Rect (*(ptr__a),*(ptr__b),*(ptr_c_),*(ptr_d_)));
						Mat multResult(*(ptr_c_),*(ptr_d_),CV_32F);

						*(ptr_inputBB_) = sum(inputBBCrop)[0];
						*(ptr_inputB_) = sum(inputBCrop)[0];
					}
				}






				if(inputA[j].type() != inputB.type()) return;
				if(inputA[j].size() != inputB.size()) return;
				// based on offset of the reference image

				ptr_a_ = a__;
				ptr_b_ = a__+sRsize;
				ptr_c_ = ptr_b_+sRsize;
				ptr_d_ = ptr_c_+sRsize;
				ptr__a = ptr_d_+sRsize;
				ptr__b = ptr__a+sRsize;
				ptr_inputB_ = inputB_;
				ptr_inputBB_ = inputB_+sRsize;


				Mat inputA32; inputA[j].convertTo(inputA32,CV_32F);
				Mat inputAA32; multiply (inputA32,inputA32,inputAA32);


				for (int i=lower; i<=upper; i++) {
					for (int j=lower; j<=upper; j++,ptr_a_++,ptr_b_++,ptr_c_++,ptr_d_++,ptr__a++,ptr__b++,ptr_inputB_++,ptr_inputBB_++) {
						float Asq,Bsq,Ms;
						float As,Bs;

						int a_=*(ptr_a_),b_=*(ptr_b_),c_=*(ptr_c_),d_=*(ptr_d_);
						int _a=*(ptr__a),_b=*(ptr__b);

						Mat inputACrop=inputA32(Rect (a_,b_,c_,d_));
						Mat inputBCrop=inputB32(Rect (_a,_b,c_,d_));
						Mat inputAACrop=inputAA32(Rect (a_,b_,c_,d_));
						Mat multResult(c_,d_,CV_32F);
						multiply (inputACrop,inputBCrop,multResult);

						Ms = sum(multResult)[0];
						Asq = sum(inputAACrop)[0];
						Bsq = *(ptr_inputBB_);
						As = sum(inputACrop)[0];
						Bs = *(ptr_inputB_);

						int s = c_*d_;

						float refSigma = sqrt((double)s*Asq-(double)As*As);
						float tesSigma = sqrt((double)s*Bsq-(double)Bs*Bs);
						float corrCoef = ((double)s*Ms - (double)As*Bs)/(refSigma*tesSigma);
						if (refSigma*tesSigma == 0) continue;
						if (maxCorrCoef < corrCoef) {
							maxCorrCoef = corrCoef;
							posX = i;
							posY = j;
							posAngle = angle;
						}
					}
				}
			}
			*(ptr_rpx) = posX;
			*(ptr_rpy) = posY;
			*(ptr_rs)  = maxCorrCoef;
			if (maxCorrCoef>max) {
				max = maxCorrCoef;
				maxSubjectIndex = j;
			}
		}

		RecognitionResult.at<ushort>(nFileIndex,0) = maxSubjectIndex;
	}
}


void FaceRecognition::getPCAscore(
		const Mat						inputB,
		const int						nFileIndex)
{
	int nTotalReferenceImages = nSubject*nRefImagesPerSubject;
	Mat vec = inputB.reshape(1,1), coeffs;
	pca.project(vec, coeffs);

	char *ptr_rpx = &(RecognitionPositionX.at<char>(nFileIndex,0));
	char *ptr_rpy = &(RecognitionPositionY.at<char>(nFileIndex,0));
	float *ptr_rs = &(RecognitionScore.at<float>(nFileIndex,0));

	float maxCorrCoef = -1;
	ushort maxSubjectIndex = 0;

	for (int j = 0; j < nTotalReferenceImages; j++) {
		Mat result;
		matchTemplate(coeffs, pcaRefCoeffs[j], result, CV_TM_CCOEFF_NORMED);
		//matchTemplate(coeffs, pcaRefCoeffs[j], result, CV_TM_SQDIFF_NORMED);
//		Mat temp = coeffs - pcaRefCoeffs[j];
//		Mat tempsq;
//		multiply(temp,temp,tempsq);
//		Scalar ttt = sum(tempsq);
//		float r = (float)ttt.val[0];
		float r = result.at<float>(0,0);
		//cout <<"D- "<< r<<endl;
		if (r > maxCorrCoef) {
			maxCorrCoef = r;
			maxSubjectIndex = (ushort) j;
			*(ptr_rs)  = maxCorrCoef;
		}
	}

	*(ptr_rpx) = 0;
	*(ptr_rpy) = 0;

	RecognitionResult.at<ushort>(nFileIndex,0) = maxSubjectIndex;

}

void FaceRecognition::_Recognition(
		vector<Mat>						referenceImage,
		vector<string>					files,
		int								DBname,
		int								criterion,
		int								startAngle,
		int								endAngle,
		int								startX,
		int								startY,
		int								endX,
		int								endY)
{
	nFiles = files.size();
	int nTotalReferenceImages = nSubject*nRefImagesPerSubject;
	RecognitionScore = Mat(nFiles,nTotalReferenceImages,CV_32FC1);
	RecognitionPositionX = Mat(nFiles,nTotalReferenceImages,CV_8SC1);
	RecognitionPositionY = Mat(nFiles,nTotalReferenceImages,CV_8SC1);
	RecognitionResult = Mat(nFiles,1,CV_16UC1);

	if(DBname == DB_YALEB) {
		int nis[5] = {7,12,12,14,19};
		nImagesSubset.assign(nis,nis+5);
		getBadImageInfo(files,1);
	}
	if (criterion == METHOD_PCA) {
		Mat data = asRowMatrix(referenceImage, CV_32FC1);
		int num_components = nTotalReferenceImages-1;
		pcaRefCoeffs.resize(nTotalReferenceImages);

		cout << "PCA Training";
		pca(data, Mat(), CV_PCA_DATA_AS_ROW, num_components);
		cout << " ... Done" << endl;

		for (int i = 0; i < nTotalReferenceImages; i++) {
			cout << "PCA coeffs: "<< i;
			pcaRefCoeffs[i] = Mat(1, num_components, CV_32FC1);
			Mat vec = refImage[i].reshape(1,1), coeffs;
			pca.project(vec, pcaRefCoeffs[i]);
			cout << " ...Done"<< endl;
			//vec.convertTo(pcaRefVec[i],CV_32FC1);
		}
		for (int i = 0; i < nFiles; i++) {
			cout << files[i] << endl;
			Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
			double t=(double)getTickCount();
			getPCAscore(testImage, i);
			t = ((double)getTickCount() - t)/getTickFrequency();
			cout << "Matching Time : " << t << " sec" << endl;
		}
	} else {

		if (startX != endX) {
			for (int i = 0; i < nFiles; i++) {
				cout << files[i] << endl;
				Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
				double t=(double)getTickCount();
				getScoreTestImageBasedCrop(referenceImage, testImage, i, nSearchRadius, criterion, startX, startY, endX, endY);
				t = ((double)getTickCount() - t)/getTickFrequency();
				cout << "Registration Time : " << t << " sec" << endl;
			}
		}
		else {
			if (startAngle == endAngle) {
				for (int i = 0; i < nFiles; i++) {
					cout << files[i] << endl;
					Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
					double t=(double)getTickCount();
					getScoreTestImageBased(referenceImage, testImage, i, nSearchRadius, criterion);
					t = ((double)getTickCount() - t)/getTickFrequency();
					cout << "Registration Time : " << t << " sec" << endl;
				}
			} else {
				for (int i = 0; i < nFiles; i++) {
					cout << files[i] << endl;
					Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
					double t=(double)getTickCount();
					getScoreTestImageBasedRotation(referenceImage, testImage, i, nSearchRadius, criterion, startAngle, endAngle);
					t = ((double)getTickCount() - t)/getTickFrequency();
					cout << "Registration Time : " << t << " sec" << endl;
				}
			}
		}
//		else if (startAngle != endAngle) {
//				for (int i = 0; i < nFiles; i++) {
//					cout << files[i] << endl;
//					Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
//					double t=(double)getTickCount();
//					getScoreTestImageBasedRotation(referenceImage, testImage, i, nSearchRadius, criterion, startAngle, endAngle);
//					t = ((double)getTickCount() - t)/getTickFrequency();
//					cout << "Registration Time : " << t << " sec" << endl;
//				}
//			} else {
//				for (int i = 0; i < nFiles; i++) {
//					cout << files[i] << endl;
//					Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
//					double t=(double)getTickCount();
//					getScoreTestImageBasedWeight(referenceImage, testImage, i, nSearchRadius, criterion);
//					t = ((double)getTickCount() - t)/getTickFrequency();
//					cout << "Registration Time : " << t << " sec" << endl;
//				}
//			}

	}
	cout <<"done"<<endl;
}



//void FaceRecognition::_Recognition(
//		vector<Mat>						referenceImage,
//		vector<string>					files,
//		int								DBname,
//		int								criterion)
//{
//	int nFiles = files.size();
//	int nTotalReferenceImages = nSubject*nRefImagesPerSubject;
//	RecognitionScore = Mat(nTotalReferenceImages,nFiles,CV_32FC1);
//	RecognitionPositionX = Mat(nTotalReferenceImages,nFiles,CV_8SC1);
//	RecognitionPositionY = Mat(nTotalReferenceImages,nFiles,CV_8SC1);
//	RecognitionResult = Mat(1,nFiles,CV_8SC1);
//
//	if(DBname == DB_YALEB) {
//		BadImage = Mat::zeros(1,nFiles,CV_8SC1);
//		for (int i = 0; i < nFiles; i++) {
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				BadImage.at<char>(0,i) = 1;
//
//			}
//		}
//	}
//
//	for (int i = 0; i < nFiles; i++) {
//		cout << files[i] << endl;
//		Mat testImage = imread( DirectoryLocation+"\\"+files[i], -1 );
//		float max=-2;
//		char maxSubjectIndex = 0;
//		double t=(double)getTickCount();
//
//		for (int j = 0; j < nTotalReferenceImages; j++){
//			float score = getScore(referenceImage[j],testImage,nSearchRadius,criterion,RecognitionPositionX.at<char>(j,i),RecognitionPositionY.at<char>(j,i));
//			RecognitionScore.at<float>(j,i) = score;
//			if (score>max) {
//				max = score;
//				maxSubjectIndex = j;
//			}
//			cout <<" " << (float) RecognitionScore.at<float>(j,i) << " " << (int)RecognitionPositionX.at<char>(j,i) <<" " << (int)RecognitionPositionY.at<char>(j,i) <<" " <<endl;
//		}
//		RecognitionResult.at<char>(0,i) = maxSubjectIndex;
//		t = ((double)getTickCount() - t)/getTickFrequency();
//		cout << "Registration Time : " << t << " sec" << endl;
//		//cout <<" [" << (int) RecognitionResult.at<char>(0,i) <<"] "<<endl;
//	}
//	cout <<"done"<<endl;
//}

float FaceRecognition::getAccuracy(
		vector<string>						files)
{
	if (RecognitionResult.empty()) return -1;
	int h = RecognitionResult.size().height;
	int nTestImagesPerSubject = h/nSubject;
	int correctCounter=0;
	ofstream FileOut;
	FileOut.open("error.txt",(ios::out));
	if (!nTestImageOrder) {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++) {
				if ((RecognitionResult.at<ushort>(i,0)/nRefImagesPerSubject) == ((i/nTestImagesPerSubject)%nSubject)) {
					correctCounter++;
				} else {
					FileOut<<files[i]<<endl;
				}
			}
		} else {
			for (int i=0; i<h; i++) {
				if (RecognitionResult.at<ushort>(i,0)%nSubject == ((i/nTestImagesPerSubject)%nSubject)) {
					correctCounter++;
				} else {
					FileOut<<files[i]<<endl;
				}
			}
		}
	} else {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++) {
				if ((RecognitionResult.at<ushort>(i,0)/nRefImagesPerSubject) == (i%nSubject)) {
					correctCounter++;
				} else {
					FileOut<<files[i]<<endl;
				}
			}
		} else {
			for (int i=0; i<h; i++) {
				if (RecognitionResult.at<ushort>(i,0)%nSubject == (i%nSubject)) {
					correctCounter++;
				} else {
					FileOut<<files[i]<<endl;
				}
			}
		}
	}
	FileOut.close();
	nCorrect = correctCounter;
	cout<<"h: "<<h<<endl;
	cout<<"correctCounter: "<<correctCounter<<endl;

	return (float)correctCounter/h;
}

float FaceRecognition::getAccuracyIncludingBadImages()
{
	if (RecognitionResult.empty()) return -1;
	if (BadImage.empty()) return -1;
	nBadImages = sum(BadImage)[0];
	int h = RecognitionResult.size().height;
	int nTestImagesPerSubject = h/nSubject;
	int correctCounter=0;
	ushort *ptr_rr = (ushort*)RecognitionResult.data;
	uchar *ptr_bi = BadImage.data;
	if (!nTestImageOrder) {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)/nRefImagesPerSubject == ((i/nTestImagesPerSubject)%nSubject) && !*(ptr_bi)) {
					correctCounter++;
				}
			}
		} else {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)%nSubject == ((i/nTestImagesPerSubject)%nSubject) && !*(ptr_bi)) {
					correctCounter++;
				}
			}
		}
	} else {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)/nRefImagesPerSubject == (i%nSubject) && !*(ptr_bi)) {
					correctCounter++;
				}
			}
		} else {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)%nSubject == (i%nSubject) && !*(ptr_bi)) {
					correctCounter++;
				}
			}
		}
	}
	nCorrect = correctCounter;
	cout<<"(h-nBadImages): "<<(h-nBadImages)<<endl;
	cout<<"correctCounter: "<<correctCounter<<endl;
	return (float)correctCounter/(h-nBadImages);
}

vector<float> FaceRecognition::getAccuracyIncludingBadImagesSubset()
{
	if (RecognitionResult.empty()) return vector<float>();
	if (BadImage.empty()) return vector<float>();
	if (nImagesSubset.empty()) return vector<float>();
	int nImagesSubsetSize = nImagesSubset.size();
	vector<float> nCorrectSubsetAccuracy(nImagesSubsetSize,0);
	nCorrectSubset.assign(nImagesSubsetSize,0);
	nBadImages = sum(BadImage)[0];
	int h = RecognitionResult.size().height;
	int nTestImagesPerSubject = h/nSubject;
	int correctCounter=0;
	ushort *ptr_rr = (ushort*)RecognitionResult.data;
	uchar *ptr_bi = BadImage.data;
	int subsetIndicator[64] = {0, 1, 2, 4, 1, 2, 0, 0,
			0, 1, 1, 1, 1, 2, 1, 2,
			2, 3, 2, 2, 3, 3, 3, 3,
			3, 3, 4, 4, 4, 4, 4, 4,
			4, 4, 4, 0, 0, 0, 1, 1,
			1, 1, 2, 1, 2, 2, 3, 2,
			2, 3, 3, 3, 3, 3, 3, 4,
			4, 4, 4, 4, 4, 4, 4, 4};
	vector<int> indicator;
	indicator.assign(subsetIndicator,subsetIndicator+64);
	if (!nTestImageOrder) {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)/nRefImagesPerSubject == ((i/nTestImagesPerSubject)%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i%nTestImagesPerSubject)]]++;
				}
			}
		} else {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)%nSubject == ((i/nTestImagesPerSubject)%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i%nTestImagesPerSubject)]]++;
				}
			}
		}
	} else {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)/nRefImagesPerSubject == (i%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i/nTestImagesPerSubject)]]++;
				}
			}
		} else {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)%nSubject == (i%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i/nTestImagesPerSubject)]]++;
				}
			}
		}
	}
	nCorrect = correctCounter;

	for (int i=0; i<nImagesSubsetSize; i++){
		nCorrectSubsetAccuracy[i] = (double)nCorrectSubset[i]/(nImagesSubset[i]*nSubject-nBadImagesSubset[i]);
		cout<<"# "<<nCorrectSubsetAccuracy[i]<<", "<<nCorrectSubset[i]<<", "<<(nImagesSubset[i]*nSubject-nBadImagesSubset[i])<<endl;
	}

	return nCorrectSubsetAccuracy;
}

vector<float> FaceRecognition::getAccuracyIncludingBadImagesSubset(ofstream &fw)
{
	if (RecognitionResult.empty()) return vector<float>();
	if (BadImage.empty()) return vector<float>();
	if (nImagesSubset.empty()) return vector<float>();
	int nImagesSubsetSize = nImagesSubset.size();
	vector<float> nCorrectSubsetAccuracy(nImagesSubsetSize,0);
	nCorrectSubset.assign(nImagesSubsetSize,0);
	nBadImages = sum(BadImage)[0];
	int h = RecognitionResult.size().height;
	int nTestImagesPerSubject = h/nSubject;
	int correctCounter=0;
	ushort *ptr_rr = (ushort*)RecognitionResult.data;
	uchar *ptr_bi = BadImage.data;
	int subsetIndicator[64] = {0, 1, 2, 4, 1, 2, 0, 0,
			0, 1, 1, 1, 1, 2, 1, 2,
			2, 3, 2, 2, 3, 3, 3, 3,
			3, 3, 4, 4, 4, 4, 4, 4,
			4, 4, 4, 0, 0, 0, 1, 1,
			1, 1, 2, 1, 2, 2, 3, 2,
			2, 3, 3, 3, 3, 3, 3, 4,
			4, 4, 4, 4, 4, 4, 4, 4};
	vector<int> indicator;
	indicator.assign(subsetIndicator,subsetIndicator+64);
	if (!nTestImageOrder) {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)/nRefImagesPerSubject == ((i/nTestImagesPerSubject)%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i%nTestImagesPerSubject)]]++;
				}
			}
		} else {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)%nSubject == ((i/nTestImagesPerSubject)%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i%nTestImagesPerSubject)]]++;
				}
			}
		}
	} else {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)/nRefImagesPerSubject == (i%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i/nTestImagesPerSubject)]]++;
				}
			}
		} else {
			for (int i=0; i<h; i++,ptr_rr++,ptr_bi++) {
				if (*(ptr_rr)%nSubject == (i%nSubject) && !*(ptr_bi)) {
					correctCounter++;
					nCorrectSubset[indicator[(i/nTestImagesPerSubject)]]++;
				}
			}
		}
	}
	nCorrect = correctCounter;

	for (int i=0; i<nImagesSubsetSize; i++){
		nCorrectSubsetAccuracy[i] = (double)nCorrectSubset[i]/(nImagesSubset[i]*nSubject-nBadImagesSubset[i]);
		fw<<"# "<<nCorrectSubsetAccuracy[i]<<", "<<nCorrectSubset[i]<<", "<<(nImagesSubset[i]*nSubject-nBadImagesSubset[i])<<endl;
	}

	return nCorrectSubsetAccuracy;
}


void FaceRecognition::getBadImageInfo (
		vector<string>						files,
		const int							subsetCount)
{
	BadImage = Mat::zeros(nFiles,1,CV_8SC1);
	uchar *ptr_bb = BadImage.data;
	if (subsetCount){
		if (nImagesSubset.empty()) return;
		int subsetIndicator[64] = {0, 1, 2, 4, 1, 2, 0, 0,
				0, 1, 1, 1, 1, 2, 1, 2,
				2, 3, 2, 2, 3, 3, 3, 3,
				3, 3, 4, 4, 4, 4, 4, 4,
				4, 4, 4, 0, 0, 0, 1, 1,
				1, 1, 2, 1, 2, 2, 3, 2,
				2, 3, 3, 3, 3, 3, 3, 4,
				4, 4, 4, 4, 4, 4, 4, 4};
		vector<int> indicator;
		indicator.assign(subsetIndicator,subsetIndicator+64);
		nBadImagesSubset.assign(nImagesSubset.size(),0);
		int nTestImagesPerSubject = files.size()/nSubject;
		for (int i = 0; i < nFiles; i++,ptr_bb++) {
			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				*(ptr_bb) = 1;
				nBadImagesSubset[indicator[i%nTestImagesPerSubject]] ++;
			}
		}
	} else {
		for (int i = 0; i < nFiles; i++,ptr_bb++) {
			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				*(ptr_bb) = 1;
			}
		}
	}
}


vector<int> FaceRecognition::vectorStretch(
		vector<int>							input)
{
	int len = input.size();
	int sum = 0;
	vector<int> acc(len);
	for (int i=0; i<len; i++) {
		sum += input[i];
		acc[i] = sum;
	}
	vector<int> r(sum);

	for (int i=0,index=0; i<sum; i++) {
		if(i >= acc[index]) {
			index++;
		}
		r[i] = index;
	}
	return r;
}

int FaceRecognition::getCorrects(){
	return nCorrect;
}
int FaceRecognition::getBadImages(){
	return nBadImages;
}
int FaceRecognition::getFiles(){
	return nFiles;
}



// Normalizes a given image into a value range between 0 and 255.
Mat FaceRecognition::norm_0_255(
		const Mat& 							src)
{
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

// Converts the images given in src into a row matrix.
Mat FaceRecognition::asRowMatrix(
		const vector<Mat>& 					src,
		int 								rtype,
		double 								alpha,
		double 								beta)
{
    // Number of samples:
    int n = src.size();
    // Return empty matrix if no matrices given:
    if(n == 0)
        return Mat();
    // dimensionality of (reshaped) samples
    size_t d = src[0].total();
    // Create resulting data matrix:
    Mat data(n, d, rtype);
    // Now copy data:
    for(int i = 0; i < n; i++) {
        //
        if(src[i].empty()) {
            string error_message = format("Image number %d was empty, please check your input data.", i);
            CV_Error(CV_StsBadArg, error_message);
        }
        // Make sure data can be reshaped, throw a meaningful exception if not!
        if(src[i].total() != d) {
            string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src[i].total());
            CV_Error(CV_StsBadArg, error_message);
        }
        // Get a hold of the current row:
        Mat xi = data.row(i);
        // Make reshape happy by cloning for non-continuous matrices:
        if(src[i].isContinuous()) {
            src[i].reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        } else {
            src[i].clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        }
    }
    return data;
}



}
