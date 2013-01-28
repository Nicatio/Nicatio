/*
 * dmqi.h
 *
 *  Created on: 2013. 1. 25.
 *      Author: HDSP
 */

#ifndef DMQI_H_
#define DMQI_H_


#include <fstream>
#include <math.h>
#include "filter.h"

namespace nicatio {

void DynamicMorphQuotImage(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						equalize=0);

void DynamicMorphQuotImage_revision(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						equalize);

void Reflectance(
		const unsigned char 			*deno,
		const unsigned char				*closedeno,
		unsigned char					*outputImg,
		const int&						w,
		const int&						h);

void Reflectance_revision(
		const unsigned char 			*deno,
		const unsigned char				*closedeno,
		unsigned char					*outputImg,
		const int&						w,
		const int&						h);

void Denoise(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void DynamicClosing(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						w,
		const int&						h,
		const double&					alpha=1.8,
		const double&					beta=1.35);

}


#endif /* DMQI_H_ */
