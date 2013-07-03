/*
 * FaceAnalysis.cpp
 *
 *  Created on: 2013. 4. 6.
 *      Author: Nicatio
 */

#include "FaceAnalysis.h"

using namespace cv;

namespace cvNica {

FaceAnalysis::FaceAnalysis (void){}
FaceAnalysis::FaceAnalysis (
		string							dir,
		string							type)
{
	DirectoryLocation = dir;
	files = vector<string>();
	if(nicatio::getdirType(dir,type,files,0)){
		cout<< "Error: Invalid file location \n" <<endl;
	}
	getBadImageInfo (files,0);
}
void FaceAnalysis::setGroup(
		string							location)
{
	groupMap = imread(location, -1);
	int cols = groupMap.cols;
	int rows = groupMap.rows;
	int sz = cols*rows;
	int max = groupMap.data[sz-1];
	groupCount.resize(max+1,0);
	uchar* ptr = groupMap.data;
	for(int i=0; i<sz; i++)	groupCount[*(ptr++)]++;
}
void FaceAnalysis::draw(
		const int						nPicsPerSubject,
		const int						type)
{
	int nImages = files.size();
	int nSubject = nImages / nPicsPerSubject;
	int nAnalysisImage = groupCount.size();
	vector<Mat> analysisImageIntra (nAnalysisImage);
	vector<Mat> analysisImageInter (nAnalysisImage);
	vector<Mat> analysisImageN (nAnalysisImage);
	vector<Mat> ambienceImage (nSubject);
	int cols,rows;
	for (int i=0;i<nAnalysisImage;i++) {
		analysisImageIntra[i] = Mat::zeros(511,groupCount[i],CV_32FC1);
		analysisImageInter[i] = Mat::zeros(511,groupCount[i],CV_32FC1);
		analysisImageN[i] = Mat::zeros(511,groupCount[i],CV_8UC1);
	}
	for (int i=0;i<nSubject;i++) {
		Mat temp = imread( DirectoryLocation+"/"+files[i*nPicsPerSubject],CV_8UC1);
		temp.convertTo(ambienceImage[i],CV_16SC1);

	}
	cols = ambienceImage[0].cols;
	rows = ambienceImage[0].rows;
	for (int i=0;i<nImages;i++) {
		Mat _testImage = imread( DirectoryLocation+"/"+files[i],CV_8UC1);
		Mat testImage; _testImage.convertTo(testImage,CV_16SC1);
		for (int j=0;j<nSubject;j++) {
			if(i/nPicsPerSubject == j && i%nPicsPerSubject==0) continue;
			Mat diff = testImage-ambienceImage[j];
			vector<int> tempCounter (nAnalysisImage,0);
			if(i/nPicsPerSubject == j) {
				for (int k=0;k<rows;k++) {
					for (int l=0;l<cols;l++) {
						int type = (int)groupMap.at<char>(k,l);
						int y =diff.at<short>(k,l)+255;
						//if (y!=255) {
						analysisImageIntra[type].at<float>(y,tempCounter[type]) = analysisImageIntra[type].at<float>(y,tempCounter[type])+1;
						//}
						tempCounter[type]++;
					}
				}

			} else {
				for (int k=0;k<rows;k++) {
					for (int l=0;l<cols;l++) {
						int type = (int)groupMap.at<char>(k,l);
						int y =diff.at<short>(k,l)+255;
						//if (y!=255) {
						analysisImageInter[type].at<float>(y,tempCounter[type]) = analysisImageInter[type].at<float>(y,tempCounter[type])+1;
						//}
						tempCounter[type]++;
					}
				}
			}

		}
		cout<<files[i]<<" - done"<<endl;

	}
	if (!type) {
		vector<float> maxInter(nAnalysisImage,0);
		vector<float> maxIntra(nAnalysisImage,0);
		for (int j=0;j<nAnalysisImage;j++) {
			for (int k=0;k<511;k++) {
				for (int l=0;l<groupCount[j];l++) {
					float aa = analysisImageInter[j].at<float>(k,l);
					if(aa>maxInter[j])maxInter[j]=aa;
					float bb = analysisImageIntra[j].at<float>(k,l);
					if(bb>maxIntra[j])maxIntra[j]=bb;
				}
			}
			analysisImageInter[j] /= maxInter[j]/255;
			analysisImageIntra[j] /= maxIntra[j]/255;
			vector<Mat> temp (3);
			analysisImageInter[j].convertTo(temp[0],CV_8UC1);
			analysisImageInter[j].convertTo(temp[2],CV_8UC1);
			temp[1] = analysisImageN[j];
			Mat temp2;
			merge(temp,temp2);
			stringstream a;
			a<<"inter"<<j<<".bmp";
			stringstream b;
			b<<"intra"<<j<<".bmp";
			stringstream c;
			c<<"merge"<<j<<".bmp";
			imwrite(a.str(),temp[0]);
			imwrite(b.str(),temp[2]);
			imwrite(c.str(),temp2);
		}
	} else if (type==1) {
		vector<float> maxInter(nAnalysisImage,0);
		vector<float> maxIntra(nAnalysisImage,0);
		for (int j=0;j<nAnalysisImage;j++) {
			for (int k=0;k<511;k++) {
				for (int l=0;l<groupCount[j];l++) {
					float aa = analysisImageInter[j].at<float>(k,l);
					if(aa>maxInter[j])maxInter[j]=aa;
					float bb = analysisImageIntra[j].at<float>(k,l);
					if(bb>maxIntra[j])maxIntra[j]=bb;
				}
			}
			Mat _temp1,_temp2;
			log(analysisImageInter[j], _temp1);
			log(analysisImageIntra[j], _temp2);
			_temp1 /= log(maxInter[j])/255;
			_temp2 /= log(maxIntra[j])/255;
			vector<Mat> temp (3);
			_temp1.convertTo(temp[0],CV_8UC1);
			_temp2.convertTo(temp[2],CV_8UC1);
			temp[1] = analysisImageN[j];
			Mat temp2;
			merge(temp,temp2);
			stringstream a;
			a<<"inter"<<j<<".bmp";
			stringstream b;
			b<<"intra"<<j<<".bmp";
			stringstream c;
			c<<"merge"<<j<<".bmp";
			imwrite(a.str(),temp[0]);
			imwrite(b.str(),temp[2]);
			imwrite(c.str(),temp2);
		}
	} else if (type==2) {
		for (int j=0;j<nAnalysisImage;j++) {
			for (int l=0;l<groupCount[j];l++) {
				int minintra;
				int maxintra;
				int mininter;
				int maxinter;
				for (int k=0;k<511;k++) {
					float aa = analysisImageInter[j].at<float>(k,l);
					if(aa!=0.0){maxinter = k; break;}
				}
				for (int k=0;k<511;k++) {
					float aa = analysisImageIntra[j].at<float>(k,l);
					if(aa!=0.0){maxintra = k; break;}
				}
				for (int k=510;k>=0;k--) {
					float aa = analysisImageInter[j].at<float>(k,l);
					if(aa!=0.0){mininter = k; break;}
				}
				for (int k=510;k>=0;k--) {
					float aa = analysisImageIntra[j].at<float>(k,l);
					if(aa!=0.0){minintra = k; break;}
				}
				for (int k=0;k<511;k++) {
					analysisImageInter[j].at<float>(k,l)=0.0;
					analysisImageIntra[j].at<float>(k,l)=0.0;
				}
				for (int k=maxinter;k<maxintra;k++) {
					analysisImageInter[j].at<float>(k,l)=255.0;
				}
				for (int k=mininter;k>minintra;k--) {
					analysisImageInter[j].at<float>(k,l)=255.0;
				}
				analysisImageIntra[j].at<float>(minintra,l)=255.0;
				analysisImageIntra[j].at<float>(maxintra,l)=255.0;
			}
			vector<Mat> temp (3);
			analysisImageInter[j].convertTo(temp[0],CV_8UC1);
			analysisImageIntra[j].convertTo(temp[2],CV_8UC1);
			temp[1] = analysisImageN[j];
			Mat temp2;
			merge(temp,temp2);
			stringstream a;
			a<<"inter"<<j<<".bmp";
			stringstream b;
			b<<"intra"<<j<<".bmp";
			stringstream c;
			c<<"merge"<<j<<".bmp";
			imwrite(a.str(),temp[0]);
			imwrite(b.str(),temp[2]);
			imwrite(c.str(),temp2);
		}
	}

}

void FaceAnalysis::mse(
		const int						nPicsPerSubject)
{
	int nImages = files.size();
	int nSubject = nImages / nPicsPerSubject;
	int nAnalysisImage = groupCount.size();
	vector<Mat> analysisImageIntra (nAnalysisImage);
	vector<Mat> analysisImageInter (nAnalysisImage);
	vector<Mat> analysisImageN (nAnalysisImage);
	vector<Mat> ambienceImage (nSubject);
	int cols,rows;
	for (int i=0;i<nAnalysisImage;i++) {
		analysisImageIntra[i] = Mat::zeros(1,groupCount[i],CV_32FC1);
		analysisImageInter[i] = Mat::zeros(1,groupCount[i],CV_32FC1);
		analysisImageN[i] = Mat::zeros(1,groupCount[i],CV_8UC1);
	}
	for (int i=0;i<nSubject;i++) {
		Mat temp = imread( DirectoryLocation+"/"+files[i*nPicsPerSubject],CV_8UC1);
		temp.convertTo(ambienceImage[i],CV_16SC1);
	}
	cols = ambienceImage[0].cols;
	rows = ambienceImage[0].rows;
	int x=0,y=0;
	for (int i=0;i<nImages;i++) {
		Mat _testImage = imread( DirectoryLocation+"/"+files[i],CV_8UC1);
		Mat testImage; _testImage.convertTo(testImage,CV_16SC1);
		for (int j=0;j<nSubject;j++) {
			if(i/nPicsPerSubject == j && i%nPicsPerSubject==0) continue;
			Mat diff = testImage-ambienceImage[j];
			vector<int> tempCounter (nAnalysisImage,0);
			if(i/nPicsPerSubject == j) {
				for (int k=0;k<rows;k++) {
					for (int l=0;l<cols;l++) {
						int type = (int)groupMap.at<char>(k,l);
						int y =diff.at<short>(k,l);
						analysisImageIntra[type].at<float>(0,tempCounter[type]) = analysisImageIntra[type].at<float>(0,tempCounter[type])+y*y;
						tempCounter[type]++;
					}
				}
				x++;
			} else {
				for (int k=0;k<rows;k++) {
					for (int l=0;l<cols;l++) {
						int type = (int)groupMap.at<char>(k,l);
						int y =diff.at<short>(k,l);
						analysisImageInter[type].at<float>(0,tempCounter[type]) = analysisImageInter[type].at<float>(0,tempCounter[type])+y*y;
						tempCounter[type]++;
					}
				}
				y++;
			}
		}
		cout<<files[i]<<" - done"<<endl;
	}

	ofstream FileO;
	FileO.open("i.txt",ios::out);
	for (int j=0;j<nAnalysisImage;j++) {
		analysisImageIntra[j] /= x;
		analysisImageInter[j] /= y;
	}

	double mingroupCount,maxgroupCount;
	minMaxIdx(groupCount,&mingroupCount,&maxgroupCount);
	for (int i=0;i<maxgroupCount;i++) {
		for (int j=0;j<nAnalysisImage;j++) {
			if (i<groupCount[j]) FileO<<analysisImageIntra[j].at<float>(0,i)<<"\t"<<analysisImageInter[j].at<float>(0,i)<<"\t";
			else FileO<<"\t"<<"\t";
		}
		FileO<<endl;
	}
	FileO.close();

}

void FaceAnalysis::Normalize(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Mat fsrc; src.convertTo(fsrc,CV_32FC1);
	Mat m,s;
	meanStdDev(fsrc,m,s);

	double _m=sum(m)[0];
	double _s=sum(s)[0];
	Mat dst;

	if(_s==0) {_s = 1;}
	else _s = 1.0/_s;
	fsrc.copyTo(dst);
	dst -= _m;
	dst = dst.mul(_s);

	dst.convertTo(_dst,CV_32FC1);
}

void FaceAnalysis::gray2RGB(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Size sz = Size(src.cols,src.rows);
	Mat one_ = Mat::ones(sz,CV_32FC1);

	double min,max,diff,diff2;
	minMaxIdx(src,&min,&max);
	diff2 = (abs(max)>abs(min))? abs(max):abs(min);
	diff = diff2*2;
	src+=diff2;
	src = src.mul(300.0/diff);
	Mat mix[3] = {src,one_,one_};
	Mat mix_;
	merge(mix,3,mix_);
	cvtColor(mix_, mix_, CV_HSV2RGB);
	mix_*=255;
	Mat mix__;
	mix_.convertTo(_dst,CV_8UC3);
}

void FaceAnalysis::gray2RGBminmax(
		InputArray 						_src,
		OutputArray						_dst,
		const double					min,
		const double					max)
{
	Mat __src = _src.getMat();
	Mat src; __src.copyTo(src);
	Size sz = Size(src.cols,src.rows);
	Mat one_ = Mat::ones(sz,CV_32FC1);

	Mat src1 = (src>=0)/255;
	Mat src2; src1.convertTo(src2,CV_32FC1);
	Mat src3 = (src<0)/255;
	Mat src4; src3.convertTo(src4,CV_32FC1);

	double diff,diff2;
	diff2 = (abs(max)>abs(min))? abs(max):abs(min);
	diff = diff2*2;
	src+=diff2;
	src = src.mul(240.0/diff);

	src = (src+60).mul(src2)+src.mul(src4);
	Mat mix[3] = {src,one_,one_};
	Mat mix_;
	merge(mix,3,mix_);
	cvtColor(mix_, mix_, CV_HSV2RGB);
	mix_*=255;
	Mat mix__;
	mix_.convertTo(_dst,CV_8UC3);
}

void FaceAnalysis::grayminmax(
		InputArray 						_src,
		OutputArray						_dst,
		const double					min,
		const double					max)
{
	Mat __src = _src.getMat();
	Mat src; __src.copyTo(src);
	Size sz = Size(src.cols,src.rows);

	Mat src1 = (src>=0);///255;
	Mat src2; src1.convertTo(src2,CV_8UC1);
	Mat src3 = (src<0);//255;
	Mat src4; src3.convertTo(src4,CV_8UC1);

	src = src2/255;
	src.convertTo(_dst,CV_8UC1);
}

void FaceAnalysis::getBadImageInfo (
		vector<string>					files,
		const int						subsetCount)
{
	int nFiles = files.size();
	BadImage = Mat::zeros(nFiles,1,CV_8SC1);
	uchar *ptr_bb = BadImage.data;

	for (int i = 0; i < nFiles; i++,ptr_bb++) {
		unsigned found = files[i].rfind("bad");
		if (found!=std::string::npos) {
			*(ptr_bb) = 1;
		}
	}
}

void FaceAnalysis::correlationPic(
		const int						nPicsPerSubject,
		const int						type,
		const int						bin)
{
	string kk = "smqi";
	string kk2 = "ResultBinary";
	int nImages = files.size();
	int nSubject = nImages / nPicsPerSubject;
	vector<Mat> analysisImageIntra (nSubject);
	vector<Mat> analysisImageInter (nSubject);
	vector<Mat> ambienceImage (nSubject);
	for (int i=0;i<nSubject;i++) {
		Mat temp = imread( DirectoryLocation+"/"+files[i*nPicsPerSubject],CV_8UC1);
		Normalize(temp,ambienceImage[i]);
	}

	Size sz = Size(ambienceImage[0].cols,ambienceImage[0].rows);
	for (int i=0;i<nSubject;i++) {
		analysisImageIntra[i] = Mat::zeros(sz,CV_32FC1);
		analysisImageInter[i] = Mat::zeros(sz,CV_32FC1);
	}
	for (int i=0;i<nSubject;i++) {
		Mat temp = imread( DirectoryLocation+"/"+files[i*nPicsPerSubject],CV_8UC1);
		Normalize(temp,ambienceImage[i]);
	}
	int counter=0;
	int counter2=0;
	for (int i=0;i<nImages;i++) {
		Mat _testImage = imread( DirectoryLocation+"/"+files[i],CV_8UC1);
		Mat testImage;
		Normalize(_testImage,testImage);
		for (int j=0;j<nSubject;j++) {
			if (!BadImage.at<char>(i)) {
				if(i/nPicsPerSubject == j && i%nPicsPerSubject==0) continue;
				Mat multResult; multiply(testImage,ambienceImage[j],multResult);
				if(i/nPicsPerSubject == j) {analysisImageIntra[j] += multResult;counter++;}
									  else {analysisImageInter[j] += multResult;counter2++;}
			}
		}
	}
	counter/=nSubject;
	counter2/=nSubject;

	double Tmin=1e100,Tmax=-1e100;
	double Dmin=1e100,Dmax=-1e100;
	for (int i=0;i<nSubject;i++) {
		analysisImageIntra[i]=analysisImageIntra[i].mul(1./(double)counter);
		analysisImageInter[i]=analysisImageInter[i].mul(1./(double)counter2);
		double min,max;
		minMaxIdx(analysisImageIntra[i],&min,&max);
		if (Tmin>min) Tmin = min;
		if (Tmax<max) Tmax = max;
		minMaxIdx(analysisImageInter[i],&min,&max);
		if (Tmin>min) Tmin = min;
		if (Tmax<max) Tmax = max;
		Mat diff__ = analysisImageIntra[i]-analysisImageInter[i];
		minMaxIdx(diff__,&min,&max);
		if (Dmin>min) Dmin = min;
		if (Dmax<max) Dmax = max;

	}
	Mat INTRA= Mat::zeros(sz,CV_32FC1);
	Mat INTER= Mat::zeros(sz,CV_32FC1);
	cout<<"Tmin: "<<Tmin<<endl;
	cout<<"Tmax: "<<Tmax<<endl;
	cout<<"Dmin: "<<Dmin<<endl;
	cout<<"Dmax: "<<Dmax<<endl;
	//Tmin=-13.5594,Tmax=58.8796;
	for (int i=0;i<nSubject;i++) {



		INTRA += analysisImageIntra[i];
		INTER += analysisImageInter[i];

		stringstream a;
		a<<kk2<<"/"<<kk<<"/intra/intra"<<i<<".bmp";
		stringstream b;
		b<<kk2<<"/"<<kk<<"/inter/inter"<<i<<".bmp";
		stringstream c;
		c<<kk2<<"/"<<kk<<"/diff/diff"<<i<<".bmp";
		if (!bin) {
			Mat mix__;
			gray2RGBminmax(analysisImageIntra[i],mix__,Tmin,Tmax);
			imwrite(a.str(),mix__);
			gray2RGBminmax(analysisImageInter[i],mix__,Tmin,Tmax);
			imwrite(b.str(),mix__);
			Mat diff__ = analysisImageIntra[i]-analysisImageInter[i];
			gray2RGBminmax(diff__,mix__,Dmin,Dmax);
			imwrite(c.str(),mix__);
		} else {
			Mat mix__;
			grayminmax(analysisImageIntra[i],mix__,Tmin,Tmax);
			imwrite(a.str(),mix__);
			grayminmax(analysisImageInter[i],mix__,Tmin,Tmax);
			imwrite(b.str(),mix__);
			Mat diff__ = analysisImageIntra[i]-analysisImageInter[i];
			grayminmax(diff__,mix__,Dmin,Dmax);
			imwrite(c.str(),mix__);
		}
	}
	if (!bin) {
		Mat mix__;
		gray2RGBminmax(INTRA/38,mix__,Tmin,Tmax);
		imwrite(kk2+"/"+kk+"/intra/intra.bmp",mix__);
		gray2RGBminmax(INTER/38,mix__,Tmin,Tmax);
		imwrite(kk2+"/"+kk+"/inter/inter.bmp",mix__);
		gray2RGBminmax(INTRA/38-INTER/38,mix__,Dmin,Dmax);
		imwrite(kk2+"/"+kk+"/diff/diff.bmp",mix__);
	} else {
		Mat mix__;
		grayminmax(INTRA/38,mix__,Tmin,Tmax);
		imwrite(kk2+"/"+kk+"/intra/intra.bmp",mix__);
		grayminmax(INTER/38,mix__,Tmin,Tmax);
		imwrite(kk2+"/"+kk+"/inter/inter.bmp",mix__);
		grayminmax(INTRA/38-INTER/38,mix__,Dmin,Dmax);
		imwrite(kk2+"/"+kk+"/diff/diff.bmp",mix__);
	}
}


void FaceAnalysis::maskPic(
		const int						nPicsPerSubject,
		const int						type,
		const int						bin)
{
	string kk = "smqi";
	string kk2 = "ResultBinary";
	int nOther = 38;
	int nImages = files.size();
	int nSubject = nImages / nPicsPerSubject;
	vector<Mat> analysisImageIntra (nSubject);
	vector<Mat> analysisImageInter (nSubject);
	vector<Mat> ambienceImage (nSubject);

	vector<vector<unsigned char> > randomScatter(nSubject);

	for (int i=0;i<nSubject;i++) {
		Mat temp = imread( DirectoryLocation+"/"+files[i*nPicsPerSubject],CV_8UC1);
		Normalize(temp,ambienceImage[i]);
		randomScatter[i].resize(nSubject,0);
		for (int j=0;j<nOther;j++)
			randomScatter[i][j] = 1;
		randomScatter[i][i] = 0;
//		for (int j=0;j<nSubject;j++){
//			unsigned char temp = rand()%nSubject;
//			unsigned char t = randomScatter[i][temp];
//			randomScatter[i][temp] = randomScatter[i][j];
//			randomScatter[i][j] = t;
//		}
	}

	Size sz = Size(ambienceImage[0].cols,ambienceImage[0].rows);
	for (int i=0;i<nSubject;i++) {
		analysisImageIntra[i] = Mat::zeros(sz,CV_32FC1);
		analysisImageInter[i] = Mat::zeros(sz,CV_32FC1);

	}
	for (int i=0;i<nSubject;i++) {
		Mat temp = imread( DirectoryLocation+"/"+files[i*nPicsPerSubject],CV_8UC1);
		Normalize(temp,ambienceImage[i]);
	}

	int counter=1;
	for (int j=0;j<nSubject;j++) {
		for (int i=0;i<nSubject-1;i++) {
//			if (randomScatter[j][i]) {
//				Mat multResult; multiply(ambienceImage[j],ambienceImage[i],multResult);
//				analysisImageIntra[j] += multResult;counter++;
//				cout<<i<<endl;
//			}
			if (randomScatter[j][i]&&randomScatter[j][i+1]) {

						Mat multResult; multiply(ambienceImage[i],ambienceImage[i+1],multResult);
						analysisImageIntra[j] += multResult;counter++;
						cout<<i<<endl;

			}
		}
		//bitwise_and(ambienceImage[j],  analysisImageIntra[j],analysisImageIntra[j]);
	}

	counter/=nSubject;

	cout<<counter<<endl;

	double Tmin=1e100,Tmax=-1e100;
	double Dmin=1e100,Dmax=-1e100;
	for (int i=0;i<nSubject;i++) {
		//analysisImageIntra[i]=analysisImageIntra[i].mul(1./(double)counter);
		double min,max;
		minMaxIdx(analysisImageIntra[i],&min,&max);
		if (Tmin>min) Tmin = min;
		if (Tmax<max) Tmax = max;
	}
	Mat INTRA= Mat::zeros(sz,CV_32FC1);

	for (int i=0;i<nSubject;i++) {



		INTRA += analysisImageIntra[i];

		stringstream a;
		a<<kk2<<"/"<<kk<<"/intra/intra"<<i<<".bmp";

		if (!bin) {
			Mat mix__;
			gray2RGBminmax(analysisImageIntra[i],mix__,Tmin,Tmax);
			imwrite(a.str(),mix__);
		} else {
			Mat mix__;
			grayminmax(analysisImageIntra[i],mix__,Tmin,Tmax);
			imwrite(a.str(),mix__);
		}
	}
	if (!bin) {
		Mat mix__;
		gray2RGBminmax(INTRA/nSubject,mix__,Tmin,Tmax);
		imwrite(kk2+"/"+kk+"/intra/intra.bmp",mix__);
	} else {
		Mat mix__;
		grayminmax(INTRA/nSubject,mix__,Tmin,Tmax);
		imwrite(kk2+"/"+kk+"/intra/intra.bmp",mix__);
	}
}


};




