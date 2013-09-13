/*
 * dmqi.cpp
 *
 *  Created on: 2013. 1. 28.
 *      Author: Nicatio
 */

#include "cvdmqi.h"

namespace cvNica {

void lineHistEqualize(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();
	int cols = src.cols;
	for (int i=0; i<cols; i++){
		equalizeHist(src.col(i),dst.col(i));
	}
}

void lineHistEqualize2(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Mat rowHistEqResult = Mat(src.size(),src.type());
	Mat colHistEqResult = Mat(src.size(),src.type());

//	double *rowMin = new double[src.rows];
//	double *rowMax = new double[src.rows];
//	double *colMin = new double[src.cols];
//	double *colMax = new double[src.cols];
	double *rowDiff = new double[src.rows];
	double *colDiff = new double[src.cols];

	double *ptrRowDiff = rowDiff;
	double *ptrColDiff = colDiff;

	unsigned char *ptrSrc = src.data;
	unsigned char *ptrDst = dst.data;
	unsigned char *ptrColHistEqResult = colHistEqResult.data;
	unsigned char *ptrRowHistEqResult = rowHistEqResult.data;

	int cols = src.cols;
	int rows = src.rows;
	int sz = cols*rows;
	int gamma = 2;
	for (int i=0; i<cols; i++,ptrColDiff++){
		double _min,_max;
		Mat temp = src.col(i);
		minMaxLoc(temp,&_min,&_max);
		*(ptrColDiff) = _max - _min;
		equalizeHist(temp,colHistEqResult.col(i));

	}
	for (int i=0; i<rows; i++,ptrRowDiff++){
		double _min,_max;
		Mat temp = src.row(i);
		minMaxLoc(temp,&_min,&_max);
		*(ptrRowDiff) = _max - _min;
		equalizeHist(temp,rowHistEqResult.row(i));
	}

	ptrRowDiff = rowDiff-1;
	ptrColDiff = colDiff;

	for (int i=0; i<sz; i++,ptrDst++,ptrColHistEqResult++,ptrRowHistEqResult++,ptrColDiff++){
		if(i%cols==0) {
			ptrColDiff = colDiff;
			ptrRowDiff++;
		}
		double a = *(ptrColDiff);
		double b = *(ptrRowDiff);
		*(ptrDst) =  (*(ptrColHistEqResult) * a + *(ptrRowHistEqResult) * b + *(ptrSrc))/(a+b+1);
		//*(ptrDst) =  (*(ptrColHistEqResult) * (a) + *(ptrSrc))/(a+255);
		//*(ptrDst) =  (*(ptrColHistEqResult) > *(ptrRowHistEqResult)) ? *(ptrRowHistEqResult) : *(ptrColHistEqResult);
	}
	delete [] rowDiff;
	delete [] colDiff;

}

void Reflectance_re(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst)
{
	Mat deno = _deno.getMat();
	Mat closedeno = _closedeno.getMat();
	namedWindow( "a", CV_WINDOW_AUTOSIZE );
	imshow( "a", closedeno );
	waitKey(0);
	deno.convertTo(deno, CV_32F);
	closedeno.convertTo(closedeno, CV_32F, 1);

	deno /= closedeno;
	deno*=255.0;
	deno.convertTo(_dst,CV_8UC1);
//	namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	imshow( "a", _dst );
//	waitKey(0);
}


void SelectiveClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha,
		const double&					beta)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Mat l = Mat(src.size(),src.type());
	//Mat m = Mat(src.size(),src.type());
	Mat s = Mat(src.size(),src.type());
	//Mat ss = Mat(src.size(),src.type());

	Mat _l = Mat(src.size(),src.type());
	//Mat _m = Mat(src.size(),src.type());
	Mat _s = Mat(src.size(),src.type());
	//Mat _ss = Mat(src.size(),src.type());

	int dilation_type = MORPH_RECT;
	Mat elementL = getStructuringElement( dilation_type, Size( 9,9 ), Point( 4,4 ) );
	//Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
	Mat elementS = getStructuringElement( dilation_type, Size( 5,5 ), Point( 2,2 ) );
	//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

	dilate( src, l, elementL);
	//dilate( src, m, elementM);
	dilate( src, s, elementS);
	//dilate( src, ss, elementSS);
	erode( l, _l, elementL);
	//erode( m, _m, elementM);
	erode( s, _s, elementS);
	//erode( ss, _ss, elementSS);

	//unsigned char *ptrL = _l.data, *ptrM = _m.data, *ptrS = _s.data, *ptrSS = _ss.data;
	unsigned char *ptrL = _l.data, *ptrS = _s.data;
	unsigned char *ptrDst = dst.data;
	unsigned char *ptrSrc = src.data;

	int sz = _src.total();

	//for (int i=0; i<sz; i++,ptrL++,ptrM++,ptrS++,ptrSS++,ptrDst++,ptrSrc++){
	for (int i=0; i<sz; i++,ptrL++,ptrS++,ptrDst++,ptrSrc++){
		double __l = (double)*(ptrL);
		//double __m = (double)*(ptrM);
		double __s = (double)*(ptrS);
		//double __ss = (double)*(ptrSS);
		//double _sb = __s*1.4;//beta;
		double _sa = __s*1.4;//alpha;
		//double _sc = __s*1.4;
//		if(__l>_sa) *(ptrDst) = __l;
//		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = __m;
//		else if((__l>_sc)&&(__l<=_sb)) *(ptrDst) = __s;
//		else *(ptrDst) = __ss;


//		if(__l>_sa) *(ptrDst) = __l;
//		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = __m;
//		else if((__l>_sc)&&(__l<=_sb)) *(ptrDst) = __s;
//		else *(ptrDst) = *(ptrSrc);
//		if(__l>_sa) *(ptrDst) = 0x00;
//		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = 0x50;
//		else if((__l>_sc)&&(__l<=_sb)) *(ptrDst) = 0xa0;
//		else *(ptrDst) = 0xf0;
		if(__l>_sa) *(ptrDst) = __l;
		//else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = __m;
		else *(ptrDst) = __s;
/*		if(__l>_sa) *(ptrDst) = 0x00;
		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = 0x80;
		else *(ptrDst) = 0xff;*/
	}


}

void NormDynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	DynamicClosing (src,dc);
	int sz = src.cols*src.rows;
	Mat _ddd,rep,dst,ddd;
	Reflectance_re(src,dc,_ddd);
	namedWindow( "b", CV_WINDOW_AUTOSIZE );
	imshow( "b", _ddd );

	Mat resultAbs,resultPow;
	Mat resultExpP,resultExpM;
	double a = 0.1, mean1, mean2, min_, max_;
	double do_norm = 10.0;
	double trim = abs(do_norm), oneOverTrim=1/trim;
	_ddd.convertTo(ddd,CV_32FC1);
	absdiff(ddd, Scalar::all(0), resultAbs);
	pow(resultAbs,a,resultPow);
	mean1 = sum(resultPow)[0]/sz;
	mean1 = 1/pow(mean1,(1.0/a));

	ddd*=mean1;

	absdiff(ddd, Scalar::all(0), resultAbs);
	min(resultAbs,trim,resultAbs);
	pow(resultAbs,a,resultPow);
	mean2 = sum(resultPow)[0]/sz;
	mean2 = 1/pow(mean2,(1.0/a));

	exp(ddd*mean2*oneOverTrim,resultExpP);
	exp(-ddd*mean2*oneOverTrim,resultExpM);

	divide((resultExpP - resultExpM),(resultExpP + resultExpM),ddd);

	ddd *= trim;
	minMaxLoc(ddd,&min_,&max_);


	max_ = 255/(max_-min_);

	ddd-=min_;
	ddd*=max_;
	ddd.convertTo(rep,src.type());

	_dst.create(src.size(),src.type());
	dst = _dst.getMat();

	rep.copyTo(dst);
	namedWindow( "a", CV_WINDOW_AUTOSIZE );
	imshow( "a", dst );
	waitKey(0);

}

void GaussianMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	Mat src2;
	src.convertTo(src,CV_32F);
	GaussianBlur(src,src2,Size(3,3),1.0);
	DynamicClosing (src2,dc);
	Mat dst;
	Reflectance_re(src2,dc,dst);
	dst.convertTo(_dst,CV_8UC1);




}

void SelectiveMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	SelectiveClosing (src,dc);
	Reflectance(src,dc,_dst);

}

void DynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	DynamicClosing (src,dc);
	//imwrite("dc.bmp",dc);
	Reflectance(src,dc,_dst,200);

}

void Reflectance(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst,
		double							scale)
{

	Mat deno = _deno.getMat();
	Mat closedeno = _closedeno.getMat();

	deno.convertTo(deno, CV_32F);
	closedeno.convertTo(closedeno, CV_32F, 1);

	deno /= closedeno;
	deno*=scale;
	deno.convertTo(_dst,CV_8UC1);
}

void Denoise(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Mat d = Mat(src.size(),src.type());
	Mat e = Mat(src.size(),src.type());

	//Mat element = getStructuringElement( MORPH_RECT, Size( 3,3 ), Point( 1,1 ) ); element. element.data[0]=0; element.data[1]=0;// element.at<uchar>(1,1) = 0;
	uchar _element [3][3] = {{1,1,1},{1,0,1},{1,1,1}};
	Mat element(3,3,CV_8U, _element);

	dilate( src, d, element);
	erode ( src, e, element);

	unsigned char *ptrD = d.data, *ptrE = e.data;
	unsigned char *ptrSrc = src.data;
	unsigned char *ptrDst = dst.data;

	int sz = src.rows*src.cols;

	for (int i=0; i<sz; i++,ptrD++,ptrE++,ptrSrc++,ptrDst++){
		unsigned char __d = *(ptrD);
		unsigned char __e = *(ptrE);
		unsigned char __src = *(ptrSrc);

		if 		(__d<__src)	*(ptrDst) = __d;
		else if (__e>__src) *(ptrDst) = __e;
		else 				*(ptrDst) = __src;
	}
}

void DynamicClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha,
		const double&					beta)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Mat l = Mat(src.size(),src.type());
	Mat m = Mat(src.size(),src.type());
	Mat s = Mat(src.size(),src.type());

	Mat _l = Mat(src.size(),src.type());
	Mat _m = Mat(src.size(),src.type());
	Mat _s = Mat(src.size(),src.type());

	int dilation_type = MORPH_RECT;
	Mat elementL = getStructuringElement( dilation_type, Size( 9,9 ), Point( 4,4 ) );
	Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
	Mat elementS = getStructuringElement( dilation_type, Size( 5,5 ), Point( 2,2 ) );

	dilate( src, l, elementL);
	dilate( src, m, elementM);
	dilate( src, s, elementS);
	erode( l, _l, elementL);
	erode( m, _m, elementM);
	erode( s, _s, elementS);

	unsigned char *ptrL = _l.data, *ptrM = _m.data, *ptrS = _s.data;
	unsigned char *ptrDst = dst.data;

	imwrite("l.bmp",_l);
	imwrite("m.bmp",_m);
	imwrite("s.bmp",_s);

	int sz = _src.total();

	for (int i=0; i<sz; i++,ptrL++,ptrM++,ptrS++,ptrDst++){
		double __l = (double)*(ptrL);
		double __m = (double)*(ptrM);
		double __s = (double)*(ptrS);
		double _sb = __s*beta;
		double _sa = __s*alpha;
		if(__l>_sa) *(ptrDst) = __l;
		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = __m;
		else *(ptrDst) = __s;
//		if(__l>_sa) *(ptrDst) = 0x00;
//		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = 0x80;
//		else *(ptrDst) = 0xff;
	}


}

void RemoveGrainyNoise(
		InputArray 						_src,
		OutputArray						_dst,
		int								threshold)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Mat d = Mat(src.size(),src.type());
	Mat e = Mat(src.size(),src.type());

	Mat element = getStructuringElement( MORPH_RECT, Size( 3,3 ), Point( 1,1 ) );
	dilate( src, d, element);
	erode ( src, e, element);

	unsigned char *ptrD = d.data, *ptrE = e.data;
	unsigned char *ptrSrc = src.data;
	unsigned char *ptrDst = dst.data;

	int sz = src.rows*src.cols;

	for (int i=0; i<sz; i++,ptrD++,ptrE++,ptrSrc++,ptrDst++){
		unsigned char __d = *(ptrD);
		unsigned char __e = *(ptrE);
		unsigned char __src = *(ptrSrc);
		if (__d != __e) {
			int a = ((int)__d - (int)__e);
			if (a<0) a = -a;
			if (a<threshold) {
				*(ptrDst) = __d;
			} else {
				*(ptrDst) = __src;
			}
		} else {
			*(ptrDst) = __src;
		}
//		if 		(__d>__src)	*(ptrDst) = __d;
//		else if (__e<__src) *(ptrDst) = __e;
//		else 				*(ptrDst) = __src;
	}
}

}


