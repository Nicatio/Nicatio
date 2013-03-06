/*
 * cvDoG.h
 *
 *  Created on: 2013. 3. 6.
 *      Author: Nicatio
 */

#ifndef CVDOG_H_
#define CVDOG_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

namespace cvNica {

unsigned char* DoG(
		const unsigned char 			*inputImg,
		const int&						width,
		const int&						height,
		const double&					gamma,
		const double&					sigma0,
		const double&					sigma1,
		const int&						sx,
		const int&						sy,
		const int&						mask,
		const double&					do_norm);

bool convolve2DFast(
		double							*in,
		double							*out,
		int								dataSizeX,
		int								dataSizeY,
		const double					*kernel,
		int								kernelSizeX,
		int								kernelSizeY);


}



#endif /* CVDOG_H_ */
