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



void DynamicMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	DynamicClosing (src,dc);
	Reflectance(src,dc,_dst);

}

void Reflectance(
		InputArray 						_deno,
		InputArray						_closedeno,
		OutputArray						_dst)
{

	Mat deno = _deno.getMat();
	Mat closedeno = _closedeno.getMat();
	deno.convertTo(deno, CV_32F);
	closedeno.convertTo(closedeno, CV_32F, 1,0.0001);
	deno /= closedeno;
	deno*=255.0;
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

		if 		(__d>__src)	*(ptrDst) = __d;
		else if (__e<__src) *(ptrDst) = __e;
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

}


