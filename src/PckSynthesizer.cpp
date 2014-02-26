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
const int sampleRate, const int ticksPerBuffer) {

	if(!pd.init(numOutChannels, numInChannels, sampleRate, ticksPerBuffer)){
		OF_EXIT_APP(1);
	}

	pd.start();
	pd.addReceiver(*this);

	ofLog()<<"start patch";

	Patch patch;
	pd.openPatch("pd/osc.pd");

}

void PckSynthesizer::audioReceived(float * input, int bufferSize, int nChannels){
	pd.audioIn(input, bufferSize, nChannels);
}

void PckSynthesizer::audioRequested(float * output, int bufferSize, int nChannels){
	pd.audioOut(output, bufferSize, nChannels);
}
