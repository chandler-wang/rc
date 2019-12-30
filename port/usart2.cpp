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
//    int result = 0;
    if(!s_pInstance)
    {
        s_pInstance = new USART2;
        thread = new QThread((QObject*)s_pInstance);        
        IThread::addToMap((QObject*)s_pInstance, thread);
    }    

    connect(thread, SIGNAL(started()), s_pInstance, SLOT(run()));
//    result = s_pInstance->openPort();
//    qDebug("USART2* USART2::getInstance: openPort() = %d", result);

    return s_pInstance;
}

void USART2::run()
{
    char buf[1024];
    memset(buf, 0, 1024);

    while(true){
        usleep(1);
        //qDebug("Hello, usart2 ");
        //writeData("hello, world\n", strlen("hello, world\n"));

        if (readData(buf, 1024) > 0){
            qDebug("%s", buf);
            memset(buf, 0, 1024);
        }

    }
}
