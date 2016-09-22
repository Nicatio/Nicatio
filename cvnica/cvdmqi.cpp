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
	Mat elementS = getStructuringElement( dilation_type, Size( 5,5), Point( 2,2 ) );
	//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

	dilate( src, l, elementL);
	//dilate( src, m, elementM);
	dilate( src, s, elementS);
	//dilate( src, ss, elementSS);
	erode( l, _l, elementL);
	//erode( m, _m, elementM);
	erode( s, _s, elementS);
	//erode( ss, _ss, elementSS);


	//GaussianBlur(src, _s, Size(9,9), 1.0, 1.0, BORDER_DEFAULT);

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

//	imwrite("k1.bmp",src);
//	imwrite("k5.bmp",_s);
//	imwrite("k9.bmp",_l);
//	imwrite("kk.bmp",dst);
}

void ContinuousClosing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha,
		const double&					k,
		const int&						small,
		const int&						large)
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
	//int dilation_type = MORPH_ELLIPSE;
	int small_ = (small-1)/2;
	int large_ = (large-1)/2;
	Mat elementL = getStructuringElement( dilation_type, Size( large,large), Point( large_,large_ ) );
	//Mat elementL = getStructuringElement( dilation_type, Size( 9,9), Point( 4,4 ) );
	//Mat elementL = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
	Mat elementS = getStructuringElement( dilation_type, Size( small,small), Point( small_,small_ ) );
	//Mat elementS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

	dilate( src, l, elementL);
	//dilate( src, m, elementM);
	dilate( src, s, elementS);
	//dilate( src, ss, elementSS);
	erode( l, _l, elementL);
	//erode( m, _m, elementM);
	erode( s, _s, elementS);
	//erode( ss, _ss, elementSS);


	//GaussianBlur(src, _s, Size(9,9), 1.0, 1.0, BORDER_DEFAULT);

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
		double _sa = __l/__s;//alpha;
//		_sa = 1./(1+exp(-20*(_sa-1.5))); //cmqi2 and cmqi3 (1.4 condition)
		//_sa = 1./(1+exp(-20*(_sa-1.4)));//2363
//		_sa = 1./(1+exp(-20*(_sa-1.3)));//2369
		//_sa = 1./(1+exp(-20*(_sa-1.25)));//2371
		//std::cout<<"t "<<_sa<<" ";
		_sa = 1./(1+exp(-k*(_sa-alpha)));//2371

		//_sa = 1./pow((1+exp(-20*(_sa-1.5))),0.9);
		//_sa = 1./(1+exp(-50*(_sa-1.3)));
		//_sa = (__s*(alpha)*(1-_sa)+__l*_sa);
		//if (_sa>255)_sa=255;
		*(ptrDst) = (unsigned char) (__s*(1-_sa)+__l*_sa);
		//std::cout<<"t "<<_sa<<" "<<*(ptrDst)<<std::endl;

//		*(ptrDst) = (unsigned char) __l;

//		*(ptrDst) = (unsigned char) floor((__l/__s-1)*255);
//		if (((__l/__s-1)*255)>255) *(ptrDst) = 255;

		//if (((__l/__s-1)*255)<0) *(ptrDst) = 0;
//		if ((i/168+1 == 52) && ((i%168)+1==9)){
//			std::cout<<"t "<<i/168+1<<" "<<(i%168)+1<<" "<<__l<<" "<<__s<<" "<<(__l/__s)<<" "<<((__l/__s-1)*255)<<" "<<(int)((unsigned char)((__l/__s-1)*255))<<" "<<(int)*(ptrDst)<<std::endl;
//		}

//		if ((__l/__s)>2) {
//			std::cout<<"t "<<i/168+1<<" "<<(i%168)+1<<__l<<" "<<__s<<" "<<(__l/__s)<<std::endl;
//		}
		//_sa = __s*1.4;//alpha;

		//if(__l>_sa) *(ptrDst) = __l;
		//else *(ptrDst) = __s;


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
//		if(__l>_sa) *(ptrDst) = __l;
		//else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = __m;
//		else *(ptrDst) = __s;
/*		if(__l>_sa) *(ptrDst) = 0x00;
		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = 0x80;
		else *(ptrDst) = 0xff;*/
	}

//	imwrite("k1.bmp",src);
//	imwrite("k5.bmp",_s);
//	imwrite("k9.bmp",_l);
//	imwrite("kk.bmp",dst);
}

void Closing(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					strE)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	Mat l = Mat(src.size(),src.type());
	Mat _l = Mat(src.size(),src.type());
	//int dilation_type = MORPH_RECT;
	int dilation_type = MORPH_ELLIPSE;
	Mat elementL = getStructuringElement( dilation_type, Size( strE,strE ), Point( floor(strE/2), floor(strE/2) ) );

	dilate( src, l, elementL);
	erode( l, _l, elementL);

	unsigned char *ptrL = _l.data;
	unsigned char *ptrDst = dst.data;
	unsigned char *ptrSrc = src.data;

	int sz = _src.total();
	for (int i=0; i<sz; i++,ptrL++,ptrDst++){
		*(ptrDst) = (double)*(ptrL);
	}
}

void AdaptiveClosing(
		InputArray 						_src,
		OutputArray						_dst,
		double							percent)
{
	Mat src = _src.getMat();
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();

	int sz = _src.total();

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
	Mat elementS = getStructuringElement( dilation_type, Size( 5,5), Point( 2,2 ) );
	//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

	dilate( src, l, elementL);
	//dilate( src, m, elementM);
	dilate( src, s, elementS);
	//dilate( src, ss, elementSS);
	erode( l, _l, elementL);
	//erode( m, _m, elementM);
	erode( s, _s, elementS);
	//erode( ss, _ss, elementSS);

	Mat __div = Mat(src.size(),CV_32FC1);

	//unsigned char *ptrL = _l.data, *ptrM = _m.data, *ptrS = _s.data, *ptrSS = _ss.data;
	unsigned char *ptrL = _l.data, *ptrS = _s.data;
	unsigned char *ptrDst = dst.data;
	unsigned char *ptrSrc = src.data;


	for (int i=0; i<src.rows; i++){
		for (int j=0; j<src.cols; j++,ptrL++,ptrS++){
			double __l = (double)*(ptrL);
			double __s = (double)*(ptrS);
			float div;
			if (__s==0)
				div = 1;
			else
				div = __l/__s;
			__div.at<float>(i,j) = div;
			//std::cout<<div;
		}
	}

	double minVal;
	double maxVal;

	minMaxIdx(__div,&minVal,&maxVal);

	ptrL = _l.data;
	ptrS = _s.data;
	for (int i=0; i<src.rows; i++){
		for (int j=0; j<src.cols; j++,ptrL++,ptrS++){
			double __l = (double)*(ptrL);
			double __s = (double)*(ptrS);
			if (__s==0 && __l>0)
				__div.at<float>(i,j) = maxVal;
		}
	}

	Mat __div2;
	__div = __div.reshape(0,1);
	sort(__div,__div2,CV_SORT_DESCENDING);
	int splitInd = __div2.cols*percent;
	double newalpha = __div2.at<float>(0,splitInd);

	//std::cout<<minVal<<" "<<maxVal<<" "<<__div2.rows<<" "<<__div2.cols<<" "<<splitInd<<" "<<newalpha<<std::endl;
	//for (int i=0; i<sz; i++,ptrL++,ptrM++,ptrS++,ptrSS++,ptrDst++,ptrSrc++){
	ptrL = _l.data;
	ptrS = _s.data;
	for (int i=0; i<sz; i++,ptrL++,ptrS++,ptrDst++,ptrSrc++){
		double __l = (double)*(ptrL);
		//double __m = (double)*(ptrM);
		double __s = (double)*(ptrS);
		//double __ss = (double)*(ptrSS);
		//double _sb = __s*1.4;//beta;
		double _sa = __s*newalpha;//alpha;
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
		if(__l>_sa) *(ptrDst) = 0xff;//__l;
		//else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = __m;
		else *(ptrDst) = 0x00;//__s;
/*		if(__l>_sa) *(ptrDst) = 0x00;
		else if((__l>_sb)&&(__l<=_sa)) *(ptrDst) = 0x80;
		else *(ptrDst) = 0xff;*/
	}

//	imwrite("k1.bmp",src);
//	imwrite("k5.bmp",_s);
//	imwrite("k9.bmp",_l);
//	imwrite("kk.bmp",dst);
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

void ContinuousMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					alpha,
		const double&					k,
		const int&						small,
		const int&						large,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	ContinuousClosing (src,dc,alpha,k,small,large);
	Reflectance(src,dc,_dst);

}

void MorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		const double&					strE)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	Closing (src,dc,strE);
	Reflectance(src,dc,_dst);
}

void AdaptiveMorphQuotImage(
		InputArray 						_src,
		OutputArray						_dst,
		double							percent,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	AdaptiveClosing (src,_dst,percent);
	//AdaptiveClosing (src,dc,percent);
	//Reflectance(src,dc,_dst);

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

//	imwrite("l.bmp",_l);
//	imwrite("m.bmp",_m);
//	imwrite("s.bmp",_s);

	int sz = _src.total();
	std::cout<<alpha<<beta<<std::endl;
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
	Mat dst =  _dst.getMat();
	Mat k(src.rows + 2, src.cols + 2, src.depth());
	copyMakeBorder(src,k,1,1,1,1,BORDER_REPLICATE);
	int i,j;
	int r = src.rows;
	int c = src.cols;
	double mx;
	Rect roi1 (0,0,8,1);
	Rect roi2 (1,0,8,1);

	for (j=0; j<r; j++){
		for (i=0; i<c; i++){
			Rect roi (i,j,3,3);
			Mat partial = k(roi).clone().reshape(0,1);
			sort(partial,partial,CV_SORT_DESCENDING);
			Mat p1 = partial(roi1);
			Mat p2 = partial(roi2);
			Mat p3 = p1-p2;
			minMaxLoc(p3,NULL,&mx);
			if (mx<threshold && mx>0) {
				minMaxLoc(partial,NULL,&mx);
				dst.at<uchar>(j,i) = (uchar)mx;
			} else
				dst.at<uchar>(j,i) = src.at<uchar>(j,i);
		}
	}

}

void RemoveGrainyNoise_old(
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



void SelectiveClosingParam(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						large,
		const int&						small,
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

	int large2 = large/2;
	int small2 = small/2;

	int dilation_type = MORPH_RECT;
	Mat elementL = getStructuringElement( dilation_type, Size( large,large ), Point( large2,large2 ) );
	//Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
	Mat elementS = getStructuringElement( dilation_type, Size( small,small ), Point( small2,small2 ) );
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
		double _sa = __s*alpha;
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


void SelectiveMorphQuotImageParam(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						large,
		const int&						small,
		const double&					alpha,
		const int&						equalize)
{
	Mat src = _src.getMat();
	Mat dc = Mat(src.size(),src.type());
	SelectiveClosingParam(src,dc,large,small,alpha);
	Reflectance(src,dc,_dst);
	//dc.convertTo(_dst,CV_8UC1);

}

}


