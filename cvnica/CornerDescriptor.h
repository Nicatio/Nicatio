/*
 * CornerDescriptor.h
 *
 *  Created on: 2013. 9. 16.
 *      Author: Nicatio
 */

#ifndef CORNERDESCRIPTOR_H_
#define CORNERDESCRIPTOR_H_

#define CORNER_ALL        0
#define CORNER_VERTICAL   1
#define CORNER_HORIZONTAL 2
#define CORNER_DIAG_RT    3
#define CORNER_DIAG_LT    4
#define CORNER_CORNER_RT  5
#define CORNER_CORNER_LT  6
#define CORNER_CORNER_LB  7
#define CORNER_CORNER_RB  8

#include "cv.h"
#include "highgui.h"
#include "cvDoG.h"
    #define CANNY_PUSH(d)    *(d) = uchar(2), *stack_top++ = (d)
    #define CANNY_POP(d)     (d) = *--stack_top

using namespace cv;

namespace cvNica {

void HomogeneousOperator(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						type = CORNER_ALL);
void MorphologicalThinning(CvMat *pSrc, CvMat *pDst);
void ThinSubiteration1(CvMat *pSrc, CvMat *pDst);
void ThinSubiteration2(CvMat *pSrc, CvMat *pDst);
void Canny2( InputArray _src, Mat dx, Mat dy, OutputArray _dst,
                double low_thresh, double high_thresh,
                int aperture_size, bool L2gradient );

void Canny3( InputArray _src, OutputArray _dst,
                double low_thresh, double high_thresh,
                int aperture_size, bool L2gradient );

void MeanFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size);

void VarianceFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size);

Mat kernels(
		int								type,
		Point&							point);

void CornerDetectorBasedOnEdge(
		InputArray 						_src,
		OutputArray						_dst,
		int								type);

void CornerDetector(
		InputArray 						_src,
		OutputArray						_dst,
		int								type,
		int								nPart=2);

void HeteroDetector(
		InputArray 						_src,
		OutputArray						_dst,
		int								type,
		int								nPart=2);

void RGBThresholdMinMaxSelector(
		Vector<int>						resultpoints,
		int								tolerance,
		int								type,
		int&							rb,
		int&							ru,
		int&							gb,
		int&							gu,
		int&							bb,
		int&							bu);

Mat RGBThreshold(
		const Mat						&src,
		Vector<int>						resultpoints,
		int								tolerance,
		int								type);

Mat RGBThresholdPoint(
		Size							size,
		Vector< Vector<int> >&			cornerpoints,
		int								r,
		int								g,
		int								b,
		int								tolerance);

Mat RGBThresholdPointCC(
		Mat								thImage,
		Vector< Vector<int> >&			cornerpoints,
		Vector<int>						resultpoints,
		int								tolerance,
		int								type);

Mat RGBThresholdPointCC2(
		Mat								thImage,
		Vector< Vector<int> >&			cornerpoints,
		Vector<int>						resultpoints,
		int								tolerance,
		int								type);
Vector< Vector<int> > kmeansWrapper(
		Vector< Vector<int> >&			cornerpoints,
		int								K);
void RGBhistogram(
		Mat								__src,
		Mat								points,
		Vector< Vector<int> >&			cornerpoints,
		int								type,
		int								nPart=2);

void VarianceMap32bit(
		InputArray 						_src,
		OutputArray						_dst,
		Mat								kernel,
		Point							point);

void MeanMap32bit(
		InputArray 						_src,
		OutputArray						_dst,
		Mat								kernel,
		Point							point);

void VarianceMap(
		InputArray 						_src,
		OutputArray						_dst,
		int								type);

void DifferenceOfVariance(
		InputArray 						_src,
		OutputArray						_dst);

void MultiscaleVarianceMap(
		InputArray 						_src,
		OutputArray						_dst,
		double							ratio);
}


#endif /* CORNERDESCRIPTOR_H_ */
