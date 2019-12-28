#ifndef SERIAL_H
#define SERIAL_H

#include "port.h"

#include <QMutex>
#include <QObject>

class Serial : public QObject, public IPort
{
    Q_OBJECT
public:
//    Serial();
    virtual ~Serial();

public:
    static const int  DATABITS_FIVE   = 5;
    static const int  DATABITS_SIX    = 6;
    static const int  DATABITS_SEVEN  = 7;
    static const int  DATABITS_EIGHT  = 8;

    static const int  PARITY_NO       = 0;
    static const int  PARITY_ODD      = 1;
    static const int  PARITY_EVENT    = 2;
    static const int  PARITY_MARK     = 3;
    static const int  PARITY_SPACE    = 4;

    static const int  STOPBITS_ONE     = 1;
    static const int  STOPBITS_TWO     = 2;

    static const int  BAUD_9600        = 9600;
    static const int  BAUD_115200      = 115200;

    static const int  FLUSH_RX          = 1;
    static const int  FLUSH_TX          = 2;
    static const int  BUFFER_LENGTH     = 1024;


public:
    int openPort(void);
    int closePort(void);
    int readData(char* rxBuffer, int bytes);
    int writeData(char* txBuffer, int bytes);
    int flush(int flag);

public slots:
    virtual void run()=0;

protected:
    virtual void initSerialPort(int dataBits, int parity, int stopBits, int baud)=0;

    void initFD();
    void setDataBits(int dataBits);
    void setParity(int parity);
    void setStopBits(int stopBits);
    void setBaudrate(int baudrate);
    void setDevName(char* name);

    void printBuf(char *buf, int len);

private:
    int termiosInit(struct termios *tios); // int parity, int data_bits, int stop_bits);

private:
    int fd;
    int dataBits;
    int parity;
    int stopBits;
    int baudrate;

    char* devName; //[30] = {'\0'}; //char devName[30]={'\0'}

    QMutex rxMutex;
    QMutex txMutex;
};

#endif // SERIAL_H


#if 0
#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QMutex>
#include <QLabel>

#include <termios.h>
#include <unistd.h>



/*
 *  ------------------------------good
 *
#define ELECTRIC_TABLE_PORTNUMBER       6//1 // com1: ttl->rs485
#define ELECTRIC_TABLE_PORTFILENAME     ("/dev/ttySAC6")

#define GPS_PORTNUMBER                  3 // com3: rs232
#define GPS_PORTFILENAME                ("/dev/ttySAC3")

#define INCLINOMETER_PORTNUMBER         1//6 // com6: ttl
#define INCLINOMETER_PORTFILENAME       ("/dev/ttySAC1")

#define SERIAL4_BCK_PORTNUMBER          4   // com4
#define SERIAL7_BCK_PORTNUMBER          7   // com7
*/

// com1: 485, com3: rs232, com4: rs232, com6: ttl
#define TESTPORT_PORTNUMBER       6 // com6: ttl, 9600, used for test INCLINOMETER port
#define TESTPORT_PORTFILENAME     ("/dev/ttySAC6")

//#define GPS_PORTNUMBER                  3 // com3: rs232
//#define GPS_PORTFILENAME                ("/dev/ttySAC3")




#define GPS_PORTNUMBER                  3 // com3: rs232
#define GPS_PORTFILENAME                ("/dev/ttySAC3")


#if 0

#define INCLINOMETER_PORTNUMBER         1 // com1: 485
#define INCLINOMETER_PORTFILENAME       ("/dev/ttySAC1")

#define ELECTRIC_TABLE_PORTNUMBER          4 // com1: 485  // com4: 232
#define ELECTRIC_TABLE_PORTFILENAME       ("/dev/ttySAC4")

#else
#define INCLINOMETER_PORTNUMBER         4 // com1: 485
#define INCLINOMETER_PORTFILENAME       ("/dev/ttySAC4")

#define ELECTRIC_TABLE_PORTNUMBER          1 // com1: 485  // com4: 232
#define ELECTRIC_TABLE_PORTFILENAME       ("/dev/ttySAC1")
#endif



#define SERIAL7_BCK_PORTNUMBER          7   // com7:ttl

#define BUFFER_LENGTH       1024
#define DEFAULT_BAUDRATE    115200 // gps

#define INCLINOMETER_BAUDRATE    9600 // 485
#define TESTPORT_BAUDRATE    9600 // 485

#define ELECTRICTABLE_BAUDRATE    115200 //57600 // 9600

typedef struct serial_info
{
    int portNumber;         // 当前串口号
    char sendBuf[BUFFER_LENGTH];
    char recvBuf[BUFFER_LENGTH];
    int sendLength;        // 实际发送字节数
    int recvLength;        // 实际接收字节数
    bool sendDataIsReady;  // 发送数据准备好，可以发数据
    bool recvReady;         // 接收数据ok
    QMutex sendBufMutex;    // 发送数据的锁
    QMutex recvBufMutex;    // 接收数据的锁
    bool stop;              // 退出标志

}serial_info_t;

class Serial : public QObject
{
    Q_OBJECT

public:
    Serial();
    Serial(int number, int baud);
    ~Serial();

public:
    void set_portNumber(int number);
    int serial_open(int parity,int data_bits,int stop_bits); //,int timeout);
    int serial_close(void);
    int serial_flush(int flag);
    int serial_write(void);
    int serial_read(void);
    int serial_poll(int timeout);

signals:

public slots:
    //void doOperation(void);

private:
    char* get_serial_dev_name(void);
    int termios_init(struct termios *tios, int parity,int data_bits,int stop_bits);
    void serial_print_buf(char *buf, int len);

protected:
    int fd;
    int baudrate;
    serial_info_t *si;

private:
    struct termios old_tios;
};

void serial_exit_enable(int number);
void fill_serialSendBuf(int number, char *buf, int length);
int get_serialReceivedData(int number, char *buf);
void display_serialReceivedData(int number, QLabel *label);

void get_serialNBytes(int number, char *buf, int length);
int get_InclinometersData(float *x, float *y);


#endif // SERIAL_H
#endif
