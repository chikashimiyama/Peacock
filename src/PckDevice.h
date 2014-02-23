

#ifndef __Peacock__PckDevice__
#define __Peacock__PckDevice__

#include "ofMain.h"
#include "PckConst.h"
#include "PckVisualizer.h"
#include "PckReceiver.h"
#include "PckRecognizer.h"
#include "PckSyntheizer.h"

#include "libusb.h"

/*!
    This class receives data from Peacock hardware and notify update to
    other classes.
*/
class PckDevice{

private:

    unsigned char matrix[BUFFER_SIZE][NUM_ROWS][NUM_COLUMNS]; /**<  the 3D data with history */

    PckVisualizer visualizer; /**< an instance of visualizer */
    PckRecognizer recognizer; /**< an instance of data recognizer */
    PckSyntheizer synthesizer; /**< an instance of synthesizer */

    /*!
    @{
        @name libusb
    */
    libusb_context *ctx;
    libusb_device **list;
    libusb_device *peacock; /**< pointer to peacock */
    libusb_device_handle *handle; /**< usb interface handler */
    /*!
    @}
    */
    bool forwarding; /**< OSC forwarding flag */
    bool detached;

public:
    PckDevice();
    ~PckDevice();

    /*! attempts to open USB Port, return false if fails */
    bool openUSBPort(void);

    /*! close the connection to the peacock hardware*/
    void closeUSBPort(void);

    /*! get newinfo from the device if any and notify the update
    to the sound engin*/
    void update(void);

    void draw(void);
    // visualize
    void toggleStatus(void);

    // send data to receiver


};

#endif /* defined(__Peacock__PckDevice__) */
