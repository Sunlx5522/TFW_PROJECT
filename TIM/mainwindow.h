 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>                                                   //阴影添加
#include <QPoint>
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QTcpSocket>
#include <QEvent>
#include "userlist.h"
#include<QHBoxLayout>
#include <QFont>
#include <QPixmap>
#include <QPainter>
# include <QWidget>
#include <QPainterPath>
#include <QDate>
#include <QThread>
# include <QListWidgetItem>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateApplication();
    void updateItem();
    void mousePressEvent(QMouseEvent *event) override                                 //实现窗口拖动
    {
        if (event->button() == Qt::LeftButton)
        {
            lastDragPos = event->globalPos();                                         //记录初始位置
            event->accept();                                                          //防止误触
        }
        else
        {
            event->ignore();                                                          //防止误触
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override                                  //实现窗口拖动
    {
        if (event->buttons() & Qt::LeftButton)
        {
            //计算鼠标移动的距离

            int dx = event->globalX() - lastDragPos.x();
            int dy = event->globalY() - lastDragPos.y();

            //设置动画的起始位置和结束位置

            animation2->setStartValue(pos());
            animation2->setEndValue(pos() + QPoint(dx, dy));

            //启动动画 不采用move重绘 减小cpu负担 将任务交给显卡

            animation2->start();
            lastDragPos = event->globalPos();
            event->accept();                                                          //防止误触

        }
        else
        {
            event->ignore();                                                          //防止误触
        }
    }
    QString changeFlag="0";
    QString changeFlag_s="0";
    bool isValidDate(const QString &dateStr);
    void setplacehodetext(QLineEdit*);
    void setplacehodetextRed(QLineEdit*);
    void changeMessage();
    void shenqingPage(const MyRequsest& friendData);
    void haoyouPage(const MyFriend& friendData);
    void chatPage(const MyFriend& friendData,MyMessages&);
    bool updateFlag=false;
    bool zha=false;
    bool xinzha=false;
    bool xinhao=false;
    void zhixing();
    bool readAccountsAndDisplay(const QString &filePath);
    void appConnect()
    {
        tcpServerConnect_application();
    }
    bool eventFilter(QObject *obj, QEvent *event); //自定义一些Qlable的点击实现


    void updaTe(void)
    {
       readMessage_application();
    }
    QTcpSocket *tcpsocket;

    QTcpSocket *tcpsocket_s;

    QTcpSocket *tcpsocket_application;

    QString applicationOperation;

    void readMessage_application();                         //读取服务器信息
private slots:
    void sendMessage(QString Msg);              //向服务器发送信息
    void readMessage();                         //读取服务器信息
    void tcpServerConnect();                    //连接服务器
    void handleError();

    void sendMessage_s(QString Msg);              //向服务器发送信息
    void readMessage_s();                         //读取服务器信息
    void tcpServerConnect_s();                    //连接服务器
    void handleError_s();

    void sendMessage_application(QString Msg);              //向服务器发送信息

    void tcpServerConnect_application();                    //连接服务器
    void handleError_application();




private:
    Ui::MainWindow *ui;
    QPropertyAnimation *animation1;                                                   //启动动画
    QPropertyAnimation *animation2;                                                   //拖动动画
    QPropertyAnimation *animation3;                                                   //关闭动画
    QPropertyAnimation *animation4;                                                   //关闭动画
    QPoint lastDragPos;                                                               //记录上次拖拽的位置
    QGraphicsDropShadowEffect *shadow_effect1;
    QGraphicsDropShadowEffect *shadow_effect2;
    QThread* thread;
    QThread* thread1;
    QThread* thread2;
    QTimer *timer1=new QTimer;
    QTimer *timer2=new QTimer;
    QTimer *timer3=new QTimer;
    QTimer *timer4=new QTimer;
    QTimer *timer5=new QTimer;

};

class FriendWidgetItem : public QWidget
{
    Q_OBJECT
public:

    explicit FriendWidgetItem(const MyFriend& friendData, QWidget* parent = nullptr)
        : QWidget(parent)
    {
        // 使用QHBoxLayout将头像和昵称放在一行中
        this->resize(210,70);
        QHBoxLayout* layout = new QHBoxLayout;
        // 创建并设置头像
        /*
        QLabel* headImageLabel = new QLabel(this);
        QPixmap originalPixmap(friendData.headImage);
        QPixmap scaledPixmap = originalPixmap.scaled(50, 50, Qt::KeepAspectRatio);  // 设置图片大小
        headImageLabel->setPixmap(scaledPixmap);
        layout->addWidget(headImageLabel);*/


        /* QString tmp=":/new/prefix2/image/";//QString::number(long_temp,10) :/new/prefix2/image/head (1).JPG
    tmp=tmp+"head ("+QString::number(i,10);
    tmp=tmp+").JPG";

    QPixmap originalPixmap(tmp);
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 设置背景为透明
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(originalPixmap.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    ui->userImage_2->setPixmap(roundedPixmap);
*/


        QLabel *headImageLabel=new QLabel;
        headImageLabel->resize(60,60);
        headImageLabel->setMaximumSize(60,60);
        headImageLabel->setMinimumSize(60,60);
        headImageLabel->setMaximumWidth(60);
        headImageLabel->setMaximumHeight(60);
        headImageLabel->setMinimumWidth(60);
        headImageLabel->setMinimumHeight(60);
        headImageLabel->setScaledContents(true);                                           //控件图片自适应大小
                                                   //控件图片自适应大小
        QString tmp=":/new/prefix2/image/";
        tmp=tmp+friendData.headImage;
        qDebug()<<tmp;
        QPixmap originalPixmap(tmp);
        QPixmap roundedPixmap(originalPixmap.size());
        roundedPixmap.fill(Qt::transparent); // 设置背景为透明
        QPainter painter(&roundedPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(originalPixmap.rect());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, originalPixmap);
        //ui->userImage->setPixmap(roundedPixmap);
        headImageLabel->setPixmap(roundedPixmap.scaled(headImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // 创建并设置昵称
        QLabel *nameLabel=new QLabel;
        nameLabel->setStyleSheet("QLabel { color : #FFFFFF; }");
        nameLabel->resize(150,60);
        nameLabel->setText("     "+friendData.name);
        // 设置字体大小和样式
        QFont font("Microsoft YaHei");
        font.setPointSize(10);  // 设置字体大小
        nameLabel->setFont(font);
        layout->addWidget(headImageLabel);
        layout->addWidget(nameLabel);
        this->setLayout(layout);
        itemFriend=friendData;
    }
    void mousePressEvent(QMouseEvent *event) override;
    MyFriend itemFriend;
};

class RequestWidgetItem : public QWidget
{
    Q_OBJECT
public:

    explicit RequestWidgetItem(const MyRequsest& requestData, QWidget* parent = nullptr)
        : QWidget(parent)
    {


        // 使用QHBoxLayout将头像和昵称放在一行中
        this->resize(210,70);
        QHBoxLayout* layout = new QHBoxLayout;
        // 创建并设置头像
        /*
        QLabel* headImageLabel = new QLabel(this);
        QPixmap originalPixmap(friendData.headImage);
        QPixmap scaledPixmap = originalPixmap.scaled(50, 50, Qt::KeepAspectRatio);  // 设置图片大小
        headImageLabel->setPixmap(scaledPixmap);
        layout->addWidget(headImageLabel);*/


        /* QString tmp=":/new/prefix2/image/";//QString::number(long_temp,10) :/new/prefix2/image/head (1).JPG
    tmp=tmp+"head ("+QString::number(i,10);
    tmp=tmp+").JPG";

    QPixmap originalPixmap(tmp);
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 设置背景为透明
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(originalPixmap.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    ui->userImage_2->setPixmap(roundedPixmap);
*/


        QLabel *headImageLabel=new QLabel;
        headImageLabel->resize(60,60);
        headImageLabel->setMaximumSize(60,60);
        headImageLabel->setMinimumSize(60,60);
        headImageLabel->setMaximumWidth(60);
        headImageLabel->setMaximumHeight(60);
        headImageLabel->setMinimumWidth(60);
        headImageLabel->setMinimumHeight(60);
        headImageLabel->setScaledContents(true);                                           //控件图片自适应大小
                                                   //控件图片自适应大小
        QString tmp=":/new/prefix2/image/";
        tmp=tmp+requestData.headImage;
        qDebug()<<tmp;
        QPixmap originalPixmap(tmp);
        QPixmap roundedPixmap(originalPixmap.size());
        roundedPixmap.fill(Qt::transparent); // 设置背景为透明
        QPainter painter(&roundedPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(originalPixmap.rect());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, originalPixmap);
        //ui->userImage->setPixmap(roundedPixmap);
        headImageLabel->setPixmap(roundedPixmap.scaled(headImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // 创建并设置昵称
        QLabel *nameLabel=new QLabel;
        nameLabel->setStyleSheet("QLabel { color : #FFFFFF; }");
        nameLabel->resize(150,60);
        nameLabel->setText("     "+requestData.name);
        // 设置字体大小和样式
        QFont font("Microsoft YaHei");
        font.setPointSize(10);  // 设置字体大小
        nameLabel->setFont(font);
        layout->addWidget(headImageLabel);
        layout->addWidget(nameLabel);
        this->setLayout(layout);
        itemRequest=requestData;

    }

    void mousePressEvent(QMouseEvent *event) override;
     MyRequsest itemRequest;

};


class ChatWidgetItem : public QWidget
{
    Q_OBJECT
public:

    explicit ChatWidgetItem(const MyChat& chatData, QWidget* parent = nullptr)
        : QWidget(parent)
    {
        // 使用QHBoxLayout将头像和昵称放在一行中
        this->resize(210,70);
        QHBoxLayout* layout = new QHBoxLayout;
        // 创建并设置头像
        /*
        QLabel* headImageLabel = new QLabel(this);
        QPixmap originalPixmap(friendData.headImage);
        QPixmap scaledPixmap = originalPixmap.scaled(50, 50, Qt::KeepAspectRatio);  // 设置图片大小
        headImageLabel->setPixmap(scaledPixmap);
        layout->addWidget(headImageLabel);*/


        /* QString tmp=":/new/prefix2/image/";//QString::number(long_temp,10) :/new/prefix2/image/head (1).JPG
    tmp=tmp+"head ("+QString::number(i,10);
    tmp=tmp+").JPG";

    QPixmap originalPixmap(tmp);
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 设置背景为透明
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(originalPixmap.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    ui->userImage_2->setPixmap(roundedPixmap);
*/


        QLabel *headImageLabel=new QLabel;
        headImageLabel->resize(60,60);
        headImageLabel->setMaximumSize(60,60);
        headImageLabel->setMinimumSize(60,60);
        headImageLabel->setMaximumWidth(60);
        headImageLabel->setMaximumHeight(60);
        headImageLabel->setMinimumWidth(60);
        headImageLabel->setMinimumHeight(60);
        headImageLabel->setScaledContents(true);                                           //控件图片自适应大小
                                                   //控件图片自适应大小
        QString tmp=":/new/prefix2/image/";
        tmp=tmp+chatData.Friend.headImage;
        qDebug()<<tmp;
        QPixmap originalPixmap(tmp);
        QPixmap roundedPixmap(originalPixmap.size());
        roundedPixmap.fill(Qt::transparent); // 设置背景为透明
        QPainter painter(&roundedPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(originalPixmap.rect());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, originalPixmap);
        //ui->userImage->setPixmap(roundedPixmap);
        headImageLabel->setPixmap(roundedPixmap.scaled(headImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        // 创建并设置昵称
        QLabel *nameLabel=new QLabel;
        nameLabel->setStyleSheet("QLabel { color : #FFFFFF; }");
        nameLabel->resize(150,60);
        nameLabel->setText(" "+chatData.Friend.name+"\n"+" "+chatData.Friend.account);
        // 设置字体大小和样式
        QFont font("Microsoft YaHei");
        font.setPointSize(10);  // 设置字体大小
        nameLabel->setFont(font);

        layout->addWidget(headImageLabel);
        layout->addWidget(nameLabel);
        this->setLayout(layout);
        itemChat=chatData;
    }
    void mousePressEvent(QMouseEvent *event) override;
    MyMessages messages;
    MyChat itemChat;
};

class messageWidgetItem : public QWidget
{
    Q_OBJECT
public:

    explicit messageWidgetItem(const MyMessage& messageData,int i,QString h1,QWidget* parent = nullptr)
        : QWidget(parent)
    {


        this->resize(491,70);
        QHBoxLayout* layout = new QHBoxLayout;
        QLabel *headImageLabel=new QLabel;
        headImageLabel->resize(60,60);
        headImageLabel->setMaximumSize(60,60);
        headImageLabel->setMinimumSize(60,60);
        headImageLabel->setMaximumWidth(60);
        headImageLabel->setMaximumHeight(60);
        headImageLabel->setMinimumWidth(60);
        headImageLabel->setMinimumHeight(60);
        headImageLabel->setScaledContents(true);
        QString tmp=":/new/prefix2/image/";
        tmp=tmp+h1;
        qDebug()<<tmp;
        QPixmap originalPixmap(tmp);
        QPixmap roundedPixmap(originalPixmap.size());
        roundedPixmap.fill(Qt::transparent); // 设置背景为透明
        QPainter painter(&roundedPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addEllipse(originalPixmap.rect());
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, originalPixmap);
        //ui->userImage->setPixmap(roundedPixmap);
        headImageLabel->setPixmap(roundedPixmap.scaled(headImageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


        // 创建并设置昵称
        QLabel *nameLabel=new QLabel;
        nameLabel->setStyleSheet("QLabel { color : #FFFFFF; background: rgb(89, 164, 222);border: 1px solid rgba(220,220,220, 200);border-radius:5px; }");
        nameLabel->resize(150,60);
        nameLabel->setMaximumSize(150,60);
        nameLabel->setMinimumSize(150,60);
        nameLabel->setMaximumWidth(150);
        nameLabel->setMinimumWidth(150);
        nameLabel->setMaximumHeight(60);
        nameLabel->setMinimumHeight(60);
        nameLabel->setText(messageData.message);
        qDebug()<<messageData.message;
        // 设置字体大小和样式
        QFont font("Microsoft YaHei");
        font.setPointSize(10);  // 设置字体大小
        nameLabel->setFont(font);
        if(i==0)
        {
            qDebug()<<"左";          
            layout->addWidget(headImageLabel);
            layout->addWidget(nameLabel);
            layout->addStretch();

        }
        else
        {
            qDebug()<<"右";
            layout->addStretch();
            layout->addWidget(nameLabel);
            layout->addWidget(headImageLabel);
        }
        itemMessage=messageData;
        this->setLayout(layout);

    }
    MyMessage itemMessage;
};

#endif // MAINWINDOW_H
