//
//  PckScene.cpp
//  Peacock
//
//  Created by Chikashi Miyama on 11/4/13.
//
//

#include "PckScene.h"

PckScene::PckScene(){
    receiver.setMatrix(&matrix[0][0][0]);
    visualizer.setRecognizer(&recognizer);
}

PckScene::~PckScene(){
}

void PckScene::update(){
    receiver.update();
    recognizer.update(&matrix[0][0][0]);
    visualizer.update(&matrix[0][0][0]);
}

void PckScene::draw(){
    visualizer.draw();
}

void PckScene::toggleStatus(){
    visualizer.toggleStatus();
}

