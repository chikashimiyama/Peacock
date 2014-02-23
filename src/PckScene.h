//
//  PckScene.h
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#ifndef __Peacock__PckScene__
#define __Peacock__PckScene__

#include "ofMain.h"
#include "PckConst.h"
#include "PckVisualizer.h"
#include "PckReceiver.h"
#include "PckRecognizer.h"
#include "PckSyntheizer.h"


class PckScene{
    
private:
    // 3D Matrix ...   will be updated by the secondary thread
    float matrix[BUFFER_SIZE][NUM_ROWS][NUM_COLUMNS];
    
    PckVisualizer visualizer;
    PckReceiver receiver;
    PckRecognizer recognizer;
    PckSyntheizer synthesizer;
    
    bool forwarding;
    
public:
    PckScene();
    ~PckScene();
    
    // data capture
    void openPort();
    
    void closePort();
    
    void update();
    void draw();

    // visualize
    void toggleStatus();

    // send data to receiver
    
    
};

#endif /* defined(__Peacock__PckScene__) */
