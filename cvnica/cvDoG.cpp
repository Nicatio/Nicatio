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

	}

	minMaxLoc(dog,&min_,&max_);
	max_ = 255/(max_-min_);

	dog-=min_;
	dog*=max_;
	dog.convertTo(rep,src.type());

	_dst.create(src.size(),src.type());
	dst = _dst.getMat();

	rep.copyTo(dst);
}

void DoGMask(
		InputArray 						_src,
		InputArray 						_mask,
		OutputArray						_dst,
		Size							maskSize,
		const double&					gamma,
		const double&					sigma0,
		const double&					sigma1,
		const int&						sx,
		const int&						sy,
		const int&						mask_,
		const double&					do_norm)
{
	int border = 6;
	double a = 0.1, mean1, mean2;
	double trim = abs(do_norm), oneOverTrim=1/trim;
	Mat src = _src.getMat();
	Mat __mask = _mask.getMat();
	Mat mask; __mask.convertTo(mask,CV_32FC1);
	Size srcSize = src.size();
	Size repSize = Size(srcSize.width+(border<<1), srcSize.height+(border<<1));
	int sz = sum(mask)[0]/255;//maskSize.area();
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
	multiply(dog,mask,dog);
	//dog.mult(mask);
	//dog *= (mask/255);

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

void BinFace(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						contrastMid,
		const int&						th)
{
	Mat src = _src.getMat();
	Size srcSize = src.size();

	Mat TT,CS,Th;
	DoG(src,TT,0.2,1,-2,0,0,0,10);
	IntensityShifting(TT,CS,contrastMid);
	threshold(CS,Th,th,255,THRESH_BINARY_INV);

	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Th.copyTo(dst);
}

void BinFaceMask(
		InputArray 						_src,
		InputArray 						_mask,
		OutputArray						_dst,
		Size							maskSize,
		const int&						contrastMid,
		const int&						th)
{
	Mat src = _src.getMat();
	Mat mask = _mask.getMat();
	Size srcSize = src.size();

	Mat TT,CS,Th;
	DoGMask(src,mask,TT,maskSize,0.2,1,-2,0,0,0,10);
	IntensityShifting(TT,CS,contrastMid);
	threshold(CS,Th,th,255,THRESH_BINARY_INV);

	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Th.copyTo(dst);
}


float FaceRollAngleDetection(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Size srcSize = src.size();
	Mat srcCopy (src);
	vector<Vec4i> lines;
    HoughLinesP( srcCopy, lines, 1, CV_PI/180, 50, 20, 5 );

    int b = lines.size();
    float a=0;
    return a;

}

void FourierLaplacian(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Size srcSize = src.size();
	Mat padded;                            //expand input image to optimal size

	int m = getOptimalDFTSize( srcSize.height );
	int n = getOptimalDFTSize( srcSize.width ); // on the border add zero values
	copyMakeBorder(src, padded, 0, m - srcSize.height, 0, n - srcSize.width, BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;
	Mat u2v2 = Mat::zeros(padded.size(), CV_32F);
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	dft(complexI, complexI);            // this way the result may fit in the source matrix

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))

    int cx = complexI.cols/2;
    int cy = complexI.rows/2;

    Mat q0(complexI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(complexI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(complexI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(complexI, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);




	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

    Mat circleMask(srcSize,CV_32FC1);
    ellipse (circleMask,Point(n/2,m/2), Size(n/4,n/4),0,0,360, Scalar( 1, 1, 1 ),-1);
    //circle (circleMask,Point((planes[0].cols & -2)/2, (planes[0].rows & -2)/2),50, Scalar( 1, 1, 1 ),-1);

//    int cx = circleMask.cols/2;
//    int cy = circleMask.rows/2;
//
//    Mat q0(circleMask, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
//    Mat q1(circleMask, Rect(cx, 0, cx, cy));  // Top-Right
//    Mat q2(circleMask, Rect(0, cy, cx, cy));  // Bottom-Left
//    Mat q3(circleMask, Rect(cx, cy, cx, cy)); // Bottom-Right
//
//    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
//    q0.copyTo(tmp);
//    q3.copyTo(q0);
//    tmp.copyTo(q3);
//
//    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
//    q2.copyTo(q1);
//    tmp.copyTo(q2);
//    Mat magI;
//    magnitude(planes[0], planes[1], magI);// planes[0] = magnitude
//
//
//    magI += Scalar::all(1);                    // switch to logarithmic scale
//    log(magI, magI);
//
//    // crop the spectrum, if it has an odd number of rows or columns
//    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
//    normalize(magI, magI, 0, 1, CV_MINMAX);
//
//    namedWindow( "b", CV_WINDOW_AUTOSIZE );
//    imshow("b", magI);
//    waitKey(0);








    for (int j=0; j<m; j++) {
    	for (int i=0; i<n; i++) {
//    		float u = (float)i/(n/2.)*PI;
//    		float v = (float)j/(m/2.)*PI;
//    		if (u>=PI) u=2.*PI-u;
//    		if (v>=PI) v=2.*PI-v;
    		float u = (float)(i-n/2);
    		float v = (float)(j-m/2);
    		//u2v2.at<float>(j,i) = 0.5*(u*u/n/n*4+v*v/m/m*4);
    		float d = (u*u+v*v);
    		if (sqrt(d)<100) u2v2.at<float>(j,i) = 1;
    		else u2v2.at<float>(j,i) = 0;
    	}
    }


//	planes[0]=planes[0].mul(circleMask);
//	planes[1]=planes[1].mul(circleMask);
	planes[0]=planes[0].mul(u2v2);
	planes[1]=planes[1].mul(u2v2);
	merge(planes, 2, complexI);


    Mat p0(complexI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat p1(complexI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat p2(complexI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat p3(complexI, Rect(cx, cy, cx, cy)); // Bottom-Right

//   Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    p0.copyTo(tmp);
    p3.copyTo(p0);
    tmp.copyTo(p3);

    p1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    p2.copyTo(p1);
    tmp.copyTo(p2);



	dft(complexI, complexI, DFT_INVERSE);
	split(complexI, planes);
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];

    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);

    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));




    // rearrange the quadrants of Fourier image  so that the origin is at the image center

    normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).
    namedWindow( "Input Image", CV_WINDOW_AUTOSIZE );
    imshow("Input Image"       , src   );    // Show the result
    namedWindow( "spectrum magnitude", CV_WINDOW_AUTOSIZE );
    imshow("spectrum magnitude", magI);
    namedWindow( "a", CV_WINDOW_AUTOSIZE );
    imshow("a", circleMask);
    namedWindow( "b", CV_WINDOW_AUTOSIZE );
    imshow("b", u2v2);
    waitKey(0);


}

}


