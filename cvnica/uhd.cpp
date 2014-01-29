/*
 * uhd.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: Nicatio
 */


#include "uhd.h"

namespace cvNica {


void downsample(
		const Mat 						&src,
		Mat 							&dst,
		int								startx,
		int								starty,
		const Size						&s)
{
    float factor = src.rows/(float)s.height;
    Mat _dst = Mat(s, src.type());

    for(int i=startx; i < src.cols; i += factor) {
        int _i = i/factor;
        for(int j=starty; j < src.rows; j += factor) {
            int _j = j/factor;
            //_dst.at<Vec3b> (_j, _i) = src.at<Vec3b>(j, i);
            _dst.at<uchar> (_j, _i) = src.at<uchar>(j, i);
        }
    }
    //cout << "downsample image size: " << _dst.rows << " " << _dst.cols << endl;
    dst = Mat(_dst);
}


unsigned char getpixel(
		const unsigned char 			*in,
		std::size_t 					src_width,
		std::size_t 					src_height,
		int	 							x,
		int								y)
{
	int x_ = x;
	int y_ = y;

	if (x_<0) x_ = 0;
	if (y_<0) y_ = 0;
	if (x_>=(int)src_width) x_ = (int)(src_width-1);
	if (y_>=(int)src_height) y_ = (int)(src_height-1);
    //if (x>=0 && y>=0 && x < src_width && y < src_height)
    //    return in[(y * src_width) + x];

    //return 0;
	return in[(y_ * src_width) + x_];
}

void bicubicresize(
		unsigned char 					*in,
		unsigned char 					*out,
		std::size_t 					src_width,
		std::size_t 					src_height,
		std::size_t 					dest_width,
		std::size_t 					dest_height,
		int								shiftx,
		int								shifty)
{
    //unsigned char *out = (unsigned char*) malloc(sizeof(unsigned char)*dest_width * dest_height);

    const float tx = float(src_width) / dest_width;
    const float ty = float(src_height) / dest_height;
    //const int channels = 3;
    const std::size_t row_stride = dest_width;

    unsigned char C[5] = { 0 };

    for (int i = 0; i < dest_width; ++i)
    {
        for (int j = 0; j < dest_height; ++j)
        {
            const int x = int(tx * (j-shiftx));
            const int y = int(ty * (i-shifty));
            const float dx = tx * (j-shiftx) - x;
            const float dy = ty * (i-shifty) - y;
            float a0, a1, a2, a3, d0, d2, d3;
            for (int jj = 0; jj < 4; ++jj)
			{
				const int z = y - 1 + jj;
				a0 = getpixel(in, src_width, src_height, z, x);
				d0 = getpixel(in, src_width, src_height, z, x - 1) - a0;
				d2 = getpixel(in, src_width, src_height, z, x + 1) - a0;
				d3 = getpixel(in, src_width, src_height, z, x + 2) - a0;
				a1 = -1.0 / 3 * d0 + d2 - 1.0 / 6 * d3;
				a2 = 1.0 / 2 * d0 + 1.0 / 2 * d2;
				a3 = -1.0 / 6 * d0 - 1.0 / 2 * d2 + 1.0 / 6 * d3;
				C[jj] = a0 + a1 * dx + a2 * dx * dx + a3 * dx * dx * dx;

			}

            d0 = C[0] - C[1];
            d2 = C[2] - C[1];
            d3 = C[3] - C[1];
            a0 = C[1];
            a1 = -1.0 / 3 * d0 + d2 -1.0 / 6 * d3;
            a2 = 1.0 / 2 * d0 + 1.0 / 2 * d2;
            a3 = -1.0 / 6 * d0 - 1.0 / 2 * d2 + 1.0 / 6 * d3;
            out[i  + j * row_stride] = (uchar) (a0 + a1 * dy + a2 * dy * dy + a3 * dy * dy * dy);
        }
    }

}

}
