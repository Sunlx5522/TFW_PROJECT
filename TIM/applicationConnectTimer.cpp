#include "applicationConnectTimer.h"
#include"address.h"
#include "mainwindow.h"

#include <QDebug>
extern tfwAddress* tfwaddress;
extern MainWindow *mainwindow;

extern QTcpSocket *client1_s;
HeartBeat_s::HeartBeat_s(QObject* parent) :
    QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &HeartBeat_s::applicationConnection);
    m_timer.start(60000);  // 每5秒检查一次
    connect(&m_timer_s, &QTimer::timeout, this, &HeartBeat_s::applicationConnection_s);
    m_timer_s.start(10000);  // 每3秒检查一次
    connect(&m_timer_f, &QTimer::timeout, this, &HeartBeat_s::applicationConnection_f);
    m_timer_f.start(20);  // 每5秒检查一次
}
void HeartBeat_s::applicationConnection()
{

    if(mainwindow==nullptr)
    {

    }
    else
    {
    if(mainwindow->is_open)
    {
      mainwindow->appConnect();
      client1_s->abort();
      client1_s->connectToHost(tfwaddress->serveRemoteAddress,tfwaddress->port7777);
      mainwindow->updateApplication();


       //qDebug()<<"修改成功";
    }
    else
    {
        ;
    }
    }

}

void HeartBeat_s::applicationConnection_s()
{

    if(mainwindow==nullptr)
    {

    }
    else
    {
    if(mainwindow->is_open)
    {
     if(mainwindow->updateFlag)
     {
        mainwindow->updateItem();
        mainwindow->updateFlag=false;
     }
     else
     {
        ;
     }

    }
    else
    {
        ;
    }
    }

}

void HeartBeat_s::applicationConnection_f()
{
    if(mainwindow==nullptr)
    {

    }
    else
    {
    if(mainwindow->is_open)
    {

        mainwindow->readMessage_application();




    }
    else
    {
        ;
    }
    }
}

HeartBeat_s::~HeartBeat_s()
{
 ;
}

