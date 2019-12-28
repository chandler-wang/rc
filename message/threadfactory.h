#ifndef THREADFACTORY_H
#define THREADFACTORY_H

#include "message/ithread.h"

class ThreadFactory
{
public:
    ThreadFactory();

    void startThreads();
    void stopAndDeleteThreads();
};

#endif // THREADFACTORY_H
