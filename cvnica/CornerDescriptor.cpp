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

//131016
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=200.0;
//	int meanth=0;
//
//	//int sz = width*height;
//	for(int y = 1; y < height-1; y++ ) {
//		for(int x = 1; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [4];
//			double mean [4] = {0};
//			int sum [4] = {0};
//			int sqsum [4] = {0};
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
//				}
//			}
//			for (int i=0; i<4; i++) {
//				mean[i] = sum[i]/3;
//				var[i] = (sqsum[i]/3-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<4; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth ) {
//						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth ) {
//						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 1; y < height-1; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -1; v <= 1; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<2; i++) {
//				mean[i] = sum[i]/5;
//				var[i] = (sqsum[i]/5-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+2) {
//					if ((mean[i]-mean[i+1])> meanth ) {
//						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth ) {
//						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 1; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -2; v <= 2; v++ ) {
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
//				}
//			}
//			for (int i=0; i<2; i++) {
//				mean[i] = sum[i]/5;
//				var[i] = (sqsum[i]/5-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+3) {
//					if ((mean[i]-mean[i+1])> meanth ) {
//						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth ) {
//						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [4];
//			double mean [4] = {0};
//			int sum [4] = {0};
//			int sqsum [4] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u>0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if (u<0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u>0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if (u<0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<4; i++) {
//				mean[i] = sum[i]/4;
//				var[i] = (sqsum[i]/4-mean[i]*mean[i]);////sqrt(mean[i]);
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<4; i+=2) {
//				if (!type || type == (i/2+1)+4) {
//					if ((mean[i]-mean[i+1])> meanth ) {
//						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth ) {
//						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//}


//131023
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=200.0;
//	int meanth=0;
//
//	//int sz = width*height;
//
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					int a = inputImg[p+u+v*width];
//					if(u<0 && v<0) {
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u>0 && v<0) {
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u<0 || v>0) {
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u<0 && v>0) {
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u>0 || v<0) {
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u>0 && v>0) {
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u<0 || v<0) {
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4;
//					var[i] = (sqsum[i]/4-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/16;
//					var[i] = (sqsum[i]/16-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth ) {
//						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth ) {
//						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 3; y < height-3; y++ ) {
//		for(int x = 3; x < width-3; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -3; v <= 3; v++ ) {
//				for(int u = -3; u <= 3; u++ ) {
//					if(u<0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u>0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u<0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u<0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u>0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u>0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u<0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/9;
//					var[i] = (sqsum[i]/9-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/33;
//					var[i] = (sqsum[i]/33-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)+4) {
//					if ((mean[i]-mean[i+1])> meanth ) {
//						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth ) {
//						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
//						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//}

//131030 9~12
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=3600.0;
//	int meanth=0;
//
//	//int sz = width*height;
//
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					int a = inputImg[p+u+v*width];
//					if(u<0 && v<0) {
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u>0 && v<0) {
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u<0 || v>0) {
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u<0 && v>0) {
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u>0 || v<0) {
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u>0 && v>0) {
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u<0 || v<0) {
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4;
//					var[i] = (sqsum[i]/4-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/16;
//					var[i] = (sqsum[i]/16-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//						//else {outputImg[p]+=(mean[i]-mean[i+1]);}
//
////						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
////						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//
////						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
////						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}

//	for(int y = 3; y < height-3; y++ ) {
//		for(int x = 3; x < width-3; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -3; v <= 3; v++ ) {
//				for(int u = -3; u <= 3; u++ ) {
//					if(u<0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u>0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u<0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u<0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u>0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u>0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u<0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/9.;
//					var[i] = (sqsum[i]/9.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/33.;
//					var[i] = (sqsum[i]/33.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]>varth && var[i+1]>varth) {
//						//int t = (mean[i]-mean[i+1]);//*
//						int t =sqrt((double)var[i+1]*(double)var[i]) ;//- 100000/sqrt((double)var[i+1]*(double)var[i]);
//						if (t>255) t=255;
//						if (outputImg[p]<t)outputImg[p]=t;
//						//else {outputImg[p]+=(mean[i]-mean[i+1]);}
//
////						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
////						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]>varth && var[i+1]>varth) {
//						//int t = (mean[i]-mean[i+1]);//*
//						int t = sqrt((double)var[i+1]*(double)var[i]) ;//- 100000/sqrt((double)var[i+1]*(double)var[i]);
//						if (t>255) t=255;
//						if (outputImg[p]<t)outputImg[p]=t;
//
////						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
////						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//
//				}
//			}
//		}
//	}
//}

// 131030 5~8 set 007
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=25.0;
//	int meanth=0;
//
//	for(int y = 1; y < height-2; y++ ) {
//		for(int x = 1; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -1; v <= 2; v++ ) {
//				for(int u = -1; u <= 2; u++ ) {
//					if(u>0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u<0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7.;
//					var[i] = (sqsum[i]/7.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 1; y < height-2; y++ ) {
//		for(int x = 2; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -1; v <= 2; v++ ) {
//				for(int u = -2; u <= 1; u++ ) {
//					if(u<0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7.;
//					var[i] = (sqsum[i]/7.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+1) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//
//
//
//	for(int y = 2; y < height-1; y++ ) {
//		for(int x = 1; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -2; v <= 1; v++ ) {
//				for(int u = -1; u <= 2; u++ ) {
//					if(u>0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u<0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7.;
//					var[i] = (sqsum[i]/7.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+2) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 2; y < height-1; y++ ) {
//		for(int x = 2; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -2; v <= 1; v++ ) {
//				for(int u = -2; u <= 1; u++ ) {
//					if(u<0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7;
//					var[i] = (sqsum[i]/7-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+3) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//}


// 131030 5~8
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=64.0;
//	int meanth=0;
//
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u+v == -2) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u+v == 2) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u-v == -2) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u-v == 2) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u+v == -2 || u+v == -3) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u+v == 2 || u+v == 3) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u-v == -2 || u-v == -3) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u-v == 2 || u-v == 3) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<4; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/3.;
//					var[i] = (sqsum[i]/3.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/3.;
//					var[i] = (sqsum[i]/3.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=4; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/5.;
//					var[i] = (sqsum[i]/5.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/5.;
//					var[i] = (sqsum[i]/5.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					} else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//}

// 131030 5~8 set 008
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=5.0;
//	int meanth=0;
//
//	for(int y = 1; y < height-2; y++ ) {
//		for(int x = 1; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -1; v <= 2; v++ ) {
//				for(int u = -1; u <= 2; u++ ) {
//					if(u>0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u<0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7.;
//					var[i] = (sqsum[i]/7.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 1; y < height-2; y++ ) {
//		for(int x = 2; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -1; v <= 2; v++ ) {
//				for(int u = -2; u <= 1; u++ ) {
//					if(u<0 && v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7.;
//					var[i] = (sqsum[i]/7.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+1) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//
//
//
//	for(int y = 2; y < height-1; y++ ) {
//		for(int x = 1; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -2; v <= 1; v++ ) {
//				for(int u = -1; u <= 2; u++ ) {
//					if(u>0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u<0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7.;
//					var[i] = (sqsum[i]/7.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+2) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//
//	for(int y = 2; y < height-1; y++ ) {
//		for(int x = 2; x < width-1; x++ ) {
//			p = x+y*width;
//			double var [2];
//			double mean [2] = {0};
//			int sum [2] = {0};
//			int sqsum [2] = {0};
//			for(int v = -2; v <= 1; v++ ) {
//				for(int u = -2; u <= 1; u++ ) {
//					if(u<0 && v<0) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<2; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/7;
//					var[i] = (sqsum[i]/7-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<2; i+=2) {
//				if (!type || type == (i/2+1)+3) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//}


// 9~12 set 011 var 25
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=4.0;
//	int meanth=0;
//
//	//int sz = width*height;
//
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					int a = inputImg[p+u+v*width];
//					if(u<0 && v<0) {
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u>0 || v>0) {
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u>0 && v<0) {
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u<0 || v>0) {
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u<0 && v>0) {
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u>0 || v<0) {
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u>0 && v>0) {
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u<0 || v<0) {
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//			for (int i=0; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/4.;
//					var[i] = (sqsum[i]/4.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/16.;
//					var[i] = (sqsum[i]/16.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//						//else {outputImg[p]+=(mean[i]-mean[i+1]);}
//
////						if (outputImg[p]+(mean[i]-mean[i+1])>255)outputImg[p]=255;
////						else {outputImg[p]+=(mean[i]-mean[i+1]);}
//					}
//					else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]>varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//
////						if (outputImg[p]+(mean[i+1]-mean[i])>255)outputImg[p]=255;
////						else {outputImg[p]+=(mean[i+1]-mean[i]);}
//					}
//				}
//			}
//		}
//	}
//}


//// 131030 5~8 set009 set010
//void HomogeneousOperator(
//		const unsigned char 			*inputImg,
//		unsigned char					*outputImg,
//		const int&						width,
//		const int&						height,
//		const int&						type)
//{
//	int p;
//	int varth=25.0;
//	int meanth=0;
//
//	for(int y = 2; y < height-2; y++ ) {
//		for(int x = 2; x < width-2; x++ ) {
//			p = x+y*width;
//			double var [8];
//			double mean [8] = {0};
//			int sum [8] = {0};
//			int sqsum [8] = {0};
//			for(int v = -2; v <= 2; v++ ) {
//				for(int u = -2; u <= 2; u++ ) {
//					if(u+v == -2) {
//						int a = inputImg[p+u+v*width];
//						sum[0] += a;
//						sqsum[0] += a*a;
//					} else if(u+v == 2) {
//						int a = inputImg[p+u+v*width];
//						sum[1] += a;
//						sqsum[1] += a*a;
//					}
//					if(u-v == -2) {
//						int a = inputImg[p+u+v*width];
//						sum[2] += a;
//						sqsum[2] += a*a;
//					} else if(u-v == 2) {
//						int a = inputImg[p+u+v*width];
//						sum[3] += a;
//						sqsum[3] += a*a;
//					}
//					if(u+v == -2 || u+v == -3) {
//						int a = inputImg[p+u+v*width];
//						sum[4] += a;
//						sqsum[4] += a*a;
//					} else if(u+v == 2 || u+v == 3) {
//						int a = inputImg[p+u+v*width];
//						sum[5] += a;
//						sqsum[5] += a*a;
//					}
//					if(u-v == -2 || u-v == -3) {
//						int a = inputImg[p+u+v*width];
//						sum[6] += a;
//						sqsum[6] += a*a;
//					} else if(u-v == 2 || u-v == 3) {
//						int a = inputImg[p+u+v*width];
//						sum[7] += a;
//						sqsum[7] += a*a;
//					}
//				}
//			}
//
//			for (int i=0; i<4; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/3.;
//					var[i] = (sqsum[i]/3.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/3.;
//					var[i] = (sqsum[i]/3.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=4; i<8; i++) {
//				if (i%2==0) {
//					mean[i] = sum[i]/5.;
//					var[i] = (sqsum[i]/5.-mean[i]*mean[i]);////sqrt(mean[i]);
//				} else {
//					mean[i] = sum[i]/5.;
//					var[i] = (sqsum[i]/5.-mean[i]*mean[i]);////sqrt(mean[i]);
//				}
//				//std::cout<<"d"<<var[i]<<std::endl;
//			}
//			for (int i=0; i<8; i+=2) {
//				if (!type || type == (i/2+1)) {
//					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
//					} else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
//						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
//					}
//				}
//			}
//		}
//	}
//}

// 131030 5~8 set013
void HomogeneousOperator(
		const unsigned char 			*inputImg,
		unsigned char					*outputImg,
		const int&						width,
		const int&						height,
		const int&						type)
{
	int p;
	int varth=25.0;
	int meanth=0;

	for(int y = 2; y < height-2; y++ ) {
		for(int x = 2; x < width-2; x++ ) {
			p = x+y*width;
			double var [8];
			double mean [8] = {0};
			int sum [8] = {0};
			int sqsum [8] = {0};
			for(int v = -2; v <= 2; v++ ) {
				for(int u = -2; u <= 2; u++ ) {
					if(u+v == -2) {
						int a = inputImg[p+u+v*width];
						sum[0] += a;
						sqsum[0] += a*a;
					} else if(u+v == 2) {
						int a = inputImg[p+u+v*width];
						sum[1] += a;
						sqsum[1] += a*a;
					}
					if(u-v == -2) {
						int a = inputImg[p+u+v*width];
						sum[2] += a;
						sqsum[2] += a*a;
					} else if(u-v == 2) {
						int a = inputImg[p+u+v*width];
						sum[3] += a;
						sqsum[3] += a*a;
					}
					if(u+v == -2 || u+v == -3) {
						int a = inputImg[p+u+v*width];
						sum[4] += a;
						sqsum[4] += a*a;
					} else if(u+v == 2 || u+v == 3) {
						int a = inputImg[p+u+v*width];
						sum[5] += a;
						sqsum[5] += a*a;
					}
					if(u-v == -2 || u-v == -3) {
						int a = inputImg[p+u+v*width];
						sum[6] += a;
						sqsum[6] += a*a;
					} else if(u-v == 2 || u-v == 3) {
						int a = inputImg[p+u+v*width];
						sum[7] += a;
						sqsum[7] += a*a;
					}
				}
			}

			for (int i=0; i<4; i++) {
				if (i%2==0) {
					mean[i] = sum[i]/3.;
					var[i] = (sqsum[i]/3.-mean[i]*mean[i]);////sqrt(mean[i]);
				} else {
					mean[i] = sum[i]/3.;
					var[i] = (sqsum[i]/3.-mean[i]*mean[i]);////sqrt(mean[i]);
				}
				//std::cout<<"d"<<var[i]<<std::endl;
			}
			for (int i=4; i<8; i++) {
				if (i%2==0) {
					mean[i] = sum[i]/5.;
					var[i] = (sqsum[i]/5.-mean[i]*mean[i]);////sqrt(mean[i]);
				} else {
					mean[i] = sum[i]/5.;
					var[i] = (sqsum[i]/5.-mean[i]*mean[i]);////sqrt(mean[i]);
				}
				//std::cout<<"d"<<var[i]<<std::endl;
			}
			for (int i=0; i<8; i+=2) {
				if (!type || type == (i/2+1)) {
					if ((mean[i]-mean[i+1])> meanth && var[i]<varth && var[i+1]<varth) {
						if (outputImg[p]<(mean[i]-mean[i+1]))outputImg[p]=(mean[i]-mean[i+1]);
					} else if ((mean[i+1]-mean[i])> meanth  && var[i]<varth && var[i+1]<varth) {
						if (outputImg[p]<(mean[i+1]-mean[i]))outputImg[p]=(mean[i+1]-mean[i]);
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

Mat kernels(
		int								type,
		Point&							point)
{
	Mat kernel;
	if (type==0){
		kernel = (Mat_<float>(5,5) << 1,1,1,1,1 , 1,1,1,1,1 , 1,1,0,0,0 , 1,1,0,0,0 , 1,1,0,0,0);
		point = Point(-1,-1);
	} else if (type==1){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,1,1 , 0,0,0,1,1);
		point = Point(-1,-1);
	} else if (type==2){
		kernel = (Mat_<float>(5,5) << 1,1,1,1,1 , 1,1,1,1,1 , 0,0,0,1,1 , 0,0,0,1,1 , 0,0,0,1,1);
		point = Point(-1,-1);
	} else if (type==3){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0 , 1,1,0,0,0 , 1,1,0,0,0);
		point = Point(-1,-1);
	} else if (type==4){
		kernel = (Mat_<float>(5,5) << 1,1,0,0,0 , 1,1,0,0,0 , 1,1,0,0,0 , 1,1,1,1,1 , 1,1,1,1,1);
		point = Point(-1,-1);
	} else if (type==5){
		kernel = (Mat_<float>(5,5) << 0,0,0,1,1 , 0,0,0,1,1 , 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==6){
		kernel = (Mat_<float>(5,5) << 0,0,0,1,1 , 0,0,0,1,1 , 0,0,0,1,1 , 1,1,1,1,1 , 1,1,1,1,1);
		point = Point(-1,-1);
	} else if (type==7){
		kernel = (Mat_<float>(5,5) << 1,1,0,0,0 , 1,1,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	}


	else if (type==8){
		kernel = (Mat_<float>(6,6) << 1,1,1,1,1,0 , 1,1,1,1,1,0 , 1,1,0,0,0,0 , 1,1,0,0,0,0 , 1,1,0,0,0,0 , 0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==9){
		kernel = (Mat_<float>(6,6) << 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,1,1 , 0,0,0,0,1,1);
		point = Point(-1,-1);
	} else if (type==10){
		kernel = (Mat_<float>(6,6) << 1,1,1,1,1,0 , 1,1,1,1,1,0 , 0,0,0,0,1,1 , 0,0,0,0,1,1 , 0,0,0,0,1,1 , 0,0,0,0,0,0);
		point = Point(3,3);
	} else if (type==11){
		kernel = (Mat_<float>(6,6) << 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 1,1,0,0,0,0 , 1,1,0,0,0,0);
		point = Point(3,3);
	} else if (type==12){
		kernel = (Mat_<float>(6,6) << 0,0,0,0,0,0 , 1,1,0,0,0,0 , 1,1,0,0,0,0 , 1,1,0,0,0,0 , 1,1,1,1,1,0 , 1,1,1,1,1,0);
		point = Point(-1,-1);
	} else if (type==13){
		kernel = (Mat_<float>(6,6) << 0,0,0,0,1,1 , 0,0,0,0,1,1 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==14){
		kernel = (Mat_<float>(6,6) << 0,0,0,0,0,0 , 0,0,0,0,1,1 , 0,0,0,0,1,1 , 0,0,0,0,1,1 , 0,1,1,1,1,1 , 0,1,1,1,1,1);
		point = Point(-1,-1);
	} else if (type==15){
		kernel = (Mat_<float>(6,6) << 1,1,0,0,0,0 , 1,1,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0 , 0,0,0,0,0,0);
		point = Point(-1,-1);
	}


	else if (type==16){
		kernel = (Mat_<float>(7,7) << 1,1,1,1,1,0,0 , 1,1,1,1,1,0,0 , 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==17){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1);
		point = Point(-1,-1);
	} else if (type==18){
		kernel = (Mat_<float>(7,7) << 0,0,1,1,1,1,1 , 0,0,1,1,1,1,1 , 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==19){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==20){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0 , 1,1,1,1,1,0,0 , 1,1,1,1,1,0,0);
		point = Point(-1,-1);
	} else if (type==21){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==22){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1 , 0,0,1,1,1,1,1 , 0,0,1,1,1,1,1);
		point = Point(-1,-1);
	} else if (type==23){
		kernel = (Mat_<float>(7,7) << 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	}


	else if (type==24){
		kernel = (Mat_<float>(5,5) << 0,0,1,0,0 , 0,0,0,1,0 , 0,0,0,0,1 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==25){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 1,0,0,0,0 , 0,1,0,0,0 , 0,0,1,0,0);
		point = Point(-1,-1);
	} else if (type==26){
		kernel = (Mat_<float>(5,5) << 0,0,1,0,0 , 0,1,0,0,0 , 1,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==27){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,1 , 0,0,0,1,0 , 0,0,1,0,0);
		point = Point(-1,-1);
	} else if (type==28){
		kernel = (Mat_<float>(5,5) << 0,0,1,1,0 , 0,0,0,1,1 , 0,0,0,0,1 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==29){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 1,0,0,0,0 , 1,1,0,0,0 , 0,1,1,0,0);
		point = Point(-1,-1);
	} else if (type==30){
		kernel = (Mat_<float>(5,5) << 0,1,1,0,0 , 1,1,0,0,0 , 1,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==31){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 0,0,0,0,1 , 0,0,0,1,1 , 0,0,1,1,0);
		point = Point(-1,-1);
	}


	else if (type==32){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 0,0,1,1,1 , 0,0,1,0,0 , 0,0,1,0,0);
		point = Point(-1,-1);
	} else if (type==33){
		kernel = (Mat_<float>(5,5) << 0,0,0,0,0 , 0,0,0,0,0 , 1,1,1,0,0 , 0,0,1,0,0 , 0,0,1,0,0);
		point = Point(-1,-1);
	} else if (type==34){
		kernel = (Mat_<float>(5,5) << 0,0,1,0,0 , 0,0,1,0,0 , 0,0,1,1,1 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==35){
		kernel = (Mat_<float>(5,5) << 0,0,1,0,0 , 0,0,1,0,0 , 1,1,1,0,0 , 0,0,0,0,0 , 0,0,0,0,0);
		point = Point(-1,-1);
	}

	else if (type==36){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,1,1,1,1 , 0,0,0,1,1,1,1 , 0,0,0,1,1,0,0 , 0,0,0,1,1,0,0);
		point = Point(-1,-1);
	} else if (type==37){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 1,1,1,1,0,0,0 , 1,1,1,1,0,0,0 , 0,0,1,1,0,0,0 , 0,0,1,1,0,0,0);
		point = Point(-1,-1);
	} else if (type==38){
		kernel = (Mat_<float>(7,7) << 0,0,0,1,1,0,0 , 0,0,0,1,1,0,0 , 0,0,0,1,1,1,1 , 0,0,0,1,1,1,1 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==39){
		kernel = (Mat_<float>(7,7) << 0,0,1,1,0,0,0 , 0,0,1,1,0,0,0 , 1,1,1,1,0,0,0 , 1,1,1,1,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	}

	else if (type==40){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,1,1,1,1 , 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0);
		point = Point(-1,-1);
	} else if (type==41){
		kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 1,1,1,1,0,0,0 , 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0);
		point = Point(-1,-1);
	} else if (type==42){
		kernel = (Mat_<float>(7,7) << 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0 , 0,0,0,1,1,1,1 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==43){
		kernel = (Mat_<float>(7,7) << 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0 , 0,0,0,1,0,0,0 , 1,1,1,1,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
		point = Point(-1,-1);
	}

	else if (type==44){
		kernel = (Mat_<float>(11,7) <<  1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0 ,
										1,1,1,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==45){
		kernel = (Mat_<float>(11,7) <<  0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1 ,
										0,0,0,0,1,1,1);
		point = Point(-1,-1);
	} else if (type==46){
		kernel = (Mat_<float>(7,11) <<  1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==47){
		kernel = (Mat_<float>(7,11) <<  0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1);
		point = Point(-1,-1);
	}

	else if (type==48){
		kernel = (Mat_<float>(11,10) << 1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==49){
		kernel = (Mat_<float>(11,10) << 0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0 ,
										0,0,0,0,1,1,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==50){
		kernel = (Mat_<float>(11,10) << 0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,1,1,1);
		point = Point(-1,-1);
	} else if (type==51){
		kernel = (Mat_<float>(10,11) << 1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==52){
		kernel = (Mat_<float>(10,11) << 0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==53){
		kernel = (Mat_<float>(10,11) << 0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1);
		point = Point(-1,-1);
	}

	else if (type==54){
		kernel = (Mat_<float>(11,8) <<  1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==55){
		kernel = (Mat_<float>(11,8) <<  0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,1,1,1);
		point = Point(-1,-1);
	} else if (type==56){
		kernel = (Mat_<float>(8,11) <<  1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==57){
		kernel = (Mat_<float>(8,11) <<  0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1);
		point = Point(-1,-1);
	}


	else if (type==58){
		kernel = (Mat_<float>(11,12) << 1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0 ,
										1,1,1,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==59){
		kernel = (Mat_<float>(11,12) << 0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0 ,
										0,0,0,0,0,1,1,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==60){
		kernel = (Mat_<float>(11,12) << 0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1 ,
										0,0,0,0,0,0,0,0,0,1,1,1);
		point = Point(-1,-1);
	} else if (type==61){
		kernel = (Mat_<float>(12,11) << 1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==62){
		kernel = (Mat_<float>(12,11) << 0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0);
		point = Point(-1,-1);
	} else if (type==63){
		kernel = (Mat_<float>(12,11) << 0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										0,0,0,0,0,0,0,0,0,0,0 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1 ,
										1,1,1,1,1,1,1,1,1,1,1);
		point = Point(-1,-1);
	}


	else if (type==64){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,1,1,1,1,0,0 , 0,1,0,0,0,0,0 , 0,1,0,0,0,0,0 , 0,1,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==65){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1);
			point = Point(-1,-1);
		} else if (type==66){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,1,1,1,1,0 , 0,0,0,0,0,1,0 , 0,0,0,0,0,1,0 , 0,0,0,0,0,1,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==67){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==68){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,1,0,0,0,0,0 , 0,1,0,0,0,0,0 , 0,1,0,0,0,0,0 , 0,1,1,1,1,0,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==69){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,1,1 , 0,0,0,0,0,1,1 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==70){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,1,0 , 0,0,0,0,0,1,0 , 0,0,0,0,0,1,0 , 0,0,1,1,1,1,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==71){
			kernel = (Mat_<float>(7,7) << 1,1,0,0,0,0,0 , 1,1,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		}

	return kernel;
}

void CornerDetectorBasedOnEdge(
		InputArray 						_src,
		OutputArray						_dst,
		int								type)
{
	Mat src,__src = _src.getMat();
	Mat kernel;
	Mat mean;
	Mat thr;
	Mat meanDiff;
	Point point;
	double min, max;
	//double varth=187./255;
	double varth=187./255;
	int meanth=0;

	Mat frame (__src.size(),CV_32FC1);
	//Mat frame_ = Mat(frame, Rect(2, 2, __src.cols-4, __src.rows-4));
	Mat frame_ = Mat(frame, Rect(3, 3, __src.cols-6, __src.rows-6));
	//type = 21;
	__src.convertTo(src,CV_32FC1);
	kernel = kernels(type,point);

	//MeanMap32bit(src,mean,kernel,point);

	matchTemplate (src,kernel,mean,CV_TM_CCOEFF_NORMED);
//	namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	minMaxLoc (mean,&min,&max);
//	imshow( "c", mean);//thrCrCb[0] );
//	waitKey(0);

	threshold(mean,thr,varth,255.0,THRESH_BINARY);
	thr.copyTo(frame_);
	frame.convertTo(_dst,CV_8UC1);

//	minMaxLoc (thr,&min,&max);
//	//mean/=max;
//			namedWindow( "d", CV_WINDOW_AUTOSIZE );
//			imshow( "d", thr);//thrCrCb[0] );
//			waitKey(0);
//
//
//	threshold(mean,thr,varth,1.0,THRESH_BINARY_INV);
//	threshold(varI,thrI,varth,1.0,THRESH_BINARY_INV);
//
//	absdiff(meanO, meanI, meanDiff);
//
//	meanDiff = meanDiff.mul(thrO);
//	meanDiff = meanDiff.mul(thrI);
//
//	meanDiff /= 2;
//	meanDiff.convertTo(_dst,CV_8UC1);
}


void CornerDetector(
		InputArray 						_src,
		OutputArray						_dst,
		int								type,
		int								nPart)
{
	Mat src,__src = _src.getMat();
	Mat kernel[nPart];
	Mat var[nPart];
	Mat mean[nPart];
	Mat thr[nPart];
	Mat meanDiff[nPart];
	Point point[nPart];
	double min_, max_;
	double varth=16.0;
	int meanth=0;

	//type = 21;
	__src.convertTo(src,CV_32F);
	if(type == 9) {
		kernel[0] = kernels(0,point[0]);
		kernel[1] = kernels(1,point[1]);
	} else if (type == 10) {
		kernel[0] = kernels(2,point[0]);
		kernel[1] = kernels(3,point[1]);
	} else if (type == 11) {
		kernel[0] = kernels(4,point[0]);
		kernel[1] = kernels(5,point[1]);
	} else if (type == 12) {
		kernel[0] = kernels(6,point[0]);
		kernel[1] = kernels(7,point[1]);
	} else if (type == 17) {
		kernel[0] = kernels(8,point[0]);
		kernel[1] = kernels(9,point[1]);
	} else if (type == 18) {
		kernel[0] = kernels(10,point[0]);
		kernel[1] = kernels(11,point[1]);
	} else if (type == 19) {
		kernel[0] = kernels(12,point[0]);
		kernel[1] = kernels(13,point[1]);
	} else if (type == 20) {
		kernel[0] = kernels(14,point[0]);
		kernel[1] = kernels(15,point[1]);
	} else if (type == 21) {
		kernel[0] = kernels(16,point[0]);
		kernel[1] = kernels(17,point[1]);
	} else if (type == 22) {
		kernel[0] = kernels(18,point[0]);
		kernel[1] = kernels(19,point[1]);
	} else if (type == 23) {
		kernel[0] = kernels(20,point[0]);
		kernel[1] = kernels(21,point[1]);
	} else if (type == 24) {
		kernel[0] = kernels(22,point[0]);
		kernel[1] = kernels(23,point[1]);
	} else if (type == 5) {
		kernel[0] = kernels(24,point[0]);
		kernel[1] = kernels(25,point[1]);
	} else if (type == 6) {
		kernel[0] = kernels(26,point[0]);
		kernel[1] = kernels(27,point[1]);
	} else if (type == 7) {
		kernel[0] = kernels(28,point[0]);
		kernel[1] = kernels(29,point[1]);
	} else if (type == 8) {
		kernel[0] = kernels(30,point[0]);
		kernel[1] = kernels(31,point[1]);
	} else if (type == 33) {
		kernel[0] = kernels(44,point[0]);
		kernel[1] = kernels(45,point[1]);
	} else if (type == 34) {
		kernel[0] = kernels(46,point[0]);
		kernel[1] = kernels(47,point[1]);
	} else if (type == 35) {
		kernel[0] = kernels(48,point[0]);
		kernel[1] = kernels(49,point[1]);
		kernel[2] = kernels(50,point[2]);
	} else if (type == 36) {
		kernel[0] = kernels(51,point[0]);
		kernel[1] = kernels(52,point[1]);
		kernel[2] = kernels(53,point[2]);
	} else if (type == 37) {
		kernel[0] = kernels(54,point[0]);
		kernel[1] = kernels(55,point[1]);
	} else if (type == 38) {
		kernel[0] = kernels(56,point[0]);
		kernel[1] = kernels(57,point[1]);
	} else if (type == 39) {
		kernel[0] = kernels(58,point[0]);
		kernel[1] = kernels(59,point[1]);
		kernel[2] = kernels(60,point[2]);
	} else if (type == 40) {
		kernel[0] = kernels(61,point[0]);
		kernel[1] = kernels(62,point[1]);
		kernel[2] = kernels(63,point[2]);
	} else if (type == 41) {
		kernel[0] = kernels(64,point[0]);
		kernel[1] = kernels(65,point[1]);
	} else if (type == 42) {
		kernel[0] = kernels(66,point[0]);
		kernel[1] = kernels(67,point[1]);
	} else if (type == 43) {
		kernel[0] = kernels(68,point[0]);
		kernel[1] = kernels(69,point[1]);
	} else if (type == 44) {
		kernel[0] = kernels(70,point[0]);
		kernel[1] = kernels(71,point[1]);
	}
	for (int i=0; i<nPart; i++) {
		MeanMap32bit(src,mean[i],kernel[i],point[i]);
		VarianceMap32bit(src,var[i],kernel[i],point[i]);
		threshold(var[i],thr[i],varth,1.0,THRESH_BINARY_INV);
	}

//	MeanMap32bit(src,mean[0],kernel[0],point[0]);
//	MeanMap32bit(src,mean[1],kernel[1],point[1]);
//	VarianceMap32bit(src,var[0],kernel[0],point[0]);
//	VarianceMap32bit(src,var[1],kernel[1],point[1]);
//	minMaxLoc(var[0],&min,&max);
//	threshold(var[0],thr[0],varth,1.0,THRESH_BINARY_INV);
//	threshold(var[1],thr[1],varth,1.0,THRESH_BINARY_INV);

	if (nPart==3) {
		absdiff(mean[0], mean[1], meanDiff[0]);
		absdiff(mean[2], mean[1], meanDiff[1]);

		min (meanDiff[1],meanDiff[0],meanDiff[2]);

		meanDiff[2] = meanDiff[2].mul(thr[0]);
		meanDiff[2] = meanDiff[2].mul(thr[1]);
		meanDiff[2] = meanDiff[2].mul(thr[2]);

		meanDiff[2] /= 4;
		meanDiff[2].convertTo(_dst,CV_8UC1);
	} else {
		absdiff(mean[0], mean[1], meanDiff[0]);

		meanDiff[0] = meanDiff[0].mul(thr[0]);
		meanDiff[0] = meanDiff[0].mul(thr[1]);

		meanDiff[0] /= 2;
		meanDiff[0].convertTo(_dst,CV_8UC1);
	}
}

Mat RGBThresholdPoint(
		Size							size,
		Vector< Vector<int> >&			cornerpoints,
		int								r,
		int								g,
		int								b,
		int								tolerance)
{
	Mat temp (size,CV_8UC1);
	size_t s = cornerpoints.size();
	int rb = r - tolerance; if(rb<0) rb=0; if(rb>255) rb=255;
	int ru = r + tolerance; if(ru<0) ru=0; if(ru>255) ru=255;
	int gb = g - tolerance; if(gb<0) gb=0; if(gb>255) gb=255;
	int gu = g + tolerance; if(gu<0) gu=0; if(gu>255) gu=255;
	int bb = b - tolerance; if(bb<0) bb=0; if(bb>255) bb=255;
	int bu = b + tolerance; if(bu<0) bu=0; if(bu>255) bu=255;

	for (size_t i=0; i<s; i++){
		if (cornerpoints[i][2] >= rb && cornerpoints[i][2] <= ru
				&& cornerpoints[i][3] >= gb && cornerpoints[i][3] <= gu
				&& cornerpoints[i][4] >= bb && cornerpoints[i][4] <= bu) {
			temp.at<uchar>(cornerpoints[i][1],cornerpoints[i][0]) = 255;
		}
	}
	return temp;
}

void RGBhistogram(
		Mat								__src,
		Mat								points,
		Vector< Vector<int> >&			cornerpoints,
		int								type,
		int								nPart)
{
		Mat src;
		Mat kernel[nPart];
		Mat var[nPart];
		Mat mean[nPart];
		Mat thr[nPart];
		Mat meanDiff[nPart];
		Point point[nPart];
		double min_, max_;
		double varth=16.0;
		int meanth=0;
		int dx[2], dy[2];
		//type = 21;
		__src.convertTo(src,CV_32F);

		if(type == 9) {
			kernel[0] = kernels(0,point[0]);
			kernel[1] = kernels(1,point[1]);
		} else if (type == 10) {
			kernel[0] = kernels(2,point[0]);
			kernel[1] = kernels(3,point[1]);
		} else if (type == 11) {
			kernel[0] = kernels(4,point[0]);
			kernel[1] = kernels(5,point[1]);
		} else if (type == 12) {
			kernel[0] = kernels(6,point[0]);
			kernel[1] = kernels(7,point[1]);
		} else if (type == 17) {
			kernel[0] = kernels(8,point[0]);
			kernel[1] = kernels(9,point[1]);
		} else if (type == 18) {
			kernel[0] = kernels(10,point[0]);
			kernel[1] = kernels(11,point[1]);
		} else if (type == 19) {
			kernel[0] = kernels(12,point[0]);
			kernel[1] = kernels(13,point[1]);
		} else if (type == 20) {
			kernel[0] = kernels(14,point[0]);
			kernel[1] = kernels(15,point[1]);
		} else if (type == 21) {
			kernel[0] = kernels(16,point[0]);
			kernel[1] = kernels(17,point[1]);
		} else if (type == 22) {
			kernel[0] = kernels(18,point[0]);
			kernel[1] = kernels(19,point[1]);
		} else if (type == 23) {
			kernel[0] = kernels(20,point[0]);
			kernel[1] = kernels(21,point[1]);
		} else if (type == 24) {
			kernel[0] = kernels(22,point[0]);
			kernel[1] = kernels(23,point[1]);
		} else if (type == 5) {
			kernel[0] = kernels(24,point[0]);
			kernel[1] = kernels(25,point[1]);
		} else if (type == 6) {
			kernel[0] = kernels(26,point[0]);
			kernel[1] = kernels(27,point[1]);
		} else if (type == 7) {
			kernel[0] = kernels(28,point[0]);
			kernel[1] = kernels(29,point[1]);
		} else if (type == 8) {
			kernel[0] = kernels(30,point[0]);
			kernel[1] = kernels(31,point[1]);
		} else if (type == 33) {
			kernel[0] = kernels(44,point[0]);
			kernel[1] = kernels(45,point[1]);
		} else if (type == 34) {
			kernel[0] = kernels(46,point[0]);
			kernel[1] = kernels(47,point[1]);
		} else if (type == 35) {
			kernel[0] = kernels(48,point[0]);
			kernel[1] = kernels(49,point[1]);
			kernel[2] = kernels(50,point[2]);
		} else if (type == 36) {
			kernel[0] = kernels(51,point[0]);
			kernel[1] = kernels(52,point[1]);
			kernel[2] = kernels(53,point[2]);
		} else if (type == 37) {
			kernel[0] = kernels(54,point[0]);
			kernel[1] = kernels(55,point[1]);
		} else if (type == 38) {
			kernel[0] = kernels(56,point[0]);
			kernel[1] = kernels(57,point[1]);
		} else if (type == 39) {
			kernel[0] = kernels(58,point[0]);
			kernel[1] = kernels(59,point[1]);
			kernel[2] = kernels(60,point[2]);
		} else if (type == 40) {
			kernel[0] = kernels(61,point[0]);
			kernel[1] = kernels(62,point[1]);
			kernel[2] = kernels(63,point[2]);
		} else if (type == 41) {
			kernel[0] = kernels(64,point[0]);
			kernel[1] = kernels(65,point[1]);
			dx[0]=-2;	dy[0]=-2;
			dx[1]=2;	dy[1]=2;
		} else if (type == 42) {
			kernel[0] = kernels(66,point[0]);
			kernel[1] = kernels(67,point[1]);
			dx[0]=2;	dy[0]=-2;
			dx[1]=-2;	dy[1]=2;
		} else if (type == 43) {
			kernel[0] = kernels(68,point[0]);
			kernel[1] = kernels(69,point[1]);
			dx[0]=-2;	dy[0]=2;
			dx[1]=2;	dy[1]=-2;
		} else if (type == 44) {
			kernel[0] = kernels(70,point[0]);
			kernel[1] = kernels(71,point[1]);
			dx[0]=2;	dy[0]=2;
			dx[1]=-2;	dy[1]=-2;
		}
		for (int i=0; i<nPart; i++) {
			MeanMap32bit(src,mean[i],kernel[i],point[i]);
		}

		//std::cout<<": "<<mean[1].channels()<<std::endl;
		//std::cout<<": "<<points.type()<<std::endl;

		//Mat df; mean[1].convertTo(df,CV_8U);
//		namedWindow( "c", CV_WINDOW_AUTOSIZE );
//		imshow( "c", mean[0]/255);//thrCrCb[0] );
//		namedWindow( "d", CV_WINDOW_AUTOSIZE );
//		imshow( "d", mean[1]/255);//thrCrCb[0] );
//
//		namedWindow( "e", CV_WINDOW_AUTOSIZE );
//		imshow( "e", points);//thrCrCb[0] );
//		waitKey(0);

	Mat mean8[2]; mean[0].convertTo(mean8[0],CV_8UC1);
	mean[1].convertTo(mean8[1],CV_8UC1);
		//mean[1]/=255;
		int count=0;
	for(int y=0; y < points.rows; y++) {
		for(int x=0; x < points.cols; x++) {
			if((int)points.at<uchar>(y,x) != 255) {
				continue;
			}
			for (int i=0; i<nPart; i++) {
				Vector<int> temp;
				temp.push_back(x+dx[i]);
				temp.push_back(y+dy[i]);
				temp.push_back((int)(mean8[i].at<Vec3b>(y,x)[0]));
				temp.push_back((int)(mean8[i].at<Vec3b>(y,x)[1]));
				temp.push_back((int)(mean8[i].at<Vec3b>(y,x)[2]));
				cornerpoints.push_back(temp);
				std::cout<<": "<<temp[0]<<","<<temp[1]<<","<<temp[2]<<","<<temp[3]<<","<<temp[4]<<std::endl;
			}
			count++;
		}
	}
	///std::cout<<" count: "<<count<<std::endl;
}

void VarianceMap32bit(
		InputArray 						_src,
		OutputArray						_dst,
		Mat								kernel,
		Point							point)
{
	Mat src = _src.getMat(),temp,temp2,var;
	src.convertTo(src,CV_32F);

	filter2D (src,temp,CV_32F,kernel,point,0,BORDER_CONSTANT);
	filter2D (src.mul(src),temp2,CV_32F,kernel,point,0,BORDER_CONSTANT);

	temp /= sum(kernel)[0];
	temp2 /= sum(kernel)[0];

	var = temp2 -  temp.mul(temp);
	var.convertTo(_dst,CV_32F);
}

void MeanMap32bit(
		InputArray 						_src,
		OutputArray						_dst,
		Mat								kernel,
		Point							point)
{
	Mat src = _src.getMat(),temp;

	src.convertTo(src,CV_32F);

	filter2D (src,temp,CV_32F,kernel,point,0,BORDER_CONSTANT);
	temp /= sum(kernel)[0];
	temp.convertTo(_dst,CV_32F);
}

void VarianceMap(
		InputArray 						_src,
		OutputArray						_dst,
		int								type)
{
	Mat src = _src.getMat(),temp,temp2,kernel,var;
	Point point;
	double min, max;

	src.convertTo(src,CV_32F);

	kernel = kernels(type,point);

	filter2D (src,temp,CV_32F,kernel,point,0,BORDER_CONSTANT);
	filter2D (src.mul(src),temp2,CV_32F,kernel,point,0,BORDER_CONSTANT);

	temp /= sum(kernel)[0];
	temp2 /= sum(kernel)[0];

	var = temp2 -  temp.mul(temp);
	var /= 255/4;

	minMaxLoc(var,&min,&max);
	var.convertTo(_dst,CV_8UC1);

//	namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	imshow( "c", _dst);//thrCrCb[0] );
//	waitKey(0);
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

	Mat var3_,var5_;
	var3.convertTo(var3_,CV_32FC1);
	var5.convertTo(var5_,CV_32FC1);
	//diff = (1./var5-1./var3);
	//diff = (1./(var5+1));
	diff = (var5_-var3_);

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


