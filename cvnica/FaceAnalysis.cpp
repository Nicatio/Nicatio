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

};



