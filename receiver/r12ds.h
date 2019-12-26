#ifndef R12DS_H
#define R12DS_H

#include <QObject>
#include "receiver/receiver.h"

class R12DS : public QObject, public IReceiver
{
public:
    R12DS();
    ~R12DS();

    void receive(char* buf, int len);
    int getPWM(int channel);
};

#endif // R12DS_H
