/*
 * LineTracker.cpp
 *
 *  Created on: 2013. 12. 17.
 *      Author: Nicatio
 */


#include "LineTracker.h"

namespace cvNica {

int order5x5[34] = {-2,-2,
					-2,-1,
					-2, 0,
					-2, 1,
					-2, 2,
					-1, 2,
					 0, 2,
					 1, 2,
					 2, 2,
					 2, 1,
					 2, 0,
					 2,-1,
					 2,-2,
					 1,-2,
					 0,-2,
					-1,-2,
					-2,-2};


void LineTracker(
		InputArray 						_src,
		int								startX,
		int								startY)
{
	Mat src = _src.getMat();
	int curX=startX;
	int curY=startY;
	float curA=-90;
	int nOut;
	for(;;) {
		if (src.at<uchar>(curY,curX)==255){
			src.at<uchar>(curY,curX)=127;
			nOut=0;
			for (int i=0; i<32; i+=2){
				if ((src.at<uchar>(curY+order5x5[i],curX+order5x5[i+1])>127)
						!= (src.at<uchar>(curY+order5x5[i+2],curX+order5x5[i+3])>127)){
					nOut++;
				}
			}
			nOut/=2;

			if ((nOut <= 2 && curA<0) || (nOut == 1 && curA>=0)) {
				if (src.at<uchar>(curY-1,curX)==255){
					curY--;
					curA=0;
				} else if (src.at<uchar>(curY,curX+1)==255){
					curX++;
					curA=90;
				} else if (src.at<uchar>(curY+1,curX)==255){
					curY++;
					curA=180;
				} else if (src.at<uchar>(curY,curX-1)==255){
					curX--;
					curA=270;
				} else if (src.at<uchar>(curY-1,curX+1)==255){
					curX++;
					curY--;
					curA=45;
				} else if (src.at<uchar>(curY+1,curX+1)==255){
					curX++;
					curY++;
					curA=135;
				} else if (src.at<uchar>(curY+1,curX-1)==255){
					curX--;
					curY++;
					curA=225;
				} else if (src.at<uchar>(curY-1,curX-1)==255){
					curX--;
					curY--;
					curA=315;
				}

			} else if (nOut >= 1){
				//int tempX = curX;
				//int tempY = curY;
				if (curA==0) {
					if (src.at<uchar>(curY-1,curX)==255){
						curY--;
						curA=0;
					} else if (src.at<uchar>(curY-1,curX+1)==255){
						curX++;
						curY--;
						curA=45;
					} else if (src.at<uchar>(curY-1,curX-1)==255){
						curX--;
						curY--;
						curA=315;
					}
				} else if (curA==45) {
					if (src.at<uchar>(curY-1,curX+1)==255){
						curX++;
						curY--;
						curA=45;
					} else if (src.at<uchar>(curY-1,curX)==255){
						curY--;
						curA=0;
					} else if (src.at<uchar>(curY,curX+1)==255){
						curX++;
						curA=90;
					}
				} else if (curA==90) {
					if (src.at<uchar>(curY,curX+1)==255){
						curX++;
						curA=90;
					} else if (src.at<uchar>(curY-1,curX+1)==255){
						curX++;
						curY--;
						curA=45;
					} else if (src.at<uchar>(curY+1,curX+1)==255){
						curX++;
						curY++;
						curA=135;
					}
				} else if (curA==135) {
					if (src.at<uchar>(curY+1,curX+1)==255){
						curX++;
						curY++;
						curA=135;
					} else if (src.at<uchar>(curY,curX+1)==255){
						curX++;
						curA=90;
					} else if (src.at<uchar>(curY+1,curX)==255){
						curY++;
						curA=180;
					}
				} else if (curA==180) {
					if (src.at<uchar>(curY+1,curX)==255){
						curY++;
						curA=180;
					} else if (src.at<uchar>(curY+1,curX+1)==255){
						curX++;
						curY++;
						curA=135;
					} else if (src.at<uchar>(curY+1,curX-1)==255){
						curX--;
						curY++;
						curA=225;
					}
				} else if (curA==225) {
					if (src.at<uchar>(curY+1,curX-1)==255){
						curX--;
						curY++;
						curA=225;
					} else if (src.at<uchar>(curY+1,curX)==255){
						curY++;
						curA=180;
					} else if (src.at<uchar>(curY,curX-1)==255){
						curX--;
						curA=270;
					}
				} else if (curA==270) {
					if (src.at<uchar>(curY,curX-1)==255){
						curX--;
						curA=270;
					} else if (src.at<uchar>(curY+1,curX-1)==255){
						curX--;
						curY++;
						curA=225;
					} else if (src.at<uchar>(curY-1,curX-1)==255){
						curX--;
						curY--;
						curA=315;
					}
				} else if (curA==315) {
					if (src.at<uchar>(curY-1,curX-1)==255){
						curX--;
						curY--;
						curA=315;
					} else if (src.at<uchar>(curY,curX-1)==255){
						curX--;
						curA=270;
					} else if (src.at<uchar>(curY-1,curX)==255){
						curY--;
						curA=0;
					}
				}





			} else break;

			namedWindow( "c", CV_WINDOW_AUTOSIZE );
			imshow( "c", src);//thrCrCb[0] );
			waitKey(0);
			curX=curX+1-1;


		} else {
			break;
		}

	}
}

}
