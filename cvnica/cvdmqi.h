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

void ContinuousClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha,
		const double&					k);

void Closing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					strE);

void AdaptiveClosing(
		InputArray 						_src,
		OutputArray						_dst,
		double							percent);

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

void ContinuousMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha,
		const double&					k,
		const int&						equalize=0);

void MorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					strE);

void AdaptiveMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		double							percent,
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
		const double&					alpha,
		const int&						equalize);
}


#endif /* DMQI_H_ */
