#ifndef PORT_H
#define PORT_H

//#include <QObject>

class IPort //: public QObject
{
//    Q_OBJECT

public:
    virtual ~IPort();

    virtual int openPort()=0;
    virtual int closePort()=0;
    virtual int readData(char* rxBuffer, int bytes)=0;
    virtual int writeData(char* txBuffer, int bytes)=0;
//    virtual void Package(char* data)=0;
//    virtual void unPackage(void)=0;
};

//IPort::~IPort()
//{}

#endif // PORT_H
