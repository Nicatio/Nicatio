/*
 * guidedFilter.cpp
 *
 *  Created on: 2013. 1. 31.
 *      Author: Nicatio
 */


#include "GuidedFilter.h"


CGuidedFilter::CGuidedFilter(void)
{
	cv::setUseOptimized(true);
	cv::setNumThreads(8);
}


CGuidedFilter::~CGuidedFilter(void)
{
}

cv::Mat CGuidedFilter::filtering(const cv::Mat& guidenceIMG, const cv::Mat& inputIMG, const int radius, const double eps)
{
	cv::Mat dst;

	if (radius >= 0 && eps >= 0.0)
	{
		if (guidenceIMG.channels() == 1)
		{
			cv::Mat l, p;
			const double alpha = 1.0 / 255.0;

			guidenceIMG.convertTo(l, CV_64FC1, alpha);
			inputIMG.convertTo(p, CV_64FC1, alpha);

			int hei = l.rows;
			int wid = l.cols;

			// the size of each local patch; N=(2r+1)^2 except for boundary pixels.
			cv::Mat N = boxfilter(cv::Mat::ones(hei, wid, CV_64FC1), radius);

			cv::Mat mean_l = boxfilter(l, radius).mul(1 / N);
			cv::Mat mean_p = boxfilter(p, radius).mul(1 / N);
			cv::Mat mean_lp = boxfilter(l.mul(p), radius).mul(1 / N);
			cv::Mat cov_lp = mean_lp - mean_l.mul(mean_p);		// this is the covariance of (I, p) in each local patch.

			cv::Mat mean_ll = boxfilter(l.mul(l), radius).mul(1 / N);
			cv::Mat var_l = mean_ll - mean_l.mul(mean_l);

			cv::Mat a = cov_lp.mul(1 / (var_l + eps));		// Eqn. (5) in the paper
			cv::Mat b = mean_p - a.mul(mean_l);				// Eqn. (6) in the paper

			cv::Mat mean_a = boxfilter(a, radius).mul(1 / N);
			cv::Mat mean_b = boxfilter(b, radius).mul(1 / N);

			dst = mean_a.mul(l) + mean_b;		// Eqn. (8) in the paper

			dst.convertTo(dst, CV_8UC1, 255.0);
		}
		else if (guidenceIMG.channels() == 3)
		{
			cv::Mat l, p;
			const double alpha = 1.0 / 255.0;

			guidenceIMG.convertTo(l, CV_64FC3, alpha);
			inputIMG.convertTo(p, CV_64FC1, alpha);

			cv::Size frame_size = l.size();

			// the size of each local patch; N=(2r+1)^2 except for boundary pixels.
			cv::Mat N = boxfilter(cv::Mat::ones(frame_size, CV_64FC1), radius);

			std::vector< cv::Mat > l_split;
			cv::split(l, l_split);

			cv::Mat mean_l_r = boxfilter(l_split[2], radius).mul(1 / N);
			cv::Mat mean_l_g = boxfilter(l_split[1], radius).mul(1 / N);
			cv::Mat mean_l_b = boxfilter(l_split[0], radius).mul(1 / N);

			cv::Mat mean_p = boxfilter(p, radius).mul(1 / N);

			cv::Mat mean_lp_r = boxfilter(l_split[2].mul(p), radius).mul(1 / N);
			cv::Mat mean_lp_g = boxfilter(l_split[1].mul(p), radius).mul(1 / N);
			cv::Mat mean_lp_b = boxfilter(l_split[0].mul(p), radius).mul(1 / N);

			// covariance of (l, p) in each local patch
			cv::Mat cov_lp_r = mean_lp_r - mean_l_r.mul(mean_p);
			cv::Mat cov_lp_g = mean_lp_g - mean_l_g.mul(mean_p);
			cv::Mat cov_lp_b = mean_lp_b - mean_l_b.mul(mean_p);

			// variance of l in each local path: the matrix Sigma in Eqn (14).
			// Note the variance in each local patch is a 3x3 symmetric matrix:
			//			rr, rg, rb
			//	Sigma = rg, gg, gb
			//			rb, gb, bb
			cv::Mat var_l_rr = boxfilter(l_split[2].mul(l_split[2]), radius).mul(1 / N) - mean_l_r.mul(mean_l_r);
			cv::Mat var_l_rg = boxfilter(l_split[2].mul(l_split[1]), radius).mul(1 / N) - mean_l_r.mul(mean_l_g);
			cv::Mat var_l_rb = boxfilter(l_split[2].mul(l_split[0]), radius).mul(1 / N) - mean_l_r.mul(mean_l_b);
			cv::Mat var_l_gg = boxfilter(l_split[1].mul(l_split[1]), radius).mul(1 / N) - mean_l_g.mul(mean_l_g);
			cv::Mat var_l_gb = boxfilter(l_split[1].mul(l_split[0]), radius).mul(1 / N) - mean_l_g.mul(mean_l_b);
			cv::Mat var_l_bb = boxfilter(l_split[0].mul(l_split[0]), radius).mul(1 / N) - mean_l_b.mul(mean_l_b);

			std::vector< cv::Mat > a;
			cv::split(cv::Mat::zeros(frame_size, CV_64FC3), a);
			for (int y = 0; y < frame_size.height; y++)
			{
				for (int x = 0; x < frame_size.width; x++)
				{
					cv::Mat Sigma = (cv::Mat_<double>(3,3) <<
						var_l_rr.at<double>(y, x), var_l_rg.at<double>(y, x), var_l_rb.at<double>(y, x),
						var_l_rg.at<double>(y, x), var_l_gg.at<double>(y, x), var_l_gb.at<double>(y, x),
						var_l_rb.at<double>(y, x), var_l_gb.at<double>(y, x), var_l_bb.at<double>(y, x));

					cv::Mat cov_lp = (cv::Mat_<double>(1, 3) <<
						cov_lp_r.at<double>(y, x), cov_lp_g.at<double>(y, x), cov_lp_b.at<double>(y, x));

					cv::Mat eye_temp = cv::Mat::eye(3, 3, CV_64FC1);
					cv::Mat inv = cov_lp * (Sigma + eye_temp.mul(eps)).inv();

					for (int i = 0; i < 3; i++)
					{
						a[i].at<double>(y, x) = inv.at<double>(i);		// Eqn. (14) in the paper
					}
				}
			}

			cv::Mat b = mean_p - a[0].mul(mean_l_r) - a[1].mul(mean_l_g) - a[2].mul(mean_l_b);		// Eqn. (15) in the paper

			// Eqn. (16) in the paper
			dst = boxfilter(a[2], radius).mul(l_split[0]) +
				boxfilter(a[1], radius).mul(l_split[1]) +
				boxfilter(a[0], radius).mul(l_split[2]) +
				boxfilter(b, radius);
			dst = dst.mul(1 / N);

			dst.convertTo(dst, CV_8UC3, 255.0);
		}
	}

	return dst;
}

cv::Mat CGuidedFilter::boxfilter(const cv::Mat& imSrc, const int r)
{
	int wid = imSrc.cols;
	int hei = imSrc.rows;
	cv::Mat dst = cv::Mat::zeros(imSrc.size(), CV_64FC1);

	if (r >= 0 && hei >= (2*r+1) && wid >= (2*r+1))
	{
		cv::Mat src;
		imSrc.convertTo(src, CV_64FC1);

		// cumulative sum over Y axis
		cv::Mat imCum = cumsum(src, 1);
		// difference over Y axis
		imCum(cv::Range(r, 2*r+1), cv::Range::all()).copyTo(dst(cv::Range(0, r+1), cv::Range::all()));
		cv::Mat temp = imCum(cv::Range(2*r+1, hei), cv::Range::all()) - imCum(cv::Range(0, hei-2*r-1), cv::Range::all());
		temp.copyTo(dst(cv::Range(r+1, hei-r), cv::Range::all()));
		temp = repmat(imCum(cv::Range(hei-1, hei), cv::Range::all()), r, 1) - imCum(cv::Range(hei-2*r-1, hei-r-1), cv::Range::all());
		temp.copyTo(dst(cv::Range(hei-r, hei), cv::Range::all()));

		// cumulative sum over X axis
		imCum = cumsum(dst, 2);
		// difference over Y axis
		imCum(cv::Range::all(), cv::Range(r, 2*r+1)).copyTo(dst(cv::Range::all(), cv::Range(0, r+1)));
		temp = imCum(cv::Range::all(), cv::Range(2*r+1, wid)) - imCum(cv::Range::all(), cv::Range(0, wid-2*r-1));
		temp.copyTo(dst(cv::Range::all(), cv::Range(r+1, wid-r)));
		temp = repmat(imCum(cv::Range::all(), cv::Range(wid-1, wid)), 1, r) - imCum(cv::Range::all(), cv::Range(wid-2*r-1, wid-r-1));
		temp.copyTo(dst(cv::Range::all(), cv::Range(wid-r, wid)));
	}

	return dst;
}

cv::Mat CGuidedFilter::cumsum(const cv::Mat& imSrc, const int dim)
{
	cv::Mat dst;

	if (dim > 0 && dim < 3)
	{
		cv::Mat src;
		imSrc.convertTo(src, CV_64FC1);
		dst.create(cv::Size(src.cols, src.rows), CV_64FC1);

		switch (dim)
		{
		case 1:		// cumulate columns
			src.row(0).copyTo(dst.row(0));

			for (int i = 1; i < src.rows; i++)
			{
				cv::Mat col_sum = dst.row(i-1) + src.row(i);
				col_sum.copyTo(dst.row(i));
			}
			break;
		case 2:		// cumulate rows
			src.col(0).copyTo(dst.col(0));

			for (int i = 1; i < src.cols; i++)
			{
				cv::Mat row_sum = dst.col(i-1) + src.col(i);
				row_sum.copyTo(dst.col(i));
			}
			break;
		}
	}

	return dst;
}

cv::Mat CGuidedFilter::cumsum(const cv::Mat& imSrc)
{
	cv::Mat dst;

	if (imSrc.channels() == 1)
	{
		dst = cv::Mat::zeros(imSrc.size(), CV_64FC1);

		// If imSrc is a vector, cumsum(imSrc) returns a vector containing the cumulative sum of the elements of imSrc.
		if (imSrc.rows == 1)
		{
			dst.at<double>(0, 0) = static_cast<double>(imSrc.at<uchar>(0, 0));

			double prev_cum_value = dst.at<double>(0, 0);
			for (int i = 0; i < imSrc.rows; i++)
			{
				for (int j = 1; j < imSrc.cols; j++)
				{
					dst.at<double>(i, j) = prev_cum_value + static_cast<double>(imSrc.at<uchar>(i, j));
					prev_cum_value = dst.at<double>(i, j);
				}
			}
		}
		// If imSrc is a matrix, cumsum(imSrc) returns a matrix the same size as imSrc containing the cumulative sums for each column of imSrc.
		else
		{
			cv::Mat src;
			imSrc.convertTo(src, CV_64FC1);

			// cumulate columns
			src.row(0).copyTo(dst.row(0));

			for (int i = 1; i < src.rows; i++)
			{
				cv::Mat col_sum = dst.row(i-1) + src.row(i);
				col_sum.copyTo(dst.row(i));
			}
		}
	}

	return dst;
}

cv::Mat CGuidedFilter::repmat(const cv::Mat& A, const int m, const int n)
{
	cv::Mat dst;

	if (m > 0 && n > 0)
	{
		int hei = A.rows;
		int wid = A.cols;
		int new_hei = A.rows * m;
		int new_wid = A.cols * n;

		dst.create(cv::Size(new_wid, new_hei), A.type());

		for (int i = 0; i < new_hei; i+=hei)
		{
			for (int j = 0; j < new_wid; j+=wid)
			{
				A.copyTo(dst(cv::Rect(j, i, A.cols, A.rows)));
			}
		}
	}

	return dst;
}

