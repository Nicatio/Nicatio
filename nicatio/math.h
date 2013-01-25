/*
 * math.h
 *
 *  Created on: 2013. 1. 24.
 *      Author: HDSP
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
	const unsigned char						*inputImg,
	double									**ycbcr,
	const int&								width,
	const int&								height);

}


#endif /* MATH_H_ */
