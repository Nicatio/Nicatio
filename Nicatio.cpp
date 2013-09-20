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

#define BMP
//#define PCAP
//#define TXT
//#define GF
//#define ENHANCE
//#define FEATHERING
//#define FLASH
//#define SMOOTHING
//#define FA

//#define FR
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



//#define illuminationNormalization
#define textDetection

#ifdef textDetection
int main(int argc, char* argv[] ){

#ifdef BMP
	string dir = string(argv[1]);
	//string refLocation = string(argv[2]);

	vector<string> files = vector<string>();

	if (nicatio::getdirType(dir,"bmp",files,0)) {
		cout<< "Error: Invalid file location \n" <<endl;
		return -1;
	}
#endif

	for (unsigned int i = 0;i < files.size();i++) {
		Mat _image1;
		_image1 = imread( dir+"/"+files[i], -1 );
		Size size = _image1.size();

		Mat _deno1(size,CV_8UC1);
		Mat _deno2(size,CV_8UC1);
		Mat _deno3(size,CV_8UC1);

		Mat _gray(size,CV_8UC1);
		Mat _homo(size,CV_8UC1);
		Mat _bilateral(size,CV_8UC1);

		Mat _dmqi(size,CV_8UC1);
		Mat _histeq(size,CV_8UC1);
		Mat ccanny(size,CV_8UC1);
		nicatio::Grayscale(_image1.data, _gray.data,_image1.cols,_image1.rows);
		cvNica::HomogeneousOperator(_gray.data,_homo.data,_image1.cols,_image1.rows);



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
		//Canny(_gray,ccanny,70,150);
		int kd=7;
		bilateralFilter (_gray, _bilateral, kd, kd*2, kd/2 );
		//cvNica::DifferenceOfVariance(_bilateral,ccanny);
		//cvNica::VarianceFilter(_gray,ccanny,3);
		//ccanny.convertTo(ccanny,CV_8UC1);
		Canny(_bilateral,ccanny,60,20);
		//Canny(ccanny,ccanny,70,30);
		//cvNica::VarianceFilter(_gray,ccanny,7);
		//namedWindow( "a", CV_WINDOW_AUTOSIZE );

		imwrite(dir+"/rdmqi/"+files[i],_homo);
	}
}

#endif

#ifdef illuminationNormalization

// Run configurations
// /cygdrive/e/Documents/Nicatio/Research/DB/Face/yalebDB/smqi/
// /cygdrive/e/Documents/Nicatio/Research/DB/Face/yalebDB/smqi/ref_list2.txt

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


#ifdef FR
		cvNica::FaceRecognition fr(dir,refLocation);
		//fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR,-45,0);
		fr.Recognition(dir,"pgm",DB_YALEB,METHOD_CORR);
		cout<<"1 "<<fr.getAccuracy(files)<<" "<<endl;
		cout<<"2 "<<fr.getAccuracyIncludingBadImages()<<" "<<endl;
		fr.getAccuracyIncludingBadImagesSubset();

		FileStorage abcd("dix.xml",FileStorage::WRITE);
		abcd << "frRecognitionResult" << fr.RecognitionResult;
		abcd.release();
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

#ifdef DMQI
			//cout << files[i] <<"\r"<< endl;
			Mat _image1;
			_image1 = imread( dir+"\\"+files[i], -1 );
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




			unsigned found = files[i].rfind("bad");
			if (found!=std::string::npos) {
				vector<string> tokens = nicatio::StringTokenizer::getTokens(files[i],".");
				imwrite(dir+"\\smqi\\"+tokens[0]+".pgm",_deno2);
				rename( string(dir+"\\smqi\\"+tokens[0]+".pgm").c_str() , string(dir+"\\smqi\\"+tokens[0]+".pgm.bad").c_str() );

			} else {

				imwrite(dir+"\\smqi\\"+files[i],_deno2);

			}
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


