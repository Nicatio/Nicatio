/*
 * FRID.h
 *
 *  Created on: 2014. 1. 20.
 *      Author: Nicatio
 */

#ifndef FRID_H_
#define FRID_H_
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "cv.h"
#include "highgui.h"
#include "../nicatio/fft.h"
#include "../nicatio/nicatio.h"
#include "../cvnica/cvnica.h"
//#include "./dirent/dirent.h"
#include "../io.h"


#define FRID_16   0
#define FRID_24   1
#define FRID_16F  2
#define FRID_16F2 3

using namespace cv;

namespace cvNica {

extern uint order_FRID16 [17][2];
extern uint order_FRID24 [25][2];
extern float order_FRID16F_sin [17];
extern float order_FRID16F_cos [17];

class FRID
{
	public:
	Mat orderMap[33];
	int _type;
	int w4;
	int h4;

	FRID(
			InputArray						src,
			int								type);
	Mat getFeatureVector(
			int								x,
			int								y,
			double&							phr,
			double&							phg,
			double&							phb,
			double&							sumr,
			double&							sumg,
			double&							sumb);
};



}





#endif /* FRID_H_ */

