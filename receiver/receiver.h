#ifndef RECEIVER_H
#define RECEIVER_H

#include "port/port.h"

#include <QObject>

class Receiver : public QObject
{
public:
    Receiver();
    ~Receiver();

private:
    IPort *port;

//    virtual void receive(char* buf, int len)=0;
};

//IReceiver::~IReceiver()
//{

//}

#endif // RECEIVER_H
