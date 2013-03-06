/*
 * AdaptiveManifoldFilter.h
 *
 *  Created on: 2013. 2. 1.
 *      Author: Nicatio
 */

#ifndef ADAPTIVEMANIFOLDFILTER_H_
#define ADAPTIVEMANIFOLDFILTER_H_

#include "cv.h"
#include "vector"
#include "limits"

using namespace cv;

namespace cvNica {

class AdaptiveManifoldFilter
{
public:
	AdaptiveManifoldFilter(void);
	~AdaptiveManifoldFilter(void);

	Mat minPixelDistToManifoldSquared;
	Mat sumWKiPsiBlur;
	Mat sumWKiPsiBlur0;
	int treeNodesVisited;
	void process(
			InputArray						_Fin,
			OutputArray						_Fout,
			const double					sigmaS,
			const double					sigmaR,
			InputArray						_FJoint,
			int 							treeHeight=0,
			int 							numPcaIterations=0);

	void computeManifoldTreeHeight(
			const double					sigmaS,
			const double					sigmaR,
			int&							Height);//,
			//int								K);

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
			OutputArray						_F,
			const double					sigmaS,
			const double					sigmaR,
			InputArray						_jointImage);

	void TransformedDomainRecursiveFilter_Horizontal(
			InputArray						_Fin,
			InputArray						_dHdx,
			const double					sigmaHi,
			OutputArray						_Fout,
			const int						secondPhaseShift=0);

	void hFilter(
			InputArray						_Fin,
			const double					sigma,
			OutputArray						_Fout);

	void channelSum(
			InputArray						_Fin,
			OutputArray						_Fout);
};

};

#endif /* ADAPTIVEMANIFOLDFILTER_H_ */
