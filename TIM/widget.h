/*此头文件包含登录窗口的相关声明*/
/*包含警戒*/

#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsDropShadowEffect>                                                   //阴影添加
#include <QGraphicsBlurEffect>                                                        //显卡渲染头文件
#include <QPropertyAnimation>                                                          //动画事件头文件
#include <QMouseEvent>                                                                //鼠标事件头文件
#include <qsystemtrayicon.h>
#include <QRegExp>
#include <QValidator>
#include <QCloseEvent>                                                                 //关闭事件头文件
#include <QTcpServer>
#include <QLineEdit>
#include <QTcpSocket>
#include <QHostInfo>
#include <QWidget>                                                                    //widget相关头文件
#include <QPainter>
#include <QMovie>
#include <QMenu>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{

    Q_OBJECT

public:

    Widget(QWidget *parent = nullptr);

    ~Widget();
    QGraphicsBlurEffect *blureffect1;

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





    bool eventFilter(QObject *obj, QEvent *event);                                    //自定义一些Qlable的点击实现
    void showEvent(QShowEvent *event);                                                //窗口最小化更改回透明度为1 辅助函数
    void changeEvent( QEvent* e );                                                    //窗口最小化更改回透明度为1
    bool isMainWindowOpen=false;
    QString myAccount;
    QString myPassword;
    void shouError();
    void duckshow();
    void chushihua();
    void setplacehodetext(QLineEdit*);
    void setplacehodetextRed(QLineEdit*);
    void registerAppend(QString);
    bool loginFlag=true;
    bool networkAbleFlag=false;
    bool loginSuccessFlag=false;
    bool AlreadyOnlineFlag=false;
    bool connectFlag=false;
    void networkStationUpdate();
    void commitMessage();
    void commitMessage1(QString Msg);
    void readMessage();
    void refresh();
    void changeImage(int);
    QTcpSocket* client;
    QTcpSocket* client1;
    QRegExp rx = QRegExp("[\40]*");
    QRegExpValidator* validator = new QRegExpValidator(rx);



private slots:
    void on_rememberPasssword_stateChanged(int arg1);


private:

    /*阴影添加*/

    QGraphicsDropShadowEffect *shadow_effect1;
    QGraphicsDropShadowEffect *shadow_effect2;
    QGraphicsDropShadowEffect *shadow_effect3;
    QGraphicsDropShadowEffect *shadow_effect4;
    QGraphicsDropShadowEffect *shadow_effect5;
    QGraphicsDropShadowEffect *shadow_effect6;
    QGraphicsDropShadowEffect *shadow_effect7;
    QGraphicsDropShadowEffect *shadow_effect8;

    QPropertyAnimation *animation;                                                    //启动动画前的一段动画
    QPropertyAnimation *animation1;                                                   //启动动画
    QPropertyAnimation *animation2;                                                   //拖动动画
    QPropertyAnimation *animation3;                                                   //最小化动画
    QPropertyAnimation *animation4;                                                   //关闭动画
    QPropertyAnimation *animation5;                                                   //关闭动画


    QPoint lastDragPos;                                                               //记录上次拖拽的位置

    QMovie *duckMovie;
    QMovie *startMovie;                                                               //开头gif播放




    QMovie *think;


   Ui::Widget *ui;


                                                                    //ui声明



};
#endif                                                                                //WIDGET_H
