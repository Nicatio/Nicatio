/*
 * guidedFilter.h
 *
 *  Created on: 2013. 1. 31.
 *      Author: Nicatio
 */

#ifndef GUIDEDFILTER_H_
#define GUIDEDFILTER_H_

#pragma once

#include "cv.h"

class CGuidedFilter
{
public:
	CGuidedFilter(void);
	~CGuidedFilter(void);

	// guidencIMG : Guidence image(Gray or RGB Color)
	// inputIMG : filtering input image(Gray)
	// radius : local window radius(>= 0)
	// eps : regularization parameter(> 0.0)
	cv::Mat filtering(const cv::Mat& guidenceIMG, const cv::Mat& inputIMG, const int radius, const double eps);

private:
	// Definition imDst(x, y)=sum(sum(imSrc(x-r:x+r,y-r:y+r)));
	// Running time independent of r;
	// Equivalent to the function: colfilt(imSrc, [2*r+1, 2*r+1], 'sliding', @sum);
	// But much faster.
	cv::Mat boxfilter(const cv::Mat& imSrc, const int r);
	// Cumulative sum
	cv::Mat cumsum(const cv::Mat& imSrc);
	cv::Mat cumsum(const cv::Mat& imSrc, const int dim);
	// Replicate and tile array
	cv::Mat repmat(const cv::Mat& A, const int m, const int n);
};


#endif /* GUIDEDFILTER_H_ */
