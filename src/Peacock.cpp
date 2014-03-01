#include "Peacock.h"
#include "libusb.h"
#include <sstream>

Peacock::~Peacock(){

}

void Peacock::setup(){

    int ticksPerBuffer = 8;	// 8 * 64 = buffer len of 512
	ofSoundStreamSetup(2, 1, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);

    synthesizer.setup(2,1,44100 ,ticksPerBuffer);
    receiver.setup();
}


//--------------------------------------------------------------
void Peacock::draw(){
    visualizer.draw();
}



void Peacock::update(void){

    unsigned char *offset = &matrix[0][0][0];

    receiver.update();
    visualizer.update(&matrix[0][0][0]);

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
	synthesizer.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void Peacock::audioRequested(float * output, int bufferSize, int nChannels) {
	synthesizer.audioRequested(output, bufferSize, nChannels);
}
