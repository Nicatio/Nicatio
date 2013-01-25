/*
 * face.cpp
 *
 *  Created on: 2013. 1. 24.
 *      Author: HDSP
 */

#include "face.h"

namespace nicatio {

void FaceRegion(
	const unsigned char					*inputImg,
	unsigned char						*outputImg,
	const int&							width,
	const int&							height,
	const int&							binary)
{
	int sz = width*height;
	double **yuv = new double*[3];
	unsigned char *u = new unsigned char[sz];
	unsigned char *v = new unsigned char[sz];

	yuv[0] = new double[sz];
	yuv[1] = new double[sz];
	yuv[2] = new double[sz];

	Ycbcr(inputImg, yuv, width, height);
	Threshold(yuv[1],u,77,127,width,height,binary);
	Threshold(yuv[2],v,133,173,width,height,binary);

	for (int i=0; i<sz; i++) outputImg[i] = u[i] & v[i];

	delete [] yuv[0];
	delete [] yuv[1];
	delete [] yuv[2];
	delete [] yuv;
	delete [] u;
	delete [] v;


}

}


