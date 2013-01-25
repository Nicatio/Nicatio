/*
 * hausdorff.h
 *
 *  Created on: 2013. 1. 25.
 *      Author: HDSP
 */

#ifndef HAUSDORFF_H_
#define HAUSDORFF_H_

#include "core.h"

namespace nicatio {

void DistTransform(
		UINT							**A,
		const int&						w,
		const int&						h);

double HausdorffDist2012(
		const unsigned char				*A,
		const unsigned char				*B,
		const int&						width,
		const int&						height,
		const int&						AoffsetX,
		const int&						AoffsetY,
		const int&						BoffsetX,
		const int&						BoffsetY,
		const int&						type);
}


#endif /* HAUSDORFF_H_ */
