#pragma once

#include "PckConst.h"
#include "ofMain.h"
#include "PckVisualizer.h"
#include "PckSynthesizer.h"
#include "PckRecognizer.h"
#include "PckReceiver.h"

class Peacock : public ofBaseApp{

    bool fullScreenFlag, statusFlag;

    unsigned char matrix[BUFFER_SIZE * NUM_ROWS * NUM_COLUMNS]; /**<  the 3D data with history */

    PckVisualizer visualizer; /**< an instance of visualizer */
    PckRecognizer recognizer; /**< an instance of data recognizer */
    PckSynthesizer synthesizer; /**< an instance of synthesizer */
    PckReceiver receiver;

    bool forwarding; /**< OSC forwarding flag */
    bool detached;

public:
    ~Peacock();

    /*! get newinfo from the device if any and notify the update
    to the sound engin*/
    void update(void);

    void draw(void);
    void toggleStatus(void);

    void setup();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioReceived(float * input, int bufferSize, int nChannels);
    void audioRequested(float * output, int bufferSize, int nChannels);

};
