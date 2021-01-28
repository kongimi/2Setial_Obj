#ifndef USBSERIAL_H
#define USBSERIAL_H

#include <QObject>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<termio.h>
#include <linux/serial.h>
#include <QString>

class UsbSerial : public QObject
{
    Q_OBJECT
public:
    explicit UsbSerial(int baud, const char *path,QObject *parent = nullptr);
    int usb_file;
    static int rate_to_constant(int baudrate) {
    #define B(x) case x: return B##x
            switch(baudrate) {
            B(50);     B(75);     B(110);    B(134);    B(150);
            B(200);    B(300);    B(600);    B(1200);   B(1800);
            B(2400);   B(4800);   B(9600);   B(19200);  B(38400);
            B(57600);  B(115200); B(230400); B(460800); B(500000);
            B(576000); B(921600); B(1000000);B(1152000);B(1500000);
        default: return 0;
        }
    #undef B
    }

signals:

public slots:
};

#endif // USBSERIAL_H
