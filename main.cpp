#include <QCoreApplication>
#include "usbserial.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UsbSerial mySerial(5760,"/dev/ttyUSB0");
    UsbSerial mySerial2(5760,"/dev/ttyUSB1");
    char ping_cmd[] = {2,1};
    char ping_cmd2[] = {3,4};
    char ping_rec[20];

    write(mySerial.usb_file,&ping_cmd,sizeof(ping_cmd));
    close(mySerial.usb_file);

    memset(ping_rec,0,sizeof (ping_rec));
    write(mySerial2.usb_file,&ping_cmd2,sizeof(ping_cmd2));
    read(mySerial2.usb_file,&ping_rec,sizeof(ping_rec));
    int m=0;

    for(int i=0;i<sizeof (ping_rec);i++){
        if(ping_rec[i]!=0){
            m++;
        }
    }
    if(m!=0){
        for(int j=0;j<m;j++){
            qDebug() << ping_rec[j];
        }
    }
    close(mySerial2.usb_file);
    return a.exec();
}
