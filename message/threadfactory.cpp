#include "threadfactory.h"

ThreadFactory::ThreadFactory()
{

}

void ThreadFactory::startThreads()
{
    QMap<QObject*, QThread*> *map = IThread::getMap();

}

void ThreadFactory::stopAndDeleteThreads()
{

}
