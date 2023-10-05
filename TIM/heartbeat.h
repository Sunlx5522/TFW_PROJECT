#ifndef HEARTBEAT_H
#define HEARTBEAT_H
#include <QObject>
#include <QTimer> //定时器装置
#include <QNetworkAccessManager> //网络连接管理
#include <QNetworkReply> //网络回应
class HeartBeat : public QObject
{
    Q_OBJECT
public:
    HeartBeat(QObject* parent = nullptr);
    ~HeartBeat();
private slots:
    void checkNetworkStatus();
private:
    QTimer m_timer;
    QNetworkAccessManager* m_manager;
};
#endif // HEARTBEAT_H
