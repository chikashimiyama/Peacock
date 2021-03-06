#ifndef __Peacock__PckFrameData__
#define __Peacock__PckFrameData__

#include <vector>

/**
 * @brief a small packet of information of one Peacock frame
 */
struct PckFrameData {

	unsigned char matrix[NUM_ROWS * NUM_COLUMNS];
	int totalValue;
	int totalDelta;

	unsigned char overTheThreashold;
	unsigned char positionOfHand;
	int frameSinceEntiring;

	vector<int> peaks;
	
	float rowCentroids[NUM_COLUMNS];
	float columnCentroids[NUM_ROWS];
	float rowCentroid;
	float columnCentroid;
};

#endif
