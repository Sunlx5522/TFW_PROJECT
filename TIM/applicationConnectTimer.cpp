#include "applicationConnectTimer.h"
#include"address.h"
#include "mainwindow.h"
#include "widget.h"
#include <QDebug>
extern tfwAddress* tfwaddress;
extern MainWindow *mainwindow;
extern Widget* loginpage;
extern QTcpSocket *client1_s;
HeartBeat_s::HeartBeat_s(QObject* parent) :
    QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &HeartBeat_s::applicationConnection);
    m_timer.start(20000);  // 每20秒检查一次
    connect(&m_timer_s, &QTimer::timeout, this, &HeartBeat_s::applicationConnection_s);
    m_timer_s.start(500);  // 每0.5秒检查一次
    connect(&m_timer_f, &QTimer::timeout, this, &HeartBeat_s::applicationConnection_f);
    m_timer_f.start(10);  // 每5秒检查一次
    connect(&m_timer_ff, &QTimer::timeout, this, &HeartBeat_s::applicationConnection_ff);
    m_timer_ff.start(1500);  // 每5秒检查一次
    //connect(&m_timer_fff, &QTimer::timeout, this, &HeartBeat_s::applicationConnection_fff);
    //m_timer_fff.start(5000);  // 每5秒检查一次
}
void HeartBeat_s::applicationConnection()
{



    if(loginpage->isMainWindowOpen)
    {
      mainwindow->appConnect();
      client1_s->abort();
      client1_s->connectToHost(tfwaddress->serveRemoteAddress,tfwaddress->port7777);
      mainwindow->updateApplication();
      delete timer;
      timer=new QTimer;
      QObject::connect(timer, &QTimer::timeout, [&]() {
          if(loginpage->isMainWindowOpen)
          {
              if(mainwindow->zha)
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

          }
          else
          {
              ;
          }
            qDebug() << "3秒后执行的函数";
            timer->stop();
          });
       timer->setSingleShot(true); // 如果只需要执行一次，设置为 true
       timer->start(3000);


       //qDebug()<<"修改成功";
    }
    else
    {
        ;
    }


}

void HeartBeat_s::applicationConnection_s()
{

     if(loginpage->isMainWindowOpen)
    {
     if(mainwindow->zha)
     {
         qDebug() << "开闸---";
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
    if(loginpage->isMainWindowOpen)
    {

        mainwindow->readMessage_application();
    }
    else
    {
        ;
    }
    }
}

void HeartBeat_s::applicationConnection_ff()
{
    if(mainwindow==nullptr)
    {

    }
    else
    {
    if(loginpage->isMainWindowOpen)
    {
      if(mainwindow->xinhao)
      {
          qDebug() << "信号已激活---";
          if(mainwindow->xinzha)
          {
              qDebug() << "应对当前页面进行刷新---";
              //刷新函数
              mainwindow->zhixing();
              mainwindow->xinzha=false;
          }
      }
      else
      {

      }

    }
    else
    {
        ;
    }
    }
}







void HeartBeat_s::applicationConnection_fff()
{
    if(mainwindow==nullptr)
    {

    }
    else
    {
    if(loginpage->isMainWindowOpen)
    {
      if(mainwindow->xinhao)
      {
          qDebug() << "信号已激活---";
          qDebug() << "应对当前页面进行刷新---";
              //刷新函数
          mainwindow->zhixing();

      }
      else
      {

      }

    }
    else
    {
        ;
    }
    }
}





HeartBeat_s::~HeartBeat_s()
{
    if(timer)
    {
 delete timer;
    }
}

