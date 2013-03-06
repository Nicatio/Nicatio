/*
 * face.h
 *
 *  Created on: 2013. 1. 24.
 *      Author: Nicatio
 */

#ifndef FACE_H_
#define FACE_H_

#include "math.h"
#include "filter.h"

namespace nicatio {

void FaceRegion(
	const unsigned char					*inputImg,
	unsigned char						*outputImg,
	const int&							width,
	const int&							height,
	const int&							binary);

}



#endif /* FACE_H_ */
