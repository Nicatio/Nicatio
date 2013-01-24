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

}


