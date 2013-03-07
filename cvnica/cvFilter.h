/*
 * cvFilter.h
 *
 *  Created on: 2013. 3. 7.
 *      Author: Nicatio
 */

#ifndef CVFILTER_H_
#define CVFILTER_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

namespace cvNica {

void ContrastShifting(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						mid);

}


#endif /* FILTER_H_ */
