/**
 * A hearder file for consts
 */

#ifndef Peacock_PckConst_h
#define Peacock_PckConst_h

#include <sstream>
#include <string>

#define ATMEL_VENDOR_ID 0x03eb
#define MY_PRODUCT_ID 0x204f

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#define NUM_FRAMES 60000
#define NUM_COLUMNS 7
#define MIDDLE_COLUMN 3

#define MAX_VALUE 250
#define NUM_ROWS 5
#define MIDDLE_ROW 2

#define NUM_SENSORS (NUM_COLUMNS * NUM_ROWS)
#define NUM_GRID_LINES (NUM_COLUMNS + NUM_ROWS)
#define DISTANCE 10.0

#define THRESHOLD 30.0
#define HEIGHT_ONSET 15.0

#define Y_SCALER 0.2

enum PCKNotification{
    PCK_ON_TIME,
    PCK_OFF_TIME,
    PCK_ENTER,
    PCK_HAND_TRACE,
    PCK_RECOGNITION,
    PCK_CONTOUR,
    PCK_GRID,
};

enum PCKDrawMode{
    PCK_DRAWMODE_3D,
    PCK_DRAWMODE_HISTORY

};

inline string intToString(int value){
	std::stringstream ss;
	ss << value;
	return ss.str();
}

#endif
