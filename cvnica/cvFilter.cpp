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
            cv::floodFill(label_image, cv::Point(x,y), cv::Scalar(label_count), &rect, cv::Scalar(0), cv::Scalar(0), 8);

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



void ELBP(const Mat& src, Mat& dst, int radius, int neighbors, int th) {
    neighbors = max(min(neighbors,31),1); // set bounds...
    // Note: alternatively you can switch to the new OpenCV Mat_
    // type system to define an unsigned int matrix... I am probably
    // mistaken here, but I didn't see an unsigned int representation
    // in OpenCV's classic typesystem...
    dst = Mat::zeros(src.rows-2*radius, src.cols-2*radius, CV_32SC1);
    for(int n=0; n<neighbors; n++) {
        // sample points
        float x = static_cast<float>(radius) * cos(2.0*PI*n/static_cast<float>(neighbors));
        float y = static_cast<float>(radius) * -sin(2.0*PI*n/static_cast<float>(neighbors));
        // relative indices
        int fx = static_cast<int>(floor(x));
        int fy = static_cast<int>(floor(y));
        int cx = static_cast<int>(ceil(x));
        int cy = static_cast<int>(ceil(y));
        // fractional part
        float ty = y - fy;
        float tx = x - fx;
        // set interpolation weights
        float w1 = (1 - tx) * (1 - ty);
        float w2 =      tx  * (1 - ty);
        float w3 = (1 - tx) *      ty;
        float w4 =      tx  *      ty;
        // iterate through your data
        for(int i=radius; i < src.rows-radius;i++) {
            for(int j=radius;j < src.cols-radius;j++) {

                float t = w1*src.at<uchar>(i+fy,j+fx) + w2*src.at<uchar>(i+fy,j+cx) + w3*src.at<uchar>(i+cy,j+fx) + w4*src.at<uchar>(i+cy,j+cx)+th;
                // we are dealing with floating point precision, so add some little tolerance
                //std::cout<<(((t > src.at<uchar>(i,j)) && (abs(t-src.at<uchar>(i,j)) > std::numeric_limits<float>::epsilon())) << n)<<std::endl;
                dst.at<unsigned int>(i-radius,j-radius) += ((t > src.at<uchar>(i,j)) && (abs(t-src.at<uchar>(i,j)) > std::numeric_limits<float>::epsilon())) << n;
            	if ((i==3)&&(j==9)) {
            		std::cout<<"\t"<<n<<"\t"<<t<<"\t"<<(double)src.at<uchar>(i,j)<<"\t"<<abs(t-src.at<uchar>(i,j))<<"\t"<<(abs(t-src.at<uchar>(i,j)) > std::numeric_limits<float>::epsilon())<<"\t"<<(((t > src.at<uchar>(i,j)) && (abs(t-src.at<uchar>(i,j)) > std::numeric_limits<float>::epsilon())) << n)<<std::endl;
            		//j=7;
            	}
            }
        }
    }
}


}


