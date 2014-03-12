#ifndef __Peacock__PckRecognizer__
#define __Peacock__PckRecognizer__


#include "ofThread.h"

/**
 * @brief Gesture Recognition class
 * @details This class can be only instantiated by PckRecevier
 * 
 * @param analyzeEnterPoint [description]
 * @return [description]
 */
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
