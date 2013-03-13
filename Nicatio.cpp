#include <iostream>
#include <fstream>
#include "cv.h"
#include "highgui.h"
#include "nicatio/nicatio.h"
#include "cvnica/cvnica.h"

using namespace cv;
using namespace std;

//#define GF
//#define ENHANCE
//#define FEATHERING
//#define FLASH
//#define SMOOTHING

//#define FR
//#define LINEHISTEQUALIZE
//#define DOG
//#define DMQIDOG
//#define DOGDMQI
#define DMQICONTRASTSHIFT
//#define BINFACE

int main(int argc, char* argv[] ){

	#ifdef GF
	CGuidedFilter guidedfilter;

		Mat l, p, q;
		vector< Mat > l_split, p_split, q_split;

		double t = 0.0;

		int r = 0;
		double eps = 0.0;

	#endif
	#ifdef ENHANCE
		t = (double)getTickCount();

		cout << "guided filtering(enhance) start" << endl;

		l = imread(".\\img_enhancement\\tulips.bmp", CV_LOAD_IMAGE_COLOR);
		p = l;

		r = 16;
		eps = pow(0.1, 2);

		split(Mat::zeros(l.rows, l.cols, CV_8UC3), q_split);
		split(l, l_split);
		split(p, p_split);

		for (int i = 0; i < 3; i++)
		{
			q_split[i] = guidedfilter.filtering(l_split[i], p_split[i], r, eps);
		}

		merge(q_split, q);

		Mat sub = l - q;
		Mat l_enhanced = sub.mul(5) + q;

		resize(l, l, Size(l.cols/2, l.rows/2));
		resize(q, q, Size(q.cols/2, q.rows/2));
		resize(l_enhanced, l_enhanced, Size(l_enhanced.cols/2, l_enhanced.rows/2));
		namedWindow( "tulips", CV_WINDOW_AUTOSIZE );
		namedWindow( "reference", CV_WINDOW_AUTOSIZE );
		namedWindow( "enhanced", CV_WINDOW_AUTOSIZE );
		imshow("tulips", l);
		imshow("reference", q);
		imshow("enhanced", l_enhanced);

		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "guided filtering(enhance) finish.\nelapsed time : " << t << " sec" << endl;
	#endif

	#ifdef FEATHERING
		t = (double)getTickCount();

		cout << "guided filtering(feathering) start" << endl;

		l = imread(".\\img_feathering\\toy.bmp", CV_LOAD_IMAGE_COLOR);
		p = imread(".\\img_feathering\\toy-mask.bmp", CV_LOAD_IMAGE_GRAYSCALE);

		r = 60;
		eps = pow(10.0, -6);

		q = guidedfilter.filtering(l, p, r, eps);


		namedWindow( "toy", CV_WINDOW_AUTOSIZE );
		namedWindow( "mask", CV_WINDOW_AUTOSIZE );
		namedWindow( "feather", CV_WINDOW_AUTOSIZE );

		imshow("toy", l);
		imshow("mask", p);
		imshow("feather", q);

		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "guided filtering(feathering) finish.\nelapsed time : " << t << " sec" << endl;
	#endif

	#ifdef FLASH
		t = (double)getTickCount();

		cout << "guided filtering(flash) start" << endl;

		l = imread(".\\img_flash\\cave-flash.bmp", CV_LOAD_IMAGE_COLOR);
		p = imread(".\\img_flash\\cave-noflash.bmp", CV_LOAD_IMAGE_COLOR);

		r = 8;
		eps = pow(0.02, 2);

		split(Mat::zeros(l.rows, l.cols, CV_8UC3), q_split);
		split(l, l_split);
		split(p, p_split);

		for (int i = 0; i < 3; i++)
		{
			q_split[i] = guidedfilter.filtering(l_split[i], p_split[i], r, eps);
		}

		merge(q_split, q);


		namedWindow( "flash", CV_WINDOW_AUTOSIZE );
		namedWindow( "no flash", CV_WINDOW_AUTOSIZE );
		namedWindow( "adjustment", CV_WINDOW_AUTOSIZE );

		imshow("flash", l);
		imshow("no flash", p);
		imshow("adjustment", q);

		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "guided filtering(flash) finish.\nelapsed time : " << t << " sec" << endl;
	#endif

	#ifdef SMOOTHING
		t = (double)getTickCount();

		cout << "guided filtering(smoothing) start" << endl;

		l = imread(".\\img_smoothing\\cat.bmp", CV_LOAD_IMAGE_GRAYSCALE);
		p = l;

		r = 4;
		eps = pow(0.2, 2);		// try eps = 0.1^2, 0.2^2, 0.4^2

		q = guidedfilter.filtering(l, p, r, eps);

		namedWindow( "cat", CV_WINDOW_AUTOSIZE );
		namedWindow( "smoothed", CV_WINDOW_AUTOSIZE );
		imshow("cat", l);
		imshow("smoothed", q);

		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "guided filtering(smoothing) finish.\nelapsed time : " << t << " sec" << endl;
	#endif








		string dir = string(argv[1]);
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		if (nicatio::getdirType(dir,"pgm",files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}

		Mat temp1 =  imread( dir+"/"+files[64], -1 );
		cout<<dir+"/"+files[64]<<endl;
		Mat temp2,colortemp2;
		vector<Vec4i> lines;
		cvNica::BinFace(temp1,temp2,135,109);
		cvtColor( temp2, colortemp2, CV_GRAY2BGR );
	    HoughLinesP( temp2, lines, 1, CV_PI/180, 50, 20, 5 );
	    for( size_t i = 0; i < lines.size(); i++ )
	    {
	        line( colortemp2, Point(lines[i][0], lines[i][1]),
	            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
	    }

		namedWindow( "a", CV_WINDOW_AUTOSIZE );
		imshow( "a",colortemp2 );
		waitKey(0);


		Size s = temp1.size();
		//nicatio::Grayscale(temp2.data, temp2_.data, temp2.cols, temp2.rows);


		//cvNica::FaceRecognition fr(1,ad);
		//fr.Recognition(dir,"pgm",METHOD_CORR);

#ifdef FR
		cvNica::FaceRecognition fr(dir,refLocation);
		fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR);
		cout<<"1 "<<fr.getAccuracy()<<" "<<endl;
		cout<<"2 "<<fr.getAccuracyIncludingBadImages()<<" "<<endl;
		fr.getAccuracyIncludingBadImagesSubset();

		FileStorage abcd("dix.xml",FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		abcd.release();
#endif
		double t = (double)getTickCount();
		for (unsigned int i = 0;i < files.size();i++) {
//		//for (unsigned int i = 0;i < 1;i++) {
//			//int iter = 1;
//			cout << files[i] << endl;
//			Mat _image1;
//			_image1 = imread( dir+"\\"+files[i], -1 );
//			Size size = _image1.size();
//			Mat dmqi(size,CV_8UC3);
//		   	Mat _gray(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//			Mat _histeq2(size,CV_8UC1);
//			Mat _dmqi_o(size,CV_8UC1);
//			Mat _deno1(size,CV_8UC1);
//			Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//		   	nicatio::Grayscale(_image1.data, _gray.data,_image1.cols,_image1.rows);
//			//nicatio::HistEqualize2(_gray.data,_histeq.data,_image.cols,_image.rows);
//			//cvNica::Denoise(_gray,_deno2);
//		   	//nicatio::HistEqualize2(_gray.data,_gray.data,_image1.cols,_image1.rows);
//			nicatio::Denoise( _gray.data,_deno1.data,_image1.cols,_image1.rows);
//
//			nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi_o.data,_image1.cols,_image1.rows, 0);
//			//equalizeHist(_dmqi_o,_dmqi_o);
//			//nicatio::HistEqualize2(_dmqi_o.data,_dmqi_o.data,_image1.cols,_image1.rows);
//		   	double sigmaS = 24;
//		   	double sigmaR = 0.1;
//		   	cvNica::AdaptiveManifoldFilter amf;
//		   	Mat result;
//		   	Mat result2(_image1.size(),CV_8UC1);
//
//		   	Mat empty;
//
//		   	Mat dmqiRGB[3] = {_dmqi_o,_dmqi_o,_dmqi_o};
//
//		   	merge(dmqiRGB,3,dmqi);
//
//
//		   	double t = (double)getTickCount();
//
//		   	amf.process(_image1,result,sigmaS,sigmaR,empty);
//
//			t = ((double)getTickCount() - t)/getTickFrequency();
//			cout << "filtering finish.\nelapsed time : " << t << " sec" << endl;
//		   	//amf.process(_gray,result,sigmaS,sigmaR,empty);
////		   	nicatio::Grayscale(result.data, result2.data,result.cols,result.rows);
////						cvNica::Reflectance(_gray,result2,_deno1);
////						equalizeHist(_deno1,_deno1);
//
//		   	//namedWindow( "a", CV_WINDOW_AUTOSIZE );
//		   	//imshow( "a", result );
//		   	imwrite(dir+"\\new5\\"+files[i]+"_processed.bmp",result);
//		   	//waitKey(0);
			//for (unsigned int i = 0;i < 1;i++) {
				//int iter = 1;




			//fr.getScore(temp1_,temp2_,5,METHOD_CORR);



#ifdef LINEHISTEQUALIZE
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2;
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			cvNica::lineHistEqualize2(_deno1,_deno2);
			imwrite(dir+"\\new9\\"+files[i]+".bmp",_deno2);
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\new9\\"+tokens[0]+".pgm",_deno2);
//				rename( string(dir+"\\new9\\"+tokens[0]+".pgm").c_str() , string(dir+"\\new9\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\new9\\"+files[i],_deno2);
//
//			}
#endif

#ifdef DOG
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			Mat temp2;

			cvNica::DoG(_image1,temp2,0.2,1,-2,0,0,0,10);


			//unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\dog2\\"+tokens[0]+".pgm",temp2);
//				rename( string(dir+"\\dog2\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dog2\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\dog2\\"+files[i],temp2);
//
//			}
#endif

#ifdef DMQICONTRASTSHIFT
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			nicatio::HistEqualize2(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			cvNica::IntensityShifting(_histeq, _deno2, 246);
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\dmqicontshift\\"+tokens[0]+".pgm",_deno2);
//				rename( string(dir+"\\dmqicontshift\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dmqicontshift\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\dmqicontshift\\"+files[i],_deno2);
//
//			}
#endif




#ifdef DMQIDOG
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			nicatio::HistEqualize2(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			cvNica::DoG(_histeq,_deno2,0.2,1,-2,0,0,0,10);
			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"\\dmqidog\\"+tokens[0]+".pgm",_deno2);
				rename( string(dir+"\\dmqidog\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dmqidog\\"+tokens[0]+".pgm.bad").c_str() );

			} else {

				imwrite(dir+"\\dmqidog\\"+files[i],_deno2);

			}
#endif

#ifdef DOGDMQI
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			cvNica::DoG(_image1,_deno2,0.2,1,-2,0,0,0,10);
			nicatio::Denoise( _deno2.data,_deno1.data,_image1.cols,_image1.rows);
			nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			nicatio::HistEqualize2(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"\\dogdmqi\\"+tokens[0]+".pgm",_histeq);
				rename( string(dir+"\\dogdmqi\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dogdmqi\\"+tokens[0]+".pgm.bad").c_str() );

			} else {

				imwrite(dir+"\\dogdmqi\\"+files[i],_histeq);

			}
#endif

#ifdef BINFACE
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			cvNica::BinFace(_image1,_deno2,135,109);

			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"\\binface\\"+tokens[0]+".pgm",_deno2);
				rename( string(dir+"\\binface\\"+tokens[0]+".pgm").c_str() , string(dir+"\\binface\\"+tokens[0]+".pgm.bad").c_str() );

			} else {

				imwrite(dir+"\\binface\\"+files[i],_deno2);

			}
#endif



//			cout << files[i] <<"\r"<< endl;
//			Mat _image1;
//			_image1 = imread( dir+"\\"+files[i], -1 );
//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//			nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
//			nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
//			nicatio::HistEqualize2(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
//
//
//
//			double sigmaS = 24;
//			double sigmaR = 0.2;
//			cvNica::AdaptiveManifoldFilter amf;
//			Mat result;
//			Mat result2;
//			Mat result3(size,CV_8UC1);
//			Mat empty;
//
//			Mat dmqiRGB[3] = {_histeq,_histeq,_histeq};
//
//			merge(dmqiRGB,3,result);
//
//			amf.process(result,result2,sigmaS,sigmaR,empty);
//
//			nicatio::Grayscale(result2.data, result3.data,_image1.cols,_image1.rows);
//
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\new8\\"+tokens[0]+".pgm",result3);
//				rename( string(dir+"\\new8\\"+tokens[0]+".pgm").c_str() , string(dir+"\\new8\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\new8\\"+files[i],result3);
//
//			}





/////////////////////////

//			cout << files[i] << endl;
//			Mat _image1;
//			_image1 = imread( dir+"\\"+files[i], -1 );
//
//			Size size = _image1.size();
//			Mat dmqi(size,CV_8UC3);
//			Mat _gray(size,CV_8UC1);
//			nicatio::Grayscale(_image1.data, _gray.data,_image1.cols,_image1.rows);
//			Mat _histeq(size,CV_8UC1);
//			Mat _histeq2(size,CV_8UC1);
//			Mat _dmqi_o(size,CV_8UC1);
//			Mat _deno1(size,CV_8UC1);
//			Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//
//			double sigmaS = 24;
//			double sigmaR = 0.2;
//			double sigmaR2 = 0.4;
//			cvNica::AdaptiveManifoldFilter amf;
//			Mat result;
//			Mat result2(_image1.size(),CV_8UC1);
//
//			Mat empty;
//			double t = (double)getTickCount();
//
//			amf.process(_image1,result,sigmaS,sigmaR,empty);
//
//			t = ((double)getTickCount() - t)/getTickFrequency();
//			cout << "filtering finish.\nelapsed time : " << t << " sec" << endl;
//		   	nicatio::Grayscale(result.data, result2.data,result.cols,result.rows);
//						cvNica::Reflectance(_gray,result2,_deno1);
//						nicatio::DynamicMorphQuotImage( _deno1.data,_deno1.data,_image1.cols,_image1.rows, 0);
//						equalizeHist(_deno1,_deno1);
//									Mat dfdf;
//								   	Mat dmqiRGB[3] = {_deno1,_deno1,_deno1};
//
//								   	merge(dmqiRGB,3,dfdf);
//						amf.process(dfdf,_deno2,sigmaS,sigmaR2,empty);
//						//equalizeHist(_deno2,_deno2);
//
//			//namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			//imshow( "a", result );
//			imwrite(dir+"\\new5\\"+files[i]+"_processed.bmp",result);
//			//waitKey(0);
		}
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "filtering finish.\nelapsed time : " << t << " sec" << endl;
///////////////////////



//
//
//
//
//location ::::::::::::: E:\yalebDB\
//
//
//	//int e=0;
//
//	if (argv[1]==NULL) {
//
//		cout<< "Error: Invalid file location \n" <<endl;
//		return -1;
//	}
//
//
//	string dir = string(argv[1]);
//	    vector<string> files = vector<string>();
//
//	    if (nicatio::getdirType(dir,"bmp",files,0)) {
//			cout<< "Error: Invalid file location \n" <<endl;
//			return -1;
//	    }
//
//
//	    for (unsigned int i = 0;i < files.size();i++) {
//	    //for (unsigned int i = 0;i < 1;i++) {
//	    	//int iter = 1;
//	        cout << files[i] << endl;
//	    	Mat _image;
//	    	_image = imread( dir+"\\"+files[i], -1 );
//	    	Size size =  _image.size();
//
//
//	    	double sigmaS = 24;
//			double sigmaR = 0.2;
//
//			cvNica::AdaptiveManifoldFilter amf;
//
//			Mat result;
//			Mat empty;
//			amf.process(_image,result,sigmaS,sigmaR,empty);
//
////	    	for(int df=1;df<=9;df++){
////	    		_image.col(0).copyTo(_image.col(df));
////	    		_image.row(0).copyTo(_image.row(df));
////	    	}
//
//
////	    	_image.col(1).setTo(_image.col(0));
////	    	_image.col(2).setTo(_image.col(0));
////	    	_image.col(3).setTo(_image.col(0));
////	    	_image.col(4).setTo(_image.col(0));
////	    	_image.col(5).setTo(_image.col(0));
////	    	_image.col(6).setTo(_image.col(0));
////	    	_image.col(7).setTo(_image.col(0));
////	    	_image.col(8).setTo(_image.col(0));
////	    	_image.col(9).setTo(_image.col(0));
//
//
//
//
//
//
//	    	Mat _gray(size,CV_8UC1);
//	    	Mat _histeq(size,CV_8UC1);
//	    	Mat _histeq2(size,CV_8UC1);
//	    	Mat _dmqi_o(size,CV_8UC1);
//	    	Mat _deno1(size,CV_8UC1);
//	    	Mat _deno2(size,CV_8UC1);
//	    	Mat _dmqi(size,CV_8UC1);
//	    	nicatio::Grayscale(_image.data, _gray.data,_image.cols,_image.rows);
//	    	//nicatio::HistEqualize2(_gray.data,_histeq.data,_image.cols,_image.rows);
//	    	//cvNica::Denoise(_gray,_deno2);
//	    	//nicatio::Denoise( _gray.data,_deno1.data,_image.cols,_image.rows);
//	    	//nicatio::DynamicMorphQuotImage( _histeq.data,_dmqi_o.data,_image.cols,_image.rows, 0);
//
//			//nicatio::HistEqualize2(_dmqi.data,_histeq2.data,_image.cols,_image.rows);
//
//
//
//
//
////			vector< Mat > l_split, p_split, q_split;
////			l = _image;
////			p = l;
////
////			r = 16;
////			eps = pow(0.1, 2);
////
////			split(Mat::zeros(l.rows, l.cols, CV_8UC3), q_split);
////			split(l, l_split);
////			split(p, p_split);
////
////			for (int i = 0; i < 3; i++)
////			{
////				q_split[i] = guidedfilter.filtering(l_split[i], p_split[i], r, eps);
////			}
////
////			merge(q_split, q);
////
////			Mat sub = l - q;
////			Mat l_enhanced = sub.mul(5) + q;
//
//
//			//resize(l, l, Size(l.cols/2, l.rows/2));
//			//resize(q, q, Size(q.cols/2, q.rows/2));
//			//resize(l_enhanced, l_enhanced, Size(l_enhanced.cols/2, l_enhanced.rows/2));
////			namedWindow( "tulips", CV_WINDOW_AUTOSIZE );
////			namedWindow( "reference", CV_WINDOW_AUTOSIZE );
////			namedWindow( "enhanced", CV_WINDOW_AUTOSIZE );
////			imshow("tulips", l);
////			imshow("reference", q);
////			imshow("enhanced", l_enhanced);
//
//
//
//
//
//
//	    	//GaussianBlur(_gray,_gray,Size(5,5),0.0,0.0);
//			cvNica::lineHistEqualize2(_gray,_deno1);
//	    	//Canny(_gray,_deno1,0.4,70);
//			nicatio::Denoise( _gray.data,_deno2.data,_image.cols,_image.rows);
//
//
//			//equalizeHist(_histeq2,_histeq2);
//			//equalizeHist(_dmqi,_histeq2);
//
//
//			CGuidedFilter guidedfilter;
//
//			Mat l=_gray1, p, q;
//
//			int r = 0;
//			double eps = 0.0;
//
//			p = _gray;
//
//			r = 2;
//			eps = pow(10.0, -6);
//
//
//			q = guidedfilter.filtering(l, p, r, eps);
//
//			Mat sub = l - q;
//			Mat l_enhanced = sub.mul(5) + q;
//
//
//			cvNica::Reflectance(_gray,q,_deno1);
//			equalizeHist(_deno1,_deno1);
////
//
//			cvNica::DynamicMorphQuotImage(q,_histeq2);
//			equalizeHist(_histeq2,_histeq2);
////	    	namedWindow( "a", CV_WINDOW_AUTOSIZE );
////	    	imshow( "a", _dmqi_o );
////	    	namedWindow( "b", CV_WINDOW_AUTOSIZE );
////	    	imshow( "b", _dmqi );
////			waitKey(0);
//
//	    	//nicatio::filter3x3(_image_6.data,_image6.data,_image.cols,_image.rows,NULL);
//	    	//nicatio::Denoise(_image_6.data,_image7.data,_image.cols,_image.rows);
//	    	//nicatio::DynamicClosing(_image7.data,_image8.data,_image.cols,_image.rows);
////	    	for (int j=0;j<iter;j++){
////	    		nicatio::DynamicMorphQuotImage( _gray.data,_image9_.data,_image.cols,_image.rows, 0);
////	    		//nicatio::DynamicMorphQuotImage_revision(_image_6.data,_image9.data,_image.cols,_image.rows, 0);
////	    		//nicatio::Threshold(_image9.data,_image10.data,0,185,_image.cols,_image.rows,0,0xff);
////	    		//nicatio::Threshold(_image9_.data,_image10_.data,0,185,_image.cols,_image.rows,0,0xff);
////	    		//nicatio::MedianFilter(_image10_.data,_image11.data,_image.cols,_image.rows);
////	    		//cout<<j<<endl;
////	    	}
//			//imwrite("E:\\yalebDB\\new4\\"+files[i]+"_processed.bmp",_dmqi);
//			//imwrite("E:\\yalebDB\\new4\\"+files[i]+"_processed1.bmp",_gray);
//			//imwrite("E:\\yalebDB\\new4\\"+files[i]+"_processed2.bmp",q);
//			//imwrite("E:\\yalebDB\\new4\\"+files[i]+"_processed3.bmp",_deno1);
//			//imwrite("E:\\yalebDB\\new4\\"+files[i]+"_processed.bmp",q);
//			imwrite("E:\\yalebDB\\new4\\"+files[i]+"_processed4.bmp",_histeq2);
//
//
//	    }
//
//













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

//	Mat _image, _image2, _image3;
//	_image = imread( argv[1], -1 );
//
//	/*
//	int dilation_size = 1;
//	int dilation_type = MORPH_RECT;
//	Mat element = getStructuringElement( dilation_type,
//	                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
//	                                       Point( dilation_size, dilation_size ) );
//	dilate( _image,  _image2, element, Point(-1,-1),1);
//	erode( _image2,  _image3, element, Point(-1,-1),1);
//	 */
//	//medianBlur(_image,_image2,3);
//	GaussianBlur(_image,_image2,Size(3,3),0.0,0.0);
//
//	int _srcType = _image.channels();
//
//	e = _srcType;
//	cout<<e<<endl;
//
//	Size size =  _image.size();
//	Mat _image4(size,CV_8UC3);
//	Mat _image5(size,CV_8UC3);
//	int sz = _image.cols*_image.rows;
//	int iter=1;
//	int sum=0;
//
//		//nicatio::MorphColor(nicatio::Dilation,_image.data,_image4.data,_image.cols,_image.rows);
//	nicatio::filter3x3Color(_image.data,_image4.data,_image.cols,_image.rows,NULL);
//
//
//	for(int i=0; i < sz*3;i++){
//		_image5.data[i] = abs(_image4.data[i] - _image2.data[i]);
//		sum+=_image5.data[i];
//	}
//
//	double dfaf = nicatio::Lightness(_image.data,_image.cols,_image.rows,3);
//	cout<<dfaf<<endl;
//
//	cout<<sum<<endl;
//
////	namedWindow( "a", CV_WINDOW_AUTOSIZE );
////	imshow( "a", _image4 );
////	namedWindow( "b", CV_WINDOW_AUTOSIZE );
////	imshow( "b", _image2 );
////	namedWindow( "c", CV_WINDOW_AUTOSIZE );
////	imshow( "c", _image5 );
//
//	Mat _image_6(size,CV_8UC1);
//	Mat _image6(size,CV_8UC1);
//	Mat _image7(size,CV_8UC1);
//	Mat _image8(size,CV_8UC1);
//	Mat _image9(size,CV_8UC1);
//	Mat _image9_(size,CV_8UC1);
//	Mat _image10(size,CV_8UC1);
//	Mat _image10_(size,CV_8UC1);
//	Mat _image11(size,CV_8UC1);
//	nicatio::Grayscale(_image.data,_image_6.data,_image.cols,_image.rows);
//	nicatio::filter3x3(_image_6.data,_image6.data,_image.cols,_image.rows,NULL);
//	nicatio::Denoise(_image6.data,_image7.data,_image.cols,_image.rows);
//	nicatio::DynamicClosing(_image7.data,_image8.data,_image.cols,_image.rows);
//	for (int j=0;j<iter;j++){
//		nicatio::DynamicMorphQuotImage(_image6.data,_image9_.data,_image.cols,_image.rows, 0);
//		nicatio::DynamicMorphQuotImage_revision(_image6.data,_image9.data,_image.cols,_image.rows, 0);
//		nicatio::Threshold(_image9.data,_image10.data,0,185,_image.cols,_image.rows,0,0xff);
//		nicatio::Threshold(_image9_.data,_image10_.data,0,185,_image.cols,_image.rows,0,0xff);
//		nicatio::MedianFilter(_image10_.data,_image11.data,_image.cols,_image.rows);
//		cout<<j<<endl;
//	}
//
//	namedWindow( "e", CV_WINDOW_AUTOSIZE );
//	imshow( "e", _image9_ );
//	namedWindow( "f", CV_WINDOW_AUTOSIZE );
//	imshow( "f", _image11 );
//	namedWindow( "g", CV_WINDOW_AUTOSIZE );
//	imshow( "g", _image9 );
//	namedWindow( "h", CV_WINDOW_AUTOSIZE );
//	imshow( "h", _image10 );
//	waitKey(0);
//	return e;
	return 0;
}
