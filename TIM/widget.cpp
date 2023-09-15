#include <QGraphicsDropShadowEffect>                                                  //动画事件头文件
#include<QParallelAnimationGroup>                                                     //动画事件头文件
#include <QNetworkConfigurationManager>
#include<QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTcpServer>
#include <QTcpSocket>
#include<QPropertyAnimation>                                                          //动画
#include<QRegExpValidator>                                                            //用于输入限制
#include <QElapsedTimer>                                                              //时间
#include <QApplication>                                                               //外部引用 关闭应用
#include <QPushButton>                                                                //按钮控件
#include <QMouseEvent>                                                                //鼠标拖动事件
#include<QFuture>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>
#include "ui_widget.h"                                                                //与ui界面设计师的链接
#include<QCloseEvent>                                                                 //最小化动画实现辅助函数
#include<QMessageBox>                                                                 //用于预留接口
#include<QVBoxLayout>                                                                 //用于布局
#include <QHostInfo>
#include<QShowEvent>                                                                  //最小化动画实现辅助函数
#include"widget.h"                                                                   //登陆界面头文件
#include<QObject>                                                                     //QObject 头文件引用
#include<QLabel>                                                                     //laable控件头文件
#include<QPixmap>                                                                     //qlable 图片渲染
#include<QMovie>                                                                      //用于gif动画播放
#include<QLabel>                                                                      //lable相关函数
#include<QMovie>                                                                      //gif动画
#include<QTimer>

extern QApplication a;                                                                //外部变量声明 用于关闭应用

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    ui->setupUi(this);
    this->setWindowTitle("TFW");                                                      //登录窗口名
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());                          //去窗口边框
    setAttribute(Qt::WA_TranslucentBackground);                                       //把窗口背景设置为透明;
    setMouseTracking(true);                                                           //窗口可进行鼠标追踪，以进行拖动

    //登录界面lable点击功能实现

    ui->getVerificationCode->installEventFilter(this);                                //将qlable设置点击事件
    ui->rememberPasssword->installEventFilter(this);                                  //将qlable设置点击事件
    ui->accountLineEdit->installEventFilter(this);                                    //将qlable设置点击事件
    ui->return_back1->installEventFilter(this);                                       //将qlable设置点击事件
    ui->passwordBack->installEventFilter(this);                                       //将qlable设置点击事件
    ui->logInButton->installEventFilter(this);                                        //将qlable设置点击事件
    ui->duckLabel->installEventFilter(this);                                          //将qlable设置点击事件
    ui->setting->installEventFilter(this);                                            //将qlable设置点击事件
    ui->qrLabel->installEventFilter(this);                                            //将qlable设置点击事件
    ui->signUp->installEventFilter(this);                                             //将qlable设置点击事件
    ui->next1->installEventFilter(this);                                              //将qlable设置点击事件
    ui->close->installEventFilter(this);                                              //将qlable设置点击事件
    ui->mim->installEventFilter(this);                                                //将qlable设置点击事件
    ui->passwordBack->setAttribute(Qt::WA_Hover,true);                                //开启悬停事件
    ui->logInButton->setAttribute(Qt::WA_Hover,true);                                 //开启悬停事件
    ui->setting->setAttribute(Qt::WA_Hover,true);                                     //开启悬停事件
    ui->qrLabel->setAttribute(Qt::WA_Hover,true);                                     //开启悬停事件
    ui->signUp->setAttribute(Qt::WA_Hover,true);                                      //开启悬停事件
    ui->close->setAttribute(Qt::WA_Hover,true);                                       //开启悬停事件
    ui->mim->setAttribute(Qt::WA_Hover,true);                                         //开启悬停事件
    ui->duckLabel->setScaledContents(true);                                           //控件图片自适应大小
    ui->userImage->setScaledContents(true);                                           //控件图片自适应大小
    ui->qrLabel->setScaledContents(true);                                             //控件图片自适应大小
    ui->setting->setScaledContents(true);                                             //控件图片自适应大小
    ui->close->setScaledContents(true);                                               //控件图片自适应大小
    ui->logo->setScaledContents(true);                                                //控件图片自适应大小
    ui->mim->setScaledContents(true);                                                 //控件图片自适应大小
    ui->userImage->raise();                                                           //控件置顶显示
    ui->accountLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->passwordLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->nameLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->signUpPasswordLineEdit1->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->signUpPasswordLineEdit2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->phoneNumber->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));//输入限制
    ui->verificationCode->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));//输入限制
    ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#4169E1");         //color:#FFFAFA;字体颜色设置

    //duck gif动画播放

    duckMovie = new QMovie(":/new/prefix1/duck.gif");
    duckMovie->setSpeed(120);
    ui->duckLabel->setMovie(duckMovie);

    //窗口焦点 防止失焦

    ui->frame->setFocus();

    //设置具体阴影

    shadow_effect1 = new QGraphicsDropShadowEffect(this);
    shadow_effect1->setOffset(0, 0);
    shadow_effect2 = new QGraphicsDropShadowEffect(this);
    shadow_effect2->setOffset(0, 0);
    shadow_effect3 = new QGraphicsDropShadowEffect(this);
    shadow_effect3->setOffset(0, 0);
    shadow_effect4 = new QGraphicsDropShadowEffect(this);
    shadow_effect4->setOffset(0, 0);
    shadow_effect5 = new QGraphicsDropShadowEffect(this);
    shadow_effect5->setOffset(0, 0);
    shadow_effect6 = new QGraphicsDropShadowEffect(this);
    shadow_effect6->setOffset(0, 0);
    shadow_effect7 = new QGraphicsDropShadowEffect(this);
    shadow_effect7->setOffset(0, 0);
    shadow_effect8 = new QGraphicsDropShadowEffect(this);
    shadow_effect8->setOffset(0, 0);


    //阴影颜色

    shadow_effect1->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect2->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect3->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect4->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect5->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect6->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect7->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect8->setColor(QColor(0,191,255, 255));//蓝色

    //阴影半径

    shadow_effect1->setBlurRadius(20);
    shadow_effect2->setBlurRadius(20);
    shadow_effect3->setBlurRadius(20);
    shadow_effect4->setBlurRadius(20);
    shadow_effect5->setBlurRadius(20);
    shadow_effect6->setBlurRadius(20);
    shadow_effect7->setBlurRadius(20);
    shadow_effect8->setBlurRadius(20);
    ui->rememberPasssword->setGraphicsEffect(shadow_effect6);
    ui->passwordBack->setGraphicsEffect(shadow_effect7);
    ui->signUp->setGraphicsEffect(shadow_effect5);
    //ui->frame->setGraphicsEffect(shadow_effect1);
    ui->label_3->setGraphicsEffect(shadow_effect2);
    QLabel *glb;
    glb=new QLabel(this);
    QVBoxLayout layout(ui->frame);
    layout.addWidget(glb);
    // 设置布局管理器的对齐方式为居中
    layout.setAlignment(Qt::AlignCenter);
    //登录动画
    startMovie = new QMovie(":/new/prefix1/start_gif.gif");
    startMovie->setSpeed(250);
    glb->setMovie(startMovie);
    //新建动画

    animation = new QPropertyAnimation(this, "windowOpacity");
    animation1 = new QPropertyAnimation(this, "windowOpacity");
    animation2 = new QPropertyAnimation(this, "pos");                                 //动画效果
    animation2->setDuration(0);                                                       //设置动画持续时间（毫秒）//动画效果
    animation3 = new QPropertyAnimation(this, "windowOpacity");
    animation4 = new QPropertyAnimation(this, "windowOpacity");

    //gif结束动画

    animation->setDuration(1000);
    animation->setKeyValueAt(0, 1);
    animation->setKeyValueAt(0.1, 0.9);
    animation->setKeyValueAt(0.2, 0.8);
    animation->setKeyValueAt(0.3, 0.7);
    animation->setKeyValueAt(0.4, 0.6);
    animation->setKeyValueAt(0.5, 0.5);
    animation->setKeyValueAt(0.6, 0.4);
    animation->setKeyValueAt(0.7, 0.3);
    animation->setKeyValueAt(0.8, 0.2);
    animation->setKeyValueAt(0.9, 0.1);
    animation->setKeyValueAt(1, 0);
    QObject::connect(startMovie, &QMovie::frameChanged, [=](int frameNumber) {
        // GIF 动画执行一次就结束
        if (frameNumber == startMovie->frameCount() - 1) {
            startMovie->stop();
            animation->start();
        }
    });
    QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
        // GIF 动画执行一次就结束
        if (frameNumber == duckMovie->frameCount()-1) {
            duckMovie->stop();
        }
    });
    //启动动画
    animation1->setDuration(1000);
    animation1->setKeyValueAt(0,0);
    animation1->setKeyValueAt(0.1,0.1);
    animation1->setKeyValueAt(0.2,0.2);
    animation1->setKeyValueAt(0.3,0.3);
    animation1->setKeyValueAt(0.4,0.4);
    animation1->setKeyValueAt(0.5,0.5);
    animation1->setKeyValueAt(0.6,0.6);
    animation1->setKeyValueAt(0.7,0.7);
    animation1->setKeyValueAt(0.8,0.8);
    animation1->setKeyValueAt(0.9,0.9);
    animation1->setKeyValueAt(1,1);
    QObject::connect(animation, &QPropertyAnimation::finished, [=](){
        animation->stop();  // 停止属性动画 a
        delete glb;
        animation1->start();
        duckMovie->start();
    });
    //关闭动画
    animation4->setDuration(1000);
    animation4->setKeyValueAt(0, 1);
    animation4->setKeyValueAt(0.1, 0.9);
    animation4->setKeyValueAt(0.2, 0.8);
    animation4->setKeyValueAt(0.3, 0.7);
    animation4->setKeyValueAt(0.4, 0.6);
    animation4->setKeyValueAt(0.5, 0.5);
    animation4->setKeyValueAt(0.6, 0.4);
    animation4->setKeyValueAt(0.7, 0.3);
    animation4->setKeyValueAt(0.8, 0.2);
    animation4->setKeyValueAt(0.9, 0.1);
    animation4->setKeyValueAt(1, 0);
    connect(animation4, SIGNAL(finished()), this, SLOT(close()));

    //最小化动画
    animation3->setDuration(1000);
    animation3->setKeyValueAt(0, 1);
    animation3->setKeyValueAt(0.1, 0.9);
    animation3->setKeyValueAt(0.2, 0.8);
    animation3->setKeyValueAt(0.3, 0.7);
    animation3->setKeyValueAt(0.4, 0.6);
    animation3->setKeyValueAt(0.5, 0.5);
    animation3->setKeyValueAt(0.6, 0.4);
    animation3->setKeyValueAt(0.7, 0.3);
    animation3->setKeyValueAt(0.8, 0.2);
    animation3->setKeyValueAt(0.9, 0.1);
    animation3->setKeyValueAt(1, 0);
    connect(animation3, SIGNAL(finished()), this, SLOT(showMinimized()));

    blureffect1=new QGraphicsBlurEffect;                                                           //模糊特效
    blureffect1->setBlurRadius(20);	                                                               //数值越大，越模糊
    ui->frame->setGraphicsEffect(blureffect1);
    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));

    client=new QTcpSocket(this);
    connect(client,&QTcpSocket::readyRead, this, &Widget::readMessage);
    startMovie->start();


}
//析构函数
Widget::~Widget()
{
    delete animation;                                                                 //启动动画前的一段动画
    delete animation1;                                                                //启动动画
    delete animation2;                                                                //拖动动画
    delete animation3;                                                                //关闭动画
    delete animation4;                                                                //最小化动画
    delete startMovie;                                                                //开头gif播放
    delete duckMovie;
    delete shadow_effect1;
    delete shadow_effect2;
    delete shadow_effect3;
    delete shadow_effect4;
    delete shadow_effect5;
    delete shadow_effect6;
    delete shadow_effect7;
    delete shadow_effect8;
    delete ui;
}
//自定义点击事件
bool Widget::eventFilter(QObject *obj, QEvent *event)
{

    if(qobject_cast<QLabel*>(obj) == ui->passwordBack)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color:#FFE4E1");//color:#FFFAFA;
            QMessageBox::information(this, "提示", QString("点击了该Label 1"));//待添加
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color:#1E90FF");//color:#FFFAFA;
            return true;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color: rgb(176, 224 ,230)");//color:#FFFAFA;
            return true;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color:#FFE4E1");//color:#FFFAFA;
            return true;
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->logInButton)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if(!networkAbleFlag)
            {
                ui->duckLabel->hide();
                ui->duckLabel->update();
                QLabel *thinkLable;
                thinkLable=new QLabel(this);
                thinkLable->resize(512,256);
                thinkLable->setScaledContents(true);
                thinkLable->setGeometry(444,392,512,256);
                QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
                thinkLable->show();
                //ui->gridLayout->addWidget(thinkLable);
                // 设置布局管理器的对齐方式为居中
                think = new QMovie(":/new/prefix1/duck3.gif");
                think->setSpeed(300);
                thinkLable->setMovie(think);
                think->start();
                setEnabled(false);
                ui->rememberPasssword->removeEventFilter(this);
                ui->signUp->removeEventFilter(this);
                ui->qrLabel->removeEventFilter(this);
                ui->mim->removeEventFilter(this);
                ui->setting->removeEventFilter(this);
                ui->close->removeEventFilter(this);
                ui->passwordBack->removeEventFilter(this);
                ui->logInButton->removeEventFilter(this);
                ui->return_back1->removeEventFilter(this);
                ui->getVerificationCode->removeEventFilter(this);
                ui->next1->removeEventFilter(this);
                QObject::connect(think, &QMovie::frameChanged, [=](int frameNumber) {
                    // GIF 动画 执行一次就结束
                    if (frameNumber == think->frameCount() - 1) {
                        think->stop();
                        delete thinkLable;
                        QString det="互联网未连接";
                        det = tr("<font size='6' color='white'>") + det;
                        det += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                        QMessageBox msgbox(QMessageBox::Information,"",det);                        //将QMessageBox实例化出来，好方便后面setStyleSheet
                        //下面补上Qss样式表的设置写法即可
                        msgbox.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                        msgbox.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                        QLabel *Lable1;
                        Lable1=new QLabel(this);
                        Lable1->resize(200,50);
                        Lable1->setGeometry(380,380,200,50);
                        msgbox.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                        QPoint globalPos = Lable1->mapToGlobal(QPoint(0, 0));
                        msgbox.move(globalPos.x(),globalPos.y());
                        //qDebug() << msgbox.rect().width()<< endl;
                        //qDebug() << msgbox.rect().height()<< endl;
                        QTimer::singleShot(1500,&msgbox,SLOT(accept()));
                        msgbox.addButton(QMessageBox::Ok);
                        msgbox.button(QMessageBox::Ok)->hide();
                        msgbox.exec();

                        setEnabled(true);
                        ui->rememberPasssword->installEventFilter(this);
                        ui->signUp->installEventFilter(this);
                        ui->qrLabel->installEventFilter(this);
                        ui->mim->installEventFilter(this);
                        ui->setting->installEventFilter(this);
                        ui->close->installEventFilter(this);
                        ui->passwordBack->installEventFilter(this);
                        ui->logInButton->installEventFilter(this);
                        ui->return_back1->installEventFilter(this);
                        ui->getVerificationCode->installEventFilter(this);
                        ui->next1->installEventFilter(this);
                        QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                        ui->duckLabel->show();
                        ui->duckLabel->update();
                    }
                });




            }
            else
            {
                         setEnabled(false);
                         ui->rememberPasssword->removeEventFilter(this);
                         ui->signUp->removeEventFilter(this);
                         ui->qrLabel->removeEventFilter(this);
                         ui->mim->removeEventFilter(this);
                         ui->setting->removeEventFilter(this);
                         ui->close->removeEventFilter(this);
                         ui->passwordBack->removeEventFilter(this);
                         ui->logInButton->removeEventFilter(this);
                         ui->return_back1->removeEventFilter(this);
                         ui->getVerificationCode->removeEventFilter(this);
                         ui->next1->removeEventFilter(this);
                         ui->duckLabel->hide();
                         ui->duckLabel->update();
                         QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
                         client->abort();
                         client->connectToHost("127.0.0.1",5555);
                         QString det="正在链接服务器";
                         det = tr("<font size='6' color='white'>") + det;
                         det += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                         QMessageBox msgbox(QMessageBox::Information,"",det);                        //将QMessageBox实例化出来，好方便后面setStyleSheet
                         //下面补上Qss样式表的设置写法即可
                         msgbox.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                         msgbox.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                         QLabel *Lable1;
                         Lable1=new QLabel(this);
                         Lable1->resize(200,50);
                         Lable1->setGeometry(380,380,200,50);
                         msgbox.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                         QPoint globalPos = Lable1->mapToGlobal(QPoint(0, 0));
                         msgbox.move(globalPos.x(),globalPos.y());
                         //qDebug() << msgbox.rect().width()<< endl;
                         //qDebug() << msgbox.rect().height()<< endl;
                         QTimer::singleShot(3000,&msgbox,SLOT(accept()));
                         msgbox.addButton(QMessageBox::Ok);
                         msgbox.button(QMessageBox::Ok)->hide();
                         msgbox.exec();
                         bool connectFlag = client->waitForConnected(10000);
                         if(connectFlag)
                         {
                             QString det1="链接成功";
                             det1 = tr("<font size='6' color='white'>") + det1;
                             det1 += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                             QMessageBox msgbox1(QMessageBox::Information,"",det1);
                             msgbox1.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                             msgbox1.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                             QLabel *Lable2;
                             Lable2=new QLabel(this);
                             Lable2->resize(200,50);
                             Lable2->setGeometry(380,380,200,50);
                             msgbox1.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                             QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
                             msgbox1.move(globalPos1.x(),globalPos1.y());
                             //qDebug() << msgbox.rect().width()<< endl;
                             //qDebug() << msgbox.rect().height()<< endl;
                             QTimer::singleShot(3000,&msgbox1,SLOT(accept()));
                             msgbox1.addButton(QMessageBox::Ok);
                             msgbox1.button(QMessageBox::Ok)->hide();
                             msgbox1.exec();

                             QString det2="正在检测账号与密码";
                             det2 = tr("<font size='6' color='white'>") + det2;
                             det2 += tr("</font>");
                             QMessageBox msgbox2(QMessageBox::Information,"",det2);
                             msgbox2.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                             msgbox2.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                             QLabel *Lable3;
                             Lable3=new QLabel(this);
                             Lable3->resize(200,50);
                             Lable3->setGeometry(380,380,200,50);
                             msgbox2.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                             QPoint globalPos2 = Lable3->mapToGlobal(QPoint(0, 0));
                             msgbox2.move(globalPos2.x(),globalPos2.y());
                             //qDebug() << msgbox.rect().width()<< endl;
                             //qDebug() << msgbox.rect().height()<< endl;
                             QTimer::singleShot(3000,&msgbox2,SLOT(accept()));
                             msgbox2.addButton(QMessageBox::Ok);
                             msgbox2.button(QMessageBox::Ok)->hide();
                             msgbox2.exec();
                             commitMessage();

                         }
                         else
                         {
                             QString det1="链接失败";
                             det1 = tr("<font size='6' color='white'>") + det1;
                             det1 += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                             QMessageBox msgbox1(QMessageBox::Information,"",det1);
                             msgbox1.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                             msgbox1.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                             QLabel *Lable2;
                             Lable2=new QLabel(this);
                             Lable2->resize(200,50);
                             Lable2->setGeometry(380,380,200,50);
                             msgbox1.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                             QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
                             msgbox1.move(globalPos1.x(),globalPos1.y());
                             //qDebug() << msgbox.rect().width()<< endl;
                             //qDebug() << msgbox.rect().height()<< endl;
                             QTimer::singleShot(3000,&msgbox1,SLOT(accept()));
                             msgbox1.addButton(QMessageBox::Ok);
                             msgbox1.button(QMessageBox::Ok)->hide();
                             msgbox1.exec();
                             QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                             setEnabled(true);
                             ui->rememberPasssword->installEventFilter(this);
                             ui->signUp->installEventFilter(this);
                             ui->qrLabel->installEventFilter(this);
                             ui->mim->installEventFilter(this);
                             ui->setting->installEventFilter(this);
                             ui->close->installEventFilter(this);
                             ui->passwordBack->installEventFilter(this);
                             ui->logInButton->installEventFilter(this);
                             ui->return_back1->installEventFilter(this);
                             ui->getVerificationCode->installEventFilter(this);
                             ui->next1->installEventFilter(this);
                             ui->duckLabel->show();
                             ui->duckLabel->update();
                         }
            }
        }





    }
    else if(qobject_cast<QLineEdit*>(obj) == ui->accountLineEdit)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
           ;
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->return_back1)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            int currentIndex = ui->stackedWidget->currentIndex();
            int windowWidth = ui->stackedWidget->widget(currentIndex)->width();
            int windowHieght = ui->stackedWidget->widget(currentIndex)->height();
            int PreIndex = currentIndex - 1;
            ui->stackedWidget->setCurrentIndex(PreIndex);
            ui->stackedWidget->widget(currentIndex)->show();
            QPropertyAnimation* animation1;
            QPropertyAnimation* animation2;
            QParallelAnimationGroup* group = new QParallelAnimationGroup;
            animation1 = new QPropertyAnimation(ui->stackedWidget->widget(currentIndex),"geometry");
            animation1->setDuration(700);
            animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
            animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
            animation2 =new QPropertyAnimation(ui->stackedWidget->widget(PreIndex), "geometry");
            animation2->setDuration(700);
            animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
            animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->start();
            group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
            //connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
            QMovie *duckMovie;
            duckMovie = new QMovie(":/new/prefix1/duck.gif");
            duckMovie->setSpeed(120);
            ui->duckLabel->setMovie(duckMovie);
            duckMovie->start();
            QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                if (frameNumber == duckMovie->frameCount() - 1) {
                    duckMovie->stop();
                }
            });
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->next1)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->getVerificationCode)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
    }
    else if(qobject_cast<QCheckBox*>(obj) == ui->rememberPasssword)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->signUp)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#4169E1");//color:#FFFAFA; 字体颜色设置
            int currentIndex = ui->stackedWidget->currentIndex();
            int windowWidth = ui->stackedWidget->widget(currentIndex)->width();
            int windowHieght = ui->stackedWidget->widget(currentIndex)->height();
            int NextIndex = currentIndex + 1;
            ui->stackedWidget->setCurrentIndex(NextIndex);
            ui->stackedWidget->widget(currentIndex)->show();
            QPropertyAnimation* animation1;
            QPropertyAnimation* animation2;
            QParallelAnimationGroup* group = new QParallelAnimationGroup;
            animation1 = new QPropertyAnimation(ui->stackedWidget->widget(currentIndex),"geometry");
            animation1->setDuration(700);
            animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
            animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
            animation2 =new QPropertyAnimation(ui->stackedWidget->widget(NextIndex), "geometry");
            animation2->setDuration(700);
            animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
            animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->start();
            group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
            //connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
            QMovie *duckMovie;
            duckMovie = new QMovie(":/new/prefix1/duck2.gif");
            duckMovie->setSpeed(120);
            ui->duckLabel->setMovie(duckMovie);
            duckMovie->start();
            QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                if (frameNumber == duckMovie->frameCount() - 1) {
                    duckMovie->stop();
                }
            });
            return true;}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#1E90FF");//color:#FFFAFA;
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color: rgb(176, 224 ,230)");//color:#FFFAFA;
            return true;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#4169E1");//color:#FFFAFA; 字体颜色设置
            return true;
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->qrLabel)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            QMessageBox::information(this, "提示", QString("点击了该Label 3"));//待添加
            return true;}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->setting)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/ssetting.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            QMessageBox::information(this, "提示", QString("点击了该Label 4"));//待添加
            return true;}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/ssetting2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/ssetting1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/ssetting.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->mim)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/mim.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            animation3->start();
            return true;}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/mim2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/mim1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/mim.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->close)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            setEnabled(false);
            ui->rememberPasssword->removeEventFilter(this);
            ui->signUp->removeEventFilter(this);
            ui->qrLabel->removeEventFilter(this);
            ui->mim->removeEventFilter(this);
            ui->setting->removeEventFilter(this);
            ui->close->removeEventFilter(this);
            ui->passwordBack->removeEventFilter(this);
            ui->logInButton->removeEventFilter(this);
            ui->return_back1->removeEventFilter(this);
            ui->getVerificationCode->removeEventFilter(this);
            ui->next1->removeEventFilter(this);
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            QMovie *duckMovie;
            duckMovie = new QMovie(":/new/prefix1/duck1.gif");
            duckMovie->setSpeed(120);
            ui->duckLabel->setMovie(duckMovie);
            duckMovie->start();
            QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                if (frameNumber == duckMovie->frameCount() - 1) {
                    duckMovie->stop();
                    animation4->start();
                }
            });
            return true;}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/close2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/close1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            return true;
        }
    }
    return false;
}
//以下两个个函数均参与最小化过程的处理  隐藏窗口后将其透明度重新设置为1
void Widget::showEvent(QShowEvent *event)
{
    setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}
void Widget::changeEvent( QEvent* e )
{

    if( e->type() == QEvent::WindowStateChange)
    {
        if(this->windowState() & Qt::WindowMinimized )
        {
            setWindowOpacity(1);                                                             //设置透明度为1
            ui->frame->setFocus();
        }
        else
        {
            setWindowFlags(Qt::Window);                                                      //set normal window flag
            setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//and return to your old flags
            this->showNormal();
        }
    }
}

void Widget::networkStationUpdate()
{
    if(networkAbleFlag)
    {
      ui->netWorkStation->setText("网络连接状态：已连接");
    }
    else
    {
        ui->netWorkStation->setText("网络连接状态：未连接");
    }
}

void Widget::commitMessage(){
    QString account = ui->accountLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    ui->accountLineEdit->clear();
    ui->passwordLineEdit->clear();
    client->write(account.toUtf8() + " " + password.toUtf8());
}

void Widget::readMessage(){
    loginSuccessFlag=false;
    QString str;
    str = client->readAll();
    if(str == "loginSuccess"){
        loginSuccessFlag = true;
    }else if(str == "loginFail"){
        loginSuccessFlag = false;
    }else if(str == "AlreadyOnline"){
        loginSuccessFlag = false;
    }

    QLabel *thinkLable;
    thinkLable=new QLabel(this);
    thinkLable->resize(512,256);
    thinkLable->setScaledContents(true);
    thinkLable->setGeometry(444,392,512,256);
    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
    thinkLable->show();
    //ui->gridLayout->addWidget(thinkLable);
    // 设置布局管理器的对齐方式为居中
    think = new QMovie(":/new/prefix1/duck3.gif");
    think->setSpeed(300);
    thinkLable->setMovie(think);
    think->start();

    QObject::connect(think, &QMovie::frameChanged, [=](int frameNumber) {
        // GIF 动画 执行一次就结束
        if (frameNumber == think->frameCount() - 1) {
            think->stop();
            delete thinkLable;
            if(loginSuccessFlag)
            {
                QString det1="登录成功";
                det1 = tr("<font size='6' color='white'>") + det1;
                det1 += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                QMessageBox msgbox1(QMessageBox::Information,"",det1);
                msgbox1.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                msgbox1.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                QLabel *Lable2;
                Lable2=new QLabel(this);
                Lable2->resize(200,50);
                Lable2->setGeometry(380,380,200,50);
                msgbox1.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
                msgbox1.move(globalPos1.x(),globalPos1.y());
                //qDebug() << msgbox.rect().width()<< endl;
                //qDebug() << msgbox.rect().height()<< endl;
                QTimer::singleShot(3000,&msgbox1,SLOT(accept()));
                msgbox1.addButton(QMessageBox::Ok);
                msgbox1.button(QMessageBox::Ok)->hide();
                msgbox1.exec();
                QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                setEnabled(true);
                ui->rememberPasssword->installEventFilter(this);
                ui->signUp->installEventFilter(this);
                ui->qrLabel->installEventFilter(this);
                ui->mim->installEventFilter(this);
                ui->setting->installEventFilter(this);
                ui->close->installEventFilter(this);
                ui->passwordBack->installEventFilter(this);
                ui->logInButton->installEventFilter(this);
                ui->return_back1->installEventFilter(this);
                ui->getVerificationCode->installEventFilter(this);
                ui->next1->installEventFilter(this);
                ui->duckLabel->show();
                ui->duckLabel->update();

            }
            else
            {
                QString det1="用户名或密码错误";
                det1 = tr("<font size='6' color='white'>") + det1;
                det1 += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                QMessageBox msgbox1(QMessageBox::Information,"",det1);
                msgbox1.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                msgbox1.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                QLabel *Lable2;
                Lable2=new QLabel(this);
                Lable2->resize(200,50);
                Lable2->setGeometry(380,380,200,50);
                msgbox1.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
                msgbox1.move(globalPos1.x(),globalPos1.y());
                //qDebug() << msgbox.rect().width()<< endl;
                //qDebug() << msgbox.rect().height()<< endl;
                QTimer::singleShot(3000,&msgbox1,SLOT(accept()));
                msgbox1.addButton(QMessageBox::Ok);
                msgbox1.button(QMessageBox::Ok)->hide();
                msgbox1.exec();
                QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                setEnabled(true);
                ui->rememberPasssword->installEventFilter(this);
                ui->signUp->installEventFilter(this);
                ui->qrLabel->installEventFilter(this);
                ui->mim->installEventFilter(this);
                ui->setting->installEventFilter(this);
                ui->close->installEventFilter(this);
                ui->passwordBack->installEventFilter(this);
                ui->logInButton->installEventFilter(this);
                ui->return_back1->installEventFilter(this);
                ui->getVerificationCode->installEventFilter(this);
                ui->next1->installEventFilter(this);
                ui->duckLabel->show();
                ui->duckLabel->update();
            }

        }
    });

}



