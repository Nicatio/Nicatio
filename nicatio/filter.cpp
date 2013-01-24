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

	for(int i=0; i<sz; i++){
		r[i] = inputImg[i*3];
		g[i] = inputImg[i*3+1];
		b[i] = inputImg[i*3+2];
	}

	(*pf)(r,_r,width,height);
	(*pf)(g,_g,width,height);
	(*pf)(b,_b,width,height);

	for(int i=0; i<sz; i++){
		outputImg[i*3]   = _r[i];
		outputImg[i*3+1] = _g[i];
		outputImg[i*3+2] = _b[i];
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
		if((double)d[7][i]>(double)d[12][i]*beta&&(double)d[7][i]<=(double)d[12][i]*alpha) outputImg[i] = d[10][i];
		else outputImg[i] = d[12][i];
	}

	for (int i=0; i<13; i++){
		delete [] d[i];
	}
	delete [] d;
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
	if (lower_limit < upper_limit) {
		int sz = width*height;
		if (!binary){
			for (int i=0; i<sz; i++){
				unsigned char temp = inputImg[i];
				outputImg[i] = (temp>=lower_limit && temp<=upper_limit)? temp : bg;
			}
		} else {
			for (int i=0; i<sz; i++){
				unsigned char temp = inputImg[i];
				outputImg[i] = (temp>=lower_limit && temp<=upper_limit)? 0xff : bg;
			}
		}
	}
}

void Invert(
		const unsigned char				*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int sz = width*height;
	for (int i=0; i<sz; i++) outputImg[i] = 0xff - inputImg[i];
}

void MedianFilter(
		const unsigned char						*inputImg,
		unsigned char							*outputImg,
		const int&								width,
		const int&								height)
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



}

