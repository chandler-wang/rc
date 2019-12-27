#ifndef USART2_H
#define USART2_H

#include "serial.h"

//#include <QObject>

#define USART2_DEVNAME ("/dev/ttySAC1")

//class USART2 : public QObject, public Serial
class USART2 : public Serial
{
public:
    USART2();
    USART2(int dataBits, int parity, int stopBits, int baud);
    ~USART2();

public:
    void initSerialPort(int dataBits, int parity, int stopBits, int baud);

private:
    char deviceName[30];
    char txBuf[1024];
    char rxBuf[1024];
};

#endif // USART2_H
