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



void MorphologicalThinning(CvMat *pSrc, CvMat *pDst) {
        bool bDone = false;
        int rows = pSrc->rows;
        int cols = pSrc->cols;
        /// pad source
        CvMat *p_enlarged_src = cvCreateMat(rows + 2, cols + 2, CV_32FC1);
        for(int i = 0; i < (rows+2); i++) {
                CV_MAT_ELEM(*p_enlarged_src, float, i, 0)	 = 0.0f;
                CV_MAT_ELEM(*p_enlarged_src, float, i, cols+1)	= 0.0f;
        }
        for(int j = 0; j < (cols+2); j++) {
                CV_MAT_ELEM(*p_enlarged_src, float, 0, j)	 = 0.0f;
                CV_MAT_ELEM(*p_enlarged_src, float, rows+1, j)	= 0.0f;
        }
        for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                        if (CV_MAT_ELEM(*pSrc, float, i, j) >= 0.5f) {
                                CV_MAT_ELEM(*p_enlarged_src, float, i+1, j+1) = 1.0f;
                        }
                        else
                                CV_MAT_ELEM(*p_enlarged_src, float, i+1, j+1) = 0.0f;
                }
        }
        /// start to thin
        CvMat *p_thinMat1	= cvCreateMat(rows + 2, cols + 2, CV_32FC1);
        CvMat *p_thinMat2	= cvCreateMat(rows + 2, cols + 2, CV_32FC1);
        CvMat *p_cmp	 = cvCreateMat(rows + 2, cols + 2, CV_8UC1);
        while (bDone != true) {
                /// sub-iteration 1
                ThinSubiteration1(p_enlarged_src, p_thinMat1);
                /// sub-iteration 2
                ThinSubiteration2(p_thinMat1, p_thinMat2);
                /// compare
                cvCmp(p_enlarged_src, p_thinMat2, p_cmp, CV_CMP_EQ);
                /// check
                int num_non_zero = cvCountNonZero(p_cmp);
                if(num_non_zero == (rows + 2) * (cols + 2)) {
                        bDone = true;
                }
                /// copy
                cvCopy(p_thinMat2, p_enlarged_src);
        }
        /// copy result
        for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                        CV_MAT_ELEM(*pDst, float, i, j) = CV_MAT_ELEM(*p_enlarged_src, float, i+1, j+1);
                }
        }
        /// clean memory
        cvReleaseMat(&p_enlarged_src);
        cvReleaseMat(&p_thinMat1);
        cvReleaseMat(&p_thinMat2);
        cvReleaseMat(&p_cmp);
}
void ThinSubiteration1(CvMat *pSrc, CvMat *pDst) {
        int rows = pSrc->rows;
        int cols = pSrc->cols;
        cvCopy(pSrc, pDst);
        for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                        if(CV_MAT_ELEM(*pSrc, float, i, j) == 1.0f) {
                                /// get 8 neighbors
                                /// calculate C(p)
                                int neighbor0 = (int) CV_MAT_ELEM(*pSrc, float, i-1, j-1);
                                int neighbor1 = (int) CV_MAT_ELEM(*pSrc, float, i-1, j);
                                int neighbor2 = (int) CV_MAT_ELEM(*pSrc, float, i-1, j+1);
                                int neighbor3 = (int) CV_MAT_ELEM(*pSrc, float, i, j+1);
                                int neighbor4 = (int) CV_MAT_ELEM(*pSrc, float, i+1, j+1);
                                int neighbor5 = (int) CV_MAT_ELEM(*pSrc, float, i+1, j);
                                int neighbor6 = (int) CV_MAT_ELEM(*pSrc, float, i+1, j-1);
                                int neighbor7 = (int) CV_MAT_ELEM(*pSrc, float, i, j-1);
                                int C = int(~neighbor1 & ( neighbor2 | neighbor3)) +
                                                 int(~neighbor3 & ( neighbor4 | neighbor5)) +
                                                 int(~neighbor5 & ( neighbor6 | neighbor7)) +
                                                 int(~neighbor7 & ( neighbor0 | neighbor1));
                                if(C == 1) {
                                        /// calculate N
                                        int N1 = int(neighbor0 | neighbor1) +
                                                         int(neighbor2 | neighbor3) +
                                                         int(neighbor4 | neighbor5) +
                                                         int(neighbor6 | neighbor7);
                                        int N2 = int(neighbor1 | neighbor2) +
                                                         int(neighbor3 | neighbor4) +
                                                         int(neighbor5 | neighbor6) +
                                                         int(neighbor7 | neighbor0);
                                        int N = min(N1,N2);
                                        if ((N == 2) || (N == 3)) {
                                                /// calculate criteria 3
                                                int c3 = ( neighbor1 | neighbor2 | ~neighbor4) & neighbor3;
                                                if(c3 == 0) {
                                                        CV_MAT_ELEM(*pDst, float, i, j) = 0.0f;
                                                }
                                        }
                                }
                        }
                }
        }
}


void ThinSubiteration2(CvMat *pSrc, CvMat *pDst) {
        int rows = pSrc->rows;
        int cols = pSrc->cols;
        cvCopy(pSrc, pDst);
        for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                        if ( CV_MAT_ELEM(*pSrc, float, i, j) == 1.0f) {
                                /// get 8 neighbors
                                /// calculate C(p)
                                int neighbor0 = (int) CV_MAT_ELEM(*pSrc, float, i-1, j-1);
                                int neighbor1 = (int) CV_MAT_ELEM(*pSrc, float, i-1, j);
                                int neighbor2 = (int) CV_MAT_ELEM(*pSrc, float, i-1, j+1);
                                int neighbor3 = (int) CV_MAT_ELEM(*pSrc, float, i, j+1);
                                int neighbor4 = (int) CV_MAT_ELEM(*pSrc, float, i+1, j+1);
                                int neighbor5 = (int) CV_MAT_ELEM(*pSrc, float, i+1, j);
                                int neighbor6 = (int) CV_MAT_ELEM(*pSrc, float, i+1, j-1);
                                int neighbor7 = (int) CV_MAT_ELEM(*pSrc, float, i, j-1);
                                int C = int(~neighbor1 & ( neighbor2 | neighbor3)) +
                                        int(~neighbor3 & ( neighbor4 | neighbor5)) +
                                        int(~neighbor5 & ( neighbor6 | neighbor7)) +
                                        int(~neighbor7 & ( neighbor0 | neighbor1));
                                if(C == 1) {
                                        /// calculate N
                                        int N1 = int(neighbor0 | neighbor1) +
                                                int(neighbor2 | neighbor3) +
                                                int(neighbor4 | neighbor5) +
                                                int(neighbor6 | neighbor7);
                                        int N2 = int(neighbor1 | neighbor2) +
                                                int(neighbor3 | neighbor4) +
                                                int(neighbor5 | neighbor6) +
                                                int(neighbor7 | neighbor0);
                                        int N = min(N1,N2);
                                        if((N == 2) || (N == 3)) {
                                                int E = (neighbor5 | neighbor6 | ~neighbor0) & neighbor7;
                                                if(E == 0) {
                                                        CV_MAT_ELEM(*pDst, float, i, j) = 0.0f;
                                                }
                                        }
                                }
                        }
                }
        }
}






void Canny2( InputArray _src, Mat dx, Mat dy, OutputArray _dst,
                double low_thresh, double high_thresh,
                int aperture_size, bool L2gradient )
{
    Mat src = _src.getMat();
    CV_Assert( src.depth() == CV_8U );

    _dst.create(src.size(), CV_8U);
    Mat dst = _dst.getMat();

    if (!L2gradient && (aperture_size & CV_CANNY_L2_GRADIENT) == CV_CANNY_L2_GRADIENT)
    {
        //backward compatibility
        aperture_size &= ~CV_CANNY_L2_GRADIENT;
        L2gradient = true;
    }

    if ((aperture_size & 1) == 0 || (aperture_size != -1 && (aperture_size < 3 || aperture_size > 7)))
        CV_Error(CV_StsBadFlag, "");

#ifdef HAVE_TEGRA_OPTIMIZATION
    if (tegra::canny(src, dst, low_thresh, high_thresh, aperture_size, L2gradient))
        return;
#endif

    const int cn = src.channels();
   // cv::Mat dx(src.rows, src.cols, CV_16SC(cn));
   // cv::Mat dy(src.rows, src.cols, CV_16SC(cn));

   // cv::Sobel(src, dx, CV_16S, 1, 0, aperture_size, 1, 0, cv::BORDER_REPLICATE);
   // cv::Sobel(src, dy, CV_16S, 0, 1, aperture_size, 1, 0, cv::BORDER_REPLICATE);

    if (low_thresh > high_thresh)
        std::swap(low_thresh, high_thresh);

    if (L2gradient)
    {
        low_thresh = std::min(32767.0, low_thresh);
        high_thresh = std::min(32767.0, high_thresh);

        if (low_thresh > 0) low_thresh *= low_thresh;
        if (high_thresh > 0) high_thresh *= high_thresh;
    }
    int low = cvFloor(low_thresh);
    int high = cvFloor(high_thresh);

    ptrdiff_t mapstep = src.cols + 2;
    cv::AutoBuffer<uchar> buffer((src.cols+2)*(src.rows+2) + cn * mapstep * 3 * sizeof(int));

    int* mag_buf[3];
    mag_buf[0] = (int*)(uchar*)buffer;
    mag_buf[1] = mag_buf[0] + mapstep*cn;
    mag_buf[2] = mag_buf[1] + mapstep*cn;
    memset(mag_buf[0], 0, /* cn* */mapstep*sizeof(int));

    uchar* map = (uchar*)(mag_buf[2] + mapstep*cn);
    memset(map, 1, mapstep);
    memset(map + mapstep*(src.rows + 1), 1, mapstep);

    int maxsize = std::max(1 << 10, src.cols * src.rows / 10);
    std::vector<uchar*> stack(maxsize);
    uchar **stack_top = &stack[0];
    uchar **stack_bottom = &stack[0];

    /* sector numbers
       (Top-Left Origin)

        1   2   3
         *  *  *
          * * *
        0*******0
          * * *
         *  *  *
        3   2   1
    */



    // calculate magnitude and angle of gradient, perform non-maxima supression.
    // fill the map with one of the following values:
    //   0 - the pixel might belong to an edge
    //   1 - the pixel can not belong to an edge
    //   2 - the pixel does belong to an edge
    for (int i = 0; i <= src.rows; i++)
    {
        int* _norm = mag_buf[(i > 0) + 1] + 1;
        if (i < src.rows)
        {
            short* _dx = dx.ptr<short>(i);
            short* _dy = dy.ptr<short>(i);

            if (!L2gradient)
            {
                for (int j = 0; j < src.cols*cn; j++)
                    _norm[j] = abs(int(_dx[j])) +  abs(int(_dy[j]));
            }
            else
            {
                for (int j = 0; j < src.cols*cn; j++)
                    _norm[j] = int(_dx[j])*_dx[j] + int(_dy[j])*_dy[j];
            }

            if (cn > 1)
            {
                for(int j = 0, jn = 0; j < src.cols; ++j, jn += cn)
                {
                    int maxIdx = jn;
                    for(int k = 1; k < cn; ++k)
                        if(_norm[jn + k] > _norm[maxIdx]) maxIdx = jn + k;
                    _norm[j] = _norm[maxIdx];
                    _dx[j] = _dx[maxIdx];
                    _dy[j] = _dy[maxIdx];
                }
            }
            _norm[-1] = _norm[src.cols] = 0;
        }
        else
            memset(_norm-1, 0, /* cn* */mapstep*sizeof(int));

        // at the very beginning we do not have a complete ring
        // buffer of 3 magnitude rows for non-maxima suppression
        if (i == 0)
            continue;

        uchar* _map = map + mapstep*i + 1;
        _map[-1] = _map[src.cols] = 1;

        int* _mag = mag_buf[1] + 1; // take the central row
        ptrdiff_t magstep1 = mag_buf[2] - mag_buf[1];
        ptrdiff_t magstep2 = mag_buf[0] - mag_buf[1];

        const short* _x = dx.ptr<short>(i-1);
        const short* _y = dy.ptr<short>(i-1);

        if ((stack_top - stack_bottom) + src.cols > maxsize)
        {
            int sz = (int)(stack_top - stack_bottom);
            maxsize = maxsize * 3/2;
            stack.resize(maxsize);
            stack_bottom = &stack[0];
            stack_top = stack_bottom + sz;
        }

        int prev_flag = 0;
        for (int j = 0; j < src.cols; j++)
        {
            #define CANNY_SHIFT 15
            const int TG22 = (int)(0.4142135623730950488016887242097*(1<<CANNY_SHIFT) + 0.5);

            int m = _mag[j];

            if (m > low)
            {
                int xs = _x[j];
                int ys = _y[j];
                int x = abs(xs);
                int y = abs(ys) << CANNY_SHIFT;

                int tg22x = x * TG22;

                if (y < tg22x)
                {
                    if (m > _mag[j-1] && m >= _mag[j+1]) goto __ocv_canny_push;
                }
                else
                {
                    int tg67x = tg22x + (x << (CANNY_SHIFT+1));
                    if (y > tg67x)
                    {
                        if (m > _mag[j+magstep2] && m >= _mag[j+magstep1]) goto __ocv_canny_push;
                    }
                    else
                    {
                        int s = (xs ^ ys) < 0 ? -1 : 1;
                        if (m > _mag[j+magstep2-s] && m > _mag[j+magstep1+s]) goto __ocv_canny_push;
                    }
                }
            }
            prev_flag = 0;
            _map[j] = uchar(1);
            continue;
__ocv_canny_push:
            if (!prev_flag && m > high && _map[j-mapstep] != 2)
            {
                CANNY_PUSH(_map + j);
                prev_flag = 1;
            }
            else
                _map[j] = 0;
        }

        // scroll the ring buffer
        _mag = mag_buf[0];
        mag_buf[0] = mag_buf[1];
        mag_buf[1] = mag_buf[2];
        mag_buf[2] = _mag;
    }

    // now track the edges (hysteresis thresholding)
    while (stack_top > stack_bottom)
    {
        uchar* m;
        if ((stack_top - stack_bottom) + 8 > maxsize)
        {
            int sz = (int)(stack_top - stack_bottom);
            maxsize = maxsize * 3/2;
            stack.resize(maxsize);
            stack_bottom = &stack[0];
            stack_top = stack_bottom + sz;
        }

        CANNY_POP(m);

        if (!m[-1])         CANNY_PUSH(m - 1);
        if (!m[1])          CANNY_PUSH(m + 1);
        if (!m[-mapstep-1]) CANNY_PUSH(m - mapstep - 1);
        if (!m[-mapstep])   CANNY_PUSH(m - mapstep);
        if (!m[-mapstep+1]) CANNY_PUSH(m - mapstep + 1);
        if (!m[mapstep-1])  CANNY_PUSH(m + mapstep - 1);
        if (!m[mapstep])    CANNY_PUSH(m + mapstep);
        if (!m[mapstep+1])  CANNY_PUSH(m + mapstep + 1);
    }

    // the final pass, form the final image
    const uchar* pmap = map + mapstep + 1;
    uchar* pdst = dst.ptr();
    for (int i = 0; i < src.rows; i++, pmap += mapstep, pdst += dst.step)
    {
        for (int j = 0; j < src.cols; j++)
            pdst[j] = (uchar)-(pmap[j] >> 1);
    }
}


void Canny3( InputArray _src, OutputArray _dst,
                double low_thresh, double high_thresh,
                int aperture_size, bool L2gradient )
{
    Mat src = _src.getMat();
    CV_Assert( src.depth() == CV_8U );

    _dst.create(src.size(), CV_8U);
    Mat dst = _dst.getMat();

    if (!L2gradient && (aperture_size & CV_CANNY_L2_GRADIENT) == CV_CANNY_L2_GRADIENT)
    {
        //backward compatibility
        aperture_size &= ~CV_CANNY_L2_GRADIENT;
        L2gradient = true;
    }

    if ((aperture_size & 1) == 0 || (aperture_size != -1 && (aperture_size < 3 || aperture_size > 7)))
        CV_Error(CV_StsBadFlag, "");

#ifdef HAVE_TEGRA_OPTIMIZATION
    if (tegra::canny(src, dst, low_thresh, high_thresh, aperture_size, L2gradient))
        return;
#endif

    const int cn = src.channels();
    cv::Mat dx(src.rows, src.cols, CV_16SC(cn));
    cv::Mat dy(src.rows, src.cols, CV_16SC(cn));

    cv::Sobel(src, dx, CV_16S, 1, 0, aperture_size, 1, 0, cv::BORDER_REPLICATE);
    cv::Sobel(src, dy, CV_16S, 0, 1, aperture_size, 1, 0, cv::BORDER_REPLICATE);

    if (low_thresh > high_thresh)
        std::swap(low_thresh, high_thresh);

    if (L2gradient)
    {
        low_thresh = std::min(32767.0, low_thresh);
        high_thresh = std::min(32767.0, high_thresh);

        if (low_thresh > 0) low_thresh *= low_thresh;
        if (high_thresh > 0) high_thresh *= high_thresh;
    }
    int low = cvFloor(low_thresh);
    int high = cvFloor(high_thresh);

    ptrdiff_t mapstep = src.cols + 2;
    cv::AutoBuffer<uchar> buffer((src.cols+2)*(src.rows+2) + cn * mapstep * 3 * sizeof(int));

    int* mag_buf[3];
    mag_buf[0] = (int*)(uchar*)buffer;
    mag_buf[1] = mag_buf[0] + mapstep*cn;
    mag_buf[2] = mag_buf[1] + mapstep*cn;
    memset(mag_buf[0], 0, /* cn* */mapstep*sizeof(int));

    uchar* map = (uchar*)(mag_buf[2] + mapstep*cn);
    memset(map, 1, mapstep);
    memset(map + mapstep*(src.rows + 1), 1, mapstep);

    int maxsize = std::max(1 << 10, src.cols * src.rows / 10);
    std::vector<uchar*> stack(maxsize);
    uchar **stack_top = &stack[0];
    uchar **stack_bottom = &stack[0];

    /* sector numbers
       (Top-Left Origin)

        1   2   3
         *  *  *
          * * *
        0*******0
          * * *
         *  *  *
        3   2   1
    */

    #define CANNY_PUSH(d)    *(d) = uchar(2), *stack_top++ = (d)
    #define CANNY_POP(d)     (d) = *--stack_top

    // calculate magnitude and angle of gradient, perform non-maxima supression.
    // fill the map with one of the following values:
    //   0 - the pixel might belong to an edge
    //   1 - the pixel can not belong to an edge
    //   2 - the pixel does belong to an edge
    for (int i = 0; i <= src.rows; i++)
    {
        int* _norm = mag_buf[(i > 0) + 1] + 1;
        if (i < src.rows)
        {
            short* _dx = dx.ptr<short>(i);
            short* _dy = dy.ptr<short>(i);

            if (!L2gradient)
            {
                for (int j = 0; j < src.cols*cn; j++)
                    _norm[j] = abs(int(_dx[j])) +  abs(int(_dy[j]));
            }
            else
            {
                for (int j = 0; j < src.cols*cn; j++)
                    _norm[j] = int(_dx[j])*_dx[j] + int(_dy[j])*_dy[j];
            }

            if (cn > 1)
            {
                for(int j = 0, jn = 0; j < src.cols; ++j, jn += cn)
                {
                    int maxIdx = jn;
                    for(int k = 1; k < cn; ++k)
                        if(_norm[jn + k] > _norm[maxIdx]) maxIdx = jn + k;
                    _norm[j] = _norm[maxIdx];
                    _dx[j] = _dx[maxIdx];
                    _dy[j] = _dy[maxIdx];
                }
            }
            _norm[-1] = _norm[src.cols] = 0;
        }
        else
            memset(_norm-1, 0, /* cn* */mapstep*sizeof(int));

        // at the very beginning we do not have a complete ring
        // buffer of 3 magnitude rows for non-maxima suppression
        if (i == 0)
            continue;

        uchar* _map = map + mapstep*i + 1;
        _map[-1] = _map[src.cols] = 1;

        int* _mag = mag_buf[1] + 1; // take the central row
        ptrdiff_t magstep1 = mag_buf[2] - mag_buf[1];
        ptrdiff_t magstep2 = mag_buf[0] - mag_buf[1];

        const short* _x = dx.ptr<short>(i-1);
        const short* _y = dy.ptr<short>(i-1);

        if ((stack_top - stack_bottom) + src.cols > maxsize)
        {
            int sz = (int)(stack_top - stack_bottom);
            maxsize = maxsize * 3/2;
            stack.resize(maxsize);
            stack_bottom = &stack[0];
            stack_top = stack_bottom + sz;
        }

        int prev_flag = 0;
        for (int j = 0; j < src.cols; j++)
        {
            #define CANNY_SHIFT 15
            const int TG22 = (int)(0.4142135623730950488016887242097*(1<<CANNY_SHIFT) + 0.5);

            int m = _mag[j];

            if (m > low)
            {
                int xs = _x[j];
                int ys = _y[j];
                int x = abs(xs);
                int y = abs(ys) << CANNY_SHIFT;

                int tg22x = x * TG22;

                if (y < tg22x)
                {
                    if (m > _mag[j-1] && m >= _mag[j+1]) goto __ocv_canny_push;
                }
                else
                {
                    int tg67x = tg22x + (x << (CANNY_SHIFT+1));
                    if (y > tg67x)
                    {
                        if (m > _mag[j+magstep2] && m >= _mag[j+magstep1]) goto __ocv_canny_push;
                    }
                    else
                    {
                        int s = (xs ^ ys) < 0 ? -1 : 1;
                        if (m > _mag[j+magstep2-s] && m > _mag[j+magstep1+s]) goto __ocv_canny_push;
                    }
                }
            }
            prev_flag = 0;
            _map[j] = uchar(1);
            continue;
__ocv_canny_push:
            if (!prev_flag && m > high && _map[j-mapstep] != 2)
            {
                CANNY_PUSH(_map + j);
                prev_flag = 1;
            }
            else
                _map[j] = 0;
        }

        // scroll the ring buffer
        _mag = mag_buf[0];
        mag_buf[0] = mag_buf[1];
        mag_buf[1] = mag_buf[2];
        mag_buf[2] = _mag;
    }

    // now track the edges (hysteresis thresholding)
    while (stack_top > stack_bottom)
    {
        uchar* m;
        if ((stack_top - stack_bottom) + 8 > maxsize)
        {
            int sz = (int)(stack_top - stack_bottom);
            maxsize = maxsize * 3/2;
            stack.resize(maxsize);
            stack_bottom = &stack[0];
            stack_top = stack_bottom + sz;
        }

        CANNY_POP(m);

        if (!m[-1])         CANNY_PUSH(m - 1);
        if (!m[1])          CANNY_PUSH(m + 1);
        if (!m[-mapstep-1]) CANNY_PUSH(m - mapstep - 1);
        if (!m[-mapstep])   CANNY_PUSH(m - mapstep);
        if (!m[-mapstep+1]) CANNY_PUSH(m - mapstep + 1);
        if (!m[mapstep-1])  CANNY_PUSH(m + mapstep - 1);
        if (!m[mapstep])    CANNY_PUSH(m + mapstep);
        if (!m[mapstep+1])  CANNY_PUSH(m + mapstep + 1);
    }

    // the final pass, form the final image
    const uchar* pmap = map + mapstep + 1;
    uchar* pdst = dst.ptr();
    for (int i = 0; i < src.rows; i++, pmap += mapstep, pdst += dst.step)
    {
        for (int j = 0; j < src.cols; j++)
            pdst[j] = (uchar)-(pmap[j] >> 1);
    }
}

void MeanFilter(
		InputArray 						_src,
		OutputArray						_dst,
		int								size)
{
	Mat src = _src.getMat();
	src.convertTo(src,CV_32F);
	blur(src, _dst, Size(size, size));
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
	if (type==-5){
			kernel = (Mat_<float>(5,5) << 1,1,1,1,1 , 1,1,1,1,1 , 1,1,1,1,1 , 1,1,1,1,1 , 1,1,1,1,1);
			point = Point(-1,-1);
	}


	else if (type==0){
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





		else if (type==72){
			kernel = (Mat_<float>(11,7) <<  1,1,.0,0,0,0,0 ,
											.9,1,.1,0,0,0,0 ,
											.8,1,.2,0,0,0,0 ,
											.7,1,.3,0,0,0,0 ,
											.6,1,.4,0,0,0,0 ,
											.5,1,.5,0,0,0,0 ,
											.4,1,.6,0,0,0,0 ,
											.3,1,.7,0,0,0,0 ,
											.2,1,.8,0,0,0,0 ,
											.1,1,.9,0,0,0,0 ,
											.0,1,1,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==73){
			kernel = (Mat_<float>(11,7) <<  0,0,0,0,1,1,0 ,
											0,0,0,0,.9,1,.1 ,
											0,0,0,0,.8,1,.2 ,
											0,0,0,0,.7,1,.3 ,
											0,0,0,0,.6,1,.4 ,
											0,0,0,0,.5,1,.5 ,
											0,0,0,0,.4,1,.6 ,
											0,0,0,0,.3,1,.7 ,
											0,0,0,0,.2,1,.8 ,
											0,0,0,0,.1,1,.9 ,
											0,0,0,0,0,1,1);
			point = Point(-1,-1);
		} else if (type==74){
			kernel = (Mat_<float>(7,11) <<  .0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1 ,
											1,1,1,1,1,1,1,1,1,1,1 ,
											1,.9,.8,.7,.6,.5,.4,.3,.2,.1,.0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==75){
			kernel = (Mat_<float>(7,11) <<  0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											.0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1 ,
											1,1,1,1,1,1,1,1,1,1,1 ,
											1,.9,.8,.7,.6,.5,.4,.3,.2,.1,.0 );
			point = Point(-1,-1);
		}



		else if (type==76){
			kernel = (Mat_<float>(11,7) <<  .0,1,1,0,0,0,0 ,
											.1,1,.9,0,0,0,0 ,
											.2,1,.8,0,0,0,0 ,
											.3,1,.7,0,0,0,0 ,
											.4,1,.6,0,0,0,0 ,
											.5,1,.5,0,0,0,0 ,
											.6,1,.4,0,0,0,0 ,
											.7,1,.3,0,0,0,0 ,
											.8,1,.2,0,0,0,0 ,
											.9,1,.1,0,0,0,0 ,
											1,1,.1,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==77){
			kernel = (Mat_<float>(11,7) <<  0,0,0,0,0,1,1 ,
											0,0,0,0,.1,1,.9 ,
											0,0,0,0,.2,1,.8 ,
											0,0,0,0,.3,1,.7 ,
											0,0,0,0,.4,1,.6 ,
											0,0,0,0,.5,1,.5 ,
											0,0,0,0,.6,1,.4 ,
											0,0,0,0,.7,1,.3 ,
											0,0,0,0,.8,1,.2 ,
											0,0,0,0,.9,1,.1 ,
											0,0,0,0,1,1,0);
			point = Point(-1,-1);
		} else if (type==78){
			kernel = (Mat_<float>(7,11) <<  1,.9,.8,.7,.6,.5,.4,.3,.2,.1,.0 ,
											1,1,1,1,1,1,1,1,1,1,1 ,
											.0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==79){
			kernel = (Mat_<float>(7,11) <<  0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											0,0,0,0,0,0,0,0,0,0,0 ,
											1,.9,.8,.7,.6,.5,.4,.3,.2,.1,.0 ,
											1,1,1,1,1,1,1,1,1,1,1 ,
											.0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1);
			point = Point(-1,-1);
		}




		else if (type==80){
			kernel = (Mat_<float>(6,7) <<  1,1,.0,0,0,0,0 ,
											.8,1,.2,0,0,0,0 ,
											.6,1,.4,0,0,0,0 ,
											.4,1,.6,0,0,0,0 ,
											.2,1,.8,0,0,0,0 ,
											.0,1,1,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==81){
			kernel = (Mat_<float>(6,7) <<  0,0,0,0,1,1,0 ,
											0,0,0,0,.8,1,.2 ,
											0,0,0,0,.6,1,.4 ,
											0,0,0,0,.4,1,.6 ,
											0,0,0,0,.2,1,.8 ,
											0,0,0,0,0,1,1);
			point = Point(-1,-1);
		} else if (type==82){
			kernel = (Mat_<float>(7,6) <<  .0,.2,.4,.6,.8,1 ,
											1,1,1,1,1,1 ,
											1,.8,.6,.4,.2,.0 ,
											0,0,0,0,0,0 ,
											0,0,0,0,0,0 ,
											0,0,0,0,0,0 ,
											0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==83){
			kernel = (Mat_<float>(7,6) <<  0,0,0,0,0,0,
											0,0,0,0,0,0,
											0,0,0,0,0,0,
											0,0,0,0,0,0,
											.0,.2,.4,.6,.8,1 ,
											1,1,1,1,1,1 ,
											1,.8,.6,.4,.2,.0 );
			point = Point(-1,-1);
		}



		else if (type==84){
			kernel = (Mat_<float>(6,7) <<  .0,1,1,0,0,0,0 ,
											.2,1,.8,0,0,0,0 ,
											.4,1,.6,0,0,0,0 ,
											.6,1,.4,0,0,0,0 ,
											.8,1,.2,0,0,0,0 ,
											1,1,.1,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==85){
			kernel = (Mat_<float>(6,7) <<  0,0,0,0,0,1,1 ,
											0,0,0,0,.2,1,.8 ,
											0,0,0,0,.4,1,.6 ,
											0,0,0,0,.6,1,.4 ,
											0,0,0,0,.8,1,.2 ,
											0,0,0,0,1,1,0);
			point = Point(-1,-1);
		} else if (type==86){
			kernel = (Mat_<float>(7,6) <<  1,.8,.6,.4,.2,.0 ,
											1,1,1,1,1,1,
											.0,.2,.4,.6,.8,1 ,
											0,0,0,0,0,0,
											0,0,0,0,0,0,
											0,0,0,0,0,0,
											0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==87){
			kernel = (Mat_<float>(7,6) <<  0,0,0,0,0,0,
											0,0,0,0,0,0,
											0,0,0,0,0,0,
											0,0,0,0,0,0,
											1,.8,.6,.4,.2,.0 ,
											1,1,1,1,1,1,
											.0,.2,.4,.6,.8,1);
			point = Point(-1,-1);
		}


		else if (type==88){
			kernel = (Mat_<float>(5,1) <<  1,
											1,
											1,
											1,
											1);
			point = Point(-1,-1);
		} else if (type==89){
			kernel = (Mat_<float>(1,5) <<  1,1,1,1,1);
			point = Point(-1,-1);
		} else if (type==90){
			kernel = (Mat_<float>(7,1) <<  1,
											1,
											1,
											1,
											1,
											1,
											1);
			point = Point(-1,-1);
		} else if (type==91){
			kernel = (Mat_<float>(1,7) <<  1,1,1,1,1,1,1);
			point = Point(-1,-1);
		} else if (type==92){
			kernel = (Mat_<float>(5,5) <<  1,0,0,0,0,
											0,1,0,0,0,
											0,0,1,0,0,
											0,0,0,1,0,
											0,0,0,0,1);
			point = Point(-1,-1);
		} else if (type==93){
			kernel = (Mat_<float>(5,5) <<  0,0,0,0,1,
											0,0,0,1,0,
											0,0,1,0,0,
											0,1,0,0,0,
											1,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==94){
			kernel = (Mat_<float>(5,3) <<   0,0,1,
											0,.5,.5,
											0,1,0,
											.5,.5,0,
											1,0,0);
			point = Point(-1,-1);
		} else if (type==95){
			kernel = (Mat_<float>(3,5) <<  1,.5,0,0,0,
											0,.5,1,.5,0,
											0,0,0,.5,1);
			point = Point(-1,-1);
		} else if (type==96){
			kernel = (Mat_<float>(5,3) <<   1,0,0,
											.5,.5,0,
											0,1,0,
											.5,.5,0,
											0,0,1);
			point = Point(-1,-1);
		} else if (type==97){
			kernel = (Mat_<float>(3,5) <<  0,0,0,.5,1,
											0,.5,1,.5,0,
											1,.5,0,0,0);
			point = Point(-1,-1);
		}

		else if (type==98){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,.5,.5,.5,.5,.5 , 0,0,.5,1,1,1,1 , 0,0,.5,1,.5,.5,.5 , 0,0,.5,1,.5,0,0 , 0,0,.5,1,.5,0,0);
			point = Point(-1,-1);
		} else if (type==99){
			kernel = (Mat_<float>(7,7) << 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0 , 0,0,.5,.5,.5,.5,.5 , 1,1,1,1,.5,0,0 , .5,.5,.5,1,.5,0,0 , 0,0,.5,1,.5,0,0 , 0,0,.5,1,.5,0,0);
			point = Point(-1,-1);
		} else if (type==100){
			kernel = (Mat_<float>(7,7) << 0,0,.5,1,.5,0,0 , 0,0,.5,1,.5,0,0 , 0,0,.5,1,.5,.5,.5 , 0,0,.5,1,1,1,1 , 0,0,.5,.5,.5,.5,.5 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
			point = Point(-1,-1);
		} else if (type==101){
			kernel = (Mat_<float>(7,7) << 0,0,.5,1,.5,0,0 , 0,0,.5,1,.5,0,0 , .5,.5,.5,1,.5,0,0 , 1,1,1,1,.5,0,0 , .5,.5,.5,.5,.5,0,0 , 0,0,0,0,0,0,0 , 0,0,0,0,0,0,0);
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
	double varth=25.0;
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
	} else if (type == 45) {
		kernel[0] = kernels(72,point[0]);
		kernel[1] = kernels(73,point[1]);
	} else if (type == 46) {
		kernel[0] = kernels(74,point[0]);
		kernel[1] = kernels(75,point[1]);
	} else if (type == 47) {
		kernel[0] = kernels(76,point[0]);
		kernel[1] = kernels(77,point[1]);
	} else if (type == 48) {
		kernel[0] = kernels(78,point[0]);
		kernel[1] = kernels(79,point[1]);
	} else if (type == 49) {
		kernel[0] = kernels(80,point[0]);
		kernel[1] = kernels(81,point[1]);
	} else if (type == 50) {
		kernel[0] = kernels(82,point[0]);
		kernel[1] = kernels(83,point[1]);
	} else if (type == 51) {
		kernel[0] = kernels(84,point[0]);
		kernel[1] = kernels(85,point[1]);
	} else if (type == 52) {
		kernel[0] = kernels(86,point[0]);
		kernel[1] = kernels(87,point[1]);
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


void HeteroDetector(
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
	double varthupper=200.0;
	double varthlower=36.0;
	int meanth=0;

	__src.convertTo(src,CV_32F);
	if(type == 53) {
		kernel[0] = kernels(88,point[0]);
		kernel[1] = kernels(89,point[1]);
	} else if (type == 54) {
		kernel[0] = kernels(90,point[0]);
		kernel[1] = kernels(91,point[1]);
	} else if (type == 55) {
		kernel[0] = kernels(92,point[0]);
		kernel[1] = kernels(93,point[1]);
	} else if (type == 56) {
		kernel[0] = kernels(94,point[0]);
		kernel[1] = kernels(95,point[1]);
	} else if (type == 57) {
		kernel[0] = kernels(96,point[0]);
		kernel[1] = kernels(97,point[1]);
	}

	for (int i=0; i<nPart; i++) {
		MeanMap32bit(src,mean[i],kernel[i],point[i]);
		VarianceMap32bit(src,var[i],kernel[i],point[i]);
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


		Mat temp1,temp2,varmean1,varmean2;
		threshold(var[0],temp1,varthlower,1.0,THRESH_BINARY_INV);


		MeanMap32bit(var[1],varmean1,kernel[0],point[0]);
		//threshold(var[1],temp2,varth,1.0,THRESH_BINARY);
		threshold(varmean1,temp2,varthupper,1.0,THRESH_BINARY);

//		namedWindow( "z", CV_WINDOW_AUTOSIZE );
//		imshow( "z", temp1);
//		namedWindow( "y", CV_WINDOW_AUTOSIZE );
//		imshow( "y", temp2);
//		waitKey(0);
//

		multiply(temp1,temp2,thr[0]);

		threshold(var[1],temp1,varthlower,1.0,THRESH_BINARY_INV);
		MeanMap32bit(var[0],varmean2,kernel[1],point[1]);
		threshold(varmean2,temp2,varthupper,1.0,THRESH_BINARY);
		//threshold(var[0],temp2,varth,1.0,THRESH_BINARY);
		multiply(temp1,temp2,thr[1]);


		absdiff(mean[0], mean[1], meanDiff[0]);
		absdiff(mean[0], mean[1], meanDiff[1]);

		meanDiff[0] = meanDiff[0].mul(thr[0]);
		meanDiff[1] = meanDiff[1].mul(thr[1]);


		meanDiff[0] += meanDiff[1];
		meanDiff[0].convertTo(_dst,CV_8UC1);
	}
}



void RGBThresholdMinMaxSelector(
		Vector<int>						resultpoints,
		int								tolerance,
		int								type,
		int&							rb,
		int&							ru,
		int&							gb,
		int&							gu,
		int&							bb,
		int&							bu)
{
	if (type == 0) {
		rb = resultpoints[0] - tolerance; if(rb<0) rb=0; if(rb>255) rb=255;
		ru = resultpoints[0] + tolerance; if(ru<0) ru=0; if(ru>255) ru=255;
		gb = resultpoints[1] - tolerance; if(gb<0) gb=0; if(gb>255) gb=255;
		gu = resultpoints[1] + tolerance; if(gu<0) gu=0; if(gu>255) gu=255;
		bb = resultpoints[2] - tolerance; if(bb<0) bb=0; if(bb>255) bb=255;
		bu = resultpoints[2] + tolerance; if(bu<0) bu=0; if(bu>255) bu=255;
	} else if (type == 1) {
		rb = resultpoints[3] - tolerance; if(rb<0) rb=0; if(rb>255) rb=255;
		ru = resultpoints[6] + tolerance; if(ru<0) ru=0; if(ru>255) ru=255;
		gb = resultpoints[4] - tolerance; if(gb<0) gb=0; if(gb>255) gb=255;
		gu = resultpoints[7] + tolerance; if(gu<0) gu=0; if(gu>255) gu=255;
		bb = resultpoints[5] - tolerance; if(bb<0) bb=0; if(bb>255) bb=255;
		bu = resultpoints[8] + tolerance; if(bu<0) bu=0; if(bu>255) bu=255;
	} else if (type == 2) {
		rb = resultpoints[0] - resultpoints[9]*2; if(rb<0) rb=0; if(rb>255) rb=255;
		ru = resultpoints[0] + resultpoints[9]*2; if(ru<0) ru=0; if(ru>255) ru=255;
		gb = resultpoints[1] - resultpoints[10]*2; if(gb<0) gb=0; if(gb>255) gb=255;
		gu = resultpoints[1] + resultpoints[10]*2; if(gu<0) gu=0; if(gu>255) gu=255;
		bb = resultpoints[2] - resultpoints[11]*2; if(bb<0) bb=0; if(bb>255) bb=255;
		bu = resultpoints[2] + resultpoints[11]*2; if(bu<0) bu=0; if(bu>255) bu=255;
	} else if (type == 3) {
		rb = resultpoints[3] - resultpoints[9]/2; if(rb<0) rb=0; if(rb>255) rb=255;
		ru = resultpoints[6] + resultpoints[9]/2; if(ru<0) ru=0; if(ru>255) ru=255;
		gb = resultpoints[4] - resultpoints[10]/2; if(gb<0) gb=0; if(gb>255) gb=255;
		gu = resultpoints[7] + resultpoints[10]/2; if(gu<0) gu=0; if(gu>255) gu=255;
		bb = resultpoints[5] - resultpoints[11]/2; if(bb<0) bb=0; if(bb>255) bb=255;
		bu = resultpoints[8] + resultpoints[11]/2; if(bu<0) bu=0; if(bu>255) bu=255;
	}
}

Mat RGBThreshold(
		const Mat						&src,
		Vector<int>						resultpoints,
		int								tolerance,
		int								type)
{
	Mat srcRGB[3],th[6],th_;
	int rb, ru, gb, gu, bb, bu;
	RGBThresholdMinMaxSelector(resultpoints,tolerance,type,rb,ru,gb,gu,bb,bu);
	std::cout<<": "<<rb<<","<<ru<<","<<gb<<","<<gu<<","<<bb<<","<<bu<<","<<std::endl;
	split(src,srcRGB);
	if (rb==0) th[0] = Mat::zeros(srcRGB[0].size(),CV_8UC1)+255;
	else threshold(srcRGB[0],th[0],rb,255,THRESH_BINARY);
	threshold(srcRGB[0],th[1],ru,255,THRESH_BINARY_INV);
	if (gb==0) th[2] = Mat::zeros(srcRGB[0].size(),CV_8UC1)+255;
	else threshold(srcRGB[1],th[2],gb,255,THRESH_BINARY);
	threshold(srcRGB[1],th[3],gu,255,THRESH_BINARY_INV);
	if (bb==0) th[4] = Mat::zeros(srcRGB[0].size(),CV_8UC1)+255;
	else threshold(srcRGB[2],th[4],bb,255,THRESH_BINARY);
	threshold(srcRGB[2],th[5],bu,255,THRESH_BINARY_INV);

//
//				namedWindow( "a", CV_WINDOW_AUTOSIZE );
//				imshow( "a", th[0]);//thrCrCb[0] );
//				namedWindow( "b", CV_WINDOW_AUTOSIZE );
//				imshow( "b", th[1]);//thrCrCb[0] );
//				namedWindow( "c", CV_WINDOW_AUTOSIZE );
//				imshow( "c", th[2]);//thrCrCb[0] );
//				namedWindow( "d", CV_WINDOW_AUTOSIZE );
//				imshow( "d", th[3]);//thrCrCb[0] );
//				namedWindow( "e", CV_WINDOW_AUTOSIZE );
//				imshow( "e", th[4]);//thrCrCb[0] );
//				namedWindow( "f", CV_WINDOW_AUTOSIZE );
//				imshow( "f", th[5]);//thrCrCb[0] );
//				waitKey(0);


	bitwise_and(th[0],th[1],th_);
	bitwise_and(th_,th[2],th_);
	bitwise_and(th_,th[3],th_);
	bitwise_and(th_,th[4],th_);
	bitwise_and(th_,th[5],th_);
	//merge(th,3,th_);
	return th_;

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

Mat RGBThresholdPointCC(
		Mat								thImage,
		Vector< Vector<int> >&			cornerpoints,
		Vector<int>						resultpoints,
		int								tolerance,
		int								type)
{
	Size size = thImage.size();
	Mat temp = Mat::zeros(size,CV_8UC1);
	size_t s = cornerpoints.size();
	vector < vector<Point2i> > blobs;

	int rb, ru, gb, gu, bb, bu;
	RGBThresholdMinMaxSelector(resultpoints,tolerance,type,rb,ru,gb,gu,bb,bu);
	Mat clone; thImage.copyTo(clone);
	FindBlobs(clone,blobs);
	size_t t = blobs.size();
	int flag = -1;

	for (size_t i=0; i<s; i++){
		if (cornerpoints[i][2] >= rb && cornerpoints[i][2] <= ru
				&& cornerpoints[i][3] >= gb && cornerpoints[i][3] <= gu
				&& cornerpoints[i][4] >= bb && cornerpoints[i][4] <= bu) {
			for (size_t j=0; j<t; j++){
				size_t u = blobs[j].size();
				for (size_t k=0; k<u; k++){
					if (blobs[j][k].x == cornerpoints[i][0] &&
						blobs[j][k].y == cornerpoints[i][1]){
						flag=j; break;
					}
				}
				if(flag!=-1) break;
			}
			if(flag!=-1) {
				size_t u = blobs[flag].size();
				for (size_t k=0; k<u; k++){
	//				blobs[flag][k].x == cornerpoints[i][0] &&
	//					blobs[flag][k].y == cornerpoints[i][1])
					temp.at<uchar>(blobs[flag][k].y,blobs[flag][k].x) = 255;
				}
				flag=-1;
			}
			//temp.at<uchar>(cornerpoints[i][1],cornerpoints[i][0]) = 255;
		}

	}
//	namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	imshow( "c", temp);//thrCrCb[0] );
//	waitKey(0);
	return temp;
}


Mat RGBThresholdPointCC2(
		Mat								thImage,
		Vector< Vector<int> >&			cornerpoints,
		Vector<int>						resultpoints,
		int								tolerance,
		int								type)
{
	Size size = thImage.size();
	Mat temp = Mat::zeros(size,CV_8UC1);
	size_t s = cornerpoints.size();
	vector < vector<Point2i> > blobs;
	int rb, ru, gb, gu, bb, bu;
	RGBThresholdMinMaxSelector(resultpoints,tolerance,type,rb,ru,gb,gu,bb,bu);
	Mat clone; thImage.copyTo(clone);
	FindBlobs(clone,blobs);
	size_t t = blobs.size();
	int flag = -1;
	int flagGMM = 0;
	//int Gmaxx=0,Gmaxy=0,Gminx=size.width,Gminy=size.height;
	vector< vector<int> > GlobalMinMax;

	for (size_t i=0; i<s; i++){
		if (cornerpoints[i][2] >= rb && cornerpoints[i][2] <= ru
				&& cornerpoints[i][3] >= gb && cornerpoints[i][3] <= gu
				&& cornerpoints[i][4] >= bb && cornerpoints[i][4] <= bu) {

			for (size_t j=0; j<t; j++){
				size_t u = blobs[j].size();

				int maxx=0,maxy=0,minx=size.width,miny=size.height;

				for (size_t k=0; k<u; k++){
					if(maxx<blobs[j][k].x)maxx = blobs[j][k].x;
					if(maxy<blobs[j][k].y)maxy = blobs[j][k].y;
					if(minx>blobs[j][k].x)minx = blobs[j][k].x;
					if(miny>blobs[j][k].y)miny = blobs[j][k].y;
				}

				if ((maxx-minx)>size.width/2) {
					vector<int> tempm;
					tempm.push_back(maxx);
					tempm.push_back(maxy);
					tempm.push_back(minx);
					tempm.push_back(miny);
					GlobalMinMax.push_back(tempm);
					continue;
				}
				if ((maxy-miny)>size.height/2) {
					vector<int> tempm;
					tempm.push_back(maxx);
					tempm.push_back(maxy);
					tempm.push_back(minx);
					tempm.push_back(miny);
					GlobalMinMax.push_back(tempm);
					continue;
				}
				int gmmSize = GlobalMinMax.size();
				if (gmmSize) {
					for (int z = 0; z < gmmSize; z++){
						if(maxx<GlobalMinMax[z][0] &&
							maxy<GlobalMinMax[z][1] &&
							minx>GlobalMinMax[z][2] &&
							miny>GlobalMinMax[z][3]){
							flagGMM=1;
						}
					}
					if(flagGMM) {flagGMM=0;continue;}
				}
				for (size_t k=0; k<u; k++){
					if (blobs[j][k].x == cornerpoints[i][0] &&
						blobs[j][k].y == cornerpoints[i][1]){
						flag=j; break;
					}
				}
				if(flag!=-1) break;
			}
			if(flag!=-1) {
				size_t u = blobs[flag].size();
				for (size_t k=0; k<u; k++){
	//				blobs[flag][k].x == cornerpoints[i][0] &&
	//					blobs[flag][k].y == cornerpoints[i][1])
					temp.at<uchar>(blobs[flag][k].y,blobs[flag][k].x) = 255;
				}
				flag=-1;
			}
			//temp.at<uchar>(cornerpoints[i][1],cornerpoints[i][0]) = 255;
		}

	}
//	namedWindow( "c", CV_WINDOW_AUTOSIZE );
//	imshow( "c", temp);//thrCrCb[0] );
//	waitKey(0);
	return temp;
}

Vector< Vector<int> > kmeansWrapper(
		Vector< Vector<int> >&			cornerpoints,
		int								K)
{
	int cornerpointsRow = cornerpoints.size();
	//if (cornerpointsRow==0) return ;
	int cornerpointsCol = cornerpoints[0].size();
	Mat cornerpointsMat (cornerpointsRow,cornerpointsCol-2,CV_32FC1);
	Mat minColors_ = Mat::zeros(K,cornerpointsCol-2,CV_32FC1)+255;
	Mat maxColors_ = Mat::zeros(K,cornerpointsCol-2,CV_32FC1);
	Mat sumColors_ = Mat::zeros(K,cornerpointsCol-2,CV_32FC1);
	Mat sqsumColors_ = Mat::zeros(K,cornerpointsCol-2,CV_32FC1);
	Mat stdColors_ = Mat::zeros(K,cornerpointsCol-2,CV_32FC1);
	Mat bestColors_ = Mat::zeros(K,cornerpointsCol-2,CV_32FC1);
	Mat counter = Mat::zeros(K,cornerpointsCol-2,CV_32SC1);
	Mat minColors;
	Mat maxColors;
	Mat bestColors;
	Mat stdColors;
	Mat clusters(cornerpointsRow,1,CV_32SC1);
	Vector< Vector<int> > returnpoints;
	for (int ii = 0; ii<cornerpointsRow; ii++){
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			cornerpointsMat.at<float>(ii,jj) = cornerpoints[ii][jj+2];
		}
	}
//	for (int ii = 0; ii<3; ii++){
//		for (int jj = 0; jj<3; jj++){
//			std::cout<<ii<<" "<<jj<<" "<<cornerpointsMat.at<float>(ii,jj)<<std::endl;
//		}
//	}

	kmeans(cornerpointsMat, K, clusters, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.1), 10, KMEANS_PP_CENTERS,bestColors_);
	//kmeans(cornerpointsMat, K, clusters, TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 10, 0.1), 10, KMEANS_RANDOM_CENTERS);
	//kmeans(cornerpointsMat, K, clusters, TermCriteria(TermCriteria::EPS, 5, 0.1), 5, KMEANS_RANDOM_CENTERS);

	for (int ii = 0; ii<cornerpointsRow; ii++){
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			long cl = clusters.at<long>(ii);
			float cb = cornerpointsMat.at<float>(ii,jj);
			if (minColors_.at<float>(cl,jj)>cb)minColors_.at<float>(cl,jj)=cb;
			if (maxColors_.at<float>(cl,jj)<cb)maxColors_.at<float>(cl,jj)=cb;
			sumColors_.at<float>(cl,jj)+=cb;
			sqsumColors_.at<float>(cl,jj)+=cb*cb;
			counter.at<long>(cl,jj)++;
		}
		//for (int jj = 0; jj<3; jj++){
		//std::cout<<ii<<" "<<clusters.at<long>(ii)<std::<endl;
		//}
	}
	for (int ii = 0; ii<K; ii++){
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			//std::cout<<ii<<" "<<jj<<" "<<bestColors_.at<float>(ii,jj)<<std::endl;
			sumColors_.at<float>(ii,jj) = sumColors_.at<float>(ii,jj)/counter.at<long>(ii,jj);
			sqsumColors_.at<float>(ii,jj) = sqsumColors_.at<float>(ii,jj)/counter.at<long>(ii,jj);
			stdColors_.at<float>(ii,jj) = sqrt(sqsumColors_.at<float>(ii,jj)-sumColors_.at<float>(ii,jj)*sumColors_.at<float>(ii,jj));
			//std::cout<<ii<<" "<<jj<<" "<<counter.at<long>(ii,jj)<<std::endl;
		}
	}

	bestColors_.convertTo(bestColors,CV_8UC1);
	minColors_.convertTo(minColors,CV_8UC1);
	maxColors_.convertTo(maxColors,CV_8UC1);
	stdColors_.convertTo(stdColors,CV_8UC1);
	for (int ii = 0; ii<K; ii++){
		Vector<int> temp;
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			temp.push_back((int)bestColors.at<uchar>(ii,jj));
			std::cout<<ii<<" "<<jj<<" "<<(int)bestColors.at<uchar>(ii,jj)<<std::endl;
		}
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			temp.push_back((int)minColors.at<uchar>(ii,jj));
		}
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			temp.push_back((int)maxColors.at<uchar>(ii,jj));
		}
		for (int jj = 0; jj<cornerpointsCol-2; jj++){
			temp.push_back((int)stdColors.at<uchar>(ii,jj));
		}
		returnpoints.push_back(temp);
	}
	return returnpoints;
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
	diff = (var3_-var5_);
	threshold(diff,diff,0,0,THRESH_TOZERO);
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

void MultiscaleVarianceMap(
		InputArray 						_src,
		OutputArray						_dst,
		double							ratio)
{
	Mat src = _src.getMat();
	Size size = src.size();
	Mat var3, var5, diff;
	double minW = 50;
	double minH = 50;
	double curW = size.width;
	double curH = size.height;
	double oriW = size.width;
	double oriH = size.height;
	VarianceFilter(_src,var3,3);

	for(;curW>minW,curH>minH;curW/=ratio,curH/=ratio) {
		Mat temp,varR,temp2;
		resize(src,temp,Size(curW,curH),0,0,INTER_NEAREST);
		VarianceFilter(temp,varR,3);
		resize(varR,temp2,Size(oriW,oriH),0,0,INTER_NEAREST);
		max(var3,temp2,var3);
	}

	double mn,mx;
	minMaxIdx(var3,&mn,&mx);

	var3 = (var3-mn)/(mx-mn)*255;

	var3.convertTo(_dst,CV_8UC1);
	minMaxIdx(_dst,&mn,&mx);
	std::cout<<mn<<","<<mx<<std::endl;


}




}



