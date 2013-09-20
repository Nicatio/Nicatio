/*
 * CornerDescriptor.h
 *
 *  Created on: 2013. 9. 16.
 *      Author: Nicatio
 */

#ifndef CORNERDESCRIPTOR_H_
#define CORNERDESCRIPTOR_H_

#include "cv.h"
#include "highgui.h"
#include "cvDoG.h"

using namespace cv;

namespace cvNica {

void HomogeneousOperator(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void VarianceFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size);

void DifferenceOfVariance(
		InputArray 						_src,
		OutputArray						_dst);
}


#endif /* CORNERDESCRIPTOR_H_ */
