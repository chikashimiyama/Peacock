#include "Peacock.h"
#include "PckReceiver.h"
#include "PckConst.h"
#include "ofMain.h"
#include "ofMath.h"

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
}

void PckReceiver::threadedFunction(){
    ofLog() << "thread started";
    while(isThreadRunning()){

        unsigned char byte, type;
        while(serial.available() > 0){ // if there is something in the buffer
            byte = serial.readByte();
            switch(byte){ // end delimeter
                case 0xFE:{
                    lock();
                        Peacock* peacock = static_cast<Peacock*>(ofGetAppPtr());
                        void* matrix = static_cast<void*>(peacock->getMatrix());
                        memcpy(matrix, static_cast<void*>(buffer), 35);
                    unlock();
                    index = 0;
                    break;
                }
                case 0xFF:{
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
