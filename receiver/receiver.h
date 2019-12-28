#ifndef RECEIVER_H
#define RECEIVER_H

#include "port/port.h"

#include <QObject>

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver();
    ~Receiver();
    void init (int dataBits, int parity, int stopBits, int baud);

public slots:
    void run();

private:
    IPort *port;
    QThread* thread;
};

#endif // RECEIVER_H
