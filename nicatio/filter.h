/*
 * filter.h
 *
 *  Created on: 2013. 1. 24.
 *      Author: Nicatio
 */

#ifndef FILTER_H_
#define FILTER_H_
#include "core.h"
#include "math.h"

namespace nicatio {

void MorphColor (
		void 							(*pf)(const unsigned char*, unsigned char*, const int&, const int&),
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void Dilation (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void Erosion (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void Closing_once (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void Opening_once (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void Closing (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						iteration=1);

void Opening (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						iteration=1);

void Threshold(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						lower_limit,
		const int&						upper_limit,
		const int&						width,
		const int&						height,
		const int&						binary=0,
		const int&						bg=0x00);

void Threshold(
		const double					*inputImg,
		unsigned char					*outputImg,
		const int&						lower_limit,
		const int&						upper_limit,
		const int&						width,
		const int&						height,
		const int&						binary=0,
		const int&						bg=0x00);

void Invert(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						channel);

void MedianFilter(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void filter3x3(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		int								filter[][3],
		const int&						offset = 0);

void filter3x3Color(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		int								filter[][3],
		const int&						offset = 0);

void Grayscale(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void Gamma(
		const unsigned char				*inputImg,
		double 							*outputImg,
		const int&						width,
		const int&						height,
		const double&					gamma);

void HistEqualize(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

void HistEqualize2(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height);

}


#endif /* FILTER_H_ */
