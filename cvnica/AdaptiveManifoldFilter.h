/*
 * AdaptiveManifoldFilter.h
 *
 *  Created on: 2013. 2. 1.
 *      Author: HDSP
 */

#ifndef ADAPTIVEMANIFOLDFILTER_H_
#define ADAPTIVEMANIFOLDFILTER_H_

#include "cv.h"
#include "vector"

using namespace cv;

namespace cvNica {

void computeEigenvector(
		InputArray	 					X,
		int								numPCA_Iterations,
		InputArray						randVec,
		OutputArray						p);

}



#endif /* ADAPTIVEMANIFOLDFILTER_H_ */
