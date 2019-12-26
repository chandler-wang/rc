#ifndef RECEIVER_H
#define RECEIVER_H


class IReceiver
{
public:
    virtual ~IReceiver()=0;

    virtual void receive(char* buf, int len)=0;
};

IReceiver::~IReceiver()
{

}

#endif // RECEIVER_H
