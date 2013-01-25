/*
 * math.cpp
 *
 *  Created on: 2013. 1. 24.
 *      Author: HDSP
 */

#include "math.h"

namespace nicatio {

int Median(
		int								*num,
		const int&						len)
{
	int i,j,tempINT;
    for(i=0; i<len-1; i++){
        for(j=0; j<len-i-1; j++){
            if(num[j+1] < num[j]){
                tempINT = num[j];
                num[j] = num[j+1];
                num[j+1] = tempINT;
            }
        }
    }
	return (len%2)?num[len/2]:num[len/2-1];
}

unsigned char Median(
		unsigned char					*num,
		const int&						len)
{
	int i,j;
	unsigned char tempINT;
    for(i=0; i<len-1; i++){
        for(j=0; j<len-i-1; j++){
            if(num[j+1] < num[j]){
                tempINT = num[j];
                num[j] = num[j+1];
                num[j+1] = tempINT;
            }
        }
    }
	return (len%2)?num[len/2]:num[len/2-1];
}

void Ycbcr(
		const unsigned char				*inputImg,
		double							**ycbcr,
		const int&						width,
		const int&						height)
{
	int sz = width*height;
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	for (int i=0; i<sz; i++){
		double a = *(ptrInputImg++);
		double b = *(ptrInputImg++);
		double c = *(ptrInputImg++);
		ycbcr[0][i] = 16  + 1.0/256 * (   65.738  * a +  129.057  *  b +  25.064  *  c);
		ycbcr[1][i] = 128 + 1.0/256 * (  -37.945  * a -   74.494  *  b + 112.439  *  c);
		ycbcr[2][i] = 128 + 1.0/256 * (  112.439  * a -   94.154  *  b -  18.285  *  c);
	}
}

double Lightness(
		const unsigned char 			*inputImg,
		const int&						width,
		const int&						height,
		const int&						channel)
{
	int sz = width*height;
	double oneOverSZ = 1.0/sz;
	int sum = 0;
	unsigned char *ptrInputImg = (unsigned char*) inputImg;
	if (channel == 1){
		for (int i=0; i<sz; i++){
			sum += *(ptrInputImg++);
		}
		return (double)sum * oneOverSZ;
	} else {

		for (int i=0; i<sz; i++){
			sum += *(ptrInputImg++);
			sum += *(ptrInputImg++);
			sum += *(ptrInputImg++);
		}
		return (double)sum * 0.333333333333 * oneOverSZ;
	}

}

}


