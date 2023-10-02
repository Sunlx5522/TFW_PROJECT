#include "findpassword.h"
#include "ui_findpassword.h"
#include <QParallelAnimationGroup>
#include <QTcpSocket>
#include "widget.h"
extern Widget* ww;
extern findpassword * ffd;
extern QString internetRemoteAddress;
extern QString serveRemoteAddress;
findpassword::findpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findpassword)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("findpassword");                                           //登录窗口名
    setWindowFlags(Qt::FramelessWindowHint | windowFlags()|Qt::WindowStaysOnTopHint);                          //去窗口边框
    setAttribute(Qt::WA_TranslucentBackground);                                       //把窗口背景设置为透明;

    ui->close->installEventFilter(this);
    ui->close->setAttribute(Qt::WA_Hover,true);                                       //开启悬停事件
    ui->commit_2->installEventFilter(this);
    ui->commit_2->setAttribute(Qt::WA_Hover,true);                                       //开启悬停事件
    ui->changePassword->installEventFilter(this);
    ui->changePassword->setAttribute(Qt::WA_Hover,true);                                       //开启悬停事件

    //"[a-zA-Z0-9\u4e00-\u9fa5]+"
    ui->accout_line->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->passwordProtect1->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->passwordProtect2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->passwordProtect3->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->newpassword1->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->newpassword2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制



    tcpsocket = new QTcpSocket(this);

}

findpassword::~findpassword()
{
    delete ui;
    delete validator;
    ww->refresh();
}


bool findpassword::eventFilter(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj) == ui->close)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            ffd->close();
           }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/close2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img


        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
    }
    else if(qobject_cast<QPushButton*>(obj) == ui->commit_2)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if((!ui->accout_line->text().isEmpty())&&(!ui->passwordProtect1->text().isEmpty())&&(!ui->passwordProtect2->text().isEmpty())&&(!ui->passwordProtect3->text().isEmpty()))
            {

                myAccount = ui->accout_line->text();
                passwordp1 = ui->passwordProtect1->text();
                passwordp2 = ui->passwordProtect2->text();
                passwordp3 = ui->passwordProtect3->text();

                tcpServerConnect();
                sendMessage("findpassword");
            }
            else
            {
                ww->setplacehodetext(ui->accout_line);
                ww->setplacehodetext(ui->passwordProtect1);
                ww->setplacehodetext(ui->passwordProtect2);
                ww->setplacehodetext(ui->passwordProtect3);
                if(ui->accout_line->text().isEmpty())
                {
                    ui->accout_line->setPlaceholderText("请输入账号");
                }
                if(ui->passwordProtect1->text().isEmpty())
                {
                    ui->passwordProtect1->setPlaceholderText("请输入密保一");
                }
                if(ui->passwordProtect2->text().isEmpty())
                {
                    ui->passwordProtect2->setPlaceholderText("请输入密保二");
                }
                if(ui->passwordProtect3->text().isEmpty())
                {
                    ui->passwordProtect3->setPlaceholderText("请输入密保三");
                }
            }


        }
    }

    else if(qobject_cast<QPushButton*>(obj) == ui->changePassword)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            if((!ui->newpassword1->text().isEmpty())&&(!ui->newpassword2->text().isEmpty()))
            {

                myAccount = ui->accout_line->text();
                newpassword1=ui->newpassword1->text();
                newpassword2=ui->newpassword2->text();
                if(newpassword1==newpassword2)
                {
                tcpServerConnect();
                sendMessage("changepassword");
                }
                else
                {
                    ui->newpassword1->clear();
                    ui->newpassword2->clear();
                    update();
                    ww->setplacehodetext(ui->newpassword1);
                    ww->setplacehodetext(ui->newpassword2);
                    ui->newpassword1->setPlaceholderText("密码不一致");
                    ui->newpassword2->setPlaceholderText("密码不一致");
                }
            }
            else
            {
                ww->setplacehodetext(ui->newpassword1);
                ww->setplacehodetext(ui->newpassword2);
                if(ui->newpassword1->text().isEmpty())
                {
                    ui->newpassword1->setPlaceholderText("请输入新密码");
                }
                if(ui->newpassword2->text().isEmpty())
                {
                    ui->newpassword2->setPlaceholderText("请确认新密码");
                }
            }


        }
    }

    return QWidget::eventFilter(obj,event);
}



void findpassword::tcpServerConnect()
{
    delete tcpsocket;
    tcpsocket = nullptr;
    //实例化socket
    tcpsocket = new QTcpSocket(this);
    //断开现有连接
    tcpsocket->abort();
    //连接到本地的7777端口
    tcpsocket->connectToHost(serveRemoteAddress, 55418);
    //有可读信息，发送readyRead()
    connect(tcpsocket,&QTcpSocket::readyRead,this,&findpassword::readMessage);
}

void findpassword::sendMessage(QString Msg)
{
    qDebug() << "FindPassword::sendMessage:发送消息";
    if(Msg == "findpassword"){
        //初始化界面
        QString string = "findpassword|" + myAccount;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "FindPassword::sendMessage:" << string;
        //发送信息
        tcpsocket->write(message);
    }
    else if(Msg == "changepassword")
    {
        QString temp=myAccount+"___"+newpassword1;
        QString string = "changepassword|" + temp;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "FindPassword::sendMessage:" << string;
        //发送信息
        tcpsocket->write(message);
    }
    qDebug() << "FindPassword::sendMessage:发送完成";
}
void findpassword::readMessage()
{
    //实例化套接字的输入流，读信息
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_4);
    qDebug() << "FindPassword::readMessage:读取消息";
    QString greeting;
    QString account;
    QString password;
    //将信息写入greeting读取信息
    in >> greeting;
    //读取的信息
    qDebug() << "FindPassword::readMessage:" << greeting;
    //字符串分割
    QStringList msg = greeting.split("|");
    if(msg[0] == "findpassword"){
        account = msg[1];
        password = msg[2];
        QString pp1=msg[3];
        QString pp2=msg[4];
        QString pp3=msg[5];
        qDebug() << account;
        if(myAccount==account)
        {
        if((pp1==passwordp1)&&(pp2==passwordp2)&&(pp3==passwordp3)){
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
            ui->passwordback->setText(password);
        }
        else
        {
            int currentIndex = ui->stackedWidget->currentIndex();
            int windowWidth = ui->stackedWidget->widget(currentIndex)->width();
            int windowHieght = ui->stackedWidget->widget(currentIndex)->height();
            int NextIndex = currentIndex + 2;
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
            ui->passwordback->setText(password);
            ui->textEdit->append("您输入的密保有误");
            ui->textEdit->append("密码无法进行找回");
            ui->textEdit->append("请您和工作人员联系");
            ui->textEdit->append("拨打:+86 13894980185");
            ui->textEdit->append("提供诸如所在地 注册号码 生日等信息进行解封");
            ui->textEdit->append("为了操作安全 我们会对您的找回信用进行评估");
            ui->textEdit->append("24小时后 您将收到我们的电话");
        }
        }
    }else if(msg[0] == "changepassword"){
         account = msg[1];
         if(account==myAccount)
         {
             ui->newpassword1->clear();
             ui->newpassword2->clear();
             ui->display->setText("修改成功");
             update();
         }
    }
    qDebug() << "FindPassword::readMessage:读取完成";
}