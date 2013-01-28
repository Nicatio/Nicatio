/*
 * dmqi.h
 *
 *  Created on: 2013. 1. 28.
 *      Author: HDSP
 */

#ifndef CVDMQI_H_
#define CVDMQI_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

namespace cvNica {

void DynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize=0);

void Reflectance(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst);

void Denoise(
		InputArray 						_src,
		OutputArray						_dst);


void DynamicClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha=1.8,
		const double&					beta=1.35);
}


#endif /* DMQI_H_ */
