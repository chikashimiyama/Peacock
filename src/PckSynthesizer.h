//
//  PckSyntheizer.h
//  Peacock
//
//  Created by Chikashi Miyama on 11/22/13.
//
//

#ifndef __Peacock__PckSyntheizer__
#define __Peacock__PckSyntheizer__

#include <iostream>
#include "ofxPd.h"
using namespace pd;

class PckSynthesizer : PdReceiver{

    ofxPd pd;

public:
    void setup(const int numOutChannels, const int numInChannels,
				   const int sampleRate, const int ticksPerBuffer);

	// audio callbacks
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested(float * output, int bufferSize, int nChannels);


};

#endif /* defined(__Peacock__PckSyntheizer__) */
