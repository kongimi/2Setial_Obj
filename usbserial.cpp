#include "usbserial.h"
#include <QDebug>

UsbSerial::UsbSerial(int baud, const char *path, QObject *parent) : QObject(parent)
{
    struct termios options;
    struct serial_struct serinfo;
    int fd;
    int speed = 0;
    int rate = baud;

    /* Open and configure serial port */
    if ((fd = open(path,O_RDWR|O_NOCTTY)) == -1)
    {
        qDebug() << "niran0";
    }else{
        qDebug() << path << " ok";
    }

    // if you've entered a standard baud the function below will return it
    speed = rate_to_constant(rate);

    if (speed == 0) {
        /* Custom divisor */
        serinfo.reserved_char[0] = 0;
        if (ioctl(fd, TIOCGSERIAL, &serinfo) < 0)
            qDebug() << "niran1";
        serinfo.flags &= ~ASYNC_SPD_MASK;
        serinfo.flags |= ASYNC_SPD_CUST;
        serinfo.custom_divisor = (serinfo.baud_base + (rate / 2)) / rate;
        if (serinfo.custom_divisor < 1)
            serinfo.custom_divisor = 1;
        if (ioctl(fd, TIOCSSERIAL, &serinfo) < 0)
            qDebug() << "niran2";
        if (ioctl(fd, TIOCGSERIAL, &serinfo) < 0)
            qDebug() << "niran3";
        if (serinfo.custom_divisor * rate != serinfo.baud_base) {
//            qDebug("actual baudrate is ");
//            qDebug() << serinfo.baud_base;
//            qDebug() << serinfo.custom_divisor;
//            qDebug() << (float)serinfo.baud_base / serinfo.custom_divisor;
        }
    }

    fcntl(fd, F_SETFL, 0);
    tcgetattr(fd, &options);
    cfsetispeed(&options, speed ?: B38400);
    cfsetospeed(&options, speed ?: B38400);
    cfmakeraw(&options);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= PARENB;
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        qDebug() << "niran4";
    }
    usb_file = fd;
}
