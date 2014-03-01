#ifndef PCKSERIAL_H
#define PCKSERIAL_H

#include <ofSerial.h>


class PckSerial : public ofSerial
{
    public:
    bool setup(string portName, int baud);
};

#endif // PCKSERIAL_H
