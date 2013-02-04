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

class AdaptiveManifoldFilter
{
public:
	AdaptiveManifoldFilter(void);
	~AdaptiveManifoldFilter(void);

	Mat minPixelDistToManifoldSquared;

	void computeEigenvector(
			InputArray	 					_XX,
			const int						numPCA_Iterations,
			InputArray						_randVec,
			OutputArray						_p);

	void buildManifoldsAndPerformFiltering(
			InputArray						_f,
			InputArray						_fJoint,
			OutputArray						_fOut,
			InputArray						_etaK,
			InputArray						_clusterK,
			const double					sigmaS,
			const double					sigmaR,
			const int 						currentTreeLevel,
			const int 						treeHeight,
			const int 						numPcaIterations);
	void RFFilter(
			InputArray						_img,
			InputArray						_img0,
			OutputArray						_F,
			const double					sigmaS,
			const double					sigmaR,
			InputArray						_jointImage=NULL);
};

};

#endif /* ADAPTIVEMANIFOLDFILTER_H_ */
