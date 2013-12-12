/*
 * cvFilter.cpp
 *
 *  Created on: 2013. 3. 7.
 *      Author: Nicatio
 */

#include "cvFilter.h"


using namespace cv;

namespace cvNica {

void IntensityShifting(
		InputArray 						_src,
		OutputArray						_dst,
		const int&						mid)
{
	Mat src = _src.getMat();
	Size srcSize = src.size();
	int sz = srcSize.area();
	unsigned char bb = (sum(src)[0]/sz);
	Mat temp = src + (mid-bb);
	_dst.create(src.size(),src.type());
	Mat dst = _dst.getMat();
	temp.copyTo(dst);
}

Mat rotateImage(
		const Mat						&src,
		double 							angle,
		bool							type,
		int 							borderType,
		int								borderColor)
{
	Mat dst;
	if (type) {
	    Point2f src_center(src.cols/2.0F, src.rows/2.0F);
	    Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);

	    warpAffine(src, dst, rot_mat, src.size());
	    return dst;
	} else {
		Size repSize(src.cols*3, src.rows*3);
		Mat rep(repSize,src.type());
		if (!borderType) {
			copyMakeBorder(src, rep, src.rows, src.rows, src.cols, src.cols, BORDER_CONSTANT, borderColor);
		} else {
			copyMakeBorder(src, rep, src.rows, src.rows, src.cols, src.cols, BORDER_REPLICATE);
		}

		int newW = ceil((double)src.cols * cos(angle/180*PI)) + abs((double)src.rows * sin(angle/180*PI));
		int newH = ceil((double)src.cols * sin(angle/180*PI)) + abs((double)src.rows * cos(angle/180*PI));

		Point2f src_center((float)src.cols*1.5F, (float)src.rows*1.5F);
		Mat rot_mat = getRotationMatrix2D(src_center, angle, 1.0);
		Mat _dst;
		warpAffine(rep, _dst, rot_mat, repSize);
		//dst = _dst(Rect(src.cols*1.5F-newW/2,src.rows*1.5F-newH/2,newW,newH));
		dst = _dst(Rect(src.cols*1.5F-src.cols/2,src.rows*1.5F-src.rows/2,src.cols,src.rows));
	}

    return dst;
}




void FindBlobs(
		const Mat &binary,
		vector < vector<Point2i> > 		&blobs)
{
    blobs.clear();

    // Fill the label_image with the blobs
    // 0  - background
    // 1  - unlabelled foreground
    // 2+ - labelled foreground

    cv::Mat label_image;
    binary.convertTo(label_image, CV_32FC1); // weird it doesn't support CV_32S!

    int label_count = 2; // starts at 2 because 0,1 are used already

    for(int y=0; y < binary.rows; y++) {
        for(int x=0; x < binary.cols; x++) {
            if((int)label_image.at<float>(y,x) != 255) {
                continue;
            }

            cv::Rect rect;
            cv::floodFill(label_image, cv::Point(x,y), cv::Scalar(label_count), &rect, cv::Scalar(0), cv::Scalar(0), 4);

            std::vector <cv::Point2i> blob;

            for(int i=rect.y; i < (rect.y+rect.height); i++) {
                for(int j=rect.x; j < (rect.x+rect.width); j++) {
                    if((int)label_image.at<float>(i,j) != label_count) {
                        continue;
                    }

                    blob.push_back(cv::Point2i(j,i));
                }
            }

            blobs.push_back(blob);

            label_count++;
        }
    }
}

Mat RGBThreshold(
		const Mat						&src,
		int								r,
		int								g,
		int								b,
		int								tolerance)
{
	Mat srcRGB[3],th[6],th_;
	double rb = r - tolerance; if(rb<0) rb=0; if(rb>255) rb=255;
	double ru = r + tolerance; if(ru<0) ru=0; if(ru>255) ru=255;
	double gb = g - tolerance; if(gb<0) gb=0; if(gb>255) gb=255;
	double gu = g + tolerance; if(gu<0) gu=0; if(gu>255) gu=255;
	double bb = b - tolerance; if(bb<0) bb=0; if(bb>255) bb=255;
	double bu = b + tolerance; if(bu<0) bu=0; if(bu>255) bu=255;

	split(src,srcRGB);
	threshold(srcRGB[0],th[0],rb,255,THRESH_BINARY);
	threshold(srcRGB[0],th[1],ru,255,THRESH_BINARY_INV);
	threshold(srcRGB[1],th[2],gb,255,THRESH_BINARY);
	threshold(srcRGB[1],th[3],gu,255,THRESH_BINARY_INV);
	threshold(srcRGB[2],th[4],bb,255,THRESH_BINARY);
	threshold(srcRGB[2],th[5],bu,255,THRESH_BINARY_INV);

	bitwise_and(th[0],th[1],th_);
	bitwise_and(th_,th[2],th_);
	bitwise_and(th_,th[3],th_);
	bitwise_and(th_,th[4],th_);
	bitwise_and(th_,th[5],th_);
	//merge(th,3,th_);
	return th_;

}





}


