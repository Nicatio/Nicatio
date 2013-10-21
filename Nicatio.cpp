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
//#define PCA_




#ifdef FERET_face_database_120x120_normalization
int main(int argc, char* argv[] ){
	const float EYE_DISTANCE = 95;//70.0;	/* final distance between eyes		*/
	const float EYEROW = 48;//45.0;		/* vertical position of eyes		*/
	const int   NEW_ROW = 192;		/* size of images after normalization	*/
	const int   NEW_COL = 168;
	const float outw = 168;
	const float outh = 192;

	//string dir = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	//string refLocation = string(argv[2]);
	//string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/probe_fafc_diffcamera_diffillum.names";
	string names = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd2/partitions/by_previously_reported/feret/gallery.names";
	string gnd = "/cygdrive/e/Downloads/colorferet/colorferet/dvd2/gray_feret_cd1/data/ground_truths/name_value/";
	string svloc = "/cygdrive/e/Documents/Nicatio/Research/DB/Face/feret/gallery4/";
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

	for (unsigned int i = 0;i < files.size();i++) {
		Mat _image1;
		_image1 = imread( dir+"/"+files[i], -1 );
		Size size = _image1.size();
		Size size2 (_image1.cols*2,_image1.rows*2);

		Mat _deno1(size,CV_8UC1);
		Mat _deno2(size,CV_8UC1);
		Mat _deno3(size,CV_8UC1);

		Mat _gray(size,CV_8UC1);

		Mat _homo=Mat::zeros(size,CV_8UC1);
		Mat _homo2=Mat::zeros(size2,CV_8UC1);

		Mat _bilateral(size,CV_8UC1);

		Mat _dmqi(size,CV_8UC1);
		Mat _histeq(size,CV_8UC1);
		Mat ccanny(size,CV_8UC1);
		Mat sobelx(size,CV_8UC1);
		Mat sobely(size,CV_8UC1);
		Mat gradx(size,CV_8UC1);
		Mat grady(size,CV_8UC1);
		Mat sobel(size,CV_8UC1);
		nicatio::Grayscale(_image1.data, _gray.data,_image1.cols,_image1.rows);




		cvNica::Denoise(_gray,_deno1);
		cvNica::SelectiveMorphQuotImageParam(_deno1,_dmqi,101,55,0);
		nicatio::HistEqualize(_dmqi.data,_deno2.data,_image1.cols,_image1.rows);
		cvNica::DoG(_gray,_deno1,0.2,1,-2,0,0,0,1000);
		equalizeHist(_deno1,_deno2);
		threshold(_deno2,_deno3,224.0,255.0,THRESH_BINARY);
		threshold(_deno2,_deno2,0.0,30.0,THRESH_BINARY);
		bitwise_or(_deno2,_deno3,_deno2);
		//medianBlur(_histeq,_deno2,3);
		//_deno2=_histeq;
		Canny(_gray,ccanny,70,150);
		Sobel(_gray,sobelx,CV_16S,1,0,3,1, 0, BORDER_DEFAULT );
		convertScaleAbs( sobelx, gradx );
		Sobel(_gray,sobely,CV_16S,0,1,3,1, 0, BORDER_DEFAULT );
		convertScaleAbs( sobely, grady );
		addWeighted( gradx, 0.5, grady, 0.5, 0, sobel );
		int kd=5;

		//cvNica::DifferenceOfVariance(_bilateral,ccanny);
		//cvNica::VarianceFilter(_gray,ccanny,3);
		//ccanny.convertTo(ccanny,CV_8UC1);
		//Canny(_bilateral,ccanny,60,20);
		//Canny(ccanny,ccanny,70,30);
		//cvNica::VarianceFilter(_gray,ccanny,7);
		//namedWindow( "a", CV_WINDOW_AUTOSIZE );
		//bitwise_and(ccanny,_homo,_homo);

//131016
//		Mat _gray2;
//		medianBlur(_gray,_gray,3);
//		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
//		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);
//
//
//		Mat im3(_image1.rows*3, _image1.cols*4, CV_8UC1);
//		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
//		resize(_homo2,_homo,size,0,0,INTER_LINEAR);
//
//		Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
//		_homo.copyTo(right);
//
//		for (int j=1; j<=8; j++) {
//			Mat _k=Mat::zeros(size,CV_8UC1);
//			Mat _h=Mat::zeros(size2,CV_8UC1);
//			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j);
//			resize(_h,_k,size,0,0,INTER_LINEAR);
//			Mat right(im3, Rect(_image1.cols*((j-1)%4), _image1.rows*((int)((j-1)/4)+1), _image1.cols, _image1.rows));
//			_k.copyTo(right);
//		}




		// 131023
		Mat _gray2;
		medianBlur(_gray,_gray,3);
		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
		resize(_bilateral,_gray2,Size(),2,2,INTER_LINEAR);


		Mat im3(_image1.rows*3, _image1.cols*4, CV_8UC1);
		cvNica::HomogeneousOperator(_gray2.data,_homo2.data,_image1.cols*2,_image1.rows*2);
		resize(_homo2,_homo,size,0,0,INTER_LINEAR);

		Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));
		Mat right2(im3, Rect(_image1.cols*2, 0, _image1.cols, _image1.rows));
		Mat right3(im3, Rect(_image1.cols*3, 0, _image1.cols, _image1.rows));



		for (int j=1; j<=8; j++) {
			Mat _k=Mat::zeros(size,CV_8UC1);
			Mat _h=Mat::zeros(size2,CV_8UC1);
			cvNica::HomogeneousOperator(_gray2.data,_h.data,_image1.cols*2,_image1.rows*2,j);
			resize(_h,_k,size,0,0,INTER_LINEAR);
			Mat right(im3, Rect(_image1.cols*((j-1)%4), _image1.rows*((int)((j-1)/4)+1), _image1.cols, _image1.rows));
			_k.copyTo(right);
		}

		_homo.copyTo(right);

		Mat skel( size, CV_8UC1, cv::Scalar(0));
		Mat temp( size, CV_8UC1);
		Mat element = getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));
		bool done;
		do
		{
		  morphologyEx(_homo, temp, cv::MORPH_OPEN, element);
		  bitwise_not(temp, temp);
		  bitwise_and(_homo, temp, temp);
		  bitwise_or(skel, temp, skel);
		  erode(_homo, _homo, element);
		  double max;

		  minMaxLoc(_homo, 0, &max);
		  done = (max == 0);
		} while (!done);


		Mat left(im3, Rect(0, 0, _image1.cols, _image1.rows));
		_gray.copyTo(left);

		//Mat right(im3, Rect(_image1.cols, 0, _image1.cols, _image1.rows));

		skel.copyTo(right2);
		sobel.copyTo(right3);
		//ccanny.copyTo(right3);
		imwrite(dir+"/set002/"+files[i]+".png",im3);
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


#ifdef FA
		//cvNica::FaceAnalysis fhhhah();

		Mat dsf = Mat::zeros(3,3,CV_32FC1);
		dsf.at<float>(2,2) = 255;

		Mat dsf2; dsf.convertTo(dsf2,CV_8UC1);
		imwrite("dfdf.bmp",dsf2);

		cvNica::FaceAnalysis fa(dir,"pgm");
		fa.setGroup("faceindex.bmp");
		//fa.draw(64,2);
		fa.mse(64);
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

