#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HeartBeat : public QObject
{
    Q_OBJECT
public:
    HeartBeat(QObject* parent = nullptr);

private slots:
    void checkNetworkStatus();

private:
    QTimer m_timer;
    QNetworkAccessManager* m_manager;
};

#endif // HEARTBEAT_H
