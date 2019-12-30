#include "serial.h"
#include "global.h"

#include <stdio.h>      /* Standard input/output */
#include <fcntl.h>      /* File control definitions */
#include <string.h>
#include <stdlib.h>
#include <termio.h>     /* POSIX terminal control definitions */
#include <sys/time.h>   /* Time structures for select() */
#include <unistd.h>     /* POSIX Symbolic Constants */
#include <assert.h>
#include <errno.h>      /* Error definitions */
#include <sys/mman.h>

///////////////////////////////
#include <sched.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
//#include <unistd.h>
//#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <strings.h>
///////////////////////////////

#define  CMSPAR 010000000000

//Serial::Serial()
//{

//}

Serial::~Serial()
{

}

void Serial::printBuf(char *buf, int len)
{
    int i;
    for(i=0;i<len;i++)
        printf("%02X ",buf[i]);
    printf("\n");
}

void Serial::initFD(void)
{
    fd = -1;
}

void Serial::setDataBits(int dataBits)
{
    this->dataBits = dataBits;
}

void Serial::setParity(int parity)
{
    this->parity = parity;
}

void Serial::setStopBits(int stopBits)
{
    this->stopBits = stopBits;
}

void Serial::setBaudrate(int baudrate)
{
    this->baudrate = baudrate;
}

void Serial::setDevName(char* name)
{
    this->devName = name;
}

int Serial::termiosInit(struct termios *tios)
{
    if (tios == NULL)
        return FAIL;

    tios->c_line  = 0;
    tios->c_cc[VMIN ] = 0;
    tios->c_cc[VTIME] = 0;
    tios->c_iflag =  IGNBRK | IGNPAR | INPCK; /* configure the input modes... */

    /* configure the output modes... */
    tios->c_oflag = 0;     /* enable implementation-defined output processing */
    tios->c_cflag = CREAD | CLOCAL; /* configure the control modes... */

    switch (dataBits) {
        case 5:
            tios->c_cflag |= CS5;
            break;
        case 6:
            tios->c_cflag |= CS6;
            break;
        case 7:
            tios->c_cflag |= CS7;
            break;
        case 8:
            tios->c_cflag |= CS8;
            break;
        default:
            return FAIL;
    }

    if (stopBits == 1)
        tios->c_cflag &=~ CSTOPB;
    else if (stopBits == 2)
        tios->c_cflag |= CSTOPB;
    else
        return FAIL;

    switch (parity) {
        case 0: /* none */
            tios->c_cflag &=~ PARENB;
            tios->c_cflag &=~ PARODD;
            break;
        case 1:/* odd */
            tios->c_cflag |= PARENB;
            tios->c_cflag |= PARODD;
            break;
        case 2: /* even */
            tios->c_cflag |= PARENB;
            tios->c_cflag &=~ PARODD;
            break;
        case 3: /* mark */
            tios->c_cflag |= PARENB;
            tios->c_cflag |= CMSPAR;
            tios->c_cflag |= PARODD;
            break;
        case 4: /* space */
            tios->c_cflag |= PARENB;
            tios->c_cflag |= CMSPAR;
            break;
        default:
            return FAIL;
    }

    /* configure the local modes... */
    tios->c_lflag = 0;    /* enable implementation-defined input processing   */

    speed_t speed;
    /* Set the baud rate */
    switch(baudrate)
    {
        case 110:
            speed = B110;
            break;
        case 300:
            speed = B300;
            break;
        case 600:
            speed = B600;
            break;
        case 1200:
            speed = B1200;
            break;
        case 2400:
            speed = B2400;
            break;
        case 4800:
            speed = B4800;
            break;
        case 9600:
            speed = B9600;
            break;
        case 19200:
            speed = B19200;
            break;
        case 38400:
            speed = B38400;
            break;
        case 57600:
            speed = B57600;
            break;
        case 115200:
            speed = B115200;
            break;
        case 230400:
            speed = B230400;
            break;
        case 460800:
            speed = B460800;
            break;
        case 576000:
            speed = B576000;
            break;
        case 921600:
            speed = B921600;
            break;

        default:
            return FAIL;
    }

    if ((cfsetispeed(tios, speed) < 0) ||(cfsetospeed(tios, speed) < 0))
        return FAIL;

    return OK;
}

//设置波特率，比如28800, 100000
void Serial::setSpecifiedBaudrate(int baudrate)
{
    int   status;
    struct termios   Opt;
    struct serial_struct serialStruct;

    tcgetattr(fd, &Opt);
    tcflush(fd, TCIOFLUSH);
    qDebug("\ncfsetispeed(&Opt,B38400)\n");

    cfsetispeed(&Opt, B38400);
    cfsetospeed(&Opt, B38400);
    tcflush(fd,TCIOFLUSH);
    status = tcsetattr(fd, TCSANOW, &Opt);
    if  (status != 0)
    {
        perror("tcsetattr fd1");
        return;
    }

    if((ioctl(fd,TIOCGSERIAL, &serialStruct))<0)
    {
        qDebug("Fail to get Serial!\n");
        return;
    }

    qDebug("TIOCGSERIAL: OK.\n");
    serialStruct.flags = ASYNC_SPD_CUST;
    serialStruct.custom_divisor=serialStruct.baud_base/baudrate;
    qDebug("divisor is %x\n",serialStruct.custom_divisor);
    if((ioctl(fd,TIOCSSERIAL,&serialStruct))<0)
    {
        qDebug("Fail to set Serial\n");
        return;
    }

    qDebug("TIOCSSERIAL: OK.\n");
    ioctl(fd,TIOCGSERIAL,&serialStruct);
    qDebug("\nBAUD: success set baud to %d,custom_divisor=%d,baud_base=%d\n",baudrate,serialStruct.custom_divisor,serialStruct.baud_base);
}

/*
 * return serial fd, error return -1
 */
int Serial::openPort(void)
{
    struct termios settings;
    struct termios old_tios;
    int fd_tmp;
    int ret = FAIL;

    fd_tmp = fd;
    if (fd_tmp >= 0)
        return ret;

    qDebug("openPort: 1.");
    if (termiosInit(&settings)<0)
    {
//        char warning[100];
//        sprintf(warning, "port%d, termios_init error", si->portNumber);
//        LogRecord::getInstance()->record(warning);
//        qDebug(warning);
        return ret;
    }

//    serial_dev_name = get_serial_dev_name();
    //qDebug("serial_port_node: %s", serial_dev_name);
    //if (serial_dev_name == NULL)

    qDebug("openPort: 2.");
    if (devName == NULL)
    {
//        char warning[100];
//        sprintf(warning, "invalid serial port:%d\n", si->portNumber);
//        LogRecord::getInstance()->record(warning);
//        qDebug(warning);
        return ret;
    }

    qDebug("openPort: 3.");
    if((fd_tmp = open(devName, O_RDWR | O_NOCTTY | O_NDELAY))< 0) // 非阻塞
    {
//        char warning[100];
//        sprintf(warning, "open %s error", serial_dev_name);
//        LogRecord::getInstance()->record(warning);
//        qDebug(warning);
        return ret;
    }

    qDebug("openPort: 4.");
    if(tcgetattr(fd_tmp, &old_tios) < 0)
    {
//        char warning[100];
//        sprintf(warning, "%s tcgetattr error", serial_dev_name);
//        LogRecord::getInstance()->record(warning);
//        qDebug(warning);
        close(fd_tmp);
        return ret;
    }

    qDebug("openPort: 5.");
    if(tcsetattr(fd_tmp, TCSANOW, &settings) < 0)
    {
//        char warning[100];
//        sprintf(warning, "%s tcsetattr error", serial_dev_name);
//        LogRecord::getInstance()->record(warning);
//        qDebug(warning);
        close(fd_tmp);
        return ret;
    }

    fd = fd_tmp;
    ret = OK;

    qDebug("openPort: final ok.");
    return ret;
}

int Serial::closePort(void)
{
    struct termios old_tios;
    int fd_tmp = fd;

    if (fd_tmp < 0)
        return FAIL;

    tcsetattr(fd_tmp, TCSANOW, &old_tios);
    close(fd_tmp);
    fd = -1;

    return OK;
}

int Serial::flush(int flag)
{
    int fd_tmp = fd;

    if (fd_tmp < 0)
        return FAIL;

    switch (flag) {
        case FLUSH_TX:
            tcflush(fd_tmp,TCOFLUSH);
            break;
        case FLUSH_RX:
            tcflush(fd_tmp,TCIFLUSH);
            break;
        case (FLUSH_RX|FLUSH_TX):
            tcflush(fd_tmp,TCIOFLUSH);
            break;
    }

    return OK;
}

int Serial::readData(char* rxBuffer, int bytes)
{
    int recvBytes = -1;
    Q_UNUSED(bytes);

    QMutexLocker locker(&rxMutex);
    if (fd < 0)
        return recvBytes;

    recvBytes = read(fd, rxBuffer, BUFFER_LENGTH);

    return recvBytes;
}

int Serial::writeData(char *txBuffer, int bytes)
{
    int writesize = -1;

    QMutexLocker locker(&txMutex);
    if (fd < 0)
        return writesize;

    writesize = write(fd, txBuffer, bytes);

    return writesize;
}
