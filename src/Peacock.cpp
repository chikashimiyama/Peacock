#include "Peacock.h"
#include <sstream>

Peacock::~Peacock(){

    if(receiver.isThreadRunning()){
        receiver.stopThread();
        ofLog() << "Peacock: receiver thread stopped";
    }

    if(synthesizer.isThreadRunning()){
        synthesizer.stopThread();
        ofLog() << "Peacock: synthesizer thread stopped";
    }
}

void Peacock::setup(){
    int ticksPerBuffer = 8;	// 8 * 64 = buffer len of 512
	ofSoundStreamSetup(2, 1, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
    synthesizer.setup(2,1,44100 ,ticksPerBuffer, false);
    receiver.setup();
    visualizer.setup();

    // start thread;
    receiver.startThread(true, false);
    synthesizer.startThread(true, false);
}

//--------------------------------------------------------------
void Peacock::draw(){
    visualizer.draw();
}

void Peacock::update(void){
    unsigned char *offset = &matrix[0];
    receiver.lock();
    visualizer.update();
    receiver.unlock();
}

//--------------------------------------------------------------
void Peacock::keyPressed(int key){
    switch(key) {
        case 't':{
            break;
        }
        case 's':{
            break;
        }
        case 'f':{
            fullScreenFlag = !fullScreenFlag;
            ofSetFullscreen(fullScreenFlag);
            break;
        }
        case 'q':{
            synthesizer.stopThread();
            receiver.stopThread();

            break;
        }
    }
}


void Peacock::audioReceived(float * input, int bufferSize, int nChannels) {
	synthesizer.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void Peacock::audioRequested(float * output, int bufferSize, int nChannels) {
	synthesizer.audioRequested(output, bufferSize, nChannels);
}
