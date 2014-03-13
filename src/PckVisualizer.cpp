#include "PckVisualizer.h"
#include "Peacock.h"

PckVisualizer::PckVisualizer(){
    bgColor = ofColor(0);
    camera.setDistance(70);
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
            sensorPosition[i][j][0].x = (x - MIDDLE_COLUMN) * DISTANCE;
            sensorPosition[i][j][0].y = HEIGHT_ONSET;
            sensorPosition[i][j][0].z = (i- MIDDLE_ROW) * DISTANCE;

            sensorPosition[i][j][1].x = (x - MIDDLE_COLUMN) * DISTANCE;
            sensorPosition[i][j][1].y = 0.0;
            sensorPosition[i][j][1].z = (i- MIDDLE_ROW) * DISTANCE;

            sensorColor[i][j][0] = ofFloatColor(1.0, 1.0, 1.0);
            sensorColor[i][j][1] = ofFloatColor(1.0, 1.0, 1.0);
        }
    }
    sensorVbo.setColorData(&sensorColor[0][0][0], NUM_SENSORS*2, GL_DYNAMIC_DRAW);
    sensorVbo.setVertexData(&sensorPosition[0][0][0], NUM_SENSORS*2, GL_DYNAMIC_DRAW);

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
    thresholdPlaneData[0].y = HEIGHT_ONSET - (THRESHOLD * Y_SCALER);

    thresholdPlaneColor[1] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[1].x = -MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[1].z = MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[1].y = HEIGHT_ONSET - (THRESHOLD * Y_SCALER);

    thresholdPlaneColor[2] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[2].x = -MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[2].z = -MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[2].y = HEIGHT_ONSET- (THRESHOLD * Y_SCALER);

    thresholdPlaneColor[3] = ofFloatColor(1.0, 0.0, 0.0);
    thresholdPlaneData[3].x = MIDDLE_COLUMN * DISTANCE;
    thresholdPlaneData[3].z = -MIDDLE_ROW * DISTANCE;
    thresholdPlaneData[3].y = HEIGHT_ONSET -(THRESHOLD * Y_SCALER);

    thresholdPlaneVbo.setColorData(thresholdPlaneColor, 4, GL_STATIC_DRAW);
    thresholdPlaneVbo.setVertexData(thresholdPlaneData, 4, GL_STATIC_DRAW);
}

void PckVisualizer::dataPanelSetup(){
    dataPanel.setup("general info:");

    dataPanel.add(currentFrameSlider.setup("current frame", 0, 0, NUM_FRAMES));
    dataPanel.add(totalValueSlider.setup("total", 0, 0, NUM_SENSORS * MAX_VALUE));
    dataPanel.add(totalDeltaSlider.setup("delta", 0, 0, MAX_VALUE* 3));

    dataPanel.add(pointsOverThresholdSlider.setup("current", 0, 0, NUM_SENSORS));

    dataPanel.add(columnCentroidSlider.setup("column centroid", 0.0, -3.0, 3.0));
    dataPanel.add(rowCentroidSlider.setup("row centroid", 0.0, -2.0, 2.0));



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
            data = copiedCurrentMatrix[i*NUM_COLUMNS+j];

            if (data > THRESHOLD) {
                sensorColor[i][j][0] = ofFloatColor(1.0, 0.0, 0.0);
                sensorColor[i][j][1] = ofFloatColor(1.0, 0.0, 0.0);
            }else{
                sensorColor[i][j][0] = ofFloatColor(1.0, 1.0, 1.0);
                sensorColor[i][j][1] = ofFloatColor(1.0, 1.0, 1.0);
            }

            sensorPosition[i][j][1].y = HEIGHT_ONSET - (static_cast<float>(copiedCurrentMatrix[i*NUM_COLUMNS + j]) * Y_SCALER);
        }
    }

    totalValueSlider = copiedFrameData.totalValue;
    totalDeltaSlider = copiedFrameData.totalDelta;

    sensorVbo.updateColorData(&sensorColor[0][0][0], NUM_SENSORS*2);
    sensorVbo.updateVertexData(&sensorPosition[0][0][0], NUM_SENSORS*2);

}

void PckVisualizer::draw(){
    ofBackground(bgColor);

    camera.begin();
    ofRotateX(ofRadToDeg(.5));

    ofSetLineWidth(3);
    sensorVbo.draw(GL_LINES, 0, NUM_SENSORS*2);

    ofSetColor(gridColor);
    ofSetLineWidth(1);
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

