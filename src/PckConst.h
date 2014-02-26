//
//  PckConst.h
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#ifndef Peacock_PckConst_h
#define Peacock_PckConst_h

#define ATMEL_VENDOR_ID 0x03eb
#define MY_PRODUCT_ID 0x204f

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#define BUFFER_SIZE 1024
#define NUM_COLUMNS 7
#define MIDDLE_COLUMN 3

#define NUM_ROWS 5
#define MIDDLE_ROW 2

#define NUM_SENSORS (NUM_COLUMNS * NUM_ROWS)
#define NUM_GRID_LINES (NUM_COLUMNS + NUM_ROWS)
#define DISTANCE 10.0

#define THRESHOLD 10.0

enum PCKDetection{
    PCK_ON_TIME,
    PCK_OFF_TIME,
    PCK_MOVEMENT,
    PCK_HAND_TRACE,
    PCK_RECOGNITION,
    PCK_CONTOUR,
    PCK_GRID,
};

enum PCKDrawMode{
    PCK_DRAWMODE_3D,
    PCK_DRAWMODE_HISTORY


};

#endif
