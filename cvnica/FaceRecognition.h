/*
 * FaceRecognition.h
 *
 *  Created on: 2013. 2. 15.
 *      Author: HDSP
 */

#ifndef FACERECOGNITION_H_
#define FACERECOGNITION_H_

#include "cv.h"
#include "vector"
#include "../nicatio/io.h"

#define METHOD_L1NORM	0
#define METHOD_L2NORM	1
#define METHOD_L2HYS	2
#define METHOD_CORR		3
#define METHOD_DIFF		4


using namespace cv;

namespace cvNica {

class FaceRecognition
{
public:
	FaceRecognition(void);
	FaceRecognition(
			int								imagesPerSubject,
			vector<Mat>						referenceImage);
	~FaceRecognition(void);
	void DirectoryRegister(
			string							dir);
	void Enroll(
			vector<Mat>						referenceImage);
	void Recognition(
			vector<string>					files,
			int								criterion);
	void Recognition(
			string							dir,
			string							type,
			int								criterion);
	double getScore(
			Mat								inputA,
			Mat								inputB,
			int								searchRadius,
			int								criterion);
private:
	int nSubject;
	int nImagesPerSubject;
	string DirectoryLocation;
	Mat RecognitionResult;
	Mat RecognitionPositionX;
	Mat RecognitionPositionY;
	vector<Mat> refImage;
	void _Recognition(
			vector<Mat>						referenceImage,
			vector<string>					files,
			int								criterion);
};

};
#endif /* FACERECOGNITION_H_ */
