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
			string							referenceInfoFileLocation);
	~FaceRecognition(void);
	void DirectoryRegister(
			string							dir);
	void Enroll(
			vector<Mat>						referenceImage);
	void Recognition(
			vector<string>					files,
			int								DBname,
			int								criterion=METHOD_CORR);
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
	void getScoreTestImageBasedWeight(
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
	void getScoreTestImageBasedRotation(
			const vector<Mat>				inputA,
			const Mat						inputB,
			const int						nFileIndex,
			const int						searchRadius,
			const int						criterion,
			const int						startAngle,
			const int						endAngle);
	float getAccuracy(
			vector<string>						filess);
	float getAccuracyIncludingBadImages();
	vector<float> getAccuracyIncludingBadImagesSubset(ofstream &fw);
	void getBadImageInfo (
			vector<string>						files,
			const int							subsetCount=0);
	int getCorrects();
	int getBadImages();
	int getFiles();
	Mat RecognitionScore;
	Mat RecognitionResult;
	Mat RecognitionPositionX;
	Mat RecognitionPositionY;
	Mat BadImage;
private:
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
