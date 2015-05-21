/*
 * SWT.cpp
 *
 *  Created on: 2014. 6. 18.
 *      Author: Nicatio
 */

#include "SWT.h"

namespace cvNica {

void SWT(
		InputArray 						_src,
		OutputArray						_dst)
{
	Mat src = _src.getMat();
	Mat src_gray, canny, canny_clone;
	Size size = src.size();
	int _width = size.width;
	int _height = size.height;
	int searchDirection = 1;

	cvtColor(src,src_gray,CV_BGR2GRAY);
	Canny( src_gray, canny, 30, 50, 3, 1 );

	canny.copyTo(canny_clone);

	Mat sobelx(size,CV_32FC1);
	Mat sobely(size,CV_32FC1);

	Sobel(src_gray,sobelx,CV_32FC1,1,0,3,1, 0, BORDER_DEFAULT );
	Sobel(src_gray,sobely,CV_32FC1,0,1,3,1, 0, BORDER_DEFAULT );

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);
//	namedWindow( "Canny", CV_WINDOW_AUTOSIZE );
//	imshow( "Canny", canny );
//	/// Find contours
//	findContours( canny, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE, Point(0, 0) );
//	namedWindow( "Canny2", CV_WINDOW_AUTOSIZE );
//	imshow( "Canny2", canny );

//	/// Draw contours
//	Mat drawing = Mat::zeros( canny.size(), CV_8UC3 );
//	for( int i = 0; i< contours.size(); i++ )
//	{
//		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//		drawContours( drawing, contours, i, color, 1, 8, hierarchy, 0, Point() );
//	}
//	namedWindow( "Canny", CV_WINDOW_AUTOSIZE );
//	imshow( "Canny", canny_clone );
//
//	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
//	imshow( "Contours", drawing );

	Mat gradientMap = Mat::zeros(size,CV_32FC1);
	int totalContourLength = 0;
	vector<Point> pointList;
	for( int i = 0; i< _height; i++ ){
		for( int j = 0; j< _width; j++ ){
			if (canny.at<uchar>(i,j)) {
				gradientMap.at<float>(i,j) = atan2 (sobely.at<float>(i,j),sobelx.at<float>(i,j));
				totalContourLength++;
				pointList.push_back(Point(j,i));
			}
		}
	}

//	for( int i = 0; i< contours.size(); i++ ){
//		for( int j = 0; j< contours[i].size(); j++ ){
//			gradientMap.at<float>(contours[i][j]) = atan2 (sobely.at<float>(contours[i][j]),sobelx.at<float>(contours[i][j]));
//			totalContourLength++;
//		}
//	}
	namedWindow( "gm", CV_WINDOW_AUTOSIZE );
	imshow( "gm", gradientMap );

	int maxStrokeWidth = 350;
	int *strokePointsX = new int[totalContourLength];
	int *strokePointsY = new int[totalContourLength];
	int sizeOfStrokePoints = 0;
	Mat swtMap = Mat::zeros(size,CV_32FC1)+maxStrokeWidth;
	std::cout<<"len: "<<pointList.size()<<std::endl;
	std::cout<<"len: "<<totalContourLength<<std::endl;

	for( int i = 0; i<totalContourLength; i++ ){

			int step = 1;
			int initialX = pointList[i].x;
			int initialY = pointList[i].y;
			int isStroke = 0;
			float initialTheta = gradientMap.at<float>(pointList[i]);
			int sizeOfRay = 0;
			int *pointOfRayX = new int[maxStrokeWidth];
			int *pointOfRayY = new int[maxStrokeWidth];
			pointOfRayX[sizeOfRay] = initialX;
			pointOfRayY[sizeOfRay++] = initialY;
			int nextX;
			int nextY;
			while (step < maxStrokeWidth){
				nextX = floor(initialX + cos(initialTheta)*searchDirection*step+.5);
				nextY = floor(initialY + sin(initialTheta)*searchDirection*step+.5);
				step++;

				if(nextX < 0 || nextY < 0 || nextX >= _width || nextY >= _height) {
					break;
				}

				pointOfRayX[sizeOfRay] = nextX;
				pointOfRayY[sizeOfRay] = nextY;

				sizeOfRay++;

				if (canny_clone.at<uchar>(nextY,nextX)){
					if (abs(abs(initialTheta-gradientMap.at<float>(nextY,nextX))-PI)<PI/2){
						isStroke = 1;
						strokePointsX[sizeOfStrokePoints] = initialX;
						strokePointsY[sizeOfStrokePoints] = initialY;
						sizeOfStrokePoints++;
						//std::cout<<"k: "<<(uint)canny_clone.at<uchar>(nextY,nextX)<<std::endl;
					}
					break;
				}
			}

			if (isStroke){
				float strokeWidth = sqrt((double)(nextX - initialX)*(nextX - initialX) + (nextY - initialY)*(nextY - initialY));
				//std::cout<<"k: "<<strokeWidth<<std::endl;
				for (int k=0; k<sizeOfRay; k++){
					swtMap.at<float>(pointOfRayY[k],pointOfRayX[k]) = min(swtMap.at<float>(pointOfRayY[k],pointOfRayX[k]),strokeWidth);
				}
			}

			delete [] pointOfRayX;
			delete [] pointOfRayY;
//

	}


//	for( int i = 0; i< contours.size(); i++ ){
//		for( int j = 0; j< contours[i].size(); j++ ){
//			int step = 1;
//			int initialX = contours[i][j].x;
//			int initialY = contours[i][j].y;
//			int isStroke = 0;
//			float initialTheta = gradientMap.at<float>(contours[i][j]);
//			int sizeOfRay = 0;
//			int *pointOfRayX = new int[maxStrokeWidth];
//			int *pointOfRayY = new int[maxStrokeWidth];
//			pointOfRayX[sizeOfRay] = initialX;
//			pointOfRayY[sizeOfRay++] = initialY;
//			int nextX;
//			int nextY;
//			while (step < maxStrokeWidth){
//				nextX = round(initialX + cos(initialTheta)*searchDirection*step);
//				nextY = round(initialY + sin(initialTheta)*searchDirection*step);
//				step++;
//
//				if(nextX < 0 || nextY < 0 || nextX >= _width || nextY >= _height) {
//					break;
//				}
//
//				pointOfRayX[sizeOfRay] = nextX;
//				pointOfRayY[sizeOfRay] = nextY;
//
//				sizeOfRay++;
//
//				if (canny_clone.at<uchar>(nextY,nextX)){
//					if (abs(abs(initialTheta-gradientMap.at<float>(nextY,nextX))-PI)<PI/2){
//						isStroke = 1;
//						strokePointsX[sizeOfStrokePoints] = initialX;
//						strokePointsY[sizeOfStrokePoints] = initialY;
//						sizeOfStrokePoints++;
//						//std::cout<<"k: "<<(uint)canny_clone.at<uchar>(nextY,nextX)<<std::endl;
//					}
//					break;
//				}
//			}
//
//			if (isStroke){
//				float strokeWidth = sqrt((nextX - initialX)*(nextX - initialX) + (nextY - initialY)*(nextY - initialY));
//				//std::cout<<"k: "<<strokeWidth<<std::endl;
//				for (int k=0; k<sizeOfRay; k++){
//					swtMap.at<float>(pointOfRayY[k],pointOfRayX[k]) = min(swtMap.at<float>(pointOfRayY[k],pointOfRayX[k]),strokeWidth);
//				}
//			}
//
//			delete [] pointOfRayX;
//			delete [] pointOfRayY;
////
//		}
//	}

	namedWindow( "swt", CV_WINDOW_AUTOSIZE );
	imshow( "swt", swtMap/350 );



	waitKey(0);

}

}


