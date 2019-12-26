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
        usleep(1000*1000);//1s
        qDebug("MessageManager::run()");
    }
}
