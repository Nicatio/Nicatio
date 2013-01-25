#include <iostream>
#include "cv.h"
#include "highgui.h"
#include "nicatio/nica.h"
template <typename _T>
_T add (_T a, _T b){
	return a+b;
}
int main(int argc, char** argv ){

	int e;

	if (argv[1]==NULL) {

		std::cout<< "No image data1 \n" <<std::endl;
		return -1;
	}
	cv::Mat _image, _image2, _image3;
	_image = cv::imread( argv[1], -1 );

	if( argc != 2 || !_image.data )
	{
		std::cout<< "No image data2 \n" <<std::endl;
		return -1;
	}

/*
	int dilation_size = 1;
	int dilation_type = cv::MORPH_RECT;
	cv::Mat element = cv::getStructuringElement( dilation_type,
	                                       cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),
	                                       cv::Point( dilation_size, dilation_size ) );
	cv::dilate( _image,  _image2, element, cv::Point(-1,-1),1);
	cv::erode( _image2,  _image3, element, cv::Point(-1,-1),1);
*/
	//cv::medianBlur(_image,_image2,3);
	//cv::GaussianBlur(_image,_image2,cv::Size(3,3),0.0,0.0);

	int _srcType = _image.channels();

	e = _srcType;
	std::cout<<e<<std::endl;

	cv::Size size =  _image.size();
	cv::Mat _image4(size,CV_8UC3);
	cv::Mat _image5(size,CV_8UC3);
	int sz = _image.cols*_image.rows;
	int iter=1;
	double **yuv = new double*[3];
	yuv[0] = new double[sz];
	yuv[1] = new double[sz];
	yuv[2] = new double[sz];
	int sum=0;
	for (int j=0;j<iter;j++){
		//nicatio::MorphColor(nicatio::Dilation,_image.data,_image4.data,_image.cols,_image.rows);
		nicatio::filter3x3Color(_image.data,_image4.data,_image.cols,_image.rows,NULL);
	std::cout<<j<<std::endl;
	}
	for(int i=0; i < sz*3;i++){
		_image5.data[i] = abs(_image4.data[i] - _image2.data[i]);
		sum+=_image5.data[i];
	}
	std::cout<<sum<<std::endl;
	cv::namedWindow( "a", CV_WINDOW_AUTOSIZE );
	cv::imshow( "a", _image4 );
	cv::namedWindow( "b", CV_WINDOW_AUTOSIZE );
	cv::imshow( "b", _image2 );
	cv::namedWindow( "c", CV_WINDOW_AUTOSIZE );
	cv::imshow( "c", _image5 );

	cv::waitKey(0);
	return e;
}
