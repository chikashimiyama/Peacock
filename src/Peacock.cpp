#include "Peacock.h"
#include "libusb.h"
#include <sstream>

Peacock::~Peacock(){
    closeUSBPort();
}

void Peacock::setup(){

    int ticksPerBuffer = 8;	// 8 * 64 = buffer len of 512
	ofSoundStreamSetup(2, 1, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);

    synthesizer.setup(2,1,44100 ,ticksPerBuffer);
    openUSBPort();
}


//--------------------------------------------------------------
void Peacock::draw(){
    visualizer.draw();
}



bool Peacock::openUSBPort(void){

    // discover devices
    libusb_init(&ctx);
    libusb_set_debug(ctx,3);

    ssize_t cnt = libusb_get_device_list(ctx, &list);
    ssize_t i = 0;
    int err = 0;

    if(cnt == 0){
        ofLog() << "PckDevice: no usb devices found";
        return false;
    }

    ofLog() << "PckDevice: "<< cnt << " usb devices found";

    struct libusb_device_descriptor desc;
    for(i = 0; i < cnt; i++){
        libusb_device *device = list[i];
        libusb_get_device_descriptor( device, &desc );
        if( desc.idVendor == ATMEL_VENDOR_ID && desc.idProduct == MY_PRODUCT_ID ){
            peacock = device;
            break;
        }
    }

    if(!peacock){
        ofLog() << "PckDevice: Peacock not found. check the connection";
    }else{
        ofLog() << "PckDevice: found peacock";
        err = libusb_open(peacock, &handle);
        if (err){
            ofLog() << "PckDevice: unable to open usb device";
        }else{
            ofLog() << "PckDevice: device opened";
        }

        if( libusb_kernel_driver_active(handle,0)){
            ofLog() << "PckDevice: Device busy...detaching...";
            libusb_detach_kernel_driver(handle,0);
            detached = 1;
        }else{
            ofLog() << "PckDevice: device free from karnel" << endl;
        }

        err = libusb_claim_interface( handle, 0 );

        if(err){
            ofLog() << "PckDevice: failed to claim interface";
            switch( err ){
            case LIBUSB_ERROR_NOT_FOUND:
                ofLog() << "PckDevice: interface not found";
                break;
            case LIBUSB_ERROR_BUSY:
                ofLog() << "PckDevice: interface busy";
                break;
            case LIBUSB_ERROR_NO_DEVICE:
                ofLog() << "PckDevice: no device";
                break;
            default:
                ofLog() << "PckDevice: unknown error";
                break;
            }
            return false;
        }
        return true;
    }
    ofLog() << "PckDevice: Interface not found";
    return false;
}

void Peacock::closeUSBPort(void){
    libusb_close( handle );
    libusb_free_device_list(list, 1);
    libusb_exit( ctx );
}

void Peacock::update(void){

    int nTimeout = 100;	//in milliseconds
    int BytesWritten = 0;
    int i;
    unsigned char bufs[8];
    std::ostringstream os;

    libusb_interrupt_transfer( handle, 0x81, bufs, 8, &BytesWritten, nTimeout);
    //ofLog() << "read " <<  BytesWritten << "bytes from endpoint address\n";


    for(i = 0; i< 1; i++){
    int ofs = i*7;static_cast<int>
      os << "Row:" <<
        i << ' ' <<
        static_cast<int>(bufs[ofs]) << ' ' <<
        static_cast<int>(bufs[ofs+1]) << ' ' <<
         static_cast<int>(bufs[ofs+2]) << ' ' <<
        static_cast<int>(bufs[ofs+3]) << ' ' <<
        static_cast<int>(bufs[ofs+4]) << ' ' <<
        static_cast<int>(bufs[ofs+5]) << ' ' <<
        static_cast<int>(bufs[ofs+6]) << '\n';
        ofLog() << os.str();
    }


    unsigned char *offset = &matrix[0][0][0];

    memcpy(offset, bufs, sizeof(unsigned char)*35);
    //ofLog() << "button state" << bufs[35] << "\n";

    if(detached){
        libusb_attach_kernel_driver( handle, 0 );
    }
    visualizer.update(&matrix[0][0][0]);

}

//--------------------------------------------------------------
void Peacock::keyPressed(int key){
    switch(key) {
        case 't':
            break;
        case 's':
            break;
        case 'f':
            fullScreenFlag = !fullScreenFlag;
            ofSetFullscreen(fullScreenFlag);
            break;
    }
}

//--------------------------------------------------------------
void Peacock::keyReleased(int key){

}

//--------------------------------------------------------------
void Peacock::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Peacock::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void Peacock::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void Peacock::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Peacock::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Peacock::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Peacock::dragEvent(ofDragInfo dragInfo){

}

void Peacock::audioReceived(float * input, int bufferSize, int nChannels) {
	synthesizer.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void Peacock::audioRequested(float * output, int bufferSize, int nChannels) {
	synthesizer.audioRequested(output, bufferSize, nChannels);
}
