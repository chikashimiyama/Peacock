#include "Peacock.h"
#include "PckReceiver.h"
#include "PckConst.h"
#include "ofMain.h"
#include "ofMath.h"
#include <cstdlib>

void PckReceiver::setup(){
    //serial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
    if(deviceList.size() == 0){
        ofLog(OF_LOG_FATAL_ERROR) << "PckReceiver: no serial / CDC devices found. application abort...\n";
        OF_EXIT_APP(1);
    }
    int baud = 9600;
    if(!serial.setup("/dev/ttyACM0",baud)){
        ofLog(OF_LOG_FATAL_ERROR) << "PckReceiver: could not initialize serial";
        OF_EXIT_APP(1);
    }
    ofLog() << "PckReceiver: established connection to Peacock Hardware";
    clearMatrix(preMatrix);
}

void PckReceiver::clearMatrix(unsigned char* matrix){
    // set all to 0
    for(int i = 0; i < NUM_SENSORS; i++){
        matrix[i] = 0;
    }
}

void PckReceiver::lowPassFilter(unsigned char* currentMatrix, unsigned char* previousMatrix){
    for(int i = 0; i < NUM_SENSORS; i++){
        currentMatrix[i] = (currentMatrix[i] - previousMatrix[i]) * 0.1 + previousMatrix[i];
    }
}

void PckReceiver::noiseGate(unsigned char *matrix){

}

float PckReceiver::calculateCentroid(unsigned char *array, int sizeOfArray){
    float middle = (static_cast<float>(sizeOfArray) - 1.0)/ 2.0;
    float bias, force = 0.0,centroid;
    int sum = 0;

    for(int i = 0; i < sizeOfArray; i++){
        bias = static_cast<float>(i) - middle;
        force += bias * static_cast<float>(array[i]);
        sum += array[i];
    }
    centroid = force / static_cast<float>(sum);
    return centroid;
}

int PckReceiver::matrixDelta(unsigned char* currentMatrix, unsigned char* previousMatrix){
    int delta = 0;
    for(int i = 0; i < NUM_SENSORS; i++){
        delta += abs(currentMatrix[i] - previousMatrix[i]);
    }
    return delta;
}

int PckReceiver::matrixTotal(unsigned char* matrix){
    int total = 0;    
    for(int i = 0; i < NUM_SENSORS; i++){
        total += buffer[i];
    }
    return total;
}

void PckReceiver::threadedFunction(){
    ofLog() << "PckReceiver: thread started";
    while(isThreadRunning()){

        unsigned char byte, type;
        while(serial.available() > 0){ // if there is something in the buffer
            byte = serial.readByte();
            switch(byte){ 
                case 0xFE:{
                    // end delimiter
                    lowPassFilter(buffer, preMatrix);
                    int total = matrixTotal(buffer); // check the total value
                    int delta = matrixDelta(buffer, preMatrix); // check the difference

                    /****** CRITICAL SESSIONS ********/
                    lock();
                        Peacock* peacock = static_cast<Peacock*>(ofGetAppPtr());

                        // get next frame index
                        int nextFrameIndex = (peacock->getFrameIndex() + 1) % NUM_FRAMES;

                        // get a pointer to the frame x in frameData array 
                        PckFrameData* frameDataPtr = peacock->getFrameData(nextFrameIndex);
                        // get a pointer to the matrix in the frameData
                        unsigned char* matrixPtr = frameDataPtr->matrix; 
                        // copy the data in buffer to the matrix in the shared resource
                        memcpy(static_cast<void*>(matrixPtr), static_cast<void*>(buffer), NUM_SENSORS);
                        // set the precalculated total and delta buffer in the shared resource
                        frameDataPtr->totalValue = total; 
                        frameDataPtr->totalDelta = delta;

                        // advance frame index by one
                        peacock->setFrameIndex(nextFrameIndex);
                    unlock();
                    /****** CRITICAL SESSIONS ********/

                    memcpy(static_cast<void*>(preMatrix), static_cast<void*>(buffer), NUM_SENSORS);
                    index = 0;
                    break;
                }
                case 0xFF:{
                    // start delimiter
                    index = 0;  // ensure that buffer is empty
                    break;
                }
                case 0xFD:{
                    type = 0;
                    break;
                }
                default:{
                    buffer[index] = byte;
                    index++;
                }
            }
        }

        Peacock *peacock = static_cast<Peacock*>(ofGetAppPtr());
        PckSynthesizer *synthesizer = peacock->getSynthesizer();
        synthesizer->lock();
        synthesizer->pushNotification(PCK_ENTER);
        synthesizer->unlock();
    }// thread loop

    serial.close();
    ofLog()<< "PckReceiver: connection to Peacock hardware closed.";

}
