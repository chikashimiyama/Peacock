//
//  PckRecognizer.h
//  Peacock
//
//  Created by Chikashi Miyama on 11/22/13.
//
//

#ifndef __Peacock__PckRecognizer__
#define __Peacock__PckRecognizer__


#include "ofThread.h"

class PckRecognizer {

private:
    void analyzeEnterPoint();
    void analyzeNumberOfHands();
    void analyzePositionOfHands();
    void countActivatedSensors();
    void analyzeSum();
    void analyzeBody();
    void analyzeArmAngle();
    void analyzeWeight();
    
    int sum;
public:
    void update(float *matrix);
    inline int getSum(void);
};

int PckRecognizer::getSum(void){
    return sum;
}


#endif /* defined(__Peacock__PckRecognizer__) */
