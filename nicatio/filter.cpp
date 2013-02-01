/*
 * filter.cpp
 *
 *  Created on: 2013. 1. 24.
 *      Author: HDSP
 */


#include "filter.h"


namespace nicatio {


void MorphColor (
		void 							(*pf)(const unsigned char*, unsigned char*, const int&, const int&),
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int sz = width*height;
	unsigned char *r=new unsigned char[sz],*g=new unsigned char[sz],*b=new unsigned char[sz];
	unsigned char *_r=new unsigned char[sz],*_g=new unsigned char[sz],*_b=new unsigned char[sz];
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;

	for(int i=0; i<sz; i++){
		r[i] = *(ptrInputImg++);
		g[i] = *(ptrInputImg++);
		b[i] = *(ptrInputImg++);
	}

	(*pf)(r,_r,width,height);
	(*pf)(g,_g,width,height);
	(*pf)(b,_b,width,height);

	for(int i=0; i<sz; i++){
		*(ptrOutputImg++) = _r[i];
		*(ptrOutputImg++) = _g[i];
		*(ptrOutputImg++) = _b[i];
	}

	delete [] r;
	delete [] g;
	delete [] b;
	delete [] _r;
	delete [] _g;
	delete [] _b;
}

void Dilation (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int p;
	int sz = width*height;
	for(int y = 1; y < height-1; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			unsigned char r = inputImg[p-width-1];
			unsigned char a = inputImg[p-width];
			unsigned char b = inputImg[p-width+1];
			unsigned char c = inputImg[p-1];
			unsigned char d = inputImg[p+1];
			unsigned char e = inputImg[p+width-1];
			unsigned char f = inputImg[p+width];
			unsigned char g = inputImg[p+width+1];
			unsigned char z = inputImg[p];
			if (r<z) r=z;
			if (r<a) r=a;
			if (r<b) r=b;
			if (r<c) r=c;
			if (r<d) r=d;
			if (r<e) r=e;
			if (r<f) r=f;
			if (r<g) r=g;
			outputImg[p] = (unsigned char)r;
			r=r+0;
		}
		p = y*width;
		unsigned char r = inputImg[p-width];
		unsigned char b = inputImg[p-width+1];
		unsigned char d = inputImg[p+1];
		unsigned char f = inputImg[p+width];
		unsigned char g = inputImg[p+width+1];
		unsigned char z = inputImg[p];
		if (r<z) r=z;
		if (r<b) r=b;
		if (r<d) r=d;
		if (r<f) r=f;
		if (r<g) r=g;
		outputImg[p] = (unsigned char)r;

		p = width-1+y*width;
		r = inputImg[p-width-1];
		unsigned char a = inputImg[p-width];
		unsigned char c = inputImg[p-1];
		unsigned char e = inputImg[p+width-1];
		f = inputImg[p+width];
		z = inputImg[p];
		if (r<z) r=z;
		if (r<a) r=a;
		if (r<c) r=c;
		if (r<e) r=e;
		if (r<f) r=f;
		outputImg[p] = (unsigned char)r;
	}
	for(int x = 1; x < width-1; x++ ) {
		p = x;
		unsigned char r = inputImg[p-1];
		unsigned char d = inputImg[p+1];
		unsigned char e = inputImg[p+width-1];
		unsigned char f = inputImg[p+width];
		unsigned char g = inputImg[p+width+1];
		unsigned char z = inputImg[p];
		if (r<z) r=z;
		if (r<d) r=d;
		if (r<e) r=e;
		if (r<f) r=f;
		if (r<g) r=g;
		outputImg[p] = (unsigned char)r;

		p = x+(height-1)*width;
		r = inputImg[p-width-1];
		unsigned char a = inputImg[p-width];
		unsigned char b = inputImg[p-width+1];
		unsigned char c = inputImg[p-1];
		d = inputImg[p+1];
		z = inputImg[p];
		if (r<z) r=z;
		if (r<a) r=a;
		if (r<b) r=b;
		if (r<c) r=c;
		if (r<d) r=d;
		outputImg[p] = (unsigned char)r;
	}
	p = 0;
	unsigned char r = inputImg[p+1];
	unsigned char f = inputImg[p+width];
	unsigned char g = inputImg[p+width+1];
	unsigned char z = inputImg[p];
	if (r<z) r=z;
	if (r<f) r=f;
	if (r<g) r=g;

	outputImg[p] = (unsigned char)r;

	p = width-1;
	r = inputImg[p-1];
	unsigned char e = inputImg[p+width-1];
	f = inputImg[p+width];
	z = inputImg[p];
	if (r<z) r=z;
	if (r<e) r=e;
	if (r<f) r=f;
	outputImg[p] = (unsigned char)r;

	p = (height-1)*width;
	r = inputImg[p-width];
	unsigned char b = inputImg[p-width+1];
	unsigned char d = inputImg[p+1];
	z = inputImg[p];
	if (r<z) r=z;
	if (r<b) r=b;
	if (r<d) r=d;
	outputImg[p] = (unsigned char)r;
	p = sz-1;

	r = inputImg[p-width-1];
	unsigned char a = inputImg[p-width];
	unsigned char c = inputImg[p-1];
	z = inputImg[p];
	if (r<z) r=z;
	if (r<a) r=a;
	if (r<c) r=c;
	outputImg[p] = (unsigned char)r;
}

void Erosion (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int p;
	int sz = width*height;
	//int *inputImg = new int[sz];
	//for (int j=0; j<sz; j++) inputImg[j] = (int) _inputImg[j];
	for(int y = 1; y < height-1; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			unsigned char r = inputImg[p-width-1];
			unsigned char a = inputImg[p-width];
			unsigned char b = inputImg[p-width+1];
			unsigned char c = inputImg[p-1];
			unsigned char d = inputImg[p+1];
			unsigned char e = inputImg[p+width-1];
			unsigned char f = inputImg[p+width];
			unsigned char g = inputImg[p+width+1];

			if (r>a) r=a;
			if (r>b) r=b;
			if (r>c) r=c;
			if (r>d) r=d;
			if (r>e) r=e;
			if (r>f) r=f;
			if (r>g) r=g;
			outputImg[p] = (unsigned char)r;
		}
		p = y*width;
		unsigned char r = inputImg[p-width];
		unsigned char b = inputImg[p-width+1];
		unsigned char d = inputImg[p+1];
		unsigned char f = inputImg[p+width];
		unsigned char g = inputImg[p+width+1];

		if (r>b) r=b;
		if (r>d) r=d;
		if (r>f) r=f;
		if (r>g) r=g;
		outputImg[p] = (unsigned char)r;

		p = width-1+y*width;
		r = inputImg[p-width-1];
		unsigned char a = inputImg[p-width];
		unsigned char c = inputImg[p-1];
		unsigned char e = inputImg[p+width-1];
		f = inputImg[p+width];

		if (r>a) r=a;
		if (r>c) r=c;
		if (r>e) r=e;
		if (r>f) r=f;
		outputImg[p] = (unsigned char)r;
	}
	for(int x = 1; x < width-1; x++ ) {
		p = x;
		unsigned char r = inputImg[p-1];
		unsigned char d = inputImg[p+1];
		unsigned char e = inputImg[p+width-1];
		unsigned char f = inputImg[p+width];
		unsigned char g = inputImg[p+width+1];

		if (r>d) r=d;
		if (r>e) r=e;
		if (r>f) r=f;
		if (r>g) r=g;
		outputImg[p] = (unsigned char)r;

		p = x+(height-1)*width;
		r = inputImg[p-width-1];
		unsigned char a = inputImg[p-width];
		unsigned char b = inputImg[p-width+1];
		unsigned char c = inputImg[p-1];
		d = inputImg[p+1];

		if (r>a) r=a;
		if (r>b) r=b;
		if (r>c) r=c;
		if (r>d) r=d;
		outputImg[p] = (unsigned char)r;
	}
	p = 0;
	unsigned char r = inputImg[p+1];
	unsigned char f = inputImg[p+width];
	unsigned char g = inputImg[p+width+1];
	if (r>f) r=f;
	if (r>g) r=g;
	outputImg[p] = (unsigned char)r;

	p = width-1;
	r = inputImg[p-1];
	unsigned char e = inputImg[p+width-1];
	f = inputImg[p+width];
	if (r>e) r=e;
	if (r>f) r=f;
	outputImg[p] = (unsigned char)r;

	p = (height-1)*width;
	r = inputImg[p-width];
	unsigned char b = inputImg[p-width+1];
	unsigned char d = inputImg[p+1];
	if (r>b) r=b;
	if (r>d) r=d;
	outputImg[p] = (unsigned char)r;
	p = sz-1;

	r = inputImg[p-width-1];
	unsigned char a = inputImg[p-width];
	unsigned char c = inputImg[p-1];
	if (r>a) r=a;
	if (r>c) r=c;
	outputImg[p] = (unsigned char)r;
}

void Closing_once (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	unsigned char *temp = new unsigned char[width*height];
	Dilation(inputImg,temp,width,height);
	Erosion(temp,outputImg,width,height);
	delete [] temp;
}

void Opening_once (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	unsigned char *temp = new unsigned char[width*height];
	Erosion(inputImg,temp,width,height);
	Dilation(temp,outputImg,width,height);
	delete [] temp;
}

void Closing (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						iteration)
{
	if(iteration==1) Closing_once(inputImg,outputImg,width,height);
	else if (iteration>1) {
		unsigned char *temp = (unsigned char*) inputImg;
		unsigned char *innerLoopTemp;
		for(int i = 0; i < iteration; i++) {
			innerLoopTemp = new unsigned char[width*height];
			Dilation(temp,innerLoopTemp,width,height);
			if(i) delete [] temp;
			temp = innerLoopTemp;
		}
		for(int i = 0; i < iteration-1; i++) {
			innerLoopTemp = new unsigned char[width*height];
			Erosion(temp,innerLoopTemp,width,height);
			delete [] temp;
			temp = innerLoopTemp;
		}
		Erosion(temp,outputImg,width,height);
		delete [] temp;
	}
}

void Opening (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						iteration)
{
	if(iteration==1) Opening_once(inputImg,outputImg,width,height);
	else if (iteration>1) {
		unsigned char *temp = (unsigned char*) inputImg;
		unsigned char *innerLoopTemp;
		for(int i = 0; i < iteration; i++) {
			innerLoopTemp = new unsigned char[width*height];
			Erosion(temp,innerLoopTemp,width,height);
			if(i) delete [] temp;
			temp = innerLoopTemp;
		}
		for(int i = 0; i < iteration-1; i++) {
			innerLoopTemp = new unsigned char[width*height];
			Dilation(temp,innerLoopTemp,width,height);
			delete [] temp;
			temp = innerLoopTemp;
		}
		Dilation(temp,outputImg,width,height);
		delete [] temp;
	}
}

void Threshold(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						lower_limit,
		const int&						upper_limit,
		const int&						width,
		const int&						height,
		const int&						binary,
		const int&						bg)
{
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;

	if (lower_limit < upper_limit) {
		int sz = width*height;
		if (!binary){
			for (int i=0; i<sz; i++){
				unsigned char temp = *(ptrInputImg++);
				*(ptrOutputImg++) = (temp>=lower_limit && temp<=upper_limit)? temp : bg;
			}
		} else {
			for (int i=0; i<sz; i++){
				unsigned char temp = *(ptrInputImg++);
				*(ptrOutputImg++) = (temp>=lower_limit && temp<=upper_limit)? binary : bg;
			}
		}
	}
}

void Threshold(
		const double					*inputImg,
		unsigned char					*outputImg,
		const int&						lower_limit,
		const int&						upper_limit,
		const int&						width,
		const int&						height,
		const int&						binary,
		const int&						bg)
{
	double *ptrInputImg = (double*) inputImg;
	double *ptrOutputImg = (double*) outputImg;
	int sz = width*height;
	if (lower_limit < upper_limit) {
		if (!binary){
			for (int i=0; i<sz; i++){
				double temp = *(ptrInputImg++);
				*(ptrOutputImg++) = (unsigned char) ((temp>=lower_limit && temp<=upper_limit)? temp : bg);
			}
		} else {
			for (int i=0; i<sz; i++){
				double temp = *(ptrInputImg++);
				*(ptrOutputImg++) = (unsigned char) ((temp>=lower_limit && temp<=upper_limit)? binary : bg);
			}
		}
	}
}

void Invert(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						channel)
{
	int sz = width*height;
	double *ptrInputImg = (double*) inputImg;
	double *ptrOutputImg = (double*) outputImg;
	int f = 0xff;
	if (channel == 2) f = 0xffff;
	if (channel == 3) f = 0xffffff;

	for (int i=0; i<sz; i++) *(ptrOutputImg++) = f - *(ptrInputImg++);
}

void MedianFilter(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{

	int p;
	int sz = width*height;
	for(int y = 1; y < height-1; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			unsigned char *temparr = new unsigned char[9];
			temparr[0] = inputImg[p-width-1];
			temparr[1] = inputImg[p-width];
			temparr[2] = inputImg[p-width+1];
			temparr[3] = inputImg[p-1];
			temparr[4] = inputImg[p];
			temparr[5] = inputImg[p+1];
			temparr[6] = inputImg[p+width-1];
			temparr[7] = inputImg[p+width];
			temparr[8] = inputImg[p+width+1];
			outputImg[p] = Median(temparr,9);
			delete [] temparr;
		}
		p = y*width;
		unsigned char *temparr = new unsigned char[6];
		temparr[0] = inputImg[p-width];
		temparr[1] = inputImg[p-width+1];
		temparr[2] = inputImg[p];
		temparr[3] = inputImg[p+1];
		temparr[4] = inputImg[p+width];
		temparr[5] = inputImg[p+width+1];
		outputImg[p] = Median(temparr,6);

		p = width-1+y*width;
		temparr[0] = inputImg[p-width-1];
		temparr[1] = inputImg[p-width];
		temparr[2] = inputImg[p-1];
		temparr[3] = inputImg[p];
		temparr[4] = inputImg[p+width-1];
		temparr[5] = inputImg[p+width];
		outputImg[p] = Median(temparr,6);
		delete [] temparr;
	}

	for(int x = 1; x < width-1; x++ ) {
		p = x;
		unsigned char *temparr = new unsigned char[6];
		temparr[0] = inputImg[p-1];
		temparr[1] = inputImg[p];
		temparr[2] = inputImg[p+1];
		temparr[3] = inputImg[p+width-1];
		temparr[4] = inputImg[p+width];
		temparr[5] = inputImg[p+width+1];
		outputImg[p] = Median(temparr,6);

		p = x+(height-1)*width;
		temparr[0] = inputImg[p-width-1];
		temparr[1] = inputImg[p-width];
		temparr[2] = inputImg[p-width+1];
		temparr[3] = inputImg[p-1];
		temparr[4] = inputImg[p];
		temparr[5] = inputImg[p+1];
		outputImg[p] = Median(temparr,6);
		delete [] temparr;
	}
	p = 0;
	unsigned char *temparr = new unsigned char[4];
	temparr[0] = inputImg[p];
	temparr[1] = inputImg[p+1];
	temparr[2] = inputImg[p+width];
	temparr[3] = inputImg[p+width+1];
	outputImg[p] = Median(temparr,4);

	p = width-1;
	temparr[0] = inputImg[p-1];
	temparr[1] = inputImg[p];
	temparr[2] = inputImg[p+width-1];
	temparr[3] = inputImg[p+width];
	outputImg[p] = Median(temparr,4);

	p = (height-1)*width;
	temparr[0] = inputImg[p-width];
	temparr[1] = inputImg[p-width+1];
	temparr[2] = inputImg[p];
	temparr[3] = inputImg[p+1];
	outputImg[p] = Median(temparr,4);

	p = sz-1;
	temparr[0] = inputImg[p-width-1];
	temparr[1] = inputImg[p-width];
	temparr[2] = inputImg[p-1];
	temparr[3] = inputImg[p];
	outputImg[p] = Median(temparr,4);

	delete [] temparr;
}

void filter3x3(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		int								filter[][3],
		const int&						offset)
{

	int p;
	int sz = width*height;
	int gaussianFilter[3][3] = {{1, 2, 1},{2,4,2},{1,2,1}};
	if (!filter) {
		filter = gaussianFilter;
	}
	int a = filter[0][0]+filter[0][1]+filter[0][2]+filter[1][0]+filter[1][1]+filter[1][2]+filter[2][0]+filter[2][1]+filter[2][2];
	int b = filter[0][1]+filter[0][2]+filter[1][1]+filter[1][2]+filter[2][1]+filter[2][2];
	int c = filter[0][0]+filter[0][1]+filter[1][0]+filter[1][1]+filter[2][0]+filter[2][1];
	int d = filter[1][0]+filter[1][1]+filter[1][2]+filter[2][0]+filter[2][1]+filter[2][2];
	int e = filter[0][0]+filter[0][1]+filter[0][2]+filter[1][0]+filter[1][1]+filter[1][2];
	int f = filter[1][1]+filter[1][2]+filter[2][1]+filter[2][2];
	int g = filter[1][0]+filter[1][1]+filter[2][0]+filter[2][1];
	int h = filter[0][1]+filter[0][2]+filter[1][1]+filter[1][2];
	int i = filter[0][0]+filter[0][1]+filter[1][0]+filter[1][1];

	for(int y = 1; y < height-1; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			int r = ((((inputImg[p-width-1] *filter[0][0]) +
			  			(inputImg[p-width]  *filter[0][1]) +
						(inputImg[p-width+1]*filter[0][2]) +
						(inputImg[p-1]      *filter[1][0]) +
						(inputImg[p]        *filter[1][1]) +
						(inputImg[p+1]      *filter[1][2]) +
						(inputImg[p+width-1]*filter[2][0]) +
						(inputImg[p+width]  *filter[2][1]) +
						(inputImg[p+width+1]*filter[2][2])) / a) + offset);
			if(r<0) r=0;
			if(r>255) r=255;
			outputImg[p] = (unsigned char)r;
		}
		p = y*width;
		int r = ((((inputImg[p-width]  *filter[0][1]) +
					(inputImg[p-width+1]*filter[0][2]) +
					(inputImg[p]        *filter[1][1]) +
					(inputImg[p+1]      *filter[1][2]) +
					(inputImg[p+width]  *filter[2][1]) +
					(inputImg[p+width+1]*filter[2][2])) / b) + offset);
		if(r<0) r=0;
		if(r>255) r=255;
		outputImg[p] = (unsigned char)r;
		p = width-1+y*width;
		r = ((((inputImg[p-width-1] *filter[0][0]) +
			  		(inputImg[p-width]  *filter[0][1]) +
					(inputImg[p-1]      *filter[1][0]) +
					(inputImg[p]        *filter[1][1]) +
					(inputImg[p+width-1]*filter[2][0]) +
					(inputImg[p+width]  *filter[2][1]) ) / c) + offset);
		if(r<0) r=0;
		if(r>255) r=255;
		outputImg[p] = (unsigned char)r;
	}
	for(int x = 1; x < width-1; x++ ) {
		p = x;
		int r = ((((inputImg[p-1]      *filter[1][0]) +
					(inputImg[p]        *filter[1][1]) +
					(inputImg[p+1]      *filter[1][2]) +
					(inputImg[p+width-1]*filter[2][0]) +
					(inputImg[p+width]  *filter[2][1]) +
					(inputImg[p+width+1]*filter[2][2])) / d) + offset);
		if(r<0) r=0;
		if(r>255) r=255;
		outputImg[p] = (unsigned char)r;
		p = x+(height-1)*width;
		r = ((((inputImg[p-width-1] *filter[0][0]) +
			  			(inputImg[p-width]  *filter[0][1]) +
						(inputImg[p-width+1]*filter[0][2]) +
						(inputImg[p-1]      *filter[1][0]) +
						(inputImg[p]        *filter[1][1]) +
						(inputImg[p+1]      *filter[1][2])) / e) + offset);
		if(r<0) r=0;
		if(r>255) r=255;
		outputImg[p] = (unsigned char)r;
	}
	p = 0;
	int r = ((((inputImg[p]        *filter[1][1]) +
				(inputImg[p+1]      *filter[1][2]) +
				(inputImg[p+width]  *filter[2][1]) +
				(inputImg[p+width+1]*filter[2][2])) / f) + offset);
	if(r<0) r=0;
	if(r>255) r=255;
	outputImg[p] = (unsigned char)r;
	p = width-1;
	r = ((((inputImg[p-1]        *filter[1][0]) +
				(inputImg[p]      *filter[1][1]) +
				(inputImg[p+width-1]  *filter[2][0]) +
				(inputImg[p+width]*filter[2][1])) / g) + offset);
	if(r<0) r=0;
	if(r>255) r=255;
	outputImg[p] = (unsigned char)r;
	p = (height-1)*width;
	r = ((((inputImg[p-width] *filter[0][1]) +
			  	(inputImg[p-width+1]  *filter[0][2]) +
				(inputImg[p]      *filter[1][1]) +
				(inputImg[p+1]        *filter[1][2])) / h) + offset);
	if(r<0) r=0;
	if(r>255) r=255;
	outputImg[p] = (unsigned char)r;
		p = sz-1;
	r = ((((inputImg[p-width-1] *filter[0][0]) +
			  	(inputImg[p-width]  *filter[0][1]) +
				(inputImg[p-1]      *filter[1][0]) +
				(inputImg[p]        *filter[1][1])) / i) + offset);
	if(r<0) r=0;
	if(r>255) r=255;
	outputImg[p] = (unsigned char)r;
}

void filter3x3Color (
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		int								filter[][3],
		const int&						offset)
{
	int sz = width*height;
	unsigned char *r=new unsigned char[sz],*g=new unsigned char[sz],*b=new unsigned char[sz];
	unsigned char *_r=new unsigned char[sz],*_g=new unsigned char[sz],*_b=new unsigned char[sz];

	for(int i=0; i<sz; i++){
		int index = (i<<2) - i;
		r[i] = inputImg[index];
		g[i] = inputImg[index+1];
		b[i] = inputImg[index+2];
	}

	filter3x3(r,_r,width,height,filter,offset);
	filter3x3(g,_g,width,height,filter,offset);
	filter3x3(b,_b,width,height,filter,offset);

	for(int i=0; i<sz; i++){
		int index = (i<<2) - i;
		outputImg[index]   = _r[i];
		outputImg[index+1] = _g[i];
		outputImg[index+2] = _b[i];
	}

	delete [] r;
	delete [] g;
	delete [] b;
	delete [] _r;
	delete [] _g;
	delete [] _b;
}

void Grayscale(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int sz = width*height;
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;

	for( int p = 0; p < sz; p++ )
	{
		unsigned char a = *(ptrInputImg++);
		unsigned char b = *(ptrInputImg++);
		unsigned char c = *(ptrInputImg++);

		*(ptrOutputImg++) = (int) floor(0.299 * a + 0.587 * b + 0.114 * c + 0.5);
	}
}

void Gamma(
		const unsigned char				*inputImg,
		double 							*outputImg,
		const int&						width,
		const int&						height,
		const double&					gamma)
{
	int _max = 0;
	int sz = width*height;
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;

	for( int p = 0; p < sz; p++ ){
		if(_max < *(ptrInputImg)) _max = *(ptrInputImg++);
	}
	if (gamma == 0.0) {
		ptrInputImg = (unsigned char*) inputImg;
		for( int p = 0; p < sz; p++ )
		{
			*(ptrOutputImg++) = log((double) (*(ptrInputImg++) + (1>_max)?1:_max))/256;
		}
	} else {
		for( int p = 0; p < sz; p++ )
		{
			*(ptrOutputImg++) = pow((double) *(ptrInputImg++)/255, gamma)*255;
		}
	}
}

void HistEqualize(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int sum = 0;
	int sz = width*height;
	int hist[256] = {0};
    int sum_of_hist[256] = {0};
    unsigned char *ptrInputImg = (unsigned char*) inputImg;
    unsigned char *ptrOutputImg = (unsigned char*) outputImg;
    int *ptrHist = hist;
    int *ptrSOH = sum_of_hist;

    for(int i = 0 ; i < sz ; i++ ) hist[*(ptrInputImg++)]++;

    for(int i = 0 ; i < 256 ; i++ ) {
            sum = sum + *(ptrHist++) ;
            *(ptrSOH++) = sum ;
    }

    ptrInputImg = (unsigned char*) inputImg;

    for(int i = 0 ; i < sz ; i++ ) {
    	*(ptrOutputImg++) = sum_of_hist[*(ptrInputImg++)] * (255.0/sz);
    }
}

void HistEqualize2(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int sum = 0;
	int sz = width*height;
	int hist[256] = {0};
    int sum_of_hist[256] = {0};
    unsigned char *ptrInputImg = (unsigned char*) inputImg;
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;
	int *ptrHist = hist;
	int *ptrSOH = sum_of_hist;

    for(int i = 0 ; i < sz ; i++ ) hist[*(ptrInputImg++)]++;

	int start = 0;
	int check = 0;
    for(int i = 0 ; i < 255 ; i++,ptrSOH++ ) {
    	sum = sum + *(ptrHist++) ;
    	*(ptrSOH) = sum ;
		if (!check && *(ptrSOH)!=0) {start=i;check++;}
    }

    ptrInputImg = (unsigned char*) inputImg;


    for(int i = 0 ; i < sz ; i++,ptrInputImg++ ) {
		unsigned char aa;
		if (*(ptrInputImg) == start) aa = 0;
		else aa = sum_of_hist[*(ptrInputImg)-1] * (255.0/sz) ;
		*(ptrOutputImg++) = aa;
    }
}



}

