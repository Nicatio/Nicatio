/*
 * cvDoG.cpp
 *
 *  Created on: 2013. 3. 6.
 *      Author: Nicatio
 */

#include "cvDoG.h"

using namespace cv;

namespace cvNica {

unsigned char* DoG(
		const unsigned char 			*inputImg,
		const int&						width,
		const int&						height,
		const double&					gamma,
		const double&					sigma0,
		const double&					sigma1,
		const int&						sx,
		const int&						sy,
		const int&						mask,
		const double&					do_norm)
{

	int sz = width*height;
	int border = 6;
	int border1ContainedWidth = width + border;
	int border1ContainedHeight = height + border;
	int border2ContainedWidth = width + border*2;
	int border2ContainedHeight = height + border*2;
	int newsz = border2ContainedWidth*border2ContainedHeight;
	double *inputImgDouble = new double[newsz];
	double *outputImgDouble1 = new double[newsz];
	double *outputImgDouble2 = new double[newsz];
	double *outputImgDouble = new double[sz];
	unsigned char *inputImgPtr;
	double *inputImgDoublePtr, *inputImgDoublePtr2, *outputImgDoublePtr;
	double a = 0.1;
	double trim = abs(do_norm), oneOverTrim=1/trim;
	double mean1=0,mean2=0,tempdouble;
	double min_,max_;
	unsigned char *norm = new unsigned char[sz];

	for (int y=border; y<border1ContainedHeight; y++){
		inputImgDoublePtr = inputImgDouble + y*border2ContainedWidth+border;
		inputImgPtr = (unsigned char*)inputImg + (y-border)*width;
		for (int x=0; x<width; x++){
			//*(inputImgDoublePtr++) = gamma02[(int)(*(inputImgPtr++)&0xff)];
			*(inputImgDoublePtr++) = gamma02[(int)(*(inputImgPtr++))];
		}
	}

	for (int y=0; y<border; y++){
		inputImgDoublePtr = inputImgDouble + y*border2ContainedWidth+border;
		inputImgDoublePtr2 = inputImgDouble + border*border2ContainedWidth+border;
		for (int x=0; x<width; x++){
			*(inputImgDoublePtr++) = *(inputImgDoublePtr2++);
		}
	}

	for (int y=border1ContainedHeight; y<border2ContainedHeight; y++){
		inputImgDoublePtr = inputImgDouble + y*border2ContainedWidth+border;
		inputImgDoublePtr2 = inputImgDouble + (border1ContainedHeight-1)*border2ContainedWidth+border;
		for (int x=0; x<width; x++){
			*(inputImgDoublePtr++) = *(inputImgDoublePtr2++);
		}
	}

	for (int y=0; y<border2ContainedHeight; y++){
		inputImgDoublePtr = inputImgDouble + y*border2ContainedWidth;
		inputImgDoublePtr2 = inputImgDouble + y*border2ContainedWidth+border;
		for (int x=0; x<border; x++){
			*(inputImgDoublePtr++) = *(inputImgDoublePtr2);
		}
		inputImgDoublePtr = inputImgDouble + y*border2ContainedWidth + border1ContainedWidth;
		inputImgDoublePtr2 = inputImgDouble + y*border2ContainedWidth + border1ContainedWidth-1;
		for (int x=0; x<border; x++){
			*(inputImgDoublePtr++) = *(inputImgDoublePtr2);
		}
	}

	convolve2DFast(inputImgDouble, outputImgDouble1, border2ContainedWidth, border2ContainedHeight, kernel_sigma0, 7, 7);
	convolve2DFast(inputImgDouble, outputImgDouble2, border2ContainedWidth, border2ContainedHeight, kernel_sigma1,13,13);


	for (int y=border; y<border1ContainedHeight; y++){
		inputImgDoublePtr  = outputImgDouble1 + y*border2ContainedWidth+border;
		inputImgDoublePtr2 = outputImgDouble2 + y*border2ContainedWidth+border;
		outputImgDoublePtr = outputImgDouble + (y-border)*width;
		for (int x=0; x<width; x++){
			*(outputImgDoublePtr++) = *(inputImgDoublePtr++) - *(inputImgDoublePtr2++) ;
		}
	}

	if(do_norm) {
		outputImgDoublePtr = outputImgDouble;
		for (int i=0; i<sz; i++){
			mean1 += pow(abs(*(outputImgDoublePtr++)),a);
		}
		mean1 /= sz;
		mean1 = 1/pow(mean1,(1.0/a));
		outputImgDoublePtr = outputImgDouble;
		for (int i=0; i<sz; i++){
			tempdouble = *(outputImgDoublePtr) * mean1;
			*(outputImgDoublePtr++) = tempdouble;
			mean2 += pow((trim>abs(tempdouble))?abs(tempdouble):trim,a);
		}
		mean2 /= sz;
		mean2 = 1/pow(mean2,(1.0/a));
		outputImgDoublePtr = outputImgDouble;
		*(outputImgDoublePtr) = trim*tanh(*(outputImgDoublePtr) * mean2 * oneOverTrim);
		min_ = *(outputImgDoublePtr);
		max_ = *(outputImgDoublePtr++);
		for (int i=1; i<sz; i++){
			tempdouble = trim*tanh(*(outputImgDoublePtr) * mean2 * oneOverTrim);
			*(outputImgDoublePtr++) = tempdouble;
			if (min_>tempdouble) min_ = tempdouble;
			if (max_<tempdouble) max_ = tempdouble;
		}
	}
	tempdouble = 255/(max_-min_);
	inputImgPtr = norm;
	outputImgDoublePtr = outputImgDouble;
	for (int i=0; i<sz; i++){
		*(inputImgPtr++) = (unsigned int)((*(outputImgDoublePtr++)-min_)*tempdouble);
	}
	delete [] inputImgDouble;
	delete [] outputImgDouble1;
	delete [] outputImgDouble2;
	delete [] outputImgDouble;
	return norm;
}



bool convolve2DFast(
		double							*in,
		double							*out,
		int								dataSizeX,
		int								dataSizeY,
		const double					*kernel,
		int								kernelSizeX,
		int								kernelSizeY)
{
    int i, j, m, n, x, y, t;
    double **inPtr, *outPtr, *ptr;
    int kCenterX, kCenterY;
    int rowEnd, colEnd;                             // ending indice for section divider
    double sum;                                      // temp accumulation buffer
    int k, kSize;

    // check validity of params
    if(!in || !out || !kernel) return false;
    if(dataSizeX <= 0 || kernelSizeX <= 0) return false;

    // find center position of kernel (half of kernel size)
    kCenterX = kernelSizeX >> 1;
    kCenterY = kernelSizeY >> 1;
    kSize = kernelSizeX * kernelSizeY;              // total kernel size

    // allocate memeory for multi-cursor
    inPtr = new double*[kSize];
    if(!inPtr) return false;                        // allocation error

    // set initial position of multi-cursor, NOTE: it is swapped instead of kernel
    ptr = in + (dataSizeX * kCenterY + kCenterX); // the first cursor is shifted (kCenterX, kCenterY)
    for(m=0, t=0; m < kernelSizeY; ++m)
    {
        for(n=0; n < kernelSizeX; ++n, ++t)
        {
            inPtr[t] = ptr - n;
        }
        ptr -= dataSizeX;
    }

    // init working  pointers
    outPtr = out;

    rowEnd = dataSizeY - kCenterY;                  // bottom row partition divider
    colEnd = dataSizeX - kCenterX;                  // right column partition divider

    // convolve rows from index=0 to index=kCenterY-1
    y = kCenterY;
    for(i=0; i < kCenterY; ++i)
    {
        // partition #1 ***********************************
        x = kCenterX;
        for(j=0; j < kCenterX; ++j)                 // column from index=0 to index=kCenterX-1
        {
            sum = 0;
            t = 0;
            for(m=0; m <= y; ++m)
            {
                for(n=0; n <= x; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
                t += (kernelSizeX - x - 1);         // jump to next row
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }

        // partition #2 ***********************************
        for(j=kCenterX; j < colEnd; ++j)            // column from index=kCenterX to index=(dataSizeX-kCenterX-1)
        {
            sum = 0;
            t = 0;
            for(m=0; m <= y; ++m)
            {
                for(n=0; n < kernelSizeX; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }

        // partition #3 ***********************************
        x = 1;
        for(j=colEnd; j < dataSizeX; ++j)           // column from index=(dataSizeX-kCenter) to index=(dataSizeX-1)
        {
            sum = 0;
            t = x;
            for(m=0; m <= y; ++m)
            {
                for(n=x; n < kernelSizeX; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
                t += x;                             // jump to next row
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }

        ++y;                                        // add one more row to convolve for next run
    }

    // convolve rows from index=kCenterY to index=(dataSizeY-kCenterY-1)
    for(i= kCenterY; i < rowEnd; ++i)               // number of rows
    {
        // partition #4 ***********************************
        x = kCenterX;
        for(j=0; j < kCenterX; ++j)                 // column from index=0 to index=kCenterX-1
        {
            sum = 0;
            t = 0;
            for(m=0; m < kernelSizeY; ++m)
            {
                for(n=0; n <= x; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
                t += (kernelSizeX - x - 1);
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }

        // partition #5 ***********************************
        for(j = kCenterX; j < colEnd; ++j)          // column from index=kCenterX to index=(dataSizeX-kCenterX-1)
        {
            sum = 0;
            t = 0;
            for(m=0; m < kernelSizeY; ++m)
            {
                for(n=0; n < kernelSizeX; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++inPtr[t]; // in this partition, all cursors are used to convolve. moving cursors to next is safe here
                    ++t;
                }
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
        }

        // partition #6 ***********************************
        x = 1;
        for(j=colEnd; j < dataSizeX; ++j)           // column from index=(dataSizeX-kCenter) to index=(dataSizeX-1)
        {
            sum = 0;
            t = x;
            for(m=0; m < kernelSizeY; ++m)
            {
                for(n=x; n < kernelSizeX; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
                t += x;
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }
    }

    // convolve rows from index=(dataSizeY-kCenterY) to index=(dataSizeY-1)
    y = 1;
    for(i= rowEnd; i < dataSizeY; ++i)               // number of rows
    {
        // partition #7 ***********************************
        x = kCenterX;
        for(j=0; j < kCenterX; ++j)                 // column from index=0 to index=kCenterX-1
        {
            sum = 0;
            t = kernelSizeX * y;

            for(m=y; m < kernelSizeY; ++m)
            {
                for(n=0; n <= x; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
                t += (kernelSizeX - x - 1);
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }

        // partition #8 ***********************************
        for(j=kCenterX; j < colEnd; ++j)            // column from index=kCenterX to index=(dataSizeX-kCenterX-1)
        {
            sum = 0;
            t = kernelSizeX * y;
            for(m=y; m < kernelSizeY; ++m)
            {
                for(n=0; n < kernelSizeX; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];
        }

        // partition #9 ***********************************
        x = 1;
        for(j=colEnd; j < dataSizeX; ++j)           // column from index=(dataSizeX-kCenter) to index=(dataSizeX-1)
        {
            sum = 0;
            t = kernelSizeX * y + x;
            for(m=y; m < kernelSizeY; ++m)
            {
                for(n=x; n < kernelSizeX; ++n)
                {
                    sum += *inPtr[t] * kernel[t];
                    ++t;
                }
                t += x;
            }

            // store output
            *outPtr = sum;
            ++outPtr;
            ++x;
            for(k=0; k < kSize; ++k) ++inPtr[k];    // move all cursors to next
        }

        ++y;                                        // the starting row index is increased
    }

    return true;
}


}


