/*
 * FaceRecognition.h
 *
 *  Created on: 2013. 2. 15.
 *      Author: HDSP
 */

#ifndef FACERECOGNITION_H_
#define FACERECOGNITION_H_

#include "fstream"
#include "cv.h"
#include "highgui.h"
#include "vector"
#include "../nicatio/io.h"
#include "../nicatio/filter.h"

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
			int								criterion=METHOD_CORR);
	float getScore(
			const Mat						inputA,
			const Mat						inputB,
			const int						searchRadius,
			const int						criterion,
			char&							posX,
			char&							posY);
	void getScoreTestImageBased(
			const vector<Mat>				inputA,
			const Mat						inputB,
			const int						nFileIndex,
			const int						searchRadius,
			const int						criterion);
	float getAccuracy();
	float getAccuracyIncludingBadImages();
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
	string DirectoryLocation;

	vector<Mat> refImage;
	void _Recognition(
			vector<Mat>						referenceImage,
			vector<string>					files,
			int								DBname,
			int								criterion);
};

};
#endif /* FACERECOGNITION_H_ */
