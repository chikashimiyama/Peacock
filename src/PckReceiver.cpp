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
    testMode = false;
    serialbufferVector.reserve(128); // 128byte allocate
}

void PckReceiver::setup(){
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

    int bt;
    bt = serial.readByte();
    if(bt == OF_SERIAL_ERROR){
        ofLog(OF_LOG_WARNING) << "PckReceiver: Serial error detected.";
    }else if(bt == OF_SERIAL_NO_DATA){
        ofLog(OF_LOG_WARNING) << "PckReceiver: No data received";
    }else{
        ofLog() << bt;
    }
}
