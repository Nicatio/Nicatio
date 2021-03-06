/*
 * hausdorff.cpp
 *
 *  Created on: 2013. 1. 25.
 *      Author: Nicatio
 */

#include "hausdorff.h"

namespace nicatio {

void DistTransform(
		unsigned int				**A,
		const int&					w,
		const int&					h)
{
	int _w = w-1;
	int _h = h-1;

	//forward pass
	for (int i=1;i<w;i++){
		unsigned int a_min = A[ 0 ][ i ];
		unsigned int l = A[ 0 ][i-1]+5, lb = A[ 1 ][i-1]+7;
		if (a_min>l ) a_min = l;
		if (a_min>lb) a_min = lb;
		A[0][i] = a_min;
	}

	for (int j=1;j<_h;j++) {
		unsigned int a_min = A[j-1][ 0 ]+5;
		if (A[j][0]>a_min) A[j][0] = a_min;

		for (int i=1;i<w;i++){
			unsigned int a_min = A[j][i];
			unsigned int lt = A[j-1][i-1]+7, l = A[ j ][i-1]+5, lb = A[j+1][i-1]+7, t = A[j-1][ i ];
			if (a_min>lt) a_min = lt;
			if (a_min>l ) a_min = l;
			if (a_min>lb) a_min = lb;
			if (a_min>t ) a_min = t;
			A[j][i] = a_min;
		}
	}

	unsigned int a_min = A[_h-1][ 0 ]+5;
	if (A[_h][0]>a_min) A[_h][0] = a_min;

	for (int i=1;i<w;i++){
		unsigned int a_min = A[_h][i];
		unsigned int lt = A[_h-1][i-1]+7, l = A[ _h ][i-1]+5, t = A[_h-1][ i ];
		if (a_min>lt) a_min = lt;
		if (a_min>l ) a_min = l;
		if (a_min>t ) a_min = t;
		A[_h][i] = a_min;
	}

	//backward pass
	for (int i=_w-1;i>=0;i--){
		unsigned int a_min = A[_h][i];
		unsigned int rt = A[_h-1][i+1]+7, r = A[_h][i+1]+5;
		if (a_min>rt) a_min = rt;
		if (a_min>r ) a_min = r;
		A[_h][i] = a_min;
	}
	for (int j=_h-1;j>0;j--) {
		for (int i=_w-1;i>=0;i--){
			unsigned int a_min = A[j][i];
			unsigned int b = A[j+1][ i ]+5, rt = A[j-1][i+1]+7, r = A[ j ][i+1]+5, rb = A[j+1][i+1]+7;
			if (a_min>b ) a_min = b;
			if (a_min>rt) a_min = rt;
			if (a_min>r ) a_min = r;
			if (a_min>rb) a_min = rb;
			A[j][i] = a_min;
		}
		unsigned int a_min = A[j+1][ _w ]+5;
		if (A[j][_w]>a_min) A[j][_w] = a_min;
	}

	a_min = A[ 1 ][ _w ]+5;
	if (A[0][_w]>a_min) A[0][_w] = a_min;

	for (int i=_w-1;i>=0;i--){
		unsigned int a_min = A[0][i];
		unsigned int b = A[ 1 ][ i ]+5, r = A[ 0 ][i+1]+5, rb = A[ 1 ][i+1]+7;
		if (a_min>b ) a_min = b;
		if (a_min>r ) a_min = r;
		if (a_min>rb) a_min = rb;
		A[0][i] = a_min;
	}
}

double HausdorffDist2012(
		const unsigned char				*A,
		const unsigned char				*B,
		const int&						width,
		const int&						height,
		const int&						AoffsetX,
		const int&						AoffsetY,
		const int&						BoffsetX,
		const int&						BoffsetY,
		const int&						type)
{
	unsigned int sz = width*height;
	unsigned int **DA = new unsigned int* [height];
	unsigned int **DB = new unsigned int* [height];
	for (int i=height-1;i>=0;i--) {
		DA[i] = new unsigned int [width];
		DB[i] = new unsigned int [width];
		for (int j=width-1;j>=0;j--){
			DA[i][j] = (A[(i+AoffsetY)*width+(j+AoffsetX)] == 0)? 0xffffff:0;
			DB[i][j] = (B[(i+BoffsetY)*width+(j+BoffsetX)] == 0)? 0xffffff:0;
		}
	}
	DistTransform(DA,width,height);
	DistTransform(DB,width,height);
	unsigned int sumA = 0;
	unsigned int sumB = 0;
	if (!type) // max
	{

	}
	else
	{
		for (int i=height-1;i>=0;i--) {
			for (int j=width-1;j>=0;j--){
				if (B[i*width+j]) sumA += DA[i][j];
				if (A[i*width+j]) sumB += DB[i][j];
			}
		}
	}

	for (int i=height-1;i>=0;i--) {
		delete [] DA[i];
		delete [] DB[i];
	}
	delete [] DA;
	delete [] DB;

	unsigned int sum = (sumA>sumB)? sumA:sumB;

	return (double)(sum)/(sz);

}

}
