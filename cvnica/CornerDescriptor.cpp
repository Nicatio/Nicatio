/*
 * CornerDescriptor.cpp
 *
 *  Created on: 2013. 9. 16.
 *      Author: Nicatio
 */

#include "CornerDescriptor.h"

namespace cvNica {

//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=300;
//	int meanth=2;
//	//int sz = width*height;
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var1, var2, var3, var4;
//			double mean1=0, mean2=0, mean3=0, mean4=0;
//			int sum1=0, sum2=0, sum3=0, sum4=0;
//			int sqsum1=0, sqsum2=0, sqsum3=0, sqsum4=0;
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum1 += a;
//						sqsum1 += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum2 += a;
//						sqsum2 += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum3 += a;
//						sqsum3 += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum4 += a;
//						sqsum4 += a*a;
//					}
//				}
//			}
//			mean1 = sum1/10;
//			mean2 = sum2/10;
//			mean3 = sum3/10;
//			mean4 = sum4/10;
//
//			var1 = sqsum1/10-mean1*mean1;
//			var2 = sqsum2/10-mean2*mean2;
//			var3 = sqsum3/10-mean3*mean3;
//			var4 = sqsum4/10-mean4*mean4;
//			//std::cout<<"d"<<var1<<"d"<<var2<<"d"<<(mean1-mean2)<<std::endl;
//			if (var1 < varth && var2 < varth && ((mean1-mean2)< meanth  || (mean2-mean1)< meanth)) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				outputImg[p]=255;
//			} else if (var3 < varth && var4 < varth && ((mean3-mean4)< meanth  || (mean4-mean3)<meanth)) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				outputImg[p]=127;
//			} else {
//				outputImg[p]=0;
//			}
//		}
//	}
//}

//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=8000;
//	int meanth=15;
//	//int sz = width*height;
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var1, var2, var3, var4;
//			int mean1=0, mean2=0, mean3=0, mean4=0;
//			int sum1=0, sum2=0, sum3=0, sum4=0;
//			int sqsum1=0, sqsum2=0, sqsum3=0, sqsum4=0;
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum1 += a;
//						sqsum1 += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum2 += a;
//						sqsum2 += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum3 += a;
//						sqsum3 += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum4 += a;
//						sqsum4 += a*a;
//					}
//				}
//			}
//			mean1 = sum1/10;
//			mean2 = sum2/10;
//			mean3 = sum3/10;
//			mean4 = sum4/10;
//
//			var1 = sqsum1;//-mean1*mean1;
//			var2 = sqsum2;//-mean2*mean2;
//			var3 = sqsum3;//-mean3*mean3;
//			var4 = sqsum4;//-mean4*mean4;
//
//			if (var1 > varth && var2 > varth) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//				if ((mean1-mean2)> meanth ) {outputImg[p]=240;}
//				else if ((mean2-mean1)> meanth ) {outputImg[p]=180;}
//			}
//			if (var3 > varth && var4 > varth ) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				if ((mean3-mean4)> meanth ) {outputImg[p]=120;}
//				else if ((mean4-mean3)> meanth ) {outputImg[p]=60;}
//			}
//		}
//	}
//}

//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=30;
//	int meanth=10;
//
//	//int sz = width*height;
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if (v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(-v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if (-v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<8; i++) {
//				mean[i] = sum[i]/10;
//				var[i] = sqrt(sqsum[i]/10-mean[i]*mean[i]);
//			}
//
//			if (var[0] < varth && var[1] < varth) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//				if ((mean[0]-mean[1])> meanth ) {outputImg[p]=240;}
//				else if ((mean[1]-mean[0])> meanth ) {outputImg[p]=180;}
//			}
//			if (var[2] < varth && var[3] < varth ) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				if ((mean[2]-mean[3])> meanth ) {outputImg[p]=120;}
//				else if ((mean[3]-mean[2])> meanth ) {outputImg[p]=60;}
//			}
//
//			if (var[4] < varth && var[5] < varth ) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				if ((mean[4]-mean[5])> meanth ) {outputImg[p]=120;}
//				else if ((mean[5]-mean[4])> meanth ) {outputImg[p]=60;}
//			}
//
//			if (var[6] < varth && var[7] < varth) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//				if ((mean[6]-mean[7])> meanth ) {outputImg[p]=240;}
//				else if ((mean[7]-mean[6])> meanth ) {outputImg[p]=180;}
//			}
//		}
//	}
//}


//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=20000;
//	int meanth=10;
//
//	//int sz = width*height;
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if (v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(-v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if (-v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<8; i++) {
//				mean[i] = sum[i]/10;
//				var[i] = sqsum[i];
//			}
//
//			if (var[0] > varth && var[1] > varth) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//				if ((mean[0]-mean[1])> meanth ) {outputImg[p]=240;}
//				else if ((mean[1]-mean[0])> meanth ) {outputImg[p]=180;}
//			}
//			if (var[2] > varth && var[3] > varth ) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				if ((mean[2]-mean[3])> meanth ) {outputImg[p]=120;}
//				else if ((mean[3]-mean[2])> meanth ) {outputImg[p]=60;}
//			}
//
//			if (var[4] > varth && var[5] > varth ) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//				if ((mean[4]-mean[5])> meanth ) {outputImg[p]=120;}
//				else if ((mean[5]-mean[4])> meanth ) {outputImg[p]=60;}
//			}
//
//			if (var[6] > varth && var[7] > varth) {
//				//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//				if ((mean[6]-mean[7])> meanth ) {outputImg[p]=240;}
//				else if ((mean[7]-mean[6])> meanth ) {outputImg[p]=180;}
//			}
//		}
//	}
//}

//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=100.0;
//	int meanth=20;
//
//	//int sz = width*height;
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [16];
//			double mean [16] = {0};
//			int sum [16] = {0};
//			int sqsum [16] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if (v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(-v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if (-v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//					if(v>0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[8] += a;
//						sqsum[8] += a*a;
//					} else if (v<0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[9] += a;
//						sqsum[9] += a*a;
//					}
//					if(v>0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[10] += a;
//						sqsum[10] += a*a;
//					} else if (v<0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[11] += a;
//						sqsum[11] += a*a;
//					}
//					if(v<0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[12] += a;
//						sqsum[12] += a*a;
//					} else if (v>0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[13] += a;
//						sqsum[13] += a*a;
//					}
//					if(v<0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[14] += a;
//						sqsum[14] += a*a;
//					} else if (v>0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[15] += a;
//						sqsum[15] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<8; i++) {
//				mean[i] = sum[i]/10;
//				var[i] = (sqsum[i]/10-mean[i]*mean[i]);///sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=8; i<16; i+=2) {
//				mean[i] = sum[i]/4;
//				mean[i+1] = sum[i+1]/16;
//				var[i] = (sqsum[i]/4-mean[i]*mean[i]);///sqrt(mean[i]);
//				var[i+1] = (sqsum[i+1]/16-mean[i+1]*mean[i+1])/sqrt(mean[i+1]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//				if ((var[i] > varth && var[i+1] > varth)){//||(var[i] < varth && var[i+1] < varth)) {
//					//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//					if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//					else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//				}
//			}
//			for (int i=0; i<8; i+=2) {
//				if ((var[i] > varth && var[i+1] > varth)){//||(var[i] < varth && var[i+1] < varth)) {
//					//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//
//					if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//					else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//
//				}
//			}
//
//		}
//	}
//}

//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=100.0;
//	int meanth=7;
//
//	//int sz = width*height;
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [17];
//			double mean [17] = {0};
//			int sum [17] = {0};
//			int sqsum [17] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if (v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(-v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if (-v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//					if(v>0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[8] += a;
//						sqsum[8] += a*a;
//					} else if (v<0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[9] += a;
//						sqsum[9] += a*a;
//					}
//					if(v>0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[10] += a;
//						sqsum[10] += a*a;
//					} else if (v<0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[11] += a;
//						sqsum[11] += a*a;
//					}
//					if(v<0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[12] += a;
//						sqsum[12] += a*a;
//					} else if (v>0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[13] += a;
//						sqsum[13] += a*a;
//					}
//					if(v<0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[14] += a;
//						sqsum[14] += a*a;
//					} else if (v>0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[15] += a;
//						sqsum[15] += a*a;
//					}
//					int a = inputImg[p+u+v*width];
//					sum[16] += a;
//					sqsum[16] += a*a;
//				}
//			}
//			//mean[16] = sum[16]/25;
//			//var[16] = (sqsum[16]/25-mean[16]*mean[16])/mean[16];
//			//if (var[16] < 2) outputImg[p]=255;
//			for (int i=0; i<8; i++) {
//				mean[i] = sum[i]/10;
//				var[i] = (sqsum[i]/10-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=8; i<16; i+=2) {
//				mean[i] = sum[i]/4;
//				mean[i+1] = sum[i+1]/16;
//				var[i] = (sqsum[i]/4-mean[i]*mean[i]);////sqrt(mean[i]);
//				var[i+1] = (sqsum[i+1]/16-mean[i+1]*mean[i+1]);////sqrt(mean[i+1]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//				if ((var[i] > varth && var[i+1] > varth)){// ||(var[i] > varth && var[i+1] < varth)) {
//					//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//					//outputImg[p]=255;
//					if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//					else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//				}
//			}
//			for (int i=0; i<8; i+=2) {
//				if ((var[i] > varth && var[i+1] > varth)){// ||(var[i] > varth && var[i+1] < varth)) {
//					//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//					//outputImg[p]=255;
//					if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//					else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//
//				}
//			}
//
//		}
//	}
//}

//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height)
//{
//	int p;
//	int varth=100.0;
//	int meanth=7;
//
//	//int sz = width*height;
//	for(int y = 1; y < height-1; y++ ) {
//		for(int x = 1; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [17];
//			double mean [17] = {0};
//			int sum [17] = {0};
//			int sqsum [17] = {0};
//			for(int v = -1; v <= 1; v++ ) {
//				for(int u = -1; u <= 1; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if (v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(-v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if (-v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//					if(v>0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[8] += a;
//						sqsum[8] += a*a;
//					} else if (v<0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[9] += a;
//						sqsum[9] += a*a;
//					}
//					if(v>0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[10] += a;
//						sqsum[10] += a*a;
//					} else if (v<0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[11] += a;
//						sqsum[11] += a*a;
//					}
//					if(v<0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[12] += a;
//						sqsum[12] += a*a;
//					} else if (v>0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[13] += a;
//						sqsum[13] += a*a;
//					}
//					if(v<0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[14] += a;
//						sqsum[14] += a*a;
//					} else if (v>0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[15] += a;
//						sqsum[15] += a*a;
//					}
//					int a = inputImg[p+u+v*width];
//					sum[16] += a;
//					sqsum[16] += a*a;
//				}
//			}
//			//mean[16] = sum[16]/25;
//			//var[16] = (sqsum[16]/25-mean[16]*mean[16])/mean[16];
//			//if (var[16] < 2) outputImg[p]=255;
//			for (int i=0; i<8; i++) {
//				mean[i] = sum[i]/3;
//				var[i] = (sqsum[i]/3-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=8; i<16; i+=2) {
//				mean[i] = sum[i]/1;
//				mean[i+1] = sum[i+1]/5;
//				var[i] = (sqsum[i]/1-mean[i]*mean[i]);////sqrt(mean[i]);
//				var[i+1] = (sqsum[i+1]/5-mean[i+1]*mean[i+1]);////sqrt(mean[i+1]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//				if ((var[i+1] > varth)){// ||(var[i] > varth && var[i+1] < varth)) {
//					//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//					//outputImg[p]=255;
//					if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//					else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//				}
//			}
//			for (int i=0; i<8; i+=2) {
//				if ((var[i] > varth || var[i+1] > varth)){// ||(var[i] > varth && var[i+1] < varth)) {
//					//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//					//outputImg[p]=255;
//					if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//					else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//
//				}
//			}
//
//		}
//	}
//}



// LATEST
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=200.0;
//	int meanth=4;
//
//	//int sz = width*height;
//	for(int y = 1; y < height-1; y++ ) {
//		for(int x = 1; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [17];
//			double mean [17] = {0};
//			int sum [17] = {0};
//			int sqsum [17] = {0};
//			for(int v = -1; v <= 1; v++ ) {
//				for(int u = -1; u <= 1; u++ ) {
//					if(u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if (v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(-v<u) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if (-v>u) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//					if(v>0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[8] += a;
//						sqsum[8] += a*a;
//					} else if (v<0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[9] += a;
//						sqsum[9] += a*a;
//					}
//					if(v>0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[10] += a;
//						sqsum[10] += a*a;
//					} else if (v<0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[11] += a;
//						sqsum[11] += a*a;
//					}
//					if(v<0 && u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[12] += a;
//						sqsum[12] += a*a;
//					} else if (v>0 || u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[13] += a;
//						sqsum[13] += a*a;
//					}
//					if(v<0 && u<0) {
//						int a = inputImg[p+u+v*width];
//						sum[14] += a;
//						sqsum[14] += a*a;
//					} else if (v>0 || u>0) {
//						int a = inputImg[p+u+v*width];
//						sum[15] += a;
//						sqsum[15] += a*a;
//					}
//					int a = inputImg[p+u+v*width];
//					sum[16] += a;
//					sqsum[16] += a*a;
//				}
//			}
//			//mean[16] = sum[16]/25;
//			//var[16] = (sqsum[16]/25-mean[16]*mean[16])/mean[16];
//			//if (var[16] < 2) outputImg[p]=255;
//			for (int i=0; i<8; i++) {
//				mean[i] = sum[i]/3;
//				var[i] = (sqsum[i]/3-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if (var[i] < varth || var[i+1] < varth){// ||(var[i] > varth && var[i+1] < varth)) {
//						//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//						//outputImg[p]=255;
//						if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//						else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//					}
//				}
//			}
//
//			for (int i=8; i<16; i+=2) {
//				if (!type || type == (i/2+1)) {
//					mean[i] = sum[i]/1;
//					mean[i+1] = sum[i+1]/5;
//					var[i] = (sqsum[i]/1-mean[i]*mean[i]);////sqrt(mean[i]);
//					var[i+1] = (sqsum[i+1]/5-mean[i+1]*mean[i+1]);////sqrt(mean[i+1]);
//					//std::cout<<"d"<<var[i]<<std::endl;
//					if (var[i+1] < varth){// ||(var[i] > varth && var[i+1] < varth)) {
//						//std::cout<<"d"<<var1<<"d"<<var2<<std::endl;
//						//outputImg[p]=255;
//						if ((mean[i]-mean[i+1])> meanth ) {outputImg[p]=255;}
//						else if ((mean[i+1]-mean[i])> meanth ) {outputImg[p]=255;}
//					}
//				}
//			}
//
//
//		}
//	}
//}


void HomogeneousOperator(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						type)
{
	int p;
	int varth=200.0;
	int meanth=0;

	//int sz = width*height;
	for(int y = 1; y < height-1; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			double var [4];
			double mean [4] = {0};
			int sum [4] = {0};
			int sqsum [4] = {0};
			for(int v = -1; v <= 1; v++ ) {
				for(int u = -1; u <= 1; u++ ) {
					if(u<0) {
						int a = inputImg[p+u+v*width];
						sum[0] += a;
						sqsum[0] += a*a;
					} else if (u>0) {
						int a = inputImg[p+u+v*width];
						sum[1] += a;
						sqsum[1] += a*a;
					}
					if(v<0) {
						int a = inputImg[p+u+v*width];
						sum[2] += a;
						sqsum[2] += a*a;
					} else if (v>0) {
						int a = inputImg[p+u+v*width];
						sum[3] += a;
						sqsum[3] += a*a;
					}
				}
			}
			for (int i=0; i<4; i++) {
				mean[i] = sum[i]/3;
				var[i] = (sqsum[i]/3-mean[i]*mean[i]);////sqrt(mean[i]);
				//std::cout<<"d"<<var[i]<<std::endl;
			}

			for (int i=0; i<4; i+=2) {
				if (!type || type == (i/2+1)) {
					if ((mean[i]-mean[i+1])> meanth ) {
						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i]-mean[i+1]);}
					}
					else if ((mean[i+1]-mean[i])> meanth ) {
						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i+1]-mean[i]);}
					}
				}
			}
		}
	}

	for(int y = 1; y < height-1; y++ ) {
		for(int x = 2; x < width-2; x++ ) {
			p = x+y*width;
			double var [2];
			double mean [2] = {0};
			int sum [2] = {0};
			int sqsum [2] = {0};
			for(int v = -1; v <= 1; v++ ) {
				for(int u = -2; u <= 2; u++ ) {
					if(v<0) {
						int a = inputImg[p+u+v*width];
						sum[0] += a;
						sqsum[0] += a*a;
					} else if (v>0) {
						int a = inputImg[p+u+v*width];
						sum[1] += a;
						sqsum[1] += a*a;
					}
				}
			}
			for (int i=0; i<2; i++) {
				mean[i] = sum[i]/5;
				var[i] = (sqsum[i]/5-mean[i]*mean[i]);////sqrt(mean[i]);
				//std::cout<<"d"<<var[i]<<std::endl;
			}

			for (int i=0; i<2; i+=2) {
				if (!type || type == (i/2+1)+2) {
					if ((mean[i]-mean[i+1])> meanth ) {
						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i]-mean[i+1]);}
					}
					else if ((mean[i+1]-mean[i])> meanth ) {
						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i+1]-mean[i]);}
					}
				}
			}
		}
	}

	for(int y = 2; y < height-2; y++ ) {
		for(int x = 1; x < width-1; x++ ) {
			p = x+y*width;
			double var [2];
			double mean [2] = {0};
			int sum [2] = {0};
			int sqsum [2] = {0};
			for(int v = -2; v <= 2; v++ ) {
				for(int u = -1; u <= 1; u++ ) {
					if(u<0) {
						int a = inputImg[p+u+v*width];
						sum[0] += a;
						sqsum[0] += a*a;
					} else if (u>0) {
						int a = inputImg[p+u+v*width];
						sum[1] += a;
						sqsum[1] += a*a;
					}
				}
			}
			for (int i=0; i<2; i++) {
				mean[i] = sum[i]/5;
				var[i] = (sqsum[i]/5-mean[i]*mean[i]);////sqrt(mean[i]);
				//std::cout<<"d"<<var[i]<<std::endl;
			}

			for (int i=0; i<2; i+=2) {
				if (!type || type == (i/2+1)+3) {
					if ((mean[i]-mean[i+1])> meanth ) {
						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i]-mean[i+1]);}
					}
					else if ((mean[i+1]-mean[i])> meanth ) {
						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i+1]-mean[i]);}
					}
				}
			}
		}
	}
	for(int y = 2; y < height-2; y++ ) {
		for(int x = 2; x < width-2; x++ ) {
			p = x+y*width;
			double var [4];
			double mean [4] = {0};
			int sum [4] = {0};
			int sqsum [4] = {0};
			for(int v = -2; v <= 2; v++ ) {
				for(int u = -2; u <= 2; u++ ) {
					if(u>0 && v>0) {
						int a = inputImg[p+u+v*width];
						sum[0] += a;
						sqsum[0] += a*a;
					} else if (u<0 && v<0) {
						int a = inputImg[p+u+v*width];
						sum[1] += a;
						sqsum[1] += a*a;
					}
					if(u>0 && v<0) {
						int a = inputImg[p+u+v*width];
						sum[2] += a;
						sqsum[2] += a*a;
					} else if (u<0 && v>0) {
						int a = inputImg[p+u+v*width];
						sum[3] += a;
						sqsum[3] += a*a;
					}
				}
			}
			for (int i=0; i<4; i++) {
				mean[i] = sum[i]/4;
				var[i] = (sqsum[i]/4-mean[i]*mean[i]);////sqrt(mean[i]);
				//std::cout<<"d"<<var[i]<<std::endl;
			}

			for (int i=0; i<4; i+=2) {
				if (!type || type == (i/2+1)+4) {
					if ((mean[i]-mean[i+1])> meanth ) {
						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i]-mean[i+1]);}
					}
					else if ((mean[i+1]-mean[i])> meanth ) {
						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
						else {outputImg[p]+=(mean[i+1]-mean[i]);}
					}
				}
			}
		}
	}
}


void VarianceFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size)
{
	Mat src = _src.getMat();
	src.convertTo(src,CV_32F);
	Mat mu, mu2;
	blur(src, mu, Size(size, size));
	blur(src.mul(src), mu2, Size(size, size));
	cv::sqrt(mu2 - mu.mul(mu), _dst);
}


void DifferenceOfVariance(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Size size = src.size();
	Mat var3, var5, diff;
	VarianceFilter(_src,var3,3);
	VarianceFilter(_src,var5,5);

	//diff = (1./var5-1./var3);
	//diff = (1./(var5+1));
	diff = (var3);

	double mn,mx;
	minMaxIdx(diff,&mn,&mx);

	diff = (diff-mn)/(mx-mn)*255;

	diff.convertTo(_dst,CV_8UC1);
	minMaxIdx(_dst,&mn,&mx);
	std::cout<<mn<<","<<mx<<std::endl;
	//_dst.create(src.size(),src.type());
//	diff = (var3-var5);
//	Mat df(Size(3,3),CV_8UC1);
//	Mat df2(Size(3,3),CV_32FC1);
//
//	std::cout<<diff.type()<<","<<df.type()<<","<<df2.type()<<std::endl;
	//normalize(dst, _dst, 0.0, 1.0, NORM_MINMAX);
	//dst.copyTo(_dst);

//	namedWindow( "a", CV_WINDOW_AUTOSIZE );
//	imshow("a",dst);
//
//	waitKey(0);
//	Mat df;

}


}


