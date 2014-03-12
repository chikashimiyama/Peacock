#ifndef __Peacock__PckVisualizer__
#define __Peacock__PckVisualizer__

#include "ofMain.h"
#include "PckConst.h"
#include "PckRecognizer.h"
#include "ofxGui.h"

/**
 * @brief OepnGL-based visualizer class
 * @details This class utilizes the OpenFrameworks Graphic functionalities to render the current status of Peacock Hardware. This class conforms to Singleton design pattern. 
 * It is not possible to create multiple instances of this class
 */
class PckVisualizer{

private:

    ofColor bgColor;
    ofColor gridColor;
    ofColor gridLineColor;

    ofEasyCam camera;


    ofFloatColor sensorColor[NUM_ROWS][NUM_COLUMNS];
    ofVec3f sensorPosition[NUM_ROWS][NUM_COLUMNS];

    ofVec3f gridLineData[NUM_GRID_LINES][2];

    ofFloatColor thresholdPlaneColor[4];
    ofVec3f thresholdPlaneData[4];

    ofVbo sensorVbo, gridLineVbo;
    ofVbo thresholdPlaneVbo;


    void sensorSetup();
    void gridLineSetup();
    void thresholdPlaneSetup();

    bool statusFlag;
    // gui
    ofxPanel dataPanel;

public:
    PckVisualizer();
    ~PckVisualizer();

    inline void setRecognizer(PckRecognizer *recog);
    void update();

    void setup();
    void draw();
    void toggleStatus();

};




#endif /* defined(__Peacock__PckVisualizer__) */
