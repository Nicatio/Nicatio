#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//#include "dirent.h"
#include "cv.h"
#include "highgui.h"
#include "nicatio/nicatio.h"
//#include "./dirent/dirent.h"
#include "io.h"
#include "cvnica/cvnica.h"

#include <sys/types.h>
#include <sys/stat.h>


using namespace cv;
using namespace std;

//#define PGM

#define DATA_TYPE_SELECT
#define DATA_TYPE 0
// 0: bmp
// 1: png
// 2: pgm
// 3: jpg


//#define BMP
//#define PNG
//#define PCAP
//#define TXT
//#define GF
//#define ENHANCE
//#define FEATHERING
//#define FLASH
//#define SMOOTHING
//#define FA

//#define CMQI

//#define FR_for_integrated
//#define FR_for_separated
//#define FR_REGION
//#define Fileout

//#define CMUCROP
//#define LINEHISTEQUALIZE
//#define DOG
//#define RAW2BMP
//#define DOGCIRCLE
//#define DMQIDOG
//#define DOGDMQI
//#define DMQICONTRASTSHIFT
//#define crop
//#define DMQI
//#define DMQIHE


//#define MDMQI_stretch
//#define MDMQI_lhe
//#define MDMQI_lhe_he
//#define MDMQI_clahe

//#define closing
//#define LBPadv
//#define LBPadv2
//#define LBPnoise
//#define LBPblur
//#define MDMQI_LBP
//#define LBPAvg


//#define SMQI_adaptive
//#define SMQI
//#define SMQI_noise
//#define SMQI_noise2
//#define SMQI_onlyClose


//#define SMQI_varparam
//#define SMQI_varparam_adaptive

#define CMQI_varparam
//#define MQI_varparam

//#define DMQIADVANCED
//#define BINFACE
//#define ROTATEFACEANGLEDETECTION
//#define ROTATEFACEANGLEDETECTIONDMQI

//#define Auto_crop
//#define Auto_crop2
//#define Auto_crop3
//#define Detect_traffic_sign
//#define Detect_traffic_sign2
//#define MUCT_face_database_120x120_normalization
//#define MUCT_face_database_120x120_normalization
//#define FERET_face_database_120x120_normalization
//#define FERETcopy


//#define illuminationNormalization
//#define textDetection
//#define t140311
//#define faceDetection
//#define faceDetection3
//#define faceDetection_dog
//#define faceDetection2
//#define PCA_

//#define YUVUHD










//Mat src, src_gray;
//Mat dst, detected_edges;
//
//int edgeThresh = 1;
//int lowThreshold=57;
//int const max_lowThreshold = 100;
//int ratio = 3;
//int kernel_size = 3;
//char* window_name = "Edge Map";
//RNG rng(12345);
//vector<vector<Point> > contours;
//vector<Vec4i> hierarchy;
///**
// * @function CannyThreshold
// * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
// */
//void CannyThreshold(int, void*)
//{
//
//  /// Reduce noise with a kernel 3x3
//
//  blur( src_gray, detected_edges, Size(3,3) );
//
//  /// Canny detector
//  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
//
//  /// Using Canny's output as a mask, we display our result
//  dst = Scalar::all(0);
//  Mat dd;
//
//  detected_edges.copyTo(dd);
//	findContours( dd, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
//
//	/// Draw contours
//
//	Mat drawing = Mat::zeros( src_gray.size(), CV_8UC3 );
//	for( int i = 0; i< contours.size(); i++ )
//	{
//		double area0 = contourArea(contours[i]);
//		cout<<area0<<endl;
//		if (area0>100){// && area0<1000) {
//			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//			drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
//		}
//	}
//
//
//  src.copyTo( dst, detected_edges);
//  imshow( window_name, detected_edges );
// }
//
//
///** @function main */
//int main( int argc, char** argv )
//{
//  /// Load an image
//  src = imread( argv[1] );
//
//  if( !src.data )
//  { return -1; }
//
//  /// Create a matrix of the same type and size as src (for dst)
//  dst.create( src.size(), src.type() );
//
//  /// Convert the image to grayscale
//  cvtColor( src, src_gray, CV_BGR2GRAY );
//
//  /// Create a window
//  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//
//  /// Create a Trackbar for user to enter threshold
//  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
//
//  /// Show the image
//  CannyThreshold(0, 0);
//
//  /// Wait until user exit program by pressing a key
//  waitKey(0);
//
//  return 0;
//  }

/*
int main(int argc, char* argv[]){
	RNG rng(12345);
	string dir = "/cygdrive/e/Documents/Nicatio/Database/TrafficSign/night_quarter/png";
	string dir2 = "/cygdrive/e/Documents/Nicatio/Database/TrafficSign/night_quarter/detectResult_Gomez";
	//string refLocation = string(argv[2]);

	vector<string> files = vector<string>();

	if (nicatio::getdirType(dir,"png",files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
	int lowThreshold = 37;
	float ratio = 3;
	int kernel_size = 3;
	for (unsigned int i = 0;i < files.size();i++) {
		Mat src = imread(dir+"/"+files[i], -1);
		Mat src_gray;
		Mat src_gray_med;
		Mat src_gray_med_RGB;
		Mat src_gray_med_canny;
		Mat src_gray_med_canny_RGB;
		if (src.type()!= CV_8UC1) cvtColor(src, src_gray, CV_RGB2GRAY);
		medianBlur(src_gray,src_gray_med,3);
		Canny( src_gray_med, src_gray_med_canny, lowThreshold, lowThreshold*ratio, kernel_size );

		cvtColor(src_gray_med, src_gray_med_RGB, CV_GRAY2RGB);
		cvtColor(src_gray_med_canny, src_gray_med_canny_RGB, CV_GRAY2RGB);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		Mat dd;
		Mat drawing = Mat::zeros( src_gray_med_canny.size(), CV_8UC3 );

		src_gray_med_canny.copyTo(dd);
		findContours( dd, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		for( int i = 0; i< contours.size(); i++ )
		{
			double area0 = contourArea(contours[i]);
			cout<<area0<<endl;
			if (area0>50){// && area0<1000) {
				Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
				drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
			}
		}

		Mat concat = Mat::zeros( Size(src_gray_med_canny.cols*2,src_gray_med_canny.rows*2), CV_8UC3 );
		Mat roi1 = concat(Rect(0, 0, src_gray_med_canny.cols, src_gray_med_canny.rows));
		Mat roi2 = concat(Rect(src_gray_med_canny.cols, 0, src_gray_med_canny.cols, src_gray_med_canny.rows));
		Mat roi3 = concat(Rect(0, src_gray_med_canny.rows, src_gray_med_canny.cols, src_gray_med_canny.rows));
		Mat roi4 = concat(Rect(src_gray_med_canny.cols, src_gray_med_canny.rows, src_gray_med_canny.cols, src_gray_med_canny.rows));

		src.copyTo(roi1);
		src_gray_med_RGB.copyTo(roi2);
		src_gray_med_canny_RGB.copyTo(roi3);
		drawing.copyTo(roi4);

//		namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//		imshow( "Contours", concat );
//		waitKey(0);
		imwrite(dir2+"/"+files[i],concat);
	}

}
*/



#ifdef FERETcopy
int main(int argc, char* argv[] ){
//	const float EYE_DISTANCE = 95;//70.0;	/* final distance between eyes		*/
//	const float EYEROW = 36;//45.0;		/* vertical position of eyes		*/
////	const int   NEW_ROW = 192;		/* size of images after normalization	*/
////	const int   NEW_COL = 168;
////	const float outw = 168;
////	const float outh = 192;
//	const int   NEW_ROW = 168;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 168;

	const float EYE_DISTANCE = 80;//70.0;	/* final distance between eyes		*/
	const float EYEROW = 45;//45.0;		/* vertical position of eyes		*/
//	const int   NEW_ROW = 192;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 192;
	const int   NEW_ROW = 172;		/* size of images after normalization	*/
	const int   NEW_COL = 144;
	const float outw = 144;
	const float outh = 172;

	//string dir = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	//string refLocation = string(argv[2]);
	string namesfc = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	string namesfa = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/gallery.names";
	string namesfb = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafb_expression.names";
	string namesdup1 = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup1_temporal_zero_to_34_months.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup1_temporal_zero_to_34_months.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/new.names";
	string namesdup2 = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup2_at_least_18_months.names";

	//string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/gallery9/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/fb/";
	string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/new_mask/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/illum4/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/gallery2/";
	//string imgloc = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd1/data/images/e/";
	string imgloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/k2/";
//	string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	ifstream FileI;
	char buffer[256];											// use limited buffer

		FileI.open(namesfa.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);



		do {
			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer<<endl;

			stringstream buffer4;
			buffer4<<imgloc<<buffer<<".pgm";
			stringstream buffer5;
			buffer5<<svloc<<"_fa/"<<buffer<<".bmp";
			Mat im;
			im= imread( buffer4.str(), -1 );
			imwrite(buffer5.str(),im);
		} while (buffer[0] != 0);
		FileI.close();

		FileI.open(namesfb.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);


		do {
			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer;

			stringstream buffer4;
			buffer4<<imgloc<<buffer<<".pgm";
			stringstream buffer5;
			buffer5<<svloc<<"_fb/"<<buffer<<".bmp";
			Mat im;
			im= imread( buffer4.str(), -1 );
			imwrite(buffer5.str(),im);
		} while (buffer[0] != 0);
		FileI.close();

		FileI.open(namesfc.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);


		do {
			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer;

			stringstream buffer4;
			buffer4<<imgloc<<buffer<<".pgm";
			stringstream buffer5;
			buffer5<<svloc<<"_fc/"<<buffer<<".bmp";
			Mat im;
			im= imread( buffer4.str(), -1 );
			imwrite(buffer5.str(),im);
		} while (buffer[0] != 0);
		FileI.close();

		FileI.open(namesdup1.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);


		do {
			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer;

			stringstream buffer4;
			buffer4<<imgloc<<buffer<<".pgm";
			stringstream buffer5;
			buffer5<<svloc<<"_dup1/"<<buffer<<".bmp";
			Mat im;
			im= imread( buffer4.str(), -1 );
			imwrite(buffer5.str(),im);
		} while (buffer[0] != 0);
		FileI.close();

		FileI.open(namesdup2.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);


		do {
			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer;

			stringstream buffer4;
			buffer4<<imgloc<<buffer<<".pgm";
			stringstream buffer5;
			buffer5<<svloc<<"_dup2/"<<buffer<<".bmp";
			Mat im;
			im= imread( buffer4.str(), -1 );
			imwrite(buffer5.str(),im);
		} while (buffer[0] != 0);
		FileI.close();
}

#endif





#ifdef MUCT_face_database_120x120_normalization
int main(int argc, char* argv[] ){
//	const float EYE_DISTANCE = 95;//70.0;	/* final distance between eyes		*/
//	const float EYEROW = 36;//45.0;		/* vertical position of eyes		*/
////	const int   NEW_ROW = 192;		/* size of images after normalization	*/
////	const int   NEW_COL = 168;
////	const float outw = 168;
////	const float outh = 192;
//	const int   NEW_ROW = 168;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 168;

//	const float EYE_DISTANCE = 80;//70.0;	/* final distance between eyes		*/
//	const float EYEROW = 45;//45.0;		/* vertical position of eyes		*/
//	const int   NEW_ROW = 192;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 192;
//	const int   NEW_ROW = 172;		/* size of images after normalization	*/
//	const int   NEW_COL = 144;
//	const float outw = 144;
//	const float outh = 172;

//	const float EYE_DISTANCE = 52;//70.0;	/* final distance between eyes		*/
//	const float EYEROW = 22;//45.0;		/* vertical position of eyes		*/
//	const int   NEW_ROW = 100;		/* size of images after normalization	*/
//	const int   NEW_COL = 100;
//	const float outw = 100;
//	const float outh = 100;
//	const float EYE_DISTANCE = 42;//70.0;	/* final distance between eyes		*/
//	const float EYEROW = 17;//45.0;		/* vertical position of eyes		*/
//	const int   NEW_ROW = 80;		/* size of images after normalization	*/
//	const int   NEW_COL = 80;
//	const float outw = 80;
//	const float outh = 80;
	const float EYE_DISTANCE = 62;//70.0;	/* final distance between eyes		*/
	const float EYEROW = 27;//45.0;		/* vertical position of eyes		*/
	const int   NEW_ROW = 120;		/* size of images after normalization	*/
	const int   NEW_COL = 120;
	const float outw = 120;
	const float outh = 120;
	//string dir = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	//string refLocation = string(argv[2]);
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/gallery.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafb_expression.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup1_temporal_zero_to_34_months.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup1_temporal_zero_to_34_months.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/new.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup2_at_least_18_months.names";
	string names = "/cygdrive/e/Documents/Nicatio/Database/Face/AR_CROP/datalist.txt";

	//string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/gallery9/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/fb/";
	string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/AR_CROP/normalized120/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/illum4/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/gallery2/";
	//string imgloc = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd1/data/images/e/";
	string imgloc = "/cygdrive/e/Documents/Nicatio/Database/Face/AR_CROP/bmp/";
//	string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	ifstream FileI;
		FileI.open(names.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);

		char buffer[256];											// use limited buffer

		do {
//			FileI.getline(buffer,256);								// get the entire line
//			cout<<""<<buffer;
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer," ");
//			double lx, ly, rx, ry;
//			lx = atof(tokens[3].c_str());
//			ly = atof(tokens[4].c_str());
//			cout<<" "<<lx;
//			cout<<" "<<ly;
//
//			rx = atof(tokens[1].c_str());
//			ry = atof(tokens[2].c_str());
//			cout<<" "<<rx;
//			cout<<" "<<ry;

			float lx=0, ly=0, rx=0, ry=0;
			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer;

			vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer,",");
			lx = atof(tokens[1].c_str());
			ly = atof(tokens[2].c_str());
			rx = atof(tokens[3].c_str());
			ry = atof(tokens[4].c_str());

			cout<<" "<<lx;
			cout<<" "<<ly;
			cout<<" "<<rx;
			cout<<" "<<ry;

			if (lx != 0) {
				stringstream buffer4;
				buffer4<<imgloc<<tokens[0].c_str()<<".bmp";
				stringstream buffer5;
				buffer5<<svloc<<tokens[0].c_str()<<".bmp";

//				stringstream buffer4;
//				buffer4<<imgloc<<tokens[0]<<".tif";
//				stringstream buffer5;
//				buffer5<<svloc<<tokens[0]<<".bmp";
				cout<<buffer4.str()<<endl;
				Mat im2, im;
				im= imread( buffer4.str(), -1 );
//				int lr = lx-rx;
//				double rate = 65./lr;
//				lx *= rate;
//				ly *= rate;
//				rx *= rate;
//				ry *= rate;
				//resize(im2,im,Size(),rate,rate,INTER_CUBIC);

				Mat rot;
				Size size = im.size();

				double angle = -atan(((double)ry - (double)ly) / ((double)rx - (double)lx));
				double scale = EYE_DISTANCE/sqrt(((double)ry - (double)ly)*((double)ry - (double)ly) + ((double)rx - (double)lx)*((double)rx - (double)lx));

				resize(im,im2,Size(),scale,scale,INTER_CUBIC);


				lx *=scale;
				ly *=scale;
				rx *=scale;
				ry *=scale;


//			   	im2.at<uchar>(ly,lx) = 255;
//
//			   	im2.at<uchar>(ry,rx) = 255;


//				  const float x0 = (int)((rx+lx)/2);
//				  const float y0 = (int)((ry+ly)/2);
				  const float x0 = (int)(im2.cols/2+.5);
				  const float y0 = (int)(im2.rows/2+.5);

				Point center = Point( im2.cols/2, im2.rows/2);

				//Point center2 = Point(y0,x0);
				Mat rot_mat = getRotationMatrix2D( center, -angle*180/PI, 1 );


				warpAffine( im2, rot, rot_mat, im2.size());






				  double  COS = cos(angle);
				   double SIN = sin(angle);


				  float xx = (COS*(lx-x0) - SIN*(ly-y0) + x0);
				  float yy = (SIN*(lx-x0) + COS*(ly-y0) + y0);
			      lx = xx;
			      ly = yy;


			      xx = (COS*(rx-x0) - SIN*(ry-y0) + x0);
			      yy = (SIN*(rx-x0) + COS*(ry-y0) + y0);
			      rx = xx;
			      ry = yy;


//				   rot.at<uchar>(ly,lx) = 255;
//
//				   rot.at<uchar>(ry,rx) = 255;
//					namedWindow( "e", CV_WINDOW_AUTOSIZE );
//					imshow( "e", rot);
//					waitKey(0);

//			      cout<<scale<<endl;
//					cout<<lx<<endl;
//					cout<<ly<<endl;
//					cout<<rx<<endl;
//					cout<<ry<<endl;

				   float edgetoeyedistance = (outw - EYE_DISTANCE)/2.0;
				   int lftcol = (int)(rx - edgetoeyedistance);
				   int rgtcol = (int)(lx + edgetoeyedistance);
				   int uprrow = (int)(ly - EYEROW);
				   int btmrow = uprrow + outh;



//					cout<<lftcol<<endl;
//					cout<<rgtcol<<endl;
//					cout<<uprrow<<endl;
//					cout<<btmrow<<endl;

				   if (btmrow > im.rows*scale)
				   {
				      //fprintf(stderr, "%s: bottom row crop restricted\n", routine);
				      btmrow = im.rows*scale;
				      uprrow = (im.rows*scale < btmrow - outh)?im.rows*scale: btmrow - outh;
				   }

				   if (uprrow < 0)
				   {
				      //fprintf(stderr, "%s: top row crop restricted\n", routine);
				      uprrow = 0;
				      btmrow = (im.rows*scale < uprrow + outh)?im.rows*scale : uprrow + outh;
				   }

				   if (lftcol < 0)
				   {
				      //fprintf(stderr, "%s: left column crop restricted\n", routine);
				      lftcol = 0;
				   }

				   if (rgtcol > im.cols*scale)
				   {
				      //fprintf(stderr, "%s: right column crop restricted\n", routine);
				      rgtcol = im.cols*scale;
				   }

//					cout<<lftcol<<endl;
//					cout<<rgtcol<<endl;
//					cout<<uprrow<<endl;
//					cout<<btmrow<<endl;




//				cout<<angle*180/PI<<endl;
				   cout<<endl;
				Rect myROI(lftcol, uprrow, outw, outh);
				Mat croppedImage;
				Mat(rot, myROI).copyTo(croppedImage);
				imwrite(buffer5.str(),croppedImage);
			}
			//FileI2.close();

		} while (buffer[0] != 0);
		FileI.close();

}

#endif


#ifdef FERET_face_database_120x120_normalization
int main(int argc, char* argv[] ){
//	const float EYE_DISTANCE = 95;//70.0;	/* final distance between eyes		*/
//	const float EYEROW = 36;//45.0;		/* vertical position of eyes		*/
////	const int   NEW_ROW = 192;		/* size of images after normalization	*/
////	const int   NEW_COL = 168;
////	const float outw = 168;
////	const float outh = 192;
//	const int   NEW_ROW = 168;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 168;

	const float EYE_DISTANCE = 80;//70.0;	/* final distance between eyes		*/
	const float EYEROW = 45;//45.0;		/* vertical position of eyes		*/
//	const int   NEW_ROW = 192;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 192;
	const int   NEW_ROW = 172;		/* size of images after normalization	*/
	const int   NEW_COL = 144;
	const float outw = 144;
	const float outh = 172;

	//string dir = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	//string refLocation = string(argv[2]);
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/gallery.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafb_expression.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup1_temporal_zero_to_34_months.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup1_temporal_zero_to_34_months.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/new.names";
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_dup2_at_least_18_months.names";
	string gnd = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd1/data/ground_truths/name_value2/";

	//string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/gallery9/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/fb/";
	string svloc = "/cygdrive/e/Documents/Nicatio/Database/Face/feret/fa_re/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/illum4/";
	//string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/gallery2/";
	//string imgloc = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd1/data/images/e/";
	string imgloc = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd1/data/images/e/";
//	string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	ifstream FileI;
		FileI.open(names.c_str(),ios::in | ios::app);
		FileI.seekg (0, FileI.beg);

		char buffer[256];											// use limited buffer

		do {
//			FileI.getline(buffer,256);								// get the entire line
//			cout<<""<<buffer;
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer," ");
//			double lx, ly, rx, ry;
//			lx = atof(tokens[3].c_str());
//			ly = atof(tokens[4].c_str());
//			cout<<" "<<lx;
//			cout<<" "<<ly;
//
//			rx = atof(tokens[1].c_str());
//			ry = atof(tokens[2].c_str());
//			cout<<" "<<rx;
//			cout<<" "<<ry;


			FileI.getline(buffer,256);								// get the entire line
			cout<<""<<buffer;

			stringstream buffer2;
			buffer2<<gnd<<buffer<<".gnd";
			ifstream FileI2;
			FileI2.open(buffer2.str().c_str(),ios::in | ios::app);
			FileI2.seekg (0, FileI.beg);
			char buffer3[256];
			float lx=0, ly=0, rx=0, ry=0;
			do {
				FileI2.getline(buffer3,256);

				if (buffer3[0]=='l' && buffer3[1]=='e' && buffer3[2]=='f' && buffer3[3]=='t') {
					//cout<<buffer3<<endl;
					vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer3," ");
					lx = atof(tokens[1].c_str());
					ly = atof(tokens[2].c_str());
					cout<<" "<<lx;
					cout<<" "<<ly;


				}
				if (buffer3[0]=='r' && buffer3[1]=='i' && buffer3[2]=='g' && buffer3[3]=='h') {
					//cout<<buffer3<<endl;
					vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer3," ");
					rx = atof(tokens[1].c_str());
					ry = atof(tokens[2].c_str());
					cout<<" "<<rx;
					cout<<" "<<ry;
				}
				if (buffer3[0]=='n' && buffer3[1]=='o' && buffer3[2]=='s' && buffer3[3]=='e') {
					//cout<<buffer3<<endl;
					vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer3," ");
					cout<<" "<<atof(tokens[1].c_str());
					cout<<" "<<atof(tokens[2].c_str());
				}
				if (buffer3[0]=='m' && buffer3[1]=='o' && buffer3[2]=='u' && buffer3[3]=='t') {
					//cout<<buffer3<<endl;
					vector<string> tokens = nicatio::StringTokenizer::getTokens(buffer3," ");
					cout<<" "<<atof(tokens[1].c_str());
					cout<<" "<<atof(tokens[2].c_str());
				}
			} while (buffer3[0] != 0);
			if (lx != 0) {
				stringstream buffer4;
				buffer4<<imgloc<<buffer<<".tif";
				stringstream buffer5;
				buffer5<<svloc<<buffer<<".bmp";

//				stringstream buffer4;
//				buffer4<<imgloc<<tokens[0]<<".tif";
//				stringstream buffer5;
//				buffer5<<svloc<<tokens[0]<<".bmp";
				cout<<buffer4.str()<<endl;
				Mat im2, im;
				im= imread( buffer4.str(), -1 );
//				int lr = lx-rx;
//				double rate = 65./lr;
//				lx *= rate;
//				ly *= rate;
//				rx *= rate;
//				ry *= rate;
				//resize(im2,im,Size(),rate,rate,INTER_CUBIC);

				Mat rot;
				Size size = im.size();

				double angle = -atan(((double)ry - (double)ly) / ((double)rx - (double)lx));
				double scale = EYE_DISTANCE/sqrt(((double)ry - (double)ly)*((double)ry - (double)ly) + ((double)rx - (double)lx)*((double)rx - (double)lx));

				resize(im,im2,Size(),scale,scale,INTER_CUBIC);


				lx *=scale;
				ly *=scale;
				rx *=scale;
				ry *=scale;


//			   	im2.at<uchar>(ly,lx) = 255;
//
//			   	im2.at<uchar>(ry,rx) = 255;


//				  const float x0 = (int)((rx+lx)/2);
//				  const float y0 = (int)((ry+ly)/2);
				  const float x0 = (int)(im2.cols/2+.5);
				  const float y0 = (int)(im2.rows/2+.5);

				Point center = Point( im2.cols/2, im2.rows/2);

				//Point center2 = Point(y0,x0);
				Mat rot_mat = getRotationMatrix2D( center, -angle*180/PI, 1 );


				warpAffine( im2, rot, rot_mat, im2.size());






				  double  COS = cos(angle);
				   double SIN = sin(angle);


				  float xx = (COS*(lx-x0) - SIN*(ly-y0) + x0);
				  float yy = (SIN*(lx-x0) + COS*(ly-y0) + y0);
			      lx = xx;
			      ly = yy;


			      xx = (COS*(rx-x0) - SIN*(ry-y0) + x0);
			      yy = (SIN*(rx-x0) + COS*(ry-y0) + y0);
			      rx = xx;
			      ry = yy;


//				   rot.at<uchar>(ly,lx) = 255;
//
//				   rot.at<uchar>(ry,rx) = 255;
//					namedWindow( "e", CV_WINDOW_AUTOSIZE );
//					imshow( "e", rot);
//					waitKey(0);

//			      cout<<scale<<endl;
//					cout<<lx<<endl;
//					cout<<ly<<endl;
//					cout<<rx<<endl;
//					cout<<ry<<endl;

				   float edgetoeyedistance = (outw - EYE_DISTANCE)/2.0;
				   int lftcol = (int)(rx - edgetoeyedistance);
				   int rgtcol = (int)(lx + edgetoeyedistance);
				   int uprrow = (int)(ly - EYEROW);
				   int btmrow = uprrow + outh;



//					cout<<lftcol<<endl;
//					cout<<rgtcol<<endl;
//					cout<<uprrow<<endl;
//					cout<<btmrow<<endl;

				   if (btmrow > im.rows*scale)
				   {
				      //fprintf(stderr, "%s: bottom row crop restricted\n", routine);
				      btmrow = im.rows*scale;
				      uprrow = (im.rows*scale < btmrow - outh)?im.rows*scale: btmrow - outh;
				   }

				   if (uprrow < 0)
				   {
				      //fprintf(stderr, "%s: top row crop restricted\n", routine);
				      uprrow = 0;
				      btmrow = (im.rows*scale < uprrow + outh)?im.rows*scale : uprrow + outh;
				   }

				   if (lftcol < 0)
				   {
				      //fprintf(stderr, "%s: left column crop restricted\n", routine);
				      lftcol = 0;
				   }

				   if (rgtcol > im.cols*scale)
				   {
				      //fprintf(stderr, "%s: right column crop restricted\n", routine);
				      rgtcol = im.cols*scale;
				   }

//					cout<<lftcol<<endl;
//					cout<<rgtcol<<endl;
//					cout<<uprrow<<endl;
//					cout<<btmrow<<endl;




//				cout<<angle*180/PI<<endl;
				   cout<<endl;
				Rect myROI(lftcol, uprrow, outw, outh);
				Mat croppedImage;
				Mat(rot, myROI).copyTo(croppedImage);
				imwrite(buffer5.str(),croppedImage);
			}
			//FileI2.close();

		} while (buffer[0] != 0);
		FileI.close();

}

#endif

#ifdef textDetection



//double getPSNR ( const Mat& I1, const Mat& I2);
//Scalar getMSSIM( const Mat& I1, const Mat& I2);

int main(int argc, char* argv[] ){




#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "JPG";
	else dataType = "bmp";

		string dir = string(argv[1]);
		//dir = "/cygdrive/e/4/5/";
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif

#ifdef PNG
	string dir = string(argv[1]);
	//string refLocation = string(argv[2]);

	vector<string> files = vector<string>();

	if (nicatio::getdirType(dir,"png",files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif


#ifdef BMP
	string dir = string(argv[1]);
	//string refLocation = string(argv[2]);

	vector<string> files = vector<string>();

	if (nicatio::getdirType(dir,"bmp",files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif

//
//
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 2;
//		int row = 4;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//
//		//Mat gradx(size,CV_8UC1);
//		//Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		Mat sobelMAX=Mat::zeros(size,CV_8UC1);
//
//		Mat sobelColor;
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		//_bilateral3 = _image1;
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		split (_bilateral3,_image1_split);
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//
//		for (int k=0; k<3; k++) {
//			Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//			Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//			Mat sobel(size,CV_32FC1);
//			Mat gradx(size,CV_32FC1);
//			Mat grady(size,CV_32FC1);
//			Mat varmapa(size,CV_8UC1);
//					Mat varmapa_(size,CV_32FC1);
//					Mat varmapa__(size,CV_32FC1);
//			cvNica::VarianceFilter(_image1_split[k],varmapa_,5);
//
//			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
//			float spsum = sum(sp32)[0]/size.width/size.height;
//			float spsqsum = sum(sp32.mul(sp32))[0];
//			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
//			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
////						imshow( "d", varmapa__/255);
////						waitKey(0);
//
//			//sqrt( varmapa__, varmapa_);
//
//			//threshold(varmapa_,varmapa,5,255,THRESH_BINARY_INV);
//			//max(varmapa_,varmapa,varmapa_);
//			std = (std<30)? 30:std;
//			//cv::pow(varmapa_,1.1,varmapa_);
//			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,10,255,THRESH_BINARY_INV);
//			max(varmapa_,varmapa,varmapa);
//
//
////			varmapa.convertTo(varmapa_,CV_8UC1);
////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
////			imshow( "c", varmapa_);
////
////			waitKey(0);
//
//			Mat sobelx(size,CV_32FC1);
//			Mat sobely(size,CV_32FC1);
//			Mat sobelxsq(size,CV_32FC1);
//			Mat sobelysq(size,CV_32FC1);
//			Sobel(_image1_split[k],sobelx,CV_32F,1,0,3,1, 0, BORDER_DEFAULT );
//
//
////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
////			imshow( "c", sobelx/255);
////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
////			imshow( "d", varmapa/255);
////			waitKey(0);
//
//			sobelx/=varmapa/25;
//			multiply(sobelx,sobelx,sobelxsq);
//
//			sobelxsqsum += sobelxsq;
//			//convertScaleAbs( sobelx, gradx );
//			Sobel(_image1_split[k],sobely,CV_32F,0,1,3,1, 0, BORDER_DEFAULT );
//			sobely/=varmapa/25;
//			multiply(sobely,sobely,sobelysq);
//
//			sobelysqsum += sobelysq;
//
//
//			sqrt (sobelxsqsum,gradx);
//			sqrt (sobelysqsum,grady);
//			//convertScaleAbs( sobely, grady );
//			addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//			Mat sobel8U;
//					sobel.convertTo(sobel8U,CV_8UC1);
//					max(sobel8U,sobelMAX,sobelMAX);
//		}
//
////		sobelxsqsum/=1;
////		sobelysqsum/=1;
////		sqrt (sobelxsqsum,gradx);
////		sqrt (sobelysqsum,grady);
////
////		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
////		Mat _sobel;
////		cvNica::MeanFilter(sobel,_sobel,7);
////
////		threshold(_sobel,_sobel,80,255,THRESH_BINARY_INV);
////		namedWindow( "e", CV_WINDOW_AUTOSIZE );
////				imshow( "e", _sobel/255);
////				waitKey(0);
////		sobel=sobel.mul(_sobel)/255;
//		//Mat sobel8U;
//		//sobel.convertTo(sobel8U,CV_8UC1);
//
//
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//
//		Mat varmapa(size,CV_8UC1);
//		Mat varmapa_(size,CV_32FC1);
//		cvNica::VarianceFilter(_gray,varmapa_,5);
//
//		varmapa_.convertTo(varmapa,CV_8UC1);
//
//
//
//				//sobel
//				Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//				convertScaleAbs( sobelx, gradx );
//				Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//				convertScaleAbs( sobely, grady );
//				addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
//
//
//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", varmapa);
//		namedWindow( "d", CV_WINDOW_AUTOSIZE );
//		imshow( "d", sobel);
//		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//		imshow( "e", sobelMAX);
//		waitKey(0);
//
///*
//
//
//
//		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//
//		Mat mergePos [col*row];
//		for (int k=0; k<row; k++) {
//			for (int j=0; j<col; j++) {
//				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//		Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
//		for (int j=0; j<=3; j++) {
//			Mat varmap_[4],varmap[4],varmapColor;
//
//			for (int k=0; k<3; k++) { // apply to each color channel
//				Mat temp;
//
//				//if (j<2)
//					cvNica::CornerDetector(_image1_split[k],varmap_[k],j+45);
//
//				threshold(varmap_[k],varmap[k],15,255,THRESH_BINARY);
//
//			}
//
//
//			max(varmap[0],varmap[1],varmap[3]);
//			max(varmap[3],varmap[2],varmap[3]);
//
//
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap[3],varmap[3]};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//			varmap4Merge += varmap[3];
//			//varmap4Merge2 += varmap__[3];
//			varmapColor.copyTo(mergePos[4+j]);
//
//		}
//
//
//
//
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
//
//
//		_homoInv = 255-varmap4Merge;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(varmap4Merge,_gray,_homoOverlay);
//		bitwise_or(varmap4Merge2,_gray,_homoOverlay3);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay,_homoOverlay};
//		Mat _homoColor_2[3] = {_homoOverlay2,_homoOverlay3,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//		merge(_homoColor_2,3,_homoColor2);
//
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (varmap4Merge,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		//_homoColor2.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//
//
//		imwrite(dir+"/set029/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//		*/
//	}








	// 131223
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 2;
//		int row = 3;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//
//		//Mat gradx(size,CV_8UC1);
//		//Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//
//		Mat sobelColor_[3];
//		Mat sobelColor;
//		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
//		Mat sobelOR = Mat::zeros(size,CV_8UC1);
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat __image1_split[3];
//		Mat __bilateral3 (size,CV_8UC3);
//		//_bilateral3 = _image1;
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		split (_bilateral3,_image1_split);
//
//
//		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(__bilateral3,__bilateral3,3);
//		split (__bilateral3,__image1_split);
//
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		waitKey(0);
//
//		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		int dilation_type = MORPH_CROSS;
//		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//
//		float stdsum=.0;
//		Mat hetero1 = Mat::zeros(size,CV_8UC1),
//			hetero2 = Mat::zeros(size,CV_8UC1),
//			hetero3 = Mat::zeros(size,CV_8UC1);
//
//		for (int k=0; k<3; k++) {
//			Mat hetero1t,
//				hetero2t,
//				hetero3t;
//
//			cvNica::HeteroDetector(_image1_split[k],hetero1t,53);
//			//cvNica::HeteroDetector(__image1_split[k],hetero2t,54);
//			cvNica::HeteroDetector(_image1_split[k],hetero3t,55);
//
//			max(hetero1,hetero1t,hetero1);
//			//max(hetero2,hetero2t,hetero2);
//			max(hetero3,hetero3t,hetero3);
//		}
//
////		namedWindow( "ze1", CV_WINDOW_AUTOSIZE );
////		imshow( "ze1", hetero1);
////		namedWindow( "ze2", CV_WINDOW_AUTOSIZE );
////		imshow( "ze2", hetero2);
////		namedWindow( "ze3", CV_WINDOW_AUTOSIZE );
////		imshow( "ze3", hetero3);
//		//namedWindow( "ze4", CV_WINDOW_AUTOSIZE );
//		//imshow( "ze4", (hetero1+hetero3));
//
//		//waitKey(0);
//
//
//
//		Mat mergePos [col*row];
//		for (int k=0; k<row; k++) {
//			for (int j=0; j<col; j++) {
//				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat hetero1RGB;
//		Mat hetero3RGB;
//		Mat hetero13RGB;
//		Mat hetero13RGB2;
//		cvtColor(hetero1,hetero1RGB,CV_GRAY2RGB);
//		cvtColor(hetero3,hetero3RGB,CV_GRAY2RGB);
//		cvtColor(hetero1+hetero3,hetero13RGB,CV_GRAY2RGB);
//		cvtColor((hetero1+hetero3)*255,hetero13RGB2,CV_GRAY2RGB);
//		_image1.copyTo(mergePos[0]);
//		hetero1RGB.copyTo(mergePos[2]);
//		hetero3RGB.copyTo(mergePos[3]);
//		hetero13RGB.copyTo(mergePos[4]);
//		hetero13RGB2.copyTo(mergePos[5]);
//
//		//imwrite(dir+"/set032/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//
//
////		for (int k=0; k<3; k++) {
////
////			Mat varmapa(size,CV_8UC1);
////					Mat varmapa_(size,CV_32FC1);
////					Mat varmapa__(size,CV_32FC1);
////
////			cvNica::VarianceFilter(__image1_split[k],varmapa_,5);
////
////
////
////
////			//erode(varmapa_,varmapa_,elementL);
////
////			Mat sp32; __image1_split[k].convertTo(sp32,CV_32FC1);
////			float spsum = sum(sp32)[0]/size.width/size.height;
////			float spsqsum = sum(sp32.mul(sp32))[0];
////			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
////			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
//////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//////						imshow( "d", varmapa__/255);
//////						waitKey(0);
////
////			//sqrt( varmapa__, varmapa_);
////
////			//threshold(varmapa_,varmapa,5,255,THRESH_BINARY_INV);
////			//max(varmapa_,varmapa,varmapa_);
////
////			std = (std<30)? 30:std;
////			//cv::pow(varmapa_,1.1,varmapa_);
////			stdsum += std;
////
////
////			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
////			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
////			//threshold(varmapa_,varmapa,10,255,THRESH_BINARY_INV);
////			max(varmapa_,varmapa,varmapa);
////
////
//////			varmapa.convertTo(varmapa_,CV_8UC1);
//////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//////			imshow( "c", varmapa_);
//////
//////			waitKey(0);
////
////			Mat sobelx(size,CV_32FC1);
////			Mat sobely(size,CV_32FC1);
////			Mat sobelxsq(size,CV_32FC1);
////			Mat sobelysq(size,CV_32FC1);
////			Sobel(__image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );
////
////
//////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//////			imshow( "c", sobelx/255);
//////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//////			imshow( "d", varmapa/255);
//////			waitKey(0);
////
////			sobelx/=varmapa/85;
////			multiply(sobelx,sobelx,sobelxsq);
////
////			sobelxsqsum += sobelxsq*std;
////			//convertScaleAbs( sobelx, gradx );
////			Sobel(__image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
////			sobely/=varmapa/85;
////			multiply(sobely,sobely,sobelysq);
////
////			sobelysqsum += sobelysq*std;
////		}
////		sobelxsqsum/=stdsum;
////		sobelysqsum/=stdsum;
////		sqrt (sobelxsqsum,gradx);
////		sqrt (sobelysqsum,grady);
////
////		Mat canny2;Mat gradx2;Mat grady2;
////		gradx.convertTo(gradx2,CV_16S);
////		grady.convertTo(grady2,CV_16S);
////		Canny( _gray, canny2, 60, 120, 3, 1 );
////		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
////		merge(sobelColor_,3,sobelColor);
//////		Mat _sobel;
//////		cvNica::MeanFilter(sobel,_sobel,7);
//////
//////		threshold(_sobel,_sobel,80,255,THRESH_BINARY_INV);
//////		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//////				imshow( "e", _sobel/255);
//////				waitKey(0);
//////		sobel=sobel.mul(_sobel)/255;
////		Mat sobel8U;
////		sobel.convertTo(sobel8U,CV_8UC1);
////		medianBlur(sobel8U,sobelOR,13);
////		//sobelOR/=25;
////		Mat sobel222 = sobel/150;
////		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
////		//				imshow( "a", sobel222);
////		CvMat pSrc = sobel222;
////		CvMat *pDst = cvCreateMat(size.height, size.width, CV_32FC1);;
////
////		cvNica::MorphologicalThinning(&pSrc,pDst);
////		Mat dm = cv::Mat(pDst, true);
////
////		Mat sobelx(size,CV_8UC1);
////		Mat sobely(size,CV_8UC1);
////
////		Mat varmapa(size,CV_8UC1);
////		Mat varmapa_(size,CV_32FC1);
////		cvNica::VarianceFilter(_gray,varmapa_,5);
////
////		varmapa_.convertTo(varmapa,CV_8UC1);
////		//erode(varmapa,varmapa,elementL);
////
////
////				//sobel
////		Mat canny3(size,CV_8UC1);
////				Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
////				Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
////				cvNica::Canny2( _gray, sobelx,sobely, canny3, 60, 120, 3, 1 );
////				//cvNica::CannyEdge( _gray.data, size.width, size.height, 20,40, canny3.data );
////				//Canny( _gray, canny3, 20,40, 3,1 );
////				convertScaleAbs( sobelx, gradx );
////
////				convertScaleAbs( sobely, grady );
////				addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
////
////
////
////				//Canny( _gray, canny3, 60, 120, 3, false );
////
////				//dilate(canny3,canny3,elementL);
////				//erode(canny3,canny3,elementL);
////
////				//erode(sobel8U,sobel8U,elementL);
////
////
////
//////				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//////								imshow( "a", sobelOR);
//////				namedWindow( "b", CV_WINDOW_AUTOSIZE );
//////				imshow( "b", sobelAND);
////			    vector< vector<Point> > contours;
////			    findContours(sobel8U, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
////
////			    // you could also reuse img1 here
////			    Mat mask = Mat::zeros(size, CV_8UC1);
////
////			    // CV_FILLED fills the connected components found
////			    drawContours(mask, contours, -1, Scalar(255), CV_FILLED);
////				namedWindow( "b", CV_WINDOW_AUTOSIZE );
////				imshow( "b", mask);
////		namedWindow( "c", CV_WINDOW_AUTOSIZE );
////		imshow( "c", canny2);
////		namedWindow( "d", CV_WINDOW_AUTOSIZE );
////		imshow( "d", sobel);
////		namedWindow( "e", CV_WINDOW_AUTOSIZE );
////		imshow( "e", sobel8U);
////		waitKey(0);
//
///*
//
//
//
//		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//
//		Mat mergePos [col*row];
//		for (int k=0; k<row; k++) {
//			for (int j=0; j<col; j++) {
//				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//		Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
//		for (int j=0; j<=3; j++) {
//			Mat varmap_[4],varmap[4],varmapColor;
//
//			for (int k=0; k<3; k++) { // apply to each color channel
//				Mat temp;
//
//				//if (j<2)
//					cvNica::CornerDetector(_image1_split[k],varmap_[k],j+45);
//
//				threshold(varmap_[k],varmap[k],15,255,THRESH_BINARY);
//
//			}
//
//
//			max(varmap[0],varmap[1],varmap[3]);
//			max(varmap[3],varmap[2],varmap[3]);
//
//
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap[3],varmap[3]};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//			varmap4Merge += varmap[3];
//			//varmap4Merge2 += varmap__[3];
//			varmapColor.copyTo(mergePos[4+j]);
//
//		}
//
//
//
//
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
//
//
//		_homoInv = 255-varmap4Merge;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(varmap4Merge,_gray,_homoOverlay);
//		bitwise_or(varmap4Merge2,_gray,_homoOverlay3);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay,_homoOverlay};
//		Mat _homoColor_2[3] = {_homoOverlay2,_homoOverlay3,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//		merge(_homoColor_2,3,_homoColor2);
//
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (varmap4Merge,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		//_homoColor2.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//
//
//		imwrite(dir+"/set029/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//		*/
//	}



//131230
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 2;
//		int row = 1;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*4,_image1.rows*4);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _gray_enlarged (size2,CV_8UC1);
//		Mat _bilateral (size,CV_8UC1);
//
//		Mat sobel(size,CV_8UC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//
//		Mat sobel_enlarged(size2,CV_8UC1);
//		Mat gradx_enlarged(size2,CV_32FC1);
//		Mat grady_enlarged(size2,CV_32FC1);
//		Mat sobelx_enlarged(size2,CV_8UC1);
//		Mat sobely_enlarged(size2,CV_8UC1);
//		Mat sobel_redim (size,CV_8UC1);
//
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _image1_split_resized[3];
//		Mat _image1_split2[3];
//		Mat _image1_split_resized2[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat _bilateral3_resized (size2,CV_8UC3);
//
//		Mat _resized;
//
//
//		Mat sobel1MAX = Mat::zeros(size,CV_8UC1);
//		Mat sobel2MAX = Mat::zeros(size,CV_8UC1);
//		Mat sobel3MAX = Mat::zeros(size,CV_8UC1);
//		Mat sobel4MAX = Mat::zeros(size,CV_8UC1);
//
//		Mat sobel1RGB;
//		Mat sobel2RGB;
//		Mat sobel3RGB;
//		Mat sobel4RGB;
//
//
//
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		split (_image1,_image1_split);
//
//		resize (_bilateral3,_resized, size2, 0, 0, INTER_CUBIC);
//		bilateralFilter (_resized, _bilateral3_resized , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3_resized,_bilateral3_resized,3);
//		split (_resized,_image1_split_resized);
//
//
//		//cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		for (int k=0; k<3; k++) {
////			Sobel(_image1_split[k],sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
////			Sobel(_image1_split[k],sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
////			convertScaleAbs( sobelx, gradx );
////			convertScaleAbs( sobely, grady );
////			addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
////			max(sobel,sobel1MAX,sobel1MAX);
////
////			Sobel(_image1_split_resized[k],sobelx_enlarged,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
////			Sobel(_image1_split_resized[k],sobely_enlarged,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
////			convertScaleAbs( sobelx_enlarged, gradx_enlarged );
////			convertScaleAbs( sobely_enlarged, grady_enlarged );
////			addWeighted( gradx_enlarged, 0.5, grady_enlarged, 0.5, 0, sobel_enlarged );
////			resize (sobel_enlarged,sobel_redim, size, 0, 0, INTER_CUBIC);
////			max(sobel_redim,sobel3MAX,sobel3MAX);
//		}
//
//
//		split (_bilateral3,_image1_split2);
//		split (_bilateral3_resized,_image1_split_resized2);
//
//
//		for (int k=0; k<3; k++) {
////			Sobel(_image1_split2[k],sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
////			Sobel(_image1_split2[k],sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
////			convertScaleAbs( sobelx, gradx );
////			convertScaleAbs( sobely, grady );
////			addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
////			max(sobel,sobel2MAX,sobel2MAX);
//
//			Sobel(_image1_split_resized2[k],sobelx_enlarged,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//			Sobel(_image1_split_resized2[k],sobely_enlarged,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//			convertScaleAbs( sobelx_enlarged, gradx_enlarged );
//			convertScaleAbs( sobely_enlarged, grady_enlarged );
//			addWeighted( gradx_enlarged, 0.5, grady_enlarged, 0.5, 0, sobel_enlarged );
//			resize (sobel_enlarged,sobel_redim, size, 0, 0, INTER_CUBIC);
//			max(sobel_redim,sobel4MAX,sobel4MAX);
//		}
//
//
//				cvtColor(_image1,_gray,CV_RGB2GRAY);
//				Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//				Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//				convertScaleAbs( sobelx, gradx );
//				convertScaleAbs( sobely, grady );
//				addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//				cvtColor(sobel,sobel1RGB,CV_GRAY2RGB);
//		//
//		//		cvtColor(_bilateral3,_gray,CV_RGB2GRAY);
//		//		Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//		//		Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//		//		convertScaleAbs( sobelx, gradx );
//		//		convertScaleAbs( sobely, grady );
//		//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		//		cvtColor(sobel,sobel2RGB,CV_GRAY2RGB);
//		//
//		//
//		//		cvtColor(_resized,_gray_enlarged,CV_RGB2GRAY);
//		//		Sobel(_gray_enlarged,sobelx_enlarged,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//		//		Sobel(_gray_enlarged,sobely_enlarged,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//		//		convertScaleAbs( sobelx_enlarged, gradx_enlarged );
//		//		convertScaleAbs( sobely_enlarged, grady_enlarged );
//		//		addWeighted( gradx_enlarged, 0.5, grady_enlarged, 0.5, 0, sobel_enlarged );
//		//		resize (sobel_enlarged,sobel_redim, size, 0, 0, INTER_CUBIC);
//		//		cvtColor(sobel_redim,sobel3RGB,CV_GRAY2RGB);
//		//
//		//		cvtColor(_bilateral3_resized,_gray_enlarged,CV_RGB2GRAY);
//		//		Sobel(_gray_enlarged,sobelx_enlarged,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//		//		Sobel(_gray_enlarged,sobely_enlarged,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//		//		convertScaleAbs( sobelx_enlarged, gradx_enlarged );
//		//		convertScaleAbs( sobely_enlarged, grady_enlarged );
//		//		addWeighted( gradx_enlarged, 0.5, grady_enlarged, 0.5, 0, sobel_enlarged );
//		//		resize (sobel_enlarged,sobel_redim, size, 0, 0, INTER_CUBIC);
//		//		cvtColor(sobel_redim,sobel4RGB,CV_GRAY2RGB);
//
//				//cvtColor(sobel1MAX,sobel1RGB,CV_GRAY2RGB);
//				//cvtColor(sobel2MAX,sobel2RGB,CV_GRAY2RGB);
//				//cvtColor(sobel3MAX,sobel3RGB,CV_GRAY2RGB);
//				cvtColor(sobel4MAX,sobel4RGB,CV_GRAY2RGB);
//
//
//
//				//sobel3RGB*=2.3;
//				sobel4RGB*=1.5;
//
//				//equalizeHist(sobel_redim,sobel_redim);
//
//		//		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//		//		imshow( "e", sobel);
//		//		namedWindow( "e2", CV_WINDOW_AUTOSIZE );
//		//		imshow( "e2", sobel_redim*2);
//		//		waitKey(0);
//						Mat mergePos [col*row];
//						for (int k=0; k<row; k++) {
//							for (int j=0; j<col; j++) {
//								mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//							}
//						}
////						_image1.copyTo(mergePos[0]);
////						_bilateral3.copyTo(mergePos[1]);
////						sobel1RGB.copyTo(mergePos[2]);
////						sobel2RGB.copyTo(mergePos[3]);
////						sobel3RGB.copyTo(mergePos[4]);
////						sobel4RGB.copyTo(mergePos[5]);
//
//						sobel1RGB.copyTo(mergePos[0]);
//						sobel4RGB.copyTo(mergePos[1]);
//						imwrite(dir+"/set035_2/"+files[i]+".png",merged);
//
//				cout<<files[i]<<endl;
//
//	}




// 140226

//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 2;
//		int row = 1;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*4,_image1.rows*4);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _gray_enlarged (size2,CV_8UC1);
//		Mat _bilateral (size,CV_8UC1);
//
//		Mat sobel(size,CV_8UC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//
//		Mat sobel_enlarged(size2,CV_8UC1);
//		Mat gradx_enlarged(size2,CV_32FC1);
//		Mat grady_enlarged(size2,CV_32FC1);
//		Mat sobelx_enlarged(size2,CV_8UC1);
//		Mat sobely_enlarged(size2,CV_8UC1);
//		Mat sobel_redim (size,CV_8UC1);
//
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _image1_split_resized[3];
//		Mat _image1_split2[3];
//		Mat _image1_split_resized2[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat _bilateral3_resized (size2,CV_8UC3);
//
//		Mat _resized;
//
//
//		Mat sobel1MAX = Mat::zeros(size,CV_8UC1);
//		Mat sobel2MAX = Mat::zeros(size,CV_8UC1);
//		Mat sobel3MAX = Mat::zeros(size,CV_8UC1);
//		Mat sobel4MAX = Mat::zeros(size,CV_8UC1);
//
//		Mat sobel1RGB;
//		Mat sobel2RGB;
//		Mat sobel3RGB;
//		Mat sobel4RGB;
//
//
//
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		split (_image1,_image1_split);
//
//		Mat _bilateral3_gray,cornerharrisdst[3],cornerharrisdst_norm[3],cornerharrisdst_norm_scaled[3], cornerharrisdst_norm_scaled2[3],cornerharrisdst_norm_scaled2_merge;
//
//		cvtColor(_bilateral3,_bilateral3_gray,CV_RGB2GRAY);
//		int thresh = 80;
//		int blockSize = 3;
//		int apertureSize = 3;
//		double k = 0.04;
//		double min_,max_;
//
//		Mat cannny[3],soobel[3],cannny_merge,soobel_merge;
//
//		for (int q=0;q<3;q++){
//			cornerHarris(_image1_split[q], cornerharrisdst[q], blockSize, apertureSize, k, BORDER_DEFAULT );
//
//			minMaxIdx(cornerharrisdst[q],&min_,&max_,0);
//			cout<<"max: "<<max_<<endl;
//			cout<<"min: "<<min_<<endl;
//
//			cornerharrisdst_norm[q] = cornerharrisdst[q]/max_*255.;
//
//
//
//
//			/// Normalizing
//			normalize( cornerharrisdst[q], cornerharrisdst_norm[q], 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
//			convertScaleAbs( cornerharrisdst_norm[q], cornerharrisdst_norm_scaled[q] );
//			normalize( cornerharrisdst_norm_scaled[q], cornerharrisdst_norm_scaled2[q], 0, 255, NORM_MINMAX, CV_8UC1, Mat() );
//	//		minMaxIdx(cornerharrisdst_norm,&min_,&max_,0);
//	//		cout<<"max: "<<max_<<endl;
//	//		cout<<"min: "<<min_<<endl;
//	//		cornerharrisdst_norm.convertTo(cornerharrisdst_norm_scaled,CV_8UC1);
//
//
//
//
//
//			Canny( _image1_split[q], cannny[q], 30, 50, 3, 1 );
//
//
//			Mat sobelx(size,CV_32FC1);
//			Mat sobely(size,CV_32FC1);
//			Mat sobelxsq(size,CV_32FC1);
//			Mat sobelysq(size,CV_32FC1);
//			Sobel(_image1_split[q],sobelx,CV_32FC1,1,0,3,1, 0, BORDER_DEFAULT );
//			Sobel(_image1_split[q],sobely,CV_32FC1,0,1,3,1, 0, BORDER_DEFAULT );
//			convertScaleAbs( sobelx, gradx );
//			convertScaleAbs( sobely, grady );
//			addWeighted( gradx, 0.5, grady, 0.5, 0, soobel[q] );
//
//
//		}
//
//		merge (cornerharrisdst_norm_scaled2,3,cornerharrisdst_norm_scaled2_merge);
//		merge (soobel,3,soobel_merge);
//		merge (cannny,3,cannny_merge);
//		//threshold(cornerharrisdst_norm_scaled,cornerharrisdst_norm_scaled_cvt,20,255,THRESH_BINARY);
//
//
//
//
//
//
//
//		//			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		//			imshow( "c", sobelx/255);
//		//			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//		//			imshow( "d", varmapa/255);
//		//			waitKey(0);
//
//
//
//
//
//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", soobel_merge);
//		namedWindow( "d", CV_WINDOW_AUTOSIZE );
//		imshow( "d", cannny_merge);
//		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//		imshow( "e", cornerharrisdst_norm_scaled2_merge);
//		waitKey(0);
//
//
//
//		resize (_bilateral3,_resized, size2, 0, 0, INTER_CUBIC);
//		bilateralFilter (_resized, _bilateral3_resized , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3_resized,_bilateral3_resized,3);
//		split (_resized,_image1_split_resized);
//
//
//		split (_bilateral3,_image1_split2);
//		split (_bilateral3_resized,_image1_split_resized2);
//
//
//		for (int k=0; k<3; k++) {
//			Sobel(_image1_split_resized2[k],sobelx_enlarged,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//			Sobel(_image1_split_resized2[k],sobely_enlarged,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//			convertScaleAbs( sobelx_enlarged, gradx_enlarged );
//			convertScaleAbs( sobely_enlarged, grady_enlarged );
//			addWeighted( gradx_enlarged, 0.5, grady_enlarged, 0.5, 0, sobel_enlarged );
//			resize (sobel_enlarged,sobel_redim, size, 0, 0, INTER_CUBIC);
//			max(sobel_redim,sobel4MAX,sobel4MAX);
//		}
//
//
//				cvtColor(_image1,_gray,CV_RGB2GRAY);
//				Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//				Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//				convertScaleAbs( sobelx, gradx );
//				convertScaleAbs( sobely, grady );
//				addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//				cvtColor(sobel,sobel1RGB,CV_GRAY2RGB);
//
//				cvtColor(sobel4MAX,sobel4RGB,CV_GRAY2RGB);
//				sobel4RGB*=1.5;
//
//						Mat mergePos [col*row];
//						for (int k=0; k<row; k++) {
//							for (int j=0; j<col; j++) {
//								mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//							}
//						}
//
//						sobel1RGB.copyTo(mergePos[0]);
//						sobel4RGB.copyTo(mergePos[1]);
//						imwrite(dir+"/set035_2/"+files[i]+".png",merged);
//
//				cout<<files[i]<<endl;
//
//	}






//		int kd=5;
//		for (unsigned int i = 0;i < files.size();i++) {
//
//			int col = 2;
//			int row = 3;
//
//			Mat _image1 = imread( dir+"/"+files[i], -1 );
//			Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//			Size size = _image1.size();
//			Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//			Mat _gray (size,CV_8UC1),_grayRGB;
//			Mat _bilateral (size,CV_8UC1);
//
//			//Mat gradx(size,CV_8UC1);
//			//Mat grady(size,CV_8UC1);
//			Mat sobel(size,CV_8UC1);
//
//			Mat sobelColor_[3];
//			Mat sobelColor;
//			Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
//			Mat sobelOR = Mat::zeros(size,CV_8UC1);
//			Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//			Mat _image1_split[3];
//			Mat _bilateral3 (size,CV_8UC3);
//			Mat __image1_split[3];
//			Mat __bilateral3 (size,CV_8UC3);
//			//_bilateral3 = _image1;
//			bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//			medianBlur(_bilateral3,_bilateral3,3);
//			split (_bilateral3,_image1_split);
//
//
//			bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
//			medianBlur(__bilateral3,__bilateral3,3);
//			split (__bilateral3,__image1_split);
//
//			cvtColor(_image1,_gray,CV_RGB2GRAY);
//			cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//			waitKey(0);
//
//			Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//			Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//			Mat gradx(size,CV_32FC1);
//			Mat grady(size,CV_32FC1);
//			int dilation_type = MORPH_CROSS;
//			Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//
//			float stdsum=.0;
//			Mat hetero1 = Mat::zeros(size,CV_8UC1),
//				hetero2 = Mat::zeros(size,CV_8UC1),
//				hetero3 = Mat::zeros(size,CV_8UC1);
//
//			for (int k=0; k<3; k++) {
//				Mat hetero1t,
//					hetero2t,
//					hetero3t;
//
//				cvNica::HeteroDetector(_image1_split[k],hetero1t,53);
//				//cvNica::HeteroDetector(__image1_split[k],hetero2t,54);
//				cvNica::HeteroDetector(_image1_split[k],hetero3t,55);
//
//				max(hetero1,hetero1t,hetero1);
//				//max(hetero2,hetero2t,hetero2);
//				max(hetero3,hetero3t,hetero3);
//			}
//
//	//		namedWindow( "ze1", CV_WINDOW_AUTOSIZE );
//	//		imshow( "ze1", hetero1);
//	//		namedWindow( "ze2", CV_WINDOW_AUTOSIZE );
//	//		imshow( "ze2", hetero2);
//	//		namedWindow( "ze3", CV_WINDOW_AUTOSIZE );
//	//		imshow( "ze3", hetero3);
//			//namedWindow( "ze4", CV_WINDOW_AUTOSIZE );
//			//imshow( "ze4", (hetero1+hetero3));
//
//			//waitKey(0);
//
//
//
//			Mat mergePos [col*row];
//			for (int k=0; k<row; k++) {
//				for (int j=0; j<col; j++) {
//					mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//				}
//			}
//
//			Mat hetero1RGB;
//			Mat hetero3RGB;
//			Mat hetero13RGB;
//			Mat hetero13RGB2;
//			cvtColor(hetero1,hetero1RGB,CV_GRAY2RGB);
//			cvtColor(hetero3,hetero3RGB,CV_GRAY2RGB);
//			cvtColor(hetero1+hetero3,hetero13RGB,CV_GRAY2RGB);
//			cvtColor((hetero1+hetero3)*255,hetero13RGB2,CV_GRAY2RGB);
//			_image1.copyTo(mergePos[0]);
//			hetero1RGB.copyTo(mergePos[2]);
//			hetero3RGB.copyTo(mergePos[3]);
//			hetero13RGB.copyTo(mergePos[4]);
//			hetero13RGB2.copyTo(mergePos[5]);
//
//			//imwrite(dir+"/set032/"+files[i]+".png",merged);
//			cout<<files[i]<<endl;
//
//
//	//		for (int k=0; k<3; k++) {
//	//
//	//			Mat varmapa(size,CV_8UC1);
//	//					Mat varmapa_(size,CV_32FC1);
//	//					Mat varmapa__(size,CV_32FC1);
//	//
//	//			cvNica::VarianceFilter(__image1_split[k],varmapa_,5);
//	//
//	//
//	//
//	//
//	//			//erode(varmapa_,varmapa_,elementL);
//	//
//	//			Mat sp32; __image1_split[k].convertTo(sp32,CV_32FC1);
//	//			float spsum = sum(sp32)[0]/size.width/size.height;
//	//			float spsqsum = sum(sp32.mul(sp32))[0];
//	//			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
//	//			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
//	////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//	////						imshow( "d", varmapa__/255);
//	////						waitKey(0);
//	//
//	//			//sqrt( varmapa__, varmapa_);
//	//
//	//			//threshold(varmapa_,varmapa,5,255,THRESH_BINARY_INV);
//	//			//max(varmapa_,varmapa,varmapa_);
//	//
//	//			std = (std<30)? 30:std;
//	//			//cv::pow(varmapa_,1.1,varmapa_);
//	//			stdsum += std;
//	//
//	//
//	//			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
//	//			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
//	//			//threshold(varmapa_,varmapa,10,255,THRESH_BINARY_INV);
//	//			max(varmapa_,varmapa,varmapa);
//	//
//	//
//	////			varmapa.convertTo(varmapa_,CV_8UC1);
//	////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	////			imshow( "c", varmapa_);
//	////
//	////			waitKey(0);
//	//
//	//			Mat sobelx(size,CV_32FC1);
//	//			Mat sobely(size,CV_32FC1);
//	//			Mat sobelxsq(size,CV_32FC1);
//	//			Mat sobelysq(size,CV_32FC1);
//	//			Sobel(__image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );
//	//
//	//
//	////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	////			imshow( "c", sobelx/255);
//	////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//	////			imshow( "d", varmapa/255);
//	////			waitKey(0);
//	//
//	//			sobelx/=varmapa/85;
//	//			multiply(sobelx,sobelx,sobelxsq);
//	//
//	//			sobelxsqsum += sobelxsq*std;
//	//			//convertScaleAbs( sobelx, gradx );
//	//			Sobel(__image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
//	//			sobely/=varmapa/85;
//	//			multiply(sobely,sobely,sobelysq);
//	//
//	//			sobelysqsum += sobelysq*std;
//	//		}
//	//		sobelxsqsum/=stdsum;
//	//		sobelysqsum/=stdsum;
//	//		sqrt (sobelxsqsum,gradx);
//	//		sqrt (sobelysqsum,grady);
//	//
//	//		Mat canny2;Mat gradx2;Mat grady2;
//	//		gradx.convertTo(gradx2,CV_16S);
//	//		grady.convertTo(grady2,CV_16S);
//	//		Canny( _gray, canny2, 60, 120, 3, 1 );
//	//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//	//		merge(sobelColor_,3,sobelColor);
//	////		Mat _sobel;
//	////		cvNica::MeanFilter(sobel,_sobel,7);
//	////
//	////		threshold(_sobel,_sobel,80,255,THRESH_BINARY_INV);
//	////		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//	////				imshow( "e", _sobel/255);
//	////				waitKey(0);
//	////		sobel=sobel.mul(_sobel)/255;
//	//		Mat sobel8U;
//	//		sobel.convertTo(sobel8U,CV_8UC1);
//	//		medianBlur(sobel8U,sobelOR,13);
//	//		//sobelOR/=25;
//	//		Mat sobel222 = sobel/150;
//	//		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	//		//				imshow( "a", sobel222);
//	//		CvMat pSrc = sobel222;
//	//		CvMat *pDst = cvCreateMat(size.height, size.width, CV_32FC1);;
//	//
//	//		cvNica::MorphologicalThinning(&pSrc,pDst);
//	//		Mat dm = cv::Mat(pDst, true);
//	//
//	//		Mat sobelx(size,CV_8UC1);
//	//		Mat sobely(size,CV_8UC1);
//	//
//	//		Mat varmapa(size,CV_8UC1);
//	//		Mat varmapa_(size,CV_32FC1);
//	//		cvNica::VarianceFilter(_gray,varmapa_,5);
//	//
//	//		varmapa_.convertTo(varmapa,CV_8UC1);
//	//		//erode(varmapa,varmapa,elementL);
//	//
//	//
//	//				//sobel
//	//		Mat canny3(size,CV_8UC1);
//	//				Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//	//				Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//	//				cvNica::Canny2( _gray, sobelx,sobely, canny3, 60, 120, 3, 1 );
//	//				//cvNica::CannyEdge( _gray.data, size.width, size.height, 20,40, canny3.data );
//	//				//Canny( _gray, canny3, 20,40, 3,1 );
//	//				convertScaleAbs( sobelx, gradx );
//	//
//	//				convertScaleAbs( sobely, grady );
//	//				addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//	//
//	//
//	//
//	//				//Canny( _gray, canny3, 60, 120, 3, false );
//	//
//	//				//dilate(canny3,canny3,elementL);
//	//				//erode(canny3,canny3,elementL);
//	//
//	//				//erode(sobel8U,sobel8U,elementL);
//	//
//	//
//	//
//	////				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	////								imshow( "a", sobelOR);
//	////				namedWindow( "b", CV_WINDOW_AUTOSIZE );
//	////				imshow( "b", sobelAND);
//	//			    vector< vector<Point> > contours;
//	//			    findContours(sobel8U, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	//
//	//			    // you could also reuse img1 here
//	//			    Mat mask = Mat::zeros(size, CV_8UC1);
//	//
//	//			    // CV_FILLED fills the connected components found
//	//			    drawContours(mask, contours, -1, Scalar(255), CV_FILLED);
//	//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
//	//				imshow( "b", mask);
//	//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	//		imshow( "c", canny2);
//	//		namedWindow( "d", CV_WINDOW_AUTOSIZE );
//	//		imshow( "d", sobel);
//	//		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//	//		imshow( "e", sobel8U);
//	//		waitKey(0);
//
//	/*
//
//
//
//			Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//
//			Mat mergePos [col*row];
//			for (int k=0; k<row; k++) {
//				for (int j=0; j<col; j++) {
//					mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//				}
//			}
//
//			Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//			Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
//			for (int j=0; j<=3; j++) {
//				Mat varmap_[4],varmap[4],varmapColor;
//
//				for (int k=0; k<3; k++) { // apply to each color channel
//					Mat temp;
//
//					//if (j<2)
//						cvNica::CornerDetector(_image1_split[k],varmap_[k],j+45);
//
//					threshold(varmap_[k],varmap[k],15,255,THRESH_BINARY);
//
//				}
//
//
//				max(varmap[0],varmap[1],varmap[3]);
//				max(varmap[3],varmap[2],varmap[3]);
//
//
//				Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap[3],varmap[3]};
//				merge(varmapColor_,3,varmapColor);
//				varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//				varmap4Merge += varmap[3];
//				//varmap4Merge2 += varmap__[3];
//				varmapColor.copyTo(mergePos[4+j]);
//
//			}
//
//
//
//
//			Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
//
//
//			_homoInv = 255-varmap4Merge;
//			bitwise_and(_homoInv,_gray,_homoOverlay2);
//			bitwise_or(varmap4Merge,_gray,_homoOverlay);
//			bitwise_or(varmap4Merge2,_gray,_homoOverlay3);
//
//			Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay,_homoOverlay};
//			Mat _homoColor_2[3] = {_homoOverlay2,_homoOverlay3,_homoOverlay};
//			merge(_homoColor_,3,_homoColor);
//			merge(_homoColor_2,3,_homoColor2);
//
//			cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//			cvtColor (varmap4Merge,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//			_image1.copyTo(mergePos[0]);
//			_homoColor.copyTo(mergePos[1]);
//			//_homoColor2.copyTo(mergePos[3]);
//			_homoThresholdColor.copyTo(mergePos[2]);
//
//
//			imwrite(dir+"/set029/"+files[i]+".png",merged);
//			cout<<files[i]<<endl;
//			*/
//		}






//	// GOOOOOOOOOOOOOOOOOOd
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 2;
//		int row = 4;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//
//		//Mat gradx(size,CV_8UC1);
//		//Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//
//		Mat sobelColor_[3];
//		Mat sobelColor;
//		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
//		Mat sobelOR = Mat::zeros(size,CV_8UC1);
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat __image1_split[3];
//		Mat __bilateral3 (size,CV_8UC3);
//		//_bilateral3 = _image1;
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		split (_bilateral3,_image1_split);
//
//
//		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(__bilateral3,__bilateral3,3);
//		split (__bilateral3,__image1_split);
//
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		int dilation_type = MORPH_CROSS;
//			Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//
//			float stdsum=.0;
//			Mat canny = Mat::zeros(size,CV_32FC1);;
//		for (int k=0; k<3; k++) {
//
//			Mat varmapa(size,CV_8UC1);
//					Mat varmapa_(size,CV_32FC1);
//					Mat varmapa__(size,CV_32FC1);
//
//			cvNica::VarianceFilter(_image1_split[k],varmapa_,5);
//
//
//
//
//			//erode(varmapa_,varmapa_,elementL);
//
//			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
//			float spsum = sum(sp32)[0]/size.width/size.height;
//			float spsqsum = sum(sp32.mul(sp32))[0];
//			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
//			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
////						imshow( "d", varmapa__/255);
////						waitKey(0);
//
//			//sqrt( varmapa__, varmapa_);
//
//			//threshold(varmapa_,varmapa,5,255,THRESH_BINARY_INV);
//			//max(varmapa_,varmapa,varmapa_);
//
//			std = (std<18)? 18:std;
//			//cv::pow(varmapa_,1.1,varmapa_);
//			stdsum += std;
//
//
//			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,8,255,THRESH_BINARY_INV);
//			max(varmapa_,varmapa,varmapa);
//			Mat canny_,canny__;
//			Canny( _image1_split[k], canny_, 20, 40, 3, 1 );
//			canny_.convertTo(canny__,CV_32FC1);
//			canny__/=varmapa*15;
//			max(canny,canny__,canny);
//
//		}
//
//		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//		imshow( "e", canny);
//		waitKey(0);
//
//	}






	// 131122 set 024
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		Vector< Vector<int> > cornerpoints;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//
//
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//
//		Mat sobelColor;
//		Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//
//		split (_bilateral3,_image1_split);
//
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//
//		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//		Mat canny[3];
//		Canny(_image1_split[0],canny[0],2,4);
//		Canny(_image1_split[1],canny[1],2,4);
//		Canny(_image1_split[2],canny[2],2,4);
//		bitwise_or(canny[0],canny[1],canny[1]);
//		bitwise_or(canny[1],canny[2],canny[2]);
//
//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", canny[2]);//thrCrCb[0] );
//		waitKey(0);
//		cvNica::LineTracker(canny[2],367,247);
//
//		Mat mergePos [8];
//		for (int k=0; k<=1; k++) {
//			for (int j=0; j<=3; j++) {
//				mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//		Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
//		for (int j=0; j<=3; j++) {
//			Mat varmap__[4],varmap_[4],varmap[4],varmapColor,ccanny[4];
//
//			for (int k=0; k<3; k++) {
//				Mat temp;
//
//				cvNica::CornerDetector(_image1_split[k],varmap_[k],j+41);
//				Canny(_image1_split[k],ccanny[k],70,120);
//				cvNica::CornerDetectorBasedOnEdge(ccanny[k],varmap__[k],j+40);
//
//
//				threshold(varmap_[k],varmap_[k],15,255,THRESH_BINARY);
//				bitwise_and(varmap_[k],varmap__[k],varmap[k]);
//
//			}
//
//
//			max(varmap[0],varmap[1],varmap[3]);
//			max(varmap[3],varmap[2],varmap[3]);
//			max(varmap__[0],varmap__[1],varmap__[3]);
//			max(varmap__[3],varmap__[2],varmap__[3]);
//
//
//
//			max(varmap[0],varmap[1],varmap[3]);
//			max(varmap[3],varmap[2],varmap[3]);
//
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap__[3],varmap[3]};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//			varmap4Merge += varmap[3];
//			varmap4Merge2 += varmap__[3];
//
//
//			cvNica::RGBhistogram(_bilateral3,varmap[3],cornerpoints,j+41,2);
//		}
//
//
//		if (cornerpoints.size()==0) continue;
//
//		int KK=3;
//		int tolerance=30;
//		int thresholdType=2;
//		Vector< Vector<int> > returnpoints=cvNica::kmeansWrapper(cornerpoints,KK);
//		Mat agg = Mat::zeros(size,CV_8UC1);
//		Mat kmColor[KK];
//		Mat akmColor[KK];
//		for (int kk=0;kk<KK;kk++){
//
//			Mat km,pp,app;
//			//km = cvNica::RGBThreshold(_bilateral3,returnpoints[kk][0],returnpoints[kk][1],returnpoints[kk][2],tolerance);
//			km = cvNica::RGBThreshold(_bilateral3,returnpoints[kk],tolerance,thresholdType);
//			pp = cvNica::RGBThresholdPointCC(km,cornerpoints,returnpoints[kk],tolerance,thresholdType);
//			app = cvNica::RGBThresholdPointCC2(pp,cornerpoints,returnpoints[kk],tolerance,thresholdType);
//			bitwise_or (app,agg,agg);
//			Mat kmColor_[3] = {pp,km-127,pp};
//			Mat akmColor_[3] = {app,km-127,app};
//			merge(kmColor_,3,kmColor[kk]);
//			merge(akmColor_,3,akmColor[kk]);
//		}
//
//		Mat agg_[3] = {agg,agg,agg};
//		Mat agg__; merge(agg_,3,agg__);
//
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
//
//
//		_homoInv = 255-varmap4Merge;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(varmap4Merge,_gray,_homoOverlay);
//		bitwise_or(varmap4Merge2,_gray,_homoOverlay3);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay2,_homoOverlay};
//		Mat _homoColor_2[3] = {_homoOverlay2,_homoOverlay3,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//		merge(_homoColor_2,3,_homoColor2);
//
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (varmap4Merge,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		_homoColor2.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//
//
//
//
//		kmColor[0].copyTo(mergePos[1]);
//		kmColor[1].copyTo(mergePos[2]);
//		kmColor[2].copyTo(mergePos[3]);
//		akmColor[0].copyTo(mergePos[5]);
//		akmColor[1].copyTo(mergePos[6]);
//		akmColor[2].copyTo(mergePos[7]);
//		agg__.copyTo(mergePos[4]);
//
//
//
//
//		imwrite(dir+"/set028/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//	}



// 140304
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 3;
//		int row = 2;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//
//		//Mat gradx(size,CV_8UC1);
//		//Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//
//		Mat sobelColor_[3];
//		Mat sobelColor;
//		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
//		Mat sobelOR = Mat::zeros(size,CV_8UC1);
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat __image1_split[3];
//		Mat __bilateral3 (size,CV_8UC3);
//		//_bilateral3 = _image1;
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		//medianBlur(_image1,_bilateral3,3);
//		int dilation_type = MORPH_RECT;
//		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//		//			//dilate(__Gray,__Gray,elementL);
//		//			//erode(__Gray,__Gray,elementL);
//
////		dilate(_image1,_bilateral3,elementL);
////		erode(_bilateral3,_bilateral3,elementL);
////		erode(_bilateral3,_bilateral3,elementL);
////		dilate(_bilateral3,_bilateral3,elementL);
//
//		split (_bilateral3,_image1_split);
//		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(__bilateral3,__bilateral3,3);
//		//medianBlur(__image1,__bilateral3,3);
//
////		dilate(__image1,__bilateral3,elementL);
////		erode(__bilateral3,__bilateral3,elementL);
////		erode(__bilateral3,__bilateral3,elementL);
////		dilate(__bilateral3,__bilateral3,elementL);
//		split (__bilateral3,__image1_split);
//
//		//split (_image1,_image1_split);
//		//split (__image1,__image1_split);
//
//
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		 //dilation_type = MORPH_ELLIPSE;
//		//int dilation_type = MORPH_RECT;
//			//elementL = getStructuringElement( dilation_type, Size( 25,25 ), Point( 12,12 ) );
//
//			float stdsum=.0;
//		for (int k=0; k<3; k++) {
//
//			Mat varmapa(size,CV_8UC1);
//					Mat varmapa_(size,CV_32FC1);
//					Mat varmapa__(size,CV_32FC1);
//
//			cvNica::VarianceFilter(_image1_split[k],varmapa_,7);
//
//			Mat canny_,canny__;
//
//			Canny( _image1_split[k], canny_, 30, 50, 3, 1 );
//			canny_.convertTo(canny__,CV_32FC1);
//
//			//erode(varmapa_,varmapa_,elementL);
//
//			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
//			float spsum = sum(sp32)[0]/size.width/size.height;
//			float spsqsum = sum(sp32.mul(sp32))[0];
//			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
//			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
////						imshow( "d", varmapa__/255);
////						waitKey(0);
//
//			//sqrt( varmapa__, varmapa_);
//
//			//threshold(varmapa_,varmapa,5,255,THRESH_BINARY_INV);
//			//max(varmapa_,varmapa,varmapa_);
//
//			std = (std<30)? 30:std;
//			//cv::pow(varmapa_,1.1,varmapa_);
//			stdsum += std;
//
//
//			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,8,255,THRESH_BINARY_INV);
//			max(varmapa_,varmapa,varmapa);
//
//
////			varmapa.convertTo(varmapa_,CV_8UC1);
////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
////			imshow( "c", varmapa_);
////
////			waitKey(0);
//
//			Mat sobelx(size,CV_32FC1);
//			Mat sobely(size,CV_32FC1);
//			Mat sobelxsq(size,CV_32FC1);
//			Mat sobelysq(size,CV_32FC1);
//			Sobel(_image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );
//
//
////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
////			imshow( "c", sobelx/255);
////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
////			imshow( "d", varmapa/255);
////			waitKey(0);
//
//
////			Mat __Gray,__Gray8;
////			cvNica::DifferenceOfVariance(_image1_split[k],__Gray);
////			//__Gray8.convertTo(__Gray,CV_8UC1);
////			threshold(__Gray,__Gray,0,255,THRESH_BINARY);
////			//Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
////			//dilate(__Gray,__Gray,elementL);
////			//erode(__Gray,__Gray,elementL);
////			//multiply(sobel8U2,(255-__Gray)/255,sobel8U);
////			__Gray=(255-__Gray)/255;
////
////
////
////			__Gray.convertTo(__Gray8,CV_32FC1);
////			namedWindow( "ze4", CV_WINDOW_AUTOSIZE );
////			imshow( "ze4", __Gray8);
////			waitKey(0);
//			sobelx/=varmapa/150;
//			sobelx=sobelx.mul(canny__/255);
//			//sobelx=sobelx.mul(__Gray8);
//			multiply(sobelx,sobelx,sobelxsq);
//
//			sobelxsqsum += sobelxsq*std;
//			//convertScaleAbs( sobelx, gradx );
//			Sobel(_image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
//			sobely/=varmapa/150;
//			sobely=sobely.mul(canny__/255);
//			//sobely=sobely.mul(__Gray8);
//			multiply(sobely,sobely,sobelysq);
//
//			sobelysqsum += sobelysq*std;
//
//
//
//			convertScaleAbs( sobelx, gradx );
//			convertScaleAbs( sobely, grady );
//			addWeighted( gradx, 0.5, grady, 0.5, 0, sobelColor_[k] );
//			Mat sobel8UU;
//			sobelColor_[k].convertTo(sobel8UU,CV_8UC1);
//			bitwise_and(sobel8UU,sobelAND,sobelAND);
//			bitwise_or(sobel8UU,sobelOR,sobelOR);
//			//convertScaleAbs( sobely, grady );
//
//		}
////		for (int k=0; k<3; k++) {
////
////			Mat varmapa(size,CV_8UC1);
////					Mat varmapa_(size,CV_32FC1);
////					Mat varmapa__(size,CV_32FC1);
////
////			cvNica::VarianceFilter(__image1_split[k],varmapa_,5);
////
////
////
////
////			//erode(varmapa_,varmapa_,elementL);
////
////			Mat sp32; __image1_split[k].convertTo(sp32,CV_32FC1);
////			float spsum = sum(sp32)[0]/size.width/size.height;
////			float spsqsum = sum(sp32.mul(sp32))[0];
////			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
////			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
//////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//////						imshow( "d", varmapa__/255);
//////						waitKey(0);
////
////			//sqrt( varmapa__, varmapa_);
////
////			//threshold(varmapa_,varmapa,5,255,THRESH_BINARY_INV);
////			//max(varmapa_,varmapa,varmapa_);
////
////			std = (std<30)? 30:std;
////			//cv::pow(varmapa_,1.1,varmapa_);
////			stdsum += std;
////
////
////			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
////			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
////			//threshold(varmapa_,varmapa,10,255,THRESH_BINARY_INV);
////			max(varmapa_,varmapa,varmapa);
////
////
//////			varmapa.convertTo(varmapa_,CV_8UC1);
//////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//////			imshow( "c", varmapa_);
//////
//////			waitKey(0);
////
////			Mat sobelx(size,CV_32FC1);
////			Mat sobely(size,CV_32FC1);
////			Mat sobelxsq(size,CV_32FC1);
////			Mat sobelysq(size,CV_32FC1);
////			Sobel(__image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );
////
////
//////			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//////			imshow( "c", sobelx/255);
//////			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//////			imshow( "d", varmapa/255);
//////			waitKey(0);
////
////			sobelx/=varmapa/85;
////			multiply(sobelx,sobelx,sobelxsq);
////
////			sobelxsqsum += sobelxsq*std;
////			//convertScaleAbs( sobelx, gradx );
////			Sobel(__image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
////			sobely/=varmapa/85;
////			multiply(sobely,sobely,sobelysq);
////
////			sobelysqsum += sobelysq*std;
////		}
//		sobelxsqsum/=stdsum;
//		sobelysqsum/=stdsum;
//		sqrt (sobelxsqsum,gradx);
//		sqrt (sobelysqsum,grady);
//
//		Mat canny2;Mat gradx2;Mat grady2;
//		gradx.convertTo(gradx2,CV_16S);
//		grady.convertTo(grady2,CV_16S);
//		Canny( _gray, canny2, 60, 120, 3, 1 );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
//		Point a1;
//		Mat matchtresultAcc;
//		Mat matchtresult;
//		Mat kernel1;
////		kernel1 = cvNica::kernels(98,a1);
////		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
////		threshold(matchtresult,matchtresult,0.63,1,THRESH_BINARY);
////		matchtresult.copyTo(matchtresultAcc);
////
////		kernel1 = cvNica::kernels(99,a1);
////		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
////		threshold(matchtresult,matchtresult,0.63,1,THRESH_BINARY);
////		matchtresultAcc += matchtresult;
////
////		kernel1 = cvNica::kernels(100,a1);
////		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
////		threshold(matchtresult,matchtresult,0.63,1,THRESH_BINARY);
////		matchtresultAcc += matchtresult;
////
////		kernel1 = cvNica::kernels(101,a1);
////		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
////		threshold(matchtresult,matchtresult,0.63,1,THRESH_BINARY);
////		matchtresultAcc += matchtresult;
//
//		int startIndex = 36;//98;//36;
//		kernel1 = cvNica::kernels(startIndex,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,0.7,1,THRESH_BINARY);
//		matchtresult.copyTo(matchtresultAcc);
//
//		kernel1 = cvNica::kernels(startIndex+1,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,0.7,1,THRESH_BINARY);
//		matchtresultAcc += matchtresult;
//
//		kernel1 = cvNica::kernels(startIndex+2,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,0.7,1,THRESH_BINARY);
//		matchtresultAcc += matchtresult;
//
//		kernel1 = cvNica::kernels(startIndex+3,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,0.7,1,THRESH_BINARY);
//		matchtresultAcc += matchtresult;
//
//
//
//
//
//		Point a2;
//		Mat matchtresultAcc2;
//		Mat matchtresult2;
//		Mat kernel2;
//		Mat canny232F;
//		canny2.convertTo(canny232F,CV_32FC1);
//		kernel2 = cvNica::kernels(startIndex,a2)*255;
//		matchTemplate(canny232F,kernel2,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,0.7,1,THRESH_BINARY);
//		matchtresult2.copyTo(matchtresultAcc2);
//
//		kernel2 = cvNica::kernels(startIndex+1,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,0.7,1,THRESH_BINARY);
//		matchtresultAcc2 += matchtresult2;
//
//		kernel2 = cvNica::kernels(startIndex+2,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,0.7,1,THRESH_BINARY);
//		matchtresultAcc2 += matchtresult2;
//
//		kernel2 = cvNica::kernels(startIndex+3,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,0.7,1,THRESH_BINARY);
//		matchtresultAcc2 += matchtresult2;
//
//
//
//
//
//
//
//		//
////		namedWindow( "ze4", CV_WINDOW_AUTOSIZE );
////		imshow( "ze4", 255-__Gray);
////		waitKey(0);
//
////		Mat sobelbinary=sobel>0;
////		cvNica::MeanFilter(sobelbinary,sobelbinary,5);
////				namedWindow( "ze4", CV_WINDOW_AUTOSIZE );
////				imshow( "ze4", sobelbinary);
////				waitKey(0);
////		void MeanFilter(
////				InputArray 						_src,
////				OutputArray						_dst,
////				int								size)
//
//		merge(sobelColor_,3,sobelColor);
////		Mat _sobel;
////		cvNica::MeanFilter(sobel,_sobel,7);
////
////		threshold(_sobel,_sobel,80,255,THRESH_BINARY_INV);
////		namedWindow( "e", CV_WINDOW_AUTOSIZE );
////				imshow( "e", _sobel/255);
////				waitKey(0);
////		sobel=sobel.mul(_sobel)/255;
//		Mat sobel8U2;Mat sobel8U;
//
//
//		/*
//		Mat _sobelx, _sobely;
//		Mat sobell,sobell32;
//		Sobel(_gray,_sobelx,CV_32F,1,0,5,1, 0, BORDER_REPLICATE );
//		Sobel(_gray,_sobely,CV_32F,0,1,5,1, 0, BORDER_REPLICATE );
//		convertScaleAbs( _sobelx, _sobelx );
//		convertScaleAbs( _sobely, _sobely );
//		addWeighted( _sobelx, 0.5, _sobely, 0.5, 0, sobell );
//					double mmin, mmax;
////
//
////
//		//GaussianBlur(sobel,sobelOR,Size(3,3),1);
//
//					//sobel.copyTo(sobell);
//					minMaxIdx(sobell,&mmin,&mmax);
//					cout<<": "<<mmin<<" "<<mmax<<endl;
//					//sobell/=mmax;
//					//sobell=255-sobell;
//		//dilate(1-sobell,sobell,elementL);
//		erode(sobell,sobell,elementL);
//		dilate(sobell,sobell,elementL);
////		namedWindow( "e", CV_WINDOW_AUTOSIZE );
////		imshow( "e", sobell);
////		waitKey(0);
//		sobell.convertTo(sobell32,CV_32FC1);
////		erode(sobelOR,sobelOR,elementL);
////		erode(sobelOR,sobelOR,elementL);
////
////		minMaxIdx(sobelOR,&mmin,&mmax);
////							cout<<": "<<mmin<<" "<<mmax<<endl;
////
////				namedWindow( "e", CV_WINDOW_AUTOSIZE );
////				imshow( "e", (255-sobell32*2)/256);
////				waitKey(0);
//		multiply(sobel, (255-sobell32*2.5)/256, sobel);
//
//*/
//
//		sobel.convertTo(sobel8U,CV_8UC1);
//
////
////		Mat __Gray,__Gray8;
////		cvNica::DifferenceOfVariance(_gray,__Gray8);
////		__Gray8.convertTo(__Gray,CV_8UC1);
////		threshold(__Gray,__Gray,0,255,THRESH_BINARY);
////		//Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
////		dilate(__Gray,__Gray,elementL);
////		erode(__Gray,__Gray,elementL);
////
////		multiply(sobel8U2,(255-__Gray)/255,sobel8U);
//
//
//
//		//sobelOR/=25;
//		Mat sobel222 = sobel/150;
//		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
//		//				imshow( "a", sobel222);
//		CvMat pSrc = sobel222;
//		CvMat *pDst = cvCreateMat(size.height, size.width, CV_32FC1);;
//
//		cvNica::MorphologicalThinning(&pSrc,pDst);
//		Mat dm = cv::Mat(pDst, true);
//
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//
//		Mat varmapa(size,CV_8UC1);
//		Mat varmapa_(size,CV_32FC1);
//		cvNica::VarianceFilter(_gray,varmapa_,5);
//
//		varmapa_.convertTo(varmapa,CV_8UC1);
//		//erode(varmapa,varmapa,elementL);
//
//
//				//sobel
//		Mat canny3(size,CV_8UC1);
//				Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//				Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//				cvNica::Canny2( _gray, sobelx,sobely, canny3, 60, 120, 3, 1 );
//				//cvNica::CannyEdge( _gray.data, size.width, size.height, 20,40, canny3.data );
//				//Canny( _gray, canny3, 20,40, 3,1 );
//				convertScaleAbs( sobelx, gradx );
//
//				convertScaleAbs( sobely, grady );
//				addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
//
//
//				//Canny( _gray, canny3, 60, 120, 3, false );
//
//				//dilate(canny3,canny3,elementL);
//				//erode(canny3,canny3,elementL);
//
//				//erode(sobel8U,sobel8U,elementL);
//
//
//
////				namedWindow( "a", CV_WINDOW_AUTOSIZE );
////								imshow( "a", sobelOR);
////				namedWindow( "b", CV_WINDOW_AUTOSIZE );
////				imshow( "b", sobelAND);
//			    vector< vector<Point> > contours;
//			    //findContours(sobel8U, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//
//			    // you could also reuse img1 here
//			   // Mat mask = Mat::zeros(size, CV_8UC1);
//
//			    // CV_FILLED fills the connected components found
//			    //drawContours(mask, contours, -1, Scalar(255), CV_FILLED);
////				namedWindow( "b", CV_WINDOW_AUTOSIZE );
////				imshow( "b", mask);
////		namedWindow( "c", CV_WINDOW_AUTOSIZE );
////		imshow( "c", canny2);
////		namedWindow( "d", CV_WINDOW_AUTOSIZE );
////		imshow( "d", sobel);
//
//
//				Mat mergePos [col*row];
//				for (int k=0; k<row; k++) {
//					for (int j=0; j<col; j++) {
//						mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//					}
//				}
//				Mat sobel8URGB;
//				Mat sobelRGB;
//				Mat canny2RGB;
//				Mat __GrayRGB;
//				Mat matchtresultRGB;
//				Mat matchtresult2RGB;
//				Mat matchtresult8U;
//				Mat matchtresult28U;
//				cvtColor(sobel8U,sobel8URGB,CV_GRAY2RGB);
//				cvtColor(sobel,sobelRGB,CV_GRAY2RGB);
//				cvtColor(canny2,canny2RGB,CV_GRAY2RGB);
//				matchtresultAcc*=255;
//				matchtresultAcc2*=255;
//				matchtresultAcc.convertTo(matchtresult8U,CV_8UC1);
//				matchtresultAcc2.convertTo(matchtresult28U,CV_8UC1);
//
//				Mat matchtresultlarge(size,CV_8UC1);
//				Mat matchtresult2large(size,CV_8UC1);
//
//				Mat matchtresulttemp = Mat(matchtresultlarge, Rect(3, 3, matchtresult.cols, matchtresult.rows));
//				Mat matchtresult2temp = Mat(matchtresult2large, Rect(3, 3, matchtresult2.cols, matchtresult2.rows));
//				matchtresult8U.copyTo(matchtresulttemp);
//				matchtresult28U.copyTo(matchtresult2temp);
//
//
//				cvtColor(matchtresultlarge,matchtresultRGB,CV_GRAY2RGB);
//				cvtColor(matchtresult2large,matchtresult2RGB,CV_GRAY2RGB);
//				//cvtColor(255-__Gray,__GrayRGB,CV_GRAY2RGB);
////				namedWindow( "c", CV_WINDOW_AUTOSIZE );
////				imshow( "c", matchtresultRGB);
////				namedWindow( "d", CV_WINDOW_AUTOSIZE );
////				imshow( "d", matchtresult2RGB);
////				namedWindow( "e", CV_WINDOW_AUTOSIZE );
////				imshow( "e", sobel);
////				waitKey(0);
//
////				cout<<matchtresultRGB.cols<<endl;
////				cout<<matchtresultRGB.rows<<endl; /// size not fit
//
//				dilate(matchtresultlarge,matchtresultlarge,elementL);
//				dilate(matchtresult2large,matchtresult2large,elementL);
//
//				Mat matchtresultmerged_[3] = {_gray-matchtresultlarge,_gray-matchtresultlarge,_gray+matchtresultlarge};
//				Mat matchtresultmerged;
//				merge(matchtresultmerged_,3,matchtresultmerged);
//
//				Mat matchtresultmerged2_[3] = {_gray-matchtresult2large,_gray-matchtresult2large,_gray+matchtresult2large};
//				Mat matchtresultmerged2;
//				merge(matchtresultmerged2_,3,matchtresultmerged2);
//
//				//_image1.copyTo(mergePos[0]);
//				canny2RGB.copyTo(mergePos[1]);
//				matchtresultRGB.copyTo(mergePos[5]);
//				matchtresultmerged.copyTo(mergePos[3]);
//				//sobelRGB.copyTo(mergePos[4]);
//				sobel8URGB.copyTo(mergePos[4]);
//				matchtresult2RGB.copyTo(mergePos[2]);
//				matchtresultmerged2.copyTo(mergePos[0]);
//
//				imwrite(dir+"/set036/"+files[i]+".png",merged);
//				cout<<files[i]<<endl;
//				//_homoColor2.copyTo(mergePos[3]);
//				//_homoThresholdColor.copyTo(mergePos[2]);
//
///*
//
//
//
//		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//
//		Mat mergePos [col*row];
//		for (int k=0; k<row; k++) {
//			for (int j=0; j<col; j++) {
//				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//		Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
//		for (int j=0; j<=3; j++) {
//			Mat varmap_[4],varmap[4],varmapColor;
//
//			for (int k=0; k<3; k++) { // apply to each color channel
//				Mat temp;
//
//				//if (j<2)
//					cvNica::CornerDetector(_image1_split[k],varmap_[k],j+45);
//
//				threshold(varmap_[k],varmap[k],15,255,THRESH_BINARY);
//
//			}
//
//
//			max(varmap[0],varmap[1],varmap[3]);
//			max(varmap[3],varmap[2],varmap[3]);
//
//
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap[3],varmap[3]};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//			varmap4Merge += varmap[3];
//			//varmap4Merge2 += varmap__[3];
//			varmapColor.copyTo(mergePos[4+j]);
//
//		}
//
//
//
//
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
//
//
//		_homoInv = 255-varmap4Merge;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(varmap4Merge,_gray,_homoOverlay);
//		bitwise_or(varmap4Merge2,_gray,_homoOverlay3);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay,_homoOverlay};
//		Mat _homoColor_2[3] = {_homoOverlay2,_homoOverlay3,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//		merge(_homoColor_2,3,_homoColor2);
//
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (varmap4Merge,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		//_homoColor2.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//
//
//		imwrite(dir+"/set029/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//		*/
//	}



//140304_2
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 3;
//		int row = 2;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//
//		//Mat gradx(size,CV_8UC1);
//		//Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//
//		Mat sobelColor_[3];
//		Mat sobelColor;
//		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
//		Mat sobelOR = Mat::zeros(size,CV_8UC1);
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat __image1_split[3];
//		Mat __bilateral3 (size,CV_8UC3);
//		//_bilateral3 = _image1;
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		//medianBlur(_image1,_bilateral3,3);
//		int dilation_type = MORPH_RECT;
//		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//		//			//dilate(__Gray,__Gray,elementL);
//		//			//erode(__Gray,__Gray,elementL);
//
//	//		dilate(_image1,_bilateral3,elementL);
//	//		erode(_bilateral3,_bilateral3,elementL);
//	//		erode(_bilateral3,_bilateral3,elementL);
//	//		dilate(_bilateral3,_bilateral3,elementL);
//
//		split (_bilateral3,_image1_split);
//		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(__bilateral3,__bilateral3,3);
//		//medianBlur(__image1,__bilateral3,3);
//
//	//		dilate(__image1,__bilateral3,elementL);
//	//		erode(__bilateral3,__bilateral3,elementL);
//	//		erode(__bilateral3,__bilateral3,elementL);
//	//		dilate(__bilateral3,__bilateral3,elementL);
//		split (__bilateral3,__image1_split);
//
//		//split (_image1,_image1_split);
//		//split (__image1,__image1_split);
//
//
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		 //dilation_type = MORPH_ELLIPSE;
//		//int dilation_type = MORPH_RECT;
//			//elementL = getStructuringElement( dilation_type, Size( 25,25 ), Point( 12,12 ) );
//
//			float stdsum=.0;
//		for (int k=0; k<3; k++) {
//
//			Mat varmapa(size,CV_8UC1);
//					Mat varmapa_(size,CV_32FC1);
//					Mat varmapa__(size,CV_32FC1);
//
//			cvNica::VarianceFilter(_image1_split[k],varmapa_,7);
//
//			Mat canny_,canny__;
//
//			Canny( _image1_split[k], canny_, 30, 50, 3, 1 );
//			canny_.convertTo(canny__,CV_32FC1);
//
//			//erode(varmapa_,varmapa_,elementL);
//
//			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
//			float spsum = sum(sp32)[0]/size.width/size.height;
//			float spsqsum = sum(sp32.mul(sp32))[0];
//			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
//			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
//
//			std = (std<30)? 30:std;
//			//cv::pow(varmapa_,1.1,varmapa_);
//			stdsum += std;
//
//
//			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,8,255,THRESH_BINARY_INV);
//			max(varmapa_,varmapa,varmapa);
//
//
//			Mat sobelx(size,CV_32FC1);
//			Mat sobely(size,CV_32FC1);
//			Mat sobelxsq(size,CV_32FC1);
//			Mat sobelysq(size,CV_32FC1);
//			Sobel(_image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );
//
//
//			sobelx/=varmapa/150;
//			//sobelx=sobelx.mul(canny__/255);
//			//sobelx=sobelx.mul(__Gray8);
//			multiply(sobelx,sobelx,sobelxsq);
//
//			sobelxsqsum += sobelxsq*std;
//			//convertScaleAbs( sobelx, gradx );
//			Sobel(_image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
//			sobely/=varmapa/150;
//			//sobely=sobely.mul(canny__/255);
//			//sobely=sobely.mul(__Gray8);
//			multiply(sobely,sobely,sobelysq);
//
//			sobelysqsum += sobelysq*std;
//
//
//
//			convertScaleAbs( sobelx, gradx );
//			convertScaleAbs( sobely, grady );
//			addWeighted( gradx, 0.5, grady, 0.5, 0, sobelColor_[k] );
//			Mat sobel8UU;
//			sobelColor_[k].convertTo(sobel8UU,CV_8UC1);
//			bitwise_and(sobel8UU,sobelAND,sobelAND);
//			bitwise_or(sobel8UU,sobelOR,sobelOR);
//			//convertScaleAbs( sobely, grady );
//
//		}
//
//		sobelxsqsum/=stdsum;
//		sobelysqsum/=stdsum;
//		sqrt (sobelxsqsum,gradx);
//		sqrt (sobelysqsum,grady);
//
//		Mat canny2;Mat gradx2;Mat grady2;
//		gradx.convertTo(gradx2,CV_16S);
//		grady.convertTo(grady2,CV_16S);
//		Canny( _gray, canny2, 60, 120, 3, 1 );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
//		Point a1;
//		Mat matchtresultAcc;
//		Mat matchtresult;
//		Mat kernel1;
//		double thrval=0.7;
//		int startIndex = 36;//98;//36;
//		kernel1 = cvNica::kernels(startIndex,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		matchtresult.copyTo(matchtresultAcc);
//
//		kernel1 = cvNica::kernels(startIndex+1,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		matchtresultAcc += matchtresult;
//
//		kernel1 = cvNica::kernels(startIndex+2,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		matchtresultAcc += matchtresult;
//
//		kernel1 = cvNica::kernels(startIndex+3,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		matchtresultAcc += matchtresult;
//
//
//
//
//
//		Point a2;
//		Mat matchtresultAcc2;
//		Mat matchtresult2;
//		Mat kernel2;
//		Mat canny232F;
//		canny2.convertTo(canny232F,CV_32FC1);
//		kernel2 = cvNica::kernels(startIndex,a2)*255;
//		matchTemplate(canny232F,kernel2,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		matchtresult2.copyTo(matchtresultAcc2);
//
//		kernel2 = cvNica::kernels(startIndex+1,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		matchtresultAcc2 += matchtresult2;
//
//		kernel2 = cvNica::kernels(startIndex+2,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		matchtresultAcc2 += matchtresult2;
//
//		kernel2 = cvNica::kernels(startIndex+3,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		matchtresultAcc2 += matchtresult2;
//
//
//
//
//		merge(sobelColor_,3,sobelColor);
//
//		Mat sobel8U2;Mat sobel8U;
//
//
//
//
//		sobel.convertTo(sobel8U,CV_8UC1);
//
//
//		Mat sobel222 = sobel/150;
//		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
//		//				imshow( "a", sobel222);
//		CvMat pSrc = sobel222;
//		CvMat *pDst = cvCreateMat(size.height, size.width, CV_32FC1);;
//
//		cvNica::MorphologicalThinning(&pSrc,pDst);
//		Mat dm = cv::Mat(pDst, true);
//
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//
//		Mat varmapa(size,CV_8UC1);
//		Mat varmapa_(size,CV_32FC1);
//		cvNica::VarianceFilter(_gray,varmapa_,5);
//
//		varmapa_.convertTo(varmapa,CV_8UC1);
//
//		Mat canny3(size,CV_8UC1);
//		Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
//		Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
//		cvNica::Canny2( _gray, sobelx,sobely, canny3, 60, 120, 3, 1 );
//
//		convertScaleAbs( sobelx, gradx );
//
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
//
//
//		Mat mergePos [col*row];
//		for (int k=0; k<row; k++) {
//			for (int j=0; j<col; j++) {
//				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//			}
//		}
//		Mat sobel8URGB;
//		Mat sobelRGB;
//		Mat canny2RGB;
//		Mat __GrayRGB;
//		Mat matchtresultRGB;
//		Mat matchtresult2RGB;
//		Mat matchtresult8U;
//		Mat matchtresult28U;
//		cvtColor(sobel8U,sobel8URGB,CV_GRAY2RGB);
//		cvtColor(sobel,sobelRGB,CV_GRAY2RGB);
//		cvtColor(canny2,canny2RGB,CV_GRAY2RGB);
//		matchtresultAcc*=255;
//		matchtresultAcc2*=255;
//		matchtresultAcc.convertTo(matchtresult8U,CV_8UC1);
//		matchtresultAcc2.convertTo(matchtresult28U,CV_8UC1);
//
//		Mat matchtresultlarge(size,CV_8UC1);
//		Mat matchtresult2large(size,CV_8UC1);
//
//		Mat matchtresulttemp = Mat(matchtresultlarge, Rect(3, 3, matchtresult.cols, matchtresult.rows));
//		Mat matchtresult2temp = Mat(matchtresult2large, Rect(3, 3, matchtresult2.cols, matchtresult2.rows));
//		matchtresult8U.copyTo(matchtresulttemp);
//		matchtresult28U.copyTo(matchtresult2temp);
//
//		dilate(matchtresultlarge,matchtresultlarge,elementL);
//		dilate(matchtresult2large,matchtresult2large,elementL);
//		dilate(matchtresultlarge,matchtresultlarge,elementL);
//		dilate(matchtresult2large,matchtresult2large,elementL);
//
//		cvtColor(matchtresultlarge,matchtresultRGB,CV_GRAY2RGB);
//		cvtColor(matchtresult2large,matchtresult2RGB,CV_GRAY2RGB);
//		//cvtColor(255-__Gray,__GrayRGB,CV_GRAY2RGB);
//	//				namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	//				imshow( "c", matchtresultRGB);
//	//				namedWindow( "d", CV_WINDOW_AUTOSIZE );
//	//				imshow( "d", matchtresult2RGB);
//	//				namedWindow( "e", CV_WINDOW_AUTOSIZE );
//	//				imshow( "e", sobel);
//	//				waitKey(0);
//
//	//				cout<<matchtresultRGB.cols<<endl;
//	//				cout<<matchtresultRGB.rows<<endl; /// size not fit
//
//		bitwise_and(sobel8URGB,matchtresultRGB,matchtresultRGB);
//		bitwise_and(canny2RGB,matchtresult2RGB,matchtresult2RGB);
//
//
//
//		cvtColor(matchtresultRGB,matchtresultlarge,CV_RGB2GRAY);
//		cvtColor(matchtresult2RGB,matchtresult2large,CV_RGB2GRAY);
//
//		dilate(matchtresultlarge,matchtresultlarge,elementL);
//		dilate(matchtresult2large,matchtresult2large,elementL);
//
//		Mat matchtresultmerged_[3] = {_gray-matchtresultlarge,_gray-matchtresultlarge,_gray+matchtresultlarge};
//		Mat matchtresultmerged;
//		merge(matchtresultmerged_,3,matchtresultmerged);
//
//		Mat matchtresultmerged2_[3] = {_gray-matchtresult2large,_gray-matchtresult2large,_gray+matchtresult2large};
//		Mat matchtresultmerged2;
//		merge(matchtresultmerged2_,3,matchtresultmerged2);
//
//		//_image1.copyTo(mergePos[0]);
//
//
//
//
//		matchtresultmerged.copyTo(mergePos[3]);
//		sobel8URGB.copyTo(mergePos[4]);
//		matchtresultRGB.copyTo(mergePos[5]);
//
//		matchtresultmerged2.copyTo(mergePos[0]);
//		canny2RGB.copyTo(mergePos[1]);
//		matchtresult2RGB.copyTo(mergePos[2]);
//
//		imwrite(dir+"/set039/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//		//_homoColor2.copyTo(mergePos[3]);
//		//_homoThresholdColor.copyTo(mergePos[2]);
//
//
//	}


//140304_3 MD
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 3;
//		int row = 2;
//
//		Mat _image = imread( dir+"/"+files[i], -1 );
//		Size size = _image.size();
//		Mat _bilateral3 (size,CV_8UC3);
//
//		//_bilateral3 = _image1;
//		bilateralFilter (_image, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		Mat __bilateral3_split[3];
//		Mat _image_split[3];
//		Mat _DoG_split[3];
//		Mat _DoG;
//		split (_image,_image_split);
//		split (_bilateral3,__bilateral3_split);
//		Mat dst;
//		cvNica::FourierLaplacian(_image_split[1],dst);
//		Mat dst2;
//		 Laplacian(_image_split[1], dst2, CV_8U,3,
//				 1,128);
//
//		Mat maxMap;
//		Mat minMap;
//		int dilation_type = MORPH_CROSS;
//		Mat elementL = getStructuringElement( dilation_type, Size( 21,1 ), Point( 10,0 ) );
//
//		dilate (dst2,maxMap,elementL);
//		erode (dst2,minMap,elementL);
//		Mat maxMinDiff = maxMap-minMap;
//
//
//
//		for (int k = 0; k<3; k++) {
//			cvNica::DoG(_image_split[k],_DoG_split[k],0.2,1,-2,0,0,0,0);
//		}
//
//		merge(_DoG_split,3,_DoG);
//					namedWindow( "a", CV_WINDOW_AUTOSIZE );
//					imshow( "a", maxMinDiff);
//					namedWindow( "b", CV_WINDOW_AUTOSIZE );
//					imshow( "b", dst2);
//
//
//					namedWindow( "c", CV_WINDOW_AUTOSIZE );
//					imshow( "c", _image_split[0]);
//					namedWindow( "d", CV_WINDOW_AUTOSIZE );
//					imshow( "d", _DoG_split[1]);
//					namedWindow( "e", CV_WINDOW_AUTOSIZE );
//					imshow( "e", _DoG_split[2]);
//
//					waitKey(0);
//
//	//				cout<<matchtresultRGB.cols<<endl;
//	//				cout<<matchtresultRGB.rows<<endl; /// size not fit
//
//
//
//	}


	int kd=5;

	for (unsigned int i = 0;i < files.size();i++) {

		int col = 2;
		int row = 2;

		Mat _image = imread( dir+"/"+files[i], -1 );
		Size size = _image.size();
		Mat _bilateral3 (size,CV_8UC3);
		Mat merged(_image.rows*row, _image.cols*col, CV_8UC1);
		//_bilateral3 = _image1;
		bilateralFilter (_image, _bilateral3 , kd, kd*2, kd/2 );
		medianBlur(_bilateral3,_bilateral3,3);
		Mat __bilateral3_split[3];
		Mat _image_split[3];
		Mat _DoG_split[3];
		Mat _DoG;
		split (_image,_image_split);
		split (_bilateral3,__bilateral3_split);
		//Mat dst;
		//cvNica::FourierLaplacian(_image_split[1],dst);

		Mat dst2 = Mat::zeros(size,CV_8UC1);
		Mat ang = Mat::zeros(size,CV_8UC1);
		Mat ang2 = Mat::zeros(size,CV_8UC1);
		Mat sobel = Mat::zeros(size,CV_8UC1);



	//						namedWindow( "e", CV_WINDOW_AUTOSIZE );
	//						imshow( "e", corrcoefmap);
	//waitKey(0);
		for(int j=0;j<3;j++) {

			Mat dst2_;
			Laplacian(_image_split[j], dst2_, CV_8U,5,
					 0.025,128);

			Mat maxMap_;
			Mat minMap_;
			Mat ang_;
			Mat ang2_;
			int dilation_type = MORPH_RECT;
			Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

			dilate (dst2_,maxMap_,elementL);
			erode (dst2_,minMap_,elementL);
			Mat maxMinDiff_ = maxMap_-minMap_;

			cvNica::VarianceMap(_image_split[j],ang_,-3);

			cvNica::VarianceMap(__bilateral3_split[j],ang2_,-3);
			normalize(ang_, ang_, 0, 255, NORM_MINMAX, CV_8UC1);
			normalize(ang2_, ang2_, 0, 255, NORM_MINMAX, CV_8UC1);
			max(dst2,dst2_,dst2);
			max(ang,ang_,ang);
			max(ang2,ang2_,ang2);
	//
	//		cvNica::VarianceMap(_image_split[j],ang_,-1);
	//		cvNica::VarianceMap(__bilateral3_split[j],ang2_,-1);
	//		max(ang,ang_,ang);
	//		max(ang2,ang2_,ang2);


			Mat sobelx;
			Mat sobely;
			Mat gradx,grady;
			Mat sobel_;
	//		Sobel(_image_split[j],sobelx,CV_32F,1,0,1,1, 0, BORDER_DEFAULT );
			//Sobel(_image_split[j],sobely,CV_32F,0,1,1,1, 0, BORDER_DEFAULT );
			Sobel(_image_split[j],sobelx,CV_32F,1,0,3,1, 0, BORDER_REPLICATE );
			Sobel(_image_split[j],sobely,CV_32F,0,1,3,1, 0, BORDER_REPLICATE );

			  convertScaleAbs( sobelx, gradx);

			  convertScaleAbs( sobely, grady);
			//convertScaleAbs( sobely, grady );
			addWeighted( gradx, 0.5, grady, 0.5, 0, sobel_ );


			max(sobel,sobel_,sobel);
		}

		for (int k = 0; k<3; k++) {
			cvNica::DoG(_image_split[k],_DoG_split[k],0.2,1,-2,0,0,0,0);
		}


				Mat mergePos [col*row];
				for (int k=0; k<row; k++) {
					for (int j=0; j<col; j++) {
						mergePos[j+k*col] = Mat(merged, Rect(_image.cols*(j%col), _image.rows*((int)(j/col)+k), _image.cols, _image.rows));
					}
				}


				//equalizeHist(ang,ang);
				//equalizeHist(ang2,ang2);

				normalize(sobel, sobel, 0, 255, NORM_MINMAX, CV_8UC1);
				normalize(ang, ang, 0, 255, NORM_MINMAX, CV_8UC1);
				normalize(ang2, ang2, 0, 255, NORM_MINMAX, CV_8UC1);

				Mat corrcoefmap,corrcoefmap_;
				cvNica::CorrCoefMap3(_image,corrcoefmap);
				corrcoefmap*=255;
				corrcoefmap.convertTo( corrcoefmap_,CV_8UC1);
				copyMakeBorder( corrcoefmap_, corrcoefmap_, 1, 1, 1, 1, BORDER_CONSTANT, 0 );


				Mat corrcoefmap2,corrcoefmap2_;
				cvNica::CorrCoefMap4(_image,corrcoefmap2);
				corrcoefmap2*=255;
				corrcoefmap2.convertTo( corrcoefmap2_,CV_8UC1);
//				copyMakeBorder( corrcoefmap2_, corrcoefmap2_, 1, 1, 1, 1, BORDER_CONSTANT, 0 );

				Mat afd234;
				cvNica::SWT(_image,afd234);


				sobel.copyTo(mergePos[0]);
				ang.copyTo(mergePos[1]);
				corrcoefmap_.copyTo(mergePos[3]);
				//corrcoefmap2_.copyTo(mergePos[2]);
								namedWindow( "e", CV_WINDOW_AUTOSIZE );
								imshow( "e", corrcoefmap2_);

		Mat dfad;


								distanceTransform(_image_split[0],dfad, CV_DIST_L2, 5);
										namedWindow( "f", CV_WINDOW_AUTOSIZE );
							imshow( "f",_image_split[0]);

		merge(_DoG_split,3,_DoG);

		//imwrite(dir+"/set049/"+files[i]+".png",merged);
		//		cout<<files[i]<<endl;

	//	namedWindow( "d", CV_WINDOW_AUTOSIZE );
	//			imshow( "d", sobel);
	//					namedWindow( "e", CV_WINDOW_AUTOSIZE );
	//					imshow( "e", ang);



	//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
	//				imshow( "c", maxMap);
	//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//				imshow( "b", minMap);
	//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
	//				imshow( "a", maxMinDiff/2);

	//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//				imshow( "b", dst2);
	//
	//
	//				namedWindow( "c", CV_WINDOW_AUTOSIZE );
	//				imshow( "c", _image_split[0]);
	//				namedWindow( "d", CV_WINDOW_AUTOSIZE );
	//				imshow( "d", _DoG_split[1]);
	//				namedWindow( "e", CV_WINDOW_AUTOSIZE );
	//				imshow( "e", _DoG_split[2]);

					waitKey(0);

	//				cout<<matchtresultRGB.cols<<endl;
	//				cout<<matchtresultRGB.rows<<endl; /// size not fit



	}

#ifdef t140311set048
	int kd=5;

	for (unsigned int i = 0;i < files.size();i++) {

		int col = 2;
		int row = 2;

		Mat _image = imread( dir+"/"+files[i], -1 );
		Size size = _image.size();
		Mat _bilateral3 (size,CV_8UC3);
		Mat merged(_image.rows*row, _image.cols*col, CV_8UC1);
		//_bilateral3 = _image1;
		bilateralFilter (_image, _bilateral3 , kd, kd*2, kd/2 );
		medianBlur(_bilateral3,_bilateral3,3);
		Mat __bilateral3_split[3];
		Mat _image_split[3];
		Mat _DoG_split[3];
		Mat _DoG;
		split (_image,_image_split);
		split (_bilateral3,__bilateral3_split);
		//Mat dst;
		//cvNica::FourierLaplacian(_image_split[1],dst);

		Mat dst2 = Mat::zeros(size,CV_8UC1);
		Mat ang = Mat::zeros(size,CV_8UC1);
		Mat ang2 = Mat::zeros(size,CV_8UC1);
		Mat sobel = Mat::zeros(size,CV_8UC1);



	//						namedWindow( "e", CV_WINDOW_AUTOSIZE );
	//						imshow( "e", corrcoefmap);
	//waitKey(0);
		for(int j=0;j<3;j++) {

			Mat dst2_;
			Laplacian(_image_split[j], dst2_, CV_8U,5,
					 0.025,128);

			Mat maxMap_;
			Mat minMap_;
			Mat ang_;
			Mat ang2_;
			int dilation_type = MORPH_RECT;
			Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

			dilate (dst2_,maxMap_,elementL);
			erode (dst2_,minMap_,elementL);
			Mat maxMinDiff_ = maxMap_-minMap_;

			cvNica::VarianceMap(_image_split[j],ang_,-3);

			cvNica::VarianceMap(__bilateral3_split[j],ang2_,-3);
			normalize(ang_, ang_, 0, 255, NORM_MINMAX, CV_8UC1);
			normalize(ang2_, ang2_, 0, 255, NORM_MINMAX, CV_8UC1);
			max(dst2,dst2_,dst2);
			max(ang,ang_,ang);
			max(ang2,ang2_,ang2);
	//
	//		cvNica::VarianceMap(_image_split[j],ang_,-1);
	//		cvNica::VarianceMap(__bilateral3_split[j],ang2_,-1);
	//		max(ang,ang_,ang);
	//		max(ang2,ang2_,ang2);


			Mat sobelx;
			Mat sobely;
			Mat gradx,grady;
			Mat sobel_;
	//		Sobel(_image_split[j],sobelx,CV_32F,1,0,1,1, 0, BORDER_DEFAULT );
			//Sobel(_image_split[j],sobely,CV_32F,0,1,1,1, 0, BORDER_DEFAULT );
			Sobel(_image_split[j],sobelx,CV_32F,1,0,3,1, 0, BORDER_REPLICATE );
			Sobel(_image_split[j],sobely,CV_32F,0,1,3,1, 0, BORDER_REPLICATE );

			  convertScaleAbs( sobelx, gradx);

			  convertScaleAbs( sobely, grady);
			//convertScaleAbs( sobely, grady );
			addWeighted( gradx, 0.5, grady, 0.5, 0, sobel_ );


			max(sobel,sobel_,sobel);
		}

		for (int k = 0; k<3; k++) {
			cvNica::DoG(_image_split[k],_DoG_split[k],0.2,1,-2,0,0,0,0);
		}


				Mat mergePos [col*row];
				for (int k=0; k<row; k++) {
					for (int j=0; j<col; j++) {
						mergePos[j+k*col] = Mat(merged, Rect(_image.cols*(j%col), _image.rows*((int)(j/col)+k), _image.cols, _image.rows));
					}
				}


				//equalizeHist(ang,ang);
				//equalizeHist(ang2,ang2);

				normalize(sobel, sobel, 0, 255, NORM_MINMAX, CV_8UC1);
				normalize(ang, ang, 0, 255, NORM_MINMAX, CV_8UC1);
				normalize(ang2, ang2, 0, 255, NORM_MINMAX, CV_8UC1);

				Mat corrcoefmap,corrcoefmap_;
				cvNica::CorrCoefMap3(_image,corrcoefmap);
				corrcoefmap*=255;
				corrcoefmap.convertTo( corrcoefmap_,CV_8UC1);
				copyMakeBorder( corrcoefmap_, corrcoefmap_, 1, 1, 1, 1, BORDER_CONSTANT, 0 );


//				Mat corrcoefmap2,corrcoefmap2_;
//				cvNica::CorrCoefMap2(_image,corrcoefmap2);
//				corrcoefmap2*=255;
//				corrcoefmap2.convertTo( corrcoefmap2_,CV_8UC1);
//				copyMakeBorder( corrcoefmap2_, corrcoefmap2_, 1, 1, 1, 1, BORDER_CONSTANT, 0 );


				sobel.copyTo(mergePos[0]);
				ang.copyTo(mergePos[1]);
				corrcoefmap_.copyTo(mergePos[3]);
				//corrcoefmap2_.copyTo(mergePos[2]);
								namedWindow( "e", CV_WINDOW_AUTOSIZE );
								imshow( "e", corrcoefmap_);

		merge(_DoG_split,3,_DoG);

		imwrite(dir+"/set048/"+files[i]+".png",merged);
		//		cout<<files[i]<<endl;

	//	namedWindow( "d", CV_WINDOW_AUTOSIZE );
	//			imshow( "d", sobel);
	//					namedWindow( "e", CV_WINDOW_AUTOSIZE );
	//					imshow( "e", ang);



	//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
	//				imshow( "c", maxMap);
	//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//				imshow( "b", minMap);
	//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
	//				imshow( "a", maxMinDiff/2);

	//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//				imshow( "b", dst2);
	//
	//
	//				namedWindow( "c", CV_WINDOW_AUTOSIZE );
	//				imshow( "c", _image_split[0]);
	//				namedWindow( "d", CV_WINDOW_AUTOSIZE );
	//				imshow( "d", _DoG_split[1]);
	//				namedWindow( "e", CV_WINDOW_AUTOSIZE );
	//				imshow( "e", _DoG_split[2]);

					waitKey(0);

	//				cout<<matchtresultRGB.cols<<endl;
	//				cout<<matchtresultRGB.rows<<endl; /// size not fit



	}
#endif

#ifdef t140311set047
int kd=5;

for (unsigned int i = 0;i < files.size();i++) {

	int col = 2;
	int row = 2;

	Mat _image = imread( dir+"/"+files[i], -1 );
	Size size = _image.size();
	Mat _bilateral3 (size,CV_8UC3);
	Mat merged(_image.rows*row, _image.cols*col, CV_8UC1);
	//_bilateral3 = _image1;
	bilateralFilter (_image, _bilateral3 , kd, kd*2, kd/2 );
	medianBlur(_bilateral3,_bilateral3,3);
	Mat __bilateral3_split[3];
	Mat _image_split[3];
	Mat _DoG_split[3];
	Mat _DoG;
	split (_image,_image_split);
	split (_bilateral3,__bilateral3_split);
	//Mat dst;
	//cvNica::FourierLaplacian(_image_split[1],dst);

	Mat dst2 = Mat::zeros(size,CV_8UC1);
	Mat ang = Mat::zeros(size,CV_8UC1);
	Mat ang2 = Mat::zeros(size,CV_8UC1);
	Mat sobel = Mat::zeros(size,CV_8UC1);



//						namedWindow( "e", CV_WINDOW_AUTOSIZE );
//						imshow( "e", corrcoefmap);
//waitKey(0);
	for(int j=0;j<3;j++) {

		Mat dst2_;
		Laplacian(_image_split[j], dst2_, CV_8U,5,
				 0.025,128);

		Mat maxMap_;
		Mat minMap_;
		Mat ang_;
		Mat ang2_;
		int dilation_type = MORPH_RECT;
		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

		dilate (dst2_,maxMap_,elementL);
		erode (dst2_,minMap_,elementL);
		Mat maxMinDiff_ = maxMap_-minMap_;

		cvNica::VarianceMap(_image_split[j],ang_,-3);

		cvNica::VarianceMap(__bilateral3_split[j],ang2_,-3);
		normalize(ang_, ang_, 0, 255, NORM_MINMAX, CV_8UC1);
		normalize(ang2_, ang2_, 0, 255, NORM_MINMAX, CV_8UC1);
		max(dst2,dst2_,dst2);
		max(ang,ang_,ang);
		max(ang2,ang2_,ang2);
//
//		cvNica::VarianceMap(_image_split[j],ang_,-1);
//		cvNica::VarianceMap(__bilateral3_split[j],ang2_,-1);
//		max(ang,ang_,ang);
//		max(ang2,ang2_,ang2);


		Mat sobelx;
		Mat sobely;
		Mat gradx,grady;
		Mat sobel_;
//		Sobel(_image_split[j],sobelx,CV_32F,1,0,1,1, 0, BORDER_DEFAULT );
		//Sobel(_image_split[j],sobely,CV_32F,0,1,1,1, 0, BORDER_DEFAULT );
		Sobel(_image_split[j],sobelx,CV_32F,1,0,3,1, 0, BORDER_REPLICATE );
		Sobel(_image_split[j],sobely,CV_32F,0,1,3,1, 0, BORDER_REPLICATE );

		  convertScaleAbs( sobelx, gradx);

		  convertScaleAbs( sobely, grady);
		//convertScaleAbs( sobely, grady );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel_ );


		max(sobel,sobel_,sobel);
	}

	for (int k = 0; k<3; k++) {
		cvNica::DoG(_image_split[k],_DoG_split[k],0.2,1,-2,0,0,0,0);
	}


			Mat mergePos [col*row];
			for (int k=0; k<row; k++) {
				for (int j=0; j<col; j++) {
					mergePos[j+k*col] = Mat(merged, Rect(_image.cols*(j%col), _image.rows*((int)(j/col)+k), _image.cols, _image.rows));
				}
			}


			//equalizeHist(ang,ang);
			//equalizeHist(ang2,ang2);

			normalize(sobel, sobel, 0, 255, NORM_MINMAX, CV_8UC1);
			normalize(ang, ang, 0, 255, NORM_MINMAX, CV_8UC1);
			normalize(ang2, ang2, 0, 255, NORM_MINMAX, CV_8UC1);

			Mat corrcoefmap,corrcoefmap_;
			cvNica::CorrCoefMap(_image,corrcoefmap);
			corrcoefmap*=255;
			corrcoefmap.convertTo( corrcoefmap_,CV_8UC1);
			copyMakeBorder( corrcoefmap_, corrcoefmap_, 1, 1, 1, 1, BORDER_CONSTANT, 0 );


			Mat corrcoefmap2,corrcoefmap2_;
			cvNica::CorrCoefMap2(_image,corrcoefmap2);
			corrcoefmap2*=255;
			corrcoefmap2.convertTo( corrcoefmap2_,CV_8UC1);
			copyMakeBorder( corrcoefmap2_, corrcoefmap2_, 1, 1, 1, 1, BORDER_CONSTANT, 0 );


			sobel.copyTo(mergePos[0]);
			ang.copyTo(mergePos[1]);
			corrcoefmap_.copyTo(mergePos[3]);
			corrcoefmap2_.copyTo(mergePos[2]);
//							namedWindow( "e", CV_WINDOW_AUTOSIZE );
//							imshow( "e", corrcoefmap2_);

	merge(_DoG_split,3,_DoG);

	imwrite(dir+"/set047/"+files[i]+".png",merged);
	//		cout<<files[i]<<endl;

//	namedWindow( "d", CV_WINDOW_AUTOSIZE );
//			imshow( "d", sobel);
//					namedWindow( "e", CV_WINDOW_AUTOSIZE );
//					imshow( "e", ang);



//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//				imshow( "c", maxMap);
//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
//				imshow( "b", minMap);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a", maxMinDiff/2);

//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
//				imshow( "b", dst2);
//
//
//				namedWindow( "c", CV_WINDOW_AUTOSIZE );
//				imshow( "c", _image_split[0]);
//				namedWindow( "d", CV_WINDOW_AUTOSIZE );
//				imshow( "d", _DoG_split[1]);
//				namedWindow( "e", CV_WINDOW_AUTOSIZE );
//				imshow( "e", _DoG_split[2]);

				waitKey(0);

//				cout<<matchtresultRGB.cols<<endl;
//				cout<<matchtresultRGB.rows<<endl; /// size not fit



}
#endif


#ifdef t140311
	int kd=5;
	for (unsigned int i = 0;i < files.size();i++) {

		int col = 2;
		int row = 2;

		Mat _image1 = imread( dir+"/"+files[i], -1 );
		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
		Size size = _image1.size();
		Size size2 (_image1.cols*2,_image1.rows*2);


		Mat _gray (size,CV_8UC1),_grayRGB;

		Mat _bilateral (size,CV_8UC1);

		//Mat gradx(size,CV_8UC1);
		//Mat grady(size,CV_8UC1);
		Mat sobel(size,CV_8UC1);

		Mat sobelColor_[3];
		Mat sobelColor;
		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
		Mat sobelOR = Mat::zeros(size,CV_8UC1);
		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
		Mat _image1_split[3];
		Mat _bilateral3 (size,CV_8UC3);
		Mat __image1_split[3];
		Mat __bilateral3 (size,CV_8UC3);
		//_bilateral3 = _image1;
		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
		medianBlur(_bilateral3,_bilateral3,3);
		//medianBlur(_image1,_bilateral3,3);
		int dilation_type = MORPH_RECT;
		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
		//			//dilate(__Gray,__Gray,elementL);
		//			//erode(__Gray,__Gray,elementL);

	//		dilate(_image1,_bilateral3,elementL);
	//		erode(_bilateral3,_bilateral3,elementL);
	//		erode(_bilateral3,_bilateral3,elementL);
	//		dilate(_bilateral3,_bilateral3,elementL);

		split (_bilateral3,_image1_split);
		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
		medianBlur(__bilateral3,__bilateral3,3);
		//medianBlur(__image1,__bilateral3,3);

	//		dilate(__image1,__bilateral3,elementL);
	//		erode(__bilateral3,__bilateral3,elementL);
	//		erode(__bilateral3,__bilateral3,elementL);
	//		dilate(__bilateral3,__bilateral3,elementL);
		split (__bilateral3,__image1_split);

		//split (_image1,_image1_split);
		//split (__image1,__image1_split);


		cvtColor(_image1,_gray,CV_RGB2GRAY);
		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);

		Mat _imageF_;
		Mat _imageF[3];
		_grayRGB.convertTo(_imageF_,CV_32FC3);
		_imageF_/=255;
		split(_imageF_,_imageF);

		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
		Mat gradx(size,CV_32FC1);
		Mat grady(size,CV_32FC1);
		 //dilation_type = MORPH_ELLIPSE;
		//int dilation_type = MORPH_RECT;
			//elementL = getStructuringElement( dilation_type, Size( 25,25 ), Point( 12,12 ) );

			float stdsum=.0;
		for (int k=0; k<3; k++) {

			Mat varmapa(size,CV_8UC1);
					Mat varmapa_(size,CV_32FC1);
					Mat varmapa__(size,CV_32FC1);

			cvNica::VarianceFilter(_image1_split[k],varmapa_,7);

			Mat canny_,canny__;

			Canny( _image1_split[k], canny_, 30, 50, 3, 1 );
			canny_.convertTo(canny__,CV_32FC1);

			//erode(varmapa_,varmapa_,elementL);

			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
			float spsum = sum(sp32)[0]/size.width/size.height;
			float spsqsum = sum(sp32.mul(sp32))[0];
			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;

			std = (std<30)? 30:std;
			//cv::pow(varmapa_,1.1,varmapa_);
			stdsum += std;


			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
			//threshold(varmapa_,varmapa,8,255,THRESH_BINARY_INV);
			max(varmapa_,varmapa,varmapa);


			Mat sobelx(size,CV_32FC1);
			Mat sobely(size,CV_32FC1);
			Mat sobelxsq(size,CV_32FC1);
			Mat sobelysq(size,CV_32FC1);
			Sobel(_image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );


			sobelx/=varmapa/150;
			//sobelx=sobelx.mul(canny__/255);
			//sobelx=sobelx.mul(__Gray8);
			multiply(sobelx,sobelx,sobelxsq);

			sobelxsqsum += sobelxsq*std;
			//convertScaleAbs( sobelx, gradx );
			Sobel(_image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
			sobely/=varmapa/150;
			//sobely=sobely.mul(canny__/255);
			//sobely=sobely.mul(__Gray8);
			multiply(sobely,sobely,sobelysq);

			sobelysqsum += sobelysq*std;



			convertScaleAbs( sobelx, gradx );
			convertScaleAbs( sobely, grady );
			addWeighted( gradx, 0.5, grady, 0.5, 0, sobelColor_[k] );
			Mat sobel8UU;
			sobelColor_[k].convertTo(sobel8UU,CV_8UC1);
			bitwise_and(sobel8UU,sobelAND,sobelAND);
			bitwise_or(sobel8UU,sobelOR,sobelOR);
			//convertScaleAbs( sobely, grady );

		}

		sobelxsqsum/=stdsum;
		sobelysqsum/=stdsum;
		sqrt (sobelxsqsum,gradx);
		sqrt (sobelysqsum,grady);

		Mat canny2;Mat gradx2;Mat grady2;
		gradx.convertTo(gradx2,CV_16S);
		grady.convertTo(grady2,CV_16S);
		Canny( _gray, canny2, 60, 120, 3, 1 );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );


		Mat sobel8U2;Mat sobel8U;
		sobel.convertTo(sobel8U,CV_8UC1);

		Point a1;

		Mat matchtresult[4];
		Mat matchtresult_border[4];
		Mat kernel1;
		Mat matchtresultbinF;
		Mat matchtresultbin = Mat::zeros (size,CV_8UC1);
		double thrval=0.7;
		int startIndex = 36;//98;//36;

		for (int l=0; l<4; l++) {
			kernel1 = cvNica::kernels(startIndex+l,a1)*255;
			matchTemplate(sobel,kernel1,matchtresult[l],CV_TM_CCOEFF_NORMED);
			threshold(matchtresult[l],matchtresult[l],thrval,1,THRESH_BINARY);
			copyMakeBorder(matchtresult[l], matchtresult_border[l], 3, 3, 3, 3, BORDER_DEFAULT);
			matchtresult_border[l]*=255;
			matchtresult_border[l].convertTo(matchtresultbinF,CV_8UC1);
			matchtresult_border[l]/=255;
			bitwise_or(matchtresultbin,matchtresultbinF,matchtresultbin);
			dilate(matchtresult_border[l],matchtresult_border[l],elementL);
			dilate(matchtresult_border[l],matchtresult_border[l],elementL);
			matchtresult_border[l]= matchtresult_border[l].mul(sobel/255);
			dilate(matchtresult_border[l],matchtresult_border[l],elementL);
			//bitwise_and(sobel,matchtresult_border[l],matchtresult_border[l]);
//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//							imshow( "a", matchtresult_border[l]);
//							waitKey(0);
		}

		Mat matchtresultAcc_[3] = {_imageF[0]+matchtresult_border[0]+matchtresult_border[1]-matchtresult_border[2]-matchtresult_border[3],
									_imageF[1]-matchtresult_border[0]+matchtresult_border[1]+matchtresult_border[2]+matchtresult_border[3],
									_imageF[2]-matchtresult_border[0]-matchtresult_border[1]-matchtresult_border[2]+matchtresult_border[3]};
		Mat matchtresultAcc;



		merge(matchtresultAcc_,3,matchtresultAcc);
//		namedWindow( "a", CV_WINDOW_AUTOSIZE );
//						imshow( "a", matchtresultbin);
//						waitKey(0);

		Point a2;
		Mat matchtresult2[4];
		Mat matchtresult2_border[4];
		Mat kernel2;
		Mat canny232F;

		canny2.convertTo(canny232F,CV_32FC1);

		for (int l=0; l<4; l++) {
			kernel2 = cvNica::kernels(startIndex+l,a2)*255;
			matchTemplate(canny232F,kernel2,matchtresult2[l],CV_TM_CCOEFF_NORMED);
			threshold(matchtresult2[l],matchtresult2[l],thrval,1,THRESH_BINARY);
			copyMakeBorder(matchtresult2[l], matchtresult2_border[l], 3, 3, 3, 3, BORDER_DEFAULT);
			//matchtresult2_border[l] = matchtresult2_border[l].mul(canny232F);

			dilate(matchtresult2_border[l],matchtresult2_border[l],elementL);
			dilate(matchtresult2_border[l],matchtresult2_border[l],elementL);
			matchtresult2_border[l]=matchtresult2_border[l].mul(canny232F);
			dilate(matchtresult2_border[l],matchtresult2_border[l],elementL);



		}


		Mat matchtresultAcc2_[3] =  {_imageF[0]+matchtresult2_border[0]+matchtresult2_border[1]-matchtresult2_border[2]-matchtresult2_border[3],
									_imageF[1]-matchtresult2_border[0]+matchtresult2_border[1]+matchtresult2_border[2]+matchtresult2_border[3],
									_imageF[2]-matchtresult2_border[0]-matchtresult2_border[1]-matchtresult2_border[2]+matchtresult2_border[3]};
		Mat matchtresultAcc2;

		merge(matchtresultAcc2_,3,matchtresultAcc2);
//		namedWindow( "a", CV_WINDOW_AUTOSIZE );
//						imshow( "a", matchtresultAcc2);
//						waitKey(0);

		merge(sobelColor_,3,sobelColor);



		RNG rng(12345);

		  vector<vector<Point> > contours;
		  vector<Vec4i> hierarchy;


//			  namedWindow( "Boxs2", CV_WINDOW_AUTOSIZE );
//			  imshow( "Boxs2", matchtresultbin );
//			  waitKey(0);
		  Mat element13 = getStructuringElement( dilation_type, Size( 1,3 ), Point( 0,1 ) );
		  Mat element31 = getStructuringElement( dilation_type, Size( 3,1 ), Point( 1,0 ) );

		  vector < vector<Point2i> > blobs;
			threshold(sobel8U,sobel8U,0,255,THRESH_OTSU);
		  cvNica::FindBlobs(sobel8U,blobs);
		  for( int di = 0; di< blobs.size(); di++ ) {
			  int maxx=0;
			  int maxy=0;
			  int minx=1e5;
			  int miny=1e5;
			  int tc=0;
			  Mat tempdrawing = Mat::zeros( size, CV_8UC1 );
			  for( int dj = 0; dj< blobs[di].size(); dj++ ) {
				  tempdrawing.at<uchar>(blobs[di][dj].y,blobs[di][dj].x)=255;
				  int dx = blobs[di][dj].x;
				  int dy = blobs[di][dj].y;
				  if(maxx<dx)maxx=dx;
				  if(minx>dx)minx=dx;
				  if(maxy<dy)maxy=dy;
				  if(miny>dy)miny=dy;
			  }
			  dilate(tempdrawing,tempdrawing,elementL);
			  dilate(tempdrawing,tempdrawing,elementL);
//			  				  namedWindow( "Boxs", CV_WINDOW_AUTOSIZE );
//			  				  imshow( "Boxs", tempdrawing );
//			  				  waitKey(0);

			  for( int dy = 0; dy< size.height; dy++ ){
				  for( int dx = 0; dx< size.width; dx++ ){

					  if (matchtresultbin.at<uchar>(dy,dx) == 255 && tempdrawing.at<uchar>(dy,dx) == 255){
						  tc++;
					  }
				  }
			  }
			  //cout<<" "<<minx<<", "<<miny<<", "<<maxx<<", "<<maxy<<", "<<endl;
			  if (maxx>minx+6 && maxy>miny+6 && tc>1){
				  rectangle(matchtresultAcc,Point(minx,miny),Point(maxx,maxy),Scalar(0,0,255));
				  cout<<" "<<minx<<", "<<miny<<", "<<maxx<<", "<<maxy<<", "<<endl;
			  }


		  }

		  //dilate(canny2,canny2,element13);
		  ///erode(canny2,canny2,element13);
//		  dilate(sobel8U,sobel8U,element31);
//		  erode(sobel8U,sobel8U,element31);
//		  Mat sobel8Ucopy;sobel8U.copyTo(sobel8Ucopy);
//		  findContours( sobel8Ucopy, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
//
//		  /// Draw contours
//		  Mat drawing = matchtresultAcc;//Mat::zeros( sobel8U.size(), CV_8UC3 );
//		  Mat drawing2 = Mat::zeros( sobel8U.size(), CV_8UC3 );
//		  for( int di = 0; di< contours.size(); di++ )
//		     {
//			  int maxx=0;
//			  int maxy=0;
//			  int minx=1e10;
//			  int miny=1e10;
//
//			  if (contours[di].size()>10) {
//		       Scalar color = Scalar( rng.uniform(100, 255), rng.uniform(100,255), rng.uniform(100,255) );
//		       //drawContours( drawing, contours, di, color, 1, 8, hierarchy, 0, Point() );
//		       Mat tempdrawing = Mat::zeros( sobel8U.size(), CV_8UC1 );
//		       drawContours( tempdrawing, contours, di, Scalar(255,255,255), 3, 8, hierarchy, 0, Point() );
////				  namedWindow( "Boxs", CV_WINDOW_AUTOSIZE );
////				  imshow( "Boxs", tempdrawing );
////				  waitKey(0);
//				  for( int dy = 0; dy< size.height; dy++ ){
//					  for( int dx = 0; dx< size.width; dx++ ){
//						  if (matchtresultbin.at<uchar>(dy,dx) == 255 && tempdrawing.at<uchar>(dy,dx) == 255){
//							  if(maxx<dx)maxx=dx;
//							  if(minx>dx)minx=dx;
//							  if(maxy<dy)maxy=dy;
//							  if(miny>dy)miny=dy;
//						  }
//					  }
//				  }
//
//				  rectangle(drawing,Point(minx,miny),Point(maxx,maxy),Scalar(0,0,255));
//				  cout<<" "<<minx<<", "<<miny<<", "<<maxx<<", "<<maxy<<", "<<contours[di].size()<<endl;
//
//
//			  }
//		     }

		  /// Show in a window
//		  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//		  imshow( "Contours", drawing );
////		  namedWindow( "Boxs", CV_WINDOW_AUTOSIZE );
////		  imshow( "Boxs", drawing2 );
//		  waitKey(0);



		Mat sobel222 = sobel/150;
		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
		//				imshow( "a", sobel222);
		CvMat pSrc = sobel222;
		CvMat *pDst = cvCreateMat(size.height, size.width, CV_32FC1);;

		cvNica::MorphologicalThinning(&pSrc,pDst);
		Mat dm = cv::Mat(pDst, true);

		Mat sobelx(size,CV_8UC1);
		Mat sobely(size,CV_8UC1);

		Mat varmapa(size,CV_8UC1);
		Mat varmapa_(size,CV_32FC1);
		cvNica::VarianceFilter(_gray,varmapa_,5);

		varmapa_.convertTo(varmapa,CV_8UC1);

		Mat canny3(size,CV_8UC1);
		Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
		Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
		cvNica::Canny2( _gray, sobelx,sobely, canny3, 60, 120, 3, 1 );

		convertScaleAbs( sobelx, gradx );

		convertScaleAbs( sobely, grady );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );



		Mat mergePos [col*row];
		for (int k=0; k<row; k++) {
			for (int j=0; j<col; j++) {
				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
			}
		}
		Mat sobel8URGB;
		Mat sobelRGB;
		Mat canny2RGB;
		Mat __GrayRGB;
		Mat matchtresultRGB;
		Mat matchtresult2RGB;
		Mat matchtresult8U;
		Mat matchtresult28U;

		cvtColor(sobel8U,sobel8URGB,CV_GRAY2RGB);
		cvtColor(sobel,sobelRGB,CV_GRAY2RGB);
		cvtColor(canny2,canny2RGB,CV_GRAY2RGB);
		matchtresultAcc*=255;
		matchtresultAcc2*=255;
		matchtresultAcc.convertTo(matchtresult8U,CV_8UC3);
		matchtresultAcc2.convertTo(matchtresult28U,CV_8UC3);
//
//		Mat matchtresultlarge(size,CV_8UC3);
//		Mat matchtresult2large(size,CV_8UC3);
//
//		Mat matchtresulttemp = matchtresultlarge;
//		Mat matchtresult2temp = matchtresult2large;
//		matchtresult8U.copyTo(matchtresulttemp);
//		matchtresult28U.copyTo(matchtresult2temp);
//
//		dilate(matchtresultlarge,matchtresultlarge,elementL);
//		dilate(matchtresult2large,matchtresult2large,elementL);
//		dilate(matchtresultlarge,matchtresultRGB,elementL);
//		dilate(matchtresult2large,matchtresult2RGB,elementL);
//
//
//		bitwise_and(sobel8URGB,matchtresulttemp,matchtresulttemp);
//		bitwise_and(canny2RGB,matchtresult2temp,matchtresult2temp);
//
//		bitwise_or(_grayRGB,matchtresulttemp,matchtresultRGB);
//		bitwise_or(_grayRGB,matchtresult2temp,matchtresult2RGB);

		//matchtresultmerged.copyTo(mergePos[3]);
		sobel8URGB.copyTo(mergePos[2]);
		matchtresult8U.copyTo(mergePos[3]);

		//matchtresultmerged2.copyTo(mergePos[0]);
		canny2RGB.copyTo(mergePos[0]);
		matchtresult28U.copyTo(mergePos[1]);

		imwrite(dir+"/set043/"+files[i]+".png",merged);
		cout<<files[i]<<endl;
		//_homoColor2.copyTo(mergePos[3]);
		//_homoThresholdColor.copyTo(mergePos[2]);


	}
#endif


#ifdef t140411
	int kd=5;
	for (unsigned int i = 0;i < files.size();i++) {

		int col = 2;
		int row = 2;

		Mat _image1 = imread( dir+"/"+files[i], -1 );
		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
		Size size = _image1.size();
		Size size2 (_image1.cols*2,_image1.rows*2);


		Mat _gray (size,CV_8UC1),_grayRGB;

		Mat _bilateral (size,CV_8UC1);

		//Mat gradx(size,CV_8UC1);
		//Mat grady(size,CV_8UC1);
		Mat sobel(size,CV_8UC1);

		Mat sobelColor_[3];
		Mat sobelColor;
		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
		Mat sobelOR = Mat::zeros(size,CV_8UC1);
		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
		Mat _image1_split[3];
		Mat _bilateral3 (size,CV_8UC3);
		Mat __image1_split[3];
		Mat __bilateral3 (size,CV_8UC3);
		//_bilateral3 = _image1;
		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
		medianBlur(_bilateral3,_bilateral3,3);
		//medianBlur(_image1,_bilateral3,3);
		int dilation_type = MORPH_RECT;
		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
		//			//dilate(__Gray,__Gray,elementL);
		//			//erode(__Gray,__Gray,elementL);

	//		dilate(_image1,_bilateral3,elementL);
	//		erode(_bilateral3,_bilateral3,elementL);
	//		erode(_bilateral3,_bilateral3,elementL);
	//		dilate(_bilateral3,_bilateral3,elementL);

		split (_bilateral3,_image1_split);
		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
		medianBlur(__bilateral3,__bilateral3,3);
		//medianBlur(__image1,__bilateral3,3);

	//		dilate(__image1,__bilateral3,elementL);
	//		erode(__bilateral3,__bilateral3,elementL);
	//		erode(__bilateral3,__bilateral3,elementL);
	//		dilate(__bilateral3,__bilateral3,elementL);
		split (__bilateral3,__image1_split);

		//split (_image1,_image1_split);
		//split (__image1,__image1_split);


		cvtColor(_image1,_gray,CV_RGB2GRAY);
		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);

		Mat _imageF_;
		Mat _imageF[3];
		_grayRGB.convertTo(_imageF_,CV_32FC3);
		_imageF_/=255;
		split(_imageF_,_imageF);

		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
		Mat gradx(size,CV_32FC1);
		Mat grady(size,CV_32FC1);
		 //dilation_type = MORPH_ELLIPSE;
		//int dilation_type = MORPH_RECT;
			//elementL = getStructuringElement( dilation_type, Size( 25,25 ), Point( 12,12 ) );

			float stdsum=.0;
		for (int k=0; k<3; k++) {

			Mat varmapa(size,CV_8UC1);
					Mat varmapa_(size,CV_32FC1);
					Mat varmapa__(size,CV_32FC1);

			cvNica::VarianceFilter(_image1_split[k],varmapa_,7);

			Mat canny_,canny__;

			Canny( _image1_split[k], canny_, 30, 50, 3, 1 );
			canny_.convertTo(canny__,CV_32FC1);

			//erode(varmapa_,varmapa_,elementL);

			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
			float spsum = sum(sp32)[0]/size.width/size.height;
			float spsqsum = sum(sp32.mul(sp32))[0];
			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;

			std = (std<30)? 30:std;
			//cv::pow(varmapa_,1.1,varmapa_);
			stdsum += std;


			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
			//threshold(varmapa_,varmapa,8,255,THRESH_BINARY_INV);
			max(varmapa_,varmapa,varmapa);


			Mat sobelx(size,CV_32FC1);
			Mat sobely(size,CV_32FC1);
			Mat sobelxsq(size,CV_32FC1);
			Mat sobelysq(size,CV_32FC1);
			Sobel(_image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );


			sobelx/=varmapa/150;
			//sobelx=sobelx.mul(canny__/255);
			//sobelx=sobelx.mul(__Gray8);
			multiply(sobelx,sobelx,sobelxsq);

			sobelxsqsum += sobelxsq*std;
			//convertScaleAbs( sobelx, gradx );
			Sobel(_image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
			sobely/=varmapa/150;
			//sobely=sobely.mul(canny__/255);
			//sobely=sobely.mul(__Gray8);
			multiply(sobely,sobely,sobelysq);

			sobelysqsum += sobelysq*std;



			convertScaleAbs( sobelx, gradx );
			convertScaleAbs( sobely, grady );
			addWeighted( gradx, 0.5, grady, 0.5, 0, sobelColor_[k] );
			Mat sobel8UU;
			sobelColor_[k].convertTo(sobel8UU,CV_8UC1);
			bitwise_and(sobel8UU,sobelAND,sobelAND);
			bitwise_or(sobel8UU,sobelOR,sobelOR);
			//convertScaleAbs( sobely, grady );

		}

		sobelxsqsum/=stdsum;
		sobelysqsum/=stdsum;
		sqrt (sobelxsqsum,gradx);
		sqrt (sobelysqsum,grady);

		Mat canny2;Mat gradx2;Mat grady2;
		gradx.convertTo(gradx2,CV_16S);
		grady.convertTo(grady2,CV_16S);
		Canny( _gray, canny2, 60, 120, 3, 1 );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );


		Mat sobel8U2;Mat sobel8U;
		sobel.convertTo(sobel8U,CV_8UC1);

		Point a1;

		Mat matchtresult[4];
		Mat matchtresult_border[4];
		Mat kernel1;
		Mat matchtresultbinF;
		Mat matchtresultbin = Mat::zeros (size,CV_8UC1);
		double thrval=0.7;
		int startIndex = 102;//98;//36;

		for (int l=0; l<4; l++) {
			kernel1 = cvNica::kernels(startIndex+l,a1)*255;
			matchTemplate(sobel,kernel1,matchtresult[l],CV_TM_CCOEFF_NORMED);
			threshold(matchtresult[l],matchtresult[l],thrval,1,THRESH_BINARY);
			//copyMakeBorder(matchtresult[l], matchtresult_border[l], 3, 3, 3, 3, BORDER_DEFAULT);
			copyMakeBorder(matchtresult[l], matchtresult_border[l], 2, 2, 2, 2, BORDER_DEFAULT);
			matchtresult_border[l]*=255;
			matchtresult_border[l].convertTo(matchtresultbinF,CV_8UC1);
			matchtresult_border[l]/=255;
			bitwise_or(matchtresultbin,matchtresultbinF,matchtresultbin);
			dilate(matchtresult_border[l],matchtresult_border[l],elementL);
			dilate(matchtresult_border[l],matchtresult_border[l],elementL);
			matchtresult_border[l]= matchtresult_border[l].mul(sobel/255);
			dilate(matchtresult_border[l],matchtresult_border[l],elementL);
			//bitwise_and(sobel,matchtresult_border[l],matchtresult_border[l]);
//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//							imshow( "a", matchtresult_border[l]);
//							waitKey(0);
		}

		Mat matchtresultAcc_[3] = {_imageF[0]+matchtresult_border[0]+matchtresult_border[1]-matchtresult_border[2]-matchtresult_border[3],
									_imageF[1]-matchtresult_border[0]+matchtresult_border[1]+matchtresult_border[2]+matchtresult_border[3],
									_imageF[2]-matchtresult_border[0]-matchtresult_border[1]-matchtresult_border[2]+matchtresult_border[3]};
		Mat matchtresultAcc;



		merge(matchtresultAcc_,3,matchtresultAcc);
//		namedWindow( "a", CV_WINDOW_AUTOSIZE );
//						imshow( "a", matchtresultbin);
//						waitKey(0);

		Point a2;
		Mat matchtresult2[4];
		Mat matchtresult2_border[4];
		Mat kernel2;
		Mat canny232F;

		canny2.convertTo(canny232F,CV_32FC1);

		for (int l=0; l<4; l++) {
			kernel2 = cvNica::kernels(startIndex+l,a2)*255;
			matchTemplate(canny232F,kernel2,matchtresult2[l],CV_TM_CCOEFF_NORMED);
			threshold(matchtresult2[l],matchtresult2[l],thrval,1,THRESH_BINARY);
			copyMakeBorder(matchtresult2[l], matchtresult2_border[l], 2, 2, 2, 2, BORDER_DEFAULT);
			//matchtresult2_border[l] = matchtresult2_border[l].mul(canny232F);

			dilate(matchtresult2_border[l],matchtresult2_border[l],elementL);
			dilate(matchtresult2_border[l],matchtresult2_border[l],elementL);
			matchtresult2_border[l]=matchtresult2_border[l].mul(canny232F);
			dilate(matchtresult2_border[l],matchtresult2_border[l],elementL);



		}


		Mat matchtresultAcc2_[3] =  {_imageF[0]+matchtresult2_border[0]+matchtresult2_border[1]-matchtresult2_border[2]-matchtresult2_border[3],
									_imageF[1]-matchtresult2_border[0]+matchtresult2_border[1]+matchtresult2_border[2]+matchtresult2_border[3],
									_imageF[2]-matchtresult2_border[0]-matchtresult2_border[1]-matchtresult2_border[2]+matchtresult2_border[3]};
		Mat matchtresultAcc2;

		merge(matchtresultAcc2_,3,matchtresultAcc2);
//		namedWindow( "a", CV_WINDOW_AUTOSIZE );
//						imshow( "a", matchtresultAcc2);
//						waitKey(0);

		merge(sobelColor_,3,sobelColor);



		RNG rng(12345);

		  vector<vector<Point> > contours;
		  vector<Vec4i> hierarchy;


//			  namedWindow( "Boxs2", CV_WINDOW_AUTOSIZE );
//			  imshow( "Boxs2", matchtresultbin );
//			  waitKey(0);
		  Mat element13 = getStructuringElement( dilation_type, Size( 1,3 ), Point( 0,1 ) );
		  Mat element31 = getStructuringElement( dilation_type, Size( 3,1 ), Point( 1,0 ) );

		  vector < vector<Point2i> > blobs;
			threshold(sobel8U,sobel8U,0,255,THRESH_OTSU);
		  cvNica::FindBlobs(sobel8U,blobs);
		  for( int di = 0; di< blobs.size(); di++ ) {
			  int maxx=0;
			  int maxy=0;
			  int minx=1e5;
			  int miny=1e5;
			  int tc=0;
			  Mat tempdrawing = Mat::zeros( size, CV_8UC1 );
			  for( int dj = 0; dj< blobs[di].size(); dj++ ) {
				  tempdrawing.at<uchar>(blobs[di][dj].y,blobs[di][dj].x)=255;
				  int dx = blobs[di][dj].x;
				  int dy = blobs[di][dj].y;
				  if(maxx<dx)maxx=dx;
				  if(minx>dx)minx=dx;
				  if(maxy<dy)maxy=dy;
				  if(miny>dy)miny=dy;
			  }
			  dilate(tempdrawing,tempdrawing,elementL);
			  dilate(tempdrawing,tempdrawing,elementL);
//			  				  namedWindow( "Boxs", CV_WINDOW_AUTOSIZE );
//			  				  imshow( "Boxs", tempdrawing );
//			  				  waitKey(0);

			  for( int dy = 0; dy< size.height; dy++ ){
				  for( int dx = 0; dx< size.width; dx++ ){

					  if (matchtresultbin.at<uchar>(dy,dx) == 255 && tempdrawing.at<uchar>(dy,dx) == 255){
						  tc++;
					  }
				  }
			  }
			  //cout<<" "<<minx<<", "<<miny<<", "<<maxx<<", "<<maxy<<", "<<endl;
			  if (maxx>minx+6 && maxy>miny+6 && tc>1){
				  rectangle(matchtresultAcc,Point(minx,miny),Point(maxx,maxy),Scalar(0,0,255));
				  cout<<" "<<minx<<", "<<miny<<", "<<maxx<<", "<<maxy<<", "<<endl;
			  }


		  }

		  //dilate(canny2,canny2,element13);
		  ///erode(canny2,canny2,element13);
//		  dilate(sobel8U,sobel8U,element31);
//		  erode(sobel8U,sobel8U,element31);
//		  Mat sobel8Ucopy;sobel8U.copyTo(sobel8Ucopy);
//		  findContours( sobel8Ucopy, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
//
//		  /// Draw contours
//		  Mat drawing = matchtresultAcc;//Mat::zeros( sobel8U.size(), CV_8UC3 );
//		  Mat drawing2 = Mat::zeros( sobel8U.size(), CV_8UC3 );
//		  for( int di = 0; di< contours.size(); di++ )
//		     {
//			  int maxx=0;
//			  int maxy=0;
//			  int minx=1e10;
//			  int miny=1e10;
//
//			  if (contours[di].size()>10) {
//		       Scalar color = Scalar( rng.uniform(100, 255), rng.uniform(100,255), rng.uniform(100,255) );
//		       //drawContours( drawing, contours, di, color, 1, 8, hierarchy, 0, Point() );
//		       Mat tempdrawing = Mat::zeros( sobel8U.size(), CV_8UC1 );
//		       drawContours( tempdrawing, contours, di, Scalar(255,255,255), 3, 8, hierarchy, 0, Point() );
////				  namedWindow( "Boxs", CV_WINDOW_AUTOSIZE );
////				  imshow( "Boxs", tempdrawing );
////				  waitKey(0);
//				  for( int dy = 0; dy< size.height; dy++ ){
//					  for( int dx = 0; dx< size.width; dx++ ){
//						  if (matchtresultbin.at<uchar>(dy,dx) == 255 && tempdrawing.at<uchar>(dy,dx) == 255){
//							  if(maxx<dx)maxx=dx;
//							  if(minx>dx)minx=dx;
//							  if(maxy<dy)maxy=dy;
//							  if(miny>dy)miny=dy;
//						  }
//					  }
//				  }
//
//				  rectangle(drawing,Point(minx,miny),Point(maxx,maxy),Scalar(0,0,255));
//				  cout<<" "<<minx<<", "<<miny<<", "<<maxx<<", "<<maxy<<", "<<contours[di].size()<<endl;
//
//
//			  }
//		     }

		  /// Show in a window
//		  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//		  imshow( "Contours", drawing );
////		  namedWindow( "Boxs", CV_WINDOW_AUTOSIZE );
////		  imshow( "Boxs", drawing2 );
//		  waitKey(0);



		Mat sobel222 = sobel/150;
		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
		//				imshow( "a", sobel222);
		CvMat pSrc = sobel222;
		CvMat *pDst = cvCreateMat(size.height, size.width, CV_32FC1);;

		cvNica::MorphologicalThinning(&pSrc,pDst);
		Mat dm = cv::Mat(pDst, true);

		Mat sobelx(size,CV_8UC1);
		Mat sobely(size,CV_8UC1);

		Mat varmapa(size,CV_8UC1);
		Mat varmapa_(size,CV_32FC1);
		cvNica::VarianceFilter(_gray,varmapa_,5);

		varmapa_.convertTo(varmapa,CV_8UC1);

		Mat canny3(size,CV_8UC1);
		Sobel(_gray,sobelx,CV_16SC1,1,0,3,1, 0, BORDER_DEFAULT );
		Sobel(_gray,sobely,CV_16SC1,0,1,3,1, 0, BORDER_DEFAULT );
		cvNica::Canny2( _gray, sobelx,sobely, canny3, 60, 120, 3, 1 );

		convertScaleAbs( sobelx, gradx );

		convertScaleAbs( sobely, grady );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );



		Mat mergePos [col*row];
		for (int k=0; k<row; k++) {
			for (int j=0; j<col; j++) {
				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
			}
		}
		Mat sobel8URGB;
		Mat sobelRGB;
		Mat canny2RGB;
		Mat __GrayRGB;
		Mat matchtresultRGB;
		Mat matchtresult2RGB;
		Mat matchtresult8U;
		Mat matchtresult28U;

		cvtColor(sobel8U,sobel8URGB,CV_GRAY2RGB);
		cvtColor(sobel,sobelRGB,CV_GRAY2RGB);
		cvtColor(canny2,canny2RGB,CV_GRAY2RGB);
		matchtresultAcc*=255;
		matchtresultAcc2*=255;
		matchtresultAcc.convertTo(matchtresult8U,CV_8UC3);
		matchtresultAcc2.convertTo(matchtresult28U,CV_8UC3);
//
//		Mat matchtresultlarge(size,CV_8UC3);
//		Mat matchtresult2large(size,CV_8UC3);
//
//		Mat matchtresulttemp = matchtresultlarge;
//		Mat matchtresult2temp = matchtresult2large;
//		matchtresult8U.copyTo(matchtresulttemp);
//		matchtresult28U.copyTo(matchtresult2temp);
//
//		dilate(matchtresultlarge,matchtresultlarge,elementL);
//		dilate(matchtresult2large,matchtresult2large,elementL);
//		dilate(matchtresultlarge,matchtresultRGB,elementL);
//		dilate(matchtresult2large,matchtresult2RGB,elementL);
//
//
//		bitwise_and(sobel8URGB,matchtresulttemp,matchtresulttemp);
//		bitwise_and(canny2RGB,matchtresult2temp,matchtresult2temp);
//
//		bitwise_or(_grayRGB,matchtresulttemp,matchtresultRGB);
//		bitwise_or(_grayRGB,matchtresult2temp,matchtresult2RGB);

		//matchtresultmerged.copyTo(mergePos[3]);
		sobel8URGB.copyTo(mergePos[2]);
		matchtresult8U.copyTo(mergePos[3]);

		//matchtresultmerged2.copyTo(mergePos[0]);
		canny2RGB.copyTo(mergePos[0]);
		matchtresult28U.copyTo(mergePos[1]);

		imwrite(dir+"/set044/"+files[i]+".png",merged);
		cout<<files[i]<<endl;
		//_homoColor2.copyTo(mergePos[3]);
		//_homoThresholdColor.copyTo(mergePos[2]);


	}
#endif

#ifdef t140508
	int kd=5;
	for (unsigned int i = 0;i < files.size();i++) {



		Mat _image1 = imread( dir+"/"+files[i], -1 );
		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
		Size size = _image1.size();
		Size size2 (_image1.cols*2,_image1.rows*2);


		Mat _gray (size,CV_8UC1),_grayRGB;
		cvtColor(_image1,_gray,CV_RGB2GRAY);
		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
		Mat l;
		Mat s;
		Mat diff;
		Mat diff_;
		Mat mean;
		Mat mean_;
		Mat _gray_;
		Mat proc;
		Mat proc_;
		int dilation_type = MORPH_RECT;
		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
		Mat elementL_; elementL.convertTo(elementL_,CV_32FC1);
		elementL_/=3.*3;
		dilate( _gray, l, elementL);
		erode( _gray, s, elementL);
		filter2D(_gray, mean, CV_8UC1, elementL_);
		mean.convertTo(mean_,CV_32FC1);
		_gray.convertTo(_gray_,CV_32FC1);

		diff = l-s;
		diff.convertTo(diff_,CV_32FC1);
		absdiff(diff_,mean_,proc);

		absdiff(l,mean,l);
		absdiff(s,mean,s);
//		equalizeHist(l,l);
//		equalizeHist(s,s);
		normalize(l,l,0,255, NORM_MINMAX);
		normalize(s,s,0,255, NORM_MINMAX);
		//max(s,l,l);
		l.convertTo(proc,CV_32FC1);

		proc = _gray+l;
		proc = proc+s;

		proc_ = 255-proc;


		equalizeHist(proc,proc);
		equalizeHist(proc_,proc_);

		proc-=proc_;

		//proc.convertTo(proc_,CV_8UC1);


		//Canny(proc_,proc, 60, 120, 3, 1 );
		//divide(proc,diff_,proc);


//		erode( proc, proc, elementL);
//
//		dilate( proc, proc, elementL);
//		erode( proc_, proc_, elementL);
//		dilate( proc_, proc_, elementL);
//		erode( proc_, proc_, elementL);
//		dilate( proc_, proc_, elementL);

				  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
				  //imshow( "Contours", (proc)/255.);
				  imshow( "Contours", (proc));
				  waitKey(0);

	}
#endif

//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//
//		int col = 3;
//		int row = 2;
//
//		Mat _image1 = imread( dir+"/"+files[i], -1 );
//		Mat __image1; cvtColor(_image1,__image1,CV_RGB2YCrCb);
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//
//		//Mat gradx(size,CV_8UC1);
//		//Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//
//		Mat sobelColor_[3];
//		Mat sobelColor;
//		Mat sobelAND = Mat::zeros(size,CV_8UC1)+255;
//		Mat sobelOR = Mat::zeros(size,CV_8UC1);
//		Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
//		Mat _image1_split[3];
//		Mat _bilateral3 (size,CV_8UC3);
//		Mat __image1_split[3];
//		Mat __bilateral3 (size,CV_8UC3);
//		//_bilateral3 = _image1;
//		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(_bilateral3,_bilateral3,3);
//		//medianBlur(_image1,_bilateral3,3);
//		int dilation_type = MORPH_RECT;
//		Mat elementL = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//		//			//dilate(__Gray,__Gray,elementL);
//		//			//erode(__Gray,__Gray,elementL);
//
//	//		dilate(_image1,_bilateral3,elementL);
//	//		erode(_bilateral3,_bilateral3,elementL);
//	//		erode(_bilateral3,_bilateral3,elementL);
//	//		dilate(_bilateral3,_bilateral3,elementL);
//
//		split (_bilateral3,_image1_split);
//		bilateralFilter (__image1, __bilateral3 , kd, kd*2, kd/2 );
//		medianBlur(__bilateral3,__bilateral3,3);
//		//medianBlur(__image1,__bilateral3,3);
//
//	//		dilate(__image1,__bilateral3,elementL);
//	//		erode(__bilateral3,__bilateral3,elementL);
//	//		erode(__bilateral3,__bilateral3,elementL);
//	//		dilate(__bilateral3,__bilateral3,elementL);
//		split (__bilateral3,__image1_split);
//
//		//split (_image1,_image1_split);
//		//split (__image1,__image1_split);
//
//
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//		Mat sobelxsqsum = Mat::zeros(size,CV_32FC1);
//		Mat sobelysqsum = Mat::zeros(size,CV_32FC1);
//		Mat gradx(size,CV_32FC1);
//		Mat grady(size,CV_32FC1);
//		 //dilation_type = MORPH_ELLIPSE;
//		//int dilation_type = MORPH_RECT;
//			//elementL = getStructuringElement( dilation_type, Size( 25,25 ), Point( 12,12 ) );
//
//			float stdsum=.0;
//		for (int k=0; k<3; k++) {
//
//			Mat varmapa(size,CV_8UC1);
//					Mat varmapa_(size,CV_32FC1);
//					Mat varmapa__(size,CV_32FC1);
//
//			cvNica::VarianceFilter(_image1_split[k],varmapa_,7);
//
//			Mat canny_,canny__;
//
//			Canny( _image1_split[k], canny_, 30, 50, 3, 1 );
//			canny_.convertTo(canny__,CV_32FC1);
//
//			//erode(varmapa_,varmapa_,elementL);
//
//			Mat sp32; _image1_split[k].convertTo(sp32,CV_32FC1);
//			float spsum = sum(sp32)[0]/size.width/size.height;
//			float spsqsum = sum(sp32.mul(sp32))[0];
//			float std = sqrt(spsqsum/size.width/size.height - spsum*spsum);
//			cout<<": "<<spsum<<": "<<spsqsum<<": "<<std<<endl;
//
//			std = (std<30)? 30:std;
//			//cv::pow(varmapa_,1.1,varmapa_);
//			stdsum += std;
//
//
//			threshold(varmapa_,varmapa,std/6+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,sqrt(std)+2,255,THRESH_BINARY_INV);
//			//threshold(varmapa_,varmapa,8,255,THRESH_BINARY_INV);
//			max(varmapa_,varmapa,varmapa);
//
//
//			Mat sobelx(size,CV_32FC1);
//			Mat sobely(size,CV_32FC1);
//			Mat sobelxsq(size,CV_32FC1);
//			Mat sobelysq(size,CV_32FC1);
//			Sobel(_image1_split[k],sobelx,CV_32F,1,0,1,1, 0, BORDER_REPLICATE );
//
//
//			sobelx/=varmapa/150;
//			sobelx=sobelx.mul(canny__/255);
//			//sobelx=sobelx.mul(__Gray8);
//			multiply(sobelx,sobelx,sobelxsq);
//
//			sobelxsqsum += sobelxsq*std;
//			//convertScaleAbs( sobelx, gradx );
//			Sobel(_image1_split[k],sobely,CV_32F,0,1,1,1, 0, BORDER_REPLICATE );
//			sobely/=varmapa/150;
//			sobely=sobely.mul(canny__/255);
//			//sobely=sobely.mul(__Gray8);
//			multiply(sobely,sobely,sobelysq);
//
//			sobelysqsum += sobelysq*std;
//
//
//
//			convertScaleAbs( sobelx, gradx );
//			convertScaleAbs( sobely, grady );
//			addWeighted( gradx, 0.5, grady, 0.5, 0, sobelColor_[k] );
//			Mat sobel8UU;
//			sobelColor_[k].convertTo(sobel8UU,CV_8UC1);
//			bitwise_and(sobel8UU,sobelAND,sobelAND);
//			bitwise_or(sobel8UU,sobelOR,sobelOR);
//			//convertScaleAbs( sobely, grady );
//
//		}
//
//		sobelxsqsum/=stdsum;
//		sobelysqsum/=stdsum;
//		sqrt (sobelxsqsum,gradx);
//		sqrt (sobelysqsum,grady);
//
//		Mat canny2;Mat gradx2;Mat grady2;
//		gradx.convertTo(gradx2,CV_16S);
//		grady.convertTo(grady2,CV_16S);
//		Canny( _gray, canny2, 60, 120, 3, 1 );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//
//		Mat sobel8URGB;
//		Mat sobelRGB;
//		Mat canny2RGB;
//		Mat sobel8U2;Mat sobel8U;
//		Mat mergePos [col*row];
//		for (int k=0; k<row; k++) {
//			for (int j=0; j<col; j++) {
//				mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat matchtresultmerged;
//		Mat matchtresultmerged2;
//		_grayRGB.copyTo(matchtresultmerged);
//		_grayRGB.copyTo(matchtresultmerged2);
//
//
//		Point a1;
//		Mat matchtresultAcc;
//		Mat matchtresult;
//		Mat kernel1;
//		double thrval=0.7;
//		int startIndex = 36;//98;//36;
//		kernel1 = cvNica::kernels(startIndex,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		dilate(matchtresult,matchtresult,elementL);
//		dilate(matchtresult,matchtresult,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult.at<float>(j,i)==1&&sobel.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged,Point(i,j),3,Scalar(255,0,0));
//
//
//
//		kernel1 = cvNica::kernels(startIndex+1,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		dilate(matchtresult,matchtresult,elementL);
//		dilate(matchtresult,matchtresult,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult.at<float>(j,i)==1&&sobel.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged,Point(i,j),3,Scalar(0,255,0));
//
//		kernel1 = cvNica::kernels(startIndex+2,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		dilate(matchtresult,matchtresult,elementL);
//		dilate(matchtresult,matchtresult,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult.at<float>(j,i)==1&&sobel.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged,Point(i,j),3,Scalar(255,255,0));
//
//		kernel1 = cvNica::kernels(startIndex+3,a1)*255;
//		matchTemplate(sobel,kernel1,matchtresult,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult,matchtresult,thrval,1,THRESH_BINARY);
//		dilate(matchtresult,matchtresult,elementL);
//		dilate(matchtresult,matchtresult,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult.at<float>(j,i)==1&&sobel.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged,Point(i,j),3,Scalar(0,255,255));
//
//
//		Point a2;
//		Mat matchtresultAcc2;
//		Mat matchtresult2;
//		Mat kernel2;
//		Mat canny232F;
//		canny2.convertTo(canny232F,CV_32FC1);
//		kernel2 = cvNica::kernels(startIndex,a2)*255;
//		matchTemplate(canny232F,kernel2,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		dilate(matchtresult2,matchtresult2,elementL);
//		dilate(matchtresult2,matchtresult2,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult2.at<float>(j,i)==1&&canny2.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged2,Point(i,j),3,Scalar(255,0,0));
//
//
//
//		kernel2 = cvNica::kernels(startIndex+1,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		dilate(matchtresult2,matchtresult2,elementL);
//		dilate(matchtresult2,matchtresult2,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult2.at<float>(j,i)==1&&canny2.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged2,Point(i,j),3,Scalar(0,255,0));
//
//
//		kernel2 = cvNica::kernels(startIndex+2,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		dilate(matchtresult2,matchtresult2,elementL);
//		dilate(matchtresult2,matchtresult2,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult2.at<float>(j,i)==1&&canny2.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged2,Point(i,j),3,Scalar(255,255,0));
//
//		kernel2 = cvNica::kernels(startIndex+3,a1)*255;
//		matchTemplate(canny232F,kernel1,matchtresult2,CV_TM_CCOEFF_NORMED);
//		threshold(matchtresult2,matchtresult2,thrval,1,THRESH_BINARY);
//		dilate(matchtresult2,matchtresult2,elementL);
//		dilate(matchtresult2,matchtresult2,elementL);
//	    for (int j=0; j<size.height; j++)
//	    	for (int i=0; i<size.width; i++)
//	    		if (matchtresult2.at<float>(j,i)==1&&canny2.at<uchar>(j,i)>150)
//	    			circle(matchtresultmerged2,Point(i,j),3,Scalar(0,255,255));
//
//
//
//
//
//		sobel.convertTo(sobel8U,CV_8UC1);
//		cvtColor(sobel8U,sobel8URGB,CV_GRAY2RGB);
//		cvtColor(sobel,sobelRGB,CV_GRAY2RGB);
//		cvtColor(canny2,canny2RGB,CV_GRAY2RGB);
//
//
//
//
//		matchtresultmerged.copyTo(mergePos[3]);
//		sobel8URGB.copyTo(mergePos[4]);
//		//matchtresultRGB.copyTo(mergePos[5]);
//
//		matchtresultmerged2.copyTo(mergePos[0]);
//		canny2RGB.copyTo(mergePos[1]);
//		//matchtresult2RGB.copyTo(mergePos[2]);
//
//		imwrite(dir+"/set040/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//		//_homoColor2.copyTo(mergePos[3]);
//		//_homoThresholdColor.copyTo(mergePos[2]);
//
//
//	}

}




#endif

#ifdef SMQI_varparam
int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpeg";
	else dataType = "bmp";
#endif

#ifdef DATA_TYPE_SELECT
	string dir = string(argv[1]);
	string refLocation = string(argv[2]);

	vector<string> files = vector<string>();
	cout<<dataType<<endl;
	if (nicatio::getdirType(dir,dataType,files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif


//					for (unsigned int i = 0;i < files.size();i++) {
//						Mat _image1;
//						_image1 = imread( dir+"/"+files[i], -1 );
//						Size size = _image1.size();
//						Mat _deno1(size,CV_8UC1);
//						Mat _dmqi(size,CV_8UC1);
//						Mat _histeq(size,CV_8UC1);
//						cvNica::Denoise(_image1,_deno1);
//						cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, 11, 3, 2.1, 0);
//						equalizeHist(_dmqi,_histeq);
//						unsigned found = files[i].rfind("bad");
//						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//						imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
//						if (found!=std::string::npos)
//							rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//					}
//					cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//					fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//					fr.getAccuracy(files);
//					fr.getAccuracyIncludingBadImages();
//					fr.getAccuracyIncludingBadImagesSubset();

					//fr.PrintScore("dfdf.txt");
					//of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;


	ofstream of;
	of.open("output_ddd32.txt");

//	//for (int large=5; large<=15; large+=2){
//	for (int large=9; large<=9; large+=2){
//		//for (int small=3; small<large;small+=2){//large; small+=2){
//		for (int small=5; small<=5;small+=2){
//			for (float alpha=1; alpha<=3.0; alpha+=0.1){
//
//				for (unsigned int i = 0;i < files.size();i++) {
//					Mat _image1;
//					_image1 = imread( dir+"/"+files[i], -1 );
//					Size size = _image1.size();
//					Mat _deno1(size,CV_8UC1);
//					Mat _dmqi(size,CV_8UC1);
//					Mat _histeq(size,CV_8UC1);
//					cvNica::Denoise(_image1,_deno1);
//					cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, large, small, alpha, 0);
//					equalizeHist(_dmqi,_histeq);
//					unsigned found = files[i].rfind("bad");
//					vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//					imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
//					if (found!=std::string::npos)
//						rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//				}
//				cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//				fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//				of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//				vector<string> ldf;
//				ldf<<alpha;
//				fr.PrintScore("dfdf_"+ldf+".txt");
//			}
//
////			for (float alpha=3.; alpha<=10.01; alpha+=1.){
////
////				for (unsigned int i = 0;i < files.size();i++) {
////					Mat _image1;
////					_image1 = imread( dir+"/"+files[i], -1 );
////					Size size = _image1.size();
////					Mat _deno1(size,CV_8UC1);
////					Mat _dmqi(size,CV_8UC1);
////					Mat _histeq(size,CV_8UC1);
////					cvNica::Denoise(_image1,_deno1);
////					cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, large, small, alpha, 0);
////					equalizeHist(_dmqi,_histeq);
////					unsigned found = files[i].rfind("bad");
////					vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
////					imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
////					if (found!=std::string::npos)
////						rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
////
////				}
////				cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
////				fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
////				of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
////			}
//
//		}
//	}


//
//	for (float alpha=0.0; alpha<=100.0; alpha+=10.0){
//		//if(alpha>=60.0) alpha=100.0;
//		for (unsigned int i = 0;i < files.size();i++) {
//			cout<<i<<endl;
//			Mat _image1;
//			_image1 = imread( dir+"/"+files[i], -1 );
//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//			cvNica::Denoise(_image1,_deno1);
//			//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
//			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//			cvNica::RemoveGrainyNoise(_dmqi,_deno1,alpha);
//			equalizeHist(_deno1,_histeq);
//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/testbed3/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/testbed3/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed3/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//		}
//		cvNica::FaceRecognition fr(dir+"/testbed3",refLocation,"integrated");
//		fr.Recognition(dir+"/testbed3",dataType,DB_YALEB,METHOD_CORR);
//		//of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//		of<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//		stringstream ldf;
//		ldf<<"CMUPIE_mdmhe_only_"<<alpha<<".txt";
//		string kk = ldf.str().c_str();
//		fr.PrintScore((char*)kk.c_str());
//	}

	for (float alpha=1.49; alpha<=1.492;){
	for (unsigned int i = 0;i < files.size();i++) {
						Mat _image1;
						_image1 = imread( dir+"/"+files[i], -1 );
						Size size = _image1.size();
						Mat _deno1(size,CV_8UC1);
						Mat _dmqi(size,CV_8UC1);
						Mat _histeq(size,CV_8UC1);
						cvNica::Denoise(_image1,_deno1);
						//cvNica::SelectiveClosingParam(_deno1,_dmqi, 5, 5, 1.4, 0);
						cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, 9, 5, alpha, 0);
						equalizeHist(_dmqi,_histeq);
						unsigned found = files[i].rfind("bad");
						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
						stringstream ad;
						ad<<alpha;
						imwrite(dir+"/smqi_a"+ad.str()+"/"+tokens[0]+"."+dataType,_histeq);
						if (found!=std::string::npos)
							rename( string(dir+"/smqi_a"+ad.str()+"/"+tokens[0]+"."+dataType).c_str() , string(dir+"/smqi_a"+ad.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );

					}
//	cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//			fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//			//of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//			of<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
////			stringstream ldf;
////			ldf<<"CMUPIE_mdmhe_only_"<<alpha<<".txt";
////			string kk = ldf.str().c_str();
////			fr.PrintScore((char*)kk.c_str());
	alpha+=0.01;


	}

	of.close();
}
#endif




#ifdef SMQI_varparam_adaptive
int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpeg";
	else dataType = "bmp";
#endif

#ifdef DATA_TYPE_SELECT
	string dir = string(argv[1]);
	string refLocation = string(argv[2]);

	vector<string> files = vector<string>();
	cout<<dataType<<endl;
	if (nicatio::getdirType(dir,dataType,files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif


//					for (unsigned int i = 0;i < files.size();i++) {
//						Mat _image1;
//						_image1 = imread( dir+"/"+files[i], -1 );
//						Size size = _image1.size();
//						Mat _deno1(size,CV_8UC1);
//						Mat _dmqi(size,CV_8UC1);
//						Mat _histeq(size,CV_8UC1);
//						cvNica::Denoise(_image1,_deno1);
//						cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, 11, 3, 2.1, 0);
//						equalizeHist(_dmqi,_histeq);
//						unsigned found = files[i].rfind("bad");
//						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//						imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
//						if (found!=std::string::npos)
//							rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//					}
//					cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//					fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//					fr.getAccuracy(files);
//					fr.getAccuracyIncludingBadImages();
//					fr.getAccuracyIncludingBadImagesSubset();

					//fr.PrintScore("dfdf.txt");
					//of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;


	ofstream of;
	of.open("output.txt");
//	//for (int large=5; large<=15; large+=2){
//	for (int large=9; large<=9; large+=2){
//		//for (int small=3; small<large;small+=2){//large; small+=2){
//		for (int small=5; small<=5;small+=2){
//			for (float alpha=1; alpha<=3.0; alpha+=0.1){
//
//				for (unsigned int i = 0;i < files.size();i++) {
//					Mat _image1;
//					_image1 = imread( dir+"/"+files[i], -1 );
//					Size size = _image1.size();
//					Mat _deno1(size,CV_8UC1);
//					Mat _dmqi(size,CV_8UC1);
//					Mat _histeq(size,CV_8UC1);
//					cvNica::Denoise(_image1,_deno1);
//					cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, large, small, alpha, 0);
//					equalizeHist(_dmqi,_histeq);
//					unsigned found = files[i].rfind("bad");
//					vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//					imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
//					if (found!=std::string::npos)
//						rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//				}
//				cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//				fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//				of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//				vector<string> ldf;
//				ldf<<alpha;
//				fr.PrintScore("dfdf_"+ldf+".txt");
//			}
//
////			for (float alpha=3.; alpha<=10.01; alpha+=1.){
////
////				for (unsigned int i = 0;i < files.size();i++) {
////					Mat _image1;
////					_image1 = imread( dir+"/"+files[i], -1 );
////					Size size = _image1.size();
////					Mat _deno1(size,CV_8UC1);
////					Mat _dmqi(size,CV_8UC1);
////					Mat _histeq(size,CV_8UC1);
////					cvNica::Denoise(_image1,_deno1);
////					cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, large, small, alpha, 0);
////					equalizeHist(_dmqi,_histeq);
////					unsigned found = files[i].rfind("bad");
////					vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
////					imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
////					if (found!=std::string::npos)
////						rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
////
////				}
////				cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
////				fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
////				of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
////			}
//
//		}
//	}



	for (float alpha=0; alpha<=1.01; alpha+=0.05){

		//if(alpha>=60.0) alpha=100.0;
		for (unsigned int i = 0;i < files.size();i++) {
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			cvNica::Denoise(_image1,_deno1);
			cvNica::AdaptiveMorphQuotImage(_deno1,_dmqi,alpha);
			equalizeHist(_dmqi,_histeq);
			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			stringstream al; al<<alpha;
			imwrite(dir+"/testbed/"+tokens[0]+"_"+al.str()+"."+dataType,_dmqi);//_histeq);
			if (found!=std::string::npos)
				rename( string(dir+"/testbed/"+tokens[0]+"_"+al.str()+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"_"+al.str()+"."+dataType+".bad").c_str() );

		}
//		cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//		fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//		of<<alpha<<"\t"<<fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//		stringstream ldf;
//		ldf<<"dfdf_"<<alpha<<".txt";
//		string kk = ldf.str().c_str();
//		fr.PrintScore((char*)kk.c_str());
	}



	of.close();
}
#endif


#ifdef CMQI_varparam
int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpeg";
	else dataType = "bmp";
#endif

#ifdef DATA_TYPE_SELECT
	string dir = string(argv[1]);
	string refLocation = string(argv[2]);
	string dir2 = string(argv[4]);
	vector<string> files = vector<string>();
	cout<<dataType<<endl;
	if (nicatio::getdirType(dir,dataType,files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif


//					for (unsigned int i = 0;i < files.size();i++) {
//						Mat _image1;
//						_image1 = imread( dir+"/"+files[i], -1 );
//						Size size = _image1.size();
//						Mat _deno1(size,CV_8UC1);
//						Mat _dmqi(size,CV_8UC1);
//						Mat _histeq(size,CV_8UC1);
//						cvNica::Denoise(_image1,_deno1);
//						cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, 11, 3, 2.1, 0);
//						equalizeHist(_dmqi,_histeq);
//						unsigned found = files[i].rfind("bad");
//						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//						imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
//						if (found!=std::string::npos)
//							rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//					}
//					cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//					fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//					fr.getAccuracy(files);
//					fr.getAccuracyIncludingBadImages();
//					fr.getAccuracyIncludingBadImagesSubset();

					//fr.PrintScore("dfdf.txt");
					//of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;


	ofstream of;
	of.open("output_ddd32.txt");

//	//for (int large=5; large<=15; large+=2){
//	for (int large=9; large<=9; large+=2){
//		//for (int small=3; small<large;small+=2){//large; small+=2){
//		for (int small=5; small<=5;small+=2){
//			for (float alpha=1; alpha<=3.0; alpha+=0.1){
//
//				for (unsigned int i = 0;i < files.size();i++) {
//					Mat _image1;
//					_image1 = imread( dir+"/"+files[i], -1 );
//					Size size = _image1.size();
//					Mat _deno1(size,CV_8UC1);
//					Mat _dmqi(size,CV_8UC1);
//					Mat _histeq(size,CV_8UC1);
//					cvNica::Denoise(_image1,_deno1);
//					cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, large, small, alpha, 0);
//					equalizeHist(_dmqi,_histeq);
//					unsigned found = files[i].rfind("bad");
//					vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//					imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
//					if (found!=std::string::npos)
//						rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//				}
//				cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
//				fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
//				of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//				vector<string> ldf;
//				ldf<<alpha;
//				fr.PrintScore("dfdf_"+ldf+".txt");
//			}
//
////			for (float alpha=3.; alpha<=10.01; alpha+=1.){
////
////				for (unsigned int i = 0;i < files.size();i++) {
////					Mat _image1;
////					_image1 = imread( dir+"/"+files[i], -1 );
////					Size size = _image1.size();
////					Mat _deno1(size,CV_8UC1);
////					Mat _dmqi(size,CV_8UC1);
////					Mat _histeq(size,CV_8UC1);
////					cvNica::Denoise(_image1,_deno1);
////					cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi, large, small, alpha, 0);
////					equalizeHist(_dmqi,_histeq);
////					unsigned found = files[i].rfind("bad");
////					vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
////					imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
////					if (found!=std::string::npos)
////						rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
////
////				}
////				cvNica::FaceRecognition fr(dir+"/testbed",refLocation,"integrated");
////				fr.Recognition(dir+"/testbed",dataType,DB_YALEB,METHOD_CORR);
////				of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
////			}
//
//		}
//	}


//
//	for (float alpha=0.0; alpha<=100.0; alpha+=10.0){
//		//if(alpha>=60.0) alpha=100.0;
//		for (unsigned int i = 0;i < files.size();i++) {
//			cout<<i<<endl;
//			Mat _image1;
//			_image1 = imread( dir+"/"+files[i], -1 );
//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//			cvNica::Denoise(_image1,_deno1);
//			//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
//			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//			cvNica::RemoveGrainyNoise(_dmqi,_deno1,alpha);
//			equalizeHist(_deno1,_histeq);
//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/testbed3/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/testbed3/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed3/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//		}
//		cvNica::FaceRecognition fr(dir+"/testbed3",refLocation,"integrated");
//		fr.Recognition(dir+"/testbed3",dataType,DB_YALEB,METHOD_CORR);
//		//of<<large<<"\t"<<small<<"\t"<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//		of<<alpha<<"\t"<<	fr.getAccuracy(files)<<"\t"<<fr.getAccuracyIncludingBadImages()<<endl;
//		stringstream ldf;
//		ldf<<"CMUPIE_mdmhe_only_"<<alpha<<".txt";
//		string kk = ldf.str().c_str();
//		fr.PrintScore((char*)kk.c_str());
//	}

//	for (float alpha=1; alpha<=2.0001;alpha+=0.05){
//		for (int k=10; k<=100; k+=10){
//			stringstream ad;
//			stringstream adhe;
//			ad<<dir<<"/cmqi_param/a"<<alpha<<"_k"<<k;
//			adhe<<dir<<"/cmqi_param_he/a"<<alpha<<"_k"<<k;
//			mkdir(ad.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//			mkdir(adhe.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//			for (unsigned int i = 0;i < files.size();i++) {
//						Mat _image1;
//						_image1 = imread( dir+"/"+files[i], -1 );
//						Size size = _image1.size();
//						Mat _deno1(size,CV_8UC1);
//						Mat _dmqi(size,CV_8UC1);
//						Mat _histeq(size,CV_8UC1);
//						cvNica::Denoise(_image1,_deno1);
//						//cvNica::SelectiveClosingParam(_deno1,_dmqi, 5, 5, 1.4, 0);
//						cvNica::ContinuousMorphQuotImage(_deno1,_dmqi, alpha, k);
//						equalizeHist(_dmqi,_histeq);
//						unsigned found = files[i].rfind("bad");
//						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//
//
//						imwrite(ad.str()+"/"+tokens[0]+"."+dataType,_dmqi);
//						if (found!=std::string::npos)
//							rename( string(ad.str()+"/"+tokens[0]+"."+dataType).c_str() , string(ad.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//						imwrite(adhe.str()+"/"+tokens[0]+"."+dataType,_histeq);
//						if (found!=std::string::npos)
//							rename( string(adhe.str()+"/"+tokens[0]+"."+dataType).c_str() , string(adhe.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//			}
//
//
//
//		}
//	}
//
//	for (float alpha=1; alpha<=2.0001;alpha+=0.05){
//		for (int k=10; k<=100; k+=10){
//			stringstream ad;
//			stringstream adhe;
//			ad<<dir<<"/cmqi_param/a"<<alpha<<"_k"<<k;
//			//adhe<<dir<<"/cmqi_param_he/a"<<alpha<<"_k"<<k;
//			cvNica::FaceRecognition fr(ad.str(),refLocation,"integrated");
//				//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
//
//				fr.Recognition(ad.str(),dataType,DB_YALEB,METHOD_CORR);
//				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
//				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);
//
//				//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
//				//fr.getAccuracyIncludingBadImages();
//				cout<<(float)alpha<<", "<<k<<", ";
//				fr.getAccuracyIncludingBadImagesSubset();
//
//				//FileStorage abcd("dix.xml",FileStorage::WRITE);
//				//abcd << "frRecognitionResult" << fr.RecognitionResult;
//				//abcd.release();
//				ad<<"_total.txt";
//				fr.PrintScore(ad.str().c_str());
//
//		}
//	}
//	for (float alpha=1; alpha<=2.0001;alpha+=0.05){
//		for (int k=10; k<=100; k+=10){
//			stringstream adhe;
//			//ad<<dir<<"/cmqi_param/a"<<alpha<<"_k"<<k;
//			adhe<<dir<<"/cmqi_param_he/a"<<alpha<<"_k"<<k;
//			cvNica::FaceRecognition fr(adhe.str(),refLocation,"integrated");
//				//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
//
//				fr.Recognition(adhe.str(),dataType,DB_YALEB,METHOD_CORR);
//				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
//				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);
//
//				//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
//				//fr.getAccuracyIncludingBadImages();
//				cout<<(float)alpha<<", "<<k<<", ";
//				fr.getAccuracyIncludingBadImagesSubset();
//
//				//FileStorage abcd("dix.xml",FileStorage::WRITE);
//				//abcd << "frRecognitionResult" << fr.RecognitionResult;
//				//abcd.release();
//				adhe<<"_total.txt";
//				fr.PrintScore(adhe.str().c_str());
//
//		}
//	}


//	for (float alpha=1; alpha<=2.0001;alpha+=0.05){
//			for (int k=10; k<=100; k+=10){
//				stringstream ad;
//				stringstream adhe;
//				ad<<dir2<<"/cmqi_param_7_11/a"<<alpha<<"_k"<<k;
//				adhe<<dir2<<"/cmqi_param_he_7_11/a"<<alpha<<"_k"<<k;
//				mkdir(ad.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//				mkdir(adhe.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
//				for (unsigned int i = 0;i < files.size();i++) {
//							Mat _image1;
//							_image1 = imread( dir+"/"+files[i], -1 );
//							Size size = _image1.size();
//							Mat _deno1(size,CV_8UC1);
//							Mat _dmqi(size,CV_8UC1);
//							Mat _histeq(size,CV_8UC1);
//							cvNica::Denoise(_image1,_deno1);
//							//cvNica::SelectiveClosingParam(_deno1,_dmqi, 5, 5, 1.4, 0);
//							cvNica::ContinuousMorphQuotImage(_deno1,_dmqi, alpha, k);
//							equalizeHist(_dmqi,_histeq);
//							unsigned found = files[i].rfind("bad");
//							vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//
//
//							imwrite(ad.str()+"/"+tokens[0]+"."+dataType,_dmqi);
//							if (found!=std::string::npos)
//								rename( string(ad.str()+"/"+tokens[0]+"."+dataType).c_str() , string(ad.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//							imwrite(adhe.str()+"/"+tokens[0]+"."+dataType,_histeq);
//							if (found!=std::string::npos)
//								rename( string(adhe.str()+"/"+tokens[0]+"."+dataType).c_str() , string(adhe.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );
//
//				}
//
//
//
//			}
//		}
//
//		for (float alpha=1; alpha<=2.0001;alpha+=0.05){
//			for (int k=10; k<=100; k+=10){
//				stringstream ad;
//				stringstream adhe;
//				ad<<dir2<<"/cmqi_param_7_11/a"<<alpha<<"_k"<<k;
//				//adhe<<dir<<"/cmqi_param_he/a"<<alpha<<"_k"<<k;
//				cvNica::FaceRecognition fr(ad.str(),refLocation,"integrated");
//					//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
//
//					fr.Recognition(ad.str(),dataType,DB_YALEB,METHOD_CORR);
//					//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
//					//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);
//
//					//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
//					//fr.getAccuracyIncludingBadImages();
//					cout<<(float)alpha<<", "<<k<<", ";
//					fr.getAccuracyIncludingBadImagesSubset();
//
//					//FileStorage abcd("dix.xml",FileStorage::WRITE);
//					//abcd << "frRecognitionResult" << fr.RecognitionResult;
//					//abcd.release();
//					ad<<"_total.txt";
//					fr.PrintScore(ad.str().c_str());
//
//			}
//		}
//		for (float alpha=1; alpha<=2.0001;alpha+=0.05){
//			for (int k=10; k<=100; k+=10){
//				stringstream adhe;
//				//ad<<dir<<"/cmqi_param/a"<<alpha<<"_k"<<k;
//				adhe<<dir2<<"/cmqi_param_he_7_11/a"<<alpha<<"_k"<<k;
//				cvNica::FaceRecognition fr(adhe.str(),refLocation,"integrated");
//					//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
//
//					fr.Recognition(adhe.str(),dataType,DB_YALEB,METHOD_CORR);
//					//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
//					//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);
//
//					//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
//					//fr.getAccuracyIncludingBadImages();
//					cout<<(float)alpha<<", "<<k<<", ";
//					fr.getAccuracyIncludingBadImagesSubset();
//
//					//FileStorage abcd("dix.xml",FileStorage::WRITE);
//					//abcd << "frRecognitionResult" << fr.RecognitionResult;
//					//abcd.release();
//					adhe<<"_total.txt";
//					fr.PrintScore(adhe.str().c_str());
//
//			}
//		}

	for (float alpha=1; alpha<=2.001;alpha+=0.05){
				for (int k=10; k<=100; k+=10){
					stringstream ad;
					stringstream adhe;
					ad<<dir2<<"/cmqi_param_5_9/a"<<alpha<<"_k"<<k;
					adhe<<dir2<<"/cmqi_param_he_5_9/a"<<alpha<<"_k"<<k;
					mkdir(ad.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					mkdir(adhe.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
					for (unsigned int i = 0;i < files.size();i++) {
								Mat _image1;
								_image1 = imread( dir+"/"+files[i], -1 );
								if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
								Size size = _image1.size();
								Mat _deno1(size,CV_8UC1);
								Mat _dmqi(size,CV_8UC1);
								Mat _histeq(size,CV_8UC1);
								cvNica::Denoise(_image1,_deno1);
								//cvNica::SelectiveClosingParam(_deno1,_dmqi, 5, 5, 1.4, 0);
								cvNica::ContinuousMorphQuotImage(_deno1,_dmqi, alpha, k);
								equalizeHist(_dmqi,_histeq);
								unsigned found = files[i].rfind("bad");
								vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");


								imwrite(ad.str()+"/"+tokens[0]+"."+dataType,_dmqi);
								if (found!=std::string::npos)
									rename( string(ad.str()+"/"+tokens[0]+"."+dataType).c_str() , string(ad.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );

								imwrite(adhe.str()+"/"+tokens[0]+"."+dataType,_histeq);
								if (found!=std::string::npos)
									rename( string(adhe.str()+"/"+tokens[0]+"."+dataType).c_str() , string(adhe.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );

					}



				}
			}

	for (float alpha=1; alpha<=2.001;alpha+=0.05){
				for (int k=10; k<=100; k+=10){
					stringstream ad;
					stringstream adhe;
					ad<<dir2<<"/cmqi_param_5_9/a"<<alpha<<"_k"<<k;
					//adhe<<dir<<"/cmqi_param_he/a"<<alpha<<"_k"<<k;
					cvNica::FaceRecognition fr(ad.str(),refLocation,"integrated");
						//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);

						fr.Recognition(ad.str(),dataType,DB_YALEB,METHOD_CORR);
						//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
						//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);

						//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
						//fr.getAccuracyIncludingBadImages();
						cout<<(float)alpha<<", "<<k<<", ";
						fr.getAccuracyIncludingBadImagesSubset();

						//FileStorage abcd("dix.xml",FileStorage::WRITE);
						//abcd << "frRecognitionResult" << fr.RecognitionResult;
						//abcd.release();
						ad<<"_total.txt";
						fr.PrintScore(ad.str().c_str());

				}
			}
	for (float alpha=1; alpha<=2.001;alpha+=0.05){
				for (int k=10; k<=100; k+=10){
					stringstream adhe;
					//ad<<dir<<"/cmqi_param/a"<<alpha<<"_k"<<k;
					adhe<<dir2<<"/cmqi_param_he_5_9/a"<<alpha<<"_k"<<k;
					cvNica::FaceRecognition fr(adhe.str(),refLocation,"integrated");
						//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);

						fr.Recognition(adhe.str(),dataType,DB_YALEB,METHOD_CORR);
						//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
						//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);

						//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
						//fr.getAccuracyIncludingBadImages();
						cout<<(float)alpha<<", "<<k<<", ";
						fr.getAccuracyIncludingBadImagesSubset();

						//FileStorage abcd("dix.xml",FileStorage::WRITE);
						//abcd << "frRecognitionResult" << fr.RecognitionResult;
						//abcd.release();
						adhe<<"_total.txt";
						fr.PrintScore(adhe.str().c_str());

				}
			}

	of.close();
}
#endif


#ifdef MQI_varparam
int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpeg";
	else dataType = "bmp";
#endif

#ifdef DATA_TYPE_SELECT
	string dir = string(argv[1]);
	string refLocation = string(argv[2]);

	vector<string> files = vector<string>();
	cout<<dataType<<endl;
	if (nicatio::getdirType(dir,dataType,files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif



		for (int strE=3; strE<=15; strE+=2){
			stringstream ad;
			stringstream adhe;
			ad<<dir<<"/mqi_param/strE"<<strE;
			adhe<<dir<<"/mqi_param_he/strE"<<strE;
			mkdir(ad.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			mkdir(adhe.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			for (unsigned int i = 0;i < files.size();i++) {
				Mat _image1;
				_image1 = imread( dir+"/"+files[i], -1 );
				Size size = _image1.size();
				Mat _deno1(size,CV_8UC1);
				Mat _dmqi(size,CV_8UC1);
				Mat _histeq(size,CV_8UC1);
				cvNica::Denoise(_image1,_deno1);
				//cvNica::SelectiveClosingParam(_deno1,_dmqi, 5, 5, 1.4, 0);
				cvNica::MorphQuotImage(_deno1,_dmqi, strE);
				equalizeHist(_dmqi,_histeq);
				unsigned found = files[i].rfind("bad");
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");


				imwrite(ad.str()+"/"+tokens[0]+"."+dataType,_dmqi);
				if (found!=std::string::npos)
					rename( string(ad.str()+"/"+tokens[0]+"."+dataType).c_str() , string(ad.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );

				imwrite(adhe.str()+"/"+tokens[0]+"."+dataType,_histeq);
				if (found!=std::string::npos)
					rename( string(adhe.str()+"/"+tokens[0]+"."+dataType).c_str() , string(adhe.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );

			}



		}


		for (int strE=3; strE<=15; strE+=2){
			stringstream ad;
			stringstream adhe;
			ad<<dir<<"/mqi_param/strE"<<strE;
			//adhe<<dir<<"/cmqi_param_he/a"<<alpha<<"_k"<<k;
			cvNica::FaceRecognition fr(ad.str(),refLocation,"integrated");
				//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);

				fr.Recognition(ad.str(),dataType,DB_YALEB,METHOD_CORR);
				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);

				//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
				//fr.getAccuracyIncludingBadImages();
				cout<<(float)strE<<", ";
				fr.getAccuracyIncludingBadImagesSubset();

				//FileStorage abcd("dix.xml",FileStorage::WRITE);
				//abcd << "frRecognitionResult" << fr.RecognitionResult;
				//abcd.release();
				ad<<"_total.txt";
				fr.PrintScore(ad.str().c_str());

		}

		for (int strE=3; strE<=15; strE+=2){
			stringstream adhe;
			//ad<<dir<<"/cmqi_param/a"<<alpha<<"_k"<<k;
			adhe<<dir<<"/mqi_param_he/strE"<<strE;
			cvNica::FaceRecognition fr(adhe.str(),refLocation,"integrated");
				//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);

				fr.Recognition(adhe.str(),dataType,DB_YALEB,METHOD_CORR);
				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
				//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);

				//cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
				//fr.getAccuracyIncludingBadImages();
				cout<<(float)strE<<", ";
				fr.getAccuracyIncludingBadImagesSubset();

				//FileStorage abcd("dix.xml",FileStorage::WRITE);
				//abcd << "frRecognitionResult" << fr.RecognitionResult;
				//abcd.release();
				adhe<<"_total.txt";
				fr.PrintScore(adhe.str().c_str());

		}


}
#endif



#ifdef illuminationNormalization

// Run configurations
// /cygdrive/e/Documents/Nicatio/Research/DB/Face/yalebDB/smqi/
// /cygdrive/e/Documents/Nicatio/Research/DB/Face/yalebDB/smqi/ref_list2.txt

int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpg";
	else if (DATA_TYPE == 4) dataType = "raw";
	else dataType = "bmp";
#endif

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


#ifdef DATA_TYPE_SELECT
		string dir = string(argv[1]);
		string refLocation = string(argv[2]);


		vector<string> files = vector<string>();
		cout<<dataType<<endl;
		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif


#ifdef TXT
		string dir = string(argv[1]);
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		if (nicatio::getdirType(dir,"txt",files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif

#ifdef PGM
		string dir = string(argv[1]);
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		if (nicatio::getdirType(dir,"pgm",files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif

#ifdef BMP
		string dir = string(argv[1]);
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		if (nicatio::getdirType(dir,"bmp",files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif

#ifdef PCAP
		string dir = string(argv[1]);
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		if (nicatio::getdirType(dir,"pcap",files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif


#ifdef FR_for_integrated
		cvNica::FaceRecognition fr(dir,refLocation,"integrated");
		//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);

		fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORR);
		//fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORRBIN);
		//fr.Recognition(dir,dataType,DB_YALEB,METHOD_L2NORM2);

		cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
		cout<<"2 "<<fr.getAccuracyIncludingBadImages()<<" "<<endl;
		fr.getAccuracyIncludingBadImagesSubset();

		FileStorage abcd("dix.xml",FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		abcd.release();

		fr.PrintScore(argv[3]);

//		string fileout = string(argv[3]);
//
//		ofstream fw;
//
//				float ra = fr.getAccuracy(files);
//				float rb = fr.getAccuracyIncludingBadImages();
//
//				fw.open(fileout.c_str(),ios::out);
//				fw<<"1 "<<ra<<" "<<endl;
//				fw<<"2 "<<rb<<" "<<endl;
//				fr.getAccuracyIncludingBadImagesSubset(fw);
//				fw.close();




//		FileStorage abcd2("dix3.xml",FileStorage::WRITE);
//		abcd2 << "frRecognitionResult" << fr.RecognitionScore;
//		abcd2.release();

		///cygdrive/e/Documents/Nicatio/Research/DB/Face/yalebDB/smqi
		///cygdrive/e/Documents/Nicatio/Research/DB/Face/yalebDB/smqi/ref_list2.txt
#endif


#ifdef FR_for_separated
		cvNica::FaceRecognition fr(dir,refLocation,"separated");
		string testDir = string(argv[3]);
		//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
		fr.Recognition(testDir,dataType,DB_YALEB,METHOD_CORR);
		//fr.Recognition(testDir,dataType,DB_YALEB,METHOD_PCA);
		//fr.Recognition(testDir,dataType,DB_YALEB,METHOD_L2NORM);
//		cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
//		cout<<"2 "<<fr.getAccuracyIncludingBadImages()<<" "<<endl;
//		fr.getAccuracyIncludingBadImagesSubset();

		FileStorage abcd(argv[4],FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		abcd.release();

		FileStorage abcd2(argv[5],FileStorage::WRITE);
		abcd2 << "frRecognitionResult" << fr.RecognitionScore;
		abcd2.release();
#endif



#ifdef FR_REGION
		int pos[52]= {0,0,167,10,	 // ÀÌ¸¶
		0,11,64,65,	 // ¿Þ´«
		65,11,102,65,	 // ¹Ì°£
		103,11,167,65,	 // ¿À¸¥´«
		0,66,50,114,	 // ÄÚ ¿ÞÂÊ
		51,66,116,114,	 // ÄÚ
		117,66,167,114,	 // ÄÚ ¿À¸¥ÂÊ
		0,115,83,134,	 // ÀÎÁß ¿ÞÂÊ
		84,115,167,134,   // ÀÎÁß ¿À¸¥ÂÊ
		0,135,39,162,	 // ÀÔ ¿ÞÂÊ
		40,135,127,162,	 // ÀÔ
		128,135,167,162,	 // ÀÔ ¿À¸¥ÂÊ
		0,163,167,191};	 // ÅÎ
		for (int i=0; i<13; i++) {
		ofstream fw;
		stringstream df;
		vector<string> tokens = nicatio::StringTokenizer::getTokens(dir,"/");

		df<<tokens[tokens.size()-1]<<i<<"_result.txt";
		string dff = df.str().c_str();


		cvNica::FaceRecognition fr(dir,refLocation);
		//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
		fr.Recognition(dir,dataType,DB_YALEB,METHOD_CORR,0,0,pos[i*4],pos[i*4+1],pos[i*4+2],pos[i*4+3]);
		//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR);

		float ra = fr.getAccuracy(files);
		float rb = fr.getAccuracyIncludingBadImages();

		fw.open(df.str().c_str(),ios::out);
		fw<<"1 "<<ra<<" "<<endl;
		fw<<"2 "<<rb<<" "<<endl;
		fr.getAccuracyIncludingBadImagesSubset(fw);
		fw.close();
		FileStorage abcd("dix.xml",FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		stringstream adf;
		adf<<i<<"n.xml";
		FileStorage abcd2(adf.str(),FileStorage::WRITE);
		abcd2 << "frRecognitionScore" << fr.RecognitionScore;
		abcd2.release();
		abcd.release();
		}
#endif



#ifdef FA
		//cvNica::FaceAnalysis fhhhah();

//		Mat dsf = Mat::zeros(3,3,CV_32FC1);
//		dsf.at<float>(2,2) = 255;
//
//		Mat dsf2; dsf.convertTo(dsf2,CV_8UC1);
//		imwrite("dfdf.bmp",dsf2);

		cvNica::FaceAnalysis fa(dir,"pgm");


		                //1
		                //fa.draw(64,2);

		                //2
		                //fa.setGroup("faceindex.bmp");
		                //fa.mse(64);

		                //3
		                //fa.correlationPic(64,2,0);
		                fa.EuDist(64,2,0);
		//fa.setGroup("faceindex.bmp");
		//fa.setGroup("faceindexweight1.bmp");

		//fa.draw(64,2);
		//fa.mse(64);
//
#endif

#ifdef Fileout
		ofstream FileOut;
		FileOut.open("result.txt",(ios::out));
		int nHist = 16;//32;
		float offset = PI * (0.5-(float)(180.0/(float)nHist)/360.0);

		double t = (double)getTickCount();
#endif

#ifdef PCAP

		ofstream FilePcap2TS;
		ofstream FilePcap2ES;
		ofstream File2642yuv;
		ofstream Filets2yuv;
		ofstream FileList;
		ofstream FileListenc;


		FilePcap2TS.open("pcap2ts.bat",(ios::out));
		FilePcap2ES.open("pcap2es.bat",(ios::out));
		File2642yuv.open("264yuv.bat",(ios::out));
		Filets2yuv.open("ts2yuv.bat",(ios::out));
		FileList.open("list.bat",(ios::out));
		FileListenc.open("list_enc.bat",(ios::out));


#endif


		for (unsigned int i = 0;i < files.size();i++) {
#ifdef PCAP
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			FilePcap2TS<<"PCAPtoTS.exe	"<<tokens[0]<<".pcap"<<endl;
			FilePcap2ES<<"PCAPtoES.exe	"<<tokens[0]<<".pcap	"<<1234<<endl;

			File2642yuv<<"ffmpeg.exe	-y	-i	"<<tokens[0]<<".264	-pix_fmt uyvy422	"<<tokens[0]<<".yuv"<<endl;
			Filets2yuv<<"ffmpeg.exe	-y	-i	"<<tokens[0]<<".ts	-pix_fmt uyvy422	"<<tokens[0]<<".yuv"<<endl;

			FileList<<tokens[0]<<".yuv	"<<tokens[0]<<".pcap	progressive"<<endl;
			FileListenc<<tokens[0]<<".yuv	"<<tokens[0]<<".pcap	progressive	pes"<<endl;

#endif
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
#ifdef CMUCROP
			stringstream a3;
			a3<<dir<<"/"<<files[i];
			vector<double> position = nicatio::readFileSingleLine(a3.str().c_str());

			int adf = 34;
			adf += 34;
#endif

#ifdef ROTATEFACEANGLEDETECTION
//			Mat _temp1 =  imread( dir+"/"+files[i], -1 );
//			//Mat temp1; resize(dtemp1,temp1,Size(0,0),0.5,0.5);
//			//GaussianBlur(temp1,temp1,Size(5,5),1.0);
//			int r2 = _temp1.cols;
//			int r = r2>>1;
//			Mat temp1 = _temp1(Rect(0,0,r2,r2));
//
//			//Mat mask =  Mat::ones(temp1.size(),CV_8U)*255;
//			Mat mask =  Mat::zeros(Size(r2*2+1,r2*2+1),CV_8U);
//
//			circle(mask,Point(r2,r2),r2-1,255,-1,CV_AA);
//			resize(mask,mask,temp1.size());
//						namedWindow( "c", CV_WINDOW_AUTOSIZE );
//						imshow( "c",mask );
//						waitKey(0);
//			double rotateAngle = rand() % 4500;
//			//rotateAngle -= 450;
//			rotateAngle /= 100;
//
//			rotateAngle = 0;
//
//			Mat temp23 = cvNica::rotateImage(temp1, rotateAngle, 0, 1);
//			Mat rotated_mask = cvNica::rotateImage(mask, rotateAngle, 0);

			Mat _temp1 =  imread( dir+"/"+files[i], -1 );
			//Mat temp1; resize(dtemp1,temp1,Size(0,0),0.5,0.5);
			//GaussianBlur(temp1,temp1,Size(5,5),1.0);
			int r2 = _temp1.cols;
			Mat temp1 = _temp1(Rect(0,0,r2,r2));

			//Mat mask =  Mat::ones(temp1.size(),CV_8U)*255;
			Mat mask =  Mat::zeros(Size(r2*2+1,r2*2+1),CV_8U);

			circle(mask,Point(r2,r2),r2-1,255,-1,CV_AA);
			resize(mask,mask,temp1.size());

			double rotateAngle = rand() % 4500;
			//rotateAngle -= 450;
			rotateAngle /= 100;

			//rotateAngle = 0;








			Mat temp23 = cvNica::rotateImage(temp1, rotateAngle, 0, 1);
			//Mat rotated_mask = cvNica::rotateImage(mask, rotateAngle, 1);


			Mat temp2,colortemp2,colortemp3;
			//cvNica::BinFace(temp23,temp2,135,109);
			cvNica::BinFaceMask(temp23,mask,temp2,temp1.size(),135,109);

			//Mat temp333;
			//cvNica::BinFace(temp1,temp333,135,109);





			Mat output = Mat::zeros(temp2.size(), CV_8UC3);
			std::vector < std::vector<cv::Point2i > > blobs;

			vector<Vec4i> lines;
			cvNica::FindBlobs(temp2, blobs);

			// Randomy color the blobs

			for(size_t m=0; m < blobs.size(); m++) {
				unsigned char r = 0;//255 * (rand()/(1.0 + RAND_MAX));
				unsigned char g = 0;//255 * (rand()/(1.0 + RAND_MAX));
				unsigned char b = 0;//255 * (rand()/(1.0 + RAND_MAX));
				if (blobs[m].size()<15) {
					for(size_t n=0; n < blobs[m].size(); n++) {
						int x = blobs[m][n].x;
						int y = blobs[m][n].y;
						temp2.at<uchar>(y,x) = b;

						//output.at<Vec3b>(y,x)[0] = b;
						//output.at<Vec3b>(y,x)[1] = g;
						//output.at<Vec3b>(y,x)[2] = r;
					}
				}
			}
//			    namedWindow( "m", CV_WINDOW_AUTOSIZE );
//			    imshow("m", temp2);
//			    namedWindow( "n", CV_WINDOW_AUTOSIZE );
//			    imshow("n", output);
//			    waitKey(0);





			cvtColor( temp2, colortemp2, CV_GRAY2BGR );
		    //HoughLinesP( temp2, lines, 1, CV_PI/180, 30, 20, 4 );
			//HoughLinesP( temp2, lines, 1, CV_PI/180, 20, 15, 4 );
			HoughLinesP( temp2, lines, 1, CV_PI/180, 30, 20, 4 );

		    vector<int> hist(nHist,0);
		    vector<float> histSum(nHist,0);
		    vector<int> histSumX(nHist,0);
		    vector<int> histSumY(nHist,0);

		    int sum = lines.size();
		    int sumsq = 0;
			int *t = new int[sum];
		    for( size_t k = 0; k < lines.size(); k++ )
		    {
		        line( colortemp2, Point(lines[k][0], lines[k][1]),
		            Point(lines[k][2], lines[k][3]), Scalar(0,0,255), 1, 8 );
				float angle = atan2(lines[k][3]-lines[k][1],lines[k][2]-lines[k][0]);
		        short temp = (short)((angle + offset)/PI*nHist);
				if (temp<0) temp = nHist-1;

				hist[temp]++;
				histSum[temp]+=angle;
				histSumX[temp]+=lines[k][3]-lines[k][1];
				histSumY[temp]+=lines[k][2]-lines[k][0];
				t[k] = temp;


		        //cout<<angle<<endl;
		    }
		    for (short j=0;j<nHist;j++){
		    	sumsq += hist[j]*hist[j];
		    }
		    double std = sqrt( ((double)sumsq/nHist) - ((double)sum/nHist)*((double)sum/nHist));
		    int max = hist[0];
			int maxIndex = 0;
			int peakPoints = 0;
			int peakSumX = 0;
			int peakSumY = 0;
		    for (short j=0;j<nHist;j++)
		    {
		    	if (max < hist[j]) {
		    		max = hist[j];
		    		maxIndex = j;
		    	}
		    	//cout<<" "<<j<<": "<<hist[j]<<" : "<<(((double)hist[j]-((double)sum/nHist))/(double)std)<<endl;
		    }
		    for (short j=0;j<nHist;j++)
		    {
				//if ((((double)hist[j]-((double)sum/nHist))/std)>2.0 && (abs(j-maxIndex)<7)) {
		    	if ((((double)hist[j]-((double)sum/nHist))/std)>=1.5 && (abs(j-maxIndex)<4)) {
					peakSumX += histSumX[j];
					peakSumY += histSumY[j];
					peakPoints++;

				    for( size_t k = 0; k < lines.size(); k++ )
				    {
				    	if (j == t[k]) {
							line( colortemp2, Point(lines[k][0], lines[k][1]),
								Point(lines[k][2], lines[k][3]), Scalar(255,0,0), 1, 8 );
				    	}
				    }
				}
		    }

//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a",colortemp2 );
//			waitKey(0);

		    //float imageAngle = histSum[maxIndex]/hist[maxIndex]/PI*180;
		    //float imageAngle = atan2(histSumX[maxIndex],histSumY[maxIndex])/PI*180;

		    double imageAngle;
		    if (peakPoints) {
		    	imageAngle = atan2(peakSumX,peakSumY)/PI*180;
		    } else {
		    	imageAngle = atan2(histSumX[maxIndex],histSumY[maxIndex])/PI*180;
		    }

		    if (hist[maxIndex]==0) imageAngle = 0;


//		    imwrite(dir+"/faceRotBinRaw/"+files[i]+".bmp",temp2);
//		    double diff = (imageAngle+rotateAngle);
//		    if (diff<0) diff*=-1;
//		    cout<<"imageAngle vs Actual: "<<imageAngle<<" / "<<rotateAngle<<" / "<<diff<<endl;
//		    if (diff>10) {
//		    	//Mat temp323 = cvNica::rotateImage(temp23, imageAngle, 0);
//		    	imwrite(dir+"/faceRotFail/a/"+files[i]+".bmp",temp23);
//		    	imwrite(dir+"/faceRotFail/"+files[i]+".bmp",colortemp2);
//		    } else {
//		    	//Mat temp323 = cvNica::rotateImage(temp23, imageAngle, 0);
//		    	imwrite(dir+"/faceRot/a/"+files[i]+".bmp",temp23);
//		    	imwrite(dir+"/faceRot/"+files[i]+".bmp",colortemp2);
//		    }
//		    //imwrite(dir+"/faceRotBin/"+files[i]+".bmp",temp2);



			Mat df;
			Mat temp1_double;
			Mat mask_double;
			//Mat temp1;
			cvNica::DoGMask(temp23,mask,temp1,mask.size(),0.2,1,-2,0,0,0,10);
//					InputArray 						_src,
//					InputArray 						_mask,
//					OutputArray						_dst,
//					Size							maskSize,
//					const double&					gamma,
//					const double&					sigma0,
//					const double&					sigma1,
//					const int&						sx,
//					const int&						sy,
//					const int&						mask_,
//					const double&					do_norm)
//			cvNica::DoG(temp1,temp1,0.2,1,-2,0,0,0,10);


			Mat correct = cvNica::rotateImage(temp1, imageAngle, 0, 1);


			Mat df_double(temp1.size(),CV_32FC1);
			correct.convertTo(temp1_double,CV_32FC1);
			mask.convertTo(mask_double,CV_32FC1);

			multiply(temp1_double,mask_double,df_double);

			df_double /= 255;
			df_double.convertTo(df,CV_8UC1);

//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a",df );
//			waitKey(0);

			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"\\circledogrotc\\"+tokens[0]+".pgm",df);
				rename( string(dir+"\\circledogrotc\\"+tokens[0]+".pgm").c_str() , string(dir+"\\circledogrotc\\"+tokens[0]+".pgm.bad").c_str() );
			} else {
				imwrite(dir+"\\circledogrotc\\"+files[i],df);
			}



		    FileOut<<imageAngle<<"\t"<<rotateAngle<<"\t"<<(((double)hist[maxIndex]-((double)sum/nHist))/std)<<"\t"<<peakPoints<<endl;
			//FileOut.write(aaa.str().c_str(),sizeof(aaa.str().c_str()));


#endif


#ifdef ROTATEFACEANGLEDETECTIONDMQI

			Mat temp1 =  imread( dir+"/"+files[i], -1 );
			//Mat temp1; resize(dtemp1,temp1,Size(0,0),0.5,0.5);
			//GaussianBlur(temp1,temp1,Size(5,5),1.0);

			Mat mask =  Mat::ones(temp1.size(),CV_8U)*255;

			double rotateAngle = rand() % 4500;
			//rotateAngle -= 450;
			rotateAngle /= 100;
			//rotateAngle = 0;
			//rotateAngle = 45;

			Mat temp23 = cvNica::rotateImage(temp1, rotateAngle, 0, 0, 0x000000);
			Mat rotated_mask = cvNica::rotateImage(mask, rotateAngle, 0);
			rotated_mask = 255- rotated_mask;

			Mat temp2,colortemp2,colortemp3;
			//cvNica::BinFace(temp23,temp2,135,109);
			//cvNica::BinFaceMask(temp23,rotated_mask,temp2,temp1.size(),135,109);

			Mat temp222,temp223;
		//cvNica::Denoise(temp23,temp222);
			cvNica::DynamicMorphQuotImage(temp23,temp223);
			bitwise_or(temp223,rotated_mask,temp2);
			//equalizeHist(temp223,temp223);

			//cvNica::IntensityShifting(temp223, temp2, 228);
			threshold(temp2,temp2,224.0,255.0,THRESH_BINARY_INV);


			//Mat temp333;
			//cvNica::BinFace(temp1,temp333,135,109);
//			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//			imshow( "d",temp223);
//			waitKey(0);
//			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//			imshow( "d",temp2);
//			waitKey(0);




			Mat output = Mat::zeros(temp2.size(), CV_8UC3);
			std::vector < std::vector<cv::Point2i > > blobs;

			vector<Vec4i> lines;
			cvNica::FindBlobs(temp2, blobs);

			// Randomy color the blobs

			for(size_t m=0; m < blobs.size(); m++) {
				unsigned char r = 0;//255 * (rand()/(1.0 + RAND_MAX));
				unsigned char g = 0;//255 * (rand()/(1.0 + RAND_MAX));
				unsigned char b = 0;//255 * (rand()/(1.0 + RAND_MAX));
				if (blobs[m].size()<15) {
					for(size_t n=0; n < blobs[m].size(); n++) {
						int x = blobs[m][n].x;
						int y = blobs[m][n].y;
						temp2.at<uchar>(y,x) = b;

						//output.at<Vec3b>(y,x)[0] = b;
						//output.at<Vec3b>(y,x)[1] = g;
						//output.at<Vec3b>(y,x)[2] = r;
					}
				}
			}
//			    namedWindow( "m", CV_WINDOW_AUTOSIZE );
//			    imshow("m", temp2);
//			    namedWindow( "n", CV_WINDOW_AUTOSIZE );
//			    imshow("n", output);
//			    waitKey(0);





			cvtColor( temp2, colortemp2, CV_GRAY2BGR );
		    //HoughLinesP( temp2, lines, 1, CV_PI/180, 30, 20, 4 );
			//HoughLinesP( temp2, lines, 1, CV_PI/180, 20, 15, 4 );
			HoughLinesP( temp2, lines, 1, CV_PI/180, 30, 20, 3 );

		    vector<int> hist(nHist,0);
		    vector<float> histSum(nHist,0);
		    vector<int> histSumX(nHist,0);
		    vector<int> histSumY(nHist,0);

		    int sum = lines.size();
		    int sumsq = 0;
			int *t = new int[sum];
		    for( size_t k = 0; k < lines.size(); k++ )
		    {
		        line( colortemp2, Point(lines[k][0], lines[k][1]),
		            Point(lines[k][2], lines[k][3]), Scalar(0,0,255), 1, 8 );
				float angle = atan2(lines[k][3]-lines[k][1],lines[k][2]-lines[k][0]);
		        short temp = (short)((angle + offset)/PI*nHist);
				if (temp<0) temp = nHist-1;

				hist[temp]++;
				histSum[temp]+=angle;
				histSumX[temp]+=lines[k][3]-lines[k][1];
				histSumY[temp]+=lines[k][2]-lines[k][0];
				t[k] = temp;


		        //cout<<angle<<endl;
		    }
		    for (short j=0;j<nHist;j++){
		    	sumsq += hist[j]*hist[j];
		    }
		    double std = sqrt( ((double)sumsq/nHist) - ((double)sum/nHist)*((double)sum/nHist));
		    int max = hist[0];
			int maxIndex = 0;
			int peakPoints = 0;
			int peakSumX = 0;
			int peakSumY = 0;
		    for (short j=0;j<nHist;j++)
		    {
		    	if (max < hist[j]) {
		    		max = hist[j];
		    		maxIndex = j;
		    	}
		    	//cout<<" "<<j<<": "<<hist[j]<<" : "<<(((double)hist[j]-((double)sum/nHist))/(double)std)<<endl;
		    }
		    for (short j=0;j<nHist;j++)
		    {
				//if ((((double)hist[j]-((double)sum/nHist))/std)>2.0 && (abs(j-maxIndex)<7)) {
		    	if ((((double)hist[j]-((double)sum/nHist))/std)>=1.5 && (abs(j-maxIndex)<4)) {
					peakSumX += histSumX[j];
					peakSumY += histSumY[j];
					peakPoints++;

				    for( size_t k = 0; k < lines.size(); k++ )
				    {
				    	if (j == t[k]) {
							line( colortemp2, Point(lines[k][0], lines[k][1]),
								Point(lines[k][2], lines[k][3]), Scalar(255,0,0), 1, 8 );
				    	}
				    }
				}
		    }

//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a",colortemp2 );
//			waitKey(0);

		    //float imageAngle = histSum[maxIndex]/hist[maxIndex]/PI*180;
		    //float imageAngle = atan2(histSumX[maxIndex],histSumY[maxIndex])/PI*180;

		    double imageAngle;
		    if (peakPoints) {
		    	imageAngle = atan2(peakSumX,peakSumY)/PI*180;
		    } else {
		    	imageAngle = atan2(histSumX[maxIndex],histSumY[maxIndex])/PI*180;
		    }

		    if (hist[maxIndex]==0) imageAngle = 0;


		    imwrite(dir+"/faceRotBinRaw/"+files[i]+".bmp",temp2);
//		    double diff = (imageAngle+rotateAngle);
//		    if (diff<0) diff*=-1;
//		    cout<<"imageAngle vs Actual: "<<imageAngle<<" / "<<rotateAngle<<" / "<<diff<<endl;
//		    if (diff>10) {
//		    	//Mat temp323 = cvNica::rotateImage(temp23, imageAngle, 0);
//		    	imwrite(dir+"/faceRotFail/a/"+files[i]+".bmp",temp23);
//		    	imwrite(dir+"/faceRotFail/"+files[i]+".bmp",colortemp2);
//		    } else {
//		    	//Mat temp323 = cvNica::rotateImage(temp23, imageAngle, 0);
//		    	imwrite(dir+"/faceRot/a/"+files[i]+".bmp",temp23);
//		    	imwrite(dir+"/faceRot/"+files[i]+".bmp",colortemp2);
//		    }
//		    //imwrite(dir+"/faceRotBin/"+files[i]+".bmp",temp2);
		    FileOut<<imageAngle<<"\t"<<rotateAngle<<"\t"<<(((double)hist[maxIndex]-((double)sum/nHist))/std)<<"\t"<<peakPoints<<endl;
			//FileOut.write(aaa.str().c_str(),sizeof(aaa.str().c_str()));


#endif


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

#ifdef DOGCIRCLE
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			Mat temp2;

			cvNica::DoG(_image1,temp2,0.2,1,-2,0,0,0,10);


			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"\\dogcircle\\"+tokens[0]+".pgm",temp2);
				rename( string(dir+"\\dogcircle\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dogcircle\\"+tokens[0]+".pgm.bad").c_str() );

			} else {

				imwrite(dir+"\\dogcircle\\"+files[i],temp2);

			}
#endif

#ifdef RAW2BMP
			cout << files[i] <<"\r"<< endl;



			FILE * f = fopen((dir+"/"+files[i]).c_str(),"rb");
			char *pixels1 = new char[768*576];
			char *pixels2 = new char[768*576];
			char *pixels3 = new char[768*576];

			fread(pixels1,768*576,1,f);
			fread(pixels2,768*576,1,f);
			fread(pixels3,768*576,1,f);

			fclose(f);


			//Mat img(768,576,CV_8UC3,pixels);



			Mat _image1(576,768,CV_8UC1,pixels1);
			Mat _image2(576,768,CV_8UC1,pixels2);
			Mat _image3(576,768,CV_8UC1,pixels3);
			//_image1 = imread( dir+"/"+files[i], -1 );
			cout << _image1.cols <<"\r"<< endl;
			cout << _image1.rows <<"\r"<< endl;
			Mat _image;
			vector<Mat> k;
			k.push_back(_image1);
			k.push_back(_image2);
			k.push_back(_image3);
			merge(k,_image);

						delete [] pixels1;
						delete [] pixels2;
						delete [] pixels3;
			if (_image.type()!= CV_8UC1) cvtColor(_image, _image, CV_RGB2GRAY);
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/bmp/"+tokens[0]+".bmp",_image);

#endif


#ifdef DOG
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Mat temp2;

			cvNica::DoG(_image1,temp2,0.2,1,-2,0,0,0,10);


			unsigned found = files[i].rfind("bad");
						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
						imwrite(dir+"/dog/"+tokens[0]+"."+dataType,temp2);
						if (found!=std::string::npos)
							rename( string(dir+"/dog/"+tokens[0]+"."+dataType).c_str() , string(dir+"/smqi/"+tokens[0]+"."+dataType+".bad").c_str() );


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

#ifdef crop
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			//if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Mat ccc = Mat(_image1,Rect(0,0,_image1.cols,_image1.rows-12));
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+tokens[0]+".png",ccc);

			//imwrite("dmqi.bmp",_dmqi);
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			//nicatio::HistEqualize(_deno2.data,_histeq.data,_image1.cols,_image1.rows);
			//nicatio::HistEqualize2(_dmqi.data,_histeq2.data,_image1.cols,_image1.rows);
			//imwrite("histeq.bmp",_histeq);
			//imwrite("histeq2.bmp",_histeq2);
			//_deno2=_dmqi;
			//cvNica::IntensityShifting(_histeq, _deno2, 128);
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\dmqi\\"+tokens[0]+".pgm",_deno2);
//				rename( string(dir+"\\dmqi\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dmqi\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\dmqi\\"+files[i],_deno2);
//
//			}


				//imwrite(dir+"\\dmqi\\"+files[i],_deno2);


#endif


#ifdef DMQI
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			//Mat _histeq2(size,CV_8UC1);
			//nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			cvNica::Denoise(_image1,_deno1);
			//imwrite("ori.bmp",_image1);
			//imwrite("deno.bmp",_deno1);

			cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
			cvNica::RemoveGrainyNoise(_dmqi,_deno2,30);
			equalizeHist(_deno2,_histeq);
			//cvNica::RemoveGrainyNoise(_dmqi,_histeq,30);
			//cvNica::RemoveGrainyNoise(_deno1,_deno2,50);
//
//			cvNica::RemoveGrainyNoise(_dmqi,_histeq,100);
//			//nicatio::HistEqualize(_dmqi.data,_deno2.data,_image1.cols,_image1.rows);
//
			unsigned found = files[i].rfind("bad");
						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
						imwrite(dir+"/dmqi_wRGN_256/"+tokens[0]+"."+dataType,_deno2);
						if (found!=std::string::npos)
							rename( string(dir+"/dmqi_wRGN_256/"+tokens[0]+"."+dataType).c_str() , string(dir+"/dmqi_wRGN_256/"+tokens[0]+"."+dataType+".bad").c_str() );

						imwrite(dir+"/dmqi_wRGN_256_he/"+tokens[0]+"."+dataType,_histeq);
						if (found!=std::string::npos)
							rename( string(dir+"/dmqi_wRGN_256_he/"+tokens[0]+"."+dataType).c_str() , string(dir+"/dmqi_wRGN_256_he/"+tokens[0]+"."+dataType+".bad").c_str() );

			//imwrite("dmqi.bmp",_dmqi);
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			//nicatio::HistEqualize(_deno2.data,_histeq.data,_image1.cols,_image1.rows);
			//nicatio::HistEqualize2(_dmqi.data,_histeq2.data,_image1.cols,_image1.rows);
			//imwrite("histeq.bmp",_histeq);
			//imwrite("histeq2.bmp",_histeq2);
			//_deno2=_dmqi;
			//cvNica::IntensityShifting(_histeq, _deno2, 128);
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"/dmqi/"+tokens[0]+".pgm",_histeq);
//				rename( string(dir+"/dmqi/"+tokens[0]+".pgm").c_str() , string(dir+"/dmqi/"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"/dmqi/"+files[i],_histeq);
//
//			}


				//imwrite(dir+"\\dmqi\\"+files[i],_deno2);


#endif

#ifdef DMQIHE
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			//Mat _histeq2(size,CV_8UC1);
			//nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			cvNica::Denoise(_image1,_deno1);
			//imwrite("ori.bmp",_image1);
			//imwrite("deno.bmp",_deno1);
			cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
			//cvNica::RemoveGrainyNoise(_dmqi,_deno1,50);
			//cvNica::RemoveGrainyNoise(_deno1,_deno2,50);

			cvNica::RemoveGrainyNoise(_dmqi,_deno1,30);
			nicatio::HistEqualize(_deno1.data,_histeq.data,_image1.cols,_image1.rows);

			unsigned found = files[i].rfind("bad");
						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
						imwrite(dir+"/dmqihe/"+tokens[0]+"."+dataType,_histeq);
						if (found!=std::string::npos)
							rename( string(dir+"/dmqihe/"+tokens[0]+"."+dataType).c_str() , string(dir+"/dmqihe/"+tokens[0]+"."+dataType+".bad").c_str() );


			//imwrite("dmqi.bmp",_dmqi);
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			//nicatio::HistEqualize(_deno2.data,_histeq.data,_image1.cols,_image1.rows);
			//nicatio::HistEqualize2(_dmqi.data,_histeq2.data,_image1.cols,_image1.rows);
			//imwrite("histeq.bmp",_histeq);
			//imwrite("histeq2.bmp",_histeq2);
			//_deno2=_dmqi;
			//cvNica::IntensityShifting(_histeq, _deno2, 128);
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\dmqi\\"+tokens[0]+".pgm",_deno2);
//				rename( string(dir+"\\dmqi\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dmqi\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\dmqi\\"+files[i],_deno2);
//
//			}


				//imwrite(dir+"\\dmqi\\"+files[i],_deno2);


#endif

#ifdef CMQI

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
//			resize(_image1, _image1, Size(0,0), 0.5, 0.5);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			cvNica::Denoise(_image1,_deno1);


			//Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			//nicatio::MedianFilter(_image1.data,_deno1.data,_image1.cols,_image1.rows);
			//nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			//cvNica::Denoise(_image1,_deno1);

			cvNica::Denoise(_image1,_deno1);
			//_deno1=_image1;
			//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);

			//cvNica::SelectiveMorphQuotImage(_deno1,_deno2,0);
			cvNica::ContinuousMorphQuotImage(_deno1,_dmqi,1.7,20);

//							namedWindow( "a", CV_WINDOW_AUTOSIZE );
//							imshow( "a",  _dmqi );
//							waitKey(0);
			//_dmqi=_deno1;
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			//_dmqi = 255-_dmqi;

			equalizeHist(_dmqi,_histeq);



			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);





			//nicatio::MedianFilter(_histeq.data,_deno2.data,_image1.cols,_image1.rows);
			//nicatio::Gamma(_dmqi.data,_deno2.data,_image1.cols,_image1.rows,2.0);
			//nicatio::Gamma(_histeq.data,_deno2.data,_image1.cols,_image1.rows,25.0);
			//_histeq = 255-_histeq;
			//equalizeHist(_dmqi,_histeq);
//			double mmin, mmax;
//			minMaxIdx(_histeq,&mmin,&mmax);
//			_deno2 = _histeq - mmin;
//			_deno2 *= 255.0/(mmax-mmin);
			//Mat _deno3;
			//GaussianBlur(_histeq, _deno2, Size(3,3), 1.0, 1.0, BORDER_DEFAULT);


			//_deno2;// = _deno3(Rect(1,1,_deno1.size().width,_deno1.size().height));
			//_deno2=_dmqi;

			//_deno2=_histeq;

			//cvNica::IntensityShifting(_histeq, _deno2, 220);
//			imwrite("ori.bmp",_image1);
//			imwrite("dmqi.bmp",_dmqi);
//			imwrite("histeq.bmp",_deno2);

			//cvNica::IntensityShifting(_histeq, _deno2, 128);



			//Rect myROI(2, 2, 126, 146);
			//Mat croppedImage;
			//Mat(_histeq, myROI).copyTo(_deno2);
			//imwrite(buffer5.str(),croppedImage);

			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/cmqi6/"+tokens[0]+"."+dataType,_dmqi);
			if (found!=std::string::npos)
				rename( string(dir+"/cmqi6/"+tokens[0]+"."+dataType).c_str() , string(dir+"/cmqi69/"+tokens[0]+"."+dataType+".bad").c_str() );

			imwrite(dir+"/cmqihe6/"+tokens[0]+"."+dataType,_histeq);
			if (found!=std::string::npos)
				rename( string(dir+"/cmqihe6/"+tokens[0]+"."+dataType).c_str() , string(dir+"/cmqihe6/"+tokens[0]+"."+dataType+".bad").c_str() );


			cvNica::ContinuousClosing(_deno1,_dmqi,1.7,20);

			imwrite(dir+"/cmqiclosing6/"+tokens[0]+"."+dataType,_dmqi);
			if (found!=std::string::npos)
				rename( string(dir+"/cmqiclosing6/"+tokens[0]+"."+dataType).c_str() , string(dir+"/cmqiclosing6/"+tokens[0]+"."+dataType+".bad").c_str() );





//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/deno/"+tokens[0]+"."+dataType,_deno2);
//			if (found!=std::string::npos)
//				rename( string(dir+"/deno/"+tokens[0]+"."+dataType).c_str() , string(dir+"/deno/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif


#ifdef SMQI_adaptive
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			cvNica::Denoise(_image1,_deno1);
			cvNica::AdaptiveMorphQuotImage(_deno1,_dmqi,0.05);
			equalizeHist(_dmqi,_histeq);
			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/testbed/"+tokens[0]+"."+dataType,_histeq);
			if (found!=std::string::npos)
				rename( string(dir+"/testbed/"+tokens[0]+"."+dataType).c_str() , string(dir+"/testbed/"+tokens[0]+"."+dataType+".bad").c_str() );
#endif

#ifdef SMQI
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
//			resize(_image1, _image1, Size(0,0), 0.5, 0.5);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			cvNica::Denoise(_image1,_deno1);
//			Mat l, s, _l, _s;
//			Mat l2, s2, _l2, _s2;
//			Mat l3, s3, _l3, _s3;
//			Mat mdmqi3,mdmqi5,mdmqi7;
//			Mat mdmqi9,mdmqi11,mdmqi13;
//
//			int dilation_type = MORPH_RECT;
//			Mat elementL = getStructuringElement( dilation_type, Size( 9,9 ), Point( 4,4 ) );
//			//Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
//			Mat elementS = getStructuringElement( dilation_type, Size( 5,5), Point( 2,2 ) );
//			//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//			Mat elementL2 = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
//			//Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
//			Mat elementS2 = getStructuringElement( dilation_type, Size( 3,3), Point( 1,1 ) );
//			//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//			Mat elementL3 = getStructuringElement( dilation_type, Size( 13,13 ), Point( 6,6 ) );
//			//Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
//			Mat elementS3 = getStructuringElement( dilation_type, Size( 11,11), Point( 5,5 ) );
//			//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//
//			dilate( _deno1, l, elementL);
//			dilate( _deno1, s, elementS);
//			erode( l, _l, elementL);
//			erode( s, _s, elementS);
//
//			dilate( _deno1, l2, elementL2);
//			dilate( _deno1, s2, elementS2);
//			erode( l2, _l2, elementL2);
//			erode( s2, _s2, elementS2);
//
//			dilate( _deno1, l3, elementL3);
//			dilate( _deno1, s3, elementS3);
//			erode( l3, _l3, elementL3);
//			erode( s3, _s3, elementS3);
//
//			cvNica::Reflectance(_deno1,_l,mdmqi9);
//			cvNica::Reflectance(_deno1,_s,mdmqi5);
//			cvNica::Reflectance(_deno1,_l2,mdmqi7);
//			cvNica::Reflectance(_deno1,_s2,mdmqi3);
//			cvNica::Reflectance(_deno1,_l3,mdmqi13);
//			cvNica::Reflectance(_deno1,_s3,mdmqi11);
//
//
//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//
//			imwrite(tokens[0]+"_mdc9.bmp",_l);
//			imwrite(tokens[0]+"_mdc5.bmp",_s);
//			imwrite(tokens[0]+"_mdc7.bmp",_l2);
//			imwrite(tokens[0]+"_mdc3.bmp",_s2);
//			imwrite(tokens[0]+"_mdc13.bmp",_l3);
//			imwrite(tokens[0]+"_mdc11.bmp",_s3);
//
//			imwrite(tokens[0]+"_mdmqi9.bmp",mdmqi9);
//			imwrite(tokens[0]+"_mdmqi7.bmp",mdmqi7);
//			imwrite(tokens[0]+"_mdmqi5.bmp",mdmqi5);
//			imwrite(tokens[0]+"_mdmqi3.bmp",mdmqi3);
//			imwrite(tokens[0]+"_mdmqi11.bmp",mdmqi11);
//			imwrite(tokens[0]+"_mdmqi13.bmp",mdmqi13);
//
//			equalizeHist(mdmqi9,mdmqi9);
//			equalizeHist(mdmqi5,mdmqi5);
//			equalizeHist(mdmqi7,mdmqi7);
//			equalizeHist(mdmqi3,mdmqi3);
//			equalizeHist(mdmqi13,mdmqi13);
//			equalizeHist(mdmqi11,mdmqi11);
//
//			imwrite(tokens[0]+"_mdmqi9_histEq.bmp",mdmqi9);
//			imwrite(tokens[0]+"_mdmqi7_histEq.bmp",mdmqi7);
//			imwrite(tokens[0]+"_mdmqi5_histEq.bmp",mdmqi5);
//			imwrite(tokens[0]+"_mdmqi3_histEq.bmp",mdmqi3);
//			imwrite(tokens[0]+"_mdmqi11_histEq.bmp",mdmqi11);
//			imwrite(tokens[0]+"_mdmqi13_histEq.bmp",mdmqi13);
//			exit(0);

			//Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			//nicatio::MedianFilter(_image1.data,_deno1.data,_image1.cols,_image1.rows);
			//nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			//cvNica::Denoise(_image1,_deno1);

			cvNica::Denoise(_image1,_deno1);
			//_deno1=_image1;
			//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);

			//cvNica::SelectiveMorphQuotImage(_deno1,_deno2,0);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//							namedWindow( "a", CV_WINDOW_AUTOSIZE );
//							imshow( "a",  _dmqi );
//							waitKey(0);
			//_dmqi=_deno1;
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			//_dmqi = 255-_dmqi;

			equalizeHist(_dmqi,_histeq);



			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);





			//nicatio::MedianFilter(_histeq.data,_deno2.data,_image1.cols,_image1.rows);
			//nicatio::Gamma(_dmqi.data,_deno2.data,_image1.cols,_image1.rows,2.0);
			//nicatio::Gamma(_histeq.data,_deno2.data,_image1.cols,_image1.rows,25.0);
			//_histeq = 255-_histeq;
			//equalizeHist(_dmqi,_histeq);
//			double mmin, mmax;
//			minMaxIdx(_histeq,&mmin,&mmax);
//			_deno2 = _histeq - mmin;
//			_deno2 *= 255.0/(mmax-mmin);
			//Mat _deno3;
			//GaussianBlur(_histeq, _deno2, Size(3,3), 1.0, 1.0, BORDER_DEFAULT);


			//_deno2;// = _deno3(Rect(1,1,_deno1.size().width,_deno1.size().height));
			//_deno2=_dmqi;

			//_deno2=_histeq;

			//cvNica::IntensityShifting(_histeq, _deno2, 220);
//			imwrite("ori.bmp",_image1);
//			imwrite("dmqi.bmp",_dmqi);
//			imwrite("histeq.bmp",_deno2);

			//cvNica::IntensityShifting(_histeq, _deno2, 128);



			//Rect myROI(2, 2, 126, 146);
			//Mat croppedImage;
			//Mat(_histeq, myROI).copyTo(_deno2);
			//imwrite(buffer5.str(),croppedImage);


//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi/"+tokens[0]+"."+dataType+".bad").c_str() );

			unsigned found = files[i].rfind("bad");
						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
						imwrite(dir+"/mdmqimovhe/"+tokens[0]+"."+dataType,_histeq);
						if (found!=std::string::npos)
							rename( string(dir+"/mdmqimovhe/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqimovhe/"+tokens[0]+"."+dataType+".bad").c_str() );

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/deno/"+tokens[0]+"."+dataType,_deno2);
//			if (found!=std::string::npos)
//				rename( string(dir+"/deno/"+tokens[0]+"."+dataType).c_str() , string(dir+"/deno/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif

#ifdef SMQI_onlyClose
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);

			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);

			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			//cvNica::SelectiveClosing(_deno1,_dmqi,0,0);
			cvNica::DynamicClosing(_deno1,_dmqi,1.35,1.35);
			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/mdmqiclosing/"+tokens[0]+"."+dataType,_dmqi);
			if (found!=std::string::npos)
				rename( string(dir+"/mdmqiclosing/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqiclosing/"+tokens[0]+"."+dataType+".bad").c_str() );

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/deno/"+tokens[0]+"."+dataType,_deno2);
//			if (found!=std::string::npos)
//				rename( string(dir+"/deno/"+tokens[0]+"."+dataType).c_str() , string(dir+"/deno/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif
#ifdef SMQI_noise
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
//			resize(_image1, _image1, Size(0,0), 0.5, 0.5);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);

			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			equalizeHist(_dmqi,_histeq);



			for (int jjj=-5;jjj<=0;jjj+=1){
				Mat _d;Mat _d2;

				_histeq.convertTo(_d,CV_32FC1);
				multiply(_d,_d,_d2);
				double sum1 = sum(_d)[0]/size.width/size.height;
				double sum2 = sum(_d2)[0]/size.width/size.height;
				sum2 = sum2 - sum1*sum1;
				double n_std=sqrt(sum2/pow(10,(jjj/20.)));

//				cout<<n_std<<endl;
				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
				randn(_noisedImage, 0, n_std);
				_d = _d+_noisedImage;
				Mat _d3;
				_d.convertTo(_d3,CV_8UC1);
				stringstream a;
				a<<jjj;
				unsigned found = files[i].rfind("bad");
							vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
							imwrite(dir+"/smqi"+a.str()+"/"+string()+tokens[0]+"."+dataType,_d3);
							if (found!=std::string::npos)
								rename( string(dir+"/smqi"+a.str()+"/"+tokens[0]+"."+dataType).c_str() , string(dir+"/smqi"+a.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );
			}





#endif

#ifdef SMQI_noise2
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
//			resize(_image1, _image1, Size(0,0), 0.5, 0.5);
			Size size = _image1.size();
			Mat _d;Mat _d2;
			_image1.convertTo(_d,CV_32FC1);
			multiply(_d,_d,_d2);
			double sum1 = sum(_d)[0]/size.width/size.height;
			double sum2 = sum(_d2)[0]/size.width/size.height;
			sum2 = sum2 - sum1*sum1;

			for (int jjj=50;jjj<=50;jjj+=1){
				Mat _deno1(size,CV_8UC1);

				Mat _dmqi(size,CV_8UC1);
				Mat _histeq(size,CV_8UC1);




				double n_std=sqrt(sum2/pow(10,(jjj/20.)));

//				cout<<n_std<<endl;
				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
				randn(_noisedImage, 0, n_std);
				_d2 = _d+_noisedImage;
				Mat _d3;
				_d2.convertTo(_d3,CV_8UC1);

				cvNica::Denoise(_d3,_deno1);
				cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
				equalizeHist(_dmqi,_histeq);


				stringstream a;
				a<<jjj;
				unsigned found = files[i].rfind("bad");
							vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
							imwrite(dir+"/smqif"+a.str()+"/"+string()+tokens[0]+"."+dataType,_histeq);
							if (found!=std::string::npos)
								rename( string(dir+"/smqif"+a.str()+"/"+tokens[0]+"."+dataType).c_str() , string(dir+"/smqif"+a.str()+"/"+tokens[0]+"."+dataType+".bad").c_str() );
			}





#endif





#ifdef MDMQI_stretch
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			normalize(_dmqi,_histeq, 0, 255, CV_MINMAX);
			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);

			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/mdmqi_stretch/"+tokens[0]+"."+dataType,_histeq);
			if (found!=std::string::npos)
				rename( string(dir+"/mdmqi_stretch/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_stretch/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif

#ifdef MDMQI_lhe
//			//cout << files[i] <<"\r"<< endl;
//			Mat _image1;
//			_image1 = imread( dir+"\\"+files[i], -1 );
//			//_image0.convertTo(_image1,CV_8UC1);
//			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//
//			cvNica::Denoise(_image1,_deno1);
//			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//			//normalize(_dmqi,_histeq, 0, 255, CV_MINMAX);
//			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
//			nicatio::localHistogramEqualization(_dmqi.data,_histeq.data,_image1.cols,_image1.rows,81);
//
//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi_lhe81/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi_lhe81/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_lhe81/"+tokens[0]+"."+dataType+".bad").c_str() );

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			//if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			//normalize(_dmqi,_histeq, 0, 255, CV_MINMAX);
			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			nicatio::localHistogramEqualization(_dmqi.data,_histeq.data,_image1.cols,_image1.rows,9);
//
			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/lhe9/"+tokens[0]+"."+dataType,_histeq);
			if (found!=std::string::npos)
				rename( string(dir+"/lhe9/"+tokens[0]+"."+dataType).c_str() , string(dir+"/lhe9/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif

#ifdef MDMQI_lhe_he
//			//cout << files[i] <<"\r"<< endl;
//			Mat _image1;
//			_image1 = imread( dir+"\\"+files[i], -1 );
//			//_image0.convertTo(_image1,CV_8UC1);
//			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//
//			cvNica::Denoise(_image1,_deno1);
//			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//			//normalize(_dmqi,_histeq, 0, 255, CV_MINMAX);
//			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
//			nicatio::localHistogramEqualization(_dmqi.data,_histeq.data,_image1.cols,_image1.rows,81);
//
//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi_lhe81/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi_lhe81/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_lhe81/"+tokens[0]+"."+dataType+".bad").c_str() );

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			//normalize(_dmqi,_histeq, 0, 255, CV_MINMAX);
			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			nicatio::localHistogramEqualization(_dmqi.data,_deno2.data,_image1.cols,_image1.rows,91);

			nicatio::HistEqualize(_deno2.data,_histeq.data,_image1.cols,_image1.rows);

			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/mdmqi_lhe_he91/"+tokens[0]+"."+dataType,_histeq);
			if (found!=std::string::npos)
				rename( string(dir+"/mdmqi_lhe_he91/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_lhe_he91/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif


#ifdef MDMQI_clahe
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			//if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			//normalize(_dmqi,_histeq, 0, 255, CV_MINMAX);
			//nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			//nicatio::localHistogramEqualization(_dmqi.data,_histeq.data,_image1.cols,_image1.rows,81);
			nicatio::CLAHE (_dmqi.data, _image1.cols, _image1.rows, 0, 255, 8, 8, 256, 16);

//			Ptr<CLAHE> clahe;// = createCLAHE();
//			clahe->setClipLimit(4);
//
//			Mat dst;
//			clahe->apply(m,dst);
//			imshow("lena_CLAHE",dst);

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi_clahe2/"+tokens[0]+"."+dataType,_dmqi);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi_clahe2/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_clahe2/"+tokens[0]+"."+dataType+".bad").c_str() );

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi_clahe/"+tokens[0]+"."+dataType,_dmqi);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi_clahe/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_clahe/"+tokens[0]+"."+dataType+".bad").c_str() );

			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/clahe/"+tokens[0]+"."+dataType,_dmqi);
			if (found!=std::string::npos)
				rename( string(dir+"/clahe/"+tokens[0]+"."+dataType).c_str() , string(dir+"/clahe/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif





#ifdef closing
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			int dilation_type = MORPH_RECT;
			Mat elementL = getStructuringElement( dilation_type, Size( 9,9 ), Point( 4,4 ) );
			//Mat elementM = getStructuringElement( dilation_type, Size( 7,7 ), Point( 3,3 ) );
			Mat elementS = getStructuringElement( dilation_type, Size( 5,5), Point( 2,2 ) );
			//Mat elementSS = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );

			dilate( _image1, _deno1, elementL);
			//dilate( src, m, elementM);
			//dilate( src, ss, elementSS);
			erode( _deno1, _dmqi, elementL);

//			Ptr<CLAHE> clahe;// = createCLAHE();
//			clahe->setClipLimit(4);
//
//			Mat dst;
//			clahe->apply(m,dst);
//			imshow("lena_CLAHE",dst);

			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/closing/"+tokens[0]+"."+dataType,_dmqi);
			if (found!=std::string::npos)
				rename( string(dir+"/closing/"+tokens[0]+"."+dataType).c_str() , string(dir+"/closing/"+tokens[0]+"."+dataType+".bad").c_str() );

			//unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/clahe/"+tokens[0]+"."+dataType,_image1);
//			if (found!=std::string::npos)
//				rename( string(dir+"/clahe/"+tokens[0]+"."+dataType).c_str() , string(dir+"/clahe/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif


#ifdef LBPadv

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			Size size2(size.width-4,size.height-4);
			Mat lbp;

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			Mat Image=_image1;
			for (int jjj=5;jjj<=50;jjj+=5){
				Mat _d;Mat _d2;

				_image1.convertTo(_d,CV_32FC1);
				multiply(_d,_d,_d2);
				double sum1 = sum(_d)[0]/size.width/size.height;
				double sum2 = sum(_d2)[0]/size.width/size.height;
				sum2 = sum2 - sum1*sum1;
				double n_std=sqrt(sum2/pow(10,(jjj/20.)));

				cout<<n_std<<endl;
				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
				randn(_noisedImage, 0, n_std);
				_d = _d+_noisedImage;
				Mat _d3;
				_d.convertTo(_d3,CV_8UC1);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a",  _d3 );
//				waitKey(0);


				cvNica::ELBP(_d3, lbp, 2, 8, 1);
				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);

	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//			imshow( "b", _image1 );
	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
	//			imshow( "a", lbp );
	//			waitKey(0);
				stringstream a;
				a<<jjj;
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"/lbp_p1/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
//				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
			}
			for (int jjj=5;jjj<=50;jjj+=5){
				Mat _d;Mat _d2;

				_image1.convertTo(_d,CV_32FC1);
				multiply(_d,_d,_d2);
				double sum1 = sum(_d)[0]/size.width/size.height;
				double sum2 = sum(_d2)[0]/size.width/size.height;
				sum2 = sum2 - sum1*sum1;
				double n_std=sqrt(sum2/pow(10,(jjj/20.)));

				cout<<n_std<<endl;
				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
				randn(_noisedImage, 0, n_std);
				_d = _d+_noisedImage;
				Mat _d3;
				_d.convertTo(_d3,CV_8UC1);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a",  _d3 );
//				waitKey(0);


				cvNica::ELBP(_d3, lbp, 2, 8, -1);
				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);

	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//			imshow( "b", _image1 );
	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
	//			imshow( "a", lbp );
	//			waitKey(0);
				stringstream a;
				a<<jjj;
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"/lbp_n1/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
//				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
			}
			for (int jjj=5;jjj<=50;jjj+=5){
				Mat _d;Mat _d2;

				_image1.convertTo(_d,CV_32FC1);
				multiply(_d,_d,_d2);
				double sum1 = sum(_d)[0]/size.width/size.height;
				double sum2 = sum(_d2)[0]/size.width/size.height;
				sum2 = sum2 - sum1*sum1;
				double n_std=sqrt(sum2/pow(10,(jjj/20.)));

				cout<<n_std<<endl;
				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
				randn(_noisedImage, 0, n_std);
				_d = _d+_noisedImage;
				Mat _d3;
				_d.convertTo(_d3,CV_8UC1);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a",  _d3 );
//				waitKey(0);


				cvNica::ELBP(_d3, lbp, 2, 8, 3);
				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);

	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//			imshow( "b", _image1 );
	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
	//			imshow( "a", lbp );
	//			waitKey(0);
				stringstream a;
				a<<jjj;
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"/lbp_p3/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
//				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
			}
			for (int jjj=5;jjj<=50;jjj+=5){
				Mat _d;Mat _d2;

				_image1.convertTo(_d,CV_32FC1);
				multiply(_d,_d,_d2);
				double sum1 = sum(_d)[0]/size.width/size.height;
				double sum2 = sum(_d2)[0]/size.width/size.height;
				sum2 = sum2 - sum1*sum1;
				double n_std=sqrt(sum2/pow(10,(jjj/20.)));

				cout<<n_std<<endl;
				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
				randn(_noisedImage, 0, n_std);
				_d = _d+_noisedImage;
				Mat _d3;
				_d.convertTo(_d3,CV_8UC1);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a",  _d3 );
//				waitKey(0);


				cvNica::ELBP(_d3, lbp, 2, 8, -3);
				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);

	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
	//			imshow( "b", _image1 );
	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
	//			imshow( "a", lbp );
	//			waitKey(0);
				stringstream a;
				a<<jjj;
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"/lbp_n3/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
//				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
			}

//			for (int jjj=5;jjj<=50;jjj+=5){
//				Mat _d;Mat _d2;
//
//				_image1.convertTo(_d,CV_32FC1);
//				multiply(_d,_d,_d2);
//				double sum1 = sum(_d)[0]/size.width/size.height;
//				double sum2 = sum(_d2)[0]/size.width/size.height;
//				sum2 = sum2 - sum1*sum1;
//				double n_std=sqrt(sum2/pow(10,(jjj/20.)));
//
//				cout<<n_std<<endl;
//				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
//				randn(_noisedImage, 0, n_std);
//				_d = _d+_noisedImage;
//				Mat _d3;
//				_d.convertTo(_d3,CV_8UC1);
////				namedWindow( "a", CV_WINDOW_AUTOSIZE );
////				imshow( "a",  _d3 );
////				waitKey(0);
//
//
//				cvNica::ELBP(_d3, lbp, 2, 8, 5);
//				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);
//
//	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
//	//			imshow( "b", _image1 );
//	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	//			imshow( "a", lbp );
//	//			waitKey(0);
//				stringstream a;
//				a<<jjj;
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
////				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
//			}
//			for (int jjj=5;jjj<=50;jjj+=5){
//				Mat _d;Mat _d2;
//
//				_image1.convertTo(_d,CV_32FC1);
//				multiply(_d,_d,_d2);
//				double sum1 = sum(_d)[0]/size.width/size.height;
//				double sum2 = sum(_d2)[0]/size.width/size.height;
//				sum2 = sum2 - sum1*sum1;
//				double n_std=sqrt(sum2/pow(10,(jjj/20.)));
//
//				cout<<n_std<<endl;
//				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
//				randn(_noisedImage, 0, n_std);
//				_d = _d+_noisedImage;
//				Mat _d3;
//				_d.convertTo(_d3,CV_8UC1);
////				namedWindow( "a", CV_WINDOW_AUTOSIZE );
////				imshow( "a",  _d3 );
////				waitKey(0);
//
//
//				cvNica::ELBP(_d3, lbp, 2, 8, -5);
//				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);
//
//	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
//	//			imshow( "b", _image1 );
//	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	//			imshow( "a", lbp );
//	//			waitKey(0);
//				stringstream a;
//				a<<jjj;
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"/lbp_n5/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
////				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
//			}
//			for (int jjj=5;jjj<=50;jjj+=5){
//				Mat _d;Mat _d2;
//
//				_image1.convertTo(_d,CV_32FC1);
//				multiply(_d,_d,_d2);
//				double sum1 = sum(_d)[0]/size.width/size.height;
//				double sum2 = sum(_d2)[0]/size.width/size.height;
//				sum2 = sum2 - sum1*sum1;
//				double n_std=sqrt(sum2/pow(10,(jjj/20.)));
//
//				cout<<n_std<<endl;
//				Mat _noisedImage = Mat::zeros(size,CV_32FC1);
//				randn(_noisedImage, 0, n_std);
//				_d = _d+_noisedImage;
//				Mat _d3;
//				_d.convertTo(_d3,CV_8UC1);
////				namedWindow( "a", CV_WINDOW_AUTOSIZE );
////				imshow( "a",  _d3 );
////				waitKey(0);
//
//
//				cvNica::ELBP(_d3, lbp, 2, 8, 0);
//				normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);
//
//	//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
//	//			imshow( "b", _image1 );
//	//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	//			imshow( "a", lbp );
//	//			waitKey(0);
//				stringstream a;
//				a<<jjj;
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"/lbp/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);
////				cout<<dir+"/lbp_p5/"+a.str()+"/"+tokens[0]+"."+dataType<<endl;
//			}

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/lbp/"+tokens[0]+"."+dataType,lbp);
//			if (found!=std::string::npos)
//				rename( string(dir+"/lbp/"+tokens[0]+"."+dataType).c_str() , string(dir+"/lbp/"+tokens[0]+"."+dataType+".bad").c_str() );



#endif



#ifdef LBPadv2

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			//equalizeHist(_image1,_image1);
			Mat lbp10;
			cvNica::ELBP(_image1, lbp10, 2, 8, 0);
			normalize(lbp10, lbp10, 0, 255, NORM_MINMAX, CV_8UC1);
			imwrite(dir+"/lbp/"+tokens[0]+"."+dataType,lbp10);

//			Mat lbp11;
//			cvNica::ELBP(_image1, lbp11, 2, 8, 2);
//			imwrite(dir+"/lbp_p2/"+tokens[0]+"."+dataType,lbp11);
//
//			Mat lbp12;
//			cvNica::ELBP(_image1, lbp12, 2, 8, 4);
//			imwrite(dir+"/lbp_p4/"+tokens[0]+"."+dataType,lbp12);
//
//			Mat lbp14;
//			cvNica::ELBP(_image1, lbp14, 2, 8, -2);
//			imwrite(dir+"/lbp_n2/"+tokens[0]+"."+dataType,lbp14);
//
//			Mat lbp15;
//			cvNica::ELBP(_image1, lbp15, 2, 8, -4);
//			imwrite(dir+"/lbp_n4/"+tokens[0]+"."+dataType,lbp15);
//
//
//			Mat lbp1;
//			cvNica::ELBP(_image1, lbp1, 2, 8, 1);
//			imwrite(dir+"/lbp_p1/"+tokens[0]+"."+dataType,lbp1);
//
//			Mat lbp2;
//			cvNica::ELBP(_image1, lbp2, 2, 8, 3);
//			imwrite(dir+"/lbp_p3/"+tokens[0]+"."+dataType,lbp2);
//
//			Mat lbp3;
//			cvNica::ELBP(_image1, lbp3, 2, 8, 5);
//			imwrite(dir+"/lbp_p5/"+tokens[0]+"."+dataType,lbp3);
//
//			Mat lbp4;
//			cvNica::ELBP(_image1, lbp4, 2, 8, -1);
//			imwrite(dir+"/lbp_n1/"+tokens[0]+"."+dataType,lbp4);
//
//			Mat lbp5;
//			cvNica::ELBP(_image1, lbp5, 2, 8, -3);
//			imwrite(dir+"/lbp_n3/"+tokens[0]+"."+dataType,lbp5);
//
//			Mat lbp6;
//			cvNica::ELBP(_image1, lbp6, 2, 8, -5);
//			imwrite(dir+"/lbp_n5/"+tokens[0]+"."+dataType,lbp6);



#endif


#ifdef LBPnoise

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat lbp;
//			cvNica::ELBP(_image1, lbp, 2, 8, 0);
//			imwrite(dir+"/noised/"+tokens[0]+"."+dataType,lbp);
//


			Mat _d;Mat _d2;
			double jjj = 10;
			_image1.convertTo(_d,CV_32FC1);
			multiply(_d,_d,_d2);
			double sum1 = sum(_d)[0]/size.width/size.height;
			double sum2 = sum(_d2)[0]/size.width/size.height;
			sum2 = sum2 - sum1*sum1;
			double n_std=sqrt(sum2/pow(10,(jjj/20.)));

			cout<<n_std<<endl;
			Mat _noisedImage = Mat::zeros(size,CV_32FC1);
			randn(_noisedImage, 0, n_std);
			_d = _d+_noisedImage;
			Mat _d3;
			_d.convertTo(_d3,CV_8UC1);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a",  _d3 );
//				waitKey(0);
			stringstream a;
			a<<jjj;
			imwrite(dir+"/noised/"+a.str()+"/"+tokens[0]+"."+dataType,_d3);

			cvNica::ELBP(_d3, lbp, 2, 8, 0);
			normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);

//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
//			imshow( "b", _image1 );
//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a", lbp );
//			waitKey(0);

//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/noised/lbp/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);





#endif


#ifdef LBPblur

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat lbp;

			double jjj = 7;

			Mat _d,_d3;
			GaussianBlur(_image1,_d,Size(jjj,jjj),1);
			_d.convertTo(_d3,CV_8UC1);
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a",  _d3 );
//				waitKey(0);
			stringstream a;
			a<<jjj;
			imwrite(dir+"/blurred/"+a.str()+"/"+tokens[0]+"."+dataType,_d3);

			cvNica::ELBP(_d3, lbp, 2, 8, 0);
			normalize(lbp, lbp, 0, 255, NORM_MINMAX, CV_8UC1);

//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
//			imshow( "b", _image1 );
//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a", lbp );
//			waitKey(0);

//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/blurred/lbp/"+a.str()+"/"+tokens[0]+"."+dataType,lbp);





#endif




#ifdef MDMQI_LBP

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			Mat lbp(size,CV_8UC1);

			cvNica::Denoise(_image1,_deno1);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			Mat Image=_image1;
			int center = 0;
						  int center_lbp = 0;

						  for (int row = 1; row < Image.rows; row++)
						  {
						    for (int col = 1; col < Image.cols; col++)
						    {
						      center = Image.at<uchar>(row, col);
						      center_lbp = 0;

						      if ( center <= Image.at<uchar>(row-1, col-1) )
						    center_lbp += 1;

						      if ( center <= Image.at<uchar>(row-1, col)   )
						        center_lbp += 2;

						      if ( center <= Image.at<uchar>(row-1, col+1) )
						        center_lbp += 4;

						      if ( center <= Image.at<uchar>(row, col-1)   )
						        center_lbp += 8;

						      if ( center <= Image.at<uchar>(row, col+1)   )
						        center_lbp += 16;

						      if ( center <= Image.at<uchar>(row+1, col-1) )
						        center_lbp += 32;

						      if ( center <= Image.at<uchar>(row+1, col)   )
						        center_lbp += 64;

						      if ( center <= Image.at<uchar>(row+1, col+1) )
						        center_lbp += 128;

						     // cout << "center lbp value: " << center_lbp << endl;
						      lbp.at<uchar>(row, col) = center_lbp;
						    }
						  }

						    //imshow("lbp_image", lbp);

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi_lbp/"+tokens[0]+"."+dataType,lbp);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi_lbp/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_lbp/"+tokens[0]+"."+dataType+".bad").c_str() );

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/lbp/"+tokens[0]+"."+dataType,lbp);
//			if (found!=std::string::npos)
//				rename( string(dir+"/lbp/"+tokens[0]+"."+dataType).c_str() , string(dir+"/lbp/"+tokens[0]+"."+dataType+".bad").c_str() );
//


#endif


#ifdef LBPAvg

			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			//_image0.convertTo(_image1,CV_8UC1);
			if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);

			Mat lbp(size,CV_8UC1);

		//	cvNica::Denoise(_image1,_deno1);

			Mat Image=_image1;
			Mat avg;
			int kernel_size = 3;
			Mat kernel = Mat::ones( kernel_size, kernel_size, CV_32F )/ (float)(kernel_size*kernel_size);
			filter2D(Image, avg, -1 , kernel, Point( -1, -1 ), 0, BORDER_DEFAULT );



			int center = 0;
						  int center_lbp = 0;

						  for (int row = 1; row < Image.rows; row++)
						  {
						    for (int col = 1; col < Image.cols; col++)
						    {
						      center = avg.at<uchar>(row, col);
						      center_lbp = 0;

						      if ( center < Image.at<uchar>(row-1, col-1) )
						    center_lbp += 1;

						      if ( center < Image.at<uchar>(row-1, col)   )
						        center_lbp += 2;

						      if ( center < Image.at<uchar>(row-1, col+1) )
						        center_lbp += 4;

						      if ( center < Image.at<uchar>(row, col-1)   )
						        center_lbp += 8;

						      if ( center < Image.at<uchar>(row, col+1)   )
						        center_lbp += 16;

						      if ( center < Image.at<uchar>(row+1, col-1) )
						        center_lbp += 32;

						      if ( center < Image.at<uchar>(row+1, col)   )
						        center_lbp += 64;

						      if ( center < Image.at<uchar>(row+1, col+1) )
						        center_lbp += 128;

						     // cout << "center lbp value: " << center_lbp << endl;
						      lbp.at<uchar>(row, col) = center_lbp;
						    }
						  }

						    //imshow("lbp_image", lbp);

//			unsigned found = files[i].rfind("bad");
//			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//			imwrite(dir+"/mdmqi_lbp/"+tokens[0]+"."+dataType,lbp);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi_lbp/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi_lbp/"+tokens[0]+"."+dataType+".bad").c_str() );

			unsigned found = files[i].rfind("bad");
			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
			imwrite(dir+"/lbpavg/"+tokens[0]+"."+dataType,lbp);
			if (found!=std::string::npos)
				rename( string(dir+"/lbpavg/"+tokens[0]+"."+dataType).c_str() , string(dir+"/lbpavg/"+tokens[0]+"."+dataType+".bad").c_str() );



#endif


#ifdef DMQIADVANCED
			cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
			Size size = _image1.size();
			Mat _deno1(size,CV_8UC1);
			Mat _deno2(size,CV_8UC1);
			Mat _dmqi(size,CV_8UC1);
			Mat _histeq(size,CV_8UC1);
			nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			cvNica::NormDynamicMorphQuotImage(_deno1,_dmqi,0);
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			nicatio::HistEqualize2(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
			_deno2=_histeq;
			//cvNica::IntensityShifting(_histeq, _deno2, 128);
//			unsigned found = files[i].rfind("bad");
//			if (found!=std::string::npos) {
//				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
//				imwrite(dir+"\\dmqiadv\\"+tokens[0]+".pgm",_deno2);
//				rename( string(dir+"\\dmqiadv\\"+tokens[0]+".pgm").c_str() , string(dir+"\\dmqiadv\\"+tokens[0]+".pgm.bad").c_str() );
//
//			} else {
//
//				imwrite(dir+"\\dmqiadv\\"+files[i],_deno2);
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


#ifdef Detect_traffic_sign
//			double weight[121] = {0.00735751157409825, -0.00735901208247242, -0.0128291412565126, -0.00731674327615839, -0.0114661413559382, -0.00584752936614508, 0.0260574384436117, 0.0223136064103442, 0.0249882577066348, 0.00936472576449166, -0.00273469385708186, -0.0271723100719608, 0.0165644906225203, 0.0808591613588888, -0.00875271816113143, -0.0212305340185850, 0.0278129404133187, -0.00328201471719070, 0.000683528691820867, -0.0319689748617197, -0.00735778281653415, -0.00666183635520340, -0.0293698670774916, -0.0383528575613082, -0.00155691371363650, 0.000231130425140863, 0.00538051487294888, -0.00952134649003356, -0.0642547870687700, 0.0867381107419523, -0.0228588505182142, -0.0406006990494049, 0.0394960775822406, 0.0282047510782707, -0.00634767879462717, -0.0353700009990622, 0.0239135839345621, 0.0442884526592954, -0.0123141215665848, 0.0155571177711797, -0.0205339138996275, 0.00584593339495279, 0.0355842612549514, -0.00971970779875211, 7.97579439964502e-05, 0.0235356394724329, -0.00494930054770465, -0.0277259784790987, 0.0187093158685209, 0.00219440755734135, -0.0387285659558380, -0.0366089300394857, 0.0240774212299766, -0.00861895289316728, 0.00552174660750207, 0.00949469468827840, -0.00751720844478682, -0.0131024222719986, 0.0222676057049996, -0.00774534466889149, -0.0301876245812615, -0.0268418361928682, 0.00260046842537431, -0.0252894234445767, -0.0357898280328915, 0.0382515805632530, 0.00632807066444030, -0.0251742641196604, -0.0217271289853943, 0.000768322339312844, 0.0322159536944759, 0.0312052233410532, -0.0504865539218670, 0.0433694155955251, 0.000448552458949481, -0.0188290965101547, -0.00556884332346846, 0.0531241443312067, -0.0397161170989969, 0.0756221984497755, -0.00666534954245318, -0.0329120172681691, -0.00698651166963832, -0.00192070581933412, 0.0630814750368205, 0.0102859955103258, -0.0116739237481556, -0.0205709651548682, -0.0331523459383964, 2.18142068318106e-05, 0.00679947225926192, 0.00353783363286486, -0.0514968256521564, 0.0131934194402792, 0.00761445003395866, 0.0114666841378781, -0.0237125387000972, 0.0105620624727123, 0.0206862683824112, 0.0266808665244678, 0.0255021390631280, -0.0162080499261977, -0.00376988586856836, -0.00206017977036749, -0.00273938761711892, 0.00711211097332820, -0.0252670241746884, -0.00895749433937797, -0.0370585362179669, 0.0274555168723313, 0.0290978439698221, -0.0180600015585780, -0.0467391413972646, 0.00201602862445537, 0.0330018471015669, -0.0269641665347565, -0.00258577682324389, 0.0293709898717699, 0.0223384004632845, -0.0113292721547947, 0.00873341660983064};
//			double cst = 3.02671939041329;
//			double weight[363] = {-0.0399828794971048, 0.0166401968522330, 0.0197119684979878, 0.0188839211916769, 0.0188244106259169, -0.00265554446407121, -0.0192548031725156, 0.0303416368425317, 0.00372250198628797, 0.00513742725928020, 0.0292535212738607, -0.0141615789635291, -0.00260794687694116, -0.00523882892250500, 0.00378222187000551, 0.00144177465215715, -0.0495228059890997, -0.00873858399677003, -0.00445324748384830, -0.0114937537907939, 0.00390077475289100, 0.00592512965469846, 0.000417480534951972, 0.00555699988534152, 0.00215057776110468, -0.00400645587527212, -0.00590734615957104, -0.0187895964344540, -0.00324496065136075, -0.0121312866288485, 0.00314311438977351, -0.0173542084231047, 0.0205422558128105, 0.00893411440902714, -0.000428406319662506, 0.00927140347040623, 0.0123278898466586, -0.0169104391829074, -0.0136414615687445, -0.0217700022156884, 0.0223460202426960, 0.00165892284333628, -0.0138889991279724, -0.0159342575567721, -0.0103226016943042, -0.0152550074586583, 0.00327605916650421, -0.0107670517236377, 0.00325989371458895, -0.00325684875033302, -0.00118211550534741, 0.0208995970450593, 0.0128196788475701, -0.0266354380234798, -0.0331693453295537, -0.00496488821936450, -0.00661980434554363, 0.00358108368419293, 0.0379454955927636, 0.0212463512409212, 0.00634148926778835, -0.000196355041868755, 0.0135941596839187, 0.00595214853078177, 0.0109766327316494, -0.0501352488546703, 0.0236134806889552, 0.00975103553733639, 0.0121077099664232, 0.00969570077594374, 0.0239180634583154, 0.0232152328261519, 0.0402207861993412, 0.00553027709905227, -0.0125436239353963, 0.0100248614466422, 0.0100587457871634, 0.0126902262882041, 0.00678125769030674, -0.00837952980210088, 0.00786366708537972, 0.00230486875313860, 0.000190462889567004, 0.00442406069091990, -0.00474264254496135, 0.0359509297150218, -0.0153722770569229, -0.00512677295542487, 0.000809801826761380, -0.0239401265873736, -0.0152634152673741, -0.0119349671933782, -0.0124841995174574, 0.00498357884586396, -0.0239085664064642, -0.00593992244677808, -0.00353776402421655, -0.00127114153418962, 0.0170238150259980, 0.00987332790608817, -0.0131549418119001, -0.0262654346256555, -0.00295878087669139, -0.0343497019889722, -0.000637568820575534, -0.00863954244022441, -0.00312791359967973, -0.00216757055503932, 0.0182107624416646, -0.0251921894473624, -0.00253488193648488, -0.0239343599783833, 0.0188477940572484, 0.00523325409178165, 0.00880401928051950, -0.00851214614835585, 0.0500629873641195, 0.00192344481202514, 0.0142310135615458, 0.00643484063542915, -0.0220961771671351, 0.0688727792031413, 0.00183224306671508, -0.0340920133085970, 0.000203738876813391, 0.0140515801445915, 0.0402684473436386, -0.0378966048844010, -0.0385021868718708, 0.00454849154269174, -0.0137069183316442, 0.00699258312654677, 0.0300313867921538, -0.0169860667486115, -0.0431741502658170, -0.00795166988949005, 0.00525638084770961, 0.00573858436087385, -0.00395699383811211, -0.0413245290204765, 0.00182616586112018, 0.0212320822571157, -0.0204525405866154, 0.00705367010685315, -0.00143758071096765, -0.0195628746360056, -0.00240828527827617, -0.00482757228370238, 0.0143912453815090, 0.00835826599190607, -0.0219938776012295, 0.00471563826269519, -0.00313977546511108, 0.0304537337986738, -0.00324103169962295, -0.00450286777630021, -0.0105821564100625, 0.00295798571430311, 0.0119371395692285, 0.0264583979015154, -0.00532158018852425, 0.0238042910877292, -0.00433711597399192, 0.0128235042328815, 0.0252197286236440, 0.0370556735273928, 0.000821758218241731, 0.0260783491415398, 0.00686159792097260, 0.0196984743340433, 0.0241779248510222, -0.00826094435159345, -0.0160068476793667, -0.00575889071101884, 0.0277778228223835, 0.0172317978174200, 0.00700335510477619, -0.0106572400813243, 0.00167632134693999, -0.0200953115373573, -9.07718072590217e-05, 0.0112355398916929, -0.0180584460461105, -0.0213467370720543, -0.000771403976050740, 0.0317895260178408, -0.00791821053839401, -0.00671611293940414, -0.0174812717563510, -0.0114619568556267, -0.0523146250623463, -0.0422576050311420, -0.0237022037327004, 0.00537819925764517, 0.000503970012583695, -0.0485477091090046, -0.0293126681439039, -0.00844137979118701, -0.0120058975698853, -0.0129880943577427, -0.0232987929754970, -0.0147744348396803, -0.0152420790900305, -0.0305407105754791, 0.0280967621190465, -0.00310955049905981, 0.00228142322411929, -0.00338587869065258, 0.00714625728407580, -0.0108776487430896, 0.0139759213426620, 0.0175830844904096, 0.0116794648295864, 0.0139762801089063, -0.00487696258876733, -0.0167340826661726, -0.00608380552319530, -0.00413256856119263, 0.00309541496394478, -0.00128810892781998, -0.0118512076441374, 0.0200248936520494, 0.00608329423531077, 0.0165221635964782, 0.00785100059341281, 0.0113563850911689, -0.00961907584044908, -0.00224710815954782, 0.00239434471785765, 0.0182899648263610, 0.0193034995623586, 0.0414773931040490, -0.00382327776849229, -0.0198099943834207, 0.0222229476089920, 0.0111351923231969, -0.00574425043984581, -0.00410207890087048, -0.00622141972785907, -0.00318830042830070, 0.0191607610943671, 0.0314963809146943, -0.0286665328565138, -0.000199931031566192, 0.0116403139058861, -0.0390844007943661, -0.0129123756576157, 0.00738076049881833, -0.00782451713177062, 0.0136698067304252, 0.00681387503588185, -0.00401740756455082, -0.0151275989323880, -0.00496212340399406, 0.0102343158131507, 0.00269766534043378, 0.00666226990274515, 0.0125868040561628, 0.0113851041897754, 0.0473278074288356, 0.0276145378107992, 0.0116858968122300, 0.00490626399102668, -0.0260662165985461, -0.0174159146426111, 0.0344118354217380, 0.0264227566328694, 0.00177842435061280, 0.0158128631368383, -0.00180582916832172, 0.0331021857637434, -0.0138968954443367, 0.00582337005642985, -0.0264475144627506, 0.0113251626670217, -0.0352108161463265, 0.00127654962130838, 0.00471521261039593, -0.00984795664890512, -0.00459210117732120, -0.0158185508499248, -0.0131979457302183, 0.00524425909027381, -0.00617597124428436, -0.0217216823960136, -0.0122283596072573, -0.00588442574454925, -0.00248163125447688, 0.00416228104576673, -0.0179500467643071, -0.00188224818388673, -0.0136811633323664, 0.00184329136769069, 0.00686025359041844, 0.0251345489736965, 0.0151690102090166, -0.00473202113902707, -0.0139871576902615, 4.43709969548778e-05, 0.00132798733712808, 0.0123757139155469, -0.0196250201379554, -0.0242525643667047, -0.0410991975418429, -0.00209021551880352, 0.000645818687967983, 0.0451801831557839, -0.00477936823846474, 0.00155621799624223, 0.0111628236894016, 0.0249467584064754, -0.0141078199650344, -0.00199647503510606, 0.00342460834770061, -0.00257661085850160, 0.0151903905238219, -0.0165865263613348, 0.0187373222189070, 0.0169450893579153, -0.0103589502864672, 0.0232244049180580, 0.0273998440594074, 0.0139996191752092, 0.0103261654617438, 0.0203223855817236, 0.00701044013079414, -0.00950968869173926, 0.00788144285066281, -0.0193060216350423, 0.00261914321886145, -0.00904951484776728, 0.00843090591692652, 0.0241292618926324, -0.00674086040803671, 0.00946457077271085, 0.00281393456259061, 0.00744830042431957, 0.00851161904256995, -0.00558807308868933, -0.0218709994873736, 0.0100074243135546, -0.00110251499710887, 0.000357247105345001, 0.00875662251098820, -0.0169687666713385, -0.0119628267394489, 0.0275843629199217, -0.00290346115737587, 0.00410923302242540, 0.00392468695207362, 0.0134319509337570, -0.0180038215204293, 0.0195547022273594, -0.0132408532508533, -0.0243978501243743, -0.00987165548416000, -0.0127475355872915, -0.00990265568230717, 0.00560952853732319, -0.0328915786504233, 0.00169432606027679, 0.00241339049208127, -0.0335212297703334};
//			double cst = 1.60100146787689;
//			double weight[363] = {0.0135626352658442, 0.00103879756814466, 0.0105138205465934, -0.00892773061004162, -0.00165804864037300, -0.00197763645076068, 0.000248916153535256, 0.00999988563126275, 0.0151005546091846, 0.00856993906920275, 0.00565288563566296, -0.00759153217106579, -0.0175765453875925, 0.00268301915668875, 0.00419355914505501, 0.00150798504919350, 0.00950202363474098, -0.00190408028408914, -0.000156430752079384, -0.00465738921552325, -0.00579919912407662, 0.00347535604025900, -0.00823521625292620, -0.00954869790603474, -0.00640449347508199, -0.00443333829290235, -0.00606276123353011, 0.00750809854526582, -0.0118007695604624, 0.00221302886020824, 0.00113355743490992, -0.00265888902853145, 0.00381025012570799, -0.00442779160648230, 0.00623354797340994, -0.00604656851398949, 0.00353870704322509, 0.000935912359045638, 0.0100039973587860, -0.00449546327944250, 0.00641773892435055, -0.00156983703319638, -0.00206348987019270, -0.00438665561666751, 0.00950971731063924, 0.0168889706700215, 0.00485769180218051, -0.00240219683224616, -0.00178629877610881, -0.00130507238268976, -0.00773526661136834, -0.00768130324622432, 0.00464169104686626, -0.00188565227376233, 0.00458208676121080, 0.00562366591334773, 0.00275446749087446, 0.00433961838626365, 0.00654216329682211, -0.000951559162607057, -0.00831435822098559, -0.0112165817258236, 0.00535221095886015, -0.0152700750889926, -0.00382191913951976, 0.00174287000812066, -0.0115986496096239, -0.00547455395059826, -0.00292790016935361, -0.00491156730774163, -0.00744559533825138, -0.00573070501359084, -0.0127184326344743, 0.00526741296598726, -0.00686010939447132, -0.00328415790608735, -0.00992941995848748, 0.0104362501114174, -0.00505844512918509, 0.0106326330578007, 0.00460351450738898, 0.00657615005523383, 0.00977757447811338, 0.00837318435837968, 0.0227960333948548, -0.00953161512047132, -0.000541335715086189, -0.00510454751497549, -0.00269278798761208, -0.0106175724974189, 0.00697131930549595, -0.00451686987661630, -0.00782028965269975, 0.00277269993970290, 0.00905955524491871, 0.0108881066362742, -0.0100903317456818, 0.00192868814935473, 0.0101781520335722, -0.00220913439992029, 0.000879766377687496, 0.00507066902858605, 0.00706528923828348, -0.00693806350271435, -0.00559820093988643, 0.0128299706536226, 0.00121098340187585, -0.00970364801385597, -0.00143740995440937, 0.00590468287349814, -0.00876285914199755, 0.00186943302230148, -0.00459703608449917, -0.000504055090899944, -0.000306986498702283, -0.000672249468303396, 0.00350431072844619, 0.0108780947104772, -0.00755937172705092, -0.00411325260231811, 8.32215344622050e-05, -0.000268722452612891, -0.000894396804764386, 0.00947272150951888, 0.00294156640761900, -0.000659062389959525, 0.00467649422698169, -0.00364261598106480, -0.0100781089545807, 5.64767807750000e-05, 0.00309237136307103, -0.00248365920076044, 0.0120389971879863, 0.00468861202329471, 0.00126113054043603, 0.000555372084632133, -0.000918247957575558, 0.00929323662282355, -0.00837736981877368, -0.00608342228942496, -0.00276792528408559, -0.00738184192052152, 0.00482778502121417, 0.0122312763917945, 0.00838353592591709, -0.00163829497221693, -0.00460345105953780, -0.00434538791097708, 0.00962340957390867, -0.0113948473382414, -0.00734298790693330, -0.00293631969156410, -0.00450400214162494, 0.00630123911060260, 0.00322372851913612, 0.00668481795627120, -0.0108988769606887, 0.000276573592540338, 0.00383932756330260, 0.0110845685608513, -0.00769474841055978, -0.00223769834644835, 0.000485929186152062, -0.00635846219420322, -0.000687487574124235, 0.00138868472159277, 0.0114276209712192, -0.00461433129063223, -0.00344341058724502, -0.00386289906252321, 0.00443276575684215, -0.000466634857954451, -0.00501913399993334, 0.00160326555647611, -0.0142707534462075, -0.00457154293688070, -0.00145809501664038, -0.00528183015934840, -0.00845136556102867, 0.000884519119752458, -0.00308689448268093, 0.00306753319757308, -0.000598410975543140, -0.0109262377407403, 0.000125048615968931, -0.00153780394903147, 0.0137154231380074, 0.00412388704226671, -0.000484031103940324, -0.00719686057551996, -0.00570053434131262, -0.00933866918847379, 0.00588594685721003, -0.00926706606677902, -0.00795665321410136, -0.000829827515548332, -0.00939774580103317, -0.00309705633893295, 0.0169995174321891, -0.00205900182444746, 0.00694901073923698, 0.000599181844120250, 0.00588017415805120, -0.000763871498739160, -0.0170318529897717, -0.00588342301974873, -0.000966496393531080, -0.00677797458712093, 0.00252513491457068, 0.0106109548132402, 0.0131584740156593, 0.00115481680839696, 0.00509381509310486, 0.00222190742890571, 0.00177361892618280, -0.00521696926415952, 0.00490582830521225, -0.00196486984702454, -0.00387400803211396, -0.000301062331543922, 0.00479701926626633, 0.000841576965136759, -0.00794505973208451, -0.0108200807306194, -0.0124155548267447, -0.00695407594661912, -0.00284169892546501, -0.00790060811888083, -0.000586545092317453, 0.0158195211751184, 0.0153109568731874, 0.000230950819866543, -0.00203945885867726, -0.00468260483682270, 0.00715096142227345, 0.00566865680380660, -0.00498611324695322, -0.00885189505478784, 0.00405797079645112, 0.00924199616178550, 0.0116639483823213, 0.00217862612587405, -0.0148068893911749, -0.0167041482005907, 0.00235336503293863, -0.00721682607156587, -0.00805695264338177, 0.00236727616903029, 0.0185547242667107, 0.00799248900644500, -0.0211314429548177, -0.00129252811943753, -0.00814125905370033, 0.000675879608679625, -0.00406430991671367, 0.00265037830511947, 0.00993908080722730, -0.00209469656879815, -0.000120313612650524, 0.00495370898036804, 0.00372730354855758, -0.00353983435293476, -0.00328394296962356, 0.000813945845489023, 0.00109320854947587, -0.000488097695570094, -0.00760658826639882, -0.00442350319140969, -0.00191503928630438, 0.00499595002500358, 0.00186852256142017, 0.0111011158126220, 0.00727793987812453, -0.00141723383505221, 0.00133174066963485, -0.00635382428166238, 0.00868891911919562, -0.0145114970243320, 0.00577616709760120, 0.00777822281332871, 0.00346652424864127, 0.00827552751497188, 0.00884284576442621, 0.00710924086969098, -0.00535361557760877, 0.00421181569439491, -0.00750848862026501, -0.00465958524060903, -0.0125630326535283, -0.00560012554912781, -0.00615270495463327, -0.00495519282776960, -0.0128639855367965, 0.00201889941875641, 0.00422712052746929, 0.00798035474354242, 0.0108272273955522, 0.00816608327173399, 0.00614207944181244, -0.00345229630860613, 0.00433534095086929, 0.00358445938147059, 0.00995637130257004, 0.00654919723525915, 0.00619273311820673, 0.00846171728513935, 0.00180232977915409, 0.00708870144300705, 0.00179179835467266, 0.00522557754267772, 0.0147818847994209, 0.000316707014497500, -0.00872071995349498, 0.0179968255023729, 0.00564956910114269, 0.00889756729288167, 0.00448580474348885, -0.00132269504177852, 0.00292940511130799, -0.00635427534148689, -0.0168223013440771, -0.00381913890001241, -0.00786405524785992, -0.00654400653466945, 0.00282655234781325, 0.00487537226408775, 0.00685457847873915, 0.00912285912943621, 0.0104265138792516, -0.00245496105315374, -0.0142964734802916, -0.0137860670566148, -0.00542791064430051, -0.00466735472649446, -0.000306264723406821, -0.00918285709200119, -0.00813536644197420, -0.00310327795818038, -0.00485554717234382, 0.0174265679114036, -0.0165772836295218, 0.0111493813105711, 0.00588631719530888, 0.000793027829290471, 0.0183183742324413, 0.00769342916639484, -0.00371827468322392, 0.00454153538114949, -0.00721450906498064, -0.00701794729396543, -0.00160696363272750, -0.0185668933199067, 0.00518513653106273, 0.00182469273770830, -0.00429896993026413, 0.0111658165808757, 0.00321231565927010, -0.00182332646769673, -0.00541449750580411, 0.00616650070423300, -0.00188970081168058, -0.00416533524732041, -0.00440965274779701};
//			double cst = 2.21838386204288;

//			double weight_blue[363] = {7.76229478664478e-05, 9.49973912009178e-05, 4.36158841053463e-05, 0.000142487299674780, 0.000157474264658131, 0.000352813278167217, 0.000294789690168850, 0.000119381055586809, -8.52944696434952e-05, -0.000142467307778367, 4.89925271434361e-05, 0.000110143775074289, 0.000131470067423648, 2.38925497541349e-05, 7.83853375623510e-05, 6.78861661346742e-05, 0.000330058792170566, 0.000291158271532612, 0.000117584579197101, -7.67600095017294e-05, -0.000213843293673472, -0.000130840411502583, 0.000142060538579133, 0.000108581828067007, 6.27404812395366e-05, 2.99621780591464e-05, 0.000127725360062681, 0.000357887860368845, 0.000417182475503524, 0.000199690684011210, 3.95483790611119e-05, -8.80712397755078e-05, 1.24557821878795e-05, 0.000209463593331097, 0.000178108294327091, 0.000143621704986662, 0.000265604601233101, 0.000444543901375738, 0.000613737308639119, 0.000685455675068189, 0.000495158535517980, 0.000258700883946091, 0.000165579584256838, 0.000303757046598718, 0.000121152329851452, 7.44755531756734e-05, 0.000180037935029721, 0.000317955052034776, 5.37743483910760e-05, -0.000260013487639998, 0.000142541328712940, 0.000543269684919204, 0.000345193685560762, 0.000251234823868742, 0.000270367284693202, 0.000145244931807890, 0.000161477133142327, 0.000397725681873154, 0.000358082033240177, -0.000279059073302324, -0.000173515591240708, -0.000251362595485118, 0.000634055036025096, 0.000354517753547046, 0.000159002254186961, 0.000236710711819655, 0.000266361241323118, 0.000250546286842705, 0.000441912005697890, 0.000440256399037793, 0.000187908414984764, -8.23964988459959e-06, 0.000268562049415296, 0.000799108625661758, 0.000396363525968498, 0.000167869959302698, 0.000152088639387276, 0.000205165023044175, 0.000153911583249983, 0.000300608598490830, 0.000288865974829626, 0.000269718959923226, 0.000253394296994745, 0.000478749776477564, 0.000641384947851600, 0.000289854772264738, 8.31015761877884e-05, 0.000149200616256568, 2.06418744606577e-05, 6.08866245853672e-05, 5.78277560250726e-05, 6.26655157421182e-05, -8.39559959954226e-05, -0.000107779127954643, -5.76203821302923e-05, -4.83563358725596e-05, -6.77639565036480e-06, 1.81860167531427e-05, 0.000232740773028674, 6.35146490568939e-07, 9.12840277779325e-05, 8.51972402529380e-05, 8.79854803230423e-05, -0.000235457146197553, -0.000273526476158470, -0.000266111370525199, -0.000283689414785571, -0.000436664774484889, -1.66153435745774e-05, 0.000259365526946558, -3.99178241569959e-05, 0.000100434874668775, 9.79728543823253e-05, 0.000186334545152689, -2.40236415066648e-05, -0.000171132765164031, -0.000229338821350385, -0.000347443617439995, -0.000220361254790055, 4.80097381272255e-05, 0.000312285863705525, -5.33496766460825e-05, -1.84532321271289e-05, -8.30783229410247e-05, 4.53519387384446e-05, 0.000107472517686173, 0.000390068998109164, 0.000374450216563635, 0.000183837293046232, -7.68290414497035e-05, -0.000205461695985659, -3.92769933726405e-05, -6.68077071089258e-07, -1.33256899941141e-05, -0.000166544869121452, -0.000149109641654609, -0.000128759563850913, 0.000219232784023796, 0.000272756278318878, 0.000106708943403079, -0.000201007991050434, -0.000360507009642741, -0.000241947341661154, -1.63074427786941e-05, -2.53963973779722e-05, -0.000130683249455771, -0.000228194856188154, -0.000155637869266772, 0.000112850390498798, 0.000223518921466947, 3.84632895100295e-05, -0.000230726001791707, -0.000328043387988699, -0.000160370092729279, 4.26706657545941e-06, 3.05703066592437e-05, -0.000127797740277796, -0.000107721415335849, -8.81638109454831e-06, 0.000162013384679659, 0.000247388930093784, 5.68202550904155e-05, -0.000180390330459045, -0.000221498119641841, 5.09942493798444e-05, -0.000145553764238457, -0.000170771144202764, -0.000248593646036401, -0.000221054410004392, -0.000603351742260909, -0.000969867371697709, -0.000611816813163555, -0.000204349092979914, -0.000164067742254087, -0.000168526241735654, -1.99562393495447e-05, -0.000161553482454635, -0.000186134209277188, -0.000144957146076535, -0.000338615008791852, -0.00109046711230367, -0.00106004259507143, -0.00120663846183922, -0.000323945442293993, -0.000154361730980837, -0.000266450118469179, -5.05704460240782e-05, -5.08208976670714e-05, -7.69456076709492e-05, -7.58693654081023e-05, -0.000215191314115569, -0.000635886332477171, -0.000913000651455519, -0.000713143802288094, -0.000160469192041575, 1.63458382706087e-05, -0.000131986105023746, -4.66508584016751e-05, -2.23258749299722e-05, -2.45186482571804e-05, -4.29247077917485e-06, -0.000133306538081139, -0.000275558902545765, -0.000364288079426334, -0.000167101210019657, 2.68184352530917e-05, 0.000111895318512395, -4.86288103082063e-05, 6.85821504655119e-05, -0.000148610845862191, -4.89382677283605e-05, -8.69509928087832e-05, -0.000150571756872317, -0.000367801770964379, -0.000385073202762038, -0.000327957404568430, -0.000272898062418105, 2.12889499858275e-05, 6.88516008916196e-05, 0.000255470208001056, -9.65285194793415e-05, -4.31036897562650e-05, -8.00302841037515e-05, -9.86677561238593e-05, -0.000433963811135681, -0.000418872501456544, -0.000331277321167019, -0.000292567123274376, -0.000296578301145399, 0.000123206125485074, 0.000337364425338082, -0.000165048958468705, -0.000134178010801203, -0.000165150078786918, -8.31443043320793e-05, -0.000259690907851905, -0.000308484602522025, -0.000288320920461981, -0.000354692923668780, -0.000103286517904423, 0.000168593213281589, 0.000398153415918820, -3.37375629031537e-05, 7.30042325140589e-06, -1.13304542447277e-05, 0.000102629736805152, 0.000139567445282422, 0.000398864133371676, 0.000341376871079527, 0.000125711654608366, -0.000143844065745051, -0.000246198813697528, -4.41247964301098e-05, -4.09060279911617e-05, -3.88942040216931e-06, -7.10045545073350e-05, -1.62085373161041e-05, -1.27125385368364e-05, 0.000256358266048229, 0.000253534958864214, 8.51340916997849e-05, -0.000171309366310385, -0.000327255102642325, -0.000227310354166120, -2.80066079408948e-05, -3.08143018312358e-05, -3.11536970840719e-05, -9.92267544077973e-05, -2.23993433847804e-05, 0.000176467555089047, 0.000261533796892536, 6.78944229444519e-05, -0.000108839523537912, -0.000232823037935206, -9.33089476480142e-05, 5.39819968729398e-05, 5.88053399488365e-05, -1.28613679927186e-06, 5.01657058540521e-05, 0.000146320123742995, 0.000279436420226406, 0.000332156660578401, 0.000168566798982909, 3.32915564491148e-05, -2.23235158445477e-05, 0.000198543753878512, 3.94047466090845e-05, -1.24228647820399e-05, -1.93226176507127e-05, 4.63125604643054e-06, -0.000406095318298590, -0.000770216861143796, -0.000419573341188771, -1.17083577476174e-05, 6.42465019318287e-05, 5.45601440963845e-05, 0.000186723352954071, 0.000142224831001880, 9.08043730928383e-05, 0.000156907887006539, -3.49723419273193e-05, -0.000839780262146244, -0.000829596311144506, -0.000962456747110888, -6.97305899314770e-05, 8.19018312229108e-05, -4.53250704540029e-05, 0.000150275939562506, 0.000282146010979490, 0.000246460196600693, 0.000248542889678050, 0.000122274564571323, -0.000297115536738020, -0.000589107822511970, -0.000382359993197793, 0.000173275714730081, 0.000260887105565741, 6.20975213194082e-05, 0.000120858429372582, 0.000230797721007437, 0.000201677986421067, 0.000272963434811402, 0.000159806452300864, 2.97519468826590e-05, -9.05103937324937e-05, 0.000109085116272226, 0.000299015832756668, 0.000329947349451049, 0.000119719955543406, 0.000186020899475744, 1.96079469243681e-05, 0.000109234292273390, 0.000140819993885986, 8.86331659707053e-05, -0.000126324103541489, -0.000191464288934076, -0.000122610680186818, -7.14708997430147e-05, 0.000194904783137470, 0.000183821546940390, 0.000351125904612413, 4.25856719194250e-05, 0.000101508182492443, 0.000127794406885488, 0.000128500410536901, -0.000198230085329773, -0.000216358487258017, -0.000150815814141283, -0.000133573167399983, -0.000173298758594919, 0.000225077124887998, 0.000436084769695577, -1.06425033876784e-06, 5.25383627327810e-05, 3.95800340464432e-05, 0.000150226200532095, -3.58110148522310e-05, -5.90662546007988e-05, -8.42598259982796e-05, -0.000176589069396433, -6.52073587837764e-06, 0.000265766127969243, 0.000528022388047818};
//			double cst_blue = 1.40095417984786;
//
//			double weight_red[363] = {1.34679248768199e-06, -0.000325894315092108, 0.000180532557995500, 0.000251532548156613, 0.000484910620988963, 0.000347065522680809, 0.000253002437182682, -3.69468973821020e-05, -0.000131804799518456, 0.000118319288099427, 0.000774183262097077, 9.86239984119834e-05, -0.000236145993859304, -1.57410799682234e-05, 0.000517744946091030, 0.000531686830742096, 0.000223755379209514, 0.000477988516001138, 3.96764543804833e-05, -0.000245277251877487, -0.000235082159289934, 0.000267095480617290, 0.000928899786094827, 0.000210160769500072, 1.26360694141665e-05, 0.000555546897418236, 0.000586298943547453, 0.000444433088218600, 0.000519799357842068, 0.000528046862030738, 0.000440634930742183, 0.000470269608800736, 0.000436761538612841, 0.00104697616995204, 0.000714140398884473, 0.000122606807973905, 0.000107090093104113, 0.000529568223531210, 0.000530698450652801, 0.000529844436724842, 0.000663144704068983, 0.000604612509077840, 0.000475785598217453, 0.000190317199761832, 0.000558012049456759, 0.000211183235385137, -0.000352409648270074, -0.000491645354852001, -0.000707093497425784, -0.00110974711987921, -0.00112547059694134, -0.000545751675147064, 9.01483797932185e-06, 0.000443529145118369, 0.000342926249198286, -0.000169782178029651, -0.000875111081802731, -0.00140042366732016, -0.00165458848037527, -0.00247746769089801, -0.00330181964885095, -0.00305802036337986, -0.00197318811182443, -0.00109779240966107, -0.000247004341271021, 0.000235162433815067, -1.66001825445604e-05, -0.000434697797801698, -0.000849113388545938, -0.00168105619773223, -0.00243584707366603, -0.00278622337965088, -0.00240791541449590, -0.00151612477553039, -0.000651489334978392, 0.000247366826457983, 0.000528131142040542, 0.000594626581799625, 0.000177243724950067, -0.000307908462512180, -0.00101681239891951, -0.00162951516595820, -0.00163521082878568, -0.000838994061801421, -0.000550986733465570, -0.000367910927511804, 0.000596158495927072, 0.000610301316411320, 0.00121201764086066, 0.000615331396291709, 0.000381945415011692, -0.000496330782934376, -0.000724557412238199, -0.000786918712882581, -0.000180648602633377, 7.64965549511217e-05, 0.000606496278897501, 0.000600658038622369, 0.000781025053277418, 0.000237760007661172, -0.000120005354351031, -8.28328398913357e-05, 0.000415492108291125, 0.00110256723785548, 0.00100202587174120, 0.00116093881216222, 0.000626841390982166, 0.000485455898895583, -0.000632411030096572, 0.000239801714160235, 0.000300864245138307, 7.73053553335145e-05, -0.000376562504137710, -0.000803835483785469, 0.000122854387951621, 0.000244102039841205, 0.000305273533453922, 4.90881341160298e-05, -0.000256193467049432, -0.000651953057070784, 0.000396220680500019, -0.000168966478456699, -9.04158385898343e-05, 0.000459392470941888, 0.000228759868256731, 0.000190958905966426, 3.85973677379903e-06, -0.000223674270634669, -0.000541549287638569, -0.000457551729343078, -0.000521676846820361, 0.000199414460904311, -0.000169885918485767, -0.000336739220830973, -8.01035208907335e-05, 0.000244985100308466, 0.000168185200104992, -0.000201948269411503, -0.000206228631782794, -0.000592993137596932, -0.000872338346086036, -0.00104579369409535, -0.000403837138548951, 0.000154798306695882, -0.000386536328187925, -0.000448989566139325, 8.47591588513827e-07, 0.000218982182445194, -3.07095298729791e-05, -0.000212259054663281, -0.000517445685482622, -0.000571127077649140, -0.000601355204075898, -0.000488759092916804, 0.000356820786191342, -2.01987522120201e-05, -0.000207133592823317, -3.64150001919225e-05, 0.000610709134361701, 0.000570427465383306, 0.000338572544832464, 0.000107838085597619, -0.000110500731560961, -0.000443890786537944, -0.000508912858286197, 0.000229917909204483, 9.40310416128932e-05, -0.000163548131233988, 0.000290200526404899, 0.000571190029785198, 0.000353911074483007, 0.000120359238572592, 0.000188701325742759, 0.000397781015802122, 5.31960659324143e-05, 7.93684093646791e-05, 0.000212781121767131, -0.000415132605752775, -0.000390986437397764, 0.000200205549712516, 4.25699960731442e-05, -0.000417827062078300, -0.000522508704611595, -0.000114078871019420, 0.000615609163435596, -9.45337662826743e-05, 0.000339514744179969, 0.000343120889857933, 5.31373742913574e-05, 0.000235375648728366, 0.000336508565396241, 0.000495882124900023, 0.000377703043320914, 0.000257118949678321, 0.000251901460521272, 0.000845951359449807, 2.66764133622108e-05, 0.000479731462394211, 0.000449978260568571, -0.000139013515558894, 4.93691527205042e-05, 0.000267965707957901, 0.000352077618358590, 0.000690916273348757, 0.000739894332391296, -3.79427613173924e-06, -0.000262796831408577, -0.000476843002530065, -1.09116096559134e-05, 0.000187212286984403, -0.000395021455291132, -0.000197285746552908, -1.79918805701468e-05, 0.000551911370173586, 0.000684078898385142, 0.000460707555103650, -0.000480582607177849, -0.000592788873876883, -0.00101043985407053, -0.000494959653221638, 6.88351514772728e-05, -0.000249422865339428, -0.000211947518024914, -5.73486064316043e-05, 0.000374141056623289, -0.000178586144277740, -9.37947458257744e-05, -0.000771967494762094, -0.000806660173234236, -0.000328328153768193, -9.69166434553605e-05, -5.42802696481934e-05, 0.000123662415857009, -5.91086701226679e-05, -0.000416197713396280, 0.000281795527767351, 0.000243322421322504, 1.64103749468067e-05, -0.000279683624803999, -0.000490268695789030, -0.000187621501631764, 0.000130530841430792, -0.000659753811310892, -0.000665872865805797, 5.99959095120181e-05, 0.000272741216313458, 0.000282894821818297, 6.79980560910479e-05, -0.000157508493604727, -0.000568000976905333, -0.000738591105574535, 0.000125460493627049, 0.000374505809371925, -0.000390814680653857, -0.000532260871141643, -0.000100108810859836, 0.000410438278382913, 0.000307165343185991, -0.000102647179150169, -0.000200739629252460, -0.000914749368442758, -0.00127457523191144, -0.000350039251027826, 0.000199623057803949, 0.000534262257514247, -5.18432948876086e-05, -0.000199540628015693, 0.000320397266534264, 0.000432536510364188, 0.000195092531731741, -0.000191687820565308, -0.000697174100613878, -0.000888675994122634, -2.26542513173986e-05, 8.34235029068889e-05, 0.00104858006180141, 0.000679385076167583, 0.000419632803557165, 0.000621146176754046, 0.00123381648845291, 0.00112870925013036, 0.000765490962480364, 0.000315060027357696, -0.000127327262053809, -0.000332219378175123, -0.000255378818483122, 0.000789066306994275, 0.000922218469310122, 0.000796470968832891, 0.00143127808169436, 0.00157542345796203, 0.00126058928723578, 0.00104500382169816, 0.000874743495768905, 0.000992976563826280, -6.01896307899736e-05, 2.82997157484187e-05, 0.000479439108235456, 0.000239291744033791, 0.000550971677773751, 0.00138605771830776, 0.00124527836917573, 0.000801710228743159, 0.000586835959126294, 0.000960868246559420, 0.00155197090050171, -0.000293003672487464, 0.000389491070518161, 0.000305255147782105, 0.000491109383442740, 0.000860350501685789, 0.00120761417845892, 0.00136308311373768, 0.00121734773070875, 0.00117422878077947, 0.00110207711877119, 0.00161310084951809, -2.10086348145792e-05, 0.000545213853354249, 0.000501954351241480, 0.000220009129190069, 0.000511974520056416, 0.000802555166072499, 0.000777895142996806, 0.00102647086205640, 0.00108635129387486, 0.000371755155261945, -7.42515757476830e-06, -0.000242642165770376, 0.000332458629094261, 0.000352575397582118, -2.25713917678074e-05, 0.000332000373171363, 0.000206383510519223, 0.000722075998452145, 0.000615457023752710, 0.000329101821198585, -0.000633978854196919, -0.000779364264325759, -0.000527826351965197, 4.28899635150183e-05, 0.000857665062346200, 0.000585376878366121, 0.000603924649698007, 0.000424095242781701, 0.000685819515891840, -0.000246857046322339, -0.000414869516604870, -0.00138630603632296, -0.00158629230233449, -0.000619532314121905, -4.40330853405018e-05, 6.16600862368492e-05, 0.000174143512902284, -0.000157276354150603, -0.000660888900875300, -0.000174155145562999, -0.000235314280289113, -0.000501274035287263, -0.000939416906823953, -0.00123512729947121, -0.000807743802757591, -0.000270282433894095};
//			double cst_red = 1.47770439613697;
//
//			double weight_yellow[363] = {9.35900645012613e-05, 6.87342691850322e-05, 4.92727321594987e-05, 3.90365227201118e-05, 4.59565887922518e-05, 4.71121853157072e-05, 5.15782378733679e-05, 6.19043761308017e-05, 6.90124088565765e-05, 5.16378425419942e-05, 7.97872539089508e-05, -3.29610226837026e-05, -4.44575754085934e-05, -1.53356812874106e-05, -1.76980894278912e-05, -1.27012477183024e-06, 1.73470557405964e-05, 2.35364502573658e-05, 1.44211409519309e-05, 1.14946141960213e-05, 4.35564918859866e-06, 2.06367051765454e-05, -0.000105013527264441, -0.000110165115296515, -0.000103532630600907, -0.000110767043544896, -8.39347754374816e-05, -4.88361856794578e-05, -1.97455848650802e-05, -1.61618707603340e-05, -9.60335473858433e-06, -8.06833465893369e-06, -6.32452427270703e-06, -0.000104576928982505, -0.000121464006392684, -0.000183443035042254, -0.000235854396698296, -0.000232789485867450, -0.000246382302334916, -0.000133011259156326, 3.39710504944057e-05, 3.49073779295684e-05, 2.58879671311041e-05, 5.44580623422393e-05, -0.000239226283213220, -0.000210651381254226, -0.000165430476372643, -0.000281384470754411, -0.000298516331772376, -0.000283255572452813, -0.000263637014616622, -7.91585356024614e-05, 1.18401367427156e-05, 1.13263642224488e-05, 5.60257524233602e-05, -0.000209234155247794, -0.000260674010221099, -0.000153346653169619, -0.000290048203609439, -0.000284007320829459, -0.000258581155044424, -0.000260180364467160, -0.000185021529410368, -4.90788434211557e-05, -1.25571914639172e-05, 3.76401605746932e-05, -0.000191821098664020, -0.000205319222024979, -0.000159863324034224, -0.000294814940601328, -0.000236453751884164, -0.000266366795998089, -0.000245058900048608, -8.64948232942913e-05, 9.72058120573232e-06, 1.21080160642408e-05, 5.44414104126926e-05, -0.000156407379455221, -0.000188868670619953, -0.000155875046352137, -0.000290870346607335, -0.000286478822149580, -0.000295728764259758, -0.000177075616124331, 3.97970791717805e-05, 5.69130750284253e-05, 3.69254095867405e-05, 5.49815767496056e-05, -0.000168578026258008, -0.000161239866721475, -0.000132784357759558, -0.000109015802871982, -0.000115575261920267, -6.40343684377448e-05, -1.43498629719947e-05, -8.94424643996776e-06, -2.47734645128169e-06, -1.81486403769945e-05, -3.64295257953904e-05, -9.10641460040919e-05, -0.000130684655459482, -0.000117203857073066, -0.000119215739043972, -0.000106774388135666, -9.71877593242523e-05, -8.93831659056391e-05, -8.11388242738178e-05, -9.02423397915324e-05, -0.000109227886545076, -9.34072309582383e-05, -0.000102117306033057, -9.91668990309576e-05, -0.000100307180378899, -0.000116049749553874, -0.000120145396677587, -0.000114486014555794, -0.000109265739667804, -8.92186381550449e-05, -6.48374921999433e-05, -6.88533755384310e-05, -4.27399972259853e-05, 9.15848118377410e-05, 5.61808833459132e-05, 3.35164116005249e-05, 1.43027737626674e-05, 4.64241586615842e-06, -3.86078772770982e-06, -1.81140579718597e-05, -1.44669962165434e-05, -1.58626191951914e-05, -2.03201863876129e-05, 8.17342692661026e-06, 9.51763710215894e-05, 6.52485223453199e-05, 5.16313822132530e-05, 1.25785256791142e-05, -4.87211095035622e-07, -1.01809467668729e-05, -2.32737708296573e-05, -3.43953485753858e-05, -3.77387780472865e-05, -3.71522834583651e-05, -1.98063570119290e-05, 8.75531267860467e-05, 5.15108275135402e-05, 1.88941834640502e-05, -2.57230450938097e-05, -3.44421924684658e-05, -3.32968571395618e-05, -3.86814995787883e-05, -5.94099736808325e-05, -6.03549839088840e-05, -4.87267187571125e-05, -4.93530807995161e-05, 0.000147370968548939, 0.000106894565075553, 4.71801070888039e-06, -9.73898274921430e-05, -0.000152777350401438, -0.000218320771105991, -0.000150315168508292, 2.97506689411459e-06, 8.09520831066663e-06, 1.20514442807471e-05, 3.35126944206466e-05, 1.28745225475618e-05, 5.34611616675227e-06, 1.73273668287249e-06, -0.000184014246093326, -0.000272514306630818, -0.000295979456963956, -0.000290395493144458, -8.53729699450174e-05, 2.42559202973869e-05, 5.03070113731759e-05, 7.62427907992814e-05, -1.08409072718414e-05, -9.37137555064391e-05, -4.06745197708406e-05, -0.000267054125487582, -0.000300758210314227, -0.000308268696557744, -0.000296014911746690, -0.000173005941766378, 6.17257797636121e-06, 6.93442516098068e-05, 9.63222144053365e-05, -1.33564766124774e-05, -5.50081262043363e-05, -6.19956724087747e-05, -0.000254030927907610, -0.000253910119427212, -0.000302375376523307, -0.000265339489423559, -6.84464554805612e-05, 5.37260073855603e-05, 8.33765982701274e-05, 0.000104768213516734, 4.95073782312563e-05, -1.11252108247976e-05, -2.67281155425662e-05, -0.000235557985381489, -0.000258066712783933, -0.000286893057419148, -0.000173795910062741, 3.65338505918384e-05, 4.87840511839564e-05, 4.49258986604583e-05, 5.44360817005856e-05, 6.93620451436916e-05, 3.79384294418512e-05, 6.69503291379807e-06, -1.92303211679440e-05, -6.42023983838724e-05, -4.61647169074050e-05, -1.81896215644846e-05, -4.56390610555396e-05, -5.96635882112295e-05, -5.80749693674828e-05, -6.96372732538922e-05, 0.000117188947105203, 3.23062040721340e-05, -1.55334974328537e-05, -7.09347361394407e-05, -8.83545393273371e-05, -0.000102103154590882, -0.000117738971961996, -0.000131924192133731, -0.000152418464369693, -0.000150144444417578, -0.000123459151534070, 1.67979143515883e-05, -2.99788733126799e-05, -7.74899094760029e-05, -0.000116241420363649, -0.000123757666885872, -0.000121982074368472, -0.000127462630197711, -0.000124259492808904, -0.000114739827922234, -9.72178506243724e-05, -5.99869321134207e-05, 3.60118827283789e-05, 2.04042972088398e-05, 2.49536307975328e-05, 3.98578294972105e-05, 5.87980551927334e-05, 6.01998551006513e-05, 4.14889695885915e-05, 3.29042838625541e-05, 2.01763361581486e-05, 2.09731959249156e-06, 1.53104429224881e-05, 6.71989442981559e-05, 6.49437654778243e-05, 8.91545348102398e-05, 8.51626943789065e-05, 8.67619423897311e-05, 8.08240890632248e-05, 5.89524144327291e-05, 2.58366394011274e-05, 1.68717849619661e-05, 1.98648924758076e-06, -3.37954585595726e-06, 9.53763107668992e-05, 0.000103728740558590, 0.000114739726753150, 0.000105433922435036, 0.000109375506024872, 0.000105043304680645, 8.75499262568356e-05, 5.67545866623424e-05, 4.18926477507652e-05, 2.98380879182016e-05, -4.83331588658666e-06, 0.000194294539389125, 0.000204838827134517, 0.000163532220690912, 0.000116391495369901, 9.66784422447425e-05, 3.12655741182533e-05, 7.87320852793026e-05, 0.000196086295173967, 0.000163938669384688, 0.000122832703323274, 9.73223079008750e-05, 0.000106242217516959, 0.000158321582070790, 0.000215437462259366, 0.000119404099504436, 7.74189191084604e-05, 5.99009086751469e-05, 2.80047783097650e-05, 0.000164963506513399, 0.000193304670934912, 0.000178000233989290, 0.000153528639656463, 0.000112998739802818, 9.16018696284587e-05, 0.000212556541880956, 7.52659264202311e-05, 8.95707075536378e-05, 8.76922403968055e-05, 4.80330775254923e-05, 9.42451233907336e-05, 0.000204105399671270, 0.000200992552185790, 0.000178537306237537, 0.000105291401639337, 0.000117415182740123, 0.000189165506141851, 5.55209543123487e-05, 9.72509372888474e-05, 4.00033974165018e-05, 3.57285176223602e-05, 0.000166732075403765, 0.000213880004975288, 0.000207037400779182, 0.000185463127009194, 0.000138165524796743, 0.000127872680752481, 0.000173214773574968, 6.86155151437751e-06, 3.42131072038049e-06, -3.57243231855084e-05, 5.21472293813289e-05, 0.000215714801226503, 0.000212238486645533, 0.000162092539837742, 0.000130771682404126, 0.000121652778842503, 0.000134812502327208, 0.000157756859253173, 0.000155686386482589, 0.000116629470584183, 0.000122403678873133, 0.000138694342762450, 0.000100177646942638, 7.60689387722559e-05, 3.40877830122127e-05, -1.95621994163653e-05, 0.000135557962312320, 9.74493317236783e-05, 9.35014157086095e-05, 5.98413854176548e-05, 3.86079709659383e-05, 1.89297985915326e-05, -1.08920245527616e-05, -3.25887923159327e-05, -5.91985715553896e-05, -9.46576902367391e-05, -0.000103898370424176, 7.50252294416798e-06, 6.39710634241549e-06, -4.25902062319992e-06, -3.27733641548158e-05, -5.30513148287150e-05, -6.02148320554699e-05, -7.43318445622855e-05, -7.38358242418180e-05, -6.78714390435638e-05, -7.06706541001959e-05, -6.91101243809575e-05};
//			double cst_yellow = 2.43897876078900;



//// 1/4
//
//
//			double weight_blue[108] = {-0.000864201074205096, -0.000603490889688942, 0.00252085241484628, 0.00113155561321054, 0.000318779165129789, -0.000715787397012040, -0.00153719877474295, -0.000391834010439348, 0.00313870382209785, 0.00303889433214145, 0.00192137360958958, 0.000683129125414567, -0.000791624966102504, 0.00159419969397775, 0.00275995209339951, 0.000412034485533040, 0.00339296458660428, 0.000751748706132423, 0.000319652327706393, 0.00153582918862019, 0.000990962713207863, 0.00413630884046397, 0.00189520158828135, -0.00149648254695109, -6.61463041714876e-05, 0.000234690736739564, 0.000341944458248152, 0.00141120472046528, 0.00128488738295858, -3.57007237583456e-05, 0.000750972173807953, -0.000677815056291537, -0.00194663626611371, -0.00123541665494785, 0.000651176246889399, 0.000380272641113496, -0.000609426749866340, -0.000346183480506090, 0.00266422813347099, 0.000954940794342340, -0.000299722884484451, -0.000721699257931356, -0.00149194478252293, -0.00131564302318215, 0.000739678517967744, -0.000422171127636771, -0.000505671664022692, -1.36383362537653e-05, 4.01725880748863e-05, -0.000101853307995155, -0.00334909177220954, -0.00789060879237799, -0.00206475458138778, -0.00104068631526883, 0.000929540402786601, 0.000121237835297225, -0.00437150151394412, -0.00352273738372704, -0.00289281731424302, -0.00288260524119719, 0.000334293956939883, 0.000321274142100583, -0.00108423430356813, -0.00112373800380107, 0.000207677520105134, 0.000191368233874379, 0.000451976602844090, -2.43544712815889e-05, -0.00134676317898661, -0.000763763283049541, 0.00167158340990175, 0.00157656814114580, -0.000532079709901580, -5.19409971925567e-06, 0.00286460480880572, 0.000281607935443616, -0.00120224828994833, -0.00112121773957940, -0.00128523197294947, -0.000802217243182682, 0.00141172397594992, 0.000380815642660656, 0.000195030759911494, 0.000604889360615548, -0.000231944102669715, 0.000828892018041960, -0.000809765709737952, -0.00415229589728560, 0.00169424702094325, 0.00157083289537685, 0.00161941039902972, 0.00153225358639922, -0.00142931775674933, 0.000818244232156542, 0.00127431150271712, -0.000441762654140025, 0.000326612529028235, 0.000709139617134056, -0.000562769094725627, 0.000209988784586064, 0.00174810564813157, 0.00105806515226759, -8.04060092062463e-05, -0.000303108537331478, -0.000928734150796207, -9.73609568798255e-05, 0.00149040648319210, 0.00104667991841666};
//			double cst_blue = 2.09254490287599;
//
//
////			double weight_blue[108] = {-0.000865140243786616, -0.000603868818577006, 0.00252051890757716, 0.00113198677049929, 0.000318825896052826, -0.000716143705190100, -0.00153788764767019, -0.000391328722404081, 0.00313959607886766, 0.00303931136330405, 0.00192100543300505, 0.000681925691394949, -0.000791529513535991, 0.00159446321433331, 0.00276104982531220, 0.000412434309449857, 0.00339382836751231, 0.000751797760259815, 0.000320266182307564, 0.00153442072709837, 0.000991347195023648, 0.00413639680880779, 0.00189522635715334, -0.00149701047604240, -6.63529583103985e-05, 0.000234528207570572, 0.000341765196088413, 0.00141172260030404, 0.00128479367762350, -3.59057654314274e-05, 0.000751763650552087, -0.000677629973146524, -0.00194715092795545, -0.00123464473130795, 0.000650872292302909, 0.000380070632751393, -0.000609585677171365, -0.000346211741808413, 0.00266373386437474, 0.000955260905509976, -0.000299318819609695, -0.000721248824866438, -0.00149211955808636, -0.00131526635637282, 0.000739846455330761, -0.000422391865071515, -0.000506101851896303, -1.41841708926811e-05, 4.07830514292770e-05, -0.000101840350783072, -0.00334927514813012, -0.00789190992483691, -0.00206494449690530, -0.00104059424936894, 0.000930392813939357, 0.000119814523193137, -0.00437173142213384, -0.00352381127652723, -0.00289361985949040, -0.00288327409737713, 0.000334161215073273, 0.000321242244589429, -0.00108467071499864, -0.00112380127927821, 0.000207481579028657, 0.000191489109804149, 0.000452586122600863, -2.38730359392661e-05, -0.00134690629758093, -0.000762880371809101, 0.00167133804477348, 0.00157669000948500, -0.000533072323982101, -5.80598269557216e-06, 0.00286407579556736, 0.000282038854836701, -0.00120175312008550, -0.00112075792073550, -0.00128609694759429, -0.000801887449182802, 0.00141248767838975, 0.000381204380260122, 0.000194812186792555, 0.000604007802886846, -0.000231645167156977, 0.000829548348268611, -0.000808760710652399, -0.00415224096840635, 0.00169515424310183, 0.00157122038890496, 0.00161989326726577, 0.00153123221703788, -0.00142826128451555, 0.000818978448235704, 0.00127489694398604, -0.000441876992721906, 0.000326055723084026, 0.000709016551479539, -0.000562930365186857, 0.000210516553466756, 0.00174839204576717, 0.00105845686334707, -8.03508485202411e-05, -0.000303375365860814, -0.000929622351278233, -9.69180342997034e-05, 0.00148996539730226, 0.00104697618288333};
////			double cst_blue = 2.09260153787214;
//
//			double weight_red[108] = {0.00852492661780513, -0.0119568591507889, -0.000666410171188594, -0.000342510119258274, -0.00374661272161987, 0.00146356087251384, -0.00173437688161543, 0.00324479144744197, 0.0130856565248007, -0.00279347032243405, -9.25311160662745e-06, -0.0127566754505203, -0.00179912630943332, 0.00659828934604551, -0.00533535187847335, -0.00594569431167575, -0.00958174215524986, -0.00235615590991880, -0.00516640792325460, 0.00580019671561848, -0.0194104154054077, -0.0114367579942957, -0.000526897480772472, 0.0157035568261859, -0.00949953050668650, 0.00259849858993184, -0.00544314455870651, -0.00758042150511173, 0.00649838592299107, 0.000157541320754424, 0.0129081640455375, 0.00217227775800825, 0.00335607282357128, -0.00596993824068108, -0.00135969064229300, 0.00879987031499426, 0.0101990516337187, 0.0103827298841343, 0.00879520698979861, -0.000532661985699429, -0.00149903928355943, 0.0174968907884601, 0.00145287681399096, -0.00642795342032055, 0.00196331161101821, 3.62122192623313e-05, 0.0159756726013449, 0.00573991382445501, 0.00197161872085701, -0.00187605924806929, -0.00794581347904298, -0.00404778081308977, 0.00214384164904258, 0.000795602040511609, 0.00916046763478687, 0.00119753525662788, -0.00907716807832313, 0.00304979825910520, -0.00688053183631386, 0.00121123348515695, 0.00495885378963496, -0.00232702563597533, -0.000100922561250646, 0.00236717613749219, -0.00970062002125820, -0.0116594162231352, -0.00620488195807488, -0.0107626890955032, -0.00388841773349286, 0.00208760736010324, 0.00168634562651266, 0.00726517102194385, -0.00212825147881204, -0.00432949556921669, -0.00677516028600341, -0.00905323964138156, -0.0100921599905933, -0.00182931829986988, 0.00237897336462680, -0.00783891709846910, 0.00456705459418204, 0.000894177892781293, 0.00423281846176344, 0.000873889767010911, 0.00213391535941959, -0.00451445549888265, 0.00435389459270372, 0.0128281090283831, -0.000796029831476053, -0.00144682230689809, 0.00256501915570172, 0.00392924484647605, 0.00530841015895730, 0.0207189789107416, -0.00682621926180926, -0.00247055559070180, 0.00609115035180594, 0.00895552586317509, 0.0165970131584756, 0.00842758777143675, -0.00215103063289397, -0.00558013841939500, -0.00848298823147136, -0.0123182735734784, 0.00251139303327096, 0.00125529068963040, -0.000700582376212662, -0.0108690662056376};
//			double cst_red = 4.53338870994548;
//
//			double weight_yellow[108] = {0.000219180090116557, -0.000186515027534734, -0.000211631030049610, -0.000169198309742152, 4.02607749469888e-05, 0.000272250835057138, 9.51780065813658e-05, -0.000307563044002270, -0.000189025523720249, -0.000367421163409316, -0.000433182517225470, -0.000121922056930868, 8.21092327118905e-05, -5.71283640328302e-05, 5.21395881173765e-05, -0.000116122289306041, 3.95060232010297e-05, 9.43293177041589e-05, 0.000164093022585295, -0.000392036215103157, -5.36108114598967e-05, -0.000216211507803641, -0.000278269402843933, -0.000110089412711573, 9.05679040670321e-06, -0.000400665601702190, -0.000252940661388713, -0.000196534369450928, -0.000279354167995257, 0.000144984997147786, 0.000334376676059110, -0.000217828772005021, -0.000316423682446498, -0.000363934470199754, -8.02234528521790e-05, 0.000499854248046478, 0.000326493227955569, 2.85158810799308e-05, -0.000273858681427817, -0.000497809757139979, -0.000255265741341054, 0.000266480074119035, 0.000318037321906686, -0.000200155065977317, -0.000359214134659780, -0.000731628815819736, -0.000769016653282861, -0.000278977963073408, 2.42084473650638e-07, -0.000509408815774050, -0.000510318786431013, -0.000735205684142253, -0.000502955454971425, -0.000259663457654742, 2.19600460384931e-05, -0.00101756520356964, -0.000841518013882421, -0.000931570967864951, -0.000866139172488973, -0.000617879336370427, 0.000115450942465158, -0.000907029280497011, -0.00113467654212059, -0.000965927482668398, -0.000939401371924868, -0.000298597587378365, 0.000477576812040839, -0.000404875266276323, -0.000898418408269825, -0.000954563437902255, -0.000492400814153009, 0.000249999173147362, 0.000169886254000482, 0.000298225879818112, 0.000440911573853820, 0.000327426266505897, 0.000442275589123046, 0.000387159209866568, 0.000642815357119551, 0.000675501774181210, 0.000850222183010333, 0.000608498563380417, 0.000503062545314135, 0.000437706818198009, 0.000483590329694521, 0.000569985725093354, 0.000929192531406592, 0.000828025376013822, 0.000897525340172324, 0.000667361784127200, 0.000577256589644336, 0.000351549327654967, 0.000800574097919010, 0.000707321975281603, 0.000577156478860996, 0.000485202807360166, 0.000651759137137517, 0.000490083627397181, 0.000605353701336740, 0.000765926302818378, 0.000658834127933873, 0.000773753458968705, 0.000793205910523887, 0.000607676174211699, 0.000548697295185158, 0.000570756733385390, 0.000720079369235082, 0.000831602402100551};
//			double cst_yellow = 2.41254244004827;


//C=0.01
			//double weight_blue[363] = {0.000397817903138288, 0.000426323264661247, -0.000221810047814491, -0.000150329547397481, 0.000285048324566436, -0.000413416396982418, 0.000101765844945532, 0.000181651936900518, -0.000235890730271329, -0.000343116288687540, -6.78456634278577e-05, 0.000104213981279446, 0.000235562925707932, 0.000429236432156931, -0.000141131029398248, 0.000445954859796402, 0.000557914121572509, 0.000319593990486966, -4.37560291868863e-05, -2.93111122217213e-05, -0.000233634644215451, -0.000591796411404108, -0.000163158181312393, -0.000104213071039687, -2.15826829203054e-05, -0.000665874540241869, 0.000624050171235451, 0.000982638147550934, 0.000487015128968802, 0.000186374662701964, -0.000122815536821136, -0.000226310162836263, -0.000236782615030100, -0.000353104759403757, -9.24273243579983e-05, -0.000157501039953066, -8.01746704035769e-05, 0.000983350226082041, 0.00224574978464261, 0.00115886407027065, 0.000163865632991855, 0.000382998499540790, 0.000265009192506416, 0.000484013191466876, 4.53541136710614e-05, -0.000392675138469991, 7.35293742222480e-05, 0.000314260442365010, 0.00147742017640519, 0.00211586110097975, 0.00144639809989996, 8.71113307821204e-05, -5.96228188401302e-05, 7.75781539171258e-05, 0.000384872943871995, 0.000990509313560931, -0.000501543759167669, 9.41050751681392e-05, 0.00136179051314169, 0.00145554971234468, -0.000592242306351378, 0.00263859503840860, 0.00105689420369559, 0.000302594385838767, -0.000179228118336468, -0.000176440433626168, 0.000588215969987811, -0.000663450306651876, -0.000638157699009675, 0.000467303262637198, 0.00201702358493154, 0.00176481585718054, 0.00195557864723529, 2.39545042176187e-05, 0.000256801280092247, 0.000154740696590930, -0.000145818758420085, 0.000184111130984714, -0.000112405708078331, 2.39334771875876e-05, 0.000121549812379071, -0.000392931150277919, -0.000619299217827459, -0.000294634482496248, -0.000315205497242280, -6.84095375156528e-05, 0.000100967277029383, -0.000108169759382909, -0.000221813205983008, 0.000483938987632886, 0.000225155025178987, -1.10624188985789e-05, -0.000116745564214124, -0.000236859504445025, -0.000389241263960387, -0.000423560862408226, -0.000227868897133449, 2.17951637827651e-05, -0.000299480478077574, -0.000117687083750390, 9.82665684020034e-05, -0.000172230446259089, 0.000124105609520472, 0.000332899462993139, 0.000384605591383181, 0.000388690675042861, 0.000339661839921934, 0.000433537020709192, -0.000135832177771455, -0.000365625266181490, -0.000592311203102113, 0.000187201476613558, -7.58604631849234e-06, -0.000444328914542178, 0.000116759831292323, -0.000592858726268461, -0.000164061145031806, 8.87593467440695e-06, 0.000291410296628641, -5.94546903372764e-05, 0.000308097838323906, 0.000402722000205637, 0.000235337702486655, -0.000495498352060857, -0.000266586500701874, 0.000245247542379392, -0.000658686204034314, -0.000155025480028271, 0.000119099145623001, -0.000100686017409898, -0.000109902040366134, 0.000164842929237791, 2.99218020415830e-05, 1.17363757426200e-05, 0.000212628920244541, -0.000331297840357456, 0.000237190964802347, 0.000316594464202758, 0.000104295027192819, -0.000315627124810859, -0.000279306920096728, -0.000248504301410770, -0.000331808852135409, 0.000113980001485465, -0.000123785925277825, -0.000148317149220008, -0.000916450890377558, 0.000126846009890568, 0.000611943900228573, 0.000279548054098516, -0.000224276969877196, -0.000623423582125007, -0.000562164638475959, -0.000407630107913268, -0.000267707525373722, -0.000172845535563041, -0.000299519581064978, -0.000541404571586348, 1.86618164430642e-05, 0.00103045749745274, 0.000212041630301387, -0.000372728380266513, 6.12670687116622e-05, -2.34537787434536e-05, 0.000331104205218606, -4.81772460656526e-05, -0.000523496135448511, -0.000242888143848394, -0.000622838709665122, -0.000898776562565543, -0.00137259702989029, -0.00137307079987407, -0.00131404930179135, -0.000345950748385574, -0.000152800449584663, 0.000389326834158429, 0.00112966935917388, 4.70387096082964e-05, 0.000263222571007650, 0.000260490233078872, -0.00250978649982251, -0.00630918289134347, -0.00189890367587078, -0.000920369133341848, -5.00980756350972e-05, -0.000297325707281603, -8.54037266424699e-05, 0.000958546457073979, -7.10703793905171e-05, -0.000333967606065326, 0.000288785772319950, -0.000217981350339347, -0.00219037951141600, -0.000898507521745707, -0.00117269896415044, -9.40251971082525e-06, 0.000209375912589717, 3.37412766443869e-05, 8.87238093648824e-05, -0.000156602154080885, -5.47280639307587e-05, 0.000425358443972971, -0.000270858539173678, -0.00103247342103226, -0.000415112460417518, -0.000224815706367574, 2.14146628331016e-05, 0.000169363801348668, 7.23939166707012e-05, -0.000310717601738905, 0.000318458107367920, 0.000149086003440698, 0.000301675377923259, 0.000199850862069518, -0.000190166445931894, -0.000229313521986461, -0.000251477335372418, -0.000161980964960773, 0.000105366337662774, 3.86091612940475e-05, -0.000244631640085949, 5.63590294339612e-05, -0.000114399701499211, 0.000284499914816171, 0.000459157007493682, 0.000390236136588422, 0.000453744806283474, 0.000519748761030346, 0.000586974696273753, -0.000141013240977774, -0.000143796858578138, -0.000595629952838115, 0.000261454736342590, 7.95321252771164e-05, -0.000263037626066001, 0.000417833122987728, -0.000228951164136006, 0.000232029635120824, 0.000220126499675755, 0.000548664083147282, 5.32715156066795e-05, 0.000457082149725672, -0.000335540504261445, -0.000359672359652815, -0.000891008308663704, -0.000388514937705305, 0.000317301929763604, -0.000499621717611567, 8.33239614207045e-05, 0.000345187130254319, -9.28172950398013e-05, -0.000149135802200193, 0.000244813639085741, -0.000400590597160176, -0.000306568479297940, 5.57908810024968e-06, -0.000297004288354672, 0.000276627927969942, 0.000367535557560113, 0.000356838309170413, 6.00151409177395e-05, -0.000113146910713745, -0.000211492613861749, -0.000406180543899156, 0.000136130155369670, -0.000206592645877823, -0.000126478453640293, -0.000666844039607136, 0.000432526120255245, 0.000730999201520730, 0.000359771239491188, -0.000144177648820657, -0.000496869135849699, -0.000387338337377013, -0.000199822217412418, -0.000121928032504385, -0.000161525407885595, -0.000233125689387488, -0.000242105969635182, 0.000585490269483931, 0.00166993323021093, 0.000649077315065938, -0.000206137988769906, 0.000265140102212515, 0.000292139800575298, 0.000611292147063545, 5.30984717301505e-05, -0.000447511431314995, 9.13204145506173e-07, 1.15898805862213e-05, 0.000291468112517772, 0.000327386551829651, 0.000169677437940334, -0.000406163120712409, 2.93194226386174e-05, 0.000201942714035232, 0.000502829727889830, 0.00115428920023830, -2.06718255625595e-05, 0.000383413900214819, 0.000798551032206847, -0.00115989327316883, -0.00420075985854615, 0.000111069484501491, 0.000316626513185868, 0.000394483737381240, -8.13464405915708e-06, 0.000161060618282897, 0.00121567831095765, 0.000164173314825087, -1.26722974347736e-05, 0.000567793598752807, 0.000836789946134824, -0.000414334139246161, 0.000652357537745017, -0.000182587346809037, 0.000428520426978443, 0.000487510169659517, 0.000235112513537210, 0.000170536238885713, -0.000250472059481467, -0.000120319562455700, 0.000358414189444129, -0.000111447653406029, -0.000517599708501139, 4.96457108066954e-05, 0.000157920904417419, 0.000413828644195446, 0.000438587320691734, 0.000163892834843997, -0.000494599296945888, 0.000114323887085873, -0.000198962608268403, -6.12922092802059e-05, 0.000200581006032355, 0.000181630465644656, -9.69155311273415e-07, -5.33844257896099e-05, 3.24990948189914e-05, 6.40264125702092e-05, -0.000233757827852102, -0.000271544791232408, -0.000148197659769677, -0.000461431552401615, -8.29010449684960e-05, 0.000285431966587779, 0.000509744007624267, 0.000411572416612180, 0.000459595838071072, 0.000421301201997222, -0.000425505927709475, -0.000624570888602992, -0.00105282653994172, -0.000117648501107306, -0.000176921541469195, -0.000482262864985997, 0.000223967783084688, -0.000149383978107071, 0.000352179603590715, 0.000206628922854355, 0.000142285380692535, -0.000377650312783360, -3.27556832052178e-05};
			//double cst_blue = 1.79867379517489;
//C=0.00001
//			double weight_blue[363] = {0.000131729319355757, 0.000365403797302592, -0.000191139609077947, -0.000216219371662463, 0.000203828651934534, -0.000137000223094598, 0.000203960293331786, 0.000171829282739681, -0.000228045196818241, -0.000413485025982531, -0.000234858057882099, -5.07034545120661e-05, 0.000216889687846137, 0.000251133303898995, -0.000189042585256662, 0.000484517318510650, 0.000605510336751940, 0.000229813928617180, -0.000149247384881187, 3.06093513484580e-05, -1.21102463815546e-06, -0.000432261293367579, -0.000160137987531257, -0.000105873564258118, -7.82158630002865e-05, -0.000559691476596938, 0.000702546162639578, 0.00125535511973517, 0.000619396406118345, 0.000314852793301735, 2.51278234895998e-05, -0.000153290311659208, -0.000138063681212199, -0.000362385628982316, -2.51856607067740e-05, -5.17997346006488e-05, 6.59872922919035e-06, 0.000958745153033738, 0.00208483518902276, 0.00116662329441928, 0.000212100983925779, 0.000259054235964004, 6.27154505644348e-05, 0.000245930501902654, 6.42343139895076e-05, -0.000423104253942717, -3.13699478433845e-05, 0.000255937769062650, 0.00129981341422476, 0.00139723673140971, 0.00120412087972177, 0.000233744755085155, -8.22274856188944e-05, -0.000101323402181877, 0.000227454603878097, 0.000809896309369289, -0.000123187338298887, 0.000193359799183041, 0.00125847790890751, 0.00104603784265085, -0.000334400672976653, 0.00205521603995766, 0.00117946130980687, 0.000240919915069008, -0.000267285012205038, -8.51909771623451e-05, 0.000677918413501926, -8.80848852948689e-05, -0.000345630940819289, 0.000463733121854187, 0.00184723798783300, 0.00120521996202066, 0.00176587308610889, 0.000283549238475800, 0.000229777910134495, 0.000141326279929696, -7.35145908498173e-05, 2.33423659887231e-05, 0.000237188062941585, -0.000101363353579369, 0.000106323866737991, -0.000120355507790954, -0.000308558054368595, -5.33857743929450e-05, -0.000198398398389986, -0.000103460813559530, 1.27521446933694e-05, -0.000153116804267605, -0.000393259644364799, 0.000282367681554133, 6.14439974569308e-05, -3.82545781855162e-06, 0.000130701610457098, -0.000104063573038682, -0.000463478471360455, -0.000245413376169088, -0.000178782658330260, -2.34852191254003e-05, -0.000267396353145356, -0.000148023804623633, 0.000184814804279570, -0.000236708589964145, -6.66128339363843e-05, 0.000387783547665827, 0.000320025913813618, 0.000223285112568669, 0.000252109428536498, 0.000292757759649332, -0.000135244579407329, -0.000274552806674394, -0.000529264900933721, 0.000183912624103802, 0.000134554976343351, -0.000232611150063425, 0.000106650687001764, -0.000145046484061781, -0.000362693002399709, -0.000128879851846801, 0.000148742455058313, -9.75106734660653e-05, 0.000209039359720438, 0.000193961441229238, 0.000269739515687315, -0.000426777378381823, -0.000372241639264220, 0.000113570803521039, -0.000370050903080144, -3.59315512520616e-05, 8.78682748335098e-05, -0.000165123153516204, -0.000295083190821669, -0.000118290212788482, -5.80906113339227e-05, 0.000102585071033378, 5.48541449818007e-05, -0.000427628628620019, 0.000218121858298860, 0.000345318574438179, -3.38073984601660e-05, -0.000513228951996693, -0.000257635890591302, -5.35876101491062e-05, -0.000266637375036779, 8.97626895990301e-05, -9.14922426511888e-05, -0.000212042467615956, -0.000851696997532387, 0.000171139699024167, 0.000860836883113793, 0.000378518990644731, -0.000124892731133925, -0.000376470936578707, -0.000364708304117648, -0.000183421953111381, -0.000317499589417065, -0.000100963668858731, -0.000161202323636434, -0.000469220752586078, -1.26355776246350e-05, 0.000959005942978699, 0.000333557448552829, -0.000237765021399310, 3.30968348231542e-05, -5.77114593775599e-05, 0.000257966010598822, -7.72388251208127e-06, -0.000553883324877780, -0.000272857945860090, -0.000635162758807421, -0.000929270808584999, -0.00183892946010677, -0.00145915835813475, -0.00106482465091364, -0.000368324684489528, -0.000269046428943568, 0.000322293306592286, 0.000851841833518358, 0.000102735690535595, 0.000120211566136109, 0.000142493460919536, -0.00241342365013577, -0.00535988092061937, -0.00215787461547743, -0.000726244607827395, -0.000141174243393621, -0.000353427398715771, 8.73798333666779e-05, 0.000803601563035730, 0.000148732350401216, -0.000260950710245776, 0.000129735589094017, -0.000250069630041095, -0.00241024125218570, -0.00100105880779361, -0.000971712161904112, -9.24999528730386e-05, 0.000192348227458300, 0.000181882291991074, -3.10292181336251e-05, 0.000208107813275524, -0.000147195314844169, 0.000241822203365013, -0.000176557568993672, -0.000738604547395403, -0.000259914592464811, -0.000207019614823719, -6.38116246769730e-05, 7.02824436467639e-05, 5.21589302768375e-05, -0.000305396261425342, 0.000246457177927671, -3.09447838281277e-05, 0.000109716939439186, 0.000224818603429177, -0.000163080906936688, -0.000367002967855042, -0.000143087477512703, -0.000151926806630566, 5.83320163240135e-05, 5.21006102860470e-05, -9.43696782842329e-05, 0.000271171152416787, -0.000171460857689751, -6.67861107683470e-06, 0.000445863834476666, 0.000365640901508045, 0.000419806206760747, 0.000524592345270073, 0.000523264828312679, -0.000112155222991137, -7.70794237507888e-05, -0.000483474752957350, 0.000341755289588728, 0.000258840031867868, -9.25562533197294e-05, 0.000339942601665129, 0.000165485354079119, 5.86936541679788e-05, 0.000208386331383003, 0.000462511255880904, 7.16209782019089e-05, 0.000393717149689678, -0.000259377596377546, -9.66732679277410e-05, -0.000654279799616999, -0.000393425274415952, 0.000194493099390939, -0.000275365136502876, 9.79292282178966e-05, 0.000254613630468976, -9.14907699263139e-05, -0.000219700936699574, 6.23481493631570e-05, -0.000289529068064432, -7.26462922504598e-05, -6.61192391670631e-05, -0.000342437936970036, 0.000377194512686495, 0.000437288763734423, 0.000184427433588318, -0.000179821202896637, -0.000104854582692957, -4.57815474603360e-05, -0.000350113615789761, 0.000191684214832851, -0.000127289362737911, -0.000171880822149701, -0.000619565412368141, 0.000469798238987696, 0.000967318058549748, 0.000410022744720681, -9.00096385342334e-05, -0.000321778702296964, -0.000321749440279358, -0.000165792327942860, -9.44728427326699e-05, -8.96963761461795e-05, -0.000210710326382990, -0.000240994880258541, 0.000574298580148910, 0.00161378119795147, 0.000755162686675315, -0.000112714580928404, 0.000160643362328604, 0.000114852409448238, 0.000351456108847656, 7.32637994803547e-05, -0.000587137559111911, -0.000237536391942636, -6.40937278480580e-05, 0.000384839418346406, -2.30404604489076e-05, 0.000202570683262627, -0.000160761889554379, -2.97163140879285e-05, 9.53141316121348e-06, 0.000386264249060799, 0.000895363975752327, 6.22926204415848e-05, 0.000197638757775291, 0.000775797261572820, -0.000903371555088996, -0.00316210224884815, -7.24547850152251e-05, 0.000510969465968979, 0.000350189700873281, -3.46226337392851e-05, 0.000356207630181047, 0.000943849212602310, 0.000275185816479961, -0.000113704267689162, 0.000402864976489604, 0.000887950579797244, -0.000626074586815306, 0.000538731869372729, -4.89246087503406e-05, 0.000306903594980234, 0.000441799966305630, 0.000351082696348675, -6.61103469162022e-05, 9.13710562213475e-06, -0.000296018303042842, 0.000187943988603440, 4.35329512975598e-05, -0.000243730857452980, 0.000177141498637822, 0.000164423015208226, 0.000284605281160336, 0.000277022362587591, 5.84987992672718e-05, -0.000540572039610450, 4.13682658496292e-05, -0.000322808587520364, -0.000173917518618149, 0.000226094520060809, 9.82777239793615e-05, -0.000267114321915683, -5.13167189090436e-05, -2.74304107122583e-05, -1.22170022932532e-05, -0.000231475938519665, -0.000225562150630729, 5.71259103536932e-05, -0.000520025550997911, -0.000347827784757915, 0.000290694256683659, 0.000375203204727502, 0.000212435072592092, 0.000348350608156895, 0.000321089989619893, -0.000346588973368686, -0.000503715682248939, -0.00100140450379986, -0.000216751911167203, -0.000244778104385251, -0.000496766134361149, 0.000110206128713389, 0.000245711189867686, 0.000174639445516378, 0.000195736677944742, 0.000135005253193506, -0.000290090401780758, -2.26125276110356e-05};
			//double cst_blue = 1.80092386876473;

//bjr
//			double weight_blue[108] = {-1.259555e-01, -3.576883e-01, 3.765126e-01, -5.735204e-02, -3.991855e-02, 1.006583e+00, 7.221417e-02, 9.443009e-01, -1.170632e+00, -4.566323e-02, -1.678598e-01, -1.471750e+00, -8.231599e-01, 1.236707e+00, -1.361339e+00, 9.470368e-01, -2.139101e-01, 4.618806e-01, 1.469955e+00, -1.346546e+00, 6.303125e-01, -1.701969e+00, -9.320652e-02, 8.344490e-01, -2.053983e+00, 2.832865e+00, -1.284864e+00, -9.410324e-01, 1.191636e+00, -1.214212e+00, 1.188675e+00, -2.502310e+00, 1.119172e+00, 1.407336e+00, -7.147919e-01, 1.511471e-01, -6.379193e-01, 1.947935e+00, -1.688920e+00, 7.074906e-01, -9.973900e-01, -1.634822e-02, 9.025669e-01, -9.751131e-01, 8.155089e-01, -6.136274e-01, 1.129325e+00, 2.421497e-01, 9.756170e-02, -1.089514e+00, 1.762804e+00, -2.515374e-02, -4.091551e-01, 4.736012e-01, -2.424181e-01, 3.555613e-01, 3.637418e-02, 2.728281e+00, -1.330473e+00, -3.932526e-01, 2.028573e-01, -1.375532e+00, 1.328107e+00, -3.429255e-01, 5.738505e-01, 5.757475e-01, -5.333884e-01, 1.551925e+00, -1.504108e+00, -4.220112e-01, -1.314587e-01, -2.239479e-01, 9.030597e-01, -1.618707e+00, 1.104638e+00, -8.730597e-01, 1.173057e+00, -8.370146e-01, -1.156816e+00, 6.998394e-01, 5.534701e-03, -1.619587e-01, -5.215818e-01, 1.161789e+00, 5.720431e-01, -2.439099e-01, -4.246291e-01, 6.736029e-01, 3.658777e-02, -1.365829e+00, -9.723158e-01, 3.476677e-01, 6.231549e-02, -1.729610e+00, 1.459556e+00, 9.589262e-02, 1.668364e+00, -1.016849e+00, -5.426158e-01, 1.628069e+00, -1.764692e+00, 5.145290e-01, -6.915735e-01, 7.407629e-01, 7.060746e-01, -9.017956e-01, 6.721856e-01, -7.734824e-02};
//			double cst_blue = 3.285981e+02;


//			double weight_blue[108] = {-0.00698163234977934410, -0.02846720221740678400, -0.02831302473145970100, 0.10588507508357861000, -0.10732937358796024000, 0.14161842592315402000, -0.11166433192456446000, 0.12834706826298214000, -0.21356620517169203000, 0.15376108872796460000, -0.11875967977156186000, 0.12024486639925901000, -0.01564110255423810400, -0.00105314907981800310, 0.01172318078915966300, 0.12266656619803137000, -0.20660401810458182000, 0.13323075043229163000, 0.05428828660477573500, 0.00362849210388635790, -0.07007807475228766700, 0.11191945884796774000, -0.12305539869328011000, -0.04566695096284059700, 0.03820822425287261100, -0.05571989812688970400, 0.07251907145504361800, -0.08489777558962369200, 0.05232328765031994700, -0.01231005023755456700, -0.04966217022424603000, 0.08574331077225610900, 0.00726236877919636020, 0.07900486631550508700, -0.08200926558071426600, 0.15967610443706634000, -0.21546940613867341000, -0.10441968287000496000, 0.06078304733735384600, -0.00109815009266214030, -0.28934167613420492000, 0.37888439611165603000, -0.07344962440696936600, -0.11931585134368664000, -0.00221468131993966030, 0.19016349772799249000, -0.14091692868073649000, -0.00268317524468907400, 0.04747334199218243600, 0.04277323586190210500, 0.09348138201033132100, -0.08813357893116366400, 0.12474881633843583000, -0.13592467508855127000, 0.08195890305780473300, -0.08531825366919608400, 0.06816026155769899800, -0.19451367435345837000, 0.13706935813582846000, -0.02327031992774816400, -0.03637196480999208700, 0.07498322672127300000, 0.12172430842456625000, -0.13008634209236716000, 0.06178524994006396500, 0.16671523833325977000, -0.14875130519901641000, -0.07751714571186119100, 0.08804337963330997900, -0.01645345793272968300, -0.11126254652591837000, -0.01727374426915541000, 0.16178856515675724000, -0.08335397334033491100, -0.01991703804016259700};
//			double cst_blue = -9.87830098482081100000;

			//gooood
//			double weight_blue[363] = {0.000359885621909795, 0.000335384083341025, -0.00120918202124540, -0.000412191342436629, 0.000262421572771093, -0.000625292861812576, 0.000658289256044181, -0.000202903914336939, -5.73957798438742e-05, -0.000137268944804616, -0.00149796653458915, 0.000508092692512186, -4.13088559407704e-05, 0.000116915151898484, -0.00103273186196581, 0.000683482917380885, 0.000392606156201663, 0.000527224274259692, -7.55112294944268e-05, 0.000684032786812050, 7.41316950212912e-05, -0.00178373159446168, -0.00102764482626940, 0.000622189314949944, 0.000396699834023786, -0.00102587840641432, 0.00235285344434465, 0.00174930150278705, 0.00103212054607864, 0.000670918338323361, 5.41399585815242e-05, -0.000431937623335271, -0.000877040908962229, -0.00100802983342738, -0.000420540460553675, -3.47079384484706e-05, -1.92692415044960e-05, 0.000806264444680072, 0.00128693322176523, 0.00131386161312508, 0.000393050748400490, 0.000283868560579107, 0.000408971389193115, 0.00109794651418581, 0.00101378848376601, 0.000122056367733474, 2.60703763342810e-05, -0.000293711298926645, 0.00117765663094027, 0.00291189591102490, 0.000916955144359089, 0.00147398241146047, 0.000681583342304242, -2.58020913422332e-05, 0.000782990058052020, 0.000407486481343536, -0.00213475835051605, 0.000146007007147707, 0.00105045919754968, 0.00442865478801434, -0.00102638140659241, 0.00533089562111850, 0.00179689024507816, -0.000557296602395707, -0.000589181590820913, -0.000549185887037553, 0.000192717270363190, -0.00199599599391072, -0.000757733305344099, 0.000204499889024155, 0.00285946633899029, 0.00424972281106717, 0.00458823298677584, 0.00142736405830514, 9.41762161812587e-05, 0.000563549277685543, 1.84539543283697e-06, 7.27183008721478e-05, 0.000522652252562960, 8.00860700648875e-05, -4.54790328209363e-05, -0.000171006845353120, 0.00109440228875966, 0.000549856020682373, 0.000349586966629586, 0.000715933617075095, 0.000733777313564374, 0.000252592990012234, -0.000631822426823035, 0.000736257594632908, 2.09828562333818e-05, -0.000810704680749891, -0.000591459653498786, -0.000709088553352855, -0.00110539979933965, -0.000758551146071462, -0.000260893472183621, -8.53293676583782e-05, -8.17392371337676e-05, -0.00106017656848992, 6.39152843335059e-06, -0.000341411628265776, 0.00101363518552641, 0.000177822399745175, 0.000201205136783923, -0.000324093872521965, -0.000240020099669534, 0.000414141567842380, 0.000268209595881532, -8.29189291607863e-05, -0.000961657790860754, 0.000647568023418169, 0.000717018605880880, 0.000290829864084639, 0.000103835251802783, -0.00203003636001452, -0.000681423734510253, -0.000489716669260178, -0.000834939188208054, -0.000927354309622176, -0.000712659886902091, 0.00174801611825390, 0.000968349789859599, -0.00137600124131210, -0.000614725163256462, -6.10417140887751e-05, -0.00181331956580608, -0.000384593616208003, -0.000163996417538404, 0.000444923693340918, 0.000602640843377472, 0.000699900775754953, 0.00147979404909797, 0.000731246938771423, 0.000522492656107031, -0.000806094133124196, 0.000636369576057873, -5.11527392011904e-05, -0.000138811524040543, -0.000808483134362622, -0.000368454126624300, -6.68918412250975e-05, -0.000350658967149799, -0.000507235520789032, 0.000983002927765816, 0.000840498882593685, -0.000790333191181829, 0.00201836305683254, 0.00153831416083499, 0.000355277626523590, -0.000488345736134631, -0.000867381423332192, -0.00117355620998158, -0.00159545528155790, -0.00106833003602547, -0.000854991295995876, -0.000404660931242536, -0.000680362864959296, -0.000580085668862058, -0.000123624430593805, 0.000453945380933308, 0.000201674865376678, 0.000121825593987997, -0.000197897744683327, 0.000523615599134999, 0.000890766695483373, -0.000237470683959399, -0.000393957608268113, -0.00154339273513156, -0.00276465520489175, -0.00244972796656270, -0.00296487502631328, 2.41344856265013e-05, 0.000406854425867227, 0.000350049310785210, 0.000869766205431032, 0.000702601335574486, -0.000909246011251159, 0.000888150316626988, 7.34566809469613e-05, -0.00173076080747052, -0.0101260397645680, -0.00214978877081752, -0.00192038541459417, -0.00119444931255075, -0.000652507296867388, -0.000906687689877789, 0.000817775617030233, -0.000783997324299569, 0.000320626242659873, 0.000646595431086196, -0.00139069623719213, -0.00497461261173007, -0.00319580716184123, -0.00192318501353935, -0.000733974775465469, -0.000155368306265424, -0.000980963350985130, 0.000118410239421704, 0.000567371013083932, -0.000229968171076024, 0.000306595399029284, 2.70734799100007e-05, -0.000361492032397472, -0.000620403999434588, 0.000897535562665045, 0.00130173294783030, 0.000634113443041823, 0.000117367424182351, -0.000241749505435765, 0.000940775237021127, 3.88917100552836e-05, -0.000485374986385151, -0.000135427309752000, -0.00130826578980820, -0.00159639121429348, 0.000294106015750187, 0.000605168045373303, 0.000365033619741771, 0.00107042377107743, -0.000351469526933092, 0.000640080925945259, -2.91308044698525e-05, 0.00152443447909992, 0.000751109236813737, 0.000133336045767782, -0.000430179841451752, 0.00100403781844103, 0.00128922709734823, 0.000870160251614726, 0.00153989686344967, 0.000399440219258333, 0.00133040869084014, 0.000682864507602636, 0.000531779062685852, 0.00121546830535623, -0.000942446115053845, 2.13760774269009e-05, 0.000200127842522438, 0.000304803884399695, 6.74512377961743e-05, 0.00123118646657797, -0.000707195605940815, -0.00122161820417072, -0.00237881387776452, -0.000207882235290243, 0.000768239146736921, -0.000491369524589957, 0.000779727679385106, 0.000645056202826725, 0.000632911402329583, 0.000570136865924246, -0.000979228744573077, -6.99154530970174e-05, -0.000994431327182732, -0.000602904678169354, -0.00106207167550284, 0.000823379675411981, 0.000385571776287771, 0.000776880000675547, 6.87458116397104e-05, 0.000431711788277687, -0.000613190752636377, -0.00184854603453323, -0.000586027402207258, 0.000470027525529644, -0.000194965328886505, -0.00166498580523167, 0.00200427628520396, 0.00179337780804044, 0.00121404790091357, -0.000363765657095063, -0.00205790873067747, -0.00140257940973952, 6.13378040362385e-05, -0.000339294062896270, -0.000261925644177701, -0.000346385703672583, -0.000263770181548183, 0.00110986509917578, 0.00139813166211353, 0.00105942152356995, -0.00114857451559355, -0.000768798629465243, 0.000811829683229141, 0.00163209221296236, 0.00121345020952502, -0.000101672880899459, 0.000223772108171938, 0.000460945251996380, 0.00168278018565771, 0.00143729930084057, -0.000940028660280691, 5.75542681444034e-05, 0.000419809397362431, 0.000248925639242448, 0.000762902093449063, 0.000680101490782832, -0.000896271165431173, 0.00128859862093204, 0.000691727305802791, 0.00138827665953340, -0.00567427345298586, 0.00176076587232946, -7.15515467461750e-05, -0.00117157589771398, -0.000378687440235544, 2.56658566558411e-05, 0.00147432563168394, 0.000149378393058154, 0.00103715497000698, 0.000416411461097481, 0.000141825203439444, -0.00134530776853309, 0.000841681293244248, -0.000380428689297184, -0.000677203702098583, 0.000626181753764309, 4.97795073789908e-05, -0.000217453799722364, 0.000469020584090203, -0.000487281028634299, -0.000268004407434079, -0.000160148717267143, 0.000616507231355166, 0.00100230463562697, 0.000657433816265970, 0.000383573045999714, 0.000473038710145714, -0.000209963423739030, -0.000501274976087335, 0.000206384013035451, -0.00145455730781604, -0.00110813980283029, 1.05981383291803e-06, 5.92971786227489e-05, -0.000186372694220149, 0.000276126913543486, -0.000474904476072985, -0.000340256487631009, 0.000234486330124884, -0.00134620208298859, -0.000716748980527893, -0.000738840377878546, 0.00110086407712951, 0.000697474774578351, 0.000945470701519695, 0.000297900695134767, 0.000865299787464654, 0.000903298193037219, -0.000452866133324702, -0.000242592694870133, -0.00172741068504122, 0.000358401137645814, 0.000277363224436862, -0.000447835675656222, -0.000656186393202642, -0.00198550361455554, 0.000335333829832442, 6.89779752016534e-05, -0.000415394033003688, -0.000384436664926656, -0.000212630852640010};
//			double cst_blue = 3.25639293718492;



			// red1 1000neg
			//double weight_blue[363] = {0.000192124319931933, 0.00296305997167245, 0.00151539958614526, 0.000263295243114580, 0.00104023113712570, 0.00194245444399212, -0.00117349398666299, -0.000467768997090743, 0.00302086172191533, 0.00246295389844813, -0.00418219266921603, -0.000305781599299959, 0.00266052712952348, 0.00203112833696767, 0.000913316680666023, -0.000301550255025540, -0.00135735954534032, -0.00140846712241285, -0.00346953138003068, -0.000787679664212664, 0.000716909067495885, -0.000897899168488953, 0.00296218510229879, 0.00154517103676293, -0.00274297591578590, -0.000527525015061967, 0.000127177372592568, -0.00285186460647450, -0.00112699464238251, -0.00241125362406594, 0.00189235280519690, -0.000105796580293245, -0.000617604742901218, 0.00472319523246166, 0.00372803606683115, 0.000162061371468396, 5.72267686778645e-05, 0.00118498396065944, -0.00405831414905806, 0.000737866088717331, 0.00131577768639583, -0.000929422181367079, -0.00170187724245117, 0.00220238021536811, 0.00122280393047417, 0.000101219524472067, -0.000432328878966668, 0.00193508982423494, -0.00166875415234498, -0.00216202906585551, -0.000743138012843942, 0.00183221063338338, 0.000457495721447038, 0.00325547257159278, 0.00664813106225430, 0.00309339228239219, -0.00294704952031373, -0.00128826405668372, -0.000313151479884181, -0.00860616259945571, -0.00852599912776656, -0.00740628039574026, -0.00244224538988546, 0.00300869261834464, 0.00496201689895704, 0.00340003921354084, 0.00464489841590137, 0.000145303176043923, 0.000150160959197976, 0.00210678576247811, -0.00477567175499867, -0.00767223342657851, -0.00179965640551708, 0.000236064082984886, -0.000660764684108522, -0.000878693320065337, 0.000226650456267337, 0.00132160828398526, -0.00181967263446165, -0.00421399796500766, 0.00260719000768012, -0.000131936252892187, 0.00146098047298470, 0.00229899976744837, -0.00218178454097139, 0.00185378925092756, -0.000830316153264579, 0.000876161935415802, 0.00301366491113728, 0.00145483586867082, -0.00205293826433801, -0.00318087620113890, 0.000450941405192792, 0.00469396693594308, 0.00309627275927227, -0.00125561184771059, -0.000247342386633066, -0.000773156747233007, 0.00383854274356874, 0.000739541150322625, 0.00153212111169548, -0.00426191027106734, -0.00509353022707921, -0.00332328537247709, -0.00487953806069610, -0.00521861657711288, -0.00276530558238319, -0.000134284754136373, 0.00108738193761432, 0.00584857562885331, -0.000400583729281424, -0.000351902256811796, -0.000268596431894114, 0.00240002117563257, 0.00459771202889989, 0.000639415144988244, -0.00242467531090429, -0.00222107500895419, 0.000597485760150800, -0.00146980202609505, 0.000186974231199268, -0.00243177287969577, 0.000644201723642874, -0.000645956780358701, -0.00191540545683210, -0.00121913119212674, 0.00157891092167693, -0.000465288835799443, -0.000705815100702779, 0.00238265518724761, 0.00180801081911292, -0.00326993811826848, -0.00349700563743585, 0.00115344304677630, 0.00101127312107361, 5.14363181087784e-05, -0.00198387785371128, -0.00121779706644806, 7.23283422503019e-05, -0.00354403161709694, -0.00172761617658052, 0.000448811343159689, -0.00145839995219969, 0.000982364610546752, 0.00122453374667749, -0.00165595448167334, 0.00188622857125249, 0.00328841592040947, 4.73416702499885e-05, 0.000986159608376481, -0.000435598033438406, 0.00337887726089462, -0.000308973171304623, -0.00349520274096414, -0.000338550564593119, 8.32447423730169e-05, -0.00263082562330325, -0.00219096296984192, 0.00209177352479985, -0.00178890815511716, 0.000743499902768806, -0.000841101248876487, 0.000443953764102774, -0.00121707162379360, -0.00225235827045024, -0.00413315340190812, -0.000368520755431449, -0.000442130526165383, -0.000550036202992565, -0.000585098256827144, 0.00364686787158084, 0.00285174016916648, -0.000271994980506766, 0.000215527729736621, 0.000909711598020389, 0.00112559876506019, 0.000119714480447876, -0.00115516324172232, 0.00142377911384902, 0.00227437123988498, 0.000821367443619190, 0.000443794729095019, -0.00123275147271531, -0.00290321116270856, 0.00299680798038737, 0.00154192727078791, -0.00268377141376020, 0.00121394504489639, 0.000905910995814013, 0.00183657904879550, 0.00340170695670893, 0.00254853651583998, 0.000922587132077039, 0.00268151920158300, -0.00310763116489447, 0.000674329836974916, 0.00139767694296179, -0.00107445702689915, -0.000285701345403589, -0.000357773647266801, -0.00143593386796550, 0.00266415429137468, -0.000582162830881044, 0.00161479678288367, 0.00322477610205450, -0.00245403919906707, 0.000917566482732543, 0.000701188730806998, -0.00135406743104933, 0.000787226625814234, 0.000865713491493814, -0.000183718922331774, 0.000137760730053294, 0.00205422482591194, 0.00596152235559134, 0.00506763885258652, -0.000333683576213839, -0.000542509474656523, -0.00156394999472671, 0.00129252372809154, -0.000636447664153608, -0.000387454911250140, -0.00340847225658994, -0.00138882680164767, 0.00124124292203592, 0.000165802290199027, -4.53065389312032e-05, 0.000232483723193197, 0.00161361703918330, -0.000675143520398632, -0.00105547119573808, 0.000106888500229145, -0.00171509317485595, -0.000749931038355275, 0.00148385666455220, 0.00228944872162389, -0.00161904346100664, -0.00133706007722704, 0.00112236797759175, 0.00495736857329714, 0.00128807674330935, -0.00133566065776931, -0.00165357011792224, -0.000215821578882898, -0.00165176909032921, -0.00147172822801447, -0.000139159910069228, 0.00256879679217476, 0.000394134389976274, 0.000206664619843771, 0.00345574949495586, 0.00121222505750869, -0.00521346542698224, -0.00444175886663060, -0.000981122668352508, -8.39054310266937e-05, -5.98900477991370e-05, -0.00138500720235055, -0.000441835400114959, 0.00153888728391700, -0.00117000123330785, 0.000784856647509014, -0.000179721467442475, -0.00211645775824240, -0.000409370545796313, 0.000980907841640747, -0.000369400624117993, 0.00279944265744282, 0.00418544428447085, -6.27026741860776e-05, 0.00120876143963207, 0.00155264637961577, 0.00502404700452262, 0.00135499158115977, -0.000556596752770516, 0.000348087073318475, 0.00203312517499571, 0.000788247828039207, -0.000491506167929367, 0.00159778962419078, -0.00250134909111746, 0.00107430320602405, 5.39424342792188e-05, -0.000404967315648847, -0.00133432569822622, -0.000846856438236954, -0.00210547641178508, 0.00120625846461338, 0.00115463457072073, -0.000200185793620074, -0.000695896629166295, 0.00203274334044524, 0.00209802911089531, 0.000492185709449926, -0.00157538020063181, -0.000669232048151149, 0.000298118921017847, 0.00189947702856172, 0.00118849367539779, 0.00130828934493647, 0.00117393278502430, 0.00147522803998887, 0.00257190429243009, 0.000804866286730777, 0.000768035520282209, 0.00299149139384197, 0.00158025367428330, -0.00187384254239465, 0.00302259959244343, 0.00153573834931043, -0.000598002294662196, -0.000841822582962105, -0.000966743588548031, -0.00196872006365159, 0.00209604579612979, -0.000897210430468003, 0.000500498436264925, 0.000678612828301774, -0.00169361474045856, 0.00112282596457447, 0.00150286125499061, -0.00215649833903047, -0.000692784054753309, -0.00433059900704520, -0.00271630380593218, 0.000781657300699131, -0.00305499121681533, 0.00117135857518791, -0.000143952531607371, -0.00290310564355096, 0.00136731112645495, 0.00183285025445515, 0.00117489433035568, -0.000801284229112842, -0.000174384019974312, 0.00236514894107244, 0.00214302015298818, -0.00357348610161220, -0.00272663681489150, -0.00377397266726848, -0.00241198513130109, 0.000519722315004036, 0.000439424046538448, -0.00202236832713075, -0.00171904950731462, -0.000118788089383808, -0.00244321384472450, -0.00220659723627455, -0.00188503510830602, -0.00102370867677932, -0.00403562593291752, -0.00462171401961357, 0.000197282483567915, -0.00115141902295582, -7.24146991451227e-05, 0.00157378944184346, 0.00233630028452965, -0.00106546836564644, -0.000434585742603081, 0.00328298721767461, 0.00668508594325856, 0.00211309564002712, -0.000904596905604481};
			//double cst_blue = 5.04557772608486;

			// red2 2000neg
//			double weight_blue[363] = {-0.000694061266089703, 0.00235515167629719, 0.000826977144236271, 0.000335036866890869, 0.000241582184289082, 0.00245803531425226, -0.000875033181056011, 0.000793414641562939, 0.00327099432690078, 0.00224412949284763, -0.00482620271217393, -0.000740954909702894, 0.00330944257989322, 0.00166022499607189, 0.000803206298651661, -0.000395501310091459, -0.000599378158302434, -0.00164974617789285, -0.00382820792326725, -0.00112010610281569, 0.000732472603550904, -0.000765953020828706, 0.00260711292953650, 0.00191209432948708, -0.00171640708851528, -5.57859429115193e-05, 0.000352366673605290, -0.00247253168859221, -0.000151465086223030, -0.00286466880867607, 0.00141523739368204, 0.00115500405232240, 0.000775135837492574, 0.00595794478345057, 0.00542628421548808, 0.000408998464126014, -0.00149505539637951, -0.00207372559914576, -0.00445331602899053, 0.00223498603564155, 0.00158412816583452, -0.00100895266385534, -0.00173582184142891, 0.00281357587620458, 0.00288389474605325, 0.00123953492084047, -0.000566064012347505, 0.00377394189872351, -0.00173018464837791, -0.000946527351674846, 0.000143214211743148, 0.000610233405487061, 0.000197042905157289, 0.00238993553777106, 0.00460762055983049, 0.00235199007145176, -0.00381614268849822, -0.00173688661855886, 0.00248599666326466, -0.0105257251451084, -0.0100363712165734, -0.00586305803389270, -0.00292026907911430, 0.00308932464102653, 0.00549542194329456, 0.00434083488615211, 0.00313057277683852, -0.00158509736566226, -0.00162907376557822, 0.00296764095920024, -0.00663699994407761, -0.00779817955574418, 0.000318107633382993, 3.46159585766764e-05, -0.000603679628262591, -0.00133742546307837, 0.000852162430583924, 0.00143617925704551, -0.00181005248856785, -0.00475884675735169, 0.00335345428441097, 0.000366451892367899, 0.00314817306321798, 0.00242261419823663, -0.00294743573479518, 0.00158842048175239, -0.00182684513039570, 0.000994133588051971, 0.00352155788639880, 0.00190925749450420, -0.00190501879715288, -0.00342761173003754, -0.000627853958498472, 0.00481894820979250, 0.00291962414505167, -0.00126768550119923, -0.000631748088361823, -0.00153479065244987, 0.00340518144201878, 0.000307815315518079, 0.00200578958374899, -0.00421993710379792, -0.00461919628198867, -0.00344851533681502, -0.00519225228903276, -0.00570037507274910, -0.00273406004836090, 0.000433328772962062, 0.00161106927260232, 0.00645645896927259, 0.000901365660094941, 7.10715453056598e-05, -0.000632772465628866, 0.00192660961272320, 0.00332319768686217, -0.000111722019920567, -0.00351673072176031, -0.00333397137741018, 0.000961867413014194, -1.35442945903503e-05, 0.00237311108915869, -0.00227389523480975, 0.000592124974472795, -0.000921773255537146, -0.00162351232933106, -0.00235721664564314, 0.00154163990784631, -0.000812642159795316, 0.000238548285606454, 0.00260690206396308, 0.00171957727939248, -0.00284040635183813, -0.00375776114637438, 0.00164253530830338, 0.000879080150713967, 0.000101671366976627, -0.00241675106819875, -0.000806355655024369, -0.000524001799573070, -0.00360372459004971, -0.00205877980904294, 0.000952640601300812, -0.000507550491716303, -0.000475020155095453, 0.000629153591181971, -0.00163617074018004, 0.00194125801303712, 0.00356131237314694, -0.000562853853810169, 0.000791229842046891, -0.00101975024683591, 0.00235200244905321, -0.000239973438576588, -0.00284523937038830, -0.00119142525447582, 0.000787471639000262, -0.00297047121630924, -0.00226007674565605, 0.00161447893943644, -0.00177677398251658, 0.000516611935050848, -0.000774957222624198, 0.000924203927831494, -0.00209337995283550, -0.00235172618311810, -0.00418701919566082, 0.000744850282524906, -0.00101317469614844, 0.000364661021238676, -0.000505185326386531, 0.00537461030727424, 0.00223689241860482, -0.00119370556886202, 0.00202253323157424, 1.49953330013262e-05, -0.000771394247702658, -0.00147941751049864, -0.00215757295109335, 0.000565707599670180, 0.00437647266033780, 0.00222169154787023, 0.00266684607354946, -0.000717676848047617, -0.00429558983515088, 0.00527627823594976, 0.00303625011896924, -0.00133505026063813, 0.00141744303518148, 0.000885997279534810, 0.000872250566979249, 0.00450415241062892, 0.00204944111950199, 0.000417149407946012, 0.00224680756900637, -0.00454654834445310, 0.00114589507847946, 0.00149972399727697, -0.000809254055278470, -2.83520706407733e-05, -0.000297256629272993, -0.00210702819157808, 0.00317420198930759, -0.000561891095073348, 0.00117372604011948, 0.00263638207424823, -0.00261945063542532, 0.000619748457829119, 0.000169190924822971, -0.00231352313022941, -2.43180239050214e-05, 0.000202416967493745, 0.000113349264245897, 0.00113673567055308, 0.00221820196139058, 0.00545229440710568, 0.00483032691160000, 0.000487055646711465, -0.000767792670029372, -0.00255821054310383, 0.000245193055862156, -0.00161735677118606, -0.000541840342305182, -0.00372714903420100, -0.000552970093679510, 0.00205690212723606, 0.00166734780623232, -0.000209292812239371, 0.000550721130367172, 0.00247251089725057, -0.000830566264645993, -0.00137192065502355, 0.000328822992108171, -0.00160161495743065, -0.000819258126054493, 0.00149792733050796, 0.00181860726808633, -0.000455448738390128, -0.000323080955896714, 0.000790625223795380, 0.00561216185958444, 0.00169514295142225, -0.000602120883571772, -0.00111573109078339, -0.000188994760856579, -0.00206455371656932, -0.00167050899348888, -0.00153185480553029, 0.00239290918177581, -0.000678256254529446, -3.34138421381660e-05, 0.00259964767171663, 0.000712232597427850, -0.00531134494719728, -0.00435467063436425, -0.000243851092596878, -0.000151144485540606, 0.000131515944235141, -0.00130210141099304, 0.000858224953252697, 0.00138530769920607, -0.00107273354966010, 0.000568004728249814, -0.000668191166747486, -0.00206748784475942, -0.000714932311208369, 0.00106919857765640, 5.27063026898493e-06, 0.00343077490702403, 0.00553344046615310, 0.000391764743781779, 0.00120591704572758, 0.000936300793560394, 0.00392408779259613, 0.00142733358863542, -0.000437335281968630, 0.000175858480265929, 0.00278098722772022, 9.19435771740830e-05, -0.000689388871363670, 0.00152381176760925, -0.00243339455159614, 0.000530551449983924, -0.000224418517608693, -2.88433384560678e-05, -0.00283656584248027, -0.00175016644578407, -0.00221486299064579, 0.00155180208111035, 0.000315282713865613, 0.00118904965370833, -0.000560270138972069, 0.00241501352784927, 0.000597075251888072, -0.000121687089950249, 0.000861858284908531, -0.00153568582864314, -0.00208153227413723, 0.000538614558057228, 5.65366669749948e-05, 0.000505903001444004, 0.00339393820331759, 0.00171012713588276, 0.00218579793769315, -0.000110583562309868, -0.000880062252988326, 0.00517986657617412, 0.00285757971379930, -0.000753640321844567, 0.00400977862720003, 0.00175080164937334, -0.00106828128488074, 0.000627007091723341, -0.00105018952095797, -0.00165461688045241, 0.00245098686730970, -0.00141265904526654, 0.00189658225475182, 0.00123312656354517, -0.000490135534527755, 0.00165866382006341, 0.00179846797298652, -0.00260853237866686, -0.000551069553749508, -0.00412326824685688, -0.00248989568156123, 0.000297149100832832, -0.00287958725199865, 0.00287207625060831, 0.000710869480457258, -0.00241811705521984, 0.00107445896908396, 0.00171217664430666, 0.00125656657973996, -0.000607482876374346, -0.000995183962183915, 0.00160097039236802, 0.00161164428017391, -0.00333904272753222, -0.00290204556827087, -0.00385752390746197, -0.00290992616201554, -0.000762287153366614, 0.000189606656955403, -0.00256389051178264, -0.00158873362113637, -0.000241872696799289, -0.00217760899815881, -0.00227661791350551, -0.00206685728394758, -0.00120455548828630, -0.00418585944876483, -0.00454952986637336, 0.000947881371343410, -0.000441707880255321, 8.67594419181614e-05, 0.00143537118625089, 0.00158531134216952, -0.000908248907755662, 2.28381322289191e-05, 0.00315926813354299, 0.00690534673750808, 0.00238626728285960, -3.81475994986934e-05};
//			double cst_blue = 4.77280971794109;


			double weight_blue[363] = {-0.000439546563884277, 0.00240231817076761, 0.000611746423344984, 0.000352012154496163, 6.81525024494251e-05, 0.00215273638201517, -0.00111528817684984, 0.000664386218395629, 0.00314470040510058, 0.00245117644166974, -0.00489118876930438, -0.000437653348109404, 0.00339255289492743, 0.00159956591997082, 0.000669986026717940, -0.000382473742999110, -0.000597566690704767, -0.00175041734680645, -0.00372183599703196, -0.00130027232654873, 0.000778240317339792, -0.000870149853639223, 0.00279185435741788, 0.00211331057506341, -0.00167447772166078, -0.000177908234406824, 0.000269351786692906, -0.00247105322331577, -0.000213578225611575, -0.00310314393106058, 0.00137755206588702, 0.00100222308925998, 0.000676976328875909, 0.00598334119053703, 0.00543088362679717, 0.000652049711118212, -0.00135265135292594, -0.00236188932342068, -0.00487926701651181, 0.00236503940508631, 0.00174064698966380, -0.000641864341812414, -0.00151641479113188, 0.00293897874246883, 0.00280325364881420, 0.00127160772215169, -0.000293402522306098, 0.00354807778123557, -0.00175996258993758, -0.000981493966394182, -0.000593438195952982, 0.000631175705256270, 0.000122762652565054, 0.00233753922927708, 0.00454732560910740, 0.00230116347651911, -0.00326431037706669, -0.00148676297114716, 0.00213317687429016, -0.0107163481136359, -0.0101158709885057, -0.00596732639130346, -0.00262214745401737, 0.00329580562038002, 0.00552102190644915, 0.00451248110125281, 0.00254365847354366, -0.00108375323913506, -0.00112641942050664, 0.00266549908420796, -0.00652767792017297, -0.00776762428650389, 0.000107264257672592, -1.64884849616137e-05, -0.000710373354692091, -0.00146949807152253, 0.000797672254302757, 0.00124003606983166, -0.00165196554984119, -0.00435915767078120, 0.00348133811839223, 0.000137312838657495, 0.00268679482024001, 0.00224538786282937, -0.00292414902326133, 0.00176317996259482, -0.00179189798844563, 0.000887383259707572, 0.00333650142559655, 0.00199857694197948, -0.00184176167624190, -0.00354148183108420, -0.000625552890314146, 0.00486332882801648, 0.00303859677370603, -0.00123224292748884, -0.000344351189310308, -0.00145842276663891, 0.00344132887767585, 0.000280177104034467, 0.00188270152958660, -0.00429060484099222, -0.00477129562011147, -0.00349356513258055, -0.00534581689738455, -0.00577140076612450, -0.00277852212640298, 0.000766129973636633, 0.00164817443828308, 0.00659322290466138, 0.000901991432413189, -0.000182995140361039, -0.000550027292784335, 0.00166392819165303, 0.00301579132750578, -0.000274277357382067, -0.00319822747193334, -0.00330277829294262, 0.00114355202581035, -7.04767448379000e-05, 0.00252693367297824, -0.00254005528662734, 0.000397456043798698, -0.00125891369012873, -0.00140456920386264, -0.00215443906538663, 0.00164400938627474, -0.000720653757989664, 0.000391183479691289, 0.00277946875277552, 0.00219113129239301, -0.00266650186554672, -0.00395342502991065, 0.00153510106237442, 0.000758306730812837, -1.20391649741367e-05, -0.00242858463032232, -0.000834259090425446, -0.000461282795705356, -0.00333224080026368, -0.00203836126121893, 0.00111843015183225, -0.000544832407294021, -0.000462191691600878, 0.000756307253258260, -0.00166006459082854, 0.00190344387022613, 0.00347021440790857, -0.000559312134497849, 0.000919937369564442, -0.00108921468220146, 0.00246134900456333, -0.000199088442185643, -0.00292663449290011, -0.000823050016392224, 0.000895468649336371, -0.00286971861607412, -0.00217506173024189, 0.00167447936656053, -0.00165024884444343, 0.000945797884878598, -0.000698298822076474, 0.00122194334165611, -0.00193044649626327, -0.00250812544700584, -0.00443176365390929, 0.000443090617143191, -0.00107942618806448, 8.17230310661370e-05, 0.000215884402588684, 0.00635301133853112, 0.00207805673111684, -0.00110364007719692, 0.00165815768981229, -0.000333222450045376, -0.00107847407569007, -0.00188020858448237, -0.00193965571055984, 0.000762304430437059, 0.00447884366260035, 0.00297972213146710, 0.00317236702828562, -0.000763526619285365, -0.00409295332452239, 0.00507480399051754, 0.00286145022633230, -0.00127307617492304, 0.00124806585447453, 0.00108259041390898, 0.000979019319401709, 0.00427834373040928, 0.00265911122148072, 0.000868697878604357, 0.00225814884398801, -0.00442874497912711, 0.000974674483419747, 0.00146103086904311, -0.000600856131757776, 0.000135840236338993, -0.000518487375215448, -0.00235840031660446, 0.00291590303090280, -0.000723900735186999, 0.00100238879801993, 0.00269732979852077, -0.00266276978297031, 0.000662847180545325, 0.000217456867047580, -0.00228963225547624, 4.96057943609675e-05, 0.000229739491518342, 7.91326170567876e-05, 0.00114180454360153, 0.00232578016224954, 0.00533263857450809, 0.00489911606761018, 0.000418782720984771, -0.000620544953727988, -0.00266763656816269, 0.000177812383201371, -0.00160100511591412, -0.000785035455224043, -0.00381696904136624, -0.000506472253432077, 0.00226606885215669, 0.00168143752323252, -0.000206375213219325, 0.000457303567450725, 0.00271472317245640, -0.000920184409595496, -0.00128448797264353, 0.000470953888777964, -0.00172716566410700, -0.000420345985455305, 0.00155306060490927, 0.00174532823849641, -0.000614808242816828, -0.000117884305437736, 0.000840480463826880, 0.00584002157176666, 0.00181517168126955, -0.000340433218447315, -0.00107283428534149, -0.000158304998501573, -0.00217801232355013, -0.00148744982755476, -0.00141180358131889, 0.00226488131733609, -0.00100189938708128, -0.000339582406843679, 0.00245013546439535, 0.000824238080262605, -0.00540724014715309, -0.00425729468096786, -0.000288232957011642, -0.000298965822641431, -6.84213658125356e-05, -0.00140244064342141, 0.000755425144820146, 0.00119202820535428, -0.00113602261975002, 0.000360340217944428, -0.000678948442043017, -0.00221453349347152, -0.000589328192971659, 0.00117728093126285, 3.60824126984479e-05, 0.00340375663238720, 0.00554205369356869, 0.000535230817437729, 0.00127448610510230, 0.000828986094272201, 0.00397778176402259, 0.00139433474041031, -0.000557645565129369, 0.000723389493157816, 0.00285498711533456, 0.000210426256844460, -0.000597115882933614, 0.00162770028335474, -0.00230263264525842, 0.000943328398714239, -3.74890407532729e-05, 0.000259193029455121, -0.00252341024885035, -0.00161231849677041, -0.00237001513390978, 0.000953121972683142, 9.35645362041702e-06, 0.000649486361621395, -0.000432023238861045, 0.00273537432284729, 7.55062979101399e-05, -0.000163816118329557, 0.000466724810130828, -0.00172449760780963, -0.00226639151465161, 0.000270066069848947, -0.000118957050091859, 0.000369276055897727, 0.00298825734038263, 0.00152470117704708, 0.00169521037761050, -0.000614269671145043, -0.000928470551490542, 0.00494761506662102, 0.00268621043382606, -0.000670473187607869, 0.00387988361555517, 0.00176619281963662, -0.00110951572244528, 0.000230927285716746, -0.000729663283912934, -0.00159103287023249, 0.00205845515903735, -0.00146366300213442, 0.00182365959510220, 0.00128172858024130, -0.000262612126530532, 0.00184666079001267, 0.00187486726192673, -0.00264914569589102, -0.000662721022826259, -0.00401880615571749, -0.00257985385548957, 0.000266924510441722, -0.00294792082114878, 0.00309844278602154, 0.000916234261513589, -0.00243519548508814, 0.00131456079235443, 0.00192216742614170, 0.00127854450463632, -0.000617505292391909, -0.000853214580914787, 0.00156105087044573, 0.00160612922933876, -0.00348783856258084, -0.00285363943429930, -0.00405752102044924, -0.00314629103220453, -0.000437628580937318, 4.01380858502396e-05, -0.00264793368426278, -0.00147542425280230, 3.04775339082298e-05, -0.00221529678620262, -0.00240850510020146, -0.00235646877534367, -0.00108114936647176, -0.00450518166866165, -0.00474223685605947, 0.00124943664987175, -0.000464924842873881, 0.000394138775233636, 0.00136298772785957, 0.00158722151220931, -0.000912913106863604, 0.000160724039539909, 0.00301030618861356, 0.00702261073376715, 0.00225708197134934, -0.000140093792891005};
			double cst_blue = 4.78435246380727;


			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );

			Mat _image2,_image3;
			_image1.copyTo(_image2);
			_image1.copyTo(_image3);

			vector<Mat> _image_split;
			split(_image1,_image_split);

			for(int ii=0; ii<_image1.rows-11; ii++){
				for(int jj=0; jj<_image1.cols-11; jj++){
					vector<int> patch;
					for (int kk=0; kk<11; kk++){
						for (int ll=0; ll<11; ll++){
							patch.push_back(_image_split[2].at<uchar>(ii+kk,jj+ll));
						}
					}
					for (int kk=0; kk<11; kk++){
						for (int ll=0; ll<11; ll++){
							patch.push_back(_image_split[1].at<uchar>(ii+kk,jj+ll));
						}
					}
					for (int kk=0; kk<11; kk++){
						for (int ll=0; ll<11; ll++){
							patch.push_back(_image_split[0].at<uchar>(ii+kk,jj+ll));
						}
					}
										double tsum = cst_blue;
										for (int kk=0; kk<363; kk++) {
											tsum+=patch[kk]*weight_blue[kk];
										}

										if(tsum<0) {
											circle( _image3,Point (jj+5,ii+5),5,Scalar( 0, 0, 255 ),1,CV_AA );

											addWeighted (_image2,0.3,_image3,0.7,0,_image2);
											_image2.copyTo(_image3);

										}

//			for(int ii=0; ii<_image1.rows-6; ii++){
//				for(int jj=0; jj<_image1.cols-6; jj++){
//					vector<int> patch;
//					for (int kk=0; kk<6; kk++){
//						for (int ll=0; ll<6; ll++){
//							patch.push_back(_image_split[0].at<uchar>(ii+kk,jj+ll));
//						}
//					}
//					for (int kk=0; kk<6; kk++){
//						for (int ll=0; ll<6; ll++){
//							patch.push_back(_image_split[1].at<uchar>(ii+kk,jj+ll));
//						}
//					}
//					for (int kk=0; kk<6; kk++){
//						for (int ll=0; ll<6; ll++){
//							patch.push_back(_image_split[2].at<uchar>(ii+kk,jj+ll));
//						}
//					}


//					double tsum = cst_red;
//					for (int kk=0; kk<108; kk++) {
//						tsum+=patch[kk]*weight_red[kk];
//					}
//
//					if(tsum<0) {
//						circle( _image3,Point (jj+3,ii+3),5,Scalar( 0,255,0 ),1,CV_AA );
//
//						addWeighted (_image2,0.7,_image3,0.3,0,_image2);
//						_image2.copyTo(_image3);
//
//					}

//					double tsum = -cst_blue;
//					for (int kk=0; kk<108; kk++) {
//						tsum+=patch[kk]*weight_blue[kk];
//					}
//
//					if(tsum<0) {
//						circle( _image3,Point (jj+3,ii+3),5,Scalar( 0,255,0 ),1,CV_AA );
//						addWeighted (_image2,0.7,_image3,0.3,0,_image2);
//						_image2.copyTo(_image3);
//
//					}


//					double tsum = cst_yellow;
//					for (int kk=0; kk<108; kk++) {
//						tsum+=patch[kk]*weight_yellow[kk];
//					}
//
//					if(tsum<0) {
//						circle( _image3,Point (jj+3,ii+3),5,Scalar( 0,255,0 ),1,CV_AA );
//						addWeighted (_image2,0.7,_image3,0.3,0,_image2);
//						_image2.copyTo(_image3);
//
//					}

//					double tsum = cst_red;
//					for (int kk=0; kk<363; kk++) {
//						tsum+=patch[kk]*weight_red[kk];
//					}
//
//					if(tsum<0) {
//						circle( _image3,Point (jj+5,ii+5),5,Scalar( 0,0, 255 ),1,CV_AA );
//
//						addWeighted (_image2,0.7,_image3,0.3,0,_image2);
//						_image2.copyTo(_image3);
//
//					}

//					double tsum = cst_yellow;
//					for (int kk=0; kk<363; kk++) {
//						tsum+=patch[kk]*weight_yellow[kk];
//					}
//
//					if(tsum<0) {
//						circle( _image3,Point (jj+5,ii+5),5,Scalar( 0,0, 255 ),1,CV_AA );
//
//						addWeighted (_image2,0.7,_image3,0.3,0,_image2);
//						_image2.copyTo(_image3);
//
//					}

					//						namedWindow( "a", CV_WINDOW_AUTOSIZE );
					//												imshow( "a", _image2);
					//												waitKey(0);


//					tsum = cst_red;
//					for (int kk=0; kk<363; kk++) {
//						tsum+=patch[kk]*weight_red[kk];
//					}
//
//					if(tsum<0)
//						circle( _image2,Point (jj+5,ii+5),0,Scalar( 255, 100, 255 ),1,8 );
//
//					tsum = cst_yellow;
//					for (int kk=0; kk<363; kk++) {
//						tsum+=patch[kk]*weight_yellow[kk];
//					}
//
//					if(tsum<0)
//						circle( _image2,Point (jj+5,ii+5),0,Scalar( 100, 255, 255 ),1,8 );


				}
			}

//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a", _image2);
//			waitKey(0);
			imwrite(dir+"/detect_red11_min3/"+tokens[0]+".png",_image2);

//
//			Mat _pointdata =  imread( dir+"/pointdata_sign/"+tokens[0]+".bmp", -1 );
//			vector<Mat> _pointdata_(3);
//			split(_pointdata,_pointdata_);
//
//			vector<int> startx;
//			vector<int> starty;
//			vector<int> endx;
//			vector<int> endy;
//
//			for(int ii=0; ii<_pointdata.rows; ii++){
//				for(int jj=0; jj<_pointdata.cols; jj++){
//					if (_pointdata_[2].at<uchar>(ii,jj)>0) {
//						if (_pointdata_[1].at<uchar>(ii,jj)>0) {
//							startx.push_back(jj-5);
//							starty.push_back(ii-5);
//							endx.push_back(jj+5);
//							endy.push_back(ii+5);
//						}
//					}
//
//				}
//			}
//
//
//
//
//			vector<int> fendx;
//			vector<int> fendy;
//
//			float dist = 0;
//			float mindist = 1e100;
//			int minind=-1;
//
//
//			ofstream FileO2;
//			stringstream strrr2;
//			strrr2<<dir<<"/cropdata_sign/agg.txt";
//
//			FileO2.open(strrr2.str().c_str(),ios::out|ios::app);
//
//
//
//			ofstream FileO;
//			char buffer[256];											// use limited buffer
//			stringstream strrr;
//			strrr<<dir<<"/cropdata_sign/"<<tokens[0]<<".txt";
//				FileO.open(strrr.str().c_str(),ios::out);
//				FileO.seekp(ios::beg);
//
//			for(int ii=0; ii<startx.size(); ii++){
//				dist = 0;
//				mindist = 1e100;
////				for(int jj=0; jj<endx.size(); jj++){
////					if (startx[ii]>endx[jj]) continue;
////					if (starty[ii]>endy[jj]) continue;
////					dist = (endx[jj]-startx[ii])*(endx[jj]-startx[ii])+(endy[jj]-starty[ii])*(endy[jj]-starty[ii]);
////					if (mindist>dist) {
////						mindist = dist;
////						minind = jj;
////					}
////				}
//				fendx.push_back(endx[ii]);
//				fendy.push_back(endy[ii]);
//				cout<<fendx[ii]<<"\t"<<fendy[ii]<<"\t";
//
//			}
//			cout<<startx.size()<<"/"<<endx.size()<<"   ";
//			cout<<startx.size()<<"/"<<fendx.size()<<endl;
//			srand(1);
//			int iiend=20;
//			for(int ii=0; ii<iiend; ii++){
//				int x = (float)rand()/RAND_MAX*(_image1.cols-11);
//				int y = (float)rand()/RAND_MAX*(_image1.rows-11);
//				cout<<x<<"_"<<y<<"_"<<11<<"_"<<11<<endl;
//				int jj;
//				for(jj=0; jj<startx.size(); jj++){
//					if ((((x-startx[jj])<11) && ((x-startx[jj])>-11)) || (((y-starty[jj])<11) && ((y-starty[jj])>-11))) {
//						break;
//					}
//				}
//				if ((((x-startx[jj])<11) && ((x-startx[jj])>-11)) || (((y-starty[jj])<11) && ((y-starty[jj])>-11))) {
//					iiend++;
//					continue;
//				}
//				Rect rect (x,y,11,11);
//				Mat croppedimage;
//				_image1(rect).copyTo(croppedimage);
//				stringstream str;
//				str<<x<<"_"<<y<<"_"<<11<<"_"<<11;
//				imwrite(dir+"/crop_neg/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
//			}
//
//
//			for(int ii=0; ii<startx.size(); ii++){
//				Mat croppedimage;
//				Rect rect (startx[ii],starty[ii],fendx[ii]-startx[ii]+1,fendy[ii]-starty[ii]+1);
//				_image1(rect).copyTo(croppedimage);
//				stringstream str;
//				str<<startx[ii]<<"_"<<starty[ii]<<"_"<<(fendx[ii]-startx[ii]+1)<<"_"<<(fendy[ii]-starty[ii]+1);
//				imwrite(dir+"/crop_sign/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
//
//
//				Mat grayy;
//				if (croppedimage.type()!= CV_8UC1) cvtColor(croppedimage,grayy, CV_RGB2GRAY);
//				int erosion_type = MORPH_RECT;
//
//				threshold(grayy,grayy,0,255,THRESH_BINARY+THRESH_OTSU);
//				 copyMakeBorder( grayy, grayy, 1, 1, 1, 1, BORDER_CONSTANT, 0 );
//
//				vector< vector<Point> > contours; // Vector for storing contour
//				    vector<Vec4i> hierarchy;
//				    int largest_area=0;
//				    int largest_contour_index=0;
//				    imwrite(dir+"/crop2_sign/"+tokens[0]+"_"+str.str()+".bmp",grayy);
//				    findContours( grayy, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image
//
//				    for( int i = 0; i< contours.size(); i++ ) {// iterate through each contour.
//				        double a=contourArea( contours[i],false);  //  Find the area of contour
//				        if(a>largest_area){
//				            largest_area=a;
//				            largest_contour_index=i;                //Store the index of largest contour
//
//				        }
//				    }
//				    Rect bounding_rect=boundingRect(contours[largest_contour_index]); // Find the bounding rectangle for biggest contour
//
//
//				stringstream str2;
//				str2<<startx[ii]<<"\t"<<starty[ii]<<"\t"<<(fendx[ii]-startx[ii]+1)<<"\t"<<(fendy[ii]-starty[ii]+1)<<"\r\n";
//				FileO.write(str2.str().c_str(),str2.str().size());
//				FileO.seekp(0,ios::end);
//
//				stringstream str3;
//				str3<<(ii+1)<<"\t"<<tokens[0]<<"\t"<<(fendy[ii]-starty[ii]+1)<<"\t"<<(fendx[ii]-startx[ii]+1)<<"\t"<<(float)(fendy[ii]-starty[ii]+1)/(fendx[ii]-startx[ii]+1)<<"\t"<<startx[ii]<<"\t"<<fendx[ii]<<"\t"<<starty[ii]<<"\t"<<fendy[ii]<<"\t"<<((float)fendx[ii]+startx[ii])/2<<"\t"<<((float)fendy[ii]+starty[ii])/2<<"\t"<<bounding_rect.width<<"\t"<<bounding_rect.height<<"\t"<<"\r\n";
//				FileO2.write(str3.str().c_str(),str3.str().size());
//				FileO2.seekp(0,ios::end);
//			}



#endif



#ifdef Detect_traffic_sign2

			//gooood
//			double weight_blue[363] = {0.000359885621909795, 0.000335384083341025, -0.00120918202124540, -0.000412191342436629, 0.000262421572771093, -0.000625292861812576, 0.000658289256044181, -0.000202903914336939, -5.73957798438742e-05, -0.000137268944804616, -0.00149796653458915, 0.000508092692512186, -4.13088559407704e-05, 0.000116915151898484, -0.00103273186196581, 0.000683482917380885, 0.000392606156201663, 0.000527224274259692, -7.55112294944268e-05, 0.000684032786812050, 7.41316950212912e-05, -0.00178373159446168, -0.00102764482626940, 0.000622189314949944, 0.000396699834023786, -0.00102587840641432, 0.00235285344434465, 0.00174930150278705, 0.00103212054607864, 0.000670918338323361, 5.41399585815242e-05, -0.000431937623335271, -0.000877040908962229, -0.00100802983342738, -0.000420540460553675, -3.47079384484706e-05, -1.92692415044960e-05, 0.000806264444680072, 0.00128693322176523, 0.00131386161312508, 0.000393050748400490, 0.000283868560579107, 0.000408971389193115, 0.00109794651418581, 0.00101378848376601, 0.000122056367733474, 2.60703763342810e-05, -0.000293711298926645, 0.00117765663094027, 0.00291189591102490, 0.000916955144359089, 0.00147398241146047, 0.000681583342304242, -2.58020913422332e-05, 0.000782990058052020, 0.000407486481343536, -0.00213475835051605, 0.000146007007147707, 0.00105045919754968, 0.00442865478801434, -0.00102638140659241, 0.00533089562111850, 0.00179689024507816, -0.000557296602395707, -0.000589181590820913, -0.000549185887037553, 0.000192717270363190, -0.00199599599391072, -0.000757733305344099, 0.000204499889024155, 0.00285946633899029, 0.00424972281106717, 0.00458823298677584, 0.00142736405830514, 9.41762161812587e-05, 0.000563549277685543, 1.84539543283697e-06, 7.27183008721478e-05, 0.000522652252562960, 8.00860700648875e-05, -4.54790328209363e-05, -0.000171006845353120, 0.00109440228875966, 0.000549856020682373, 0.000349586966629586, 0.000715933617075095, 0.000733777313564374, 0.000252592990012234, -0.000631822426823035, 0.000736257594632908, 2.09828562333818e-05, -0.000810704680749891, -0.000591459653498786, -0.000709088553352855, -0.00110539979933965, -0.000758551146071462, -0.000260893472183621, -8.53293676583782e-05, -8.17392371337676e-05, -0.00106017656848992, 6.39152843335059e-06, -0.000341411628265776, 0.00101363518552641, 0.000177822399745175, 0.000201205136783923, -0.000324093872521965, -0.000240020099669534, 0.000414141567842380, 0.000268209595881532, -8.29189291607863e-05, -0.000961657790860754, 0.000647568023418169, 0.000717018605880880, 0.000290829864084639, 0.000103835251802783, -0.00203003636001452, -0.000681423734510253, -0.000489716669260178, -0.000834939188208054, -0.000927354309622176, -0.000712659886902091, 0.00174801611825390, 0.000968349789859599, -0.00137600124131210, -0.000614725163256462, -6.10417140887751e-05, -0.00181331956580608, -0.000384593616208003, -0.000163996417538404, 0.000444923693340918, 0.000602640843377472, 0.000699900775754953, 0.00147979404909797, 0.000731246938771423, 0.000522492656107031, -0.000806094133124196, 0.000636369576057873, -5.11527392011904e-05, -0.000138811524040543, -0.000808483134362622, -0.000368454126624300, -6.68918412250975e-05, -0.000350658967149799, -0.000507235520789032, 0.000983002927765816, 0.000840498882593685, -0.000790333191181829, 0.00201836305683254, 0.00153831416083499, 0.000355277626523590, -0.000488345736134631, -0.000867381423332192, -0.00117355620998158, -0.00159545528155790, -0.00106833003602547, -0.000854991295995876, -0.000404660931242536, -0.000680362864959296, -0.000580085668862058, -0.000123624430593805, 0.000453945380933308, 0.000201674865376678, 0.000121825593987997, -0.000197897744683327, 0.000523615599134999, 0.000890766695483373, -0.000237470683959399, -0.000393957608268113, -0.00154339273513156, -0.00276465520489175, -0.00244972796656270, -0.00296487502631328, 2.41344856265013e-05, 0.000406854425867227, 0.000350049310785210, 0.000869766205431032, 0.000702601335574486, -0.000909246011251159, 0.000888150316626988, 7.34566809469613e-05, -0.00173076080747052, -0.0101260397645680, -0.00214978877081752, -0.00192038541459417, -0.00119444931255075, -0.000652507296867388, -0.000906687689877789, 0.000817775617030233, -0.000783997324299569, 0.000320626242659873, 0.000646595431086196, -0.00139069623719213, -0.00497461261173007, -0.00319580716184123, -0.00192318501353935, -0.000733974775465469, -0.000155368306265424, -0.000980963350985130, 0.000118410239421704, 0.000567371013083932, -0.000229968171076024, 0.000306595399029284, 2.70734799100007e-05, -0.000361492032397472, -0.000620403999434588, 0.000897535562665045, 0.00130173294783030, 0.000634113443041823, 0.000117367424182351, -0.000241749505435765, 0.000940775237021127, 3.88917100552836e-05, -0.000485374986385151, -0.000135427309752000, -0.00130826578980820, -0.00159639121429348, 0.000294106015750187, 0.000605168045373303, 0.000365033619741771, 0.00107042377107743, -0.000351469526933092, 0.000640080925945259, -2.91308044698525e-05, 0.00152443447909992, 0.000751109236813737, 0.000133336045767782, -0.000430179841451752, 0.00100403781844103, 0.00128922709734823, 0.000870160251614726, 0.00153989686344967, 0.000399440219258333, 0.00133040869084014, 0.000682864507602636, 0.000531779062685852, 0.00121546830535623, -0.000942446115053845, 2.13760774269009e-05, 0.000200127842522438, 0.000304803884399695, 6.74512377961743e-05, 0.00123118646657797, -0.000707195605940815, -0.00122161820417072, -0.00237881387776452, -0.000207882235290243, 0.000768239146736921, -0.000491369524589957, 0.000779727679385106, 0.000645056202826725, 0.000632911402329583, 0.000570136865924246, -0.000979228744573077, -6.99154530970174e-05, -0.000994431327182732, -0.000602904678169354, -0.00106207167550284, 0.000823379675411981, 0.000385571776287771, 0.000776880000675547, 6.87458116397104e-05, 0.000431711788277687, -0.000613190752636377, -0.00184854603453323, -0.000586027402207258, 0.000470027525529644, -0.000194965328886505, -0.00166498580523167, 0.00200427628520396, 0.00179337780804044, 0.00121404790091357, -0.000363765657095063, -0.00205790873067747, -0.00140257940973952, 6.13378040362385e-05, -0.000339294062896270, -0.000261925644177701, -0.000346385703672583, -0.000263770181548183, 0.00110986509917578, 0.00139813166211353, 0.00105942152356995, -0.00114857451559355, -0.000768798629465243, 0.000811829683229141, 0.00163209221296236, 0.00121345020952502, -0.000101672880899459, 0.000223772108171938, 0.000460945251996380, 0.00168278018565771, 0.00143729930084057, -0.000940028660280691, 5.75542681444034e-05, 0.000419809397362431, 0.000248925639242448, 0.000762902093449063, 0.000680101490782832, -0.000896271165431173, 0.00128859862093204, 0.000691727305802791, 0.00138827665953340, -0.00567427345298586, 0.00176076587232946, -7.15515467461750e-05, -0.00117157589771398, -0.000378687440235544, 2.56658566558411e-05, 0.00147432563168394, 0.000149378393058154, 0.00103715497000698, 0.000416411461097481, 0.000141825203439444, -0.00134530776853309, 0.000841681293244248, -0.000380428689297184, -0.000677203702098583, 0.000626181753764309, 4.97795073789908e-05, -0.000217453799722364, 0.000469020584090203, -0.000487281028634299, -0.000268004407434079, -0.000160148717267143, 0.000616507231355166, 0.00100230463562697, 0.000657433816265970, 0.000383573045999714, 0.000473038710145714, -0.000209963423739030, -0.000501274976087335, 0.000206384013035451, -0.00145455730781604, -0.00110813980283029, 1.05981383291803e-06, 5.92971786227489e-05, -0.000186372694220149, 0.000276126913543486, -0.000474904476072985, -0.000340256487631009, 0.000234486330124884, -0.00134620208298859, -0.000716748980527893, -0.000738840377878546, 0.00110086407712951, 0.000697474774578351, 0.000945470701519695, 0.000297900695134767, 0.000865299787464654, 0.000903298193037219, -0.000452866133324702, -0.000242592694870133, -0.00172741068504122, 0.000358401137645814, 0.000277363224436862, -0.000447835675656222, -0.000656186393202642, -0.00198550361455554, 0.000335333829832442, 6.89779752016534e-05, -0.000415394033003688, -0.000384436664926656, -0.000212630852640010};
//			double cst_blue = 3.25639293718492;


			double weight_blue[363] = {0.000192124319931933, 0.00296305997167245, 0.00151539958614526, 0.000263295243114580, 0.00104023113712570, 0.00194245444399212, -0.00117349398666299, -0.000467768997090743, 0.00302086172191533, 0.00246295389844813, -0.00418219266921603, -0.000305781599299959, 0.00266052712952348, 0.00203112833696767, 0.000913316680666023, -0.000301550255025540, -0.00135735954534032, -0.00140846712241285, -0.00346953138003068, -0.000787679664212664, 0.000716909067495885, -0.000897899168488953, 0.00296218510229879, 0.00154517103676293, -0.00274297591578590, -0.000527525015061967, 0.000127177372592568, -0.00285186460647450, -0.00112699464238251, -0.00241125362406594, 0.00189235280519690, -0.000105796580293245, -0.000617604742901218, 0.00472319523246166, 0.00372803606683115, 0.000162061371468396, 5.72267686778645e-05, 0.00118498396065944, -0.00405831414905806, 0.000737866088717331, 0.00131577768639583, -0.000929422181367079, -0.00170187724245117, 0.00220238021536811, 0.00122280393047417, 0.000101219524472067, -0.000432328878966668, 0.00193508982423494, -0.00166875415234498, -0.00216202906585551, -0.000743138012843942, 0.00183221063338338, 0.000457495721447038, 0.00325547257159278, 0.00664813106225430, 0.00309339228239219, -0.00294704952031373, -0.00128826405668372, -0.000313151479884181, -0.00860616259945571, -0.00852599912776656, -0.00740628039574026, -0.00244224538988546, 0.00300869261834464, 0.00496201689895704, 0.00340003921354084, 0.00464489841590137, 0.000145303176043923, 0.000150160959197976, 0.00210678576247811, -0.00477567175499867, -0.00767223342657851, -0.00179965640551708, 0.000236064082984886, -0.000660764684108522, -0.000878693320065337, 0.000226650456267337, 0.00132160828398526, -0.00181967263446165, -0.00421399796500766, 0.00260719000768012, -0.000131936252892187, 0.00146098047298470, 0.00229899976744837, -0.00218178454097139, 0.00185378925092756, -0.000830316153264579, 0.000876161935415802, 0.00301366491113728, 0.00145483586867082, -0.00205293826433801, -0.00318087620113890, 0.000450941405192792, 0.00469396693594308, 0.00309627275927227, -0.00125561184771059, -0.000247342386633066, -0.000773156747233007, 0.00383854274356874, 0.000739541150322625, 0.00153212111169548, -0.00426191027106734, -0.00509353022707921, -0.00332328537247709, -0.00487953806069610, -0.00521861657711288, -0.00276530558238319, -0.000134284754136373, 0.00108738193761432, 0.00584857562885331, -0.000400583729281424, -0.000351902256811796, -0.000268596431894114, 0.00240002117563257, 0.00459771202889989, 0.000639415144988244, -0.00242467531090429, -0.00222107500895419, 0.000597485760150800, -0.00146980202609505, 0.000186974231199268, -0.00243177287969577, 0.000644201723642874, -0.000645956780358701, -0.00191540545683210, -0.00121913119212674, 0.00157891092167693, -0.000465288835799443, -0.000705815100702779, 0.00238265518724761, 0.00180801081911292, -0.00326993811826848, -0.00349700563743585, 0.00115344304677630, 0.00101127312107361, 5.14363181087784e-05, -0.00198387785371128, -0.00121779706644806, 7.23283422503019e-05, -0.00354403161709694, -0.00172761617658052, 0.000448811343159689, -0.00145839995219969, 0.000982364610546752, 0.00122453374667749, -0.00165595448167334, 0.00188622857125249, 0.00328841592040947, 4.73416702499885e-05, 0.000986159608376481, -0.000435598033438406, 0.00337887726089462, -0.000308973171304623, -0.00349520274096414, -0.000338550564593119, 8.32447423730169e-05, -0.00263082562330325, -0.00219096296984192, 0.00209177352479985, -0.00178890815511716, 0.000743499902768806, -0.000841101248876487, 0.000443953764102774, -0.00121707162379360, -0.00225235827045024, -0.00413315340190812, -0.000368520755431449, -0.000442130526165383, -0.000550036202992565, -0.000585098256827144, 0.00364686787158084, 0.00285174016916648, -0.000271994980506766, 0.000215527729736621, 0.000909711598020389, 0.00112559876506019, 0.000119714480447876, -0.00115516324172232, 0.00142377911384902, 0.00227437123988498, 0.000821367443619190, 0.000443794729095019, -0.00123275147271531, -0.00290321116270856, 0.00299680798038737, 0.00154192727078791, -0.00268377141376020, 0.00121394504489639, 0.000905910995814013, 0.00183657904879550, 0.00340170695670893, 0.00254853651583998, 0.000922587132077039, 0.00268151920158300, -0.00310763116489447, 0.000674329836974916, 0.00139767694296179, -0.00107445702689915, -0.000285701345403589, -0.000357773647266801, -0.00143593386796550, 0.00266415429137468, -0.000582162830881044, 0.00161479678288367, 0.00322477610205450, -0.00245403919906707, 0.000917566482732543, 0.000701188730806998, -0.00135406743104933, 0.000787226625814234, 0.000865713491493814, -0.000183718922331774, 0.000137760730053294, 0.00205422482591194, 0.00596152235559134, 0.00506763885258652, -0.000333683576213839, -0.000542509474656523, -0.00156394999472671, 0.00129252372809154, -0.000636447664153608, -0.000387454911250140, -0.00340847225658994, -0.00138882680164767, 0.00124124292203592, 0.000165802290199027, -4.53065389312032e-05, 0.000232483723193197, 0.00161361703918330, -0.000675143520398632, -0.00105547119573808, 0.000106888500229145, -0.00171509317485595, -0.000749931038355275, 0.00148385666455220, 0.00228944872162389, -0.00161904346100664, -0.00133706007722704, 0.00112236797759175, 0.00495736857329714, 0.00128807674330935, -0.00133566065776931, -0.00165357011792224, -0.000215821578882898, -0.00165176909032921, -0.00147172822801447, -0.000139159910069228, 0.00256879679217476, 0.000394134389976274, 0.000206664619843771, 0.00345574949495586, 0.00121222505750869, -0.00521346542698224, -0.00444175886663060, -0.000981122668352508, -8.39054310266937e-05, -5.98900477991370e-05, -0.00138500720235055, -0.000441835400114959, 0.00153888728391700, -0.00117000123330785, 0.000784856647509014, -0.000179721467442475, -0.00211645775824240, -0.000409370545796313, 0.000980907841640747, -0.000369400624117993, 0.00279944265744282, 0.00418544428447085, -6.27026741860776e-05, 0.00120876143963207, 0.00155264637961577, 0.00502404700452262, 0.00135499158115977, -0.000556596752770516, 0.000348087073318475, 0.00203312517499571, 0.000788247828039207, -0.000491506167929367, 0.00159778962419078, -0.00250134909111746, 0.00107430320602405, 5.39424342792188e-05, -0.000404967315648847, -0.00133432569822622, -0.000846856438236954, -0.00210547641178508, 0.00120625846461338, 0.00115463457072073, -0.000200185793620074, -0.000695896629166295, 0.00203274334044524, 0.00209802911089531, 0.000492185709449926, -0.00157538020063181, -0.000669232048151149, 0.000298118921017847, 0.00189947702856172, 0.00118849367539779, 0.00130828934493647, 0.00117393278502430, 0.00147522803998887, 0.00257190429243009, 0.000804866286730777, 0.000768035520282209, 0.00299149139384197, 0.00158025367428330, -0.00187384254239465, 0.00302259959244343, 0.00153573834931043, -0.000598002294662196, -0.000841822582962105, -0.000966743588548031, -0.00196872006365159, 0.00209604579612979, -0.000897210430468003, 0.000500498436264925, 0.000678612828301774, -0.00169361474045856, 0.00112282596457447, 0.00150286125499061, -0.00215649833903047, -0.000692784054753309, -0.00433059900704520, -0.00271630380593218, 0.000781657300699131, -0.00305499121681533, 0.00117135857518791, -0.000143952531607371, -0.00290310564355096, 0.00136731112645495, 0.00183285025445515, 0.00117489433035568, -0.000801284229112842, -0.000174384019974312, 0.00236514894107244, 0.00214302015298818, -0.00357348610161220, -0.00272663681489150, -0.00377397266726848, -0.00241198513130109, 0.000519722315004036, 0.000439424046538448, -0.00202236832713075, -0.00171904950731462, -0.000118788089383808, -0.00244321384472450, -0.00220659723627455, -0.00188503510830602, -0.00102370867677932, -0.00403562593291752, -0.00462171401961357, 0.000197282483567915, -0.00115141902295582, -7.24146991451227e-05, 0.00157378944184346, 0.00233630028452965, -0.00106546836564644, -0.000434585742603081, 0.00328298721767461, 0.00668508594325856, 0.00211309564002712, -0.000904596905604481};
			double cst_blue = 5.04557772608486;

			// better? retrain
//			double weight_blue[363] = {-0.000142089296604829, -3.28845612221585e-05, -0.00112010970536643, -0.000447551359589290, 0.000595153607639416, -0.000823266248610198, 0.00183739311718949, -0.00104375613219347, -0.00139086512615703, -0.000875412046290534, -0.00130751354565310, 0.000443289267831786, -0.000162230324819785, -0.000254957803430930, -0.000823983883759974, 0.00177692114170545, 0.00158355028983490, 0.000494608194667303, -0.000204625216270625, 0.000912985806868310, 0.000126134817524055, -0.00135323578609172, -0.00133559092930176, -0.000365237161777332, 0.000959209221564933, -0.000861104020756212, 0.00285892293023852, 0.00317435211427705, 0.00115618778296734, 0.00104625268061678, 0.000590973733120381, -0.000458357063075659, -0.00126070146600506, -0.00105081147027679, 6.16970892957423e-05, 0.000603779996862584, 0.000590206312544643, 0.00140598682270357, 0.00182890457632955, 0.00229415934801907, 0.000622815801155589, 0.00130042181143743, 0.000835798426675941, 0.000170240152015436, 0.00149950690444697, 2.23218300162624e-05, -0.000900673686447700, -0.000187102280114344, 0.00324914599529374, 0.00397037152124265, 0.00136391073769061, 0.000523299051963798, 0.00197701180673505, 0.000404916415482381, 0.000222135645858211, 0.000992095443914733, -0.00185970604661897, -0.000873897168889750, 0.00316390806145872, 0.00379513441217269, 0.000152649672202508, 0.00624493296839084, 0.00345541147208254, 0.000635289529742810, -0.000820179058701691, -0.000981816651038354, -0.000286634174282301, -0.00164727648748713, -0.000832268649931571, 0.000256486664964535, 0.00321796710853547, 0.00469565166361832, 0.00539004728908056, 0.00119658149842639, 5.68798218268294e-05, 0.000120144289375477, -0.000233309387583115, -0.000344319274196350, 0.000506458079118604, -0.000167309965628017, -0.00102200247376395, -0.00169971402137201, 7.73671249785987e-05, -0.000249038630904500, 0.000548949123775672, 0.00113632996930723, 0.000862454718051625, -4.84253979748763e-05, -0.000530300614512312, 0.000159812236975468, 0.000526530124783555, -0.00116305962166178, -0.00178744487769293, -0.000261612407418404, -0.00120162633292337, -4.62739163976647e-05, 0.00110002765261118, 7.30688944498934e-05, -0.000719817695707453, -0.00155951200717254, 0.000142026537916379, 0.000119555622332998, 0.00117203857089201, -3.78148566791360e-05, 0.00104967113855437, 0.00109664571510965, 0.000436091033872196, 0.000794401628621777, -0.000303155769485551, -0.000499883889355044, -0.00263194134341231, 0.000221178636226304, 4.69205263009215e-05, 0.000226643882289966, 0.00131434667906378, -0.00303408492990475, 3.57175360027780e-05, -0.00118498518666437, -0.00139114566584116, -0.00160521258350685, -0.00119151997810814, 0.00210548345003329, 0.000736545407110601, -0.00165415667006930, -0.00119096555061931, 0.000308483716200075, -0.00154415993148887, 0.00127539726248312, -0.000600455765267824, -0.000446019771259703, 0.000799521250617273, 0.00233196994605571, 0.00191136234231327, 0.000888684117154403, -0.000168488702922864, -0.000936492718257388, 0.00160626596158436, 0.00138961537483190, -3.50934821058502e-05, -0.00121212412129220, -0.000204313295447989, 0.000909144467024243, 0.00126577203912939, -0.000924308745605330, -0.000481919853392525, 0.00123814540714802, -0.000733087985993456, 0.00213373839443842, 0.00223731004297113, -0.000494145752190659, -0.00138805664726446, -0.000609853072317110, -0.000922642285833092, -0.00162680427767652, -0.00119525755977439, -0.000786745893840122, -9.89084297788267e-05, -0.000627202587785110, -0.000875088226156784, -0.000738590371193491, 0.000481994106387807, -0.000391534925425590, 0.000701318495999264, 1.59674025414600e-05, -0.000505540005886860, 0.00122338725003679, -0.00109107127627011, -0.00213713681936408, -0.00202362532712248, -0.00165273980605806, -0.00267056564506500, -0.00334315634634341, -0.00135246323423336, 0.00120190197564856, -0.000680687135411799, -0.000417431986262498, 0.00104133351585391, -0.000669154598107290, -0.000251203320834063, 0.00224186263065165, -0.00309762950117217, -0.0103152840936866, -0.00286236869451618, -0.00152203748978301, -0.00152091879761534, -0.00211296628607593, -0.00192336629245661, 0.000183879351733766, -0.000470552119871959, 0.000773793003509755, 0.00186443377771947, -0.000344462190657563, -0.00549426854935490, -0.00379495871855926, -0.00314159451965856, -0.00169407683208690, -0.00112840935730854, -0.00138876136669251, -0.000591189011532252, 0.000354562454490950, -0.000144884780008761, 0.000464518574918606, 0.000134981738838986, 6.62235975038526e-05, -2.32644282028870e-05, 0.00135757494903523, 0.00124669078954523, 0.000391554989015021, -3.07633354374838e-05, -0.000328663645281440, 6.25472227098252e-05, 0.000567788943499360, -0.000611694979196678, -0.000697148209837261, 0.000339029427229733, -0.000184832331889656, 0.00126761170693059, 0.00197899291976840, 0.000445542632763750, 0.000960231541027913, -5.85915327388292e-05, 0.00162824144979528, 0.000574180460227194, 0.00123672594500635, 0.000385148550325281, 0.00156445424825914, 0.00208035581226544, 0.00229009678289193, 0.00233615022003542, 0.000925595399563789, 0.00226758754832104, -0.000596931213988480, 0.00129497779570398, 4.88922983097888e-05, 0.000110739336360954, 0.00231275624838965, -0.00141759186348700, 0.00113428232520096, -0.000522632000204284, 0.000224401460105492, 0.000338282091269505, 0.00217173788222689, -0.00108803929888052, -0.00156004457674454, -0.00243538600558175, -0.000489421784300488, 0.000488394674826970, -0.00202524251527924, 0.000703610513166903, -0.000500292471335352, -0.000272003525396698, 0.000429930157107050, -0.000326376767289182, -0.000467182560428666, -0.00170790072288919, -0.000721603604269829, -0.000714596323188255, 0.00146153822526045, 0.000606816962609688, 0.000435489765152170, 0.000219496738203390, 0.000812818658588167, -0.00107618177191175, -0.00141035331758796, -0.000288849309032846, -0.000793858495027622, -0.000297273039658260, -0.00152671827811843, 0.00205515646539686, 0.00190059140493698, 0.000683032576856047, -8.41444886308185e-05, -0.00208391398547102, -0.00120003974860767, 0.000945859329012638, -5.18988258550930e-06, 0.000822766484221761, 0.000424720189543504, -0.000309177865010391, 0.000938256852063026, 0.000473304694722888, 0.00128515310151202, -0.00189319961384186, 8.26853945333035e-05, 0.00219347757700117, 0.00153491227399989, 0.00185129472842155, 0.000161943519658911, -0.00106634221133709, -0.000519224686044518, 0.00240386587579671, 0.000603521629467162, -0.000822199984658065, -0.00133643988067834, 0.00144983290000065, 0.000890746723392943, -1.23097493366041e-05, 0.000936741516969358, -0.000411895779918394, 0.000607435288021063, 0.00241353707360491, 3.78925614750566e-05, -0.00602888864883813, 0.00120966692191664, 0.000739619832645232, 0.000150237401420936, -0.000661371354079496, -0.000849620415494318, 0.000899658254335221, 0.000787442731765354, 0.00140170301044331, 0.00126810569326728, 0.00182937091499758, -0.00139971667607167, 0.000517522215641786, -0.00139437736690087, -0.000144224269669965, 0.000732462907446317, -0.000263851871114420, -0.000287465116023515, 0.00129969077571455, -0.000430632779259819, -0.000629299996129581, -0.000783164802994815, -0.000872670645693761, -0.000371478974339676, 3.35147603416817e-05, 0.000621489579869927, 0.00109962714726133, -6.35194198523742e-05, 0.000165171346240122, 0.000445663323071901, -0.00123330834103029, -0.00174774096737615, -0.00188651246232026, -0.000877529705205882, -0.00158430279339131, 0.000359583661980510, -0.000124602263578084, -0.000626796988651688, 2.28885064112846e-05, -0.00100077438867426, 2.70062192082475e-06, 0.000673147558258079, 0.00104583576201757, -0.000682328094767669, -0.000184424276035561, -0.000394882050546110, 0.00100372485465430, 0.00182137267838820, -0.00172185368722075, -0.00102520966599105, -0.00232994102537572, 0.00163998787460295, 0.000732777412394695, -0.000665962370289905, 0.000155805407731885, -0.00349440090541692, 0.000195094794309451, -0.000808724058968569, -0.000195380784113184, -7.59802426092342e-05, -0.000114823880614115};
//			double cst_blue = 3.43081848491551;

			// better? retrain2 (more positives)
			//double weight_blue[363] = {-3.05783430604957e-05, -0.00114706746335227, -0.00251630534871197, -0.00109069887651525, 0.00118677578860259, -6.05272046820895e-06, 0.00192483404556103, -0.00117164113042155, -0.000515571336111431, -0.00143112589211207, -0.00224584554721977, 0.000676432615102347, 0.000641587619326754, 0.00110339998419831, -0.00151780234503127, 0.00180718140111019, 0.00173025079965937, 0.000597779689556985, 0.000716770481445503, 0.000709339757502469, 0.000114519522120853, -0.00160889300712455, -0.00134406575988633, -0.000553282203151161, 0.000418326838272107, -0.000890588537051111, 0.00200749304976770, 0.00398202406363825, 0.00192383862098017, 0.00172852074121309, -0.000725373130650106, -0.000624848435898205, -0.00126361713108468, -0.000689403987374079, -0.000527968262088254, -0.000763130378238901, 0.000169362687212710, 0.00257667349274913, 0.000366964437954096, 0.00475488658490141, 0.00181837871921746, 0.00144183921850081, 0.000303385692325635, -0.00189199391114128, 0.000404271019936615, -0.00115650852157070, -0.000775740582352936, 0.000341020967338881, 0.00289192174476204, 0.00772030661247648, 0.00362336934612078, 0.00202931620663220, 0.00238613974184813, 5.66436938056931e-05, -0.00101661338516677, 0.00229900422696908, -0.00108289845113272, 0.000436361122670224, 0.00301748399048116, 0.00729467414015663, 0.00248287982478309, 0.00732539962326410, 0.00623033426222667, 0.00281899243101696, -1.77510275272071e-05, -0.00123531627862243, -0.000751613032522002, -0.00184608720468421, -0.00114548282967775, 0.00203028038153265, -0.00214706866474885, 0.00648801742696323, 0.00351206872868536, 0.00192669054089329, 0.000376369068538677, 0.000427166536456030, 0.000830487373839234, -0.000655894525747706, 0.000266887426798096, 0.000177201544615822, -0.00122530208178990, 0.000666277794352205, -0.000716505579929662, 0.00241326374207831, 0.00281209418993255, 0.00252197824585186, 0.00230985711738261, -2.32519172317701e-05, -0.000194782802602450, 0.000954779989069827, 0.00149347199524650, 0.000238827039098344, -0.00203406404049488, -0.00105253683874794, -0.00194730598320482, -0.00100171778954059, 0.000805640697017428, 0.000381591132449035, -0.00170154383418972, -0.000631497518992687, 0.000610069534514400, 0.00143797754147420, 0.00291020527912960, 0.000526693059560541, 0.00110062426838930, 0.000848678348758210, 0.00130318480040327, -0.000110981237186913, -0.00138972116159067, -0.00227039392392520, -0.00512268162243537, 1.51682007940828e-05, -0.000442964090444828, -0.000488862669974452, 0.00167642749651656, -0.00470195384875318, -0.00268201776998468, -0.00353619451441884, -0.00210688296135543, -0.00193821914879178, -0.00214737603976851, 0.00348077312385471, 0.000594560933636812, -0.00303316050665356, -0.00131395351137604, 0.000839514272425065, -0.00103006748901671, 0.00213132033838106, -0.000107358262453453, -0.000679465851559117, -0.00101664608903694, 0.00175369535004805, 0.00322202907637554, 0.00334899709136403, 0.00152201727427868, -0.00192979497412297, 0.00168197457567949, 0.00103494887219517, -0.000723966789601261, -0.00117017185722796, -0.000491454299192718, 0.00172545673467267, 0.00226057961177357, -0.00146654344278962, -0.000621885275495581, 0.00144020918714099, -0.000285233623269285, 0.00215025555776206, 0.00320881774182471, -3.50661799908131e-05, -0.00164826989229336, -0.00202456911950719, -0.000719297672332120, -0.00125418449051907, -0.000764016958075765, -0.000859449445088135, -0.000219056832627862, 0.000303298940911538, 0.00144625084660343, -0.00169658680716443, 0.00254957517169311, 0.000324180690557075, 0.00122751178602804, 0.000112741601932957, -0.00121300636979264, 0.00103381505177665, -0.00137707821645235, -0.00176481158673837, -0.00247974014245540, -0.00462887885897586, -0.00243371183016397, -0.00415342501074151, -0.00110277190050603, 0.000822163989777369, -0.00160845996579920, 0.000316226686693431, 0.00222058142044724, -0.000201266852004794, -0.000613088164942791, 0.000507347285568346, -0.00325911071123832, -0.0125492046075582, -0.00509785156938830, -0.000718642009554707, -0.00134455594859796, -0.00311326443424376, -0.000858447422537882, -0.00116267447455729, -0.00115095915873871, -0.000359644155314551, 0.00171858297945460, -0.00601554678195498, -0.00297444856266037, -0.00645285326882296, -0.00425609275522726, -0.00351507764153872, -0.00295212151317229, -0.000311250483326614, -0.00254059229352871, -2.50157790595335e-05, -7.58312717861709e-05, -0.00111796837576912, 0.00244415750999745, 0.000341927566985093, 0.00229539946916535, 0.00117038372092982, 0.000688703142570610, 0.000244594232308489, -3.03914483754894e-05, -0.000641217157558375, 0.000797144479077464, 0.000575599941764434, -0.00119510255606877, -0.00102339540064180, 0.00214689086067251, 0.000727908787248229, -0.00132747202200083, 0.00124430955788003, 0.000543020031724962, 0.000586329500937450, 0.00189236582632784, 0.00274675577099117, 0.000217853421941192, 0.00118309933900864, 0.000390559084173583, 0.00263746354739404, 0.00232035636074863, 0.00222929887042299, 0.00162343962498019, 0.00107876914299830, 0.00240419694889497, -0.000666863510267779, 0.00203978348720895, -0.00175360980819033, -0.00164914481356897, 0.00274260371372360, -0.000726058413589336, 0.00179615953367806, 0.000696828054023604, 0.00183182534325087, 0.000635374707054357, 0.00247267250057133, -0.00197204846407908, -0.00177462526930579, -0.00249915105894143, 0.000259005479520548, 0.00162535528968434, -0.00155716849732781, 0.00181063595513473, 0.000390274536894637, 0.00118764205536071, 2.30690858141438e-05, -0.00126505699094143, -0.00201183361365568, -0.00143640516949558, 0.000314674292588760, -0.00136927302990961, 0.00151930291707732, -0.000627070250743020, -0.00127969494917570, 0.000322450013514852, 0.00146996383564155, -0.000945738481182922, -0.00126205150531792, 0.000150390593741136, 0.000690709193161523, -0.00113719795354718, -0.00169027684930278, 0.00128608574873051, 0.00187332000378092, 0.000212019454935053, -0.000689817051214867, -0.00493607129742699, -0.00173466258307919, 0.00224320018172100, 0.000162448453837597, 0.00199967148528323, -0.000380787990523023, -0.000846963017188554, 0.00238187613888171, -0.00172766755261003, 0.00203676810877542, -0.00342600627562448, -0.00158741644651485, 0.00176129588291758, 0.00105390325868823, 3.67067222532588e-05, -0.000235141644928137, -0.000338773926204395, -0.00117185077227380, 0.000622497043643822, 0.00139913544308350, -0.00210479045659598, -0.00278241829750639, -0.000293917703114112, 0.000790998338788661, 0.00152674241187076, 0.000654487519162558, -0.000706240551749420, 0.00177285668982564, 0.00112128830418379, 0.00267759186903028, -0.00470812723027666, 0.00150511152291712, 0.00150927822610816, 0.00154079798945514, -4.40843814365831e-06, 0.00123875619463240, 0.000677742572948117, 0.00122604943082881, 0.00105180546724725, 0.00285737003160794, 0.000152011066715089, 0.00351223611941058, -9.06421963784901e-05, -0.00153672738433127, -0.00149311996242313, -8.96512743936754e-05, 0.00190612499448361, 0.000141755174775334, 0.00284927246735923, -9.13054964351461e-05, -0.00193013986078868, 0.00155819119537775, -0.00309990985735963, 0.000820130978617928, 0.000491532885895254, 4.05691590500302e-05, 0.00156997228317978, 0.000922211685698669, -0.000152959419779402, 0.000775176274147981, -0.00273426922387473, -0.00180662614155344, -0.00318626632034061, -0.00277081738999345, -0.00374732778596586, -0.00200348041370817, -0.00119533067697940, 0.000239332753364607, 0.000362770355313994, -0.00108886835322116, -0.00126444826984641, 0.000560800531436524, 0.00130670958797018, -0.00124381551058016, -0.000615741044829514, -0.00153452798106316, 0.00142279229998261, 0.00186824916086058, -0.00132451726203717, -0.00146177494386937, -0.00220382347657210, 0.00562926806420699, 0.00227896543208525, -0.000292955331927125, 0.00103116198310307, -0.00375211095187961, -0.000116357067318674, -0.000494370832967180, 0.00176884698909554, 0.00151415043456115, 0.000103276689502608};
			//double cst_blue = 2.54098013914977;

			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );

			Mat _image2,_image3;
			_image1.copyTo(_image2);
			_image1.copyTo(_image3);

			vector<Mat> _image_split;
			split(_image1,_image_split);







			vector<int> startx;
			vector<int> starty;
			vector<int> endx;
			vector<int> endy;
			vector<int> trueer;


			Mat _pointdata =  imread( dir+"/pointdata_sign_red/"+tokens[0]+".bmp", -1 );
			vector<Mat> _pointdata_(3);
			split(_pointdata,_pointdata_);

			for(int ii=0; ii<_pointdata.rows; ii++){
				for(int jj=0; jj<_pointdata.cols; jj++){
					if (_pointdata_[2].at<uchar>(ii,jj)>0) {
						if (_pointdata_[1].at<uchar>(ii,jj)>0) {
							startx.push_back((jj-15)/2);
							starty.push_back((ii-15)/2);
							endx.push_back((jj+15)/2);
							endy.push_back((ii+15)/2);
							trueer.push_back(0);
						}
					}
				}
			}



			int truePositive = 0;
			int falsePositive = 0;



			for(int ii=0; ii<_image1.rows-11; ii++){
				for(int jj=0; jj<_image1.cols-11; jj++){
					vector<int> patch;
					for (int kk=0; kk<11; kk++){
						for (int ll=0; ll<11; ll++){
							patch.push_back(_image_split[2].at<uchar>(ii+kk,jj+ll));
						}
					}
					for (int kk=0; kk<11; kk++){
						for (int ll=0; ll<11; ll++){
							patch.push_back(_image_split[1].at<uchar>(ii+kk,jj+ll));
						}
					}
					for (int kk=0; kk<11; kk++){
						for (int ll=0; ll<11; ll++){
							patch.push_back(_image_split[0].at<uchar>(ii+kk,jj+ll));
						}
					}

					double tsum = cst_blue;
					for (int kk=0; kk<363; kk++) {
						tsum+=patch[kk]*weight_blue[kk];
					}



					if(tsum<0) {
						int truee = 0;
						int kk;
						for (kk=0; kk<startx.size(); kk++) {
							if (jj+5>=startx[kk] && jj+5<=endx[kk]
								&& ii+5>=starty[kk] && ii+5<=endy[kk]) {

								truee = 1;
								break;
							}
						}

						if (truee) {
							circle( _image3,Point (jj+5,ii+5),5,Scalar( 0, 0, 255 ),1,CV_AA );
//							Mat croppedimage;
//							Rect rect (jj,ii,11,11);
//							_image1(rect).copyTo(croppedimage);
//
//							stringstream str;
//							str<<jj<<"_"<<ii<<"_"<<"11_11";
//							imwrite(dir+"/crop_sign_true_blue/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
							trueer[kk]=1;
						} else {
							circle( _image3,Point (jj+5,ii+5),5,Scalar( 0, 255, 0 ),1,CV_AA );
//							Mat croppedimage;
//							Rect rect (jj,ii,11,11);
//							_image1(rect).copyTo(croppedimage);
//
//							stringstream str;
//							str<<jj<<"_"<<ii<<"_"<<"11_11";
//							imwrite(dir+"/crop_sign_false_blue/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
							falsePositive++;
						}
						addWeighted (_image2,0.3,_image3,0.7,0,_image2);
						_image2.copyTo(_image3);


					}


				}
			}


			int col = 1;
			int row = 2;
			Mat merged(_image1.rows*row, _image1.cols*col, CV_8UC3);
			Mat mergePos [col*row];
			for (int k=0; k<row; k++) {
				for (int j=0; j<col; j++) {
					mergePos[j+k*col] = Mat(merged, Rect(_image1.cols*(j%col), _image1.rows*((int)(j/col)+k), _image1.cols, _image1.rows));
				}
			}

//						namedWindow( "a", CV_WINDOW_AUTOSIZE );
//						imshow( "a", _image2);
//						waitKey(0);
			_image1.copyTo(mergePos[0]);
			_image2.copyTo(mergePos[1]);
//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a", merged);
//			waitKey(0);
			//imwrite(dir+"/detect_blue11_min/"+tokens[0]+".png",_image2);
			imwrite(dir+"/detect_red11_min/"+tokens[0]+".png",merged);

			for (int kk=0; kk<startx.size(); kk++ ) {
				truePositive+=trueer[kk];
			}
			cout<<startx.size()<<"\t"<<truePositive<<"\t"<<falsePositive<<endl;



#endif



#ifdef Auto_crop2
			//cout << files[i] <<"\r"<< endl;

			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );

			Mat _pointdata =  imread( dir+"/pointdata_sign/"+tokens[0]+".bmp", -1 );
			vector<Mat> _pointdata_(3);
			split(_pointdata,_pointdata_);

			vector<int> startx;
			vector<int> starty;
			vector<int> endx;
			vector<int> endy;

			for(int ii=0; ii<_pointdata.rows; ii++){
				for(int jj=0; jj<_pointdata.cols; jj++){
					if (_pointdata_[2].at<uchar>(ii,jj)>0) {
						if (_pointdata_[1].at<uchar>(ii,jj)>0) {
							startx.push_back((jj-10)/2);
							starty.push_back((ii-10)/2);
							endx.push_back((jj+10)/2);
							endy.push_back((ii+10)/2);
						}
					}

				}
			}




			vector<int> fendx;
			vector<int> fendy;

			float dist = 0;
			float mindist = 1e100;
			int minind=-1;


			ofstream FileO2;
			stringstream strrr2;
			strrr2<<dir<<"/cropdata_sign11/agg.txt";

			FileO2.open(strrr2.str().c_str(),ios::out|ios::app);



			ofstream FileO;
			char buffer[256];											// use limited buffer
			stringstream strrr;
			strrr<<dir<<"/cropdata_sign11/"<<tokens[0]<<".txt";
				FileO.open(strrr.str().c_str(),ios::out);
				FileO.seekp(ios::beg);

			for(int ii=0; ii<startx.size(); ii++){
				dist = 0;
				mindist = 1e100;
//				for(int jj=0; jj<endx.size(); jj++){
//					if (startx[ii]>endx[jj]) continue;
//					if (starty[ii]>endy[jj]) continue;
//					dist = (endx[jj]-startx[ii])*(endx[jj]-startx[ii])+(endy[jj]-starty[ii])*(endy[jj]-starty[ii]);
//					if (mindist>dist) {
//						mindist = dist;
//						minind = jj;
//					}
//				}
				fendx.push_back(endx[ii]);
				fendy.push_back(endy[ii]);
				cout<<fendx[ii]<<"\t"<<fendy[ii]<<"\t";

			}
			cout<<startx.size()<<"/"<<endx.size()<<"   ";
			cout<<startx.size()<<"/"<<fendx.size()<<endl;
			srand(1);
			int neg_width = 11;
			int neg_height = 11;
			int iiend=1000;
			for(int ii=0; ii<iiend; ii++){
				int x = (float)rand()/RAND_MAX*(_image1.cols-neg_width);
				int y = (float)rand()/RAND_MAX*(_image1.rows-neg_height);
				//cout<<x<<"_"<<y<<"_"<<11<<"_"<<11<<endl;
				int jj;
				for(jj=0; jj<startx.size(); jj++){
					if ((((x-startx[jj])<neg_width) && ((x-startx[jj])>-neg_width)) || (((y-starty[jj])<neg_height) && ((y-starty[jj])>-neg_height))) {
						break;
					}
				}
				if ((((x-startx[jj])<neg_width) && ((x-startx[jj])>-neg_width)) || (((y-starty[jj])<neg_height) && ((y-starty[jj])>-neg_height))) {
					iiend++;
					continue;
				}
				Rect rect (x,y,neg_width,neg_height);
				Mat croppedimage;
				_image1(rect).copyTo(croppedimage);
				stringstream str;
				str<<x<<"_"<<y<<"_"<<neg_width<<"_"<<neg_height;
				//imwrite(dir+"/crop_neg11/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
			}


			for(int ii=0; ii<startx.size(); ii++){
				Mat croppedimage;
				Rect rect (startx[ii],starty[ii],fendx[ii]-startx[ii]+1,fendy[ii]-starty[ii]+1);
				_image1(rect).copyTo(croppedimage);
				stringstream str;
				str<<startx[ii]<<"_"<<starty[ii]<<"_"<<(fendx[ii]-startx[ii]+1)<<"_"<<(fendy[ii]-starty[ii]+1);
				imwrite(dir+"/crop_sign11/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);


				Mat grayy;
				if (croppedimage.type()!= CV_8UC1) cvtColor(croppedimage,grayy, CV_RGB2GRAY);
				int erosion_type = MORPH_RECT;

//				Mat element = getStructuringElement( erosion_type,
//				                                       Size( 3, 3  ),
//				                                       Point( 1,1 ) );
//
				threshold(grayy,grayy,0,255,THRESH_BINARY+THRESH_OTSU);
				 copyMakeBorder( grayy, grayy, 1, 1, 1, 1, BORDER_CONSTANT, 0 );

				vector< vector<Point> > contours; // Vector for storing contour
				    vector<Vec4i> hierarchy;
				    int largest_area=0;
				    int largest_contour_index=0;
				    imwrite(dir+"/crop2_sign11/"+tokens[0]+"_"+str.str()+".bmp",grayy);
				    findContours( grayy, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image

				    for( int i = 0; i< contours.size(); i++ ) {// iterate through each contour.
				        double a=contourArea( contours[i],false);  //  Find the area of contour
				        if(a>largest_area){
				            largest_area=a;
				            largest_contour_index=i;                //Store the index of largest contour

				        }
				    }
				    Rect bounding_rect=boundingRect(contours[largest_contour_index]); // Find the bounding rectangle for biggest contour


//				erode(grayy,grayy,element);
//				dilate(grayy,grayy,element);


				stringstream str2;
				str2<<startx[ii]<<"\t"<<starty[ii]<<"\t"<<(fendx[ii]-startx[ii]+1)<<"\t"<<(fendy[ii]-starty[ii]+1)<<"\r\n";
				FileO.write(str2.str().c_str(),str2.str().size());
				FileO.seekp(0,ios::end);

				stringstream str3;
				str3<<(ii+1)<<"\t"<<tokens[0]<<"\t"<<(fendy[ii]-starty[ii]+1)<<"\t"<<(fendx[ii]-startx[ii]+1)<<"\t"<<(float)(fendy[ii]-starty[ii]+1)/(fendx[ii]-startx[ii]+1)<<"\t"<<startx[ii]<<"\t"<<fendx[ii]<<"\t"<<starty[ii]<<"\t"<<fendy[ii]<<"\t"<<((float)fendx[ii]+startx[ii])/2<<"\t"<<((float)fendy[ii]+starty[ii])/2<<"\t"<<bounding_rect.width<<"\t"<<bounding_rect.height<<"\t"<<"\r\n";
				FileO2.write(str3.str().c_str(),str3.str().size());
				FileO2.seekp(0,ios::end);
			}

			//_image0.convertTo(_image1,CV_8UC1);
			//if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);




//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			//Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//
//			cvNica::Denoise(_image1,_deno1);
//
//			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//
//
//			equalizeHist(_dmqi,_histeq);
//
//
//
//			imwrite(dir+"/mdmqi/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi/"+tokens[0]+"."+dataType+".bad").c_str() );

#endif


#ifdef Auto_crop
			//cout << files[i] <<"\r"<< endl;

			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );

			Mat _pointdata =  imread( dir+"/pointdata/"+tokens[0]+".bmp", -1 );
			vector<Mat> _pointdata_(3);
			split(_pointdata,_pointdata_);

			vector<int> startx;
			vector<int> starty;
			vector<int> endx;
			vector<int> endy;

			for(int ii=0; ii<_pointdata.rows; ii++){
				for(int jj=0; jj<_pointdata.cols; jj++){
					if (_pointdata_[2].at<uchar>(ii,jj)>0) {
						if (_pointdata_[1].at<uchar>(ii,jj)>0) {
							startx.push_back(jj);
							starty.push_back(ii);
							//cout<<startx[startx.size()-1]<<endl;
						} else {
							endx.push_back(jj);
							endy.push_back(ii);
							//cout<<endx[endx.size()-1]<<endl;
						}
					}

				}
			}




			vector<int> fendx;
			vector<int> fendy;

			float dist = 0;
			float mindist = 1e100;
			int minind=-1;


			ofstream FileO2;
			stringstream strrr2;
			strrr2<<dir<<"/cropdata/agg.txt";

			FileO2.open(strrr2.str().c_str(),ios::out|ios::app);



			ofstream FileO;
			char buffer[256];											// use limited buffer
			stringstream strrr;
			strrr<<dir<<"/cropdata/"<<tokens[0]<<".txt";
				FileO.open(strrr.str().c_str(),ios::out);
				FileO.seekp(ios::beg);

			for(int ii=0; ii<startx.size(); ii++){
				dist = 0;
				mindist = 1e100;
				for(int jj=0; jj<endx.size(); jj++){
					if (startx[ii]>endx[jj]) continue;
					if (starty[ii]>endy[jj]) continue;
					dist = (endx[jj]-startx[ii])*(endx[jj]-startx[ii])+(endy[jj]-starty[ii])*(endy[jj]-starty[ii]);
					if (mindist>dist) {
						mindist = dist;
						minind = jj;
					}
				}
				fendx.push_back(endx[minind]);
				fendy.push_back(endy[minind]);
				cout<<fendx[ii]<<"\t"<<fendy[ii]<<"\t";

			}
			cout<<startx.size()<<"/"<<endx.size()<<"   ";
			cout<<startx.size()<<"/"<<fendx.size()<<endl;

			for(int ii=0; ii<startx.size(); ii++){
				Mat croppedimage;
				Rect rect (startx[ii],starty[ii],fendx[ii]-startx[ii]+1,fendy[ii]-starty[ii]+1);
				_image1(rect).copyTo(croppedimage);
				stringstream str;
				str<<startx[ii]<<"_"<<starty[ii]<<"_"<<(fendx[ii]-startx[ii]+1)<<"_"<<(fendy[ii]-starty[ii]+1);
				imwrite(dir+"/crop/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);


				Mat grayy;
				if (croppedimage.type()!= CV_8UC1) cvtColor(croppedimage,grayy, CV_RGB2GRAY);
				int erosion_type = MORPH_RECT;

//				Mat element = getStructuringElement( erosion_type,
//				                                       Size( 3, 3  ),
//				                                       Point( 1,1 ) );
//
				threshold(grayy,grayy,0,255,THRESH_BINARY+THRESH_OTSU);
				 copyMakeBorder( grayy, grayy, 1, 1, 1, 1, BORDER_CONSTANT, 0 );

				vector< vector<Point> > contours; // Vector for storing contour
				    vector<Vec4i> hierarchy;
				    int largest_area=0;
				    int largest_contour_index=0;
				    imwrite(dir+"/crop2/"+tokens[0]+"_"+str.str()+".bmp",grayy);
				    findContours( grayy, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE ); // Find the contours in the image

				    for( int i = 0; i< contours.size(); i++ ) {// iterate through each contour.
				        double a=contourArea( contours[i],false);  //  Find the area of contour
				        if(a>largest_area){
				            largest_area=a;
				            largest_contour_index=i;                //Store the index of largest contour

				        }
				    }
				    Rect bounding_rect=boundingRect(contours[largest_contour_index]); // Find the bounding rectangle for biggest contour


//				erode(grayy,grayy,element);
//				dilate(grayy,grayy,element);


				stringstream str2;
				str2<<startx[ii]<<"\t"<<starty[ii]<<"\t"<<(fendx[ii]-startx[ii]+1)<<"\t"<<(fendy[ii]-starty[ii]+1)<<"\r\n";
				FileO.write(str2.str().c_str(),str2.str().size());
				FileO.seekp(0,ios::end);

				stringstream str3;
				str3<<(ii+1)<<"\t"<<tokens[0]<<"\t"<<(fendy[ii]-starty[ii]+1)<<"\t"<<(fendx[ii]-startx[ii]+1)<<"\t"<<(float)(fendy[ii]-starty[ii]+1)/(fendx[ii]-startx[ii]+1)<<"\t"<<startx[ii]<<"\t"<<fendx[ii]<<"\t"<<starty[ii]<<"\t"<<fendy[ii]<<"\t"<<((float)fendx[ii]+startx[ii])/2<<"\t"<<((float)fendy[ii]+starty[ii])/2<<"\t"<<bounding_rect.width<<"\t"<<bounding_rect.height<<"\t"<<"\r\n";
				FileO2.write(str3.str().c_str(),str3.str().size());
				FileO2.seekp(0,ios::end);
			}

			//_image0.convertTo(_image1,CV_8UC1);
			//if (_image1.type()!= CV_8UC1) cvtColor(_image1, _image1, CV_RGB2GRAY);




//			Size size = _image1.size();
//			Mat _deno1(size,CV_8UC1);
//			//Mat _deno2(size,CV_8UC1);
//			Mat _dmqi(size,CV_8UC1);
//			Mat _histeq(size,CV_8UC1);
//
//			cvNica::Denoise(_image1,_deno1);
//
//			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//
//
//			equalizeHist(_dmqi,_histeq);
//
//
//
//			imwrite(dir+"/mdmqi/"+tokens[0]+"."+dataType,_histeq);
//			if (found!=std::string::npos)
//				rename( string(dir+"/mdmqi/"+tokens[0]+"."+dataType).c_str() , string(dir+"/mdmqi/"+tokens[0]+"."+dataType+".bad").c_str() );

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



#ifdef Auto_crop3


		for (unsigned int i = 0;i < files.size();i++) {
			//cout << files[i] <<"\r"<< endl;

			vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");

			Mat _image1;
			_image1 = imread( dir+"/"+files[i], -1 );

			Mat _pointdata =  imread( dir+"/pointdata_sign_red/"+tokens[0]+".bmp", -1 );
			vector<Mat> _pointdata_(3);
			split(_pointdata,_pointdata_);

			vector<int> startx;
			vector<int> starty;
			vector<int> endx;
			vector<int> endy;
			vector<int> rArr;
			vector<int> gArr;
			vector<int> bArr;

			for(int ii=0; ii<_pointdata.rows; ii++){
				for(int jj=0; jj<_pointdata.cols; jj++){
					if (_pointdata_[2].at<uchar>(ii,jj)>0) {
						if (_pointdata_[1].at<uchar>(ii,jj)>0) {
							startx.push_back((jj-2)/2);
							starty.push_back((ii-2)/2);
							endx.push_back((jj+2)/2);
							endy.push_back((ii+2)/2);
						}
					}

				}
			}

			int cropw = 3;
			int croph = 3;



			vector<int> fendx;
			vector<int> fendy;

			float dist = 0;
			float mindist = 1e100;
			int minind=-1;


			ofstream FileO2;
			stringstream strrr2;
			strrr2<<dir<<"/cropdata_sign5_red/agg2.txt";

			FileO2.open(strrr2.str().c_str(),ios::out|ios::app);



			ofstream FileO;
			char buffer[256];											// use limited buffer
			stringstream strrr;
			strrr<<dir<<"/cropdata_sign5_red/"<<tokens[0]<<".txt";
				FileO.open(strrr.str().c_str(),ios::out);
				FileO.seekp(ios::beg);

			for(int ii=0; ii<startx.size(); ii++){
				dist = 0;
				mindist = 1e100;

				fendx.push_back(endx[ii]);
				fendy.push_back(endy[ii]);
				cout<<fendx[ii]<<"\t"<<fendy[ii]<<"\t";

			}
			cout<<startx.size()<<"/"<<endx.size()<<"   ";
			cout<<startx.size()<<"/"<<fendx.size()<<endl;


			for(int ii=0; ii<startx.size(); ii++){
				Mat croppedimage;
				Rect rect (startx[ii],starty[ii],fendx[ii]-startx[ii]+1,fendy[ii]-starty[ii]+1);
				_image1(rect).copyTo(croppedimage);
				stringstream str;
				str<<startx[ii]<<"_"<<starty[ii]<<"_"<<(fendx[ii]-startx[ii]+1)<<"_"<<(fendy[ii]-starty[ii]+1);
				imwrite(dir+"/crop_sign5_red/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
				vector<Mat> croppedimage_(3);
				split(croppedimage,croppedimage_);
				for (int xx=0;xx<cropw;xx++){
					for (int yy=0;yy<=croph;yy++){
						int zz=rArr.size();
						int rr= croppedimage_[2].at<uchar>(xx,yy);
						int gg= croppedimage_[1].at<uchar>(xx,yy);
						int bb= croppedimage_[0].at<uchar>(xx,yy);
						if(zz==0){
							rArr.push_back(rr);
							gArr.push_back(gg);
							bArr.push_back(bb);

						} else {
							int uu=0;

							for (int vv=0; vv<zz; vv++){
								if (rArr[vv]==rr){
									if(gArr[vv]==gg){
										if(bArr[vv]==bb){
											uu=1;
											break;
										}
									}
								}
							}
							if (uu==0){
								rArr.push_back(rr);
								gArr.push_back(gg);
								bArr.push_back(bb);
							} else {
								cout<<zz<<endl;
							}
						}
					}
				}


			}



		cout<<rArr.size()<<endl;
		int zz=rArr.size();
		//for (unsigned int i = 0;i < files.size();i++) {
					//cout << files[i] <<"\r"<< endl;


					vector<Mat> _image1_(3);
					split(_image1,_image1_);


					Mat _distmap(_image1.size(),CV_32FC1);

					float mindist_ = 1e100;
					float maxdist_ = 0;
					for(int ii=0; ii<_image1.rows; ii++){
						for(int jj=0; jj<_image1.cols; jj++){
							int rr= _image1_[2].at<uchar>(ii,jj);
							int gg= _image1_[1].at<uchar>(ii,jj);
							int bb= _image1_[0].at<uchar>(ii,jj);
							float kk=0;
							for (int vv=0; vv<zz; vv++){
								kk+=sqrt((rArr[vv]-rr)*(rArr[vv]-rr)+
										 (gArr[vv]-gg)*(gArr[vv]-gg)+
										 (bArr[vv]-bb)*(bArr[vv]-bb));

							}
							if(kk<mindist_) mindist_=kk;
							if(kk>maxdist_) maxdist_=kk;

							_distmap.at<float>(ii,jj) = kk;

						}
					}
					cout<<mindist<<" "<<maxdist_<<endl;
					_distmap-=mindist_;
					_distmap/=(maxdist_-mindist_);
					//namedWindow( "a", CV_WINDOW_AUTOSIZE );
					//imshow( "a", _distmap );
//								namedWindow( "b", CV_WINDOW_AUTOSIZE );
//								imshow( "b", _image1 );
					//waitKey(0);

					for(int ii=0; ii<_pointdata.rows; ii++){
						for(int jj=0; jj<_pointdata.cols; jj++){
							if (_pointdata_[2].at<uchar>(ii,jj)>0) {
								if (_pointdata_[1].at<uchar>(ii,jj)>0) {

									rectangle(_distmap,Rect(jj/2-6,ii/2-6,13,13),1,CV_FILLED);
									circle( _image1,Point (jj/2,ii/2),5,Scalar( 0,255,0 ),1,CV_AA );

								}
							}

						}
					}



					int neg_width=11;
					int neg_height=11;
					Rect rect2 (5,5,_image1.cols-10,_image1.rows-10);

					for (int ii=0; ii<2000; ii++) {
						Mat croppedimage;
						double minval;
						double maxval;
						Point minPoint;
						Point maxPoint;
						Mat _distmap_crop;

						_distmap(rect2).copyTo(_distmap_crop);
						minMaxLoc(_distmap_crop,&minval,&maxval,&minPoint,&maxPoint);
						//rectangle(_distmap,Rect(minPoint.x,minPoint.y,neg_width,neg_height),1,CV_FILLED);
						rectangle(_distmap,Rect(minPoint.x,minPoint.y,11,11),1,CV_FILLED);
						if (minPoint.x<0) break;
						if (minPoint.y<0) break;
						cout<<"f: "<<minPoint.x<<" "<<minPoint.y<<endl;

						stringstream str;
						str<<minPoint.x<<"_"<<minPoint.y<<"_"<<neg_width<<"_"<<neg_height;

						Rect rect (minPoint.x,minPoint.y,neg_width,neg_height);
						_image1(rect).copyTo(croppedimage);


						imwrite(dir+"/crop_neg11_min_red/"+tokens[0]+"_"+str.str()+".bmp",croppedimage);
					}

								//namedWindow( "a", CV_WINDOW_AUTOSIZE );
								//imshow( "a", _distmap );
//								namedWindow( "b", CV_WINDOW_AUTOSIZE );
//								imshow( "b", _image1 );
								//waitKey(0);

		}

#endif


#ifdef Fileout
		t = ((double)getTickCount() - t)/getTickFrequency();
		cout << "filtering finish.\nelapsed time : " << t << " sec" << endl;
		FileOut.close();
#endif

#ifdef PCAP

		FilePcap2TS.close();
		FilePcap2ES.close();
		File2642yuv.close();
		Filets2yuv.close();
		FileList.close();
		FileListenc.close();

#endif

	return 0;
}
#endif



#ifdef PCA_

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;


// Reads the images and labels from a given CSV file, a valid file would
// look like this:
//
//      /path/to/person0/image0.jpg;0
//      /path/to/person0/image1.jpg;0
//      /path/to/person1/image0.jpg;1
//      /path/to/person1/image1.jpg;1
//      ...
//
void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if(!file)
        throw std::exception();
    std::string line, path, classlabel;
    // For each line in the given file:
    while (std::getline(file, line)) {
        // Get the current line:
        std::stringstream liness(line);
        // Split it at the semicolon:
        std::getline(liness, path, ';');
        std::getline(liness, classlabel);
        // And push back the data into the result vectors:
        images.push_back(imread(path, IMREAD_GRAYSCALE));
        labels.push_back(atoi(classlabel.c_str()));
    }
}

// Normalizes a given image into a value range between 0 and 255.
Mat norm_0_255(const Mat& src) {
    // Create and return normalized image:
    Mat dst;
    switch(src.channels()) {
    case 1:
        cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC1);
        break;
    case 3:
        cv::normalize(src, dst, 0, 255, NORM_MINMAX, CV_8UC3);
        break;
    default:
        src.copyTo(dst);
        break;
    }
    return dst;
}

// Converts the images given in src into a row matrix.
Mat asRowMatrix(const vector<Mat>& src, int rtype, double alpha = 1, double beta = 0) {
    // Number of samples:
    size_t n = src.size();
    // Return empty matrix if no matrices given:
    if(n == 0)
        return Mat();
    // dimensionality of (reshaped) samples
    size_t d = src[0].total();
    // Create resulting data matrix:
    Mat data(n, d, rtype);
    // Now copy data:
    for(int i = 0; i < n; i++) {
        //
        if(src[i].empty()) {
            string error_message = format("Image number %d was empty, please check your input data.", i);
            CV_Error(CV_StsBadArg, error_message);
        }
        // Make sure data can be reshaped, throw a meaningful exception if not!
        if(src[i].total() != d) {
            string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src[i].total());
            CV_Error(CV_StsBadArg, error_message);
        }
        // Get a hold of the current row:
        Mat xi = data.row(i);
        // Make reshape happy by cloning for non-continuous matrices:
        if(src[i].isContinuous()) {
            src[i].reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        } else {
            src[i].clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
        }
    }
    return data;
}

int main(int argc, const char *argv[]) {


    // Holds some images:
    vector<Mat> db;

    // Load the greyscale images. The images in the example are
    // taken from the AT&T Facedatabase, which is publicly available
    // at:
    //
    //      http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html
    //
    // This is the path to where I stored the images, yours is different!
    //
    string prefix = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/kwonTT/smqi/";








    db.push_back(imread(prefix + "00001fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00002fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00003fa010_930831.bmp", IMREAD_GRAYSCALE));

    db.push_back(imread(prefix + "00004fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00005fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00006fa010_930831.bmp", IMREAD_GRAYSCALE));

    db.push_back(imread(prefix + "00007fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00008fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00009fa010_930831.bmp", IMREAD_GRAYSCALE));

    db.push_back(imread(prefix + "00010fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00011fa010_930831.bmp", IMREAD_GRAYSCALE));
    db.push_back(imread(prefix + "00012fa010_930831.bmp", IMREAD_GRAYSCALE));

    // The following would read the images from a given CSV file
    // instead, which would look like:
    //
    //      /path/to/person0/image0.jpg;0
    //      /path/to/person0/image1.jpg;0
    //      /path/to/person1/image0.jpg;1
    //      /path/to/person1/image1.jpg;1
    //      ...
    //
    // Uncomment this to load from a CSV file:
    //

    /*
    vector<int> labels;
    read_csv("/home/philipp/facerec/data/at.txt", db, labels);
    */
    //prefix = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/kwonTT/smqi/";

    // Build a matrix with the observations in row:
    Mat data = asRowMatrix(db, CV_32FC1);

    // Number of components to keep for the PCA:
    int num_components = 10;

    // Perform a PCA:
    PCA pca(data, Mat(), CV_PCA_DATA_AS_ROW, num_components);


    Mat df = imread(prefix + "01014ba010_960521.bmp", IMREAD_GRAYSCALE);
    Mat reconstructed;
	Mat vec = df.reshape(1,1), coeffs;
	pca.project(vec, coeffs);
	pca.backProject(coeffs, reconstructed);
	Mat vec2;
	vec.convertTo(vec2,CV_32FC1);

	  Mat df2 = imread(prefix + "01014bk010_960521.bmp", IMREAD_GRAYSCALE);
	    Mat reconstructed2;
		Mat vec3 = df2.reshape(1,1), coeffs2;
		pca.project(vec3, coeffs2);
		pca.backProject(coeffs2, reconstructed2);
		Mat vec4;
		vec3.convertTo(vec4,CV_32FC1);


	Mat result,result2;
	matchTemplate(df, df2, result2,CV_TM_CCOEFF_NORMED);
	matchTemplate(coeffs, coeffs2, result,CV_TM_CCOEFF_NORMED);
	cout<<"d:"<<result.at<float>(0,0)<<endl;
	cout<<"d:"<<result2.at<float>(0,0)<<endl;
	printf("%d. diff = %g\n", 1, norm(vec2, reconstructed, NORM_L2));


    // And copy the PCA results:
    Mat mean = pca.mean.clone();
    Mat eigenvalues = pca.eigenvalues.clone();
    Mat eigenvectors = pca.eigenvectors.clone();




    namedWindow( "avg", CV_WINDOW_AUTOSIZE );
    namedWindow( "pc1", CV_WINDOW_AUTOSIZE );
    namedWindow( "pc2", CV_WINDOW_AUTOSIZE );
    namedWindow( "pc3", CV_WINDOW_AUTOSIZE );
    namedWindow( "pc4", CV_WINDOW_AUTOSIZE );
    namedWindow( "pc5", CV_WINDOW_AUTOSIZE );
    namedWindow( "pc6", CV_WINDOW_AUTOSIZE );
    // The mean face:
    imshow("avg", norm_0_255(mean.reshape(1, db[0].rows)));

    // The first three eigenfaces:
    imshow("pc1", norm_0_255(pca.eigenvectors.row(0)).reshape(1, db[0].rows));
    imshow("pc2", norm_0_255(pca.eigenvectors.row(1)).reshape(1, db[0].rows));
    imshow("pc3", norm_0_255(pca.eigenvectors.row(2)).reshape(1, db[0].rows));
    imshow("pc4", norm_0_255(pca.eigenvectors.row(3)).reshape(1, db[0].rows));
    imshow("pc5", norm_0_255(pca.eigenvectors.row(4)).reshape(1, db[0].rows));
    imshow("pc6", norm_0_255(pca.eigenvectors.row(5)).reshape(1, db[0].rows));




    // Show the images:
    waitKey(0);




    // Success!
    return 0;
}



#endif



#ifdef faceDetection

int main(int argc, char* argv[] ){


	 String face_cascade_name = "haarcascade_frontalface_mine.xml";
	 //1340 757 583

	 //String face_cascade_name = "haarcascade_frontalface_alt.xml";



	 CascadeClassifier face_cascade;
	 string window_name = "Capture - Face detection";
	 if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "JPG";
	else dataType = "bmp";

		string dir = string(argv[1]);
		//dir = "/cygdrive/e/4/5/";
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();


		//dir = "../tutorial-haartraining/CMU-MIT_Face_Test_Set/test";
		dir = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/BAO/myDataBase";
		dataType = "jpg";

		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif



	cout<<"d dfd "<<files.size()<<endl;

	int detect [865] = {0};
	int totalWindow = 0;
	int correct = 0;
	int falsePositive = 0;

	for (int i = 0;i < files.size();i++) {
		cout<<"d dfd: "<<dir+"/"+files[i]<<endl;
		Mat frame = imread( dir+"/"+files[i], -1 );
		Size size = frame.size();

//		imshow( window_name, frame );
//				  waitKey(0);

		std::vector<Rect> faces;
		//Mat frame_gray=frame;
		Mat frame_gray;

		cvtColor( frame, frame_gray, CV_BGR2GRAY );
		//equalizeHist( frame_gray, frame_gray );

		 //-- Detect faces
	    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(20, 20) , Size(150, 150) );


	    //	    cout<<"d dfd "<<faces.size()<<endl;
	    totalWindow += faces.size();
//	    for (int k=0; k<865; k++) {
//			if (bao[k][0] == baoFileList[i]) {
//				Point truecenter (bao[k][1], bao[k][2]);
//				ellipse( frame, truecenter, Size( 10, 10), 0, 0, 360, Scalar( 0, 255, 255 ), 4, 8, 0 );
//			}
//	    }

		for( uint j = 0; j < faces.size(); j++ )
		{
		    Point center( faces[j].x + faces[j].width*0.5, faces[j].y + faces[j].height*0.5 );
//		    ellipse( frame, center, Size( faces[j].width*0.5, faces[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );


		    int counts = 0;
		    int pos = -1;
		    for (int k=0; k<865; k++) {

		    	if (bao[k][0] == baoFileList[i]) {
		    		Point truecenter (bao[k][1], bao[k][2]);


		    		double dist = norm(truecenter-center);
		    		//cout<<dist<<" "<<faces[j].width*0.5<<endl;
		    		if (dist < faces[j].width*0.5) {
		    			counts ++;
		    			pos = k;
		    		}
		    		if (counts>1) break;
		    	}

		    }
	    	if (counts == 1) {
	    		if (detect[pos]==1) {
					totalWindow -= 1;
				} else {
					detect[pos] = 1;
				}
	    	} else if (counts > 1) {
	    		falsePositive += 1;
	    	} else {
	    		falsePositive += 1;
	    	}
		}
		//-- Show what you got
//		correct=0;
//		for (int k=0; k<865; k++) {
//					correct += detect[k];
//				}
//				cout<<"total window = "<<totalWindow<<endl;
//				cout<<"correctly detected = "<<correct<<endl;
//				cout<<"false positive = "<<falsePositive<<endl;
//
//		namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//		imshow( window_name, frame );
//		waitKey(0);

	}
	for (int k=0; k<865; k++) {
		correct += detect[k];
	}


	cout<<"total window = "<<totalWindow<<endl;
	cout<<"correctly detected = "<<correct<<endl;
	cout<<"false positive = "<<falsePositive<<endl;

}

#endif

#ifdef faceDetection3
int baoFileList [100] = {
		1, 10, 100, 11, 12, 13, 14, 15, 16, 17, 18,
		19, 2, 20, 21, 22, 23, 24, 25, 26, 27, 28,
		29, 3, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 4, 40, 41, 42, 43, 44, 45, 46, 47, 48,
		49, 5, 50, 51, 52, 53, 54, 55, 56, 57, 58,
		59, 6, 60, 61, 62, 63, 64, 65, 66, 67, 68,
		69, 7, 70, 71, 72, 73, 74, 75, 76, 77, 78,
		79, 8, 80, 81, 82, 83, 84, 85, 86, 87, 88,
		89, 9, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

int baocount [100] = {
		14, 7, 7, 15, 7, 17, 21, 18, 4, 8,
		7, 8, 4, 4, 4, 8, 11, 4, 3, 4, 7,
		2, 7, 7, 4, 14, 8, 10, 10, 9, 6,
		7, 3, 6, 4, 4, 4, 3, 3, 6, 7, 8,
		10, 6, 6, 5, 5, 15, 6, 7, 4, 4, 9,
		3, 5, 14, 5, 3, 3, 10, 5, 10, 7, 3,
		30, 5, 31, 5, 2, 3, 2, 6, 17, 9, 9,
		12, 12, 9, 9, 3, 24, 23, 12, 17, 3, 4, 5, 3};

int bao [865][3] = {
		{1, 287, 29},
		{1, 419, 24},
		{1, 276, 98},
		{1, 273, 187},
		{1, 384, 221},
		{1, 469, 144},
		{1, 533, 179},
		{1, 288, 325},
		{1, 593, 321},
		{1, 322, 426},
		{1, 455, 534},
		{1, 673, 451},
		{2, 160, 73},
		{2, 349, 66},
		{2, 145, 173},
		{2, 140, 315},
		{2, 299, 347},
		{2, 419, 237},
		{2, 512, 284},
		{2, 162, 495},
		{2, 598, 488},
		{3, 133, 99},
		{3, 574, 92},
		{3, 184, 243},
		{3, 374, 396},
		{3, 685, 280},
		{4, 150, 151},
		{4, 269, 141},
		{4, 389, 116},
		{4, 515, 140},
		{4, 627, 164},
		{5, 18, 165},
		{5, 90, 168},
		{5, 173, 180},
		{5, 265, 179},
		{5, 352, 182},
		{5, 449, 176},
		{5, 555, 147},
		{5, 632, 176},
		{5, 708, 179},
		{5, 776, 180},
		{5, 109, 275},
		{5, 215, 257},
		{5, 335, 240},
		{5, 441, 265},
		{5, 539, 252},
		{5, 624, 267},
		{5, 721, 256},
		{6, 15, 155},
		{6, 90, 157},
		{6, 169, 171},
		{6, 263, 172},
		{6, 347, 177},
		{6, 448, 172},
		{6, 556, 143},
		{6, 632, 174},
		{6, 706, 177},
		{6, 780, 182},
		{6, 106, 264},
		{6, 211, 248},
		{6, 332, 234},
		{6, 437, 260},
		{6, 536, 244},
		{6, 623, 263},
		{6, 716, 257},
		{7, 147, 54},
		{7, 207, 53},
		{7, 268, 56},
		{7, 323, 66},
		{7, 383, 59},
		{7, 437, 72},
		{7, 490, 86},
		{7, 553, 79},
		{7, 112, 101},
		{7, 166, 95},
		{7, 210, 120},
		{7, 285, 100},
		{7, 349, 106},
		{7, 416, 120},
		{7, 472, 123},
		{7, 526, 122},
		{7, 589, 105},
		{7, 84, 154},
		{7, 61, 236},
		{7, 147, 228},
		{7, 144, 171},
		{7, 211, 185},
		{7, 271, 222},
		{7, 276, 178},
		{7, 342, 168},
		{7, 386, 222},
		{7, 399, 181},
		{7, 452, 170},
		{7, 473, 202},
		{7, 512, 176},
		{7, 544, 224},
		{7, 601, 162},
		{7, 622, 185},
		{8, 149, 294},
		{8, 264, 333},
		{8, 407, 273},
		{8, 391, 394},
		{8, 560, 271},
		{8, 588, 406},
		{8, 679, 307},
		{8, 759, 405},
		{8, 851, 281},
		{8, 931, 321},
		{8, 1095, 248},
		{8, 1052, 390},
		{9, 146, 223},
		{9, 205, 185},
		{9, 278, 237},
		{9, 310, 161},
		{9, 372, 219},
		{9, 432, 210},
		{9, 494, 215},
		{9, 562, 189},
		{9, 635, 190},
		{10, 163, 225},
		{10, 305, 210},
		{10, 380, 141},
		{10, 444, 216},
		{10, 549, 114},
		{10, 659, 129},
		{10, 766, 111},
		{10, 887, 172},
		{10, 1023, 174},
		{10, 1147, 149},
		{10, 1211, 154},
		{10, 1351, 104},
		{11, 102, 89},
		{11, 131, 67},
		{11, 187, 49},
		{11, 216, 96},
		{11, 278, 47},
		{11, 285, 98},
		{11, 338, 55},
		{11, 398, 99},
		{11, 446, 55},
		{12, 93, 259},
		{12, 210, 226},
		{12, 261, 246},
		{12, 300, 314},
		{12, 349, 240},
		{12, 353, 181},
		{12, 448, 204},
		{12, 511, 230},
		{12, 574, 240},
		{12, 606, 304},
		{12, 736, 214},
		{13, 78, 71},
		{13, 143, 202},
		{13, 160, 93},
		{13, 172, 50},
		{13, 197, 84},
		{13, 256, 201},
		{13, 254, 102},
		{13, 257, 58},
		{13, 310, 112},
		{13, 329, 74},
		{13, 351, 105},
		{13, 362, 208},
		{13, 411, 76},
		{13, 427, 116},
		{14, 148, 100},
		{14, 236, 58},
		{14, 268, 280},
		{14, 303, 124},
		{14, 376, 93},
		{14, 431, 109},
		{14, 390, 269},
		{15, 140, 232},
		{15, 251, 160},
		{15, 412, 200},
		{15, 573, 154},
		{15, 737, 164},
		{15, 862, 212},
		{15, 966, 268},
		{16, 233, 246},
		{16, 304, 306},
		{16, 432, 326},
		{16, 315, 706},
		{16, 520, 614},
		{16, 608, 251},
		{16, 739, 247},
		{16, 744, 489},
		{16, 807, 244},
		{16, 876, 290},
		{16, 990, 267},
		{16, 1071, 242},
		{16, 1114, 276},
		{16, 1238, 206},
		{16, 1318, 236},
		{17, 172, 194},
		{17, 231, 125},
		{17, 399, 159},
		{17, 420, 367},
		{17, 584, 129},
		{17, 673, 268},
		{17, 846, 119},
		{18, 131, 228},
		{18, 192, 222},
		{18, 244, 253},
		{18, 295, 239},
		{18, 358, 220},
		{18, 407, 248},
		{18, 472, 258},
		{18, 525, 236},
		{18, 585, 245},
		{18, 655, 238},
		{18, 726, 226},
		{18, 125, 392},
		{18, 223, 362},
		{18, 326, 349},
		{18, 470, 370},
		{18, 577, 388},
		{18, 684, 402},
		{19, 117, 152},
		{19, 161, 172},
		{19, 218, 151},
		{19, 244, 274},
		{19, 267, 142},
		{19, 326, 126},
		{19, 347, 277},
		{19, 390, 147},
		{19, 428, 118},
		{19, 470, 301},
		{19, 480, 178},
		{19, 506, 109},
		{19, 560, 190},
		{19, 556, 305},
		{19, 606, 97},
		{19, 649, 180},
		{19, 651, 309},
		{19, 739, 266},
		{19, 712, 124},
		{19, 784, 106},
		{19, 846, 107},
		{20, 149, 239},
		{20, 223, 234},
		{20, 275, 237},
		{20, 316, 257},
		{20, 378, 255},
		{20, 336, 313},
		{20, 418, 310},
		{20, 442, 351},
		{20, 482, 290},
		{20, 561, 323},
		{20, 481, 394},
		{20, 89, 437},
		{20, 197, 385},
		{20, 269, 450},
		{20, 356, 445},
		{20, 434, 466},
		{20, 480, 396},
		{20, 586, 457},
		{21, 206, 215},
		{21, 317, 197},
		{21, 452, 167},
		{21, 574, 161},
		{22, 124, 67},
		{22, 227, 83},
		{22, 78, 164},
		{22, 174, 167},
		{22, 273, 155},
		{22, 77, 271},
		{22, 165, 291},
		{22, 247, 261},
		{23, 124, 116},
		{23, 176, 220},
		{23, 284, 142},
		{23, 414, 214},
		{23, 492, 118},
		{23, 650, 229},
		{23, 647, 134},
		{24, 55, 254},
		{24, 217, 135},
		{24, 268, 238},
		{24, 376, 158},
		{24, 507, 230},
		{24, 583, 133},
		{24, 740, 151},
		{24, 741, 245},
		{25, 287, 204},
		{25, 406, 172},
		{25, 635, 154},
		{25, 689, 185},
		{26, 176, 179},
		{26, 371, 151},
		{26, 518, 183},
		{26, 671, 144},
		{27, 101, 306},
		{27, 265, 200},
		{27, 475, 251},
		{27, 626, 292},
		{28, 194, 102},
		{28, 297, 66},
		{28, 381, 88},
		{28, 529, 110},
		{28, 647, 129},
		{28, 237, 242},
		{28, 412, 247},
		{28, 602, 260},
		{29, 51, 148},
		{29, 127, 112},
		{29, 284, 128},
		{29, 457, 130},
		{29, 593, 168},
		{29, 674, 130},
		{29, 748, 199},
		{29, 110, 392},
		{29, 278, 343},
		{29, 465, 374},
		{29, 670, 420},
		{30, 101, 149},
		{30, 170, 103},
		{30, 261, 124},
		{30, 325, 142},
		{31, 214, 124},
		{31, 392, 202},
		{31, 612, 168},
		{32, 180, 302},
		{32, 267, 234},
		{32, 498, 281},
		{32, 699, 276},
		{33, 51, 144},
		{33, 222, 120},
		{33, 446, 72},
		{33, 79, 255},
		{33, 282, 245},
		{33, 468, 232},
		{33, 541, 182},
		{34, 203, 140},
		{34, 253, 119},
		{35, 46, 137},
		{35, 135, 130},
		{35, 198, 185},
		{35, 373, 169},
		{35, 503, 191},
		{35, 626, 209},
		{35, 754, 153},
		{36, 109, 183},
		{36, 213, 151},
		{36, 320, 145},
		{36, 375, 86},
		{36, 530, 136},
		{36, 577, 81},
		{36, 653, 119},
		{37, 173, 324},
		{37, 365, 266},
		{37, 550, 258},
		{37, 647, 151},
		{38, 29, 181},
		{38, 147, 166},
		{38, 218, 147},
		{38, 281, 187},
		{38, 385, 168},
		{38, 495, 162},
		{38, 584, 183},
		{38, 672, 183},
		{38, 755, 179},
		{38, 142, 364},
		{38, 255, 349},
		{38, 397, 382},
		{38, 517, 372},
		{38, 633, 322},
		{39, 145, 130},
		{39, 318, 111},
		{39, 422, 84},
		{39, 517, 138},
		{39, 674, 110},
		{39, 314, 408},
		{39, 477, 381},
		{39, 689, 432},
		{40, 101, 103},
		{40, 205, 75},
		{40, 302, 132},
		{40, 459, 103},
		{40, 619, 96},
		{40, 749, 133},
		{40, 94, 401},
		{40, 264, 375},
		{40, 474, 426},
		{40, 652, 410},
		{41, 128, 87},
		{41, 244, 61},
		{41, 374, 93},
		{41, 415, 95},
		{41, 468, 105},
		{41, 566, 90},
		{41, 655, 85},
		{41, 263, 302},
		{41, 400, 293},
		{41, 495, 314},
		{42, 79, 74},
		{42, 107, 421},
		{42, 266, 119},
		{42, 325, 121},
		{42, 302, 406},
		{42, 400, 137},
		{42, 437, 436},
		{42, 537, 115},
		{42, 666, 110},
		{43, 133, 285},
		{43, 242, 294},
		{43, 386, 273},
		{43, 512, 141},
		{43, 536, 318},
		{43, 625, 216},
		{44, 68, 174},
		{44, 258, 179},
		{44, 436, 125},
		{44, 548, 174},
		{44, 678, 191},
		{44, 178, 430},
		{44, 440, 386},
		{45, 278, 211},
		{45, 398, 250},
		{45, 525, 175},
		{46, 225, 100},
		{46, 446, 114},
		{46, 610, 96},
		{46, 191, 246},
		{46, 369, 253},
		{46, 616, 242},
		{47, 153, 119},
		{47, 340, 179},
		{47, 509, 130},
		{47, 714, 116},
		{48, 44, 125},
		{48, 242, 132},
		{48, 408, 154},
		{48, 642, 132},
		{49, 199, 130},
		{49, 360, 143},
		{49, 485, 132},
		{49, 324, 310},
		{50, 167, 128},
		{50, 238, 151},
		{50, 316, 105},
		{51, 241, 232},
		{51, 406, 167},
		{51, 516, 188},
		{52, 127, 115},
		{52, 334, 162},
		{52, 510, 159},
		{52, 652, 163},
		{52, 296, 360},
		{52, 574, 320},
		{53, 80, 158},
		{53, 220, 165},
		{53, 385, 157},
		{53, 569, 130},
		{53, 716, 141},
		{53, 143, 321},
		{53, 448, 329},
		{54, 81, 164},
		{54, 257, 157},
		{54, 400, 164},
		{54, 565, 156},
		{54, 746, 130},
		{54, 43, 361},
		{54, 322, 321},
		{54, 628, 328},
		{55, 92, 125},
		{55, 183, 104},
		{55, 273, 78},
		{55, 298, 158},
		{55, 340, 75},
		{55, 426, 111},
		{55, 479, 78},
		{55, 543, 163},
		{55, 555, 94},
		{55, 674, 69},
		{56, 124, 98},
		{56, 284, 131},
		{56, 433, 115},
		{56, 542, 123},
		{56, 96, 448},
		{56, 324, 413},
		{57, 53, 270},
		{57, 195, 233},
		{57, 348, 187},
		{57, 462, 236},
		{57, 591, 230},
		{57, 752, 251},
		{58, 115, 109},
		{58, 284, 89},
		{58, 430, 79},
		{58, 159, 354},
		{58, 348, 359},
		{59, 70, 174},
		{59, 236, 182},
		{59, 399, 141},
		{59, 566, 182},
		{59, 705, 204},
		{60, 195, 141},
		{60, 332, 143},
		{60, 471, 180},
		{60, 558, 129},
		{60, 616, 196},
		{60, 664, 180},
		{60, 753, 218},
		{60, 755, 132},
		{60, 116, 213},
		{60, 80, 372},
		{60, 275, 312},
		{60, 353, 234},
		{60, 455, 319},
		{60, 537, 251},
		{60, 627, 319},
		{61, 81, 158},
		{61, 277, 115},
		{61, 510, 143},
		{61, 695, 212},
		{61, 286, 373},
		{61, 556, 390},
		{62, 57, 124},
		{62, 198, 169},
		{62, 415, 141},
		{62, 602, 119},
		{62, 737, 117},
		{62, 242, 414},
		{62, 648, 369},
		{63, 103, 137},
		{63, 322, 107},
		{63, 492, 184},
		{63, 699, 205},
		{64, 131, 187},
		{64, 251, 165},
		{64, 372, 207},
		{64, 675, 181},
		{65, 68, 159},
		{65, 237, 149},
		{65, 395, 150},
		{65, 546, 114},
		{65, 690, 158},
		{65, 135, 388},
		{65, 334, 390},
		{65, 565, 419},
		{65, 723, 418},
		{66, 183, 235},
		{66, 398, 208},
		{66, 613, 243},
		{67, 156, 213},
		{67, 220, 160},
		{67, 352, 162},
		{67, 494, 140},
		{67, 622, 166},
		{68, 41, 155},
		{68, 154, 142},
		{68, 249, 132},
		{68, 276, 187},
		{68, 305, 88},
		{68, 347, 162},
		{68, 403, 131},
		{68, 437, 194},
		{68, 512, 147},
		{68, 553, 119},
		{68, 586, 216},
		{68, 649, 163},
		{68, 703, 117},
		{68, 763, 179},
		{69, 206, 240},
		{69, 352, 215},
		{69, 538, 128},
		{69, 484, 310},
		{69, 622, 277},
		{70, 198, 491},
		{70, 438, 134},
		{70, 525, 180},
		{71, 227, 203},
		{71, 319, 189},
		{71, 415, 205},
		{72, 54, 152},
		{72, 185, 206},
		{72, 307, 89},
		{72, 436, 200},
		{72, 561, 147},
		{72, 646, 236},
		{72, 103, 410},
		{72, 271, 431},
		{72, 472, 423},
		{72, 664, 412},
		{73, 106, 190},
		{73, 219, 177},
		{73, 312, 189},
		{73, 360, 145},
		{73, 433, 179},
		{74, 27, 200},
		{74, 87, 170},
		{74, 160, 188},
		{74, 227, 201},
		{74, 287, 149},
		{74, 359, 156},
		{74, 407, 205},
		{74, 520, 186},
		{74, 615, 152},
		{74, 703, 155},
		{75, 93, 211},
		{75, 182, 161},
		{75, 350, 145},
		{75, 332, 257},
		{75, 507, 247},
		{75, 529, 100},
		{75, 690, 185},
		{76, 156, 129},
		{76, 282, 203},
		{76, 438, 191},
		{77, 19, 185},
		{77, 12, 252},
		{77, 63, 240},
		{77, 86, 139},
		{77, 96, 264},
		{77, 112, 196},
		{77, 147, 217},
		{77, 163, 129},
		{77, 201, 247},
		{77, 219, 153},
		{77, 237, 223},
		{77, 275, 133},
		{77, 282, 191},
		{77, 308, 250},
		{77, 320, 163},
		{77, 332, 221},
		{77, 371, 163},
		{77, 421, 241},
		{77, 423, 139},
		{77, 460, 177},
		{77, 494, 198},
		{77, 501, 141},
		{77, 521, 222},
		{77, 550, 174},
		{77, 593, 161},
		{77, 597, 216},
		{77, 632, 177},
		{77, 643, 250},
		{77, 685, 212},
		{77, 748, 237},
		{78, 85, 380},
		{78, 210, 223},
		{78, 472, 208},
		{78, 611, 248},
		{78, 698, 314},
		{79, 9, 141},
		{79, 44, 24},
		{79, 52, 86},
		{79, 83, 179},
		{79, 93, 291},
		{79, 128, 113},
		{79, 145, 63},
		{79, 157, 23},
		{79, 169, 186},
		{79, 205, 51},
		{79, 221, 119},
		{79, 245, 350},
		{79, 256, 171},
		{79, 276, 85},
		{79, 313, 128},
		{79, 348, 301},
		{79, 360, 48},
		{79, 401, 379},
		{79, 405, 138},
		{79, 435, 62},
		{79, 459, 182},
		{79, 506, 298},
		{79, 533, 156},
		{79, 539, 91},
		{79, 562, 412},
		{79, 612, 69},
		{79, 621, 163},
		{79, 687, 65},
		{79, 707, 193},
		{79, 712, 349},
		{79, 778, 96},
		{80, 147, 199},
		{80, 273, 191},
		{80, 395, 167},
		{80, 546, 170},
		{80, 661, 171},
		{81, 201, 142},
		{81, 586, 254},
		{82, 145, 153},
		{82, 307, 185},
		{82, 557, 140},
		{83, 116, 109},
		{83, 196, 61},
		{84, 208, 146},
		{84, 173, 333},
		{84, 296, 324},
		{84, 353, 230},
		{84, 437, 316},
		{84, 621, 196},
		{85, 131, 93},
		{85, 191, 90},
		{85, 242, 121},
		{85, 296, 104},
		{85, 360, 88},
		{85, 407, 113},
		{85, 471, 125},
		{85, 524, 104},
		{85, 583, 112},
		{85, 655, 105},
		{85, 724, 95},
		{85, 127, 259},
		{85, 224, 228},
		{85, 323, 217},
		{85, 469, 237},
		{85, 577, 254},
		{85, 684, 267},
		{86, 167, 91},
		{86, 288, 80},
		{86, 391, 143},
		{86, 495, 111},
		{86, 620, 79},
		{86, 718, 132},
		{86, 155, 424},
		{86, 352, 360},
		{86, 554, 337},
		{87, 68, 113},
		{87, 193, 139},
		{87, 305, 97},
		{87, 422, 112},
		{87, 563, 95},
		{87, 704, 79},
		{87, 191, 359},
		{87, 407, 394},
		{87, 623, 422},
		{88, 85, 127},
		{88, 211, 172},
		{88, 285, 113},
		{88, 440, 96},
		{88, 638, 70},
		{88, 389, 234},
		{88, 553, 262},
		{88, 725, 237},
		{88, 123, 427},
		{88, 368, 478},
		{88, 539, 483},
		{88, 733, 491},
		{89, 49, 127},
		{89, 132, 152},
		{89, 218, 195},
		{89, 232, 111},
		{89, 337, 110},
		{89, 357, 210},
		{89, 421, 134},
		{89, 477, 202},
		{89, 543, 115},
		{89, 598, 143},
		{89, 682, 194},
		{89, 713, 90},
		{90, 152, 132},
		{90, 197, 101},
		{90, 282, 75},
		{90, 324, 141},
		{90, 416, 71},
		{90, 427, 148},
		{90, 507, 83},
		{90, 596, 147},
		{90, 665, 84},
		{91, 100, 161},
		{91, 183, 187},
		{91, 234, 296},
		{91, 317, 180},
		{91, 319, 95},
		{91, 460, 127},
		{91, 555, 167},
		{91, 649, 178},
		{91, 696, 279},
		{92, 244, 206},
		{92, 375, 193},
		{92, 507, 154},
		{93, 25, 134},
		{93, 80, 161},
		{93, 144, 133},
		{93, 175, 90},
		{93, 183, 150},
		{93, 228, 122},
		{93, 247, 50},
		{93, 274, 130},
		{93, 316, 170},
		{93, 343, 344},
		{93, 363, 124},
		{93, 395, 83},
		{93, 453, 193},
		{93, 471, 121},
		{93, 473, 287},
		{93, 558, 142},
		{93, 561, 198},
		{93, 612, 196},
		{93, 625, 115},
		{93, 632, 289},
		{93, 679, 92},
		{93, 688, 147},
		{93, 748, 188},
		{93, 760, 120},
		{94, 122, 45},
		{94, 262, 63},
		{94, 395, 77},
		{94, 529, 62},
		{94, 660, 75},
		{94, 71, 140},
		{94, 165, 186},
		{94, 333, 195},
		{94, 494, 174},
		{94, 607, 189},
		{94, 723, 152},
		{94, 686, 225},
		{94, 118, 304},
		{94, 252, 278},
		{94, 416, 280},
		{94, 568, 277},
		{94, 712, 342},
		{94, 90, 460},
		{94, 223, 472},
		{94, 329, 379},
		{94, 492, 381},
		{94, 656, 423},
		{94, 766, 450},
		{95, 26, 105},
		{95, 109, 94},
		{95, 156, 159},
		{95, 186, 108},
		{95, 218, 158},
		{95, 281, 146},
		{95, 358, 132},
		{95, 404, 186},
		{95, 453, 132},
		{95, 512, 138},
		{95, 671, 156},
		{95, 760, 164},
		{96, 86, 245},
		{96, 149, 47},
		{96, 196, 196},
		{96, 223, 45},
		{96, 269, 261},
		{96, 275, 46},
		{96, 315, 66},
		{96, 337, 121},
		{96, 358, 254},
		{96, 378, 61},
		{96, 416, 120},
		{96, 434, 277},
		{96, 440, 161},
		{96, 480, 205},
		{96, 482, 99},
		{96, 561, 134},
		{96, 586, 266},
		{97, 240, 182},
		{97, 295, 176},
		{97, 351, 159},
		{98, 220, 223},
		{98, 335, 205},
		{98, 475, 176},
		{98, 607, 170},
		{99, 73, 283},
		{99, 249, 165},
		{99, 431, 283},
		{99, 576, 430},
		{99, 677, 235},
		{100, 294, 215},
		{100, 532, 96},
		{100, 613, 87}};
int main(int argc, char* argv[] ){


	 //String face_cascade_name = "haarcascade_frontalface_mine.xml";
	 //1041 737 304
	 //1075	733	342 .95/.05
	 //1116	728	388 .9/.1
	 //1195 742 453 .8/.2
	 //1222 755 467 .7/.3

	 // 903 737 166
	 // 914 733 181 .95/.05
	 // 934 728 206 .9/.1
	 // 964 742 222 .8/.2
	 // 969 736 233 .7/.3


	 // 903 737 166
	 // 923 733 190 .95/.05
	 // 952 729 223 .9/.1
	 // 994 725 269 .8/.2
	 // 964 718 246 .7/.3


	 String face_cascade_name = "haarcascade_frontalface_alt.xml";
	 // 854 813	41
	 // 847 814 33 .95/.05
	 // 839 815 24 .9/.1
	 // 828 806 22 .8/.2
	 // 818 802 16 .7/.3

	 // 835	813	22
	 // 830 814 16 .95/.05
	 // 828 815 13 .9/.1
	 // 816 806 10 .8/.2
	 // 810 802 8 .7/.3

	 // 835	813	22						//HE
	 // 819 808 11 .95/.05
	 // 821 811 10 .9/.1
	 // 803 797 6 .8/.2
	 // 787 781 6 .7/.3


	 //String face_cascade_name = "haarcascade_frontalface_default.xml";
	 // 860 818	42
	 // 853 814 39 .95/.05
	 // 852 821 31 .9/.1
	 // 828 806 22 .8/.2
	 // 818 802 16 .7/.3

	 // 835	813	22
	 // 830 814 16 .95/.05
	 // 828 815 13 .9/.1
	 // 816 806 10 .8/.2
	 // 810 802 8 .7/.3

	 // 835	813	22						//HE
	 // 819 808 11 .95/.05
	 // 821 811 10 .9/.1
	 // 803 797 6 .8/.2
	 // 787 781 6 .7/.3

	 CascadeClassifier face_cascade;
	 string window_name = "Capture - Face detection";
	 if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "JPG";
	else dataType = "bmp";

		string dir = string(argv[1]);
		//dir = "/cygdrive/e/4/5/";
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();

		double aaa = atof(argv[3]);
		double bbb = atof(argv[4]);
		int ccc = atoi(argv[5]);


		//dir = "../tutorial-haartraining/CMU-MIT_Face_Test_Set/test";
		//dir = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/BAO/myDataBase";
		dataType = argv[2];

		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif



	cout<<"d dfd "<<files.size()<<endl;

	int detect [865] = {0};
	int totalWindow = 0;
	int correct = 0;
	int falsePositive = 0;
	double t=(double)getTickCount();
	for (int i = 0;i < files.size();i++) {
		//cout<<"d dfd: "<<dir+"/"+files[i]<<endl;
		Mat frame = imread( dir+"/"+files[i], -1 );
		Size size = frame.size();





		Mat frameF; frame.convertTo(frameF,CV_32FC3);
		Mat RGB[3]; split(frameF,RGB);

		Mat Cb(size,CV_8UC1);
		Mat Cr(size,CV_8UC1);
		double o256=1./256;
		Mat B_; RGB[0].convertTo(B_,CV_8UC1);
		Mat G_; RGB[1].convertTo(G_,CV_8UC1);
		Mat R_; RGB[2].convertTo(R_,CV_8UC1);

		uchar R,G,B;

		for (int k=0; k<size.height; k++){
		for (int j=0; j<size.width; j++){
			R = R_.at<uchar>(k,j);G = G_.at<uchar>(k,j);B = B_.at<uchar>(k,j);
			//cout<<R<<G<<B<<endl;
			//(*Y)  = (unsigned char)(16  + o256 * (   65.738  * R +  129.057  *  G +  25.064  *  B));
			Cb.at<uchar>(k,j) = (uchar)(128 + o256 * (  -37.945  * R -   74.494  *  G + 112.439  *  B));
			Cr.at<uchar>(k,j) = (uchar)(128 + o256 * (  112.439  * R -   94.154  *  G -  18.285  *  B));
		}}


		Mat gray; cvtColor(frame,gray,CV_RGB2GRAY);

		//imwrite("dfsafdf.png",gray);

		Mat thr(size,CV_8UC1);
		Mat thrCrCb[6];


		threshold(Cb, thrCrCb[0], 82, 255, THRESH_BINARY);
		threshold(Cb, thrCrCb[1], 122, 255, THRESH_BINARY_INV);
		bitwise_and(thrCrCb[0],thrCrCb[1],thrCrCb[2]);
		//imwrite("dfsafdf6.png",thrCrCb[2]);
		threshold(Cr, thrCrCb[3], 138, 255, THRESH_BINARY);
		threshold(Cr, thrCrCb[4], 168, 255, THRESH_BINARY_INV);
		bitwise_and(thrCrCb[3],thrCrCb[4],thrCrCb[5]);
		//imwrite("dfsafdf7.png",thrCrCb[5]);
		bitwise_or(thrCrCb[2],thrCrCb[5],thrCrCb[0]);
		//imwrite("dfsafdf8.png",thrCrCb[0]);



		Mat inv (size,CV_8UC1);
		inv = 255 - thrCrCb[0];
		std::vector < std::vector<cv::Point2i > > blobs;
		cvNica::FindBlobs(inv, blobs);

		for(size_t m=0; m < blobs.size(); m++) {
			if (blobs[m].size()<50){

				for(size_t n=0; n < blobs[m].size(); n++) {
					int x = blobs[m][n].x;
					int y = blobs[m][n].y;
					thrCrCb[0].at<uchar>(y,x) = 255;
				}
			}
		}
		//imwrite("dfsafdf9.png",thrCrCb[0]);

		//bitwise_and(thrCrCb[0],thr,thrCrCb[0]);
		//imwrite("dfsafdf9.png",thrCrCb[0]);


//				namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//				imshow( window_name, thrCrCb[0]);//thrCrCb[0] );
//				waitKey(0);









//		imshow( window_name, frame );
//				  waitKey(0);

		std::vector<Rect> faces;
		//Mat frame_gray=frame;
		Mat frame_gray2,frame_gray,frame_gray3,aa,bb;

		//imwrite("dfsafdf5.png",frame);
		cvtColor( frame, frame_gray3, CV_BGR2GRAY );
		cvNica::DoG(frame_gray3,frame_gray2,0.2,1,-2,0,0,0,10);

		//imwrite("dfsafdf3.png",Cb);
		//imwrite("dfsafdf4.png",Cr);

		//if (ccc==2) equalizeHist(frame_gray2,frame_gray2);

		frame_gray3.convertTo(aa,CV_32FC1);
		frame_gray2.convertTo(bb,CV_32FC1);
		frame_gray2 = (aa*aaa+bb*bbb);
		//frame_gray2 = (aa*.9+bb*.1);
		//imwrite("dfsafdf7.png",frame_gray2);
		//frame_gray2 = (aa*.7+bb*.3);
		//imwrite("dfsafdf7.png",frame_gray2);
		frame_gray2.convertTo(frame_gray,CV_8UC1);
		//cvtColor( frame, frame_gray, CV_BGR2GRAY );
//						namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//						imshow( window_name,frame_gray);//thrCrCb[0] );
//						waitKey(0);


		//equalizeHist( frame_gray, frame_gray );

		 //-- Detect faces
	    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, Size(20, 20) , Size(150, 150) );


	    //	    cout<<"d dfd "<<faces.size()<<endl;
	    totalWindow += faces.size();
//	    for (int k=0; k<865; k++) {
//			if (bao[k][0] == baoFileList[i]) {
//				Point truecenter (bao[k][1], bao[k][2]);
//				ellipse( frame, truecenter, Size( 10, 10), 0, 0, 360, Scalar( 0, 255, 255 ), 4, 8, 0 );
//			}
//	    }

		for( uint j = 0; j < faces.size(); j++ )
		{
		    Point center( faces[j].x + faces[j].width*0.5, faces[j].y + faces[j].height*0.5 );
//		    ellipse( frame, center, Size( faces[j].width*0.5, faces[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

		    Mat bb(thrCrCb[0], Rect(faces[j].x, faces[j].y, faces[j].width,faces[j].height));

		    double div = sum(bb)[0]/255./(faces[j].width*faces[j].height);
		    //cout<<div<<endl;
		    int counts = 0;
		    int pos = -1;
		    if (div<0.2 && ccc>=1) {
		    	totalWindow-=1;
		    	continue;
		    }
		    for (int k=0; k<865; k++) {

		    	if (bao[k][0] == baoFileList[i]) {
		    		Point truecenter (bao[k][1], bao[k][2]);


		    		double dist = norm(truecenter-center);
		    		//cout<<dist<<" "<<faces[j].width*0.5<<endl;
		    		if (dist < faces[j].width*0.5) {
		    			counts ++;
		    			pos = k;
		    		}
		    		if (counts>1) break;
		    	}

		    }
	    	if (counts == 1) {
	    		if (detect[pos]==1) {
					totalWindow -= 1;
				} else {
					detect[pos] = 1;
					//ellipse( frame, center, Size( faces[j].width*0.5, faces[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
				}
	    	} else if (counts > 1) {
	    		falsePositive += 1;
	    	} else {
	    		falsePositive += 1;
	    	}
	    	//ellipse( frame, center, Size( faces[j].width*0.5, faces[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		}
		//-- Show what you got
//		correct=0;
//		for (int k=0; k<865; k++) {
//					correct += detect[k];
//				}
//				cout<<"total window = "<<totalWindow<<endl;
//				cout<<"correctly detected = "<<correct<<endl;
//				cout<<"false positive = "<<falsePositive<<endl;
//


//		namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//		imshow( window_name, frame );
//		waitKey(0);
		//frame = imread( dir+"/"+files[i], -1 );
		//imwrite( dir+"/mine/"+files[i], frame );

	}
	for (int k=0; k<865; k++) {
		correct += detect[k];
	}

	t = ((double)getTickCount() - t)/getTickFrequency();
	cout << "Computation Time : " << t << " sec" << endl;
	cout<<"total window = "<<totalWindow<<endl;
	cout<<"correctly detected = "<<correct<<endl;
	cout<<"false positive = "<<falsePositive<<endl;

}

#endif


#ifdef faceDetection_dog

int main(int argc, char* argv[] ){

	 //String face_cascade_name = "haarcascade_frontalface_dog.xml";
	 //

	 String face_cascade_name = "haarcascade_frontalface_mine.xml";
	 //1041 737 304
	 //903	737	166

	 //String face_cascade_name = "haarcascade_frontalface_alt.xml";
	 // 854 813	41
	 // 835	813	22




	 CascadeClassifier face_cascade;
	 string window_name = "Capture - Face detection";
	 if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "JPG";
	else dataType = "bmp";

		string dir = string(argv[1]);
		//dir = "/cygdrive/e/4/5/";
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();


		//dir = "../tutorial-haartraining/CMU-MIT_Face_Test_Set/test";
		dir = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/BAO/myDataBase";
		dataType = "jpg";

		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif



	cout<<"d dfd "<<files.size()<<endl;

	int detect [865] = {0};
	int totalWindow = 0;
	int correct = 0;
	int falsePositive = 0;

	for (int i = 0;i < files.size();i++) {
		cout<<"d dfd: "<<dir+"/"+files[i]<<endl;


		for (double factor = 1; ; factor *=1.1){
			Mat frame_ = imread( dir+"/"+files[i], -1 ), frame;
			resize(frame_,frame,Size(),1./factor,1./factor);

			if( frame.cols < 20 || frame.rows < 20 )  break;


			Size size = frame.size();





			Mat frameF; frame.convertTo(frameF,CV_32FC3);
			Mat RGB[3]; split(frameF,RGB);

			Mat Cb(size,CV_8UC1);
			Mat Cr(size,CV_8UC1);
			double o256=1./256;
			Mat B_; RGB[0].convertTo(B_,CV_8UC1);
			Mat G_; RGB[1].convertTo(G_,CV_8UC1);
			Mat R_; RGB[2].convertTo(R_,CV_8UC1);

			uchar R,G,B;

			for (int k=0; k<size.height; k++){
			for (int j=0; j<size.width; j++){
				R = R_.at<uchar>(k,j);G = G_.at<uchar>(k,j);B = B_.at<uchar>(k,j);
				//cout<<R<<G<<B<<endl;
				//(*Y)  = (unsigned char)(16  + o256 * (   65.738  * R +  129.057  *  G +  25.064  *  B));
				Cb.at<uchar>(k,j) = (uchar)(128 + o256 * (  -37.945  * R -   74.494  *  G + 112.439  *  B));
				Cr.at<uchar>(k,j) = (uchar)(128 + o256 * (  112.439  * R -   94.154  *  G -  18.285  *  B));
			}}


			Mat gray; cvtColor(frame,gray,CV_RGB2GRAY);



			Mat thr(size,CV_8UC1);
			Mat thrCrCb[6];


			threshold(Cb, thrCrCb[0], 82, 255, THRESH_BINARY);
			threshold(Cb, thrCrCb[1], 122, 255, THRESH_BINARY_INV);
			bitwise_and(thrCrCb[0],thrCrCb[1],thrCrCb[2]);
			threshold(Cr, thrCrCb[3], 138, 255, THRESH_BINARY);
			threshold(Cr, thrCrCb[4], 168, 255, THRESH_BINARY_INV);

			bitwise_and(thrCrCb[3],thrCrCb[4],thrCrCb[5]);
			bitwise_or(thrCrCb[2],thrCrCb[5],thrCrCb[0]);




			Mat inv (size,CV_8UC1);
			inv = 255 - thrCrCb[0];
			std::vector < std::vector<cv::Point2i > > blobs;
			cvNica::FindBlobs(inv, blobs);

			for(size_t m=0; m < blobs.size(); m++) {
				if (blobs[m].size()<50){

					for(size_t n=0; n < blobs[m].size(); n++) {
						int x = blobs[m][n].x;
						int y = blobs[m][n].y;
						thrCrCb[0].at<uchar>(y,x) = 255;
					}
				}
			}


			//bitwise_and(thrCrCb[0],thr,thrCrCb[0]);









	//		total window = 1474
	//		correctly detected = 585
	//		false positive = 889



	//		imshow( window_name, frame );
	//				  waitKey(0);





			std::vector<Rect> faces;
			//Mat frame_gray=frame;
			Mat frame_gray,frame_gray2;
			Mat resized;
			cvtColor( frame, resized, CV_BGR2GRAY );



			cvNica::DoG(resized,frame_gray,0.2,1,-2,0,0,0,10);
			//equalizeHist( frame_gray, frame_gray );

//					namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//					imshow( window_name, frame_gray );
//					waitKey(0);

			 //-- Detect faces
			face_cascade.detectMultiScale( frame_gray, faces, 20, 1, 0|CV_HAAR_SCALE_IMAGE, Size(20, 20) , Size(150, 150) );
//			namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//			imshow( window_name, frame_gray);//thrCrCb[0] );
//			waitKey(0);

			//	    cout<<"d dfd "<<faces.size()<<endl;
			totalWindow += faces.size();
	//	    for (int k=0; k<865; k++) {
	//			if (bao[k][0] == baoFileList[i]) {
	//				Point truecenter (bao[k][1], bao[k][2]);
	//				ellipse( frame, truecenter, Size( 10, 10), 0, 0, 360, Scalar( 0, 255, 255 ), 4, 8, 0 );
	//			}
	//	    }

			for( uint j = 0; j < faces.size(); j++ )
			{
				Point center( faces[j].x + faces[j].width*0.5, faces[j].y + faces[j].height*0.5 );
	//		    ellipse( frame, center, Size( faces[j].width*0.5, faces[j].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

				Mat bb(thrCrCb[0], Rect(faces[j].x, faces[j].y, faces[j].width,faces[j].height));

				double div = sum(bb)[0]/255./(faces[j].width*faces[j].height);
				//cout<<div<<endl;
				int counts = 0;
				int pos = -1;
				if (div<0.2) {
					totalWindow-=1;
					continue;
				}
				for (int k=0; k<865; k++) {

					if (bao[k][0] == baoFileList[i]) {
						Point truecenter (bao[k][1]/factor, bao[k][2]/factor);


						double dist = norm(truecenter-center);
						//cout<<dist<<" "<<faces[j].width*0.5<<endl;
						if (dist < faces[j].width*0.5) {
							counts ++;
							pos = k;
						}
						if (counts>1) break;
					}

				}
				if (counts == 1) {
					if (detect[pos]==1) {
						totalWindow -= 1;
					} else {
						detect[pos] = 1;
					}
				} else if (counts > 1) {
					falsePositive += 1;
				} else {
					falsePositive += 1;
				}
			}
			//cout<<factor<<endl;

		}
		//-- Show what you got
//		correct=0;
//		for (int k=0; k<865; k++) {
//					correct += detect[k];
//				}
				cout<<"total window = "<<totalWindow<<endl;
				//cout<<"correctly detected = "<<correct<<endl;
				cout<<"false positive = "<<falsePositive<<endl;
//
//		namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//		imshow( window_name, frame );
//		waitKey(0);

	}
	for (int k=0; k<865; k++) {
		correct += detect[k];
	}


	cout<<"total window = "<<totalWindow<<endl;
	cout<<"correctly detected = "<<correct<<endl;
	cout<<"false positive = "<<falsePositive<<endl;

}

#endif



#ifdef faceDetection2

int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpg";
	else dataType = "bmp";

		string dir = string(argv[1]);
		//dir = "/cygdrive/e/4/5/";
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();
		dataType = "jpg";

		//dir = "../tutorial-haartraining/CMU-MIT_Face_Test_Set/test";
		dir = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/BAO/myDataBase";
		//dir = "../tutorial-haartraining/gallery72";
		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif



	cout<<" "<<files.size()<<endl;

	Mat template__ = imread("facetemplate.png",CV_8UC1);

	double startScale = 0.3;
	double endScale = 1.21;
	double scaleInterval = 0.1;
//
//
//
//
//	Mat aveImg;
//
//
//	for (unsigned int i = 0;i < files.size();i++) {
//		cout<<""<<dir+"/"+files[i]<<endl;
//		Mat frame_ = imread( dir+"/"+files[i], -1 );
//		if (i==0){
//			aveImg=Mat::zeros(frame_.size(),CV_32FC1);
//		}
//		Mat temp; frame_.convertTo(temp,CV_32FC1);
//		aveImg += temp;
//			cout<<"complete: "<<i<<endl;
//	}
//	aveImg/=files.size();
//	Mat aveImg2; aveImg.convertTo(aveImg2,CV_8UC1);
//	imwrite("aveimg.bmp",aveImg2);



	for (unsigned int i = 0;i < files.size();i++) {
		cout<<""<<dir+"/"+files[i]<<endl;
		Mat frame_ = imread( dir+"/"+files[i], -1 );


//		cvNica::Denoise(frame,_deno1);
//		//_deno1=_image1;
//		//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
//		cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//		//_dmqi=_deno1;
//		//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
//		//_dmqi = 255-_dmqi;
//		//equalizeHist(_dmqi,_histeq);
//		nicatio::HistEqualize(_dmqi.data,_histeq.data,frame.cols,frame.rows);

		//equalizeHist(frame,frame);

		for (double scale = startScale; scale<endScale; scale+=scaleInterval) {

			Mat frame; resize(frame_,frame,Size(),scale,scale,CV_INTER_CUBIC);

			Mat frameF; frame.convertTo(frameF,CV_32FC3);
			//GaussianBlur(frame,frame,Size(5,5),1.0);

			Mat RGB[3]; split(frameF,RGB);
			Size size = frame.size();
			Mat Cb(size,CV_8UC1);
			Mat Cr(size,CV_8UC1);
			double o256=1./256;
			Mat B_; RGB[0].convertTo(B_,CV_8UC1);
			Mat G_; RGB[1].convertTo(G_,CV_8UC1);
			Mat R_; RGB[2].convertTo(R_,CV_8UC1);

			uchar R,G,B;

			for (int k=0; k<size.height; k++){
			for (int j=0; j<size.width; j++){
				R = R_.at<uchar>(k,j);G = G_.at<uchar>(k,j);B = B_.at<uchar>(k,j);
				//cout<<R<<G<<B<<endl;
				//(*Y)  = (unsigned char)(16  + o256 * (   65.738  * R +  129.057  *  G +  25.064  *  B));
				Cb.at<uchar>(k,j) = (uchar)(128 + o256 * (  -37.945  * R -   74.494  *  G + 112.439  *  B));
				Cr.at<uchar>(k,j) = (uchar)(128 + o256 * (  112.439  * R -   94.154  *  G -  18.285  *  B));
			}}


			Mat gray; cvtColor(frame,gray,CV_RGB2GRAY);



	//		Mat sobelx(size,CV_8UC1);
	//		Mat sobely(size,CV_8UC1);
	//		Mat gradx(size,CV_8UC1);
	//		Mat grady(size,CV_8UC1);
	//		Mat sobel(size,CV_8UC1);
			Mat temp2(size,CV_8UC1);
	//		Mat _deno1(size,CV_8UC1);
	//		Mat _dmqi(size,CV_8UC1);
	//		Mat _histeq(size,CV_8UC1);
			Mat thr(size,CV_8UC1);
			Mat thrCrCb[6];

			cvNica::DoG(gray,temp2,0.2,1,-2,0,0,0,10);
			equalizeHist(temp2,temp2);
			threshold(temp2, thr, 109, 255, THRESH_BINARY_INV);

			threshold(Cb, thrCrCb[0], 82, 255, THRESH_BINARY);
			threshold(Cb, thrCrCb[1], 122, 255, THRESH_BINARY_INV);
			bitwise_and(thrCrCb[0],thrCrCb[1],thrCrCb[2]);
			threshold(Cr, thrCrCb[3], 138, 255, THRESH_BINARY);
			threshold(Cr, thrCrCb[4], 168, 255, THRESH_BINARY_INV);

			bitwise_and(thrCrCb[3],thrCrCb[4],thrCrCb[5]);
			bitwise_or(thrCrCb[2],thrCrCb[5],thrCrCb[0]);

			Mat inv (size,CV_8UC1);
			inv = 255 - thrCrCb[0];
			std::vector < std::vector<cv::Point2i > > blobs;
			cvNica::FindBlobs(inv, blobs);

			for(size_t m=0; m < blobs.size(); m++) {
				if (blobs[m].size()<50){

					for(size_t n=0; n < blobs[m].size(); n++) {
						int x = blobs[m][n].x;
						int y = blobs[m][n].y;
						thrCrCb[0].at<uchar>(y,x) = 255;
					}
				}
			}


			bitwise_and(thrCrCb[0],thr,thrCrCb[0]);


			Mat thrtemplate; threshold(template__, thrtemplate, 123, 255, THRESH_BINARY_INV);
//			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//			imshow( "c", thrtemplate);//thrCrCb[0] );
//			waitKey(0);

			Mat matchresult__, matchresult_,matchresult;
			matchTemplate(thrCrCb[0], template__, matchresult__, CV_TM_CCORR_NORMED);
			//matchTemplate(thrCrCb[0], thrtemplate, matchresult__, CV_TM_CCOEFF_NORMED);

			threshold(matchresult__, matchresult, 0.45, 1, THRESH_BINARY);





			Mat gray2 ; gray.convertTo(gray2,CV_32FC1);
			Mat gray3(gray2,Rect(16,16,gray2.cols-31,gray2.rows-31));

			cout<<gray2.type()<<CV_8UC1<<CV_32FC1<<endl;


			gray2/=255;
			  double min,max;
			  minMaxLoc(matchresult__, &min, &max);
			  cout<<min<<" "<<max<<endl;

			matchresult.convertTo(matchresult_,CV_8UC1);
//			matchresult.copyTo(matchresult_);

			cout<<gray3.cols<<gray3.rows<<endl;
			cout<<matchresult_.cols<<matchresult_.rows<<endl;
//
			Mat mer [3] = {matchresult,matchresult,gray3};
			Mat mer_;
			merge(mer,3,mer_);


			namedWindow( "z", CV_WINDOW_AUTOSIZE );
			imshow( "z", template__);//thrCrCb[0] );

			namedWindow( "a", CV_WINDOW_AUTOSIZE );
			imshow( "a", matchresult__);//thrCrCb[0] );

			namedWindow( "b", CV_WINDOW_AUTOSIZE );
			imshow( "b", temp2);//thrCrCb[0] );

			namedWindow( "c", CV_WINDOW_AUTOSIZE );
			imshow( "c", mer_);//thrCrCb[0] );
			waitKey(0);
		}
	}
}

#endif



#ifdef YUVUHD


int main(int argc, char* argv[] ){

#ifdef DATA_TYPE_SELECT
	string dataType;
	if (DATA_TYPE == 0) dataType = "bmp";
	else if (DATA_TYPE == 1) dataType = "png";
	else if (DATA_TYPE == 2) dataType = "pgm";
	else if (DATA_TYPE == 3) dataType = "jpg";
	else dataType = "bmp";

		string dir = string(argv[1]);
		string refLocation = string(argv[2]);

		vector<string> files = vector<string>();
		dataType = "bmp";

		dir = "/cygdrive/e/Documents/Nicatio/Research/DB/UHD";
		if (nicatio::getdirType(dir,dataType,files,0)) {
			cout<< "Error: Invalid file location \n" <<endl;
			return -1;
		}
#endif



	cout<<" "<<files.size()<<endl;





//
//
//		nicatio::cplx buf[] = {1, 1, 1, 1, 0, 0, 0, 0};
//
//
//
//		nicatio::show("Data: ",buf);
//		nicatio::fft(buf, 8);
//		nicatio::show("\nFFT : ",buf);







	for (unsigned int i = 0;i < files.size();i++) {
		cout<<""<<dir+"/"+files[i]<<endl;
		Mat frame__ = imread( dir+"/"+files[i], -1 );
		Mat frame_;
		if (frame__.channels()==1) {
			cvtColor(frame__,frame_,CV_GRAY2RGB);
		} else {
			frame_ = frame__;
		}











		//Mat frame___;
		//cvtColor(frame__,frame___,CV_RGB2GRAY);
		//cvtColor(frame___,frame_,CV_GRAY2RGB);

		Mat canny_,canny__;

		Canny( frame_, canny_, 30, 50, 3, 1 );

		Mat sobelx, gradx, sobely,grady,sobel;

		Sobel(frame_,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
		convertScaleAbs( sobelx, gradx );
		Sobel(frame_,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
		convertScaleAbs( sobely, grady );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );

		//Mat sobel8U, sobels[3];
		///sobel.convertTo(sobel8U,CV_8UC3);
		//split(sobel8U,sobels);


		Mat sobelgray_,sobelgray__,sobelgray;

		//max(sobels[0],sobels[1],sobelgray__);
		//max(sobelgray__,sobels[2],sobelgray__);
		cvtColor(sobel,sobelgray_,CV_RGB2GRAY);
		sobelgray_.convertTo(sobelgray__,CV_8UC1);
		//GaussianBlur(sobelgray__,sobelgray__,Size(5,5),1);
		//threshold(sobelgray__,sobelgray__,100,255,THRESH_BINARY);

		//resize(frame_,frame_,Size(0,0),.5,.5);

		//Canny

		Mat imageForFFT[17];

		int w = frame_.cols;
		int h = frame_.rows;
		int w4 = frame_.cols-4;
		int h4 = frame_.rows-4;
		int sz4 = w4*h4;
		int sz = w*h;

	    Point2f src_center(w/2.0F, h/2.0F);

//	    int xx = 159;
//	    int yy = 87;
	    int xx = 242;
	    int yy = 277;
	    int l;
	  //
		double ar;
		double ag;
		double ab;
		double asr;
		double asg;
		double asb;
		double br;
		double bg;
		double bb;
		double bsr;
		double bsg;
		double bsb;


		cvNica::FRID frid(frame_,FRID_16F);

		//vector<int> fp = frid.getFeaturePoints();
		vector<int> fp;






		int thresh = 80;
		int blockSize = 3;
		int apertureSize = 3;
		double k = 0.04;
		Mat frame_gray,dst,dst_norm,dst_norm_scaled;
		cvtColor(frame_,frame_gray,CV_RGB2GRAY);
		//cvtColor(frame_,frame_gray,CV_RGB2GRAY);
		/// Detecting corners
		cornerHarris( frame_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
		double min,max;
		minMaxIdx(dst,&min,&max,0);
		cout<<"max: "<<max<<endl;
		cout<<"min: "<<min<<endl;

		dst_norm = dst/max*255.;

		/// Normalizing
		//normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
		//convertScaleAbs( dst_norm, dst_norm_scaled );
		//dst_norm = dst*255*255;




		//		int maxid[2];
				//minMaxIdx(dst_norm,&min,&max,0);
				//cout<<"max: "<<max<<endl;
				//cout<<"max: "<<min<<endl;


		dst_norm.convertTo(dst_norm_scaled,CV_8UC1);






		threshold(dst_norm_scaled,dst_norm_scaled,40,255,THRESH_BINARY);

		std::vector < std::vector<cv::Point2i > > blobs;
		cvNica::FindBlobs(dst_norm_scaled, blobs);

		for(size_t m=0; m < blobs.size(); m++) {
			if (blobs[m].size()<50){
				int sumx = 0;
				int sumy = 0;
				for(size_t n=0; n < blobs[m].size(); n++) {
					int x = blobs[m][n].x;
					int y = blobs[m][n].y;
					sumx += x;
					sumy += y;
				}
				fp.push_back(sumx/blobs[m].size());
				fp.push_back(sumy/blobs[m].size());
				cout<<(sumx/blobs[m].size())<<":"<<(sumy/blobs[m].size())<<endl;
			}
		}

		/// Drawing a circle around corners
		for( int j = 0; j < dst_norm.rows ; j++ )
		   { for( int i = 0; i < dst_norm.cols; i++ )
				{
				  if( (int) dst_norm.at<float>(j,i) > thresh )
					{
					 circle( dst_norm_scaled, Point( i, j ), 25,  Scalar(0), 1, 8, 0 );
//					 fp.push_back(i);
//					 fp.push_back(j);
					}
				}
		   }
		/// Showing the result


		//namedWindow( "b", CV_WINDOW_AUTOSIZE );
		//imshow( "b", sobelgray);//thrCrCb[0] );
		//imshow( "b", dst_norm_scaled);//thrCrCb[0] );
		imwrite("dst_norm_scaled.bmp",dst_norm_scaled);

		//namedWindow( "d", CV_WINDOW_AUTOSIZE );
		//imshow( "d", corImg);//thrCrCb[0] );

		//waitKey(0);




		ofstream ofs;
		ofs.open("angle.txt",ios::out|ios::binary);



		int fpsize = fp.size();
		int fpi;
		GaussianBlur(frame_,frame_,Size(11,11),1,1);
for(double angle=0; angle<360; angle+=1){
	    //double angle = 50;
	    Mat rot_matrix = getRotationMatrix2D(src_center, angle, 1.);
	    Point2f newxys[3];


	    //cout<<"new: "<<newxx<<", "<<newyy<<endl;




	    Mat rotated_img(Size(h, w), CV_8UC3);

	    warpAffine(frame_, rotated_img, rot_matrix, frame_.size(),INTER_CUBIC);
	    warpAffine(sobelgray__, sobelgray_, rot_matrix, frame_.size(),INTER_CUBIC);


	    Mat rotated_img = imread( dir+"/"+files[1], -1 );

	    Mat cornerharrisdst,cornerharrisdst_norm,cornerharrisdst_norm_scaled,cornerharrisdst_norm_scaled2,cornerharrisdst_norm_scaled_cvt,rotated_img_gray;
	    cvtColor(rotated_img,rotated_img_gray,CV_RGB2GRAY);
		cornerHarris(rotated_img_gray, cornerharrisdst, blockSize, apertureSize, k, BORDER_DEFAULT );

		minMaxIdx(cornerharrisdst,&min,&max,0);
		cout<<"max: "<<max<<endl;
		cout<<"min: "<<min<<endl;

		cornerharrisdst_norm = cornerharrisdst/max*255.;




		/// Normalizing
		//normalize( cornerharrisdst, cornerharrisdst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
		//convertScaleAbs( cornerharrisdst_norm, cornerharrisdst_norm_scaled );
		//normalize( cornerharrisdst_norm_scaled, cornerharrisdst_norm_scaled2, 0, 255, NORM_MINMAX, CV_8UC1, Mat() );
		minMaxIdx(cornerharrisdst_norm,&min,&max,0);
		cout<<"max: "<<max<<endl;
		cout<<"min: "<<min<<endl;
		cornerharrisdst_norm.convertTo(cornerharrisdst_norm_scaled,CV_8UC1);


		threshold(cornerharrisdst_norm_scaled,cornerharrisdst_norm_scaled_cvt,20,255,THRESH_BINARY);
		//cornerharrisdst_norm_scaled.convertTo(cornerharrisdst_norm_scaled_cvt,CV_8UC1);

//		cout<<"d:" << (cornerharrisdst_norm_scaled2.type()==CV_8UC1)<<endl;
/*		namedWindow( "c", CV_WINDOW_AUTOSIZE );
		imshow( "c",  cornerharrisdst_norm_scaled);//thrCrCb[0] );
//		//namedWindow( "d", CV_WINDOW_AUTOSIZE );
//		//imshow( "d", corImg);//thrCrCb[0] );
//
		waitKey(0);*/

//	    for (int aa=1; aa<=10;aa++) {
//	    	Mat resampled;
//
//			Mat affinematrix = (Mat_<float>(2,3) << 1, 0, (float)aa/10, 0, 1, 0);;// Mat(2,3,CV_32F,affinematrix_);
//			stringstream d;
//			d<<"br_"<<aa<<".bmp";
//
//
//			warpAffine(frame_, resampled, affinematrix, frame_.size(),INTER_LINEAR);
//
//
//			imwrite("bf_.bmp",frame_);
//			imwrite(d.str().c_str(),resampled);
//	    }




		Mat cdmat;
		//Mat(rotated_img, Rect(2, 2, w4, h4)).copyTo(cdmat);
		//Mat(sobelgray_, Rect(2, 2, w4, h4)).copyTo(sobelgray);
		rotated_img.copyTo(cdmat);
		sobelgray_.copyTo(sobelgray);


//		double min,max;
//		int maxid[2];
//		minMaxIdx(sobelgray,&min,&max,0,maxid);
//
//		cout<<"max: "<<max<<endl;


		//Mat corImg = Mat::zeros(Size(w4,h4),CV_32FC1);


		double t = (double)getTickCount();

		cvNica::FRID frid2(rotated_img,FRID_16F);




//	    frid.getFeatureVector(101-2,101-2,ar,ag,ab,asr,asg,asb).copyTo(bufABSmat);
	    //frid.getFeatureVector(xx-2,yy-2,ar,ag,ab,asr,asg,asb).copyTo(bufABSmat);

		//int *adf = fp.data();
		//Mat adfa2(fpsize/2,2,CV_32SC1,adf);
		//Mat adfa2(3,2,CV_32SC1,adf);
		//Mat adfa;
		//adfa2.convertTo(adfa,CV_32FC1);

		Point2f adfa[3]; //= {Point2f((float)fp[2],(float)fp[3]),Point2f((float)fp[4],(float)fp[5]),Point2f((float)fp[6],(float)fp[7])};
		int a0=fp.at(0);
		int a1=fp.at(1);
		int a2=fp.at(2);
		int a3=fp.at(3);
		int a4=fp.at(4);
		int a5=fp.at(5);
//		int a0=fp.at(2);
//		int a1=fp.at(3);
//		int a2=fp.at(4);
//		int a3=fp.at(5);
//		int a4=fp.at(6);
//		int a5=fp.at(7);

		adfa[0].x = (float)a0;
		adfa[0].y = (float)a1;
		adfa[1].x = (float)a2;
		adfa[1].y = (float)a3;
		adfa[2].x = (float)a4;
		adfa[2].y = (float)a5;

//		cout<<" "<<(short)adfa2.at<short>(0)<<" "
//				<<(short)adfa2.at<short>(1)<<" "
//				<<(short)adfa2.at<short>(2)<<" "
//				<<(short)adfa2.at<short>(3)<<" "
//				<<(short)adfa2.at<short>(4)<<" "
//				<<(short)adfa2.at<short>(5)<<" "
//				<<(short)adfa2.at<short>(6)<<" "
//				<<(short)adfa2.at<short>(7)<<" "
//				<<endl;
//
//				cout<<" "<<(float)adfa.at<float>(0)<<" "
//						<<(float)adfa.at<float>(1)<<" "
//						<<(float)adfa.at<float>(2)<<" "
//						<<(float)adfa.at<float>(3)<<" "
//						<<(float)adfa.at<float>(4)<<" "
//						<<(float)adfa.at<float>(5)<<" "
//						<<(float)adfa.at<float>(6)<<" "
//						<<(float)adfa.at<float>(7)<<" "
//						<<endl;
for(fpi=0;fpi<fpsize;fpi+=2) {
	//Mat bufABSmat;
	Mat corImg = Mat::zeros(Size(w,h),CV_32FC1);
		xx = fp[fpi];
		yy = fp[fpi+1];
		cout<<"xy: "<<xx<<", "<<yy<<endl;
	    double diffy = yy-src_center.y;
	    double diffx = xx-src_center.x;
	    double dist = sqrt((double)diffy*diffy+diffx*diffx);
	    double angleb2wpt = atan2(diffy, diffx);
	    double newxx = dist*cos(angleb2wpt-angle/180*PI)*1.+src_center.x;
	    double newyy = dist*sin(angleb2wpt-angle/180*PI)*1.+src_center.y;
	    float* bufABS = frid.getFeatureVector(xx,yy,ar,ag,ab,asr,asg,asb);
//	    		cout<<" "<<bufABS[0]<<" "
//	    				<<bufABS[1]<<" "
//	    				<<bufABS[2]<<" "
//	    				<<bufABS[3]<<" "
//	    				<<bufABS[4]<<" "
//	    				<<bufABS[5]<<" "
//	    				<<bufABS[6]<<" "
//	    				<<bufABS[7]<<" "
//	    				<<bufABS[8]<<" "
//	    				<<bufABS[9]<<" "<<endl;
//	    frid.getFeatureVector(259-2,187-2,ar,ag,ab,asr,asg,asb).copyTo(bufABSmat);
	    //frid.getFeatureVector(249-2,182-2,ar,ag,ab,asr,asg,asb).copyTo(bufABSmat);
//		cout<<" "<<(float)bufABS3mat.at<float>(0,0)<<" "
//				<<(float)bufABS3mat.at<float>(0,1)<<" "
//				<<(float)bufABS3mat.at<float>(0,2)<<" "
//				<<(float)bufABS3mat.at<float>(0,3)<<" "
//				<<(float)bufABS3mat.at<float>(0,4)<<" "
//				<<(float)bufABS3mat.at<float>(0,5)<<" "
//				<<(float)bufABS3mat.at<float>(0,6)<<" "
//				<<(float)bufABS3mat.at<float>(0,7)<<" "
//				<<(float)bufABS3mat.at<float>(0,8)<<" "
//				<<(float)bufABS3mat.at<float>(0,9)<<" "
//				<<endl;

		//waitKey(0);


	    		//cout<<"ff: " <<imageForFFT[0].data[w4]<<" d"<<endl;

	    		for (l=0; l<sz; l++){
	    			//if (sobelgray.at<uchar>(l/w4,l%w4) < 100) continue;
	    			//if (sobelgray.at<uchar>(l/w,l%w) < 100) continue;
	    			if (cornerharrisdst_norm_scaled_cvt.at<uchar>(l/w,l%w) < 100) continue;
	    			float* bufABS2 = frid2.getFeatureVector(l%w,l/w,br,bg,bb,bsr,bsg,bsb);
	    			Mat result1;
	    			//frid2.getFeatureVector(l%w4,l/w4,br,bg,bb,bsr,bsg,bsb).copyTo(bufABS2mat);
	    			//frid2.getFeatureVector(l%w,l/w,br,bg,bb,bsr,bsg,bsb).copyTo(bufABS2mat);
	    			//matchTemplate(bufABSmat, bufABS2mat, result1, CV_TM_CCOEFF_NORMED);
	    			//corImg.at<float>(l) = pow(result1.at<float>(0),10);
	    			//cout<<(float)bufABSmat.at<float>(0) <<endl;
	    			//if (creal(buf2r[0])>255 && creal(buf2g[0])>255 && creal(buf2b[0])>255)  {
	    			//cout<<(float)pow(result1.at<float>(0),6)<<endl;
//	    			cout<<(float)bufABS2mat.at<float>(0,0)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,1)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,2)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,3)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,4)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,5)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,6)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,7)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,8)<<" "
//	    					<<(float)bufABS2mat.at<float>(0,9)<<" "
//	    					<<endl;
	    			//Mat bufABS4mat;bufABSmat.copyTo(bufABS4mat);
//	    			cout<<" "<<(float)bufABSmat.at<float>(0,0)<<" "
//	    					<<(float)bufABSmat.at<float>(0,1)<<" "
//	    					<<(float)bufABSmat.at<float>(0,2)<<" "
//	    					<<(float)bufABSmat.at<float>(0,3)<<" "
//	    					<<(float)bufABSmat.at<float>(0,4)<<" "
//	    					<<(float)bufABSmat.at<float>(0,5)<<" "
//	    					<<(float)bufABSmat.at<float>(0,6)<<" "
//	    					<<(float)bufABSmat.at<float>(0,7)<<" "
//	    					<<(float)bufABSmat.at<float>(0,8)<<" "
//	    					<<(float)bufABSmat.at<float>(0,9)<<" ";

	    			Mat bufABSmat ((16/2-1)*3+3,1,CV_32FC1,bufABS);
	    			Mat bufABS2mat ((16/2-1)*3+3,1,CV_32FC1,bufABS2);


//	    			if ((float)bufABSmat.at<float>(0,0) == (float)bufABS2mat.at<float>(0,0)) {
//	    				    			cout<<" "<<(float)bufABSmat.at<float>(0,0)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,1)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,2)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,3)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,4)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,5)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,6)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,7)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,8)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,9)<<" "
//	    				    					<<(float)bufABSmat.at<float>(0,10)<<" "
//												<<(float)bufABSmat.at<float>(0,11)<<" "
//												<<(float)bufABSmat.at<float>(0,12)<<" "
//												<<(float)bufABSmat.at<float>(0,13)<<" "
//												<<(float)bufABSmat.at<float>(0,14)<<" "
//												<<(float)bufABSmat.at<float>(0,15)<<" "
//												<<(float)bufABSmat.at<float>(0,16)<<" "
//												<<(float)bufABSmat.at<float>(0,17)<<" "
//												<<(float)bufABSmat.at<float>(0,18)<<" "
//												<<(float)bufABSmat.at<float>(0,19)<<" "
//												<<(float)bufABSmat.at<float>(0,20)<<" "
//												<<(float)bufABSmat.at<float>(0,21)<<" "
//												<<(float)bufABSmat.at<float>(0,22)<<" "
//												<<(float)bufABSmat.at<float>(0,23)<<" "<<endl;
//	    				    			cout<<" "<<(float)bufABS2mat.at<float>(0,0)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,1)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,2)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,3)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,4)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,5)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,6)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,7)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,8)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,9)<<" "
//	    				    					<<(float)bufABS2mat.at<float>(0,10)<<" "
//												<<(float)bufABS2mat.at<float>(0,11)<<" "
//												<<(float)bufABS2mat.at<float>(0,12)<<" "
//												<<(float)bufABS2mat.at<float>(0,13)<<" "
//												<<(float)bufABS2mat.at<float>(0,14)<<" "
//												<<(float)bufABS2mat.at<float>(0,15)<<" "
//												<<(float)bufABS2mat.at<float>(0,16)<<" "
//												<<(float)bufABS2mat.at<float>(0,17)<<" "
//												<<(float)bufABS2mat.at<float>(0,18)<<" "
//												<<(float)bufABS2mat.at<float>(0,19)<<" "
//												<<(float)bufABS2mat.at<float>(0,20)<<" "
//												<<(float)bufABS2mat.at<float>(0,21)<<" "
//												<<(float)bufABS2mat.at<float>(0,22)<<" "
//												<<(float)bufABS2mat.at<float>(0,23)<<" "<<endl;
//	    			}

	    			matchTemplate(bufABSmat, bufABS2mat, result1, CV_TM_CCOEFF_NORMED);
	    			if (bsr>255 && bsg>255 && bsb>255 && pow(result1.at<float>(0),3)>0.5)  {
	    				corImg.at<float>(l) = (result1.at<float>(0) > 0)? pow(result1.at<float>(0),3):0;
	    			}// else {
	    			//	corImg.at<float>(l) = 0;
	    			//}
//	    			if ((float)bufABSmat.at<float>(0,0) == (float)bufABS2mat.at<float>(0,0)) {
//	    				cout<<" -- "<<result1.at<float>(0)<<endl;
//	    			}


	    		}


		double min,max;
		int maxid[2];
		minMaxIdx(corImg,&min,&max,0,maxid);
		//cout<< "d: "<<maxid[1]<<", "<<maxid[0]<<endl;

		frid2.getFeatureVector(maxid[1],maxid[0],br,bg,bb,bsr,bsg,bsb);


		double dist_ = sqrt((maxid[1]-newxx)*(maxid[1]-newxx)+(maxid[0]-newyy)*(maxid[0]-newyy));

		//if(fpi>0) {
//			newxys[(fpi/2)-1].x = (float)maxid[1];
//			newxys[(fpi/2)-1].y = (float)maxid[0];
//		}
		if(fpi<6) {
			newxys[(fpi/2)].x = (float)maxid[1];
			newxys[(fpi/2)].y = (float)maxid[0];
		}
		//newxys.push_back(maxid[1]);
		//newxys.push_back(maxid[0]);

		cout<<"dist: "<<(double)dist_<<endl;
//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", sobelgray);//thrCrCb[0] );
//		namedWindow( "d", CV_WINDOW_AUTOSIZE );
//		imshow( "d", corImg);//thrCrCb[0] );
//
//		waitKey(0);

		if (dist_>3)
			circle( cdmat, Point(maxid[1],maxid[0]), 8, Scalar( 0, 0, 255 ), -1, 8 );
		else
			circle( cdmat, Point(maxid[1],maxid[0]), 8, Scalar( 0, 255, 0 ), -1, 8 );
		//circle( cdmat, Point(newxx,newyy), 1, Scalar( 0, 255, 0 ), -1, 8 );


}
		//int *newxyss = newxys.data();
		//Mat adfa3(fpsize/2,2,CV_32SC1,newxyss);
		//Mat adfa3(3,2,CV_32SC1,newxyss);
		//Mat adfa4;
		///adfa3.convertTo(adfa4,CV_32FC1);
	t = ((double)getTickCount() - t)/getTickFrequency();
	cout<<"elapsed: "<<(double)t<<endl;
		Mat aff = getAffineTransform(adfa, newxys);
		cout<<" "<<(double)aff.at<double>(0)<<" "
						<<(double)aff.at<double>(1)<<" "
						<<(double)aff.at<double>(2)<<" "
						<<(double)aff.at<double>(3)<<" "
						<<(double)aff.at<double>(4)<<" "
						<<(double)aff.at<double>(5)<<" "
						<<endl;
		cout<<" "<<(double)rot_matrix.at<double>(0)<<" "
						<<(double)rot_matrix.at<double>(1)<<" "
						<<(double)rot_matrix.at<double>(2)<<" "
						<<(double)rot_matrix.at<double>(3)<<" "
						<<(double)rot_matrix.at<double>(4)<<" "
						<<(double)rot_matrix.at<double>(5)<<" "
						<<endl;
		double size1 = sqrt(rot_matrix.at<double>(0)*rot_matrix.at<double>(0)+rot_matrix.at<double>(1)*rot_matrix.at<double>(1));
		double size11 = sqrt(rot_matrix.at<double>(3)*rot_matrix.at<double>(3)+rot_matrix.at<double>(4)*rot_matrix.at<double>(4));
		double size2 = sqrt(aff.at<double>(0)*aff.at<double>(0)+aff.at<double>(1)*aff.at<double>(1));
		double size21 = sqrt(aff.at<double>(4)*aff.at<double>(4)+aff.at<double>(3)*aff.at<double>(3));
		cout<<" "<<size1<<endl;
		cout<<" "<<size2<<endl;
		cout<<" "<<(acos(rot_matrix.at<double>(0)/size1)+acos(rot_matrix.at<double>(4)/size1)+asin(rot_matrix.at<double>(1)/size11)+asin(rot_matrix.at<double>(3)/size11))/2/PI*180<<endl;
		cout<<" "<<(acos(aff.at<double>(0)/size2)+acos(aff.at<double>(4)/size21)+asin(aff.at<double>(1)/size2)+asin(aff.at<double>(3)/size21))/2/PI*180<<endl;

		ofs<<size2<<"\t"<<(  acos((double)((aff.at<double>(0)/size2)))
							+asin((double)((aff.at<double>(1)/size2)))
							+asin((double)((aff.at<double>(3)/size21)))
							+acos((double)((aff.at<double>(4)/size21))))/2/PI*180<<endl;

//		ofs<<size2<<"\t"<<(  acos((double)((abs(aff.at<double>(0)/size2)>=1)?((abs(aff.at<double>(0)/size2)>=1)?1:-1):(aff.at<double>(0)/size2)))
//							+asin((double)((abs(aff.at<double>(1)/size2)>=1)?((abs(aff.at<double>(1)/size2)>=1)?1:-1):(aff.at<double>(1)/size2)))
//							+asin((double)((abs(aff.at<double>(3)/size21)>=1)?((abs(aff.at<double>(3)/size21)>=1)?1:-1):(aff.at<double>(3)/size21)))
//							+acos((double)((abs(aff.at<double>(4)/size21)>=1)?((abs(aff.at<double>(4)/size21)>=1)?1:-1):(aff.at<double>(4)/size21))))/2/PI*180<<endl;

//		cout<<" "<<(float)aff.at<float>(0)<<" "
//				<<(float)aff.at<float>(1)<<" "
//				<<(float)aff.at<float>(2)<<" "
//				<<(float)aff.at<float>(3)<<" "
//				<<(float)aff.at<float>(4)<<" "
//				<<(float)aff.at<float>(5)<<" "
//				<<endl;

		imwrite("cornerharrisdst_norm_scaled_cvt.bmp",cornerharrisdst_norm_scaled_cvt);
		imwrite("cdmat.bmp",cdmat);

		namedWindow( "b", CV_WINDOW_AUTOSIZE );
		//imshow( "b", sobelgray);//thrCrCb[0] );
		imshow( "b", cornerharrisdst_norm_scaled_cvt);//thrCrCb[0] );

		namedWindow( "c", CV_WINDOW_AUTOSIZE );
		imshow( "c", cdmat);//thrCrCb[0] );
		//namedWindow( "d", CV_WINDOW_AUTOSIZE );
		//imshow( "d", corImg);//thrCrCb[0] );

		waitKey(0);





	}
ofs.close();
waitKey(0);
/*
		cout<<"el: "<<(double)t<<endl;


		double cc;
		frid2.getFeatureVector(maxid[1],maxid[0],br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;


		frid2.getFeatureVector(maxid[1]+1,maxid[0],br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		frid2.getFeatureVector(maxid[1]-1,maxid[0],br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		frid2.getFeatureVector(maxid[1],maxid[0]+1,br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		frid2.getFeatureVector(maxid[1],maxid[0]-1,br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;


		frid2.getFeatureVector(maxid[1]+1,maxid[0]+1,br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		frid2.getFeatureVector(maxid[1]-1,maxid[0]+1,br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		frid2.getFeatureVector(maxid[1]+1,maxid[0]-1,br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		frid2.getFeatureVector(maxid[1]-1,maxid[0]-1,br,bg,bb,bsr,bsg,bsb);
		cc = ((ar-br)/PI*180+(ag-bg)/PI*180+(ab-bb)/PI*180)/3;
		if (cc>180) cc -= (((int) (cc/360))+1)*360;
		if (cc<-180) cc += (((int) (cc/360))+1)*360;
		cout<<"d: "<<cc<<endl;

		circle( cdmat, Point(maxid[1],maxid[0]), 1, Scalar( 0, 0, 255 ), -1, 8 );

		namedWindow( "a", CV_WINDOW_AUTOSIZE );
		imshow( "a", canny_);//thrCrCb[0] );
		namedWindow( "b", CV_WINDOW_AUTOSIZE );
		imshow( "b", sobelgray);//thrCrCb[0] );
		namedWindow( "c", CV_WINDOW_AUTOSIZE );
		imshow( "c", cdmat);//thrCrCb[0] );
		namedWindow( "d", CV_WINDOW_AUTOSIZE );
		imshow( "d", corImg);//thrCrCb[0] );
		corImg*=255;
		Mat corImg2; corImg.convertTo(corImg2,CV_8UC1);
		imwrite("bcorImg.bmp",corImg2);
		imwrite("bori.bmp",cdmat);
		imwrite("bsobel.bmp",sobel);
		waitKey(0);
		*/
	}
}



#endif

