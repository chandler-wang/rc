#include "ithread.h"

QMap<QObject*, QThread*> *IThread::map = new QMap<QObject*, QThread*>();

IThread::IThread()
{

}

IThread::~IThread()
{

}

void IThread::addToMap(QObject* obj, QThread* thread)
{
    map->insert(obj, thread);
}

QMap<QObject*, QThread*> *IThread::getMap(void)
{
    return map;
}
