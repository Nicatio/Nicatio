/*
 * SWT.h
 *
 *  Created on: 2014. 6. 18.
 *      Author: Nicatio
 */

#ifndef SWT_H_
#define SWT_H_

#include "cv.h"
#include "highgui.h"
//#include "cvDoG.h"
//    #define CANNY_PUSH(d)    *(d) = uchar(2), *stack_top++ = (d)
//    #define CANNY_POP(d)     (d) = *--stack_top
#define PI 3.1415926535897932384626433832795
using namespace cv;

namespace cvNica {
void SWT(
		InputArray 						_src,
		OutputArray						_dst);
}


#endif /* SWT_H_ */
