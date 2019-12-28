#ifndef THREADMANAGER_H
#define THREADMANAGER_H

//#include <QObject>
//#include <QVector>

#include "global.h"
#include "receiver/receiver.h"

class ThreadManager : public QObject
{
    Q_OBJECT

public:
    ThreadManager();
    ~ThreadManager();

private:
    void startThreads(void);
    void stopAndDestroyThreads(void);

public slots:
    void doOperation(signal_data_t *sd);

private:
    Receiver* receiver;
};

#endif // THREADMANAGER_H
