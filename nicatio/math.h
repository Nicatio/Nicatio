/*
 * math.h
 *
 *  Created on: 2013. 1. 24.
 *      Author: Nicatio
 */

#ifndef MATH_H_
#define MATH_H_

namespace nicatio {

int Median(
		int								*num,
		const int&						len);

unsigned char Median(
		unsigned char					*num,
		const int&						len);

void Ycbcr(
		const unsigned char				*inputImg,
		double							**ycbcr,
		const int&						width,
		const int&						height);

double Lightness(
		const unsigned char 			*inputImg,
		const int&						width,
		const int&						height,
		const int&						channel);

}


#endif /* MATH_H_ */
