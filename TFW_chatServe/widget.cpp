#include "MD5.h"                                                                                   //校验头文件
#include <QMenu>                                                                                   //右键菜自定义单
#include <string>                                                                                  //辅助MD5的实现
#include <QDebug>                                                                                  //调试器
#include <QLabel>                                                                                  //控件头文件
#include <string>                                                                                  //字符串
#include <QImage>                                                                                  //图像头文件
#include <QTimer>                                                                                  //qt计时器
#include <QPoint>                                                                                  //qt空间点
#include <QAction>                                                                                 //qt动作链接
#include <QLayout>                                                                                 //qt布局
#include <QString>                                                                                 //qt字符串头文件
#include "widget.h"                                                                                //widget页面
#include <QHostInfo>                                                                               //qt网络测试
#include <QClipboard>                                                                              //未知头文件
#include "userlist.h"                                                                              //用户列表
#include <QByteArray>                                                                              //字符串转化头文件
#include "ui_widget.h"                                                                             //widget设计师页面
#include <QMessageBox>                                                                             //用于预留接口
#include <QApplication>                                                                            //qt应用头文件
#include <QSqlQueryModel>                                                                          //数据库模型
#include <QDesktopWidget>                                                                          //桌面设计头文件
#include <QPropertyAnimation>                                                                      //动画时间头文件
#include <QGraphicsBlurEffect>                                                                     //显卡渲染头文件
#include <QParallelAnimationGroup>                                                                 //动画群盒子头文件
#include <QGraphicsDropShadowEffect>                                                               //显卡模糊显示头文件
#include <QRegularExpressionValidator>                                                             //qt规范表达
extern UserList * uu;
extern QApplication a;                                                                             //应用名

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{

    //ui与项目链接
    ui->setupUi(this);

    //主窗口属性设置
    setMouseTracking(true);                                                                        //窗口可进行鼠标追踪，以进行拖动
    this->setWindowTitle("TFW_chatServe");                                                         //登录窗口名
    setAttribute(Qt::WA_TranslucentBackground);                                                    //把窗口背景设置为透明;
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());                                       //去窗口边框

    //输入框输入限制
    ui->accountLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));             //输入限制
    ui->passwordLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));            //输入限制

    //动画独立申请空间
    animation  = new QPropertyAnimation(this, "pos");                                              //动画效果
    animation1 = new QPropertyAnimation(this, "windowOpacity");
    animation2 = new QPropertyAnimation(this, "windowOpacity");
    animation3 = new QPropertyAnimation(this, "windowOpacity");

    //动画独立属性设置

    animation->setDuration(0);                                                                     //设置动画持续时间（毫秒）//动画效果

    animation1->setDuration(1000);
    animation1->setKeyValueAt(0, 1);
    animation1->setKeyValueAt(0.1, 0.9);
    animation1->setKeyValueAt(0.2, 0.8);
    animation1->setKeyValueAt(0.3, 0.7);
    animation1->setKeyValueAt(0.4, 0.6);
    animation1->setKeyValueAt(0.5, 0.5);
    animation1->setKeyValueAt(0.6, 0.4);
    animation1->setKeyValueAt(0.7, 0.3);
    animation1->setKeyValueAt(0.8, 0.2);
    animation1->setKeyValueAt(0.9, 0.1);
    animation1->setKeyValueAt(1, 0);
    connect(animation1, SIGNAL(finished()), this, SLOT(showMinimized()));

    animation2->setDuration(1000);
    animation2->setKeyValueAt(0, 1);
    animation2->setKeyValueAt(0.1, 0.9);
    animation2->setKeyValueAt(0.2, 0.8);
    animation2->setKeyValueAt(0.3, 0.7);
    animation2->setKeyValueAt(0.4, 0.6);
    animation2->setKeyValueAt(0.5, 0.5);
    animation2->setKeyValueAt(0.6, 0.4);
    animation2->setKeyValueAt(0.7, 0.3);
    animation2->setKeyValueAt(0.8, 0.2);
    animation2->setKeyValueAt(0.9, 0.1);
    animation2->setKeyValueAt(1, 0);
    connect(animation2, SIGNAL(finished()), this, SLOT(close()));

    animation3->setDuration(1000);
    animation3->setKeyValueAt(0,0);
    animation3->setKeyValueAt(0.1,0.1);
    animation3->setKeyValueAt(0.2,0.2);
    animation3->setKeyValueAt(0.3,0.3);
    animation3->setKeyValueAt(0.4,0.4);
    animation3->setKeyValueAt(0.5,0.5);
    animation3->setKeyValueAt(0.6,0.6);
    animation3->setKeyValueAt(0.7,0.7);
    animation3->setKeyValueAt(0.8,0.8);
    animation3->setKeyValueAt(0.9,0.9);
    animation3->setKeyValueAt(1,1);

    //控件属性设置

    ui->mim->setScaledContents(true);                                                              //控件图片自适应大小
    ui->close->setScaledContents(true);                                                            //控件图片自适应大小
    ui->userImage->setScaledContents(true);                                                        //控件图片自适应大小
    ui->search->setScaledContents(true);                                                        //控件图片自适应大小

    ui->mim->setAttribute(Qt::WA_Hover,true);                                                      //开启悬停事件
    ui->close->setAttribute(Qt::WA_Hover,true);                                                    //开启悬停事件
    ui->search->setAttribute(Qt::WA_Hover,true);                                                   //开启悬停事件

    ui->mim->installEventFilter(this);                                                             //将qlable设置点击事件
    ui->close->installEventFilter(this);                                                           //将qlable设置点击事件
    ui->userView->installEventFilter(this);                                                        //将qlable设置点击事件ui->tableView->installEventFilter(this);                                                       //将qlable设置点击事件
    ui->pushButton->installEventFilter(this);                                                      //将qlable设置点击事件
    ui->returnBack->installEventFilter(this);                                                      //将qlable设置点击事件
    ui->send_button->installEventFilter(this);                                                     //将qlable设置点击事件
    ui->logInButton->installEventFilter(this);                                                     //将qlable设置点击事件
    ui->startButton->installEventFilter(this);                                                     //将qlable设置点击事件
    ui->close_button->installEventFilter(this);                                                    //将qlable设置点击事件
    ui->clear_button->installEventFilter(this);                                                    //将qlable设置点击事件
    ui->search->installEventFilter(this);                                                          //将qlable设置点击事件
    ui->returnToSum->installEventFilter(this);                                                     //将qlable设置点击事件

    blureffect1=new QGraphicsBlurEffect;                                                           //模糊特效
    blureffect1->setBlurRadius(10);	                                                               //数值越大，越模糊
    ui->frame->setGraphicsEffect(blureffect1);

    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));

    //实例化network



    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); // 或 QAbstractItemView::MultiSelection
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);



    contextMenu = new QMenu(ui->tableView);
    contextMenu->setStyleSheet("QMenu { background-color: #AEEEEE; /* 背景色 */ }");
    copyAction  = new QAction("复制", ui->tableView);

    contextMenu->addAction(copyAction);

    QObject::connect(copyAction, &QAction::triggered, this, &Widget::onCopyActionTriggered);
    connect(ui->tableView, &QWidget::customContextMenuRequested, this, &Widget::showContextMenu);



    think = new QMovie();
    proxyModel = new QSortFilterProxyModel(this);
    setplacehodetext(ui->accountLineEdit);
    setplacehodetext(ui->passwordLineEdit);
    animation3->start();                                                                           //渐变动画，程序正式启动



}

void Widget::setplacehodetext(QLineEdit *a)
{
    QPalette palette = a->palette();
    palette.setColor(QPalette::Normal, QPalette::PlaceholderText, "#FFFAFA");
    a->setPalette(palette);
}



//析构函数
Widget::~Widget()
{

    delete ui;
    qDebug() << "释放server";

    delete animation ;                                                                             //拖动动画
    delete animation1;                                                                             //最小化动画
    delete animation2;                                                                             //关闭动画
    delete animation3;                                                                             //启动动画
    delete blureffect1; 
    delete think;
    delete proxyModel;
    if(listenFlag_check == false && listenFlag_news == false&&listenFlag_surface == false &&listenFlag_Chatnews == false)
    {
        ;
    }
    else
    {
        listenFlag_check = false;
        listenFlag_news = false;
        listenFlag_surface = false;
        listenFlag_Chatnews = false;
        if(server_news){delete server_news;}
        if(client_news){delete client_news;}
        if(server_check){delete server_check;}
        if(server_surface){delete server_surface;}
        if(server_Chatnews){delete server_Chatnews;}
        if(client_Chatnews){delete client_Chatnews;}
        // 删除clients_news中的所有QTcpSocket对象
        for (int i = 0; i < clients_news->size(); ++i) {
            delete (*clients_news)[i];
        }
        if(clients_news){delete clients_news;}
        // 删除clients_surface中的所有QTcpSocket对象
        for (int i = 0; i < clients_surface->size(); ++i) {
            delete (*clients_surface)[i];
        }
        if(clients_surface){delete clients_surface;}
        // 删除clients_Chatnews中的所有QTcpSocket对象
        for (int i = 0; i < clients_Chatnews->size(); ++i) {
            delete (*clients_Chatnews)[i];
        }
        if(clients_Chatnews){delete clients_Chatnews;}
        server_news=nullptr;
        client_news=nullptr;
        server_check=nullptr;
        client_check=nullptr;
        server_surface=nullptr;
        client_surface=nullptr;
        server_Chatnews=nullptr;
        client_Chatnews=nullptr;
        clients_news=nullptr;
        clients_surface=nullptr;
        clients_Chatnews=nullptr;
    }
}

void Widget::shouError()
{
    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
    QString det="数据库无法创建或寻址";
    det = tr("<font size='6' color='white'>") + det;
    det += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
    QMessageBox msgbox(QMessageBox::Information,"",det);//将QMessageBox实例化出来，好方便后面setStyleSheet
    //下面补上Qss样式表的设置写法即可
    msgbox.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
    msgbox.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    QLabel *Lable1;
    Lable1=new QLabel(this);
    Lable1->resize(200,50);
    Lable1->setGeometry(375,400,200,50);
    msgbox.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
    QPoint globalPos = Lable1->mapToGlobal(QPoint(0, 0));
    msgbox.move(globalPos.x(),globalPos.y());
    //qDebug() << msgbox.rect().width()<< endl;
    //qDebug() << msgbox.rect().height()<< endl;
    QTimer::singleShot(3000,&msgbox,SLOT(accept()));
    msgbox.addButton(QMessageBox::Ok);
    msgbox.button(QMessageBox::Ok)->hide();
    msgbox.exec();
    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
}

//自定义点击事件
bool Widget::eventFilter(QObject *obj, QEvent *event)
{

    if(qobject_cast<QLabel*>(obj) == ui->close)
    {

        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/close.png");                                                  //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img));                                        //将图片放入label，使用setPixmap,注意指针*img
            setEnabled(false);
            ui->mim->removeEventFilter(this);                                                             //将qlable设置点击事件
            ui->close->removeEventFilter(this);                                                           //将qlable设置点击事件
            ui->userView->removeEventFilter(this);                                                        //将qlable设置点击事件
            ui->pushButton->removeEventFilter(this);                                                      //将qlable设置点击事件
            ui->returnBack->removeEventFilter(this);                                                      //将qlable设置点击事件
            ui->send_button->removeEventFilter(this);                                                     //将qlable设置点击事件
            ui->logInButton->removeEventFilter(this);                                                     //将qlable设置点击事件
            ui->startButton->removeEventFilter(this);                                                     //将qlable设置点击事件
            ui->close_button->removeEventFilter(this);                                                    //将qlable设置点击事件
            ui->clear_button->removeEventFilter(this);                                                    //将qlable设置点击事件
            animation2->start();
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/close2.png");                                                 //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img));                                        //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage;                                                                 //新建一个image对象
            img->load(":/new/prefix1/close1.png");                                                  //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img));                                         //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/close.png");                                                  //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img));                                        //将图片放入label，使用setPixmap,注意指针*img

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
            QString l1;
            QString l2;
            char a1[40];
            char b1[40];
            unsigned char *a;
            unsigned char *b;
            l1=ui->accountLineEdit->text();
            l2=ui->passwordLineEdit->text();
            QByteArray a2=l1.toUtf8();
            QByteArray b2=l2.toUtf8();
            a = reinterpret_cast<unsigned char*>(a2.data());
            b = reinterpret_cast<unsigned char*>(b2.data());
            MD5Function (a,a1);
            MD5Function (b,b1);

            QLabel *thinkLable;
            thinkLable=new QLabel(this);

            QSize size(512,256);
            thinkLable->setFixedSize(size);
            thinkLable->setScaledContents(true);

            thinkLable->setGeometry(244,372,512,256);

            QGraphicsDropShadowEffect *shadow_effect;
            shadow_effect=new QGraphicsDropShadowEffect(this);
            shadow_effect->setOffset(0, 0);
            shadow_effect->setColor(QColor(0,0,0, 255));//黑色
            shadow_effect->setBlurRadius(20);
            thinkLable->setGraphicsEffect(shadow_effect);

            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));

            thinkLable->show();

            //ui->gridLayout->addWidget(thinkLable);
            // 设置布局管理器的对齐方式为居中
            delete think;
            think = new QMovie();
            think->setScaledSize(thinkLable->size());
            think->setFileName(":/new/prefix1/duck.gif");
            think->setSpeed(200);
            thinkLable->setMovie(think);
            think->start();
            setEnabled(false);
            ui->mim->removeEventFilter(this);
            ui->close->removeEventFilter(this);
            ui->logInButton->removeEventFilter(this);                                              //将qlable设置点击事件

            QObject::connect(think, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画 执行一次就结束
                if (frameNumber == think->frameCount() - 1) {
                    think->stop();
                    delete shadow_effect;
                    delete thinkLable;
                    if(networkAbleFlag)
                    {
                    if(strcmp(a1,"20b02d94500c9aecf2cd67a9a115fe77")==0&&strcmp(b1,"1b6a259e20641a555e45803c8ea4f88a")==0)
                    {

                       QString det="登录成功";
                       det = tr("<font size='6' color='white'>") + det;
                       det += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                       QMessageBox msgbox(QMessageBox::Information,"",det);                        //将QMessageBox实例化出来，好方便后面setStyleSheet
                       //下面补上Qss样式表的设置写法即可
                       msgbox.setIconPixmap(QPixmap(":/new/prefix1/welcome.png"));
                       msgbox.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                       QLabel *Lable1;
                       Lable1=new QLabel(this);
                       Lable1->resize(200,50);
                       Lable1->setGeometry(420,400,200,50);
                       msgbox.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                       QPoint globalPos = Lable1->mapToGlobal(QPoint(0, 0));
                       msgbox.move(globalPos.x(),globalPos.y());
                       //qDebug() << msgbox.rect().width()<< endl;
                       //qDebug() << msgbox.rect().height()<< endl;
                       QTimer::singleShot(1500,&msgbox,SLOT(accept()));
                       msgbox.addButton(QMessageBox::Ok);
                       msgbox.button(QMessageBox::Ok)->hide();
                       msgbox.exec();

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
                       QObject::connect(animation2, &QPropertyAnimation::finished, [=](){
                       QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                       });
                       group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
                       delete Lable1;
                       Lable1 = nullptr;
                       //connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
                    }
                    else
                    {

                       QString det="用户名或密码错误";
                       det = tr("<font size='6' color='white'>") + det;
                       det += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                       QMessageBox msgbox(QMessageBox::Information,"",det);//将QMessageBox实例化出来，好方便后面setStyleSheet
                       //下面补上Qss样式表的设置写法即可
                       msgbox.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                       msgbox.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                       QLabel *Lable1;
                       Lable1=new QLabel(this);
                       Lable1->resize(200,50);
                       Lable1->setGeometry(375,400,200,50);
                       msgbox.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                       QPoint globalPos = Lable1->mapToGlobal(QPoint(0, 0));
                       msgbox.move(globalPos.x(),globalPos.y());
                       //qDebug() << msgbox.rect().width()<< endl;
                       //qDebug() << msgbox.rect().height()<< endl;
                       QTimer::singleShot(1500,&msgbox,SLOT(accept()));
                       msgbox.addButton(QMessageBox::Ok);
                       msgbox.button(QMessageBox::Ok)->hide();
                       msgbox.exec();
                       QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                       delete Lable1;
                       Lable1 = nullptr;
                    }
                    setEnabled(true);
                    ui->logInButton->installEventFilter(this);
                    ui->close->installEventFilter(this);
                    ui->mim->installEventFilter(this);

                }
                else
                {
                    QString det="互联网断开，无法部署服务器";
                    det = tr("<font size='6' color='white'>") + det;
                    det += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                    QMessageBox msgbox(QMessageBox::Information,"",det);                        //将QMessageBox实例化出来，好方便后面setStyleSheet
                    //下面补上Qss样式表的设置写法即可
                    msgbox.setIconPixmap(QPixmap(":/new/prefix1/warning.png"));
                    msgbox.setWindowFlags(Qt::FramelessWindowHint | windowFlags());
                    QLabel *Lable1;
                    Lable1=new QLabel(this);
                    Lable1->resize(200,50);
                    Lable1->setGeometry(325,400,200,50);
                    msgbox.setAttribute(Qt::WA_TranslucentBackground);                          //把窗口背景设置为透明;
                    QPoint globalPos = Lable1->mapToGlobal(QPoint(0, 0));
                    msgbox.move(globalPos.x(),globalPos.y());
                    //qDebug() << msgbox.rect().width()<< endl;
                    //qDebug() << msgbox.rect().height()<< endl;
                    QTimer::singleShot(1500,&msgbox,SLOT(accept()));
                    msgbox.addButton(QMessageBox::Ok);
                    msgbox.button(QMessageBox::Ok)->hide();
                    msgbox.exec();
                    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
                    delete Lable1;
                    Lable1 = nullptr;
                    setEnabled(true);
                    ui->logInButton->installEventFilter(this);
                    ui->close->installEventFilter(this);
                    ui->mim->installEventFilter(this);
                }
                }
            });
        }
    }




    else if(qobject_cast<QPushButton*>(obj) == ui->startButton)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if(listenFlag_check == true && listenFlag_news == true&&listenFlag_surface == true &&listenFlag_Chatnews == true)
            {
                ui->display_screen->append("服务器已开启");
            }
            else
            {
            server_news = new QTcpServer(this);
            client_news = new QTcpSocket(this);
            server_check = new QTcpServer(this);
            server_surface = new QTcpServer(this);
            client_surface = new QTcpSocket(this);
            server_Chatnews = new QTcpServer(this);
            client_Chatnews = new QTcpSocket(this);
            clients_news = new QList<QTcpSocket *>;
            clients_surface = new QList<QTcpSocket *>;
            clients_Chatnews =new QList<QTcpSocket *>;
            //监听任何连接上5555端口的ip, 成功返回true, 用于账号检验
            listenFlag_check = server_check->listen(QHostAddress::Any, 5555);
            //监听任何连接上6666端口的ip，成功返回true，用于转发消息
            listenFlag_news = server_news->listen(QHostAddress::Any, 6666);
            //监听所有连接7777端口的ip，成功返回true，用于初始化界面
            listenFlag_surface = server_surface->listen(QHostAddress::Any, 7777);
            //监听所有连接8888端口上的ip，成功返回true, 用于群聊
            listenFlag_Chatnews = server_Chatnews->listen(QHostAddress::Any, 8888);
            if(listenFlag_check == true && listenFlag_news == true&&listenFlag_surface == true &&listenFlag_Chatnews == true){
                qDebug() << "服务器已打开";
                qDebug() << "打开端口：5555 6666 7777 8888";
                ui->display_screen->append("打开端口：5555(账号检测） 6666(转发消息) 7777(初始化界面) 8888(群聊)");
                ui->display_screen->append("服务器可以正常服务");
                ui->tip_Label->setText("服务器状态：开启");
                ui->display_screen->append("成功开启服务器");
                qDebug() << "服务状态：开启";

                //新客户端连接，发射newConnect信号
                connect(server_check, &QTcpServer::newConnection,
                           this, &Widget::newClient_check);                                        //一旦有连接请求，马上执行对应函数
                connect(server_news, SIGNAL(newConnection()),
                           this, SLOT(newConnect_news()));
                connect(server_surface, SIGNAL(newConnection()),
                        this, SLOT(newConnect_surface()));
                connect(server_Chatnews, SIGNAL(newConnection()),
                            this, SLOT(newConnect_Chatnews()));
                //服务端销毁
                connect(server_check, &QTcpServer::destroyed,
                        this,&Widget::destoryServer_check);
                qDebug() << "等待连接...";
            }
            else
            {
                ui->tip_Label->setText("服务器状态：关闭");
                qDebug() << "开启服务器失败";
                ui->display_screen->append("开启服务器失败");
            }
            }
        }

    }

    else if(qobject_cast<QPushButton*>(obj) == ui->close_button)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if(listenFlag_check == false && listenFlag_news == false&&listenFlag_surface == false &&listenFlag_Chatnews == false)
            {
                ui->display_screen->append("服务器已关闭");
            }
            else
            {
            listenFlag_check = false;
            listenFlag_news = false;
            listenFlag_surface = false;
            listenFlag_Chatnews = false;
            if(server_news){delete server_news;}
            if(client_news){delete client_news;}
            if(server_check){delete server_check;}
            if(server_surface){delete server_surface;}
            if(server_Chatnews){delete server_Chatnews;}
            if(client_Chatnews){delete client_Chatnews;}
            // 删除clients_news中的所有QTcpSocket对象
            for (int i = 0; i < clients_news->size(); ++i) {
                delete (*clients_news)[i];
            }
            if(clients_news){delete clients_news;}
            // 删除clients_surface中的所有QTcpSocket对象
            for (int i = 0; i < clients_surface->size(); ++i) {
                delete (*clients_surface)[i];
            }
            if(clients_surface){delete clients_surface;}
            // 删除clients_Chatnews中的所有QTcpSocket对象
            for (int i = 0; i < clients_Chatnews->size(); ++i) {
                delete (*clients_Chatnews)[i];
            }
            if(clients_Chatnews){delete clients_Chatnews;}
            server_news=nullptr;
            client_news=nullptr;
            server_check=nullptr;
            client_check=nullptr;
            server_surface=nullptr;
            client_surface=nullptr;
            server_Chatnews=nullptr;
            client_Chatnews=nullptr;
            clients_news=nullptr;
            clients_surface=nullptr;
            clients_Chatnews=nullptr;

            ui->tip_Label->setText("服务器状态：关闭");
            ui->display_screen->append("关闭端口：5555 6666 7777 8888");
            ui->display_screen->append("成功关闭服务器");
            }
        }
    }

    else if(qobject_cast<QPushButton*>(obj) == ui->clear_button)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
             ui->display_screen->clear();
        }
    }

    else if(qobject_cast<QPushButton*>(obj) == ui->pushButton)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            user->initDB();
            ui->display_screen->append("用户状态重置成功");
        }
    }

    else if(qobject_cast<QPushButton*>(obj) == ui->userView)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->userView->removeEventFilter(this);
            ui->returnBack->removeEventFilter(this);
            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
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
            QObject::connect(animation2, &QPropertyAnimation::finished, [=](){
            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
            ui->userView->installEventFilter(this);
            ui->returnBack->installEventFilter(this);
            });
            group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
        }

    }


    else if(qobject_cast<QPushButton*>(obj) == ui->send_button)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            qDebug() << "群发";
            if(listenFlag_check == true && listenFlag_news == true&&listenFlag_surface == true &&listenFlag_Chatnews == true){
                QString msg = "server";
                msg = msg + "|" + ui->message_textEdit->toPlainText() + "|" + "All";
                sendMessage_news(msg);
                ui->display_screen->append("群发:"+ui->message_textEdit->toPlainText());
                ui->message_textEdit->clear();
                qDebug() << "群发成功";
            }
            else
            {
              ui->message_textEdit->clear();
              ui->display_screen->append("群发失败 服务未开启");
              qDebug() << "群发失败";
            }
        }

    }

    else if(qobject_cast<QPushButton*>(obj) == ui->returnToSum)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->tableView->setModel(user->model);
        }

    }


    else if(qobject_cast<QPushButton*>(obj) == ui->returnBack)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->userView->removeEventFilter(this);
            ui->returnBack->removeEventFilter(this);
            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
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
            QObject::connect(animation2, &QPropertyAnimation::finished, [=](){
            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
            ui->userView->installEventFilter(this);
            ui->returnBack->installEventFilter(this);
            });
            group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
        }

    }


    else if(qobject_cast<QLabel*>(obj) == ui->mim)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/mim.png");                                                    //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img
            animation1->start();}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage;                                                                //新建一个image对象

            img->load(":/new/prefix1/mim2.png");                                                   //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage;                                                                //新建一个image对象

            img->load(":/new/prefix1/mim1.png");                                                   //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/mim.png");                                                    //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img
        }
    }


    else if(qobject_cast<QLabel*>(obj) == ui->search)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/search.png");                                                    //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->search->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img
            ui->tableView->setModel(proxyModel);
            QString r1;
            r1=ui->searchLineEdit_2->text();
            QRegExp rx(r1);  //
            proxyModel->setFilterRegExp(rx);
            proxyModel->setFilterKeyColumn(0);  // 假设 name 字段是第二列


            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage;                                                                //新建一个image对象

            img->load(":/new/prefix1/search2.png");                                                   //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->search->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage;                                                                //新建一个image对象

            img->load(":/new/prefix1/search1.png");                                                   //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->search->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage;                                                                //新建一个image对象
            img->load(":/new/prefix1/search.png");                                                    //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->search->setPixmap(QPixmap::fromImage(*img));                                          //将图片放入label，使用setPixmap,注意指针*img
        }
    }






    return QWidget::eventFilter(obj, event);  // 对于其他事件，继续默认处理;

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
            setWindowOpacity(1);                                                                   //设置透明度为1
            ui->frame->setFocus();
        }
        else
        {
            setWindowFlags(Qt::Window);
            setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
            this->showNormal();
        }
    }
}

/************************************通过数据库验证账号部分 端口 5555***************************/
//新客户连接
void Widget::newClient_check(){
    if(!listenFlag_check) return;
    qDebug() << "新客户端登陆:";
    //设置为假，用于新客户端登陆判断
    loginSuccessFlag_check = false;
    QTcpSocket *newClient;

    //得到新进来的socket
    newClient = server_check->nextPendingConnection();
    //连接标志
    clientJoinUp_check = true;


    qDebug() << "等待信息";

    //有可读信息，发射readyread信号
    connect(newClient, &QTcpSocket::readyRead, this, &Widget::readMessage_check);
    //断开连接，发射disconnect信号
    connect(newClient, &QTcpSocket::disconnected, this, &Widget::lostClient_check);

    //在客户端列表最后添加新的socket
    clients_check.push_back(newClient);
    client_check = newClient;
}

//账号验证的反馈消息
void Widget::feedbackMessage(QString msg){
    if(!listenFlag_check) {
        qDebug() << "feedbackMessage:服务端未打开";
        return;
    }
    if(!clientJoinUp_check) {
        qDebug() << "feedbackMessage:客户端未连接";
        return;
    }
    qDebug() << "feedbackMessage:发送消息";
    //添加到显示面板
    ui->display_screen->append("登录结果:"+msg);
    ui->display_screen->moveCursor(QTextCursor::End);
    ui->message_textEdit->setText("");
    //发送
    client_check->write(msg.toUtf8());
    qDebug() << "Server_send:" <<msg;
    qDebug() << "feedbackMessage:发送完成";
}

//读取
void Widget::readMessage_check(){
    qDebug() << "readMessage_check:读取信息";
    //通过信号的发出者找到相应的对象
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    QString str;
    QString account;
    QString password;
    //读取
    str = client->readAll();
    qDebug() << "readMessage_check:" << str;
    account = str.section(' ', 0, 0);//字符串分割
    password = str.section(' ', 1, 1);
    //添加到显示面板
    ui->display_screen->append("请求登陆");
    ui->display_screen->append("登陆账号：" + account);
    ui->display_screen->append("登陆密码：" + password);
    ui->display_screen->moveCursor(QTextCursor::End);                                              //注意光标移动到末尾
    qDebug() << "登陆账号：" << account;
    qDebug() << "登陆密码：" << password;

    //temp = 0 时，账号密码不匹配登陆失败，temp = 1，登陆成功， temp = 2，已经在线
    int temp = user->CheckUser(account, password);
    if(temp == 0){
        loginSuccessFlag_check = false;
        feedbackMessage("loginFail");
        qDebug() << "登陆失败";
    }else if(temp == 1){
        loginSuccessFlag_check = true;
        feedbackMessage("loginSuccess");
        qDebug() << "登陆成功";
    }else if(temp == 2){
        loginSuccessFlag_check = true;
        feedbackMessage("AlreadyOnline");
    }
    qDebug() << "readMessage_check:读取完成";
}

//删除
void Widget::lostClient_check(){
    qDebug() << "lostClient_check:登录销毁";
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    clients_check.removeOne(client);
}

//发送
void Widget::sendMessage_check(){

}

/***********************************登录成功，转发消息部分  端口 6666****************************/
//新客户端连接
void Widget::newConnect_news(){
    if(!listenFlag_news) return;
    qDebug() << "新聊天线程：";

    //得到新连接进来的socket
    client_news = server_news->nextPendingConnection();

    //添加到聊天列表
    clients_news->append(client_news);
    clientJoinUp_news = true;

    //有可读信息发送readyRead()信号
    connect(client_news, SIGNAL(readyRead()),
            this, SLOT(readMessage_news()));
    //客户端断开连接，发送disconnected()
    connect(client_news, SIGNAL(disconnected()),
            this, SLOT(lostClient_news()));

}

//读取
void Widget::readMessage_news(){
    qDebug() << "读取信息";
    QString message;
    //遍历客户端列表，所有客户端
    for(int i = 0; i < clients_news->length(); i++){
        qDebug() << "QDataStream ";
        //设置响应socket的输入流和版本
        QDataStream in(clients_news->at(i));
        in.setVersion (QDataStream::Qt_5_14);
        //读取信息，信息写入message，
        in >> message;
        //每有一个可读信息，message非空，跳出 显示
        if(!message.isEmpty()){
            qDebug() << "break";
            break;
        }
    }
    //面板显示消息
    ui->display_screen->append(tr("新消息: '%1'").arg(message));
    ui->display_screen->setAlignment(Qt::AlignLeft);
    //发送到对应客户端
    sendMessage_news(message);
    qDebug() << "Server_read:" << message;
    qDebug() << "readMessage_news:读取完成";
}

//发送
void Widget::sendMessage_news(QString information){
    if(!listenFlag_news) {
         qDebug() << "sendMessage_news:服务端未打开";
         return;
     }
     if(!clientJoinUp_news) {
         qDebug() << "sendMessage_news:客户端未连接";
         return;
     }

     qDebug() << "sendMessage_news:发送消息";
     QString str = information;
     QByteArray message;
     //设置输出流只写，并设置版本
     QDataStream out(&message,QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_5_14);
     out << str;
     //遍历客户端，嵌套字写入
     for(int i = 0; i < clients_news->length(); i++){
         clients_news->at(i)->write(message);
     }
     qDebug() << "Server_send:" << str;
     qDebug() << "sendMessage_news:发送完成";
}

//删除
void Widget::lostClient_news(){
    qDebug() << "lostClient_news:关闭聊天";
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    clients_news->removeOne(client);
    qDebug() << "lostClient_news:colse";
}

/************************************群聊 端口8888*****************************************/
//新客户端连接
void Widget::newConnect_Chatnews(){
    if(!listenFlag_Chatnews) return;
    qDebug() << "群聊线程：";

    //得到新连接进来的socket
    client_Chatnews = server_Chatnews->nextPendingConnection();

    //添加到聊天列表
    clients_Chatnews->append(client_Chatnews);
    clientJoinUp_Chatnews = true;

    //有可读信息发送readyRead()信号
    connect(client_Chatnews, SIGNAL(readyRead()),
            this, SLOT(readMessage_Chatnews()));
    //客户端断开连接，发送disconnected()
    connect(client_Chatnews, SIGNAL(disconnected()),
            this, SLOT(lostClient_Chatnews()));
}

void Widget::readMessage_Chatnews(){
    qDebug() << "读取信息";
    QString message;
    //遍历客户端列表，所有客户端
    for(int i = 0; i < clients_Chatnews->length(); i++){
        qDebug() << "QDataStream ";
        //设置响应socket的输入流和版本
        QDataStream in(clients_Chatnews->at(i));
        in.setVersion (QDataStream::Qt_5_14);
        //读取信息，信息写入message，
        in >> message;
        //每有一个可读信息，message非空，跳出 显示
        if(!message.isEmpty()){
            qDebug() << "break";
            break;
        }
    }
    //面板显示消息
    ui->display_screen->append(tr("'%1'").arg(message));
    ui->display_screen->setAlignment(Qt::AlignLeft);
    //发送到对应客户端
    sendMessage_Chatnews(message);
    qDebug() << "Server_read:" << message;
    qDebug() << "readMessage_news:读取完成";
}

void Widget::sendMessage_Chatnews(QString information){
    if(!listenFlag_Chatnews) {
         qDebug() << "sendMessage_news:服务端未打开";
         return;
     }
     if(!clientJoinUp_Chatnews) {
         qDebug() << "sendMessage_Chatnews:客户端未连接";
         return;
     }
     qDebug() << "sendMessage_Chatnews:发送消息";
     QString str = "init|";
     if(information == "init"){
         //数据库查找
         user->query->exec("select * from User");
         while(user->query->next()){
             if(user->query->value(5).toString() == "1"){
                 str = str + user->query->value(0).toString() + "|";
             }
            qDebug() << str;
         }
     }else{
         str = information;
     }
     QByteArray message;
     //设置输出流只写，并设置版本
     QDataStream out(&message,QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_5_14);
     out << str;
     //遍历客户端，嵌套字写入
     for(int i = 0; i < clients_Chatnews->length(); i++){
         clients_Chatnews->at(i)->write(message);
     }
     qDebug() << "Server_send:" << str;
     qDebug() << "sendMessage_Chatnews:发送完成";
}

//删除
void Widget::lostClient_Chatnews(){
    qDebug() << "lostClient_Chatnews:关闭聊天";
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    clients_Chatnews->removeOne(client);
    qDebug() << "lostClient_Chatnews:colse";
}

/***************************反馈界面初始信息,账号注册，退出 端口7777****************************/
//新客户端连接
void Widget::newConnect_surface(){
    if(!listenFlag_surface) return;
    qDebug() << "新客户端连接";

    //得到新连接进来的socket
    client_surface = server_surface->nextPendingConnection();

    //添加到聊天列表
    clients_surface->append(client_surface);
    clientJoinUp_surface = true;

    //有可读信息发送readyRead()信号
    connect(client_surface,SIGNAL(readyRead()),
            this, SLOT(readMessage_surface()));
    //断开连接时
    connect(client_surface, &QTcpSocket::disconnected,
            this, &Widget::lostClient_surface);
}

//读取
void Widget::readMessage_surface(){
    qDebug() << "readMessage_surface:读取信息";
    QString message;            //全部消息
    QString flag;               //标志
    QString account;            //账号
    //遍历客户端列表，所有客户端
    for(int i = 0; i < clients_surface->length(); i++){
        qDebug() << "QDataStream";
        //设置响应socket的输入流和版本
        QDataStream in(clients_surface->at(i));
        in.setVersion(QDataStream::Qt_5_14);
        //读取信息，信息写入message
        in >> message;
        //每一个可读信息，message非空，跳出
        if(!message.isEmpty()){
            qDebug() << "break";
            break;
        }
    }
    qDebug() << "readMessage_surface:" << message;
    flag = message.section('|',0,0);
    account = message.section('|',1,1);
    //添加到显示面板
    if(flag == "initSurface"){
        //包含个人信息，和好友列表
        qDebug() << "请求初始化界面";
        ui->display_screen->append("请求获取界面");
        ui->display_screen->append("登陆账号：" + account);

        QString initAccount;
        //数据库查找
        user->query->exec("select * from User");
        while(user->query->next()){
            initAccount = user->query->value(0).toString();
            if(account == initAccount){
                QString accountTemp = user->query->value(0).toString();
                QString nameTemp = user->query->value(1).toString();
                QString tmp;
                char a1[512];
                unsigned char *a;
                tmp=user->query->value(2).toString();
                QByteArray a2=tmp.toUtf8();
                a = reinterpret_cast<unsigned char*>(a2.data());
                MD5Function (a,a1);
                QString passwordTemp=QString::fromLocal8Bit(a1,512);

                QString signTemp = user->query->value(3).toString();
                QString headTemp = user->query->value(4).toString();
                QString phoneTemp = user->query->value(5).toString();
                QString birthdayTemp = user->query->value(7).toString();
                QString localTemp = user->query->value(8).toString();
                QString tagtTemp = user->query->value(9).toString();
                QString vipTemp = user->query->value(10).toString();
                initMsg = "initSurface|" + accountTemp + "|" + nameTemp + "|"
                        + passwordTemp + "|" + signTemp+ "|"+ headTemp + "|"+ phoneTemp + "|"+ birthdayTemp + "|"+ localTemp + "|"+ tagtTemp + "|"+ vipTemp;
                qDebug() << "界面初始化消息:" << initMsg;
                sendMessage_surface(initMsg);                       //发送初始化消息
                break;
            }
        }
        ui->display_screen->append("登录成功！");
    }else if(flag == "logout"){
        ui->display_screen->append("请求退出");
        ui->display_screen->append("退出账号：" + account);
        QString logoutAccount;
        //数据库查找
        user->query->exec("select *  from User");
        while(user->query->next()){
            logoutAccount = user->query->value(0).toString();
            if(account == logoutAccount){
                //更新模型视图
                user->model->setQuery("update user set state = 0 where account = '" + account + "'");
                user->model->setQuery("select * from User");
                qDebug() << "退出成功";
                break;
            }
        }
        ui->display_screen->append("退出成功");
        initMsg = "logout|" + account +"|null|null|null";
    }else if(flag == "register"){
        //新用户注册，服务器生成'账号.db'的好友列表，登录时返回给用户
        ui->display_screen->append("请求注册");
        ui->display_screen->setAlignment(Qt::AlignCenter);
        QString accountTemp = user->addUser(message);
        qDebug() << "注册成功";
        ui->display_screen->append("账号:"+accountTemp+"注册成功");
        sendMessage_surface("register|"+accountTemp);                       //发送初始化消息
    }else if(flag == "findpassword"){
        qDebug() << "找回密码";
        ui->display_screen->append("找回密码");
        QString initAccount;
        //数据库查找
        user->query->exec("select * from User");
        while(user->query->next()){
            initAccount = user->query->value(0).toString();
            if(account == initAccount){
                QString accountTemp = user->query->value(0).toString();
                QString password = user->query->value(2).toString();
                QString p1=user->query->value(13).toString();
                QString p2=user->query->value(14).toString();
                QString p3=user->query->value(15).toString();
                initMsg = "findpassword|" + accountTemp +"|"+password+ "|" + p1 + "|"
                        + p2 + "|" + p3;
                qDebug() << "账号:" << accountTemp;
                qDebug() << "找回密码:" << password;
                qDebug() << "找回操作完成";
                ui->display_screen->append("账号:"+account);
                ui->display_screen->append("找回密码:"+password);
                ui->display_screen->append("返回信息");
                ui->display_screen->append(initMsg);
                sendMessage_surface(initMsg);                       //发送初始化消息
                break;
            }
        }
    }
    else if(flag == "changepassword")
    {
        ui->display_screen->append("修改密码");
        ui->display_screen->append("请求信息:"+account);
        QString tmp=account;
        QStringList parts = tmp.split("___");
        ui->display_screen->append(parts[0]);
        ui->display_screen->append(parts[1]);
        user->query->exec("select * from User");



        QSqlQuery readQuery;
        readQuery.exec("select * from User");

        QSqlQuery updateQuery;

        while(readQuery.next()){
            if(readQuery.value(0).toString()==parts[0])
            {
                ui->display_screen->append(readQuery.value(0).toString());
                ui->display_screen->append(readQuery.value(1).toString());
                ui->display_screen->append(readQuery.value(2).toString());
                updateQuery.prepare("UPDATE User SET password = :ps WHERE account = :account");
                updateQuery.bindValue(":ps", parts[1]);
                updateQuery.bindValue(":account", parts[0]);
                updateQuery.exec();
                uu->model->setQuery("select * from User");
            }

        }

       ui->display_screen->append("修改成功");
       initMsg = "changepassword|" + parts[0];
       sendMessage_surface(initMsg);

    }
    qDebug() << "Server_read:" << message;
    qDebug() << "readMessage_surface:读取完成";
}

void Widget::sendMessage_surface(QString Msg){
    if(!listenFlag_surface) {
         qDebug() << "sendMessage_surface:服务端未打开";
         return;
     }
     if(!clientJoinUp_surface) {
         qDebug() << "sendMessage_surface:客户端未连接";
         return;
     }
     QString flag;
     flag = Msg.section('|', 0, 0);
     qDebug() << "信息为：" << Msg;
     if(flag != "initSurface" && flag != "logout" &&flag != "changepassword" &&
            flag != "findpassword" && flag != "register"){
        qDebug() << "sendMessage_surface:错误信息,不发送";
        qDebug() << "信息为:" << Msg;
        return;
     }
     qDebug() << "sendMessage_surface:发送消息";
     QByteArray message;
     //设置输出流只写，并设置版本
     QDataStream out(&message,QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_5_14);
     out << Msg;
     //遍历客户端，套接字写入
     for (int i = 0;i < clients_surface->length();i++)
     {
         qDebug() << clients_surface->length();
         clients_surface->at(i)->write(message);
     }
     qDebug() << "Server_send:" <<Msg;
     qDebug() << "sendMessage_surface:发送完成";
}

void Widget::lostClient_surface(){
    qDebug() << "lostClient_surface:销毁";
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    clients_surface->removeOne(client);
    qDebug() << "lostClient_surface:关闭";
}

/*********************************************************************************/


//释放服务器
void Widget::destoryServer_check(){
    qDebug() << "释放服务器";
    listenFlag_check = false;
    listenFlag_news = false;
    listenFlag_surface = false;
    listenFlag_Chatnews = false;
}

 void Widget::addTable(QSqlQueryModel* a)
 {
     ui->tableView->setModel(a);
 }

 void Widget::addTable_s(QSqlQueryModel *a)
 {
     proxyModel->setSourceModel(a);  // yourOriginalModel 是你原来设置给 QTableView 的 Model
 }


void Widget::onCopyActionTriggered()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();

        qDebug() << "Selected indexes: " << indexes;
    if (!indexes.isEmpty()) {
        QString text;
        for (const QModelIndex &index : indexes) {
            text += index.data().toString() + "\t";
        }
        text.chop(1); // 移除最后一个制表符
        QApplication::clipboard()->setText(text);
    }
}
void Widget::showContextMenu(const QPoint &pos) {
    qDebug() << "Context menu should be shown at: " << pos;
    contextMenu->exec(ui->tableView->mapToGlobal(pos)+ QPoint(30, 30));
}
