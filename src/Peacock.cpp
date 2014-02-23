#include "Peacock.h"

//--------------------------------------------------------------
void Peacock::setup(){

}

//--------------------------------------------------------------
void Peacock::update(){
    scene.update();


}

//--------------------------------------------------------------
void Peacock::draw(){

}

//--------------------------------------------------------------
void Peacock::keyPressed(int key){
    switch(key) {
        case 't':
            break;
        case 's':
            scene.toggleStatus();
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
