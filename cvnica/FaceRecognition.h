/*
 * FaceRecognition.h
 *
 *  Created on: 2013. 2. 15.
 *      Author: Nicatio
 */

#ifndef FACERECOGNITION_H_
#define FACERECOGNITION_H_

#include "fstream"
#include "cv.h"
#include "highgui.h"
#include "vector"
#include "../nicatio/io.h"
#include "../nicatio/filter.h"
#include "cvFilter.h"

#define METHOD_L1NORM	0
#define METHOD_L2NORM	1
#define METHOD_L2HYS	2
#define METHOD_CORR		3
#define METHOD_DIFF		4
#define METHOD_PCA		5
#define METHOD_L2NORM2	6

#define DB_YALEB		0


using namespace cv;

namespace cvNica {

class FaceRecognition
{
public:

	FaceRecognition(
			int								imagesPerSubject,
			int								refImageorder,
			int								testImageorder,
			vector<Mat>						referenceImage);
	FaceRecognition(
			string							dir,
			string							referenceInfoFileLocation,
			string							databaseType="integrated");
	~FaceRecognition(void);
	void DirectoryRegister(
			string							dir);
	void Enroll(
			vector<Mat>						referenceImage);
	void Recognition(
			vector<string>					files,
			int								DBname,
			int								criterion=METHOD_CORR);
//	void Recognition(
//			string							dir,
//			string							type,
//			int								DBname,
//			int								criterion=METHOD_CORR,
//			int								startAngle=0,
//			int								endAngle=0);
	void Recognition(
			string							dir,
			string							type,
			int								DBname,
			int								criterion=METHOD_CORR,
			int								startAngle=0,
			int								endAngle=0,
			int								startX=0,
			int								startY=0,
			int								endX=0,
			int								endY=0);
	void getScoreTestImageBased(
			const vector<Mat>				inputA,
			const Mat						inputB,
			const int						nFileIndex,
			const int						searchRadius,
			const int						criterion);
	void getScoreTestImageBasedCrop(
			const vector<Mat>				inputA,
			const Mat						inputB,
			const int						nFileIndex,
			const int						searchRadius,
			const int						criterion,
			int								startX,
			int								startY,
			int								endX,
			int								endY);
	void getScoreTestImageBasedWeight(
			const vector<Mat>				inputA,
			const Mat						inputB,
			const int						nFileIndex,
			const int						searchRadius,
			const int						criterion);
	void getScoreTestImageBasedRotation(
			const vector<Mat>				inputA,
			const Mat						inputB,
			const int						nFileIndex,
			const int						searchRadius,
			const int						criterion,
			const int						startAngle,
			const int						endAngle);
	void getPCAscore(
			const Mat						inputB,
			const int						nFileIndex);
	float getAccuracy(
			vector<string>						filess);
	float getAccuracyIncludingBadImages();
	vector<float> getAccuracyIncludingBadImagesSubset();
	vector<float> getAccuracyIncludingBadImagesSubset(ofstream &fw);
	void getBadImageInfo (
			vector<string>						files,
			const int							subsetCount=0);
	int getCorrects();
	int getBadImages();
	int getFiles();
	void PrintScore(
			char* 							s);

	Mat norm_0_255(
			const Mat& 							src);

	// Converts the images given in src into a row matrix.
	Mat asRowMatrix(
			const vector<Mat>& 					src,
			int 								rtype,
			double 								alpha = 1,
			double 								beta = 0);

	Mat RecognitionScore;
	Mat RecognitionResult;
	Mat RecognitionPositionX;
	Mat RecognitionPositionY;
	Mat BadImage;
private:
	int bDatabaseType;
	int nSubject;
	int nRefImagesPerSubject;
	int nRefImageOrder;
	int nTestImageOrder;
	int nSearchRadius;
	int nCorrect;
	int nFiles;
	int nBadImages;
	vector<int> nCorrectSubset;
	vector<int> nImagesSubset;
	vector<int> nBadImagesSubset;
	string DirectoryLocation;
	vector<Mat> refImage;

	PCA pca;
	vector<Mat> pcaRefCoeffs;

	void _Recognition(
			vector<Mat>						referenceImage,
			vector<string>					files,
			int								DBname,
			int								criterion,
			int								startAngle=0,
			int								endAngle=0,
			int								startX=0,
			int								startY=0,
			int								endX=0,
			int								endY=0);
	vector<int> vectorStretch(
			vector<int>							input);
};

};
#endif /* FACERECOGNITION_H_ */
