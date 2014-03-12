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
#include <queue>
#include "ofxPd.h"
#include "ofxOsc.h"
#include "PckConst.h"

using namespace pd;

/**
 * @brief Interface to Synthesizer
 * @details This class is a interface between the Peacock system and Pure Data synthesizer engin. 
 * This class is implemented with @b Singleton design pattern, the instatiation of multiple instances is not allowed
 * @note For debugging propose, it has a ofxOSCSender instance for sending OSC message to Pure Data. 
 * To turn on the test mode set the flag @p debugMode to true.
 * @author Chikashi Miyama
 */

class PckSynthesizer : public PdReceiver, public ofThread{

private:
    ofxPd pd;	/*! an instance of pure data engin*/
    ofxOscSender oscSender; /*< for non-integrated application*/
	bool debugMode; /*! if this is true, end OSC Message to the designated port on the localhost*/

	//shared buffer//
	queue<PCKNotification> notificationQueue;

	//singleton
	PckSynthesizer(){} //< not allowed to instantiate with constructor
	PckSynthesizer(const PckSynthesizer& synth); //< copy constructor is also not allowed
	PckSynthesizer& operator=(const PckSynthesizer& synth); //< copy with = operator not allowed

public:

	/**
	 * @brief return a pointer to the unique instance
	 * @details this is the only way to access the unique instance of this class. 
	 * the instantiation occurs the first time this function is called.
	 * @return a pointer to the unique instance
	 */
	inline static PckSynthesizer* getInstance(void);

    /**
     * @brief send data to Pure Data continuously
     * @details Overrided function from PdReceiver. setting up audio properties
     * 
     * @param numOutChannels number of audio out channels
     * @param numInChannels number of audio in channels
     * @param sampleRate sample rate
     * @param ticksPerBuffer ticks per buffer. default 64 
     * @param debugMode if this is true, send OSC message to port 12040 and does not activate internal Pd
     */
    	
    void setup(const int numOutChannels, const int numInChannels,
				   const int sampleRate, const int ticksPerBuffer, const bool debugMode );
    /**
     * @brief add a queue to notification queue
     * @details this function contains a critical session and lock the thread while pushing
     * @param notification a notification to be pushed
     */
    void pushNotification( PCKNotification notification );

    /**
     * @brief threaded function
     * @details overrided function from ofThread
     */
    void threadedFunction();

    /**
     * @brief this function forward the audio data to Pd
     */
    void audioReceived(float * input, int bufferSize, int nChannels);

    /**
     * @brief this function forward the audio data from Pd
     */
    void audioRequested(float * output, int bufferSize, int nChannels);
};

PckSynthesizer *PckSynthesizer::getInstance(void){
	static PckSynthesizer synthesizer;
	return &synthesizer;
}

#endif /* defined(__Peacock__PckSyntheizer__) */
