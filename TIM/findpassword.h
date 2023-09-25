#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include <QWidget>
#include <QTcpSocket>
#include <QCloseEvent>

namespace Ui {
class findpassword;
}

class findpassword : public QWidget
{
    Q_OBJECT

public:
    explicit findpassword(QWidget *parent = nullptr);
    ~findpassword();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::findpassword *ui;
    //network
    QTcpSocket *tcpsocket;
    QString myAccount;
    QString passwordp1;
    QString passwordp2;
    QString passwordp3;
    QString newpassword1;
    QString newpassword2;
signals:
    void sendFindClose(bool);
private slots:
    void sendMessage(QString Msg);              //向服务器发送信息
    void readMessage();                         //读取服务器信息
    void tcpServerConnect();                    //连接服务器
};

#endif // FINDPASSWORD_H
