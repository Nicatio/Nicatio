/*
 * CornerDescriptor.h
 *
 *  Created on: 2013. 9. 16.
 *      Author: Nicatio
 */

#ifndef CORNERDESCRIPTOR_H_
#define CORNERDESCRIPTOR_H_

#define CORNER_ALL        0
#define CORNER_VERTICAL   1
#define CORNER_HORIZONTAL 2
#define CORNER_DIAG_RT    3
#define CORNER_DIAG_LT    4
#define CORNER_CORNER_RT  5
#define CORNER_CORNER_LT  6
#define CORNER_CORNER_LB  7
#define CORNER_CORNER_RB  8

#include "cv.h"
#include "highgui.h"
#include "cvDoG.h"

using namespace cv;

namespace cvNica {

void HomogeneousOperator(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						type = CORNER_ALL);

void VarianceFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size);

void DifferenceOfVariance(
		InputArray 						_src,
		OutputArray						_dst);
}


#endif /* CORNERDESCRIPTOR_H_ */
