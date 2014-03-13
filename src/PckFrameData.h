#ifndef __Peacock__PckFrameData__
#define __Peacock__PckFrameData__

#include <vector>

struct PckFrameData {

	unsigned char matrix[NUM_ROWS * NUM_COLUMNS];
	int totalValue;
	int totalDelta;

	unsigned char overTheThreashold;
	unsigned char positionOfHand;
	int frameSinceEntiring;

	vector<int> peaks;
	
	float verticalCentroid;
	float horizontalCentroid;
};

#endif