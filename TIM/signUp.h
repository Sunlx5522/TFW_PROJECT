#ifndef SIGNUP_H
#define SIGNUP_H

#include <QTcpSocket>
#include<QWidget>

class signUp: public QWidget
{
    Q_OBJECT

public:
    signUp();
    ~signUp();
     QTcpSocket *tcpsocket;
     void sendMessage(QString Msg);              //向服务器发送信息
     void readMessage();                         //读取服务器信息
     void tcpServerConnect();                    //连接服务器
};

#endif // SIGNUP_H
