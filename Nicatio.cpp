#include <iostream>
#include "cv.h"
#include "highgui.h"
#include "nicatio/nica.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv ){

	int e;

	if (argv[1]==NULL) {

		cout<< "No image data1 \n" <<endl;
		return -1;
	}
	Mat _image, _image2, _image3;
	_image = imread( argv[1], -1 );

	if( argc != 2 || !_image.data )
	{
		cout<< "No image data2 \n" <<endl;
		return -1;
	}

	/*
	int dilation_size = 1;
	int dilation_type = MORPH_RECT;
	Mat element = getStructuringElement( dilation_type,
	                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
	                                       Point( dilation_size, dilation_size ) );
	dilate( _image,  _image2, element, Point(-1,-1),1);
	erode( _image2,  _image3, element, Point(-1,-1),1);
	 */
	//medianBlur(_image,_image2,3);
	GaussianBlur(_image,_image2,Size(3,3),0.0,0.0);

	int _srcType = _image.channels();

	e = _srcType;
	cout<<e<<endl;

	Size size =  _image.size();
	Mat _image4(size,CV_8UC3);
	Mat _image5(size,CV_8UC3);
	int sz = _image.cols*_image.rows;
	int iter=1;
	int sum=0;

		//nicatio::MorphColor(nicatio::Dilation,_image.data,_image4.data,_image.cols,_image.rows);
	nicatio::filter3x3Color(_image.data,_image4.data,_image.cols,_image.rows,NULL);


	for(int i=0; i < sz*3;i++){
		_image5.data[i] = abs(_image4.data[i] - _image2.data[i]);
		sum+=_image5.data[i];
	}

	double dfaf = nicatio::Lightness(_image.data,_image.cols,_image.rows,3);
	cout<<dfaf<<endl;

	cout<<sum<<endl;

//	namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	imshow( "a", _image4 );
//	namedWindow( "b", CV_WINDOW_AUTOSIZE );
//	imshow( "b", _image2 );
//	namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	imshow( "c", _image5 );

	Mat _image6(size,CV_8UC1);
	Mat _image7(size,CV_8UC1);
	Mat _image8(size,CV_8UC1);
	Mat _image9(size,CV_8UC1);
	Mat _image9_(size,CV_8UC1);
	Mat _image10(size,CV_8UC1);
	Mat _image10_(size,CV_8UC1);
	nicatio::Grayscale(_image.data,_image6.data,_image.cols,_image.rows);
	nicatio::Denoise(_image6.data,_image7.data,_image.cols,_image.rows);
	nicatio::DynamicClosing(_image7.data,_image8.data,_image.cols,_image.rows);
	for (int j=0;j<iter;j++){
		nicatio::DynamicMorphQuotImage(_image6.data,_image9_.data,_image.cols,_image.rows, 2);
		nicatio::DynamicMorphQuotImage_revision(_image6.data,_image9.data,_image.cols,_image.rows, 2);
		nicatio::Threshold(_image9.data,_image10.data,0,58,_image.cols,_image.rows,0xff,0x00);
		nicatio::Threshold(_image9_.data,_image10_.data,0,58,_image.cols,_image.rows,0xff,0x00);
		cout<<j<<endl;
	}

	namedWindow( "e", CV_WINDOW_AUTOSIZE );
	imshow( "e", _image9_ );
	namedWindow( "f", CV_WINDOW_AUTOSIZE );
	imshow( "f", _image10_ );
	namedWindow( "g", CV_WINDOW_AUTOSIZE );
	imshow( "g", _image9 );
	namedWindow( "h", CV_WINDOW_AUTOSIZE );
	imshow( "h", _image10 );
	waitKey(0);
	return e;
}
