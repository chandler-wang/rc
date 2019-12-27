#include "receiver.h"

#include "port/serial.h"
#include "port/usart2.h"

//USART2(int dataBits, int parity, int stopBits, int baud);
Receiver::Receiver()
{
    port = new USART2(Serial::DATABITS_EIGHT, Serial::PARITY_NO, Serial::STOPBITS_ONE, Serial::BAUD_115200);

}

Receiver::~Receiver()
{
    if(port) {
        delete port;
    }
}

