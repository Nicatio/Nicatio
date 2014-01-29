/*
 * LineTracker.h
 *
 *  Created on: 2013. 12. 17.
 *      Author: Nicatio
 */

#ifndef LINETRACKER_H_
#define LINETRACKER_H_

#include "cv.h"
#include "highgui.h"

using namespace cv;

namespace cvNica {

void LineTracker(
		InputArray 						_src,
		int								startX,
		int								startY);

}



#endif /* LINETRACKER_H_ */
