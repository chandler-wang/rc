#include "usart2.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

USART2* USART2::s_pInstance = NULL;
QThread* USART2::thread = NULL;

USART2::USART2()
{
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

//    flush(Serial::FLUSH_RX|Serial::FLUSH_RX);
}

USART2* USART2::getInstance(void)
{
    if(!s_pInstance)
    {
        s_pInstance = new USART2;
        thread = new QThread((QObject*)s_pInstance);        
        IThread::addToMap((QObject*)s_pInstance, thread);
    }    

    connect(thread, SIGNAL(started()), s_pInstance, SLOT(run()));

    return s_pInstance;
}

void USART2::run()
{
    int len = 0;
    char buf[1024];

    memset(buf, 0, 1024);

    while(true){
        usleep(1);

        //qDebug("Hello, usart2 ");
        //writeData("hello, world\n", strlen("hello, world\n"));

        memset(buf, 0, 1024);
        len = readData(buf, 1024);
        if (len > 0){
            saveData(buf, len);
        }
    }
}

void USART2::saveData(char* src, int len)
{
    QMutexLocker locker(&rxBufMutex);
    memset(rxBuf, 0, 1024);
    memcpy(rxBuf, src, len);
}

void USART2::getData(char* buf)
{
    QMutexLocker locker(&rxBufMutex);
    memset(buf, 0, 1024);
    memcpy(buf, rxBuf, 1024);
    memset(rxBuf, 0, 1024);
}
