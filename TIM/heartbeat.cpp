#include "heartbeat.h"
#include"address.h"
#include"widget.h"
extern Widget* loginpage;
extern tfwAddress* tfwaddress;
HeartBeat::HeartBeat(QObject* parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this))
{
    connect(&m_timer, &QTimer::timeout, this, &HeartBeat::checkNetworkStatus);
    m_timer.start(1000);  // 每秒检查一次
}
void HeartBeat::checkNetworkStatus()
{
    QNetworkReply* reply = m_manager->get(QNetworkRequest(QUrl(tfwaddress->internetRemoteAddress)));
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (statusCode == 200) {
                 loginpage->networkAbleFlag=true;
            } else {
                 loginpage->networkAbleFlag=false;
            }
        } else {
            loginpage->networkAbleFlag=false;
        }
        reply->deleteLater();
        loginpage->networkStationUpdate();
    });
}

HeartBeat::~HeartBeat()
{
    delete m_manager;
    qDebug()<<"delete heart";
}

