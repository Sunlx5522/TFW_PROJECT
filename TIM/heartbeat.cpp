#include "heartbeat.h"
#include"address.h"
#include"widget.h"
extern Widget* ww;

extern QString internetRemoteAddress;
extern QString serveRemoteAddress;

HeartBeat::HeartBeat(QObject* parent) :
    QObject(parent),
    m_manager(new QNetworkAccessManager(this))
{
    connect(&m_timer, &QTimer::timeout, this, &HeartBeat::checkNetworkStatus);
    m_timer.start(1000);  // 每秒检查一次
}

void HeartBeat::checkNetworkStatus()
{
    QNetworkReply* reply = m_manager->get(QNetworkRequest(QUrl(internetRemoteAddress)));
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            if (statusCode == 200) {
                 ww->networkAbleFlag=true;
            } else {
                 ww->networkAbleFlag=false;
            }
        } else {
            ww->networkAbleFlag=false;
        }
        reply->deleteLater();
        ww->networkStationUpdate();
    });
}


