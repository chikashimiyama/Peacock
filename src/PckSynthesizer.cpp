//
//  PckSyntheizer.cpp
//  Peacock
//
//  Created by Chikashi Miyama on 11/22/13.
//
//

#include "PckSynthesizer.h"
#include "ofMain.h"

using namespace pd;

void PckSynthesizer::setup(const int numOutChannels, const int numInChannels,
const int sampleRate, const int ticksPerBuffer, const bool debugMode) {

	if(!pd.init(numOutChannels, numInChannels, sampleRate, ticksPerBuffer)){
		OF_EXIT_APP(1);                                                                                                                                                                                  
	}

	pd.start();
	pd.addReceiver(*this);
	ofLog() << "start patch";
	Patch patch;
	pd.openPatch("pd/osc.pd");
	PckSynthesizer::debugMode = debugMode;
}

void PckSynthesizer::threadedFunction(void){

	while(isThreadRunning()){
		//List testList;
		//testList.addSymbol("left");
		//pd.sendMessage("fromOF", "/notify/recognition/enter", testList);
		lock(); // lock mutex
		while(!notificationQueue.empty()){

			notificationQueue.front();
			notificationQueue.pop();
			pd.sendBang("fromOF");
			ofLog() << "notification poped";
		}
		unlock();
		sleep(1000);// in order to avoid stack over flow in Pd
	}
}

void PckSynthesizer::pushNotification(PCKNotification notification){
	notificationQueue.push(notification);
}

void PckSynthesizer::audioReceived(float * input, int bufferSize, int nChannels){
	pd.audioIn(input, bufferSize, nChannels);
}

void PckSynthesizer::audioRequested(float * output, int bufferSize, int nChannels){
	pd.audioOut(output, bufferSize, nChannels);
}
