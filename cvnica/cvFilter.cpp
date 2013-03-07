/*
 * cvFilter.cpp
 *
 *  Created on: 2013. 3. 7.
 *      Author: Nicatio
 */

#include "cvFilter.h"


using namespace cv;

namespace cvNica {

void ContrastShifting(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						mid)
{
	Mat src = _src.getMat();
	Size srcSize = src.size();
	int sz = srcSize.area();
	unsigned char bb = (sum(src)[0]/sz);
	Mat temp = src + (mid-bb);
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();
	temp.copyTo(dst);
}

}


