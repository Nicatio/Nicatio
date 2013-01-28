#include <iostream>
#include <fstream>
#include "cv.h"
#include "highgui.h"
#include "nicatio/nica.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[] ){

	int e;

	if (argv[1]==NULL) {

		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}


	string dir = string(argv[1]);
	    vector<string> files = vector<string>();

	    nicatio::getdirType(dir,"bmp",files);

	    for (unsigned int i = 0;i < files.size();i++) {
	        cout << files[i] << endl;
	    }


//	if (argv[2]==NULL) {
//
//		cout<< "Error: Invalid file name \n" <<endl;
//		return -1;
//	}
//
//	ofstream fin;
//
//
//	fin.open(strcat(argv[1],argv[2]),ios::out | ios::binary);
//
//	fin<<"afdfasdf";
//	fin.close();

	Mat _image, _image2, _image3;
	_image = imread( argv[1], -1 );

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

	Mat _image_6(size,CV_8UC1);
	Mat _image6(size,CV_8UC1);
	Mat _image7(size,CV_8UC1);
	Mat _image8(size,CV_8UC1);
	Mat _image9(size,CV_8UC1);
	Mat _image9_(size,CV_8UC1);
	Mat _image10(size,CV_8UC1);
	Mat _image10_(size,CV_8UC1);
	Mat _image11(size,CV_8UC1);
	nicatio::Grayscale(_image.data,_image_6.data,_image.cols,_image.rows);
	nicatio::filter3x3(_image_6.data,_image6.data,_image.cols,_image.rows,NULL);
	nicatio::Denoise(_image6.data,_image7.data,_image.cols,_image.rows);
	nicatio::DynamicClosing(_image7.data,_image8.data,_image.cols,_image.rows);
	for (int j=0;j<iter;j++){
		nicatio::DynamicMorphQuotImage(_image6.data,_image9_.data,_image.cols,_image.rows, 0);
		nicatio::DynamicMorphQuotImage_revision(_image6.data,_image9.data,_image.cols,_image.rows, 0);
		nicatio::Threshold(_image9.data,_image10.data,0,185,_image.cols,_image.rows,0,0xff);
		nicatio::Threshold(_image9_.data,_image10_.data,0,185,_image.cols,_image.rows,0,0xff);
		nicatio::MedianFilter(_image10_.data,_image11.data,_image.cols,_image.rows);
		cout<<j<<endl;
	}

	namedWindow( "e", CV_WINDOW_AUTOSIZE );
	imshow( "e", _image9_ );
	namedWindow( "f", CV_WINDOW_AUTOSIZE );
	imshow( "f", _image11 );
	namedWindow( "g", CV_WINDOW_AUTOSIZE );
	imshow( "g", _image9 );
	namedWindow( "h", CV_WINDOW_AUTOSIZE );
	imshow( "h", _image10 );
	waitKey(0);
	return e;
}
