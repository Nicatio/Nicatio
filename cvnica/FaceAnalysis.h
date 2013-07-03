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
	Mat BadImage;

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
	void Normalize(
			InputArray 						_src,
			OutputArray						_dst);
	void gray2RGB(
			InputArray 						_src,
			OutputArray						_dst);
	void gray2RGBminmax(
			InputArray 						_src,
			OutputArray						_dst,
			const double					min,
			const double					max);
	void grayminmax(
			InputArray 						_src,
			OutputArray						_dst,
			const double					min,
			const double					max);
	void getBadImageInfo (
			vector<string>					files,
			const int						subsetCount);
	void correlationPic(
			const int						nPicsPerSubject,
			const int						type=0,
			const int						bin=0);
	void maskPic(
			const int						nPicsPerSubject,
			const int						type=0,
			const int						bin=0);

};

};

