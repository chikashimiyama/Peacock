#ifndef __Peacock__Peacock__
#define __Peacock__Peacock__

#include "PckConst.h"
#include "ofMain.h"
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

    unsigned char matrix[BUFFER_SIZE * NUM_ROWS * NUM_COLUMNS]; /**<  the 3D data with history */

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

    inline unsigned char* getMatrix();
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

unsigned char* Peacock::getMatrix(){
    return matrix;
}

PckSynthesizer* Peacock::getSynthesizer(){
    return &synthesizer;
}
#endif