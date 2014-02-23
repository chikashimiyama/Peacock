//
//  PckReceiver.cpp
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#include "PckReceiver.h"
#include "PckConst.h"
#include "ofMath.h"

PckReceiver::PckReceiver(){
    testMode = true;
}


void PckReceiver::setMatrix(float *matrix){
    PckReceiver::matrix = matrix;
}


void PckReceiver::simulateUpdate(){
    
    for (int i = 0 ; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLUMNS; j ++){
            matrix[i*NUM_COLUMNS + j] = ofRandom(0.0, 20.0);
        }
    }
    
}

void PckReceiver::update(){
    if (testMode) {
        simulateUpdate();
    }
}