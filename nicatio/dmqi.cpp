/*
 * dmqi.cpp
 *
 *  Created on: 2013. 1. 25.
 *      Author: HDSP
 */

#include "dmqi.h"


namespace nicatio {

void DynamicMorphQuotImage(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						equalize)
{
	int sz = width*height;
	unsigned char *deno = new unsigned char[sz];
	unsigned char *dc = new unsigned char[sz];
	unsigned char *refTemp;

	Denoise        (inputImg, deno, width, height);
	DynamicClosing (deno,     dc,   width, height);


	if (!equalize) refTemp = outputImg;
	else refTemp = new unsigned char[sz];

	Reflectance (deno, dc, refTemp, width, height);

	if (equalize == 1) {
		HistEqualize (refTemp, outputImg, width, height);
		delete [] refTemp;
	} else if (equalize == 2) {
		HistEqualize2 (refTemp, outputImg, width, height);
		delete [] refTemp;
	}

	delete [] deno;
	delete [] dc;
}


void DynamicMorphQuotImage_revision(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						equalize)
{
	int sz = width*height;
	unsigned char *deno = new unsigned char[sz];
	unsigned char *dc = new unsigned char[sz];
	//unsigned char *med = new unsigned char[sz];
	unsigned char *refTemp;

	Denoise        (inputImg, deno, width, height);
	DynamicClosing (deno,     dc,   width, height);


	if (!equalize) refTemp = outputImg;
	else refTemp = new unsigned char[sz];

	Reflectance_revision (deno, dc, refTemp, width, height);

//	if (equalize == 1) {
//		MedianFilter(refTemp,med,width,height);
//		HistEqualize (med, outputImg, width, height);
//		delete [] med;
//		delete [] refTemp;
//	} else if (equalize == 2) {
//		MedianFilter(refTemp,med,width,height);
//		HistEqualize2 (med, outputImg, width, height);
//		delete [] med;
//		delete [] refTemp;
//	}
	if (equalize == 1) {
		HistEqualize (refTemp, outputImg, width, height);
		delete [] refTemp;
	} else if (equalize == 2) {
		HistEqualize2 (refTemp, outputImg, width, height);
		delete [] refTemp;
	}

	delete [] deno;
	delete [] dc;
}



void Reflectance(
		const unsigned char 			*deno,
		const unsigned char				*closedeno,
		unsigned char					*outputImg,
		const int&						w,
		const int&						h)
{
	int sz = w*h;
    unsigned char *ptrDeno = (unsigned char*) deno;
	unsigned char *ptrCloseDeno = (unsigned char*) closedeno;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;
	for(int i=0; i<sz; i++){
		double a = (double)(*(ptrDeno++))/((double)(*(ptrCloseDeno++))+0.0001);
		if (a>2) a=2/a;
		int b = a * 128.0;
		*(ptrOutputImg++) = b;
	}
}

void Reflectance_revision(
		const unsigned char 			*deno,
		const unsigned char				*closedeno,
		unsigned char					*outputImg,
		const int&						w,
		const int&						h)
{
	int sz = w*h;
    unsigned char *ptrDeno = (unsigned char*) deno;
	unsigned char *ptrCloseDeno = (unsigned char*) closedeno;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;
	for(int i=0; i<sz; i++,ptrDeno++,ptrCloseDeno++){
		//double a = 255 /((double)(*(ptrCloseDeno++)&0xff)+0.0001 +255-  (double)(*(ptrDeno++)&0xff));
		double a;
		if (*(ptrDeno)<255)
			a = 50 /(  (double)(*(ptrDeno)));
		else
			a = (double)(*(ptrDeno))/((double)(*(ptrCloseDeno))+0.0001);


		if (a>2) a=2/a;
		int b = a * 128.0;
		*(ptrOutputImg++) = b;
	}
}

void Denoise(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int p;
	int sz = width*height;
	for(int y = 1; y < height-1; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			unsigned char min = inputImg[p-width-1];
			unsigned char max = inputImg[p-width-1];
			unsigned char b = inputImg[p-width];
			unsigned char c = inputImg[p-width+1];
			unsigned char d = inputImg[p-1];
			unsigned char e = inputImg[p+1];
			unsigned char f = inputImg[p+width-1];
			unsigned char g = inputImg[p+width];
			unsigned char h = inputImg[p+width+1];

			if (max<b) max=b;
			if (max<c) max=c;
			if (max<d) max=d;
			if (max<e) max=e;
			if (max<f) max=f;
			if (max<g) max=g;
			if (max<h) max=h;
			if (min>b) min=b;
			if (min>c) min=c;
			if (min>d) min=d;
			if (min>e) min=e;
			if (min>f) min=f;
			if (min>g) min=g;
			if (min>h) min=h;
			if (max < inputImg[p]) outputImg[p] = max;
			else if (min > inputImg[p]) outputImg[p] = min;
			else outputImg[p] = inputImg[p];
		}
		p = y*width;
		unsigned char min = inputImg[p-width];
		unsigned char max = inputImg[p-width];
		unsigned char c = inputImg[p-width+1];
		unsigned char e = inputImg[p+1];
		unsigned char g = inputImg[p+width];
		unsigned char h = inputImg[p+width+1];
		if (max<c) max=c;
		if (max<e) max=e;
		if (max<g) max=g;
		if (max<h) max=h;
		if (min>c) min=c;
		if (min>e) min=e;
		if (min>g) min=g;
		if (min>h) min=h;
		if (max < inputImg[p]) outputImg[p] = max;
		else if (min > inputImg[p]) outputImg[p] = min;
		else outputImg[p] = inputImg[p];

		p = width-1+y*width;
		min = inputImg[p-width-1];
		max = inputImg[p-width-1];
		unsigned char b = inputImg[p-width];
		unsigned char d = inputImg[p-1];
		unsigned char f = inputImg[p+width-1];
		g = inputImg[p+width];

		if (max<b) max=b;
		if (max<d) max=d;
		if (max<f) max=f;
		if (max<g) max=g;
		if (min>b) min=b;
		if (min>d) min=d;
		if (min>f) min=f;
		if (min>g) min=g;
		if (max < inputImg[p]) outputImg[p] = max;
		else if (min > inputImg[p]) outputImg[p] = min;
		else outputImg[p] = inputImg[p];
	}
	for(int x = 1; x < width-1; x++ ) {
		p = x;
		unsigned char min = inputImg[p-1];
		unsigned char max = inputImg[p-1];
		unsigned char e = inputImg[p+1];
		unsigned char f = inputImg[p+width-1];
		unsigned char g = inputImg[p+width];
		unsigned char h = inputImg[p+width+1];
		if (max<e) max=e;
		if (max<f) max=f;
		if (max<g) max=g;
		if (max<h) max=h;
		if (min>e) min=e;
		if (min>f) min=f;
		if (min>g) min=g;
		if (min>h) min=h;
		if (max < inputImg[p]) outputImg[p] = max;
		else if (min > inputImg[p]) outputImg[p] = min;
		else outputImg[p] = inputImg[p];



		p = x+(height-1)*width;
		min = inputImg[p-width-1];
		max = inputImg[p-width-1];
		unsigned char b = inputImg[p-width];
		unsigned char c = inputImg[p-width+1];
		unsigned char d = inputImg[p-1];
		e = inputImg[p+1];

		if (max<b) max=b;
		if (max<c) max=c;
		if (max<d) max=d;
		if (max<e) max=e;
		if (min>b) min=b;
		if (min>c) min=c;
		if (min>d) min=d;
		if (min>e) min=e;
		if (max < inputImg[p]) outputImg[p] = max;
		else if (min > inputImg[p]) outputImg[p] = min;
		else outputImg[p] = inputImg[p];
	}
	p = 0;
	unsigned char min = inputImg[p+1];
	unsigned char max = inputImg[p+1];
	unsigned char g = inputImg[p+width];
	unsigned char h = inputImg[p+width+1];
	if (max<g) max=g;
	if (max<h) max=h;
	if (min>g) min=g;
	if (min>h) min=h;
	if (max < inputImg[p]) outputImg[p] = max;
	else if (min > inputImg[p]) outputImg[p] = min;
	else outputImg[p] = inputImg[p];

	p = width-1;
	min = inputImg[p-1];
	max = inputImg[p-1];
	unsigned char f = inputImg[p+width-1];
	g = inputImg[p+width];
	if (max<f) max=f;
	if (max<g) max=g;
	if (min>f) min=f;
	if (min>g) min=g;
	if (max < inputImg[p]) outputImg[p] = max;
	else if (min > inputImg[p]) outputImg[p] = min;
	else outputImg[p] = inputImg[p];

	p = (height-1)*width;
	min = inputImg[p-width];
	max = inputImg[p-width];
	unsigned char c = inputImg[p-width+1];
	unsigned char e = inputImg[p+1];
	if (max<c) max=c;
	if (max<e) max=e;
	if (min>c) min=c;
	if (min>e) min=e;
	if (max < inputImg[p]) outputImg[p] = max;
	else if (min > inputImg[p]) outputImg[p] = min;
	else outputImg[p] = inputImg[p];

	p = sz-1;
	min = inputImg[p-width-1];
	max = inputImg[p-width-1];
	unsigned char b = inputImg[p-width];
	unsigned char d = inputImg[p-1];
	if (max<b) max=b;
	if (max<d) max=d;
	if (min>b) min=b;
	if (min>d) min=d;
	if (max < inputImg[p]) outputImg[p] = max;
	else if (min > inputImg[p]) outputImg[p] = min;
	else outputImg[p] = inputImg[p];
}

void DynamicClosing(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						w,
		const int&						h,
		const double&					alpha,
		const double&					beta)
{
	int sz = w*h;
	unsigned char **d = new unsigned char*[13];
	for (int i=0; i<13; i++){
		d[i] = new unsigned char[sz];
	}

	Dilation(inputImg,d[0],w,h);
	Dilation(d[0],d[1],w,h);
	Dilation(d[1],d[2],w,h);
	Dilation(d[2],d[3],w,h);

	Erosion(d[3],d[4],w,h);
	Erosion(d[4],d[5],w,h);
	Erosion(d[5],d[6],w,h);
	Erosion(d[6],d[7],w,h);

	Erosion(d[2],d[8],w,h);
	Erosion(d[8],d[9],w,h);
	Erosion(d[9],d[10],w,h);

	Erosion(d[1],d[11],w,h);
	Erosion(d[11],d[12],w,h);

	for (int i=0; i<sz; i++){
		if((double)d[7][i]>(double)d[12][i]*alpha) outputImg[i] = d[7][i];
		if(((double)d[7][i]>(double)d[12][i]*beta)&&((double)d[7][i]<=(double)d[12][i]*alpha)) outputImg[i] = d[10][i];
		else outputImg[i] = d[12][i];
	}

	for (int i=0; i<13; i++){
		delete [] d[i];
	}
	delete [] d;
}

}
