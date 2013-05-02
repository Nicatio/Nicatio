/*
 * dmqi.h
 *
 *  Created on: 2013. 1. 28.
 *      Author: Nicatio
 */

#ifndef CVDMQI_H_
#define CVDMQI_H_

#include "cv.h"
#include "highgui.h"
#include "cvDoG.h"

using namespace cv;

namespace cvNica {

void lineHistEqualize(
		InputArray 						_src,
		OutputArray						_dst);

void lineHistEqualize2(
		InputArray 						_src,
		OutputArray						_dst);





void Reflectance_re(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst);

void SelectiveClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha=1.4,
		const int&						tempSmall=5,
		const int&						tempLarge=9);

void QuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize=0);

void NormDynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize=0);

void GaussianMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize=0);

void SelectiveMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha=1.4,
		const int&						tempSmall=5,
		const int&						tempLarge=9,
		const int&						equalize=0);

void DynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize=0);

void Reflectance(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst,
		float							mul=256.0);

void Denoise(
		InputArray 						_src,
		OutputArray						_dst);

void RemoveGrainyNoise(
		InputArray 						_src,
		OutputArray						_dst,
		int								threshold);

void DynamicClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha=1.8,
		const double&					beta=1.35);
}


#endif /* DMQI_H_ */
