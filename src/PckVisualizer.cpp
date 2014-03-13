#include "PckVisualizer.h"
#include "Peacock.h"

PckVisualizer::PckVisualizer(){
    bgColor = ofColor(0);
    camera.setDistance(60);
    camera.enableMouseInput();
}

void PckVisualizer::setup(){
    sensorSetup();
    gridLineSetup();
    thresholdPlaneSetup();
    dataPanelSetup();
}

void PckVisualizer::sensorSetup(){
    // grid vertices
    gridColor = ofColor(255, 255, 255);
    for(int i = 0; i< NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLUMNS; j++){
            float x = static_cast<float>(j);
            sensorPosition[i][j].x = (x - MIDDLE_COLUMN) * DISTANCE ;
            sensorPosition[i][j].y = 0.0;
            sensorPosition[i][j].z = (i- MIDDLE_ROW) * DISTANCE ;

            sensorColor[i][j] = ofFloatColor(1.0, 1.0, 1.0);
        }
    }
    sensorVbo.setColorData(&sensorColor[0][0], NUM_SENSORS, GL_DYNAMIC_DRAW);
    sensorVbo.setVertexData(&sensorPosition[0][0], NUM_SENSORS, GL_DYNAMIC_DRAW);

}


void PckVisualizer::gridLineSetup(){

    gridLineColor = ofColor(255, 255, 255);
    for(int i = 0; i< NUM_ROWS; i++){
        float x = static_cast<float>(i);
        gridLineData[i][0]. x = -MIDDLE_COLUMN * DISTANCE;
        gridLineData[i][0]. y = HEIGHT_ONSET;
        gridLineData[i][0]. z = (x - MIDDLE_ROW) * DISTANCE;

        gridLineData[i][1]. x = MIDDLE_COLUMN * DISTANCE;
        gridLineData[i][1]. y = HEIGHT_ONSET;
        gridLineData[i][1]. z = (x - MIDDLE_ROW) * DISTANCE;
    }
    for(int i = NUM_ROWS; i< NUM_GRID_LINES; i++){

        float x = static_cast<float>(i - NUM_ROWS);

        gridLineData[i][0]. x = (x - MIDDLE_COLUMN) * DISTANCE;
        gridLineData[i][0]. y = HEIGHT_ONSET;
        gridLineData[i][0]. z = -MIDDLE_ROW * DISTANCE;

        gridLineData[i][1]. x =  (x - MIDDLE_COLUMN) * DISTANCE;
        gridLineData[i][1]. y = HEIGHT_ONSET;
        gridLineData[i][1]. z =  MIDDLE_ROW * DISTANCE;
    }

    gridLineVbo.setVertexData(&gridLineData[0][0], NUM_GRID_LINES*2, GL_STATIC_DRAW);
}

void PckVisualizer::thresholdPlaneSetup(){

    thresholdPlaneColor[0] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[0].x = MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[0].z = MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[0].y = THRESHOLD;

    thresholdPlaneColor[1] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[1].x = -MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[1].z = MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[1].y = THRESHOLD;

    thresholdPlaneColor[2] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[2].x = -MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[2].z = -MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[2].y = THRESHOLD;

    thresholdPlaneColor[3] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[3].x = MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[3].z = -MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[3].y = THRESHOLD;

    thresholdPlaneVbo.setColorData(thresholdPlaneColor, 4, GL_STATIC_DRAW);
    thresholdPlaneVbo.setVertexData(thresholdPlaneData, 4, GL_STATIC_DRAW);
}

void PckVisualizer::dataPanelSetup(){
    dataPanel.setup("general info:");

    dataPanel.add(currentFrameSlider.setup("current frame", 0, 0, NUM_FRAMES));
    dataPanel.add(totalValueSlider.setup("total", 0, 0, NUM_SENSORS * MAX_VALUE));
    dataPanel.add(totalDeltaSlider.setup("delta", 0, 0, MAX_VALUE* 3));

    dataPanel.add(pointsOverThresholdSlider.setup("current", 0, 0, NUM_SENSORS));
    dataPanel.add(positionOfHandParameter.setup("hand position", ""));
    dataPanel.add(gestureDurationParameter.setup("gesture dur.", 0, 0, NUM_FRAMES));


}

void PckVisualizer::copyCurrentFrameData(PckFrameData* frameDataPtr, int frameIndex){
    PckFrameData* frameData = &frameDataPtr[frameIndex];
    memcpy(static_cast<void*>(&copiedFrameData), static_cast<void*>(frameData),  sizeof(PckFrameData));
    currentFrameSlider = frameIndex;
}

void PckVisualizer::update(){

    //update matrix
    float data;
    unsigned char* copiedCurrentMatrix = copiedFrameData.matrix;
    for(int i = 0; i< NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLUMNS; j++){
            data = copiedCurrentMatrix[i*NUM_COLUMNS];
            if (data > THRESHOLD) {
                sensorColor[i][j] = ofFloatColor(1.0, 0.0, 0.0);
            }else{
                sensorColor[i][j] = ofFloatColor(1.0, 1.0, 1.0);
            }

            sensorPosition[i][j].y = HEIGHT_ONSET - (static_cast<float>(copiedCurrentMatrix[i*NUM_COLUMNS + j]) / 5.0);
        }
    }

    totalValueSlider = copiedFrameData.totalValue;
    totalDeltaSlider = copiedFrameData.totalDelta;

    sensorVbo.updateColorData(&sensorColor[0][0], NUM_SENSORS);
    sensorVbo.updateVertexData(&sensorPosition[0][0], NUM_SENSORS);

}

void PckVisualizer::draw(){
    ofBackground(bgColor);

    camera.begin();
    ofRotateX(ofRadToDeg(.5));

//    ofSetColor(gridColor);
    glPointSize(10.0);
    sensorVbo.draw(GL_POINTS, 0, NUM_SENSORS);

    ofSetColor(gridColor);
    gridLineVbo.draw(GL_LINES, 0, NUM_GRID_LINES*2);
    thresholdPlaneVbo.draw(GL_LINE_LOOP, 0, 4);

    camera.end();

    // if (statusFlag) {
    //     string statusString;
    //     statusString += "Threshold: \n";
    //     statusString += "Overall value: \n";
    //     statusString += "Hand Position: \n";
    //     statusString += "Duration since the last entrance: \n";
    //     ofDrawBitmapString(statusString , 10, 20);

    // }

    dataPanel.draw();
}

void PckVisualizer::toggleStatus(){
    statusFlag = !statusFlag;
}

