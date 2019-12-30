#include "receiver.h"

#include "port/serial.h"
#include "port/usart2.h"

#include <unistd.h>

Receiver::Receiver()
{
    port = USART2::getInstance();
}

Receiver::~Receiver()
{
    if(port) {
        delete port;
    }
}

void Receiver::init (int dataBits, int parity, int stopBits, int baud)
{
    ((USART2*)port)->initSerialPort(dataBits, parity, stopBits, baud);
    thread = new QThread(this);
    IThread::addToMap(this, thread);
    connect(thread, SIGNAL(started()), this, SLOT(run()));

    qDebug("Receiver::init: openPOrt=%d", ((USART2*)port)->openPort());

    ((USART2*)port)->setSpecifiedBaudrate(100000); // 100K
}

void Receiver::run()
{
    while(true){
        sleep(10);
        qDebug("Hello, Receiver");
    }
}
