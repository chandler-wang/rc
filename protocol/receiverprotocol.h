#ifndef RECEIVERPROTOCOL_H
#define RECEIVERPROTOCOL_H

#include "port/serial.h"

typedef struct sbusPackage{
    unsigned char start;
    unsigned char value[22];
    unsigned char flag;
    unsigned char end;
} sbusPackage_t;

class ReceiverProtocol
{
public:
//    ReceiverProtocol();
//    ~ReceiverProtocol();

public:
    static const int PROTOCOL_SBUS = 0;
    static const int RECEIVER_PROTOCOL = PROTOCOL_SBUS;
    static const int SBUS_STARTBIT = 0x0f;
    static const int SBUS_ENDBIT = 0x00;
    static const int SBUS_BYTES = 25;
    //1个起始位+8个数据位+偶校验位+2个停止位，波特率=100000bit/s
    static const int SBUS_DATABITS = Serial::DATABITS_EIGHT;
    static const int SBUS_PARITY = Serial::PARITY_EVENT;
    static const int SBUS_STOPBITS = Serial::STOPBITS_TWO;
    static const int SBUS_BAUDRATE = 100000; // 100K

public:
    static void parse(char*buf, int *result);
};

#endif // RECEIVERPROTOCOL_H
