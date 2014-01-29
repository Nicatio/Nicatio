/*
 * FRID.cpp
 *
 *  Created on: 2014. 1. 20.
 *      Author: Nicatio
 */

#include "FRID.h"

using namespace cv;

namespace cvNica {

uint order_FRID16 [17][2] = {{0,0},{1,0},{2,0},{3,0},
								{4,0},{4,1},{4,2},{4,3},
								{4,4},{3,4},{2,4},{1,4},
								{0,4},{0,3},{0,2},{0,1},{2,2}};

uint order_FRID24 [25][2] = {{4,0},{5,0},{6,1},{7,1},
								{7,2},{8,3},{8,4},{8,5},
								{7,6},{7,7},{6,7},{5,8},
								{4,8},{3,8},{2,7},{1,7},
								{1,6},{0,5},{0,4},{0,3},
								{1,2},{1,1},{2,1},{3,0},{4,4}};

float order_FRID16F_sin [17] = {0, 0.382683432365090, 0.707106781186548, 0.923879532511287,
								1, 0.923879532511287, 0.707106781186548, 0.382683432365090,
								0, -0.382683432365089, -0.707106781186547, -0.923879532511287,
								-1, -0.923879532511287, -0.707106781186548, -0.382683432365090,0};

float order_FRID16F_cos [17] = {1, 0.923879532511287, 0.707106781186548, 0.382683432365090,
								0, -0.382683432365090, -0.707106781186548, -0.923879532511287,
								-1, -0.923879532511287, -0.707106781186548, -0.382683432365090,
								0, 0.382683432365089, 0.707106781186547, 0.923879532511287,0};

FRID::FRID(
		InputArray						src,
		int								type)
{

	uint _order=0;

	Mat _src = src.getMat();

	int w = _src.cols;
	int h = _src.rows;
	int sz;

	if (type == FRID_16)
		_order = 17;
	else if (type == FRID_24)
		_order = 25;
	else if (type == FRID_16F)
		_order = 17;
	else if (type == FRID_16F2)
			_order = 33;

	_type = type;

	//orderMap = new Mat[_order];

	if (type == FRID_16) {
		w4=w-4;
		h4=h-4;
		sz=w4*h4;
		for(uint i=0; i<_order; i++)
			Mat(_src, Rect(order_FRID16 [i][0], order_FRID16 [i][1], w4, h4)).copyTo(orderMap[i]);

	} else if (type == FRID_24) {
		w4=w-8;
		h4=h-8;
		sz=w4*h4;
		for(uint i=0; i<_order; i++)
			Mat(_src, Rect(order_FRID24 [i][0], order_FRID24 [i][1], w4, h4)).copyTo(orderMap[i]);
	} else if (type == FRID_16F) {
		w4=w-4;
		h4=h-4;
		sz=w4*h4;
		for(uint i=0; i<_order; i++) {

	    	Mat resampled;
			Mat affinematrix = (Mat_<float>(2,3) << 1, 0, order_FRID16F_cos[i]*7, 0, 1, order_FRID16F_sin[i]*7);// Mat(2,3,CV_32F,affinematrix_);
			warpAffine(_src, resampled, affinematrix, _src.size(), INTER_LINEAR);
			Mat(resampled, Rect(2, 2, w4, h4)).copyTo(orderMap[i]);
			stringstream d;
			d<<"br_"<<i<<".bmp";
			imwrite(d.str().c_str(),orderMap[i]);
		}
	} else if (type == FRID_16F2) {
		w4=w-4;
		h4=h-4;
		sz=w4*h4;
		for(uint i=0; i<16; i++) {

	    	Mat resampled;
			Mat affinematrix = (Mat_<float>(2,3) << 1, 0, order_FRID16F_cos[i]*7, 0, 1, order_FRID16F_sin[i]*7);// Mat(2,3,CV_32F,affinematrix_);
			warpAffine(_src, resampled, affinematrix, _src.size(), INTER_LINEAR);
			Mat(resampled, Rect(2, 2, w4, h4)).copyTo(orderMap[i]);
			//stringstream d;
			//d<<"br_"<<i<<".bmp";
			//imwrite(d.str().c_str(),orderMap[i]);
		}
		for(uint i=16; i<33; i++) {

			Mat resampled;
			Mat affinematrix = (Mat_<float>(2,3) << 1, 0, order_FRID16F_cos[i]*11, 0, 1, order_FRID16F_sin[i]*11);// Mat(2,3,CV_32F,affinematrix_);
			warpAffine(_src, resampled, affinematrix, _src.size(), INTER_LINEAR);
			Mat(resampled, Rect(2, 2, w4, h4)).copyTo(orderMap[i]);
			//stringstream d;
			//d<<"br_"<<i<<".bmp";
			//imwrite(d.str().c_str(),orderMap[i]);
		}
	}
}

Mat FRID::getFeatureVector(
		int								x,
		int								y,
		double&							phr,
		double&							phg,
		double&							phb,
		double&							sumr,
		double&							sumg,
		double&							sumb)
{
	int l=((y)*w4+(x));
//	Vec3b intensity = imageForFFT[16].at<Vec3b>(l);
//
//			cout<<"a: "<<(uint)intensity.val[0]<<"a: "<<(uint)intensity.val[1]<<"a: "<<(uint)intensity.val[2]<<endl;


	uint _order=0;
	if (_type == FRID_16)
		_order = 16;
	else if (_type == FRID_24)
		_order = 32;
	else if (_type == FRID_16F)
		_order = 16;
	else if (_type == FRID_16F2)
		_order = 32;
		//_order = 24;


	if(_type != FRID_16F2) {
		Vec3b intensity;
		nicatio::cplx *bufr = new nicatio::cplx[_order];
		nicatio::cplx *bufg = new nicatio::cplx[_order];
		nicatio::cplx *bufb = new nicatio::cplx[_order];

		for(uint m=0;m<_order;m++) {
		//for(uint m=0;m<24;m++) {
			intensity = orderMap[m].at<Vec3b>(l);
			bufr[m]=intensity.val[0];
			bufg[m]=intensity.val[1];
			bufb[m]=intensity.val[2];
		}
	//	for(uint m=24;m<_order;m++) {
	//		bufr[m]=0;
	//		bufg[m]=0;
	//		bufb[m]=0;
	//	}

		nicatio::fft(bufr, _order);
		nicatio::fft(bufg, _order);
		nicatio::fft(bufb, _order);

		phr = atan2(cimag(bufr[1]),creal(bufr[1]));
		phg = atan2(cimag(bufg[1]),creal(bufg[1]));
		phb = atan2(cimag(bufb[1]),creal(bufb[1]));
		sumr = cabsf(bufr[0]);
		sumg = cabsf(bufr[0]);
		sumb = cabsf(bufr[0]);

		float *bufABS = new float[(int)((_order/2-1)*3)+3];

		int n=0;

		for (int m=1; m<_order/2; m++){
			bufABS[n++] = cabsf(bufr[m]);
			bufABS[n++] = cabsf(bufg[m]);
			bufABS[n++] = cabsf(bufb[m]);
		}
		intensity = orderMap[_order].at<Vec3b>(l);
		//intensity = orderMap[24].at<Vec3b>(l);
		bufABS[n++] = intensity.val[0];
		bufABS[n++] = intensity.val[1];
		bufABS[n++] = intensity.val[2];

		Mat bufABSmat ((_order/2-1)*3+3,1,CV_32FC1,bufABS);
		delete [] bufr;
		delete [] bufg;
		delete [] bufb;
		delete [] bufABS;
		return bufABSmat;
	} else {
		Vec3b intensity;
		nicatio::cplx *bufr1 = new nicatio::cplx[16];
		nicatio::cplx *bufg1 = new nicatio::cplx[16];
		nicatio::cplx *bufb1 = new nicatio::cplx[16];
		nicatio::cplx *bufr2 = new nicatio::cplx[16];
		nicatio::cplx *bufg2 = new nicatio::cplx[16];
		nicatio::cplx *bufb2 = new nicatio::cplx[16];

		for(uint m=0;m<16;m++) {
			intensity = orderMap[m].at<Vec3b>(l);
			bufr1[m]=intensity.val[0];
			bufg1[m]=intensity.val[1];
			bufb1[m]=intensity.val[2];
		}
		for(uint m=16;m<32;m++) {
			intensity = orderMap[m].at<Vec3b>(l);
			bufr2[m]=intensity.val[0];
			bufg2[m]=intensity.val[1];
			bufb2[m]=intensity.val[2];
		}

		nicatio::fft(bufr1, 16);
		nicatio::fft(bufg1, 16);
		nicatio::fft(bufb1, 16);
		nicatio::fft(bufr2, 16);
		nicatio::fft(bufg2, 16);
		nicatio::fft(bufb2, 16);

		phr = atan2(cimag(bufr1[1]),creal(bufr1[1]));
		phg = atan2(cimag(bufg1[1]),creal(bufg1[1]));
		phb = atan2(cimag(bufb1[1]),creal(bufb1[1]));
		sumr = cabsf(bufr1[0]);
		sumg = cabsf(bufr1[0]);
		sumb = cabsf(bufr1[0]);

		float *bufABS = new float[(int)((_order/2-1)*3)+3];

		int n=0;

		for (int m=1; m<8; m++){
			bufABS[n++] = cabsf(bufr1[m]);
			bufABS[n++] = cabsf(bufg1[m]);
			bufABS[n++] = cabsf(bufb1[m]);
		}
		for (int m=1; m<8; m++){
			bufABS[n++] = cabsf(bufr2[m]);
			bufABS[n++] = cabsf(bufg2[m]);
			bufABS[n++] = cabsf(bufb2[m]);
		}
		intensity = orderMap[_order].at<Vec3b>(l);
		//intensity = orderMap[24].at<Vec3b>(l);
		bufABS[n++] = intensity.val[0];
		bufABS[n++] = intensity.val[1];
		bufABS[n++] = intensity.val[2];

		Mat bufABSmat ((_order/2-1)*3+3,1,CV_32FC1,bufABS);
		delete [] bufr1;
		delete [] bufg1;
		delete [] bufb1;
		delete [] bufr2;
		delete [] bufg2;
		delete [] bufb2;
		delete [] bufABS;
		return bufABSmat;
	}

}

}



