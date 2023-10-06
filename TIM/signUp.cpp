#include"signUp.h"
#include <QTcpSocket>
#include <QAbstractSocket>
#include "address.h"
#include "widget.h"
extern Widget* loginpage;
extern tfwAddress *tfwaddress;
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
    tcpsocket->connectToHost(tfwaddress->serveRemoteAddress, tfwaddress->port7777);
    //有可读信息，发送readyRead()
    connect(tcpsocket,&QTcpSocket::readyRead,this,&signUp::readMessage);
    connect(tcpsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
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
        loginpage->registerAppend("请等待...");

    }
}

void signUp::handleError()
{
  loginpage->registerAppend("注册失败 网络连接错误");
   qDebug()<<"注册失败 网络连接错误";
   tcpsocket->abort();

}

void signUp::readMessage()
{
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_4);
    qDebug() << "Register::readMessage:读取消息";
    QString greeting;
    QString account;
    QString password;
    //将信息写入greeting读取信息
    in >> greeting;
    //读取的信息
    qDebug() << "Register::readMessage:" << greeting;
    //字符串分割
    QStringList msg = greeting.split("|");
    if(msg[0] == "register"){
        account = msg[1];
        qDebug() << "Register";
        qDebug() << "新账号:"+account;
        QString tmp;
        QString tmp1;
        QString tmp2;
        QString tmp3;
        QString tmp4;
        tmp="您的账号:"+account;
        tmp1="您的密码:"+password1Tmp;
        tmp2="您的密保一:"+passwordq1Temp;
        tmp3="您的密保二:"+passwordq2Temp;
        tmp4="您的密保三:"+passwordq3Temp;
        loginpage->registerAppend("注册成功");
        loginpage->registerAppend(tmp);
        loginpage->registerAppend(tmp1);
        loginpage->registerAppend(tmp2);
        loginpage->registerAppend(tmp3);
        loginpage->registerAppend(tmp4);
    }else{
        loginpage->registerAppend("注册失败");
    }
    qDebug() << "Register::readMessage:读取完成";
}
