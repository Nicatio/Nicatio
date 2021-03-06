/*
 * cvFilter.h
 *
 *  Created on: 2013. 3. 7.
 *      Author: Nicatio
 */

#ifndef CVFILTER_H_
#define CVFILTER_H_
#define PI 3.1415926535897932384626433832795

#include "cv.h"
#include "highgui.h"

using namespace cv;

namespace cvNica {

void IntensityShifting(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						mid);

Mat rotateImage(
		const Mat						&source,
		double 							angle,
		bool							type,
		int								borderType=0,
		int								borderColor=0x000000);




void FindBlobs(
		const Mat &binary,
		vector < vector<Point2i> > 		&blobs);


void ELBP(const Mat& src, Mat& dst, int radius, int neighbors, int th);
}


#endif /* FILTER_H_ */
