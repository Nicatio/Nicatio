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
#include "cvFilter.h"
#include <math.h>


#define abs(x) (x<0)?-x:x



using namespace cv;

namespace cvNica {

void DoG(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					gamma,
		const double&					sigma0,
		const double&					sigma1,
		const int&						sx,
		const int&						sy,
		const int&						mask,
		const double&					do_norm);

void DoGMask(
		InputArray 						_src,
		InputArray 						_mask,
		OutputArray						_dst,
		Size							maskSize,
		const double&					gamma,
		const double&					sigma0,
		const double&					sigma1,
		const int&						sx,
		const int&						sy,
		const int&						mask,
		const double&					do_norm);

void BinFace(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						contrastMid,
		const int&						threshold);

void BinFaceMask(
		InputArray 						_src,
		InputArray 						_mask,
		OutputArray						_dst,
		Size							maskSize,
		const int&						contrastMid,
		const int&						th);

float FaceRollAngleDetection(
		InputArray 						_src,
		OutputArray						_dst);

void FourierLaplacian(
		InputArray 						_src,
		OutputArray						_dst);

}



#endif /* CVDOG_H_ */
