#ifndef INITSURFACE_H
#define INITSURFACE_H

#include <QWidget>
#include <QObject>
#include <QtNetwork>
#include <QTcpSocket>
#include <QStringList>


class InitSurface:public QObject
{

  Q_OBJECT

public:
    InitSurface();
    ~InitSurface();
    void setAccount(QString account);
    //network
    QTcpSocket *tcpsocket;
    //使用者
    QString myAccount;
    //临时信息

    void sendMessage(QString Msg);              //向服务器发送信息
    void readMessage();                         //读取服务器信息
    void tcpServerConnect();                    //连接服务器
    QString getAccount(QString account);        //得到账号
};




#endif // INITSURFACE_H
