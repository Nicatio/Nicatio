/*
 * uhd.h
 *
 *  Created on: 2014. 1. 14.
 *      Author: Nicatio
 */

#ifndef UHD_H_
#define UHD_H_


#include "cv.h"
#include "highgui.h"

using namespace cv;

namespace cvNica {

void downsample(
		const Mat 						&src,
		Mat 							&dst,
		int								startx,
		int								starty,
		const Size						&s);

unsigned char getpixel(
		const unsigned char 			*in,
		std::size_t 					src_width,
		std::size_t 					src_height,
		int	 							x,
		int								y);

void bicubicresize(
		unsigned char 					*in,
		unsigned char 					*out,
		std::size_t 					src_width,
		std::size_t 					src_height,
		std::size_t 					dest_width,
		std::size_t 					dest_height,
		int								shiftx,
		int								shifty);

}



#endif /* UHD_H_ */
