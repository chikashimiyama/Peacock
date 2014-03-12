#include "Peacock.h"
#include <sstream>

Peacock::~Peacock(){
    receiver.stopThread();
}

void Peacock::setup(){

    int ticksPerBuffer = 8;	// 8 * 64 = buffer len of 512
	ofSoundStreamSetup(2, 1, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);

    synthesizer = PckSynthesizer::getInstance();
    synthesizer->setup(2,1,44100 ,ticksPerBuffer, false);
    receiver.setup(matrix);
    visualizer.setup(matrix);

    receiver.startThread(true, false);
    synthesizer->startThread(true, false);
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
        case 't':
            break;
        case 's':
            break;
        case 'f':
            fullScreenFlag = !fullScreenFlag;
            ofSetFullscreen(fullScreenFlag);
            break;
    }
}

//--------------------------------------------------------------
void Peacock::keyReleased(int key){

}

//--------------------------------------------------------------
void Peacock::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Peacock::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Peacock::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Peacock::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Peacock::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Peacock::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Peacock::dragEvent(ofDragInfo dragInfo){

}

void Peacock::audioReceived(float * input, int bufferSize, int nChannels) {
	synthesizer->audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void Peacock::audioRequested(float * output, int bufferSize, int nChannels) {
	synthesizer->audioRequested(output, bufferSize, nChannels);
}
