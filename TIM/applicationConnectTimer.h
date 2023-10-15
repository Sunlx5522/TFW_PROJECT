#ifndef APPLICATIONCONNECTTIMER_H
#define APPLICATIONCONNECTTIMER_H


#include <QObject>
#include <QTimer> //定时器装置
class HeartBeat_s : public QObject
{
    Q_OBJECT
public:
    HeartBeat_s(QObject* parent = nullptr);
    ~HeartBeat_s();
private slots:
    void applicationConnection();
    void applicationConnection_s();
    void applicationConnection_f();

private:
    QTimer m_timer;
    QTimer m_timer_s;
    QTimer m_timer_f;
    QTimer * timer=new QTimer;
};
#endif // APPLICATIONCONNECTTIMER_H
