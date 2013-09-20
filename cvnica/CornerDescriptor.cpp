/*
 * CornerDescriptor.cpp
 *
 *  Created on: 2013. 9. 16.
 *      Author: Nicatio
 */

#include "CornerDescriptor.h"

namespace cvNica {


void HomogeneousOperator(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height)
{
	int p;
	int varth=70;
	int meanth=20;
	//int sz = width*height;
	for(int y = 2; y < height-2; y++ ) {
		for(int x = 2; x < width-2; x++ ) {
			p = x+y*width;
			double var1, var2, var3, var4;
			int mean1=0, mean2=0, mean3=0, mean4=0;
			int sum1=0, sum2=0, sum3=0, sum4=0;
			int sqsum1=0, sqsum2=0, sqsum3=0, sqsum4=0;
			for(int v = -2; v <= 2; v++ ) {
				for(int u = -2; u <= 2; u++ ) {
					if(u<0) {
						int a = inputImg[p+u+v*width];
						sum1 += a;
						sqsum1 += a*a;
					} else if (u>0) {
						int a = inputImg[p+u+v*width];
						sum2 += a;
						sqsum2 += a*a;
					}
					if(v<0) {
						int a = inputImg[p+u+v*width];
						sum3 += a;
						sqsum3 += a*a;
					} else if (v>0) {
						int a = inputImg[p+u+v*width];
						sum4 += a;
						sqsum4 += a*a;
					}
				}
			}
			mean1 = sum1/10;
			mean2 = sum2/10;
			mean3 = sum3/10;
			mean4 = sum4/10;

			var1 = sqsum1-mean1*mean1;
			var2 = sqsum2-mean2*mean2;
			var3 = sqsum3-mean3*mean3;
			var4 = sqsum4-mean4*mean4;

			if (var1 > varth && var2 > varth && ((mean1-mean2)> meanth  || (mean2-mean1)> meanth)) {
				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
				outputImg[p]=255;
			} else if (var3 > varth && var4 > varth && ((mean3-mean4)> meanth  || (mean4-mean3)>meanth)) {
				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
				outputImg[p]=127;
			} else {
				outputImg[p]=0;
			}
		}
	}
}

void VarianceFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size)
{
	Mat src = _src.getMat();
	src.convertTo(src,CV_32F);
	Mat mu, mu2;
	blur(src, mu, Size(size, size));
	blur(src.mul(src), mu2, Size(size, size));
	cv::sqrt(mu2 - mu.mul(mu), _dst);
}


void DifferenceOfVariance(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Size size = src.size();
	Mat var3, var5, diff;
	VarianceFilter(_src,var3,3);
	VarianceFilter(_src,var5,5);

	//diff = (1./var5-1./var3);
	//diff = (1./(var5+1));
	diff = (var3);

	double mn,mx;
	minMaxIdx(diff,&mn,&mx);

	diff = (diff-mn)/(mx-mn)*255;

	diff.convertTo(_dst,CV_8UC1);
	minMaxIdx(_dst,&mn,&mx);
	std::cout<<mn<<","<<mx<<std::endl;
	//_dst.create(src.size(),src.type());
//	diff = (var3-var5);
//	Mat df(Size(3,3),CV_8UC1);
//	Mat df2(Size(3,3),CV_32FC1);
//
//	std::cout<<diff.type()<<","<<df.type()<<","<<df2.type()<<std::endl;
	//normalize(dst, _dst, 0.0, 1.0, NORM_MINMAX);
	//dst.copyTo(_dst);

//	namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	imshow("a",dst);
//
//	waitKey(0);
//	Mat df;

}


}


