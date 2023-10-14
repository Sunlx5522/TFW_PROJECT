
#include "initsurface.h"
#include <QTcpServer>
#include<QTcpSocket>
#include<widget.h>
#include <QObject>
#include<QFile>
#include<QTextStream>
#include "userlist.h"
#include "address.h"
extern CurrentUser* currentuser;
extern tfwAddress* tfwaddress;
InitSurface::InitSurface()
{
    tcpServerConnect();
}


void InitSurface::tcpServerConnect()
{
    //实例化socket
    tcpsocket = new QTcpSocket;
    //断开现有连接
    tcpsocket->abort();
    //连接到远端的7777端口
    tcpsocket->connectToHost(tfwaddress->serveRemoteAddress,tfwaddress->port7777);
    //有可读信息，发送readyRead()
    connect(tcpsocket,&QTcpSocket::readyRead,this,&InitSurface::readMessage);

}

void InitSurface::readMessage()
{
    //实例化套接字的输入流，读信息
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_14);
    qDebug() << "InitSurface::readMessage:读取消息";
    QString greeting;
    //将信息写入greeting读取信息
    in >> greeting;
    //字符串分割
    QStringList msg = greeting.split("|");
    if(msg[1]==myAccount)
    {
    if(msg[0] == "initSurface"){


    currentuser->account=msg[1];
    currentuser->name=msg[2];
    currentuser->password=msg[3];
    currentuser->sign=msg[4];
    currentuser->headImage=msg[5];
    currentuser->phoneNumber=msg[6];
    currentuser->birthDay=msg[7];
    currentuser->localPlace=msg[8];
    currentuser->Tagt=msg[9];
    currentuser->VIP_Level=msg[10];


    {
    QString fileName = QCoreApplication::applicationDirPath();
            //用户目录
    QString add = "//..//TFWUserFile";
            //创建用户文件夹
    fileName = fileName + add +QString("//%1").arg(myAccount);
            //信息保存
    QDir * file = new QDir;
            //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
    bool exist_1 = file->exists(fileName);
    if(exist_1)
    {
        qDebug()<<"已存在";
        QFile file(fileName +"//data.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
        {
            QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
            out << currentuser->account<<"\n";
            out << currentuser->name<<"\n";
            out << currentuser->password<<"\n";
            out << currentuser->sign<<"\n";
            out << currentuser->headImage<<"\n";
            out << currentuser->phoneNumber<<"\n";
            out << currentuser->birthDay<<"\n";
            out << currentuser->localPlace<<"\n";
            out << currentuser->Tagt<<"\n";
            out << currentuser->VIP_Level<<"\n";
        }
        file.close();

    }
    else
    {
        bool ok = file->mkpath(fileName);
                    if(ok)
                    {
                        {
                        QFile file(fileName +"//data.txt");
                        if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                        {
                            QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
                            out << currentuser->account<<"\n";
                            out << currentuser->name<<"\n";
                            out << currentuser->password<<"\n";
                            out << currentuser->sign<<"\n";
                            out << currentuser->headImage<<"\n";
                            out << currentuser->phoneNumber<<"\n";
                            out << currentuser->birthDay<<"\n";
                            out << currentuser->localPlace<<"\n";
                            out << currentuser->Tagt<<"\n";
                            out << currentuser->VIP_Level<<"\n";
                        }
                        file.close();
                        }

                        {
                        QFile file(fileName +"//requests.txt");
                        if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                        {
                            ;
                        }
                        file.close();
                        }

                        {
                        QFile file(fileName +"//friends.txt");
                        if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                        {
                            ;
                        }
                        file.close();
                        }

                        {
                        QFile file(fileName +"//groups.txt");
                        if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                        {
                            ;
                        }
                        file.close();
                        }


                    }
                    else
                    {
                        qDebug()<<"未创建成功";
                    }

    }
    }




    }else if(msg[0] == "register"){
          ;
    }
    msg.clear();
    qDebug() << "InitSurface::readMessage:读取完成";
    }
    else
    {

        ;
    }
}


void InitSurface::setAccount(QString account)
{
    qDebug() << "InitSurface::setAccount" <<account;
    myAccount = account;
}

void InitSurface::sendMessage(QString Msg)
{
    qDebug() << "InitSurface::sendMessage:发送消息";
    if(Msg == "initSurface"){
        //初始化界面
        QString string = "initSurface|" + myAccount;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "InitSurface::sendMessage:" << string;
        //发送信息
        tcpsocket->write(message);
    }else if(Msg == "register"){
        //注册
        qDebug() << "InitSurface::sendMessage:" << "register";
    }
    qDebug() << "InitSurface::sendMessage:发送完成";
}

InitSurface::~InitSurface()
{
    ;
}
