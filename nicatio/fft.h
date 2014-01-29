/*
 * fft.h
 *
 *  Created on: 2014. 1. 19.
 *      Author: Nicatio
 */

#ifndef FFT_H_
#define FFT_H_


#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979

namespace nicatio {

typedef double complex cplx;

void _fft(cplx buf[], cplx out[], int n, int step);

void fft(cplx buf[], int n);

void show(const char * s, cplx buf[]);

}
#endif /* FFT_H_ */
