#include "heartbeat.h"
#include "userlist.h"
#include"widget.h"
extern UserList * user;
extern Widget* loginpage;
HeartBeat::HeartBeat(QObject* parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this))
{
    connect(&m_timer, &QTimer::timeout, this, &HeartBeat::checkNetworkStatus);
    m_timer.start(20);  // 每秒检查100次
}

void HeartBeat::checkNetworkStatus()
{
    QNetworkReply* reply = m_manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (statusCode == 200) {
                if(loginpage->listenFlag_news)
                {
                  loginpage->duxinxi();
                }
                 loginpage->networkAbleFlag=true;
            } else {
                 loginpage->networkAbleFlag=false;


            }
        } else {
            loginpage->networkAbleFlag=false;


        }
        reply->deleteLater();
    });
}


HeartBeat1::HeartBeat1(QObject* parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this))
{
    connect(&m_timer, &QTimer::timeout, this, &HeartBeat1::checkTageStatus);
    m_timer.start(60000);  // 每秒检查一次
}


void HeartBeat1::checkTageStatus()
{
   user->tageUpdate();
}
