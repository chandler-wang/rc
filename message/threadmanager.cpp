#include "threadmanager.h"
#include "ithread.h"
#include "receiver/receiver.h"
#include "port/serial.h"

#include <unistd.h>
#include <QThread>
#include <QMap>

#include <stdio.h>

ThreadManager::ThreadManager()
{
//    usart2 = USART2::getInstance();
//    usart2->initSerialPort(Serial::DATABITS_EIGHT, Serial::PARITY_NO, Serial::STOPBITS_ONE, Serial::BAUD_115200);
    receiver = new Receiver;
    //receiver->init(Serial::DATABITS_EIGHT, Serial::PARITY_NO, Serial::STOPBITS_ONE, Serial::BAUD_115200);
    receiver->init(Serial::DATABITS_EIGHT, Serial::PARITY_EVENT, Serial::STOPBITS_TWO, Serial::BAUD_115200);

    startThreads();
}

ThreadManager::~ThreadManager()
{

}

void ThreadManager::startThreads(void)
{
    QMap<QObject*, QThread*> *map = IThread::getMap();

    for(QMap<QObject*, QThread*>::ConstIterator iter=map->constBegin(); iter!=map->constEnd(); ++iter){
        QObject* obj = iter.key();
        QThread* thread = iter.value();

        obj->moveToThread(thread);
        thread->start();
    }
}

void ThreadManager::stopAndDestroyThreads(void)
{
    QMap<QObject*, QThread*> *map = IThread::getMap();

    for(QMap<QObject*, QThread*>::ConstIterator iter=map->constBegin(); iter!=map->constEnd(); ++iter){
        QObject* obj = iter.key();
        QThread* thread = iter.value();

//        obj->exit_enable();

        usleep(1000*10);

        if (thread)
        {
            if (thread->isRunning())
            {
                thread->quit();
                thread->wait();
            }

//            if (gpio)
//            {
//                disconnect(gpio_thread, SIGNAL(started()), gpio, SLOT(gpio_doOperation()));
//                disconnect(gpio_thread, SIGNAL(finished()), gpio, SLOT(gpio_postHandle()));
//            }

            delete thread;
            thread = NULL;
        }
        if (obj)
        {
            delete obj;
            obj = NULL;
        }
    }
}

void ThreadManager::parse(char*buf, int *result)
{
    result[ 0] = (buf[ 1] | (buf[2] << 8)) &0x07ff;                                     //!< Channel 0
    result[ 1] = ((buf[ 2] >> 3) | (buf[3] << 5)) &0x07ff;                              //!< Channel 1
    result[ 2] = ((buf[ 3] >> 6) | (buf[4] << 2) | (buf[5] << 10)) &0x07ff;  //!< Channel 2 			油门通道
    result[ 3] = ((buf[ 5] >> 1) | (buf[6] << 7)) &0x07ff;    							//!< Channel 3
    result[ 4] = ((buf[ 6] >> 4) | (buf[7] << 4)) &0x07ff;    							//!< Channel 4
    result[ 5] = ((buf[ 7] >> 7) | (buf[8] << 1) | (buf[9] << 9)) &0x07ff;	//!< Channel 5
    result[ 6] = ((buf[ 9] >> 2) | (buf[10] << 6)) &0x07ff;								//!< Channel 6
    result[ 7] = ((buf[10] >> 5) | (buf[11] << 3)) &0x07ff;								//!< Channel 7
    result[ 8] = (buf[12] | (buf[13] << 8)) &0x07ff;									//!< Channel 8
    result[ 9] = ((buf[13] >> 3) | (buf[14] << 5)) &0x07ff;								//!< Channel 9
    result[10] = ((buf[14] >> 6) | (buf[15] << 2) | (buf[16] << 10)) &0x07ff;//!< Channel 10
    result[11] = ((buf[16] >> 1) | (buf[17] << 7)) &0x07ff;								//!< Channel 11
    result[12] = ((buf[17] >> 4) | (buf[18] << 4)) &0x07ff;								//!< Channel 12
    result[13] = ((buf[18] >> 7) | (buf[19] << 1) | (buf[20] << 9)) &0x07ff;	//!< Channel 13
    result[14] = ((buf[20] >> 2) | (buf[21] << 6)) &0x07ff;								//!< Channel 14
    result[15] = ((buf[21] >> 5) | (buf[22] << 3)) &0x07ff;								//!< Channel 15

    for (int i = 0; i < 16; i++){
        printf("%d ", result[i]);
        if (i == 7)
            printf("\n");
    }
    printf("\n");
}

void ThreadManager::doOperation(signal_data_t *sd)
{
    Q_UNUSED(sd);
    qDebug("ThreadManager::doOperation");


//    RX：0F E0 03 1F 58 C0 07 16 B0 80 05 2C 60 01 0B F8 C0 07 00 00 00 00 00 03 00
//    CH: 992 992 352 992 352 352 352 352 352 352 992 992 000 000 000 000
//    RX：0F 60 01 0B 58 C0 07 66 30 83 19 7C 60 06 1F F8 C0 07 00 00 00 00 00 03 00
//    CH: 352 352 352 992 1632 1632 1632 992 1632 992 992 992 000 000 000 000

    char buf[25] = {0x0F, 0xE0, 0x03, 0x1F, 0x58,
                    0xC0, 0x07, 0x16, 0xB0, 0x80,
                    0x05, 0x2C, 0x60, 0x01, 0x0B,
                    0xF8, 0xC0, 0x07, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x03, 0x00};

    char buf1[25] = {0x0F, 0x60, 0x01, 0x0B, 0x58,
                    0xC0, 0x07, 0x66, 0x30, 0x83,
                    0x19, 0x7C, 0x60, 0x06, 0x1F,
                    0xF8, 0xC0, 0x07, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x03, 0x00};

    int result[16];

    parse(buf, result);
    parse(buf1, result);

//    int index = 0;

//    if (sd)
//    {
//        index = sd->index; //TABLEBAR_SELECT
//        //qDebug("Thread_Manager::doOperation, command:%d", index);
//    }
//    else
//    {
//        qDebug("sd is NULL.");

//        return;
//    }

//    switch (index)
//    {
//        case 0:
//        {}
//        break;
//    }
}
