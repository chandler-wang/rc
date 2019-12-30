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

    void parse(char*buf, int *result);

public slots:
    void doOperation(signal_data_t *sd);

private:
    Receiver* receiver;
};

#endif // THREADMANAGER_H
