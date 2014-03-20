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
		//w4=w-4;
		//h4=h-4;
		w4=w;
		h4=h;
		sz=w4*h4;
		for(uint i=0; i<_order; i++) {

	    	Mat resampled;
			Mat affinematrix = (Mat_<float>(2,3) << 1, 0, order_FRID16F_cos[i]*7, 0, 1, order_FRID16F_sin[i]*7);// Mat(2,3,CV_32F,affinematrix_);
			//warpAffine(_src, resampled, affinematrix, _src.size(), INTER_LINEAR);
			warpAffine(_src, orderMap[i], affinematrix, _src.size(), INTER_LINEAR);
			//Mat(resampled, Rect(2, 2, w4, h4)).copyTo(orderMap[i]);

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
			Mat affinematrix = (Mat_<float>(2,3) << 1, 0, order_FRID16F_cos[i]*3, 0, 1, order_FRID16F_sin[i]*3);// Mat(2,3,CV_32F,affinematrix_);
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

int FRID::getOrder() {
	if (_type == FRID_16)
		return 16;
	else if (_type == FRID_24)
		return 32;
	else if (_type == FRID_16F)
		return 16;
	else if (_type == FRID_16F2)
		return 32;
}

float* FRID::getFeatureVector(
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


	uint _order = getOrder();
//	if (_type == FRID_16)
//		_order = 16;
//	else if (_type == FRID_24)
//		_order = 32;
//	else if (_type == FRID_16F)
//		_order = 16;
//	else if (_type == FRID_16F2)
//		_order = 32;
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

//		cout<<" "<<bufABS[0]<<" "
//				<<bufABS[1]<<" "
//				<<bufABS[2]<<" "
//				<<bufABS[3]<<" "
//				<<bufABS[4]<<" "
//				<<bufABS[5]<<" "
//				<<bufABS[6]<<" "
//				<<bufABS[7]<<" "
//				<<bufABS[8]<<" "
//				<<bufABS[9]<<" "<<endl;

		Mat bufABSmat ((_order/2-1)*3+3,1,CV_32FC1,bufABS);


//		cout<<(float)bufABSmat.at<float>(0)<<" "
//				<<(float)bufABSmat.at<float>(1)<<" "
//				<<(float)bufABSmat.at<float>(2)<<" "
//				<<(float)bufABSmat.at<float>(3)<<" "
//				<<(float)bufABSmat.at<float>(4)<<" "
//				<<(float)bufABSmat.at<float>(5)<<" "
//				<<(float)bufABSmat.at<float>(6)<<" "
//				<<(float)bufABSmat.at<float>(7)<<" "
//				<<(float)bufABSmat.at<float>(8)<<" "
//				<<(float)bufABSmat.at<float>(9)<<" "<<endl;

		delete [] bufr;
		delete [] bufg;
		delete [] bufb;
		//delete [] bufABS;
		return bufABS;
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



		delete [] bufr1;
		delete [] bufg1;
		delete [] bufb1;
		delete [] bufr2;
		delete [] bufg2;
		delete [] bufb2;
		//delete [] bufABS;
		return bufABS;
	}

}

vector<int> FRID::getFeaturePoints()
{
	int i,j;
	vector<int> r;
	uint _order = getOrder();
	int sz=w4*h4;
	Mat sobelx, gradx, sobely,grady,sobel;
	Mat sobelgray_,sobelgray__,sobelgray;
	int totalPoints;


	Sobel(orderMap[_order],sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
	convertScaleAbs( sobelx, gradx );
	Sobel(orderMap[_order],sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
	convertScaleAbs( sobely, grady );
	addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );

	cvtColor(sobel,sobelgray_,CV_RGB2GRAY);
	sobelgray_.convertTo(sobelgray__,CV_8UC1);

	double min,max;
	int maxid[2];
	minMaxIdx(sobelgray__,&min,&max,0,maxid);

	threshold(sobelgray__,sobelgray__,(int)(((float)max)/255*100),1,THRESH_BINARY);

	totalPoints = sum(sobelgray__)[0];

	cout<<"max: "<<max<<endl;
	cout<<"totalPoints: "<<totalPoints<<endl;

	double br;
	double bg;
	double bb;
	double bsr;
	double bsg;
	double bsb;
	int xmin,xmax,ymin,ymax;
	//Mat bufABSmat;
	//Mat bufABS2mat;
	Mat result1;
	Mat cdmat;
	orderMap[_order].copyTo(cdmat);

	for (i=0; i<sz; i++){
		if (sobelgray__.at<uchar>(i/w4,i%w4) == 0) continue;
		float* bufABS = getFeatureVector(i%w4,i/w4,br,bg,bb,bsr,bsg,bsb);
		Mat bufABSmat ((_order/2-1)*3+3,1,CV_32FC1,bufABS);
				//bufABSmat;
		Mat corImg = Mat::zeros(Size(w4,h4),CV_8UC1);
		xmin=w4-1,xmax=0,ymin=h4-1,ymax=0;
		for (j=0; j<sz; j++){
			if (sobelgray__.at<uchar>(j/w4,j%w4) == 0) continue;
			float* bufABS2 = getFeatureVector(j%w4,j/w4,br,bg,bb,bsr,bsg,bsb);
			Mat bufABS2mat ((_order/2-1)*3+3,1,CV_32FC1,bufABS2);
			matchTemplate(bufABSmat, bufABS2mat, result1, CV_TM_CCOEFF_NORMED);

			if (bsr>255 && bsg>255 && bsb>255 && pow(result1.at<float>(0),3)>0.5)  {
				if (xmin > j%w4) xmin = j%w4;
				if (xmax < j%w4) xmax = j%w4;
				if (ymin > j/w4) ymin = j/w4;
				if (ymax < j/w4) ymax = j/w4;
				corImg.at<uchar>(j) = 1;//(result1.at<float>(0) > 0)? pow(result1.at<float>(0),10):0;
				if ((xmax-xmin)>6 && (ymax-ymin)>6)break;
			}
		}
//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", corImg*255);//thrCrCb[0] );
//
//		waitKey(0);

		if ((xmax-xmin)<=6 && (ymax-ymin)<=6) {
			cout<<"xy: "<<i%w4<<", "<<i/w4<<endl;
			cout<<"totalPoints: "<<sum(sobelgray__)[0]<<endl;
			circle( cdmat, Point(i%w4,i/w4), 1, Scalar( 0, 0, 255 ), -1, 8 );
			r.push_back(i%w4);
			r.push_back(i/w4);
		}
		//sobelgray__=sobelgray__-corImg;

	}



	//circle( cdmat, Point(maxid[1],maxid[0]), 1, Scalar( 0, 0, 255 ), -1, 8 );





	return r;
}

}



