#include"signUp.h"
#include <QTcpSocket>

extern QString internetRemoteAddress;
extern QString serveRemoteAddress;


extern QString nameTmp;
extern QString password1Tmp;
extern QString password2Tmp;
extern QString phoneNumberTmp;
extern QString signTemp;

extern QString birthdayDate;
extern QString localPlaceTemp;
extern QString passwordq1Temp;
extern QString passwordq2Temp;
extern QString passwordq3Temp;

extern QString headImageTemp;

signUp::signUp()
{
    tcpsocket = new QTcpSocket;
}

signUp::~signUp()
{
    delete tcpsocket;
}

void signUp::tcpServerConnect()
{
    delete tcpsocket;
    tcpsocket = nullptr;
    //实例化socket
    tcpsocket = new QTcpSocket;
    //断开现有连接
    tcpsocket->abort();
    //连接到本地的7777端口
    tcpsocket->connectToHost(serveRemoteAddress, 55418);
    //有可读信息，发送readyRead()
    connect(tcpsocket,&QTcpSocket::readyRead,this,&signUp::readMessage);
}

void signUp::sendMessage(QString Msg)
{
    if(Msg == "register"){
        //初始化界面
        QString string = "register|" + nameTmp+"|"+password1Tmp+"|"+phoneNumberTmp+"|"+signTemp+"|"+birthdayDate+"|"+localPlaceTemp+"|"+passwordq1Temp+"|"+passwordq2Temp+"|"+passwordq3Temp+"|"+headImageTemp;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        out << string;
        qDebug()<<string;
        tcpsocket->write(message);
    }
}
void signUp::readMessage()
{
;
}
