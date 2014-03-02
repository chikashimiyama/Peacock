//
//  PckVisualizer.h
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#ifndef __Peacock__PckVisualizer__
#define __Peacock__PckVisualizer__

#include "ofMain.h"
#include "PckConst.h"
#include "PckRecognizer.h"
#include "ofxGui.h"

class PckVisualizer{

private:
    PckRecognizer* recognizer;

    unsigned char *matrix;
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
 sub
public:
    PckVisualizer();
    ~PckVisualizer();

    inline void setRecognizer(PckRecognizer *recog);
    void update();

    void setup(unsigned char *matrix);
    void draw();
    void toggleStatus();

};


void PckVisualizer::setRecognizer(PckRecognizer *recog){
    recognizer = recog;
}

#endif /* defined(__Peacock__PckVisualizer__) */
