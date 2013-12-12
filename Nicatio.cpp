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


//#define FR_for_integrated
//#define FR_for_separated
//#define FR_REGION
//#define Fileout

//#define CMUCROP
//#define LINEHISTEQUALIZE
//#define DOG
//#define DOGCIRCLE
//#define DMQIDOG
//#define DOGDMQI
//#define DMQICONTRASTSHIFT
//#define DMQI


//#define SMQI

//#define DMQIADVANCED
//#define BINFACE
//#define ROTATEFACEANGLEDETECTION
//#define ROTATEFACEANGLEDETECTIONDMQI

//#define FERET_face_database_120x120_normalization

//#define illuminationNormalization
#define textDetection
//#define faceDetection
//#define faceDetection3
//#define faceDetection_dog
//#define faceDetection2
//#define PCA_






#ifdef FERET_face_database_120x120_normalization
int main(int argc, char* argv[] ){
	const float EYE_DISTANCE = 95;//70.0;	/* final distance between eyes		*/
	const float EYEROW = 36;//45.0;		/* vertical position of eyes		*/
//	const int   NEW_ROW = 192;		/* size of images after normalization	*/
//	const int   NEW_COL = 168;
//	const float outw = 168;
//	const float outh = 192;
	const int   NEW_ROW = 168;		/* size of images after normalization	*/
	const int   NEW_COL = 168;
	const float outw = 168;
	const float outh = 168;

	//string dir = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	//string refLocation = string(argv[2]);
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/gallery.names";
	string gnd = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/data/ground_truths/name_value/";
	string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/gallery7/";
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
				//cout<<buffer4.str()<<endl;
				stringstream buffer5;
				buffer5<<svloc<<buffer<<".bmp";
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
				Point center = Point( im2.cols/2, im2.rows/2);
				Mat rot_mat = getRotationMatrix2D( center, -angle*180/PI, 1 );

				warpAffine( im2, rot, rot_mat, im2.size());


				  double  COS = cos(angle);
				   double SIN = sin(angle);


				  const float x0 = (int)((rx+lx)/2);
				  const float y0 = (int)((ry+ly)/2);
				  float xx = (COS*(lx-x0) - SIN*(ly-y0) + x0);
				  float yy = (SIN*(lx-x0) + COS*(ly-y0) + y0);
			      lx = xx;
			      ly = yy;


			      xx = (COS*(rx-x0) - SIN*(ry-y0) + x0);
			      yy = (SIN*(rx-x0) + COS*(ry-y0) + y0);
			      rx = xx;
			      ry = yy;
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
			FileI2.close();

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
//	cout<<"dDdddd"<<files.size()<<endl;
//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1;
//		cout<<"dDdddd"<<dir+"/"+files[i]<<endl;
//		_image1 = imread( dir+"/"+files[i], -1 );
//		Size size = _image1.size();
//
//		Mat _deno1(size,CV_8UC3);
//
//		GaussianBlur(_image1,_deno1,Size(55,55),0,0,BORDER_DEFAULT );
//
//
//		imwrite(dir+"/ga6/"+files[i]+".png",_deno1);
//	}
//}







//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1,_gauss;
//		_image1 = imread( dir+"/"+files[i], -1 );
//		GaussianBlur(_image1,_gauss,Size(15,15),0,0);
//		Size size = _image1.size();
//		int count=0;
//		for (double k=0.1; k<=1.001; k+=0.1){
//			Mat _resize,_resize2;
//			resize(_image1,_resize,Size(),k,k,INTER_LANCZOS4);
//			resize(_gauss,_resize2,Size(),k,k,INTER_LANCZOS4);
//
//			//namedWindow( "cat", CV_WINDOW_AUTOSIZE );
//			//namedWindow( "smoothed", CV_WINDOW_AUTOSIZE );
//			//imshow("cat", _resize);
//			//imshow("smoothed", _resize2);
//			//waitKey(0);
//			double psnr = getPSNR (_resize,_resize2);
//			Scalar ssim = getMSSIM(_resize,_resize2);
//
//
//
//			cout<<"A"<<k<<","<<psnr<<","<<ssim.val[2]<<","<<ssim.val[1]<<","<<ssim.val[0]<<","<<endl;
//
//
//
//			//resize(_resize,_resize,Size(),1./k,1./k,INTER_NEAREST);
//			//resize(_resize2,_resize2,Size(),1./k,1./k,INTER_NEAREST);
//
//			stringstream d;
//			d<<dir<<"/bs/"<<files[i]<<k<<"a.png";
//			stringstream e;
//						e<<dir<<"/bs/"<<files[i]<<k<<"b.png";
//			imwrite(d.str(),_resize);
//			imwrite(e.str(),_resize2);
//		}
//
//
//
//	}
//}
//
//double getPSNR(const Mat& I1, const Mat& I2)
//{
// Mat s1;
// absdiff(I1, I2, s1);       // |I1 - I2|
// s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
// s1 = s1.mul(s1);           // |I1 - I2|^2
//
// Scalar s = sum(s1);         // sum elements per channel
//
// double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
//
// if( sse <= 1e-10) // for small values return zero
//     return 0;
// else
// {
//     double  mse =sse /(double)(I1.channels() * I1.total());
//     double psnr = 10.0*log10((255*255)/mse);
//     return psnr;
// }
//}
//
//Scalar getMSSIM( const Mat& i1, const Mat& i2)
//{
// const double C1 = 6.5025, C2 = 58.5225;
// /***************************** INITS **********************************/
// int d     = CV_32F;
//
// Mat I1, I2;
// i1.convertTo(I1, d);           // cannot calculate on one byte large values
// i2.convertTo(I2, d);
//
// Mat I2_2   = I2.mul(I2);        // I2^2
// Mat I1_2   = I1.mul(I1);        // I1^2
// Mat I1_I2  = I1.mul(I2);        // I1 * I2
//
// /***********************PRELIMINARY COMPUTING ******************************/
//
// Mat mu1, mu2;   //
// GaussianBlur(I1, mu1, Size(11, 11), 1.5);
// GaussianBlur(I2, mu2, Size(11, 11), 1.5);
//
// Mat mu1_2   =   mu1.mul(mu1);
// Mat mu2_2   =   mu2.mul(mu2);
// Mat mu1_mu2 =   mu1.mul(mu2);
//
// Mat sigma1_2, sigma2_2, sigma12;
//
// GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
// sigma1_2 -= mu1_2;
//
// GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
// sigma2_2 -= mu2_2;
//
// GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
// sigma12 -= mu1_mu2;
//
// ///////////////////////////////// FORMULA ////////////////////////////////
// Mat t1, t2, t3;
//
// t1 = 2 * mu1_mu2 + C1;
// t2 = 2 * sigma12 + C2;
// t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
//
// t1 = mu1_2 + mu2_2 + C1;
// t2 = sigma1_2 + sigma2_2 + C2;
// t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
//
// Mat ssim_map;
// divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;
//
// Scalar mssim = mean( ssim_map ); // mssim = average of ssim map
// return mssim;
//}




//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1;
//		_image1 = imread( dir+"/"+files[i], -1 );
//		Size size = _image1.size();
//		Mat _bilateral;Mat _bilateral2;
//		Size size2 (_image1.cols/4,_image1.rows/4);
//		resize(_image1,_bilateral2,Size(),1./3,1./3,INTER_LINEAR);
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//		int kd=11;
//
////		cv::GaussianBlur(_bilateral2, _bilateral, cv::Size(0, 0), 15);
////		cv::addWeighted(_bilateral2, 3, _bilateral, -2, 0, _bilateral);
//
//		bilateralFilter (_bilateral2, _bilateral, kd, kd*2, kd/2 );
//		imwrite(dir+"/bilateral/"+files[i]+".png",_bilateral);
//
//
//		 Mat img, imgLaplacian, imgResult;
//
//		    //------------------------------------------------------------------------------------------- test, first of all
//		    // now do it by hand
//		    img = (Mat_<uchar>(4,4) << 0,1,2,3,4,5,6,7,8,9,0,11,12,13,14,15);
//
//		    // first, the good result
//		    Laplacian(img, imgLaplacian, CV_8UC1);
//		    cout << "let opencv do it" << endl;
//		    cout << imgLaplacian << endl;
//
//		    Mat kernel = (Mat_<float>(3,3) <<
//		        0,  1, 0,
//		        1, -4, 1,
//		        0,  1, 0);
//		    int window_size = 3;
//
//		    // now, reaaallly by hand
//		    // note that, for avoiding padding, the result image will be smaller than the original one.
//		    Mat frame, frame32;
//		    Rect roi;
//		    imgLaplacian = Mat::zeros(img.size(), CV_32F);
//		    for(int y=0; y<img.rows-window_size/2-1; y++) {
//		        for(int x=0; x<img.cols-window_size/2-1; x++) {
//		            roi = Rect(x,y, window_size, window_size);
//		            frame = img(roi);
//		            frame.convertTo(frame, CV_32F);
//		            frame = frame.mul(kernel);
//		            float v = sum(frame)[0];
//		            imgLaplacian.at<float>(y,x) = v;
//		        }
//		    }
//		    imgLaplacian.convertTo(imgLaplacian, CV_8U);
//		    cout << "dudee" << imgLaplacian << endl;
//
//		    // a little bit less "by hand"..
//		    // using cv::filter2D
//		    filter2D(img, imgLaplacian, -1, kernel);
//		    cout << imgLaplacian << endl;
//
//
//		    //------------------------------------------------------------------------------------------- real stuffs now
//		    img = _bilateral2; // load grayscale image
//
//		    // ok, now try different kernel
//		    kernel = (Mat_<float>(3,3) <<
//		        1,  1, 1,
//		        1, -8, 1,
//		        1,  1, 1); // another approximation of second derivate, more stronger
//		    kernel = (Mat_<float>(3,3) <<
//		        0,  1, 0,
//		        1, -4, 1,
//		        0,  1, 0);
//		    // do the laplacian filtering as it is
//		    // well, we need to convert everything in something more deeper then CV_8U
//		    // because the kernel has some negative values,
//		    // and we can expect in general to have a Laplacian image with negative values
//		    // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
//		    // so the possible negative number will be truncated
//		    filter2D(img, imgLaplacian, CV_32F, kernel);
//		    //filter2D(imgLaplacian, imgLaplacian, CV_32F, kernel);
//		    img.convertTo(img, CV_32F);
//		    imgResult = img - imgLaplacian;
//
//		    // convert back to 8bits gray scale
//		    imgResult.convertTo(imgResult, CV_8U);
//		    imgLaplacian.convertTo(imgLaplacian, CV_8U);
//		    bilateralFilter (imgResult, _bilateral, kd, kd*2, kd/2 );
//		    		imwrite(dir+"/sb/"+files[i]+".png",_bilateral);
//		    imwrite(dir+"/sharpen/"+files[i]+".png", imgResult);
//
//		    bilateralFilter (_image1, _bilateral, kd, kd*2, kd/2 );
//		    filter2D(_bilateral2, imgLaplacian, CV_32F, kernel);
//		    		    //filter2D(imgLaplacian, imgLaplacian, CV_32F, kernel);
//		    		    img.convertTo(img, CV_32F);
//		    		    imgResult = img - imgLaplacian;
//
//		    		    // convert back to 8bits gray scale
//		    		    imgResult.convertTo(imgResult, CV_8U);
//		    		    imgLaplacian.convertTo(imgLaplacian, CV_8U);
//
//		    imwrite(dir+"/bs/"+files[i]+".png",imgResult);
//
//	}
//}










//////cygdrive/e/2/

//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1;
//		_image1 = imread( dir+"/"+files[i], -1 );
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//		Mat _deno1(size,CV_8UC1);
//		Mat _deno2(size,CV_8UC1);
//		Mat _deno3(size,CV_8UC1);
//
//		Mat _gray(size,CV_8UC1);
//
//		Mat _homo=Mat::zeros(size,CV_8UC1);
//		Mat _homo2=Mat::zeros(size2,CV_8UC1);
//
//		Mat _bilateral(size,CV_8UC1);
//
//		Mat _dmqi(size,CV_8UC1);
//		Mat _histeq(size,CV_8UC1);
//		Mat ccanny(size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		nicatio::Grayscale(_image1.data, _gray.data,_image1.cols,_image1.rows);
//
//
//
//
//		cvNica::Denoise(_gray,_deno1);
//		cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi,101,55,0);
//		nicatio::HistEqualize(_dmqi.data,_deno2.data,_image1.cols,_image1.rows);
//		cvNica::DoG(_gray,_deno1,0.2,1,-2,0,0,0,1000);
//		equalizeHist(_deno1,_deno2);
//		threshold(_deno2,_deno3,224.0,255.0,THRESH_BINARY);
//		threshold(_deno2,_deno2,0.0,30.0,THRESH_BINARY);
//		bitwise_or(_deno2,_deno3,_deno2);
//		//medianBlur(_histeq,_deno2,3);
//		//_deno2=_histeq;
//		Canny(_gray,ccanny,70,150);
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		int kd=5;
//
//		//cvNica::DifferenceOfVariance(_bilateral,ccanny);
//		//cvNica::VarianceFilter(_gray,ccanny,3);
//		//ccanny.convertTo(ccanny,CV_8UC1);
//		//Canny(_bilateral,ccanny,60,20);
//		//Canny(ccanny,ccanny,70,30);
//		//cvNica::VarianceFilter(_gray,ccanny,7);
//		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
//		//bitwise_and(ccanny,_homo,_homo);
//
////131016
////		Mat _gray2;
////		medianBlur(_gray,_gray,3);
////		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
////		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
////
////
////		Mat im3(_image1.rows*3, _image1.cols*4, CV_8UC1);
////		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
////		resize(_homo2,_homo,size,0,0,INTER_LINEAR);
////
////		Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
////		_homo.copyTo(right);
////
////		for (int j=1; j<=8; j++) {
////			Mat _k=Mat::zeros(size,CV_8UC1);
////			Mat _h=Mat::zeros(size2,CV_8UC1);
////			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j);
////			resize(_h,_k,size,0,0,INTER_LINEAR);
////			Mat right(im3, Rect(_image1.cols*((j-1)%4), _image1.rows*((int)((j-1)/4)+1), _image1.cols, _image1.rows));
////			_k.copyTo(right);
////		}
//
//
//
//
//		// 131023
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//		Mat varF,varF2;
//		//cvNica::VarianceFilter(_gray2,varF2,3);
//		cvNica::DifferenceOfVariance(_gray2,varF2);
//		varF2.convertTo(varF2,CV_8UC1);
//		normalize(varF2, varF2, 0, 255, NORM_MINMAX, CV_8UC1);
//
//		resize(varF2,varF,size,0,0,INTER_LINEAR);
//
//		Mat im3(_image1.rows*2, _image1.cols*4, CV_8UC1);
//		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//
//		Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
//		Mat right2(im3, Rect(_image1.cols*2, 0, _image1.cols, _image1.rows));
//		Mat right3(im3, Rect(_image1.cols*3, 0, _image1.cols, _image1.rows));
//
//
//
//		for (int j=1; j<=4; j++) {
//			Mat _k=Mat::zeros(size,CV_8UC1);
//			Mat _h=Mat::zeros(size2,CV_8UC1);
//			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j);
//			resize(_h,_k,size,0,0,INTER_LINEAR);
//			Mat right(im3, Rect(_image1.cols*((j-1)%4), _image1.rows*((int)((j-1)/4)+1), _image1.cols, _image1.rows));
//			_k.copyTo(right);
//		}
//		//normalize(_homo, _homo, 0, 255, NORM_MINMAX, CV_8UC1);
//
//		threshold(_homo,_homo,30,255,THRESH_BINARY);
//
//		_homo.copyTo(right);
//
//
//		normalize(_homo, varF, 0, 255, NORM_MINMAX, CV_8UC1);
//		Mat skel( size, CV_8UC1, cv::Scalar(0));
//		Mat temp( size, CV_8UC1);
//		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//		bool done;
//		do
//		{
//		  morphologyEx(_homo, temp, cv::MORPH_OPEN, element);
//		  bitwise_not(temp, temp);
//		  bitwise_and(_homo, temp, temp);
//		  bitwise_or(skel, temp, skel);
//		  erode(_homo, _homo, element);
//
//		  double max;
//		  minMaxLoc(_homo, 0, &max);
//		  done = (max == 0);
//		} while (!done);
//
//
//		Mat left(im3, Rect(0, 0, _image1.cols, _image1.rows));
//		_gray.copyTo(left);
//
//		//Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
//
//		//skel.copyTo(right2);
//
//		varF.copyTo(right2);
//		sobel.copyTo(right3);
//		//ccanny.copyTo(right3);
//		imwrite(dir+"/set013/"+files[i]+".png",im3);
//		cout<<files[i]<<endl;
//	}


//// 131106
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1 = imread( dir+"/"+files[i], -1 );;
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		Mat sobelColor;
//		Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
//
//
//		//grayscale
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		//bilateral + 2x
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//		//sobel
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		cvtColor(sobel,sobelColor,CV_GRAY2RGB);
//
//
//
//
//
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoOverlay2,_homoInv,_homoColorOrig,_homoThresholdColor;
//		Mat _homo2=Mat::zeros(size2,CV_8UC1);
//		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//		threshold(_homo,_homoThreshold,30,255,THRESH_BINARY);
//		_homoInv = 255-_homoThreshold;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(_homoThreshold,_gray,_homoOverlay);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay2,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//
//		Mat mergePos [8];
//		for (int k=0; k<=1; k++) {
//			for (int j=0; j<=3; j++) {
//				mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
//			}
//		}
//		for (int j=0; j<=3; j++) {
//
//			Mat varmap,varmap2,varmapColor;
//			cvNica::VarianceMap(_gray,varmap,j*2+9);
//			cvNica::VarianceMap(_gray,varmap2,j*2+1+9);
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap2,varmap};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//			varmapColor.copyTo(mergePos[j+4]);
////			Mat _c;
////			Mat _k=Mat::zeros(size,CV_8UC1);
////			Mat _h=Mat::zeros(size2,CV_8UC1);
////			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j+1);
////			resize(_h,_k,size,0,0,INTER_LINEAR);
////			cvtColor (_k,_c,CV_GRAY2RGB);
////			_c.copyTo(mergePos[j+4]);
//		}
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (_homoThreshold,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		_homoColorOrig.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//		imwrite(dir+"/set014/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//	}

//	Mat _image11 = imread("P03g.bmp",-1),_image1;
//	resize(_image11,_image1,Size(0,0),.2,.2);
//	Size size12 = _image1.size();
//	Mat _deno1(size12,CV_8UC1);
//	Mat _dmqi(size12,CV_8UC1);
//	Mat _histeq(size12,CV_8UC1);
//	Mat temp2(size12,CV_8UC1);cvNica::DoG(_image1,temp2,0.2,1,-2,0,0,0,10);
//	cvNica::Denoise(temp2,_deno1);
//	//_deno1=_image1;
//	//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
//	cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
//	//_dmqi=_deno1;
//	//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
//	//_dmqi = 255-_dmqi;
//	//equalizeHist(_dmqi,_histeq);
//	nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
//
//
//
//			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//			imshow( "c", _dmqi);//thrCrCb[0] );
//			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//						imshow( "d", _histeq);//thrCrCb[0] );
//						namedWindow( "e", CV_WINDOW_AUTOSIZE );
//									imshow( "e", temp2);
//			waitKey(0);




//	// 131118
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1 = imread( dir+"/"+files[i], -1 );;
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		Mat sobelColor;
//		Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
//
//
//		//grayscale
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		//bilateral + 2x
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//		//sobel
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		cvtColor(sobel,sobelColor,CV_GRAY2RGB);
//
//
//		Mat mergePos [8];
//		for (int k=0; k<=1; k++) {
//			for (int j=0; j<=3; j++) {
//				mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//		for (int j=0; j<=3; j++) {
//			Mat varmap_,varmap,varmapColor;
//			cvNica::CornerDetector(_gray,varmap,j+5);
//
//			//varmap_.convertTo(varmap,CV_8UC1);
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),Mat::zeros(size,CV_8UC1),varmap};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//			varmapColor.copyTo(mergePos[j+4]);
//
//			//threshold(varmap,varmap,10,255,THRESH_BINARY);
//			threshold(varmap,varmap,10,255,THRESH_BINARY);
//
//			varmap4Merge += varmap;
//		}
//
////		namedWindow( "c", CV_WINDOW_AUTOSIZE );
////		imshow( "c", varmap4Merge);//thrCrCb[0] );
////		waitKey(0);
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoOverlay2,_homoInv,_homoColorOrig,_homoThresholdColor;
//		//Mat _homo2=Mat::zeros(size2,CV_8UC1);
//		//cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		//resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//		//threshold(_homo,_homoThreshold,30,255,THRESH_BINARY);
//
//		//varmap4Merge.convertTo(_homoThreshold,CV_8UC1);
//
//		_homoThreshold = varmap4Merge;
//
//		_homoInv = 255-_homoThreshold;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(_homoThreshold,_gray,_homoOverlay);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay2,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (_homoThreshold,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		_homoColorOrig.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//		imwrite(dir+"/set016/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//	}

//	// 131119
//		int kd=5;
//		for (unsigned int i = 0;i < files.size();i++) {
//			Mat d1 = imread( dir+"/"+files[i], -1 );;
//			int dilation_type = MORPH_RECT;
//			Mat oneso = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//			Mat _image1,d2;
//			dilate(d1,d2,oneso);
//			erode(d2,_image1,oneso);
//
//			Size size = _image1.size();
//			Size size2 (_image1.cols*2,_image1.rows*2);
//			Mat _gray (size,CV_8UC1),_grayRGB;
//			Mat _bilateral (size,CV_8UC1);
//			Mat sobelx(size,CV_8UC1);
//			Mat sobely(size,CV_8UC1);
//			Mat gradx(size,CV_8UC1);
//			Mat grady(size,CV_8UC1);
//			Mat sobel(size,CV_8UC1);
//			Mat canny(size,CV_8UC1);
//			Mat sobelColor;
//			Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
//
//
//
//			//grayscale
//			cvtColor(_image1,_gray,CV_RGB2GRAY);
//			cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//			Canny(_gray,canny,60,120);
//
////					namedWindow( "c", CV_WINDOW_AUTOSIZE );
////					imshow( "c", canny);//thrCrCb[0] );
////					waitKey(0);
//
//			//bilateral + 2x
//			Mat _gray2;
//			medianBlur(_gray,_gray,3);
//			bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//			resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//			//sobel
//			Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//			convertScaleAbs( sobelx, gradx );
//			Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//			convertScaleAbs( sobely, grady );
//			addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//			cvtColor(sobel,sobelColor,CV_GRAY2RGB);
//
//
//			Mat mergePos [8];
//			for (int k=0; k<=1; k++) {
//				for (int j=0; j<=3; j++) {
//					mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
//				}
//			}
//
//			Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//			Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
//			for (int j=0; j<=3; j++) {
//				Mat varmap__,varmap_,varmap,varmapColor;
//				cvNica::CornerDetector(_gray,varmap_,j+21);
//				cvNica::CornerDetectorBasedOnEdge(canny,varmap__,j+40);
//				threshold(varmap_,varmap_,8,255,THRESH_BINARY);
//
//				bitwise_and(varmap_,varmap__,varmap);
//				//varmap = varmap__;
//				//varmap_.convertTo(varmap,CV_8UC1);
//				Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap__,varmap};
//				merge(varmapColor_,3,varmapColor);
//				varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//				varmapColor.copyTo(mergePos[j+4]);
//
//				//threshold(varmap,varmap,10,255,THRESH_BINARY);
//				//threshold(varmap,varmap,10,255,THRESH_BINARY);
//
//				varmap4Merge += varmap;
//				varmap4Merge2 += varmap__;
//			}
//
//	//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	//		imshow( "c", varmap4Merge);//thrCrCb[0] );
//	//		waitKey(0);
//			Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
//			//Mat _homo2=Mat::zeros(size2,CV_8UC1);
//			//cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//			//resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//			//threshold(_homo,_homoThreshold,30,255,THRESH_BINARY);
//
//			//varmap4Merge.convertTo(_homoThreshold,CV_8UC1);
//
//			//_homoThreshold = varmap4Merge;
//
//			_homoInv = 255-varmap4Merge;
//			bitwise_and(_homoInv,_gray,_homoOverlay2);
//			bitwise_or(varmap4Merge,_gray,_homoOverlay);
//			bitwise_or(varmap4Merge2,_gray,_homoOverlay3);
//
//			Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay2,_homoOverlay};
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
//			_homoColor2.copyTo(mergePos[3]);
//			_homoThresholdColor.copyTo(mergePos[2]);
//			imwrite(dir+"/set019/"+files[i]+".png",merged);
//			cout<<files[i]<<endl;
//		}


//	// 131122 set 020~023
//	int kd=5;
//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1 = imread( dir+"/"+files[i], -1 );;
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		Mat sobelColor;
//		Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
//
//
//		//grayscale
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		//bilateral + 2x
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//		//sobel
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		cvtColor(sobel,sobelColor,CV_GRAY2RGB);
//
//
//		Mat mergePos [8];
//		for (int k=0; k<=1; k++) {
//			for (int j=0; j<=3; j++) {
//				mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
//			}
//		}
//
//		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
//		for (int j=0; j<=1; j++) {
//			Mat varmap_,varmap,varmapColor;
//			cvNica::CornerDetector(_gray,varmap,j+39,3);
//
//			//varmap_.convertTo(varmap,CV_8UC1);
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),Mat::zeros(size,CV_8UC1),varmap};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//			varmapColor.copyTo(mergePos[j+4]);
//
//			//threshold(varmap,varmap,10,255,THRESH_BINARY);
//			threshold(varmap,varmap,10,255,THRESH_BINARY);
//
//			varmap4Merge += varmap;
//		}
//
////		namedWindow( "c", CV_WINDOW_AUTOSIZE );
////		imshow( "c", varmap4Merge);//thrCrCb[0] );
////		waitKey(0);
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoOverlay2,_homoInv,_homoColorOrig,_homoThresholdColor;
//		//Mat _homo2=Mat::zeros(size2,CV_8UC1);
//		//cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		//resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//		//threshold(_homo,_homoThreshold,30,255,THRESH_BINARY);
//
//		//varmap4Merge.convertTo(_homoThreshold,CV_8UC1);
//
//		_homoThreshold = varmap4Merge;
//
//		_homoInv = 255-_homoThreshold;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(_homoThreshold,_gray,_homoOverlay);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay,_homoOverlay2};
//		merge(_homoColor_,3,_homoColor);
//
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (_homoThreshold,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		_homoColorOrig.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//		imwrite(dir+"/set023 39-40 var25/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//	}


	// 131122 set 024
	int kd=5;
	for (unsigned int i = 0;i < files.size();i++) {
//		Mat d1 = imread( dir+"/"+files[i], -1 );;
//		int dilation_type = MORPH_RECT;
//		Mat oneso = getStructuringElement( dilation_type, Size( 3,3 ), Point( 1,1 ) );
//		Mat _image1,d2;
//		dilate(d1,d2,oneso);
//		erode(d2,_image1,oneso);
		Vector< Vector<int> > cornerpoints;

		Mat _image1 = imread( dir+"/"+files[i], -1 );


		Size size = _image1.size();
		Size size2 (_image1.cols*2,_image1.rows*2);
		Mat _gray (size,CV_8UC1),_grayRGB;
		Mat _bilateral (size,CV_8UC1);
		Mat sobelx(size,CV_8UC1);
		Mat sobely(size,CV_8UC1);
		Mat gradx(size,CV_8UC1);
		Mat grady(size,CV_8UC1);
		Mat sobel(size,CV_8UC1);
		Mat canny(size,CV_8UC1);
		Mat sobelColor;
		Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
		Mat _image1_split[3];
		Mat _bilateral3 (size,CV_8UC3);
		bilateralFilter (_image1, _bilateral3 , kd, kd*2, kd/2 );
		medianBlur(_bilateral3,_bilateral3,3);

		split (_bilateral3,_image1_split);




//		//grayscale
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//		Canny(_gray,canny,60,120);
//
////					namedWindow( "c", CV_WINDOW_AUTOSIZE );
////					imshow( "c", canny);//thrCrCb[0] );
////					waitKey(0);
//
//		//bilateral + 2x
////		Mat _gray2;
////		medianBlur(_gray,_gray,5);
//		Mat _gray2; _gray.copyTo(_gray2);
//		bilateralFilter (_gray2, _gray, kd, kd*2, kd/2 );
////		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//		medianBlur(_gray,_gray,3);
//		//sobel
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		cvtColor(sobel,sobelColor,CV_GRAY2RGB);


		Mat mergePos [8];
		for (int k=0; k<=1; k++) {
			for (int j=0; j<=3; j++) {
				mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
			}
		}

		Mat varmap4Merge = Mat::zeros(size,CV_8UC1);
		Mat varmap4Merge2 = Mat::zeros(size,CV_8UC1);
		for (int j=0; j<=3; j++) {
			Mat varmap__[4],varmap_[4],varmap[4],varmapColor,ccanny[4];

			for (int k=0; k<3; k++) {
				Mat temp;
				//_image1_split[k].copyTo(temp);
						//medianBlur(_image1_split[k],_image1_split[k],5);


				cvNica::CornerDetector(_image1_split[k],varmap_[k],j+41);
				Canny(_image1_split[k],ccanny[k],70,120);
				cvNica::CornerDetectorBasedOnEdge(ccanny[k],varmap__[k],j+40);

//				namedWindow( "c", CV_WINDOW_AUTOSIZE );
//				imshow( "c", varmap_[k]);//thrCrCb[0] );
//				waitKey(0);
				threshold(varmap_[k],varmap_[k],15,255,THRESH_BINARY);
				bitwise_and(varmap_[k],varmap__[k],varmap[k]);
				//bitwise_and(varmap_,varmap__,varmap);

			}

//			max(varmap_[0],varmap_[1],varmap_[3]);
//			max(varmap_[3],varmap_[2],varmap_[3]);
			max(varmap[0],varmap[1],varmap[3]);
			max(varmap[3],varmap[2],varmap[3]);
			max(varmap__[0],varmap__[1],varmap__[3]);
			max(varmap__[3],varmap__[2],varmap__[3]);
//			max(ccanny[0],ccanny[1],ccanny[3]);
//			max(ccanny[3],ccanny[2],ccanny[3]);
//			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//			imshow( "c", varmap[3]);//thrCrCb[0] );
//			waitKey(0);
			cvNica::RGBhistogram(_bilateral3,varmap[3],cornerpoints,j+41,2);

			Mat km1,km2,km3,pp1,pp2,pp3;
			km1 = cvNica::RGBThreshold(_bilateral3,214,186,187,30);
			km2 = cvNica::RGBThreshold(_bilateral3,155, 78,120,30);
			km3 = cvNica::RGBThreshold(_bilateral3,123, 57,124,30);
			pp1 = cvNica::RGBThresholdPoint(size,cornerpoints,214,186,187,30);
			pp2 = cvNica::RGBThresholdPoint(size,cornerpoints,155, 78,120,30);
			pp3 = cvNica::RGBThresholdPoint(size,cornerpoints,123, 57,124,30);
//			namedWindow( "a", CV_WINDOW_AUTOSIZE );
//			imshow( "a", km1);//thrCrCb[0] );
//			namedWindow( "b", CV_WINDOW_AUTOSIZE );
//			imshow( "b", km2);//thrCrCb[0] );
//			namedWindow( "c", CV_WINDOW_AUTOSIZE );
//			imshow( "c", km3);//thrCrCb[0] );
//			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//			imshow( "d", pp1);//thrCrCb[0] );
//			namedWindow( "e", CV_WINDOW_AUTOSIZE );
//			imshow( "e", pp2);//thrCrCb[0] );
//			namedWindow( "f", CV_WINDOW_AUTOSIZE );
//			imshow( "f", pp3);//thrCrCb[0] );
//			waitKey(0);
			  //214.0000  186.0000  187.0000
			  //155.0000   78.0000  120.5000
			  //123.0000   57.0000  124.0000

			Mat kmColor1;
			Mat kmColor1_[3] = {pp1,km1-127,pp1};
			merge(kmColor1_,3,kmColor1);
			Mat kmColor2;
			Mat kmColor2_[3] = {pp2,km2-127,pp2};
			merge(kmColor2_,3,kmColor2);
			Mat kmColor3;
			Mat kmColor3_[3] = {pp3,km3-127,pp3};
			merge(kmColor3_,3,kmColor3);
			namedWindow( "a", CV_WINDOW_AUTOSIZE );
			imshow( "a", kmColor1);//thrCrCb[0] );
			namedWindow( "b", CV_WINDOW_AUTOSIZE );
			imshow( "b", kmColor2);//thrCrCb[0] );
			namedWindow( "c", CV_WINDOW_AUTOSIZE );
			imshow( "c", kmColor3);//thrCrCb[0] );
			waitKey(0);
			max(varmap[0],varmap[1],varmap[3]);
			max(varmap[3],varmap[2],varmap[3]);
//							namedWindow( "c", CV_WINDOW_AUTOSIZE );
//							imshow( "c", varmap[3]);//thrCrCb[0] );
//							waitKey(0);

			//varmap = varmap__;
			//varmap_.convertTo(varmap,CV_8UC1);
//							cout<<"D "<<varmap__[3].depth()<<endl;
//							cout<<"D "<<varmap[3].depth()<<endl;
							//cout<<"D "<<size.width<<size.height<<endl;
			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap__[3],varmap[3]};
			merge(varmapColor_,3,varmapColor);
			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
			varmapColor.copyTo(mergePos[j+4]);

			//threshold(varmap,varmap,10,255,THRESH_BINARY);
			//threshold(varmap,varmap,10,255,THRESH_BINARY);

			varmap4Merge += varmap[3];
			varmap4Merge2 += varmap__[3];


//			Mat varmap__,varmap_,varmap,varmapColor;
//			cvNica::CornerDetector(_gray,varmap_,j+41);
//			cvNica::CornerDetectorBasedOnEdge(canny,varmap__,j+40);
//			threshold(varmap_,varmap_,8,255,THRESH_BINARY);
//
//			//bitwise_and(varmap_,varmap__,varmap);
//			bitwise_and(varmap_,varmap_,varmap);
//			//varmap = varmap__;
//			//varmap_.convertTo(varmap,CV_8UC1);
//			Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap__,varmap};
//			merge(varmapColor_,3,varmapColor);
//			varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//			varmapColor.copyTo(mergePos[j+4]);
//
//			//threshold(varmap,varmap,10,255,THRESH_BINARY);
//			//threshold(varmap,varmap,10,255,THRESH_BINARY);
//
//			varmap4Merge += varmap;
//			varmap4Merge2 += varmap__;
		}

//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", varmap4Merge);//thrCrCb[0] );
//		waitKey(0);
		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoColor2,_homoOverlay2,_homoOverlay3,_homoInv,_homoColorOrig,_homoThresholdColor;
		//Mat _homo2=Mat::zeros(size2,CV_8UC1);
		//cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
		//resize(_homo2,_homo,size,0,0,INTER_LINEAR);
		//threshold(_homo,_homoThreshold,30,255,THRESH_BINARY);

		//varmap4Merge.convertTo(_homoThreshold,CV_8UC1);

		//_homoThreshold = varmap4Merge;

		_homoInv = 255-varmap4Merge;
		bitwise_and(_homoInv,_gray,_homoOverlay2);
		bitwise_or(varmap4Merge,_gray,_homoOverlay);
		bitwise_or(varmap4Merge2,_gray,_homoOverlay3);

		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay2,_homoOverlay};
		Mat _homoColor_2[3] = {_homoOverlay2,_homoOverlay3,_homoOverlay};
		merge(_homoColor_,3,_homoColor);
		merge(_homoColor_2,3,_homoColor2);

		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
		cvtColor (varmap4Merge,_homoThresholdColor,CV_GRAY2RGB);




		_image1.copyTo(mergePos[0]);
		_homoColor.copyTo(mergePos[1]);
		_homoColor2.copyTo(mergePos[3]);
		_homoThresholdColor.copyTo(mergePos[2]);
		imwrite(dir+"/set024/"+files[i]+".png",merged);
		cout<<files[i]<<endl;
	}


//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1 = imread( dir+"/"+files[i], -1 );;
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//		Mat _gray (size,CV_8UC1),_grayRGB;
//		Mat _bilateral (size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		Mat sobelColor;
//		Mat merged(_image1.rows*2, _image1.cols*4, CV_8UC3);
//
//
//		//grayscale
//		cvtColor(_image1,_gray,CV_RGB2GRAY);
//		cvtColor(_gray,_grayRGB,CV_GRAY2RGB);
//
//
//		//bilateral + 2x
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//		//sobel
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		cvtColor(sobel,sobelColor,CV_GRAY2RGB);
//
//
//		Mat varmap,varmap2,varmapColor;
//		cvNica::VarianceMap(_gray,varmap,0);
//		cvNica::VarianceMap(_gray,varmap2,1);
//		Mat varmapColor_[3] = {Mat::zeros(size,CV_8UC1),varmap2,varmap};
//		merge(varmapColor_,3,varmapColor);
//		varmapColor = varmapColor*0.9 + _grayRGB*0.1;
//
//
//		Mat _homo,_homoThreshold,_homoOverlay,_homoColor,_homoOverlay2,_homoInv,_homoColorOrig,_homoThresholdColor;
//		Mat _homo2=Mat::zeros(size2,CV_8UC1);
//		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//		threshold(_homo,_homoThreshold,30,255,THRESH_BINARY);
//		_homoInv = 255-_homoThreshold;
//		bitwise_and(_homoInv,_gray,_homoOverlay2);
//		bitwise_or(_homoThreshold,_gray,_homoOverlay);
//
//		Mat _homoColor_[3] = {_homoOverlay2,_homoOverlay2,_homoOverlay};
//		merge(_homoColor_,3,_homoColor);
//
//		Mat mergePos [8];
//		for (int k=0; k<=1; k++) {
//			for (int j=0; j<=3; j++) {
//				mergePos[j+k*4] = Mat(merged, Rect(_image1.cols*(j%4), _image1.rows*((int)(j/4)+k), _image1.cols, _image1.rows));
//			}
//		}
//		for (int j=0; j<=3; j++) {
//			Mat _c;
//			Mat _k=Mat::zeros(size,CV_8UC1);
//			Mat _h=Mat::zeros(size2,CV_8UC1);
//			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j+1);
//			resize(_h,_k,size,0,0,INTER_LINEAR);
//			cvtColor (_k,_c,CV_GRAY2RGB);
//			_c.copyTo(mergePos[j+4]);
//		}
//		cvtColor (_homo,_homoColorOrig,CV_GRAY2RGB);
//		cvtColor (_homoThreshold,_homoThresholdColor,CV_GRAY2RGB);
//
//
//
//
//		_image1.copyTo(mergePos[0]);
//		_homoColor.copyTo(mergePos[1]);
//		_homoColorOrig.copyTo(mergePos[3]);
//		_homoThresholdColor.copyTo(mergePos[2]);
//		imwrite(dir+"/set013/"+files[i]+".png",merged);
//		cout<<files[i]<<endl;
//	}




//
//	for (unsigned int i = 0;i < files.size();i++) {
//		Mat _image1;
//		_image1 = imread( dir+"/"+files[i], -1 );
//		Size size = _image1.size();
//		Size size2 (_image1.cols*2,_image1.rows*2);
//
//		Mat _deno1(size,CV_8UC1);
//		Mat _deno2(size,CV_8UC1);
//		Mat _deno3(size,CV_8UC1);
//
//		Mat _gray(size,CV_8UC1);
//
//		Mat _homo=Mat::zeros(size,CV_8UC1);
//		Mat _homo2=Mat::zeros(size2,CV_8UC1);
//
//		Mat _bilateral(size,CV_8UC1);
//
//		Mat _dmqi(size,CV_8UC1);
//		Mat _histeq(size,CV_8UC1);
//		Mat ccanny(size,CV_8UC1);
//		Mat sobelx(size,CV_8UC1);
//		Mat sobely(size,CV_8UC1);
//		Mat gradx(size,CV_8UC1);
//		Mat grady(size,CV_8UC1);
//		Mat sobel(size,CV_8UC1);
//		nicatio::Grayscale(_image1.data, _gray.data,_image1.cols,_image1.rows);
//
//
//
//
//		cvNica::Denoise(_gray,_deno1);
//		cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi,101,55,0);
//		nicatio::HistEqualize(_dmqi.data,_deno2.data,_image1.cols,_image1.rows);
//		cvNica::DoG(_gray,_deno1,0.2,1,-2,0,0,0,1000);
//		equalizeHist(_deno1,_deno2);
//		threshold(_deno2,_deno3,224.0,255.0,THRESH_BINARY);
//		threshold(_deno2,_deno2,0.0,30.0,THRESH_BINARY);
//		bitwise_or(_deno2,_deno3,_deno2);
//		//medianBlur(_histeq,_deno2,3);
//		//_deno2=_histeq;
//		Canny(_gray,ccanny,70,150);
//		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobelx, gradx );
//		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
//		convertScaleAbs( sobely, grady );
//		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
//		int kd=5;
//
//
//		// 131023
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//		Mat varF,varF2;
//		//cvNica::VarianceFilter(_gray2,varF2,3);
//		cvNica::DifferenceOfVariance(_gray2,varF2);
//		varF2.convertTo(varF2,CV_8UC1);
//		normalize(varF2, varF2, 0, 255, NORM_MINMAX, CV_8UC1);
//
//		resize(varF2,varF,size,0,0,INTER_LINEAR);
//
//		Mat im3(_image1.rows*2, _image1.cols*4, CV_8UC1);
//		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//
//		Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
//		Mat right2(im3, Rect(_image1.cols*2, 0, _image1.cols, _image1.rows));
//		Mat right3(im3, Rect(_image1.cols*3, 0, _image1.cols, _image1.rows));
//
//
//
//		for (int j=1; j<=4; j++) {
//			Mat _k=Mat::zeros(size,CV_8UC1);
//			Mat _h=Mat::zeros(size2,CV_8UC1);
//			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j);
//			resize(_h,_k,size,0,0,INTER_LINEAR);
//			Mat right(im3, Rect(_image1.cols*((j-1)%4), _image1.rows*((int)((j-1)/4)+1), _image1.cols, _image1.rows));
//			_k.copyTo(right);
//		}
//		//normalize(_homo, _homo, 0, 255, NORM_MINMAX, CV_8UC1);
//
//		threshold(_homo,_homo,30,255,THRESH_BINARY);
//
//		_homo.copyTo(right);
//
//
//		normalize(_homo, varF, 0, 255, NORM_MINMAX, CV_8UC1);
//		Mat skel( size, CV_8UC1, cv::Scalar(0));
//		Mat temp( size, CV_8UC1);
//		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
//		bool done;
//		do
//		{
//		  morphologyEx(_homo, temp, cv::MORPH_OPEN, element);
//		  bitwise_not(temp, temp);
//		  bitwise_and(_homo, temp, temp);
//		  bitwise_or(skel, temp, skel);
//		  erode(_homo, _homo, element);
//
//		  double max;
//		  minMaxLoc(_homo, 0, &max);
//		  done = (max == 0);
//		} while (!done);
//
//
//		Mat left(im3, Rect(0, 0, _image1.cols, _image1.rows));
//		_gray.copyTo(left);
//
//		//Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
//
//		//skel.copyTo(right2);
//
//		varF.copyTo(right2);
//		sobel.copyTo(right3);
//		//ccanny.copyTo(right3);
//		imwrite(dir+"/set013/"+files[i]+".png",im3);
//		cout<<files[i]<<endl;
//	}

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
		cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
		cout<<"2 "<<fr.getAccuracyIncludingBadImages()<<" "<<endl;
		fr.getAccuracyIncludingBadImagesSubset();

		FileStorage abcd("dix.xml",FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		abcd.release();

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
		cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
		cout<<"2 "<<fr.getAccuracyIncludingBadImages()<<" "<<endl;
		fr.getAccuracyIncludingBadImagesSubset();

		FileStorage abcd(argv[4],FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		abcd.release();

		FileStorage abcd2(argv[5],FileStorage::WRITE);
		abcd2 << "frRecognitionResult" << fr.RecognitionScore;
		abcd2.release();
#endif



#ifdef FR_REGION
		int pos[52]= {0,0,167,10,	 // �̸�
		0,11,64,65,	 // �޴�
		65,11,102,65,	 // �̰�
		103,11,167,65,	 // ������
		0,66,50,114,	 // �� ����
		51,66,116,114,	 // ��
		117,66,167,114,	 // �� ������
		0,115,83,134,	 // ���� ����
		84,115,167,134,   // ���� ������
		0,135,39,162,	 // �� ����
		40,135,127,162,	 // ��
		128,135,167,162,	 // �� ������
		0,163,167,191};	 // ��
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

#ifdef DMQI
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
			cvNica::RemoveGrainyNoise(_dmqi,_deno1,50);
			cvNica::RemoveGrainyNoise(_deno1,_deno2,50);

			//cvNica::RemoveGrainyNoise(_dmqi,_histeq,30);
			//nicatio::HistEqualize(_dmqi.data,_deno2.data,_image1.cols,_image1.rows);

			unsigned found = files[i].rfind("bad");
						vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
						imwrite(dir+"/dmqi/"+tokens[0]+"."+dataType,_deno2);
						if (found!=std::string::npos)
							rename( string(dir+"/dmqi/"+tokens[0]+"."+dataType).c_str() , string(dir+"/dmqi/"+tokens[0]+"."+dataType+".bad").c_str() );


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

#ifdef SMQI
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
			//nicatio::MedianFilter(_image1.data,_deno1.data,_image1.cols,_image1.rows);
			//nicatio::Denoise( _image1.data,_deno1.data,_image1.cols,_image1.rows);
			cvNica::Denoise(_image1,_deno1);
			//_deno1=_image1;
			//cvNica::DynamicMorphQuotImage(_deno1,_dmqi,0);
			cvNica::SelectiveMorphQuotImage(_deno1,_dmqi,0);
			//_dmqi=_deno1;
			//nicatio::DynamicMorphQuotImage( _deno1.data,_dmqi.data,_image1.cols,_image1.rows, 0);
			//_dmqi = 255-_dmqi;
			//equalizeHist(_dmqi,_histeq);
			nicatio::HistEqualize(_dmqi.data,_histeq.data,_image1.cols,_image1.rows);
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
			_deno2=_histeq;
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
			imwrite(dir+"/smqi/"+tokens[0]+"."+dataType,_deno2);
			if (found!=std::string::npos)
				rename( string(dir+"/smqi/"+tokens[0]+"."+dataType).c_str() , string(dir+"/smqi/"+tokens[0]+"."+dataType+".bad").c_str() );

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
