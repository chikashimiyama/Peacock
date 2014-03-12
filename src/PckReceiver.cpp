//
//  PckReceiver.cpp
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#include "PckReceiver.h"
#include "PckConst.h"
#include "ofMain.h"
#include "ofMath.h"

PckReceiver::PckReceiver(){

}

void PckReceiver::setup(unsigned char *matrix){
    serial.listDevices();
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

    PckReceiver::matrix = matrix;
}


void PckReceiver::threadedFunction(){
    ofLog() << "thread started";
    while(isThreadRunning()){

        unsigned char byte, type;
        while(serial.available() > 0){ // if there is something in the buffer
            byte = serial.readByte();
            switch(byte){ // end delimeter
                case 0xFE:

                    lock();
                        // critical session
                        memcpy((void*)matrix, (void*)buffer, 35);
                    unlock();

                    index = 0;
                    break;
                case 0xFF:
                    index = 0;  // ensure that buffer is empty
                    break;
                case 0xFD:
                    type = 0;
                    break;
                default:
                    buffer[index] = byte;
                    index++;
            }

        }

        PckSynthesizer* synthesizer = PckSynthesizer::getInstance(); // singleton
        ofLog() << "notification pushed";
        //synthesizer->lock();
        //synthesizer->pushNotification(PCK_ENTER);
        //synthesizer->unlock();
    }// thread loop

}
