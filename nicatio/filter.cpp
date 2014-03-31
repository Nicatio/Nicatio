/*
 * filter.cpp
 *
 *  Created on: 2013. 1. 24.
 *      Author: Nicatio
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
		const unsigned char 			*outputImg,
		const int&						width,
		const int&						height,
		const double&					gamma)
{
	int _max = 0;
	int sz = width*height;
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	double *doubleOutputImg = new double[sz];
	unsigned char *ptrOutputImg = (unsigned char*) outputImg;

	for( int p = 0; p < sz; p++ ){
		if(_max < *(ptrInputImg)) _max = *(ptrInputImg++);
	}
	if (gamma == 0.0) {
		double min=1e100, max=0;
		double *ptrDoubleOutputImg = doubleOutputImg;
		ptrInputImg = (unsigned char*) inputImg;
//		for( int p = 0; p < sz; p++ )
//		{
//			*(ptrOutputImg++) = log((double) (*(ptrInputImg++) + (1>_max)?1:_max))/255;
//		}

		for (int i=0; i<sz; i++) {
			double t = *(ptrInputImg++);
			//t = log(t);
			if (t!=0.0)	t = log(t);//pow(t, _gamma);
			*(ptrDoubleOutputImg++) = t;
			if (t>max) max=t;
			if (t<min) min=t;								// get min max magnitude values
		}
		ptrDoubleOutputImg = doubleOutputImg;
		ptrInputImg = (unsigned char*) inputImg;
		double stretch = 1.0/(max-min)*255;					// stretch coefficient
		for (int i=0; i<sz; i++) {
			*(ptrOutputImg++) = (unsigned char) ((*(ptrDoubleOutputImg++)-min)*stretch);
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
    double sz255 = 255.0/sz;
    unsigned char *ptrInputImg = (unsigned char*) inputImg;
    unsigned char *ptrOutputImg = (unsigned char*) outputImg;
    int *ptrHist = hist;
    int *ptrSOH = sum_of_hist;

    for(int i = 0 ; i < sz ; i++ ) hist[*(ptrInputImg++)]++;

    for(int i = 0 ; i < 256 ; i++ ) {
            sum = sum + *(ptrHist++) ;
            *(ptrSOH++) = sum ;
    }

    ptrSOH = sum_of_hist;
    for(int i = 0 ; i < 256 ; i++,ptrSOH++ ) {
            *(ptrSOH) = (unsigned char) (0.5+ sz255 * *(ptrSOH)) ;
    }

    ptrInputImg = (unsigned char*) inputImg;

    for(int i = 0 ; i < sz ; i++ ) {
    	*(ptrOutputImg++) = sum_of_hist[*(ptrInputImg++)];
    	//*(ptrOutputImg++) = sum_of_hist[*(ptrInputImg++)]) * (256.0/sz);
    	//*(ptrOutputImg++) = (unsigned char)(0.5+(255.0/sz)* sum_of_hist[*(ptrInputImg++)]) ;
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

void localHistogramEqualization(
		unsigned char				*image,
		unsigned char					*out,
		int 							width,
		int 							height,
		int 							wsize)
{
    int hwsize = wsize >> 1;
    wsize = (hwsize << 1) + 1; //odd #;
    int topstop = height - wsize;
    int leftstop = width - wsize;
    for (int y = 0, offset = 0; y < height; y++, offset += width) {
        int top = y - hwsize;
        top = top < 0 ? 0 : top > topstop ? topstop : top;
        unsigned char *imgrow = &image[offset];
        unsigned char *outrow = &out[offset];
        for (int x = 0; x < width; x++) {
            int left = x - hwsize;
            left = left < 0 ? 0 : left > leftstop ? leftstop : left;
            //make local histogram;
            int histo[256] = {0};
            //memset(histo, 0, sizeof(histo));
            for (int yy = 0, woffset = top * width + left; yy < wsize; yy++, woffset += width) {
            	unsigned char * winrow = &image[woffset];
                for (int xx = 0; xx < wsize; xx++) {
                    histo[winrow[xx]]++;
                }
            }
            int level = imgrow[x];
            int csum = 0;
            if (level < 128) {
                for (int k = 0; k <= level; k++) csum += histo[k];
            }
            else {
                csum = wsize * wsize;
                for (int k = level + 1; k < 256; k++) csum -= histo[k];
            }
            //apply local histogram eq.
            int a = int((255.0 * csum)/(wsize * wsize)) ;
            outrow[x] = (a & ~255) == 0 ? a: a < 0 ? 0: 255;
        }
    }
}

int CLAHE (kz_pixel_t* pImage, unsigned int uiXRes, unsigned int uiYRes,
	 kz_pixel_t Min, kz_pixel_t Max, unsigned int uiNrX, unsigned int uiNrY,
	      unsigned int uiNrBins, float fCliplimit)
/*   pImage - Pointer to the input/output image
 *   uiXRes - Image resolution in the X direction
 *   uiYRes - Image resolution in the Y direction
 *   Min - Minimum greyvalue of input image (also becomes minimum of output image)
 *   Max - Maximum greyvalue of input image (also becomes maximum of output image)
 *   uiNrX - Number of contextial regions in the X direction (min 2, max uiMAX_REG_X)
 *   uiNrY - Number of contextial regions in the Y direction (min 2, max uiMAX_REG_Y)
 *   uiNrBins - Number of greybins for histogram ("dynamic range")
 *   float fCliplimit - Normalized cliplimit (higher values give more contrast)
 * The number of "effective" greylevels in the output image is set by uiNrBins; selecting
 * a small value (eg. 128) speeds up processing and still produce an output image of
 * good quality. The output image will have the same minimum and maximum value as the input
 * image. A clip limit smaller than 1 results in standard (non-contrast limited) AHE.
 */
{
    unsigned int uiX, uiY;		  /* counters */
    unsigned int uiXSize, uiYSize, uiSubX, uiSubY; /* size of context. reg. and subimages */
    unsigned int uiXL, uiXR, uiYU, uiYB;  /* auxiliary variables interpolation routine */
    unsigned long ulClipLimit, ulNrPixels;/* clip limit and region pixel count */
    kz_pixel_t* pImPointer;		   /* pointer to image */
    kz_pixel_t aLUT[uiNR_OF_GREY];	    /* lookup table used for scaling of input image */
    unsigned long* pulHist, *pulMapArray; /* pointer to histogram and mappings*/
    unsigned long* pulLU, *pulLB, *pulRU, *pulRB; /* auxiliary pointers interpolation */

    if (uiNrX > uiMAX_REG_X) return -1;	   /* # of regions x-direction too large */
    if (uiNrY > uiMAX_REG_Y) return -2;	   /* # of regions y-direction too large */
    if (uiXRes % uiNrX) return -3;	  /* x-resolution no multiple of uiNrX */
    if (uiYRes % uiNrY) return -4;	  /* y-resolution no multiple of uiNrY */
    if (Max >= uiNR_OF_GREY) return -5;	   /* maximum too large */
    if (Min >= Max) return -6;		  /* minimum equal or larger than maximum */
    if (uiNrX < 2 || uiNrY < 2) return -7;/* at least 4 contextual regions required */
    if (fCliplimit == 1.0) return 0;	  /* is OK, immediately returns original image. */
    if (uiNrBins == 0) uiNrBins = 128;	  /* default value when not specified */

    pulMapArray= new unsigned long [uiNrX*uiNrY*uiNrBins];//(unsigned long *)malloc(sizeof(unsigned long)*uiNrX*uiNrY*uiNrBins);
    if (pulMapArray == 0) return -8;	  /* Not enough memory! (try reducing uiNrBins) */

    uiXSize = uiXRes/uiNrX; uiYSize = uiYRes/uiNrY;  /* Actual size of contextual regions */
    ulNrPixels = (unsigned long)uiXSize * (unsigned long)uiYSize;

    if(fCliplimit > 0.0) {		  /* Calculate actual cliplimit	 */
       ulClipLimit = (unsigned long) (fCliplimit * (uiXSize * uiYSize) / uiNrBins);
       ulClipLimit = (ulClipLimit < 1UL) ? 1UL : ulClipLimit;
    }
    else ulClipLimit = 1UL<<14;		  /* Large value, do not clip (AHE) */
    MakeLut(aLUT, Min, Max, uiNrBins);	  /* Make lookup table for mapping of greyvalues */
    /* Calculate greylevel mappings for each contextual region */
    for (uiY = 0, pImPointer = pImage; uiY < uiNrY; uiY++) {
	for (uiX = 0; uiX < uiNrX; uiX++, pImPointer += uiXSize) {
	    pulHist = &pulMapArray[uiNrBins * (uiY * uiNrX + uiX)];
	    MakeHistogram(pImPointer,uiXRes,uiXSize,uiYSize,pulHist,uiNrBins,aLUT);
	    ClipHistogram(pulHist, uiNrBins, ulClipLimit);
	    MapHistogram(pulHist, Min, Max, uiNrBins, ulNrPixels);
	}
	pImPointer += (uiYSize - 1) * uiXRes;		  /* skip lines, set pointer */
    }

    /* Interpolate greylevel mappings to get CLAHE image */
    for (pImPointer = pImage, uiY = 0; uiY <= uiNrY; uiY++) {
	if (uiY == 0) {					  /* special case: top row */
	    uiSubY = uiYSize >> 1;  uiYU = 0; uiYB = 0;
	}
	else {
	    if (uiY == uiNrY) {				  /* special case: bottom row */
		uiSubY = uiYSize >> 1;	uiYU = uiNrY-1;	 uiYB = uiYU;
	    }
	    else {					  /* default values */
		uiSubY = uiYSize; uiYU = uiY - 1; uiYB = uiYU + 1;
	    }
	}
	for (uiX = 0; uiX <= uiNrX; uiX++) {
	    if (uiX == 0) {				  /* special case: left column */
		uiSubX = uiXSize >> 1; uiXL = 0; uiXR = 0;
	    }
	    else {
		if (uiX == uiNrX) {			  /* special case: right column */
		    uiSubX = uiXSize >> 1;  uiXL = uiNrX - 1; uiXR = uiXL;
		}
		else {					  /* default values */
		    uiSubX = uiXSize; uiXL = uiX - 1; uiXR = uiXL + 1;
		}
	    }

	    pulLU = &pulMapArray[uiNrBins * (uiYU * uiNrX + uiXL)];
	    pulRU = &pulMapArray[uiNrBins * (uiYU * uiNrX + uiXR)];
	    pulLB = &pulMapArray[uiNrBins * (uiYB * uiNrX + uiXL)];
	    pulRB = &pulMapArray[uiNrBins * (uiYB * uiNrX + uiXR)];
	    Interpolate(pImPointer,uiXRes,pulLU,pulRU,pulLB,pulRB,uiSubX,uiSubY,aLUT);
	    pImPointer += uiSubX;			  /* set pointer on next matrix */
	}
	pImPointer += (uiSubY - 1) * uiXRes;
    }
    delete [] pulMapArray;//free(pulMapArray);					  /* free space for histograms */
    return 0;						  /* return status OK */
}
void ClipHistogram (unsigned long* pulHistogram, unsigned int
		     uiNrGreylevels, unsigned long ulClipLimit)
/* This function performs clipping of the histogram and redistribution of bins.
 * The histogram is clipped and the number of excess pixels is counted. Afterwards
 * the excess pixels are equally redistributed across the whole histogram (providing
 * the bin count is smaller than the cliplimit).
 */
{
    unsigned long* pulBinPointer, *pulEndPointer, *pulHisto;
    unsigned long ulNrExcess, ulUpper, ulBinIncr, ulStepSize, i;
    long lBinExcess;

    ulNrExcess = 0;  pulBinPointer = pulHistogram;
    for (i = 0; i < uiNrGreylevels; i++) { /* calculate total number of excess pixels */
	lBinExcess = (long) pulBinPointer[i] - (long) ulClipLimit;
	if (lBinExcess > 0) ulNrExcess += lBinExcess;	  /* excess in current bin */
    };

    /* Second part: clip histogram and redistribute excess pixels in each bin */
    ulBinIncr = ulNrExcess / uiNrGreylevels;		  /* average binincrement */
    ulUpper =  ulClipLimit - ulBinIncr;	 /* Bins larger than ulUpper set to cliplimit */

    for (i = 0; i < uiNrGreylevels; i++) {
      if (pulHistogram[i] > ulClipLimit) pulHistogram[i] = ulClipLimit; /* clip bin */
      else {
	  if (pulHistogram[i] > ulUpper) {		/* high bin count */
	      ulNrExcess -= pulHistogram[i] - ulUpper; pulHistogram[i]=ulClipLimit;
	  }
	  else {					/* low bin count */
	      ulNrExcess -= ulBinIncr; pulHistogram[i] += ulBinIncr;
	  }
       }
    }

    while (ulNrExcess) {   /* Redistribute remaining excess  */
	pulEndPointer = &pulHistogram[uiNrGreylevels]; pulHisto = pulHistogram;

	while (ulNrExcess && pulHisto < pulEndPointer) {
	    ulStepSize = uiNrGreylevels / ulNrExcess;
	    if (ulStepSize < 1) ulStepSize = 1;		  /* stepsize at least 1 */
	    for (pulBinPointer=pulHisto; pulBinPointer < pulEndPointer && ulNrExcess;
		 pulBinPointer += ulStepSize) {
		if (*pulBinPointer < ulClipLimit) {
		    (*pulBinPointer)++;	 ulNrExcess--;	  /* reduce excess */
		}
	    }
	    pulHisto++;		  /* restart redistributing on other bin location */
	}
    }
}
//void MakeHistogram (kz_pixel_t* pImage, unsigned int uiXRes,
//		unsigned int uiSizeX, unsigned int uiSizeY,
//		unsigned long* pulHistogram,
//		unsigned int uiNrGreylevels, kz_pixel_t* pLookupTable)
///* This function classifies the greylevels present in the array image into
// * a greylevel histogram. The pLookupTable specifies the relationship
// * between the greyvalue of the pixel (typically between 0 and 4095) and
// * the corresponding bin in the histogram (usually containing only 128 bins).
// */
//{
//    kz_pixel_t* pImagePointer;
//    unsigned int i;
//
//    for (i = 0; i < uiNrGreylevels; i++) pulHistogram[i] = 0L; /* clear histogram */
//
//    for (i = 0; i < uiSizeY; i++) {
//	pImagePointer = &pImage[uiSizeX];
//	while (pImage < pImagePointer) pulHistogram[pLookupTable[*pImage++]]++;
//	pImagePointer += uiXRes;
//	pImage = &pImagePointer[-uiSizeX];
//    }
//}


void MakeHistogram (kz_pixel_t* pImage, unsigned int uiXRes,
 unsigned int uiSizeX, unsigned int uiSizeY,
 unsigned long* pulHistogram,
 unsigned int uiNrGreylevels, kz_pixel_t* pLookupTable)
/* This function classifies the greylevels present in the array image into
 * a greylevel histogram. The pLookupTable specifies the relationship
 * between the greyvalue of the pixel (typically between 0 and 4095) and
 * the corresponding bin in the histogram (usually containing only 128 bins).
 */
{
 unsigned int i,j=0;

for (i = 0; i < uiNrGreylevels; i++) pulHistogram[i] = 0L; /* clear histogram */

for (i = 0; i < uiSizeY; i++) {
 j = 0;
 while (j < uiSizeX) { pulHistogram[pLookupTable[pImage[j]]]++; ++j; }
 pImage = &pImage[uiXRes];
 }
}


void MapHistogram (unsigned long* pulHistogram, kz_pixel_t Min, kz_pixel_t Max,
	       unsigned int uiNrGreylevels, unsigned long ulNrOfPixels)
/* This function calculates the equalized lookup table (mapping) by
 * cumulating the input histogram. Note: lookup table is rescaled in range [Min..Max].
 */
{
    unsigned int i;  unsigned long ulSum = 0;
    const float fScale = ((float)(Max - Min)) / ulNrOfPixels;
    const unsigned long ulMin = (unsigned long) Min;

    for (i = 0; i < uiNrGreylevels; i++) {
	ulSum += pulHistogram[i]; pulHistogram[i]=(unsigned long)(ulMin+ulSum*fScale);
	if (pulHistogram[i] > Max) pulHistogram[i] = Max;
    }
}

void MakeLut (kz_pixel_t * pLUT, kz_pixel_t Min, kz_pixel_t Max, unsigned int uiNrBins)
/* To speed up histogram clipping, the input image [Min,Max] is scaled down to
 * [0,uiNrBins-1]. This function calculates the LUT.
 */
{
    int i;
    const kz_pixel_t BinSize = (kz_pixel_t) (1 + (Max - Min) / uiNrBins);

    for (i = Min; i <= Max; i++)  pLUT[i] = (i - Min) / BinSize;
}

void Interpolate (kz_pixel_t * pImage, int uiXRes, unsigned long * pulMapLU,
     unsigned long * pulMapRU, unsigned long * pulMapLB,  unsigned long * pulMapRB,
     unsigned int uiXSize, unsigned int uiYSize, kz_pixel_t * pLUT)
/* pImage      - pointer to input/output image
 * uiXRes      - resolution of image in x-direction
 * pulMap*     - mappings of greylevels from histograms
 * uiXSize     - uiXSize of image submatrix
 * uiYSize     - uiYSize of image submatrix
 * pLUT	       - lookup table containing mapping greyvalues to bins
 * This function calculates the new greylevel assignments of pixels within a submatrix
 * of the image with size uiXSize and uiYSize. This is done by a bilinear interpolation
 * between four different mappings in order to eliminate boundary artifacts.
 * It uses a division; since division is often an expensive operation, I added code to
 * perform a logical shift instead when feasible.
 */
{
    const unsigned int uiIncr = uiXRes-uiXSize; /* Pointer increment after processing row */
    kz_pixel_t GreyValue; unsigned int uiNum = uiXSize*uiYSize; /* Normalization factor */

    unsigned int uiXCoef, uiYCoef, uiXInvCoef, uiYInvCoef, uiShift = 0;

    if (uiNum & (uiNum - 1))   /* If uiNum is not a power of two, use division */
    for (uiYCoef = 0, uiYInvCoef = uiYSize; uiYCoef < uiYSize;
	 uiYCoef++, uiYInvCoef--,pImage+=uiIncr) {
	for (uiXCoef = 0, uiXInvCoef = uiXSize; uiXCoef < uiXSize;
	     uiXCoef++, uiXInvCoef--) {
	    GreyValue = pLUT[*pImage];		   /* get histogram bin value */
	    *pImage++ = (kz_pixel_t ) ((uiYInvCoef * (uiXInvCoef*pulMapLU[GreyValue]
				      + uiXCoef * pulMapRU[GreyValue])
				+ uiYCoef * (uiXInvCoef * pulMapLB[GreyValue]
				      + uiXCoef * pulMapRB[GreyValue])) / uiNum);
	}
    }
    else {			   /* avoid the division and use a right shift instead */
	while (uiNum >>= 1) uiShift++;		   /* Calculate 2log of uiNum */
	for (uiYCoef = 0, uiYInvCoef = uiYSize; uiYCoef < uiYSize;
	     uiYCoef++, uiYInvCoef--,pImage+=uiIncr) {
	     for (uiXCoef = 0, uiXInvCoef = uiXSize; uiXCoef < uiXSize;
	       uiXCoef++, uiXInvCoef--) {
	       GreyValue = pLUT[*pImage];	  /* get histogram bin value */
	       *pImage++ = (kz_pixel_t)((uiYInvCoef* (uiXInvCoef * pulMapLU[GreyValue]
				      + uiXCoef * pulMapRU[GreyValue])
				+ uiYCoef * (uiXInvCoef * pulMapLB[GreyValue]
				      + uiXCoef * pulMapRB[GreyValue])) >> uiShift);
	    }
	}
    }
}

}

