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
	for (int j=0;j<iter;j++){
		//nicatio::MorphColor(nicatio::Dilation,_image.data,_image4.data,_image.cols,_image.rows);
		nicatio::filter3x3Color(_image.data,_image4.data,_image.cols,_image.rows,NULL);
		cout<<j<<endl;
	}
	for(int i=0; i < sz*3;i++){
		_image5.data[i] = abs(_image4.data[i] - _image2.data[i]);
		sum+=_image5.data[i];
	}

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
	nicatio::Grayscale(_image.data,_image6.data,_image.cols,_image.rows);
	nicatio::HistEqualize(_image6.data,_image7.data,_image.cols,_image.rows);
	nicatio::HistEqualize2(_image6.data,_image8.data,_image.cols,_image.rows);


	namedWindow( "e", CV_WINDOW_AUTOSIZE );
	imshow( "e", _image6 );
	namedWindow( "f", CV_WINDOW_AUTOSIZE );
	imshow( "f", _image7 );
	namedWindow( "g", CV_WINDOW_AUTOSIZE );
	imshow( "g", _image8 );
	waitKey(0);
	return e;
}
