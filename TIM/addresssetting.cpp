#include "addresssetting.h"
#include"widget.h"
#include"address.h"
#include<QParallelAnimationGroup>
#include "ui_addresssetting.h"

extern Widget* ww;
extern addressSetting* bb;
extern QString internetRemoteAddress;
extern QString serveRemoteAddress;

addressSetting::addressSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addressSetting)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    this->setWindowTitle("addressSetting");                                           //登录窗口名
    setWindowFlags(Qt::FramelessWindowHint | windowFlags()|Qt::WindowStaysOnTopHint);                          //去窗口边框
    setAttribute(Qt::WA_TranslucentBackground);                                       //把窗口背景设置为透明;
    ui->display_screen->append("当前互联网监测地址");
    ui->display_screen->append(internetRemoteAddress);
    ui->display_screen_2->append("当前远端服务器地址");
    ui->display_screen_2->append(serveRemoteAddress);
    ui->LineEdit1->setText(internetRemoteAddress);
    ui->LineEdit_2->setText(serveRemoteAddress);
    ui->LineEdit1->installEventFilter(this);
    ui->LineEdit_2->installEventFilter(this);
    ui->reset1->installEventFilter(this);
    ui->reset2->installEventFilter(this);
    ui->confirm1->installEventFilter(this);
    ui->confirm2->installEventFilter(this);
    ui->close->installEventFilter(this);
    ui->close->setAttribute(Qt::WA_Hover,true);                                       //开启悬停事件
}


addressSetting::~addressSetting()
{
    delete ui;
    ww->refresh();
}


void addressSetting::situationUpdate()
{
 ui->display_screen->clear();
 ui->display_screen_2->clear();
 ui->display_screen->append("当前互联网监测地址");
 ui->display_screen->append(internetRemoteAddress);
 ui->display_screen_2->append("当前远端服务器地址");
 ui->display_screen_2->append(serveRemoteAddress);
 update();
}

bool addressSetting::eventFilter(QObject *obj, QEvent *event)
{
    if(qobject_cast<QPushButton*>(obj) == ui->reset1)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
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
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->reset2)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            int currentIndex = ui->stackedWidget_2->currentIndex();
            int windowWidth = ui->stackedWidget_2->widget(currentIndex)->width();
            int windowHieght = ui->stackedWidget_2->widget(currentIndex)->height();
            int NextIndex = currentIndex + 1;
            ui->stackedWidget_2->setCurrentIndex(NextIndex);
            ui->stackedWidget_2->widget(currentIndex)->show();
            QPropertyAnimation* animation1;
            QPropertyAnimation* animation2;
            QParallelAnimationGroup* group = new QParallelAnimationGroup;
            animation1 = new QPropertyAnimation(ui->stackedWidget_2->widget(currentIndex),"geometry");
            animation1->setDuration(700);
            animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
            animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
            animation2 =new QPropertyAnimation(ui->stackedWidget_2->widget(NextIndex), "geometry");
            animation2->setDuration(700);
            animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
            animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->start();
            group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
            //connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->confirm1)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            internetRemoteAddress=ui->LineEdit1->text();
            situationUpdate();
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
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->confirm2)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            serveRemoteAddress=ui->LineEdit_2->text();
            situationUpdate();
            int currentIndex = ui->stackedWidget_2->currentIndex();
            int windowWidth = ui->stackedWidget_2->widget(currentIndex)->width();
            int windowHieght = ui->stackedWidget_2->widget(currentIndex)->height();
            int PreIndex = currentIndex - 1;
            ui->stackedWidget_2->setCurrentIndex(PreIndex);
            ui->stackedWidget_2->widget(currentIndex)->show();
            QPropertyAnimation* animation1;
            QPropertyAnimation* animation2;
            QParallelAnimationGroup* group = new QParallelAnimationGroup;
            animation1 = new QPropertyAnimation(ui->stackedWidget_2->widget(currentIndex),"geometry");
            animation1->setDuration(700);
            animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
            animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
            animation2 =new QPropertyAnimation(ui->stackedWidget_2->widget(PreIndex), "geometry");
            animation2->setDuration(700);
            animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
            animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->start();
            group->setProperty("widget", QVariant::fromValue(ui->stackedWidget->widget(currentIndex)));
            //connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->close)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            bb->close();
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
