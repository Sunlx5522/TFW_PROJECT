#include "findpassword.h"
#include "ui_findpassword.h"
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
    tcpsocket = new QTcpSocket(this);

}

findpassword::~findpassword()
{
    delete ui;
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
    tcpsocket->connectToHost(serveRemoteAddress, 7777);
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
         qDebug() << "找回成功";
         qDebug() << "密码";
         qDebug() << password;
        }
        else
        {
            qDebug() << "找回失败";
        }
        }
    }else{
        ;
    }
    qDebug() << "FindPassword::readMessage:读取完成";
}
