#ifndef __Peacock__PckReceiver__
#define __Peacock__PckReceiver__

#include <vector>
#include "PckSerial.h"
#include "PckSynthesizer.h"
#include "ofThread.h"
#include "PckCentroid.h"

/**
 * @brief CDC Interface to Peacock Hardware
 * @details This class uses ofSerial to communicate with Peacock Hardware.
 * This class is implemeted with the Singleton design pattern and has its own thread
 * Usually this thread receives data of sensors more than 1000 time per seconds and
 * cooks the received value with lowpass fiter and hysteresis
 */
class PckReceiver: public ofThread, public PckCentroid{

private:
    unsigned char buffer[200];
    unsigned char preMatrix[41];
    unsigned char index;
    PckSerial serial;

    int matrixTotal(unsigned char* matrix);
	int matrixDelta(unsigned char* currentMatrix, unsigned char* previousMatrix);

	void lowPassFilter(unsigned char* currentMatrix, unsigned char* previousMatrix);
	void noiseGate(unsigned char* matrix);
	void clearMatrix(unsigned char* matrix);
public:

	/**
	 * @brief return a pointer to the unique instance(singleton)
	 * @details this is the only way to access the unique instance of this class. 
	 * the instantiation occurs the first time this function is called.
	 * @return a pointer to the unique instance
	 */

    void setup();
    void threadedFunction();



};


#endif /* defined(__Peacock__PckReceiver__) */
