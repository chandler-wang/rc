#include "usart2.h"

#include <stdio.h>
#include <string.h>

USART2::USART2()
{

}

USART2::USART2(int dataBits, int parity, int stopBits, int baud)
{
    initSerialPort(dataBits, parity, stopBits, baud);
}

USART2::~USART2()
{
    initFD();

    memset(txBuf, 0, 1024);
    memset(rxBuf, 0, 1024);
}

void USART2::initSerialPort(int dataBits, int parity, int stopBits, int baud)
{
    initFD();
    setDataBits(dataBits);
    setParity(parity);
    setStopBits(stopBits);
    setBaudrate(baud);

    memset(deviceName, 0, 30);
    memcpy(deviceName, USART2_DEVNAME, strlen(USART2_DEVNAME));
    setDevName(deviceName);

    memset(txBuf, 0, 1024);
    memset(rxBuf, 0, 1024);

    flush(Serial::FLUSH_RX|Serial::FLUSH_RX);
}
