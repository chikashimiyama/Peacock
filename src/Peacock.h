#ifndef __Peacock__Peacock__
#define __Peacock__Peacock__

#include "ofMain.h"

#include "PckConst.h"
#include "PckFrameData.h"
#include "PckVisualizer.h"
#include "PckSynthesizer.h"
#include "PckRecognizer.h"
#include "PckReceiver.h"

/**
 * @brief the main hub class for the Peacock SYstem
 * @details This class is a central hub of the entire system and holds instances of synthesizer and visualizer.
 * 
 */
class Peacock : public ofBaseApp{

private:
    bool fullScreenFlag, statusFlag;

    /**
     *  @defgroup shared memory
     *  @{
     */

    PckFrameData frameData[NUM_FRAMES];
    int frameIndex; /**< the newest matrix recorded */
    
    /**
     *  @}
     */

    PckVisualizer visualizer; /**< an submodule of this class. runs in this thread */
    PckSynthesizer synthesizer; /**< an instance of PckSynthesizer */
    PckReceiver receiver; /**< an instance of PckReceiver */

    bool forwarding; /**< OSC forwarding flag */
    bool detached;

public:

    /**
     * @brief deconstructor
     * @details this ensures to stop all thread before exiting
     */
    ~Peacock();

    inline PckFrameData* getFrameData(int frame);
    inline int getFrameIndex();
    inline void setFrameIndex(int newFrameIndex);
    inline PckSynthesizer* getSynthesizer();

    //inline static bool isInstantiated();
    /*! get newinfo from the device if any and notify the update
    to the sound engin*/
    void update(void);

    void draw(void);
    void toggleStatus(void);

    void setup();

    void keyPressed(int key);
  
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested(float * output, int bufferSize, int nChannels);

};

PckFrameData* Peacock::getFrameData(int frame){
    return &frameData[frame];
}

int Peacock::getFrameIndex(){
    return frameIndex;
}

void Peacock::setFrameIndex(int newFrameIndex){
    frameIndex = newFrameIndex;
}

PckSynthesizer* Peacock::getSynthesizer(){
    return &synthesizer;
}
#endif


