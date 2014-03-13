#ifndef __Peacock__PckVisualizer__
#define __Peacock__PckVisualizer__

#include "ofMain.h"
#include "PckConst.h"
#include "PckRecognizer.h"
#include "PckFrameData.h"
#include "ofxGui.h"
#include <string>

using namespace std;

/**
 * @brief OepnGL-based visualizer class
 * @details This class utilizes the OpenFrameworks Graphic functionalities to render the current status of Peacock Hardware. This class conforms to Singleton design pattern. 
 * It is not possible to create multiple instances of this class
 */
class PckVisualizer{

private:
    PckFrameData copiedFrameData;

    ofColor bgColor;
    ofColor gridColor;
    ofColor gridLineColor;

    ofEasyCam camera;


    ofFloatColor sensorColor[NUM_ROWS][NUM_COLUMNS][2];
    ofVec3f sensorPosition[NUM_ROWS][NUM_COLUMNS][2];

    ofVec3f gridLineData[NUM_GRID_LINES][2];

    ofFloatColor thresholdPlaneColor[4];
    ofVec3f thresholdPlaneData[4];

    ofVbo sensorVbo, gridLineVbo;
    ofVbo thresholdPlaneVbo;


    void sensorSetup();
    void gridLineSetup();
    void thresholdPlaneSetup();
    void dataPanelSetup();

    bool statusFlag;
    // gui
    ofxPanel dataPanel;

    ofxIntSlider currentFrameSlider;
    ofxIntSlider totalValueSlider;
    ofxIntSlider totalDeltaSlider;

    ofxIntSlider pointsOverThresholdSlider;
    ofxLabel positionOfHandParameter;
    ofxIntSlider gestureDurationParameter;

public:
    PckVisualizer();

    inline void setRecognizer(PckRecognizer *recog);
    /**
     * @brief copy the newest frameData for visualization
     * @details This function is a critical session; it access the shared memory.
     * @param char a pointer to the current matrx (not the pointer to the beginning of the matrix)
     */
    void copyCurrentFrameData(PckFrameData* frameDataPtr, int frameIndex);
    void update();

    void setup();
    void draw();
    void toggleStatus();

};




#endif /* defined(__Peacock__PckVisualizer__) */
