#include "messagemanager.h"

#include <unistd.h>
#include <QDebug>

MessageManager::MessageManager()
{

}

MessageManager::~MessageManager()
{

}

void MessageManager::run()
{
    while(true){
        usleep(1000*15000);//1s
        qDebug("MessageManager::run()");
    }
}


void MessageManager::handleMessage(int value)
{
    qDebug("MessageManager::handleMessage");

//    switch (value) {
//    case 0:

//        break;
//    default:
//        break;
//    }
}
