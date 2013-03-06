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
		string							referenceInfoFileLocation)
{
	setUseOptimized(true);
	setNumThreads(8);
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
		refImage.resize(nSubject * nRefImagesPerSubject);
		int i;
		for (i=0;;i++) {
			string str;
			getline(read,str);
			if(str=="") break;
			vector<string> tokens = nicatio::StringTokenizer::getTokens(str,"\n\r");
			imread( dir+"/"+tokens[0], -1 ).copyTo(refImage[i]);
		}
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

void FaceRecognition::Recognition(
		string							dir,
		string							type,
		int								DBname,
		int								criterion)
{
	DirectoryLocation = dir;
	vector<string> files = vector<string>();
	if(nicatio::getdirType(dir,type,files,0)){
		cout<< "Error: Invalid file location \n" <<endl;
	}
	_Recognition(refImage,files,DBname,criterion);
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

		if (criterion == METHOD_CORR){
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

					if (maxCorrCoef < corrCoef) {
						maxCorrCoef = corrCoef;
						posX = i;
						posY = j;
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


float FaceRecognition::getScore(
		const Mat						inputA,
		const Mat						inputB,
		const int						searchRadius,
		const int						criterion,
		char&							posX,
		char&							posY)
{
	int upper, lower;
	float maxCorrCoef = -1;
	posX = 0;
	posY = 0;
	upper = searchRadius>>1;
	lower = (searchRadius%2)? (-upper):(-upper+1);

	if(inputA.type() != inputB.type()) return -1;
	if(inputA.size() != inputB.size()) return -1;
	// based on offset of the reference image

	int w = inputA.size().width;
	int h = inputA.size().height;

	Mat inputA32; inputA.convertTo(inputA32,CV_32F);
	Mat inputB32; inputB.convertTo(inputB32,CV_32F);
	Mat inputAA32; multiply (inputA32,inputA32,inputAA32);
	Mat inputBB32; multiply (inputB32,inputB32,inputBB32);

	if (criterion == METHOD_CORR){
		for (int i=lower; i<=upper; i++) {
			for (int j=lower; j<=upper; j++) {
				int a_,b_,c_,d_;
				int _a,_b;
				int a,b,c,d;
				float Asq,Bsq,Ms;
				float As,Bs;

				if(i<0) {
					a_ = -i;
					_a = 0;
					c_ = w+i;
				}
				else {
					a_ = 0;
					_a = i;
					c_ = w-i;
				}

				if(j<0) {
					b_ = -j;
					_b = 0;
					d_ = h+j;
				}
				else {
					b_ = 0;
					_b = j;
					d_ = h-j;
				}


				if(i<0){
					a = a_;
					c = 0;
				} else {
					a = 0;
					c = _a;
				}

				if(j<0){
					b = b_;
					d = 0;
				} else {
					b = 0;
					d = _b;
				}


				Mat inputACrop=inputA32(Rect (a_,b_,c_,d_));
				Mat inputBCrop=inputB32(Rect (_a,_b,c_,d_));
				Mat inputAACrop=inputAA32(Rect (a_,b_,c_,d_));
				Mat inputBBCrop=inputBB32(Rect (_a,_b,c_,d_));
				Mat multResult(c_,d_,CV_32F);


				multiply (inputACrop,inputBCrop,multResult);


				Ms = sum(multResult)[0];
				Asq = sum(inputAACrop)[0];
				Bsq = sum(inputBBCrop)[0];
				As = sum(inputACrop)[0];
				Bs = sum(inputBCrop)[0];

				int s = c_*d_;

				float refSigma = sqrt((double)s*Asq-(double)As*As);
				float tesSigma = sqrt((double)s*Bsq-(double)Bs*Bs);
				float corrCoef = ((double)s*Ms - (double)As*Bs)/(refSigma*tesSigma);

				if (maxCorrCoef < corrCoef) {
					maxCorrCoef = corrCoef;
					posX = i;
					posY = j;
				}

			}
		}
	}
	return maxCorrCoef;
}


void FaceRecognition::_Recognition(
		vector<Mat>						referenceImage,
		vector<string>					files,
		int								DBname,
		int								criterion)
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

	for (int i = 0; i < nFiles; i++) {
		cout << files[i] << endl;
		Mat testImage = imread( DirectoryLocation+"/"+files[i], -1 );
		double t=(double)getTickCount();
		getScoreTestImageBased(referenceImage, testImage, i, nSearchRadius, criterion);
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "Registration Time : " << t << " sec" << endl;
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

float FaceRecognition::getAccuracy()
{
	if (RecognitionResult.empty()) return -1;
	int h = RecognitionResult.size().height;
	int nTestImagesPerSubject = h/nSubject;
	int correctCounter=0;
	if (!nTestImageOrder) {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++) {
				if ((RecognitionResult.at<ushort>(i,0)/nRefImagesPerSubject) == ((i/nTestImagesPerSubject)%nSubject)) {
					correctCounter++;
				}
			}
		} else {
			for (int i=0; i<h; i++) {
				if (RecognitionResult.at<ushort>(i,0)%nSubject == ((i/nTestImagesPerSubject)%nSubject)) {
					correctCounter++;
				}
			}
		}
	} else {
		if (!nRefImageOrder) {
			for (int i=0; i<h; i++) {
				if ((RecognitionResult.at<ushort>(i,0)/nRefImagesPerSubject) == (i%nSubject)) {
					correctCounter++;
				}
			}
		} else {
			for (int i=0; i<h; i++) {
				if (RecognitionResult.at<ushort>(i,0)%nSubject == (i%nSubject)) {
					correctCounter++;
				}
			}
		}
	}
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


}
