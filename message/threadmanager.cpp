#include "threadmanager.h"
#include "ithread.h"
#include "receiver/receiver.h"
#include "port/serial.h"

#include <unistd.h>
#include <QThread>
#include <QMap>

ThreadManager::ThreadManager()
{
//    usart2 = USART2::getInstance();
//    usart2->initSerialPort(Serial::DATABITS_EIGHT, Serial::PARITY_NO, Serial::STOPBITS_ONE, Serial::BAUD_115200);
    receiver = new Receiver;
    receiver->init(Serial::DATABITS_EIGHT, Serial::PARITY_NO, Serial::STOPBITS_ONE, Serial::BAUD_115200);

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

void ThreadManager::doOperation(signal_data_t *sd)
{
    qDebug("ThreadManager::doOperation");

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
