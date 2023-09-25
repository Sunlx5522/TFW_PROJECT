#ifndef WIDGET_H
#define WIDGET_H

#include <QMovie>
#include <QWidget>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>
#include <QSortFilterProxyModel>

#include <QList>
#include "userlist.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlQueryModel>

#include <QTableView>
#include <QContextMenuEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{

    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr);

    ~Widget();

    void mousePressEvent(QMouseEvent *event) override                                              //实现窗口拖动
    {
        if (event->button() == Qt::LeftButton)
        {
            lastDragPos = event->globalPos();                                                      //记录初始位置
            event->accept();                                                                       //防止误触
        }
        else
        {
            event->ignore();                                                                       //防止误触
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override                                               //实现窗口拖动
    {
        if (event->buttons() & Qt::LeftButton)
        {
            //计算鼠标移动的距离

            int dx = event->globalX() - lastDragPos.x();
            int dy = event->globalY() - lastDragPos.y();

            //设置动画的起始位置和结束位置

            animation->setStartValue(pos());
            animation->setEndValue(pos() + QPoint(dx, dy));

            //启动动画 不采用move重绘 减小cpu负担 将任务交给显卡

            animation->start();
            lastDragPos = event->globalPos();
            event->accept();                                                                       //防止误触

        }
        else
        {
            event->ignore();                                                                       //防止误触
        }
    }

    bool eventFilter(QObject *obj, QEvent *event);                                                 //自定义一些Qlable的点击实现

    void changeEvent( QEvent* e );                                                                 //窗口最小化更改回透明度为1

    void showEvent(QShowEvent *event);                                                             //窗口最小化更改回透明度为1 辅助函数


    void shouError();

    void addTable(QSqlQueryModel*);
    void addTable_s(QSqlQueryModel*);

    bool networkAbleFlag=false;

     UserList *user;

     void onCopyActionTriggered();
     void showContextMenu(const QPoint &pos);

private slots:

    //账号检测
    void newClient_check();                                                                        //账号登录
    void lostClient_check();                                                                       //删除在线的人
    void readMessage_check();                                                                      //读取账号信息
    void sendMessage_check();                                                                      //发送信息

    //消息转发
    void newConnect_news();                                                                        //新客户端连接
    void sendMessage_news(QString information);                                                    //发送消息
    void readMessage_news();                                                                       //接收消息
    void lostClient_news();                                                                        //删除聊天

    //初始化界面
    void newConnect_surface();                                                                     //新客户端连接
    void sendMessage_surface(QString initMsg);                                                     //发送消息
    void readMessage_surface();                                                                    //接收消息
    void lostClient_surface();                                                                     //删除

    //群聊界面
    void newConnect_Chatnews();                                                                    //新客户端连接
    void sendMessage_Chatnews(QString information);                                                //发送消息
    void readMessage_Chatnews();                                                                   //接收消息
    void lostClient_Chatnews();                                                                    //删除聊天

    //服务器销毁
    void destoryServer_check();




private:

    Ui::Widget *ui;

    QMovie *think;                                                                                 //开头gif播放

    QPoint lastDragPos;                                                                            //记录上次拖拽的位置

    QPropertyAnimation *animation ;                                                                //拖动动画
    QPropertyAnimation *animation1;                                                                //最小化动画
    QPropertyAnimation *animation2;                                                                //关闭动画
    QPropertyAnimation *animation3;                                                                //启动动画

    QGraphicsBlurEffect *blureffect1;
    QSortFilterProxyModel *proxyModel;

    QMenu *contextMenu ;
    QAction *copyAction ;



    int people;

    /************************账号检测 5555端口********************/
    //network
    QTcpServer *server_check;                                                                      //服务
    QTcpSocket *client_check;                                                                      //临时客户端
    QList<QTcpSocket *> clients_check;                                                             //客户端列
    //标志
    bool listenFlag_check = false;                                                                 //5555端口监听
    bool clientJoinUp_check = false;                                                               //客户端加
    bool loginSuccessFlag_check = false;                                                           //登陆成功标志
    //反馈消息
    void feedbackMessage(QString msg);
    /**********************转发消息 6666端口**********************/
    //network
    QTcpServer *server_news;                                                                       //服务器
    QTcpSocket *client_news;                                                                       //临时客户
    QList<QTcpSocket *> *clients_news;                                                             //客户端列表
    //标志
    bool listenFlag_news = false;                                                                  //6666端口监听
    bool clientJoinUp_news = false;                                                                //客户端加入
    bool loginSuccessFlag_news = false;                                                            //登陆成功标志
    /********************初始化界面 7777端口********************/
    //network
    QTcpServer *server_surface;                                                                    //服务器
    QTcpSocket *client_surface;                                                                    //临时客户端
    QList<QTcpSocket *> *clients_surface;                                                          //客户端列表
    QString initMsg;                                                                               //初始化界面的消息
    //标志
    bool listenFlag_surface = false;                                                               //7777端口监听
    bool clientJoinUp_surface = false;                                                             //客户端加入
    bool loginSuccessFlag_surface = false;                                                         //登陆成功标志
    /*******************群聊 8888端口****************************/
    //network
    QTcpServer *server_Chatnews;                                                                   //服务器
    QTcpSocket *client_Chatnews;                                                                   //临时客户
    QList<QTcpSocket *> *clients_Chatnews;                                                         //客户端列表
    //标志
    bool listenFlag_Chatnews = false;                                                              //8888端口监听
    bool clientJoinUp_Chatnews = false;                                                            //客户端加入
    bool loginSuccessFlag_Chatnews = false;                                                        //登陆成功标志



};
#endif // WIDGET_H
