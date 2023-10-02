


#include <QNetworkConfigurationManager>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsDropShadowEffect>                                                  //动画事件头文件
#include <QParallelAnimationGroup>                                                     //动画事件头文件
#include <QNetworkAccessManager>
#include <QPropertyAnimation>                                                                      //动画
#include <QRegExpValidator>                                                                        //用于输入限制
#include "addresssetting.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QElapsedTimer>                                                                           //时间
#include <QApplication>                                                                            //外部引用 关闭应用
#include <QPushButton>                                                                //按钮控件
#include <QMouseEvent>                                                                //鼠标拖动事件
#include "ui_widget.h"                                                                //与ui界面设计师的链接
#include <QCloseEvent>                                                                 //最小化动画实现辅助函数
#include <QMessageBox>                                                                 //用于预留接口
#include <QVBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QShowEvent>                                                                  //最小化动画实现辅助函数
#include "userlist.h"
#include "qrencode.h"
#include <QHostInfo>
#include "address.h"
#include <QProcess>                                                                //用于布局
#include "widget.h"                                                                   //登陆界面头文件
#include "qrcode.h"
#include <QPainter>
#include <QPalette>
#include <QFuture>
#include <QObject>                                                                     //QObject 头文件引用
#include <QPixmap>                                                                     //qlable 图片渲染
#include <QMovie>                                                                      //用于gif动画播放
#include <QLabel>                                                                      //lable相关函数
#include <QMovie>                                                                      //gif动画
#include <QLabel>                                                                     //laable控件头文件
#include <QRegExp>
#include <QValidator>
#include <QString>
#include <QSize>
#include <QImage>
#include <QTimer>
#include <QIcon>
#include "initsurface.h"
#include "findpassword.h"
#include <QDate>
#include <QRegularExpression>
#include "signUp.h"

extern signUp* ssp;

int imageCounter=1;
extern Widget* ww;
extern addressSetting* bb;
extern QApplication a;                                                                //外部变量声明 用于关闭应用
extern qrcode *cc;
extern findpassword * ffd;

extern QString internetRemoteAddress;
extern QString serveRemoteAddress;

//用于注册
QString nameTmp;
QString password1Tmp;
QString password2Tmp;
QString phoneNumberTmp;
QString signTemp;

QString birthdayDate;
QString localPlaceTemp;
QString passwordq1Temp;
QString passwordq2Temp;
QString passwordq3Temp;

QString headImageTemp="head (1).JPG";

void resetQstr()
{
    nameTmp=QString();
    password1Tmp=QString();
    password2Tmp=QString();
    phoneNumberTmp=QString();

    birthdayDate=QString();
    localPlaceTemp=QString();
    passwordq1Temp=QString();
    passwordq2Temp=QString();
    passwordq3Temp=QString();

    signTemp=QString();
    headImageTemp=QString();
}
//nameTmp=QString();

bool isValidDate(const QString &dateStr) {
    // 正则表达式检测基础格式
    QRegularExpression regex("^(\\d{4})_(\\d{1,2})_(\\d{1,2})$");
    QRegularExpressionMatch match = regex.match(dateStr);

    if (!match.hasMatch()) {
        return false;
    }

    int year = match.captured(1).toInt();
    int month = match.captured(2).toInt();
    int day = match.captured(3).toInt();

    // 利用QDate验证日期合法性
    QDate date(year, month, day);
    if (!date.isValid()) {
        return false;
    }

    // 确保日期不超过当前日期
    QDate currentDate = QDate::currentDate();
    if (date > currentDate) {
        return false;
    }

    return true;
}

void Widget::changeImage(int i)
{
    headImageTemp=QString();


    headImageTemp="head ("+QString::number(i,10);
    headImageTemp=headImageTemp+").JPG";


    QString tmp=":/new/prefix2/image/";//QString::number(long_temp,10) :/new/prefix2/image/head (1).JPG
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

    ui->brandName_6->setText(headImageTemp);


}


/*"create table User("                                                                             //构建用户数据表格
                "account varchar(25) primary key,"                                                 //用户账号
                "name varchar(25) not null,"                                                       //用户昵称
                "password varchar(25) not null,"                                                   //用户密码
                "sign varchar(25),"                                                                //个性签名
                "headImage varchar(25),"                                                           //头像图片名称
                "phoneNumber varchar(25),"
                "state bit default 0,"
                "birthDay varchar(25),"
                "localPlace varchar(25),"
                "Tagt varchar(25),"
                "VIP_Level varchar(25),"
                "signUpDate varchar(25),"
                "ban bit default 0,"
                "passwordq1 varchar(25),"
                "passwordq2 varchar(25),"
                "passwordq3 varchar(25))");*/



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


    ui->leftLabel->installEventFilter(this);                                  //将qlable设置点击事件
    ui->rightLabel->installEventFilter(this);                                  //将qlable设置点击事件
    ui->rememberPasssword->installEventFilter(this);                                  //将qlable设置点击事件
    ui->accountLineEdit->installEventFilter(this);                                    //将qlable设置点击事件
    ui->return_back1->installEventFilter(this);                                       //将qlable设置点击事件
    ui->passwordBack->installEventFilter(this);                                       //将qlable设置点击事件
    ui->logInButton->installEventFilter(this);                                        //将qlable设置点击事件
    ui->registerButton->installEventFilter(this);                                        //将qlable设置点击事件
    ui->duckLabel->installEventFilter(this);                                          //将qlable设置点击事件
    ui->setting->installEventFilter(this);                                            //将qlable设置点击事件
    ui->qrLabel->installEventFilter(this);                                            //将qlable设置点击事件
    ui->signUp->installEventFilter(this);                                             //将qlable设置点击事件

    ui->return_back1_2->installEventFilter(this);                                    //将qlable设置点击事件
    ui->next1->installEventFilter(this);                                              //将qlable设置点击事件
    ui->next1_2->installEventFilter(this);                                              //将qlable设置点击事件
    ui->return_back1_2->setAttribute(Qt::WA_Hover,true);                                //开启悬停事件
    ui->next1_2->setAttribute(Qt::WA_Hover,true);                                 //开启悬停事件

    ui->close->installEventFilter(this);                                              //将qlable设置点击事件
    ui->mim->installEventFilter(this);                                                //将qlable设置点击事件


    ui->leftLabel->setAttribute(Qt::WA_Hover,true);                                //开启悬停事件
    ui->rightLabel->setAttribute(Qt::WA_Hover,true);                                //开启悬停事件



    ui->return_back1->setAttribute(Qt::WA_Hover,true);                                //开启悬停事件
    ui->passwordBack->setAttribute(Qt::WA_Hover,true);                                //开启悬停事件
    ui->logInButton->setAttribute(Qt::WA_Hover,true);                                 //开启悬停事件
    ui->setting->setAttribute(Qt::WA_Hover,true);                                     //开启悬停事件
    ui->qrLabel->setAttribute(Qt::WA_Hover,true);                                     //开启悬停事件
    ui->signUp->setAttribute(Qt::WA_Hover,true);                                      //开启悬停事件
    ui->close->setAttribute(Qt::WA_Hover,true);                                       //开启悬停事件
    ui->mim->setAttribute(Qt::WA_Hover,true);                                         //开启悬停事件
    ui->userImage->setScaledContents(true);                                           //控件图片自适应大小
    ui->qrLabel->setScaledContents(true);                                             //控件图片自适应大小
    ui->setting->setScaledContents(true);                                             //控件图片自适应大小
    ui->close->setScaledContents(true);                                               //控件图片自适应大小
    ui->logo->setScaledContents(true);                                                //控件图片自适应大小
    ui->mim->setScaledContents(true);                                                 //控件图片自适应大小


    QSize size(512,256);
    ui->duckLabel->setFixedSize(size);
    ui->duckLabel->setScaledContents(true);



    //"[a-zA-Z0-9\u4e00-\u9fa5]+"
    ui->accountLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->passwordLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->nameLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->signUpPasswordLineEdit1->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->signUpPasswordLineEdit2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->phoneNumber->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));//输入限制
    ui->sign->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->localLineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->pd1LineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->pd2LineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->pd3LineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->phoneNumber->setInputMask("+86: 000-0000-0000");
    //ui->phoneNumber->setCursorPosition(5);  // 将光标设置在文本的开始位置




    ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#4169E1");         //color:#FFFAFA;字体颜色设置

    ui->userImage->raise();                                                           //控件置顶显示

    //duck gif动画播放
    duckMovie = new QMovie();
    duckMovie->setScaledSize(ui->duckLabel->size());
    duckMovie->setFileName(":/new/prefix1/duck.gif");
    duckMovie->setSpeed(120);
    ui->duckLabel->setMovie(duckMovie);

    think = new QMovie(":/new/prefix1/duck3.gif");

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

    shadow_effect1->setColor(QColor(0,0,0, 255));//黑色
    shadow_effect2->setColor(QColor(0,191,255, 255));//蓝色
    shadow_effect3->setColor(QColor(0,0,0, 255));//蓝色
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
    ui->duckLabel->setGraphicsEffect(shadow_effect1);
    ui->rememberPasssword->setGraphicsEffect(shadow_effect6);
    ui->passwordBack->setGraphicsEffect(shadow_effect7);
    ui->label_3->setGraphicsEffect(shadow_effect2);
    ui->signUp->setGraphicsEffect(shadow_effect5);
    QLabel *glb;
    glb=new QLabel(this);
    QVBoxLayout layout(ui->frame);
    layout.addWidget(glb);
    // 设置布局管理器的对齐方式为居中
    layout.setAlignment(Qt::AlignCenter);
    //登录动画
    startMovie = new QMovie(":/new/prefix1/start_gif.gif");
    startMovie->setSpeed(120);
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
    client1=new QTcpSocket(this);
    connect(client,&QTcpSocket::readyRead, this, &Widget::readMessage);


    QString fileName = QCoreApplication::applicationDirPath();
            //用户目录
    QString add = "//..//TFWUserFile";
            //创建用户文件夹
    fileName = fileName + add +QString("//%1").arg("ghost");
            //信息保存
    QDir * file = new QDir;
            //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
    bool exist_1 = file->exists(fileName);
    if(exist_1)
    {
        qDebug()<<"已存在";
        QFile file(fileName +"//data.txt");
        qDebug()<<fileName +"//data.txt";
        file.open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Truncate);
        QTextStream in(&file); // 创建一个QTextStream对象，用于从文件读取内容
        QString line = in.readLine(); // 读取第一行
        QString line1 = in.readLine(); // 读取第二行
        QString line2 = in.readLine(); // 读取第二行
        qDebug() << "First line: " << line;
        file.close();
        if(line=="0")
        {
            ui->rememberPasssword->setChecked(false);
            if(line1=="null")
            {
                ;
            }
            else
            {
                ui->accountLineEdit->setText(line1);
                QString fileName1 = QCoreApplication::applicationDirPath();
                        //用户目录
                QString add1 = "//..//TFWUserFile";
                        //创建用户文件夹
                fileName1 = fileName1 + add1 +QString("//%1").arg(line1);
                        //信息保存
                QDir * file1 = new QDir;
                        //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
                bool exist_2 = file1->exists(fileName1);
                if(exist_2)
                {
                    QFile file1(fileName1 +"//data.txt");
                    qDebug()<<fileName1 +"//data.txt";
                    file1.open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Truncate);
                    QTextStream in1(&file1); // 创建一个QTextStream对象，用于从文件读取内容
                    QString line = in1.readLine(); // 读取第一行
                    QString line1 = in1.readLine(); // 读取第二行
                    QString line2 = in1.readLine(); // 读取第二行
                    QString line3 = in1.readLine(); // 读取第二行
                    QString line4 = in1.readLine(); // 读取第二行
                    QString tmp=":/new/prefix2/image/";
                    tmp=tmp+line4;
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
                    ui->userImage->setPixmap(roundedPixmap);






                }
                else
                {
                    ;
                }
            }
        }
        else
        {
            ui->rememberPasssword->setChecked(true);
            if(line1=="null")
            {
                qDebug()<<"null";
            }
            else
            {
                qDebug()<<line1;
                ui->accountLineEdit->setText(line1);
                QString fileName1 = QCoreApplication::applicationDirPath();
                        //用户目录
                QString add1 = "//..//TFWUserFile";
                        //创建用户文件夹
                fileName1 = fileName1 + add1 +QString("//%1").arg(line1);
                        //信息保存
                QDir * file1 = new QDir;
                        //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
                bool exist_2 = file1->exists(fileName1);
                if(exist_2)
                {
                    QFile file1(fileName1 +"//data.txt");
                    qDebug()<<fileName1 +"//data.txt";
                    file1.open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Truncate);
                    QTextStream in1(&file1); // 创建一个QTextStream对象，用于从文件读取内容
                    QString line = in1.readLine(); // 读取第一行
                    QString line1 = in1.readLine(); // 读取第二行
                    QString line2 = in1.readLine(); // 读取第二行
                    QString line3 = in1.readLine(); // 读取第二行
                    QString line4 = in1.readLine(); // 读取第二行
                    QString tmp=":/new/prefix2/image/";
                    tmp=tmp+line4;
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
                    ui->userImage->setPixmap(roundedPixmap);


                }
                else
                {
                    ;
                }
            }
            if(line2=="null")
            {
                qDebug()<<"null";
            }
            else
            {
                ui->passwordLineEdit->setText(line2);
            }
        }


    }
    else
    {
        bool ok = file->mkpath(fileName);
                    if(ok)
                    {
                        QFile file(fileName +"//data.txt");
                         qDebug()<<fileName +"//data.txt";
                         if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                         {
                           qDebug()<<"txt文件创建成功";
                           QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
                           out << "0\n"; // 写入第一行内容为 "1"
                           out<<"null\n";
                           out<<"null\n";
                         }
                          file.close();
                      }
                    else
                    {
                        qDebug()<<"未创建成功";
                    }

    }



    think = new QMovie(":/new/prefix1/duck3.gif");

    setplacehodetext(ui->accountLineEdit);
    setplacehodetext(ui->passwordLineEdit);

    systemtrayicon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/new/prefix1/img2_s.png");
    //添加图标
    systemtrayicon->setIcon(icon);
    systemtrayicon->setToolTip(QObject::trUtf8("TFW"));
        //显示图标

    menu = new QMenu(this);
    m_pShowAction = new QAction("打开主界面");
    m_pCloseAction = new QAction("退出");
    menu->addAction(m_pShowAction);
    menu->addSeparator();
    menu->addAction(m_pCloseAction);
    systemtrayicon->setContextMenu(menu);
    connect(m_pShowAction,SIGNAL(triggered(bool)),this,SLOT(showwidget()));
    connect(m_pCloseAction,SIGNAL(triggered(bool)),this,SLOT(closewidget()));







    systemtrayicon->show();





    startMovie->start();


}

void Widget::setplacehodetext(QLineEdit *a)
{
    QPalette palette = a->palette();
    palette.setColor(QPalette::Normal, QPalette::PlaceholderText, "#FFFAFA");
    a->setPalette(palette);
}
void Widget::setplacehodetextRed(QLineEdit *a)
{
    QPalette palette = a->palette();
    palette.setColor(QPalette::Normal, QPalette::PlaceholderText, "#DC143C");
    a->setPalette(palette);
}

void Widget::showwidget()
{
    this->show();
}

void Widget::closewidget()
{
    this->close();
}

//析构函数
Widget::~Widget()
{
    delete validator;
    delete client;
    delete client1;
    delete animation;                                                                 //启动动画前的一段动画
    delete animation1;                                                                //启动动画
    delete animation2;                                                                //拖动动画
    delete animation3;                                                                //关闭动画
    delete animation4;                                                                //最小化动画
    delete startMovie;                                                                //开头gif播放
    delete duckMovie;
    delete think;
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

            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
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
            ui->next1->removeEventFilter(this);
            QLabel *Lable2;
            Lable2=new QLabel(this);
            Lable2->resize(450,350);
            Lable2->setGeometry(275,325,450,350);
            ffd=new findpassword;
            QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
            ffd->move(globalPos1.x(),globalPos1.y());

            ffd->show();




        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color:#1E90FF");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color: rgb(176, 224 ,230)");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->passwordBack->setStyleSheet("background:rgba(85,170,255,0);color:#FFE4E1");//color:#FFFAFA;
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


            if((!ui->accountLineEdit->text().isEmpty())&&(!ui->passwordLineEdit->text().isEmpty()))
            {
            if(!networkAbleFlag)
            {
                ui->duckLabel->hide();
                ui->duckLabel->update();

                QLabel *thinkLable;
                thinkLable=new QLabel(this);

                QSize size(512,256);
                thinkLable->setFixedSize(size);
                thinkLable->setScaledContents(true);

                thinkLable->setGeometry(444,392,512,256);
                QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
                QGraphicsDropShadowEffect *shadow_effect;
                shadow_effect=new QGraphicsDropShadowEffect(this);
                shadow_effect->setOffset(0, 0);
                shadow_effect->setColor(QColor(0,0,0, 255));//黑色
                shadow_effect->setBlurRadius(20);
                thinkLable->setGraphicsEffect(shadow_effect);
                thinkLable->show();

                //ui->gridLayout->addWidget(thinkLable);
                // 设置布局管理器的对齐方式为居中
                delete think;
                think = new QMovie();
                think->setScaledSize(thinkLable->size());
                think->setFileName(":/new/prefix1/duck3.gif");
                think->setSpeed(200);
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
                ui->next1->removeEventFilter(this);
                QObject::connect(think, &QMovie::frameChanged, [=](int frameNumber) {
                    // GIF 动画执行一次就结束
                    if (frameNumber == think->frameCount()-1) {
                        think->stop();
                        delete shadow_effect;
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

                        delete Lable1;
                        Lable1 = nullptr;


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
                         ui->next1->removeEventFilter(this);
                         ui->duckLabel->hide();
                         ui->duckLabel->update();
                         QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
                         client->abort();
                         client->connectToHost(serveRemoteAddress,51269);
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

                         delete Lable1;
                         Lable1 = nullptr;

                         connectFlag = client->waitForConnected(3000);
                         if(connectFlag)
                         {
                             QString det1="链接成功";
                             det1 = tr("<font size='6' color='white'>") + det1;
                             det1 += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                             QMessageBox msgbox1(QMessageBox::Information,"",det1);
                             msgbox1.setIconPixmap(QPixmap(":/new/prefix1/welcome.png"));
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
                             delete Lable2;
                             Lable2 = nullptr;
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

                             delete Lable3;
                             Lable3 = nullptr;

                             myAccount=ui->accountLineEdit->text();
                             myPassword=ui->passwordLineEdit->text();
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

                             delete Lable2;
                             Lable2 = nullptr;

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
                             ui->next1->installEventFilter(this);
                             ui->duckLabel->show();
                             ui->duckLabel->update();
                         }
            }
        }

            else
            {
                if(ui->accountLineEdit->text().isEmpty())
                {
                    ui->accountLineEdit->setPlaceholderText("请输入账号");
                    setplacehodetextRed(ui->accountLineEdit);
                }
                if(ui->passwordLineEdit->text().isEmpty())
                {
                    ui->passwordLineEdit->setPlaceholderText("请输入密码");
                    setplacehodetextRed(ui->passwordLineEdit);
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

            ui->return_back1->removeEventFilter(this);
            ui->signUp->removeEventFilter(this);
            ui->accountLineEdit->clear();
            ui->passwordLineEdit->clear();
            ui->accountLineEdit->setPlaceholderText("账号");
            ui->passwordLineEdit->setPlaceholderText("密码");
            setplacehodetext(ui->accountLineEdit);
            setplacehodetext(ui->passwordLineEdit);
            update();
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
            delete duckMovie;
            duckMovie = new QMovie();
            duckMovie->setScaledSize(ui->duckLabel->size());
            duckMovie->setFileName(":/new/prefix1/duck.gif");
            duckMovie->setSpeed(120);
            ui->duckLabel->setMovie(duckMovie);
            duckMovie->start();
            QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                if (frameNumber == duckMovie->frameCount()-1) {
                    duckMovie->stop();
                    refresh();
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
        else if(event->type()==QEvent::MouseButtonRelease)
        {
            ui->birthdayLineEdit->clear();
            ui->localLineEdit->clear();
            ui->pd1LineEdit->clear();
            ui->pd2LineEdit->clear();
            ui->pd3LineEdit->clear();
            ui->birthdayLineEdit->setPlaceholderText("生日");
            ui->localLineEdit->setPlaceholderText("所在地");
            ui->pd1LineEdit->setPlaceholderText("密保一");
            ui->pd2LineEdit->setPlaceholderText("密保二");
            ui->pd3LineEdit->setPlaceholderText("密保三");
            setplacehodetext(ui->birthdayLineEdit);
            setplacehodetext(ui->localLineEdit);
            setplacehodetext(ui->pd1LineEdit);
            setplacehodetext(ui->pd2LineEdit);
            setplacehodetext(ui->pd3LineEdit);

            if((!ui->nameLineEdit->text().isEmpty())&&(!ui->signUpPasswordLineEdit1->text().isEmpty())&&(!ui->signUpPasswordLineEdit2->text().isEmpty())&&(!ui->sign->text().isEmpty()))
            {
            nameTmp=ui->nameLineEdit->text();
            password1Tmp=ui->signUpPasswordLineEdit1->text();
            password2Tmp=ui->signUpPasswordLineEdit2->text();
            phoneNumberTmp=ui->phoneNumber->text();
            signTemp=ui->sign->text();

                           if(password1Tmp==password2Tmp)
                           {
                           qDebug()<<ui->phoneNumber->text();
                           setplacehodetext(ui->birthdayLineEdit);
                           setplacehodetext(ui->localLineEdit);
                           setplacehodetext(ui->pd1LineEdit);
                           setplacehodetext(ui->pd2LineEdit);
                           setplacehodetext(ui->pd3LineEdit);
                           ui->next1->removeEventFilter(this);
                           ui->return_back1_2->removeEventFilter(this);
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
                           delete duckMovie;
                           duckMovie = new QMovie();
                           duckMovie->setScaledSize(ui->duckLabel->size());
                           duckMovie->setFileName(":/new/prefix1/duck2.gif");
                           duckMovie->setSpeed(120);
                           ui->duckLabel->setMovie(duckMovie);
                           duckMovie->start();
                           QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                               // GIF 动画执行一次就结束
                               if (frameNumber == duckMovie->frameCount()-1) {
                                   duckMovie->stop();
                                   refresh();
                               }
                           });
                           }
                           else
                           {
                               setplacehodetextRed(ui->signUpPasswordLineEdit1);
                               setplacehodetextRed(ui->signUpPasswordLineEdit2);
                               ui->signUpPasswordLineEdit1->clear();
                               ui->signUpPasswordLineEdit2->clear();
                               update();
                               ui->signUpPasswordLineEdit1->setPlaceholderText("两次密码不一致");
                               ui->signUpPasswordLineEdit2->setPlaceholderText("两次密码不一致");
                           }



        }
        else
            {
                if(ui->nameLineEdit->text().isEmpty())
                {
                    ui->nameLineEdit->setPlaceholderText("请输入昵称");
                    setplacehodetextRed(ui->nameLineEdit);
                }
                if(ui->signUpPasswordLineEdit1->text().isEmpty())
                {
                    ui->signUpPasswordLineEdit1->setPlaceholderText("请输入密码");
                    setplacehodetextRed(ui->signUpPasswordLineEdit1);
                }
                if(ui->signUpPasswordLineEdit2->text().isEmpty())
                {
                    ui->signUpPasswordLineEdit2->setPlaceholderText("请确认密码");
                    setplacehodetextRed(ui->signUpPasswordLineEdit2);
                }
                if(ui->sign->text().isEmpty())
                {
                    ui->sign->setPlaceholderText("请输入个性签名");
                    setplacehodetextRed(ui->sign);
                }







            }
        }
    }








    /*QString birthdayDate;
QString localPlaceTemp;
QString passwordq1Temp;
QString passwordq2Temp;
QString passwordq3Temp;*/





    else if(qobject_cast<QPushButton*>(obj) == ui->next1_2)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type()==QEvent::MouseButtonRelease)
        {
            headImageTemp="head (1).JPG";
            if((!ui->birthdayLineEdit->text().isEmpty())&&(!ui->localLineEdit->text().isEmpty())&&(!ui->pd1LineEdit->text().isEmpty())&&(!ui->pd2LineEdit->text().isEmpty())&&(!ui->pd3LineEdit->text().isEmpty()))
            {

              if(isValidDate(ui->birthdayLineEdit->text()))
              {

                  QString tmp=":/new/prefix2/image/head (1).JPG";


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

                  imageCounter=1;
            birthdayDate=ui->birthdayLineEdit->text();
            localPlaceTemp=ui->localLineEdit->text();
            passwordq1Temp=ui->pd1LineEdit->text();
            passwordq2Temp=ui->pd2LineEdit->text();
            passwordq3Temp=ui->pd3LineEdit->text();

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
                           delete duckMovie;
                           duckMovie = new QMovie();
                           duckMovie->setScaledSize(ui->duckLabel->size());
                           duckMovie->setFileName(":/new/prefix1/duck2.gif");
                           duckMovie->setSpeed(120);
                           ui->duckLabel->setMovie(duckMovie);
                           duckMovie->start();
                           QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                               // GIF 动画执行一次就结束
                               if (frameNumber == duckMovie->frameCount()-1) {
                                   duckMovie->stop();
                                   refresh();
                               }
                           });
              }
              else
              {
                  ui->birthdayLineEdit->clear();
                  ui->birthdayLineEdit->setPlaceholderText("生日格式不正确");
                  setplacehodetextRed(ui->birthdayLineEdit);
              }





        }
        else
            {


                if(ui->birthdayLineEdit->text().isEmpty())
                {
                    ui->birthdayLineEdit->setPlaceholderText("请输入生日");
                    setplacehodetextRed(ui->birthdayLineEdit);
                }
                if(ui->localLineEdit->text().isEmpty())
                {
                    ui->localLineEdit->setPlaceholderText("请输入所在地");
                    setplacehodetextRed(ui->localLineEdit);
                }
                if(ui->pd1LineEdit->text().isEmpty())
                {
                    ui->pd1LineEdit->setPlaceholderText("请输入密保一");
                    setplacehodetextRed(ui->pd1LineEdit);
                }
                if(ui->pd2LineEdit->text().isEmpty())
                {
                    ui->pd2LineEdit->setPlaceholderText("请输入密保二");
                    setplacehodetextRed(ui->pd2LineEdit);
                }
                if(ui->pd3LineEdit->text().isEmpty())
                {
                    ui->pd3LineEdit->setPlaceholderText("请输入密保三");
                    setplacehodetextRed(ui->pd3LineEdit);
                }







            }
        }
    }
















    else if(qobject_cast<QPushButton*>(obj) == ui->return_back1_2)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type()==QEvent::MouseButtonRelease)
        {


            setplacehodetext(ui->nameLineEdit);
            setplacehodetext(ui->signUpPasswordLineEdit1);
            setplacehodetext(ui->signUpPasswordLineEdit2);
            setplacehodetext(ui->phoneNumber);
            setplacehodetext(ui->sign);
            ui->nameLineEdit->clear();
            ui->signUpPasswordLineEdit1->clear();
            ui->signUpPasswordLineEdit2->clear();
            ui->sign->clear();
            ui->nameLineEdit->setPlaceholderText("昵称");
            ui->signUpPasswordLineEdit1->setPlaceholderText("密码");
            ui->signUpPasswordLineEdit2->setPlaceholderText("确认密码");
            ui->sign->setPlaceholderText("个性签名");


                           ui->next1->removeEventFilter(this);
                           ui->return_back1_2->removeEventFilter(this);
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
                           delete duckMovie;
                           duckMovie = new QMovie();
                           duckMovie->setScaledSize(ui->duckLabel->size());
                           duckMovie->setFileName(":/new/prefix1/duck2.gif");
                           duckMovie->setSpeed(120);
                           ui->duckLabel->setMovie(duckMovie);
                           duckMovie->start();
                           QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                               // GIF 动画执行一次就结束
                               if (frameNumber == duckMovie->frameCount()-1) {
                                   duckMovie->stop();
                                   refresh();
                               }
                           });
        }
    }


    else if(qobject_cast<QPushButton*>(obj) == ui->registerButton)
    {
        if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type()==QEvent::MouseButtonRelease)
        {
          ssp->tcpServerConnect();
          ssp->sendMessage("register");
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
            ui->nameLineEdit->setPlaceholderText("昵称");
            ui->signUpPasswordLineEdit1->setPlaceholderText("密码");
            ui->signUpPasswordLineEdit2->setPlaceholderText("确认密码");
            ui->sign->setPlaceholderText("个性签名");
            ui->birthdayLineEdit->setPlaceholderText("生日");
            ui->localLineEdit->setPlaceholderText("所在地");
            ui->pd1LineEdit->setPlaceholderText("密保一");
            ui->pd2LineEdit->setPlaceholderText("密保二");
            ui->pd3LineEdit->setPlaceholderText("密保三");

            ui->nameLineEdit->clear();
            ui->signUpPasswordLineEdit1->clear();
            ui->signUpPasswordLineEdit2->clear();
            ui->phoneNumber->clear();
            ui->sign->clear();
            ui->birthdayLineEdit->clear();
            ui->localLineEdit->clear();
            ui->pd1LineEdit->clear();
            ui->pd2LineEdit->clear();
            ui->pd3LineEdit->clear();

            resetQstr();
            setplacehodetext(ui->nameLineEdit);
            setplacehodetext(ui->signUpPasswordLineEdit1);
            setplacehodetext(ui->signUpPasswordLineEdit2);
            setplacehodetext(ui->phoneNumber);
            setplacehodetext(ui->sign);
            setplacehodetext(ui->birthdayLineEdit);
            setplacehodetext(ui->localLineEdit);
            setplacehodetext(ui->pd1LineEdit);
            setplacehodetext(ui->pd2LineEdit);
            setplacehodetext(ui->pd3LineEdit);
            ui->return_back1->removeEventFilter(this);
            ui->signUp->removeEventFilter(this);
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
            delete duckMovie;
            duckMovie = new QMovie();
            duckMovie->setScaledSize(ui->duckLabel->size());
            duckMovie->setFileName(":/new/prefix1/duck2.gif");
            duckMovie->setSpeed(120);
            ui->duckLabel->setMovie(duckMovie);
            duckMovie->start();
            QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                if (frameNumber == duckMovie->frameCount()-1) {
                    duckMovie->stop();
                    refresh();
                }
            });
            //connect(group, SIGNAL(finished()), this, SLOT(onAnimationFinished()));
            //QMovie *duckMovie;
            //duckMovie = new QMovie(":/new/prefix1/duck2.gif");
            //duckMovie->setSpeed(120);
            //ui->duckLabel->setMovie(duckMovie);
            //duckMovie->start();
            //QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                //if (frameNumber == duckMovie->frameCount() - 1) {
                    //duckMovie->stop();


                //}
           // });
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#1E90FF");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color: rgb(176, 224 ,230)");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->signUp->setStyleSheet("background:rgba(85,170,255,0);color:#4169E1");//color:#FFFAFA; 字体颜色设置
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->qrLabel)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
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
            ui->next1->removeEventFilter(this);
            QLabel *Lable2;
            Lable2=new QLabel(this);
            Lable2->resize(400,200);
            Lable2->setGeometry(300,400,400,200);

            cc=new qrcode;
            QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
            cc->move(globalPos1.x(),globalPos1.y());
            cc->slot_GenerateQRCode();
            cc->show();



}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/qrCode.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->qrLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->setting)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/ssetting.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

            QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
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
            ui->next1->removeEventFilter(this);
            QLabel *Lable2;
            Lable2=new QLabel(this);
            Lable2->resize(400,200);
            Lable2->setGeometry(300,400,400,200);

            bb=new addressSetting;
            QPoint globalPos1 = Lable2->mapToGlobal(QPoint(0, 0));
            bb->move(globalPos1.x(),globalPos1.y());

            bb->show();



        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/ssetting2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/ssetting1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/ssetting.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->setting->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
    }
    else if(qobject_cast<QLabel*>(obj) == ui->mim)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/mim.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            animation3->start();}
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/mim2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/mim1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/mim.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->mim->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
    }


    else if(qobject_cast<QLabel*>(obj) == ui->leftLabel)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/left.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->leftLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            if(imageCounter==1)
            {
                ;

            }
            else
            {
                imageCounter--;
                changeImage(imageCounter);
            }
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/left2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->leftLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/left1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->leftLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/left.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->leftLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
    }


    else if(qobject_cast<QLabel*>(obj) == ui->rightLabel)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/right.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->rightLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            if(imageCounter==32)
            {
                ;

            }
            else
            {
                imageCounter++;
                changeImage(imageCounter);
            }
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/right2.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->rightLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/right1.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->rightLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img

        }
        else if(event->type() == QEvent::HoverLeave)
        {
            QImage *img=new QImage; //新建一个image对象

            img->load(":/new/prefix1/right.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->rightLabel->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
        }
    }


    else if(qobject_cast<QLabel*>(obj) == ui->close)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            if(loginSuccessFlag)
            {
                commitMessage1("logout");
                loginSuccessFlag=false;
            }
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
            ui->next1->removeEventFilter(this);
            QImage *img=new QImage; //新建一个image对象
            img->load(":/new/prefix1/close.png"); //将图像资源载入对象img，注意路径，可点进图片右键复制路径
            ui->close->setPixmap(QPixmap::fromImage(*img)); //将图片放入label，使用setPixmap,注意指针*img
            delete duckMovie;
            duckMovie = new QMovie();
            duckMovie->setScaledSize(ui->duckLabel->size());
            duckMovie->setFileName(":/new/prefix1/duck1.gif");
            duckMovie->setSpeed(120);
            ui->duckLabel->setMovie(duckMovie);
            duckMovie->start();
            QObject::connect(duckMovie, &QMovie::frameChanged, [=](int frameNumber) {
                // GIF 动画执行一次就结束
                if (frameNumber == duckMovie->frameCount()-1) {
                    duckMovie->stop();
                    animation4->start();
                }
            });
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
    QString str;
    str = client->readAll();
    if(str == "loginSuccess"){
        loginSuccessFlag = true;
    }else if(str == "loginFail"){
        loginSuccessFlag = false;
    }else if(str == "AlreadyOnline"){
        loginSuccessFlag = true;
        AlreadyOnlineFlag=true;
    }

    QLabel *thinkLable;
    thinkLable=new QLabel(this);
    thinkLable->resize(512,256);
    thinkLable->setScaledContents(true);
    thinkLable->setGeometry(444,392,512,256);
    QMetaObject::invokeMethod(blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, true));
    QGraphicsDropShadowEffect *shadow_effect;
    shadow_effect=new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0,0,0, 255));//黑色
    shadow_effect->setBlurRadius(20);
    thinkLable->setGraphicsEffect(shadow_effect);
    thinkLable->show();
    //ui->gridLayout->addWidget(thinkLable);
    // 设置布局管理器的对齐方式为居中
    delete  think;
    think = new QMovie(":/new/prefix1/duck3.gif");
    think->setSpeed(300);
    thinkLable->setMovie(think);
    think->start();

    QObject::connect(think, &QMovie::frameChanged, [=](int frameNumber) {
        // GIF 动画 执行一次就结束
        if (frameNumber == think->frameCount() - 1) {
            think->stop();
            delete shadow_effect;
            delete thinkLable;
            if(loginSuccessFlag)
            {
                if(AlreadyOnlineFlag)
                {
                    QString det1="禁止重复登录";
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

                    delete Lable2;
                    Lable2 = nullptr;
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
                    ui->next1->installEventFilter(this);
                    ui->duckLabel->show();
                    ui->duckLabel->update();
                }
                else
                {


                client1->connectToHost(serveRemoteAddress ,55418);
                QString det1="登录成功";

                QIcon icon = QIcon(":/new/prefix1/img2.png");
                //添加图标
                systemtrayicon->setIcon(icon);

                QString fileName = QCoreApplication::applicationDirPath();
                        //用户目录
                QString add = "//..//TFWUserFile";
                        //创建用户文件夹
                fileName = fileName + add +QString("//%1").arg("ghost");
                        //信息保存
                QDir * file = new QDir;
                        //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
                bool exist_1 = file->exists(fileName);
                if(exist_1)
                {
                     QFile file(fileName +"//data.txt");
                     if(file.open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Truncate))
                     {

                       QTextStream in(&file); // 创建一个QTextStream对象，用于从文件读取内容
                       QString l1=in.readLine();
                       file.close();
                       if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                       {
                       QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
                       out << l1; // 写入第一行内容为 "1"
                       out<<"\n";
                       out <<myAccount;
                       out<<"\n";
                       out <<myPassword;
                       file.close();
                       }
                     }

                }
                else
                {
                    ;
                }

                InitSurface *initsuface;
                initsuface = new InitSurface;
                initsuface->setAccount(myAccount);
                initsuface->sendMessage("initSurface");
                det1 = tr("<font size='6' color='white'>") + det1;
                det1 += tr("</font>");                                                       //这时候Qss写字体大小和颜色没有用了，我就在字符串里加了一些前端的写法
                QMessageBox msgbox1(QMessageBox::Information,"",det1);
                msgbox1.setIconPixmap(QPixmap(":/new/prefix1/welcome.png"));
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

                delete Lable2;
                Lable2 = nullptr;
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
                ui->next1->installEventFilter(this);
                ui->duckLabel->show();
                ui->duckLabel->update();
                }

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

                delete Lable2;
                Lable2 = nullptr;

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
                ui->next1->installEventFilter(this);
                ui->duckLabel->show();
                ui->duckLabel->update();

            }

        }
    });

}

void Widget::commitMessage1(QString Msg)
{
    qDebug() << "发送消息";
    if(Msg == "logout"){
        //初始化界面
        QString string = "logout|" + myAccount;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "SelectUserInterface::sendMessage:" << string;
        //发送信息
        client1->write(message);
    }
    qDebug() << "发送完成";
}

void Widget::refresh()
{
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
    ui->return_back1_2->installEventFilter(this);
    ui->next1->installEventFilter(this);
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






void Widget::on_rememberPasssword_stateChanged(int arg1)
{
    QString fileName = QCoreApplication::applicationDirPath();
            //用户目录
    QString add = "//..//TFWUserFile";
            //创建用户文件夹
    fileName = fileName + add +QString("//%1").arg("ghost");
            //信息保存
    QDir * file = new QDir;
            //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
    bool exist_1 = file->exists(fileName);
    if(exist_1)
    {
         QFile file(fileName +"//data.txt");
         if(file.open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::Truncate))
         {
           if(arg1==0)
           {
           qDebug()<<"0 修改成功";
           QTextStream in(&file); // 创建一个QTextStream对象，用于从文件读取内容
           QString l1=in.readLine();
           QString l2=in.readLine();
           QString l3=in.readLine();
           file.close();
           if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
           {
           QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
           out << "0\n"; // 写入第一行内容为 "1"
           out <<l2;
           out<<"\n";
           out <<l3;
           }
           }
           else
           {
               qDebug()<<"1 修改成功";
               QTextStream in(&file); // 创建一个QTextStream对象，用于从文件读取内容
               QString l1=in.readLine();
               QString l2=in.readLine();
               QString l3=in.readLine();
               file.close();
               if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
               {
               QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
               out << "1\n"; // 写入第一行内容为 "1"
               out <<l2;
               out<<"\n";
                out <<l3;
               }
           }
         }
         file.close();
    }
    else
    {
        ;
    }
}
