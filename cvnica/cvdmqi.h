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
		const double&					alpha=1.8,
		const double&					beta=1.35);

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
		const int&						equalize=0);

void DynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize=0);

void Reflectance(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst,
		double							scale=256.0);

void Denoise(
		InputArray 						_src,
		OutputArray						_dst);


void DynamicClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha=1.8,
		const double&					beta=1.35);

void RemoveGrainyNoise(
		InputArray 						_src,
		OutputArray						_dst,
		int								threshold);

void SelectiveClosingParam(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						large,
		const int&						small,
		const double&					alpha=1.8,
		const double&					beta=1.35);

void SelectiveMorphQuotImageParam(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						large,
		const int&						small,
		const int&						equalize=0);
}


#endif /* DMQI_H_ */
