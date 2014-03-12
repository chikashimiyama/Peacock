#include "PckRecognizer.h"
#include "PckConst.h"

void PckRecognizer::update(float *matrix) {
    sum = 0;
    for (int i = 0; i < NUM_SENSORS; i++) {
        sum += matrix[i];
    }
    
}