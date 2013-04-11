/*
 * FaceAnalysis.h
 *
 *  Created on: 2013. 4. 6.
 *      Author: Nicatio
 */

#ifndef FACEANALYSIS_H_
#define FACEANALYSIS_H_

#include "fstream"
#include "cv.h"
#include "highgui.h"
#include "vector"
#include "../nicatio/io.h"

#endif /* FACEANALYSIS_H_ */

using namespace cv;

namespace cvNica {

class FaceAnalysis
{
public:
	string DirectoryLocation;
	vector<int> groupCount;
	vector<string> files;
	Mat groupMap;

	FaceAnalysis (void);
	FaceAnalysis (
			string							dir,
			string							type);
	void setGroup(
			string							location);
	void mse(
			const int						nPicsPerSubject);
	void draw(
			const int						nPicsPerSubject,
			const int						type=0);

};

};

