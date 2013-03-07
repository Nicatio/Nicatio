/*
 * cvDoG.cpp
 *
 *  Created on: 2013. 3. 6.
 *      Author: Nicatio
 */

#include "cvDoG.h"

using namespace cv;

namespace cvNica {

void DoG(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					gamma,
		const double&					sigma0,
		const double&					sigma1,
		const int&						sx,
		const int&						sy,
		const int&						mask,
		const double&					do_norm)
{
	int border = 6;
	double a = 0.1, mean1, mean2;
	double trim = abs(do_norm), oneOverTrim=1/trim;
	Mat src = _src.getMat();
	Size srcSize = src.size();
	Size repSize = Size(srcSize.width+(border<<1), srcSize.height+(border<<1));
	int sz = srcSize.area();
	Mat dst;
	Mat rep(repSize,src.type());
	Mat dog;
	Mat resultAbs,resultPow;
	Mat resultExpP,resultExpM;
	Mat repFloat, gauss7, gauss13;
	Mat gammaCorrected;
	double min_,max_;




	copyMakeBorder(src, rep, border, border,
	               border, border, BORDER_REPLICATE);

	rep.convertTo(repFloat,CV_32FC1);

	pow(repFloat,gamma,repFloat);

	GaussianBlur(repFloat, gauss7, Size(7,7), 1.0, 1.0, BORDER_DEFAULT);
	GaussianBlur(repFloat, gauss13, Size(13,13), 2.0, 2.0, BORDER_DEFAULT);

	gauss7 -= gauss13;
	dog = gauss7(Rect(border,border,srcSize.width,srcSize.height));

	if(do_norm) {
		absdiff(dog, Scalar::all(0), resultAbs);
		pow(resultAbs,a,resultPow);
		mean1 = sum(resultPow)[0]/sz;
		mean1 = 1/pow(mean1,(1.0/a));

		dog*=mean1;

		absdiff(dog, Scalar::all(0), resultAbs);
		min(resultAbs,trim,resultAbs);
		pow(resultAbs,a,resultPow);
		mean2 = sum(resultPow)[0]/sz;
		mean2 = 1/pow(mean2,(1.0/a));

		exp(dog*mean2*oneOverTrim,resultExpP);
		exp(-dog*mean2*oneOverTrim,resultExpM);

		divide((resultExpP - resultExpM),(resultExpP + resultExpM),dog);

		dog *= trim;
		minMaxLoc(dog,&min_,&max_);
	}

	max_ = 255/(max_-min_);

	dog-=min_;
	dog*=max_;
	dog.convertTo(rep,src.type());

	_dst.create(src.size(),src.type());
	dst = _dst.getMat();

	rep.copyTo(dst);
}


}


