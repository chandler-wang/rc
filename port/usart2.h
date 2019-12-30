#ifndef USART2_H
#define USART2_H

#include "serial.h"
#include "message/ithread.h"

#include <QThread>

#define USART2_DEVNAME ("/dev/ttySAC1")

class USART2 : public Serial
{

public:
    USART2();
    ~USART2();

public:
    static USART2* getInstance(void);
    void initSerialPort(int dataBits, int parity, int stopBits, int baud);
    void run(void);
    void getData(char* buf);

private:
    void saveData(char* src, int len);

private:
    char deviceName[30];
    char txBuf[1024];
    char rxBuf[1024];
    static USART2* s_pInstance;
    static QThread* thread;

    QMutex rxBufMutex;
};

#endif // USART2_H
