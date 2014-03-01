//
//  PckReceiver.h
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#ifndef __Peacock__PckReceiver__
#define __Peacock__PckReceiver__

#include <vector>
#include "PckSerial.h"

class PckReceiver{

    bool testMode;
    float *matrix;
    std::vector<char> serialbufferVector;
    PckSerial serial;

public:
    PckReceiver();

    void setup();
    void setMatrix(float *matrix);
    void update();
    void simulateUpdate();
};


#endif /* defined(__Peacock__PckReceiver__) */
