#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>                                                   //阴影添加
#include <QParallelAnimationGroup>
#include "userlist.h"
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QAbstractSocket>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QTcpSocket>
#include <QDebug>
#include <QApplication>
#include <address.h>
#include "widget.h"
#include <QLineEdit>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDate>
#include <QStringList>
#include <QIcon>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QThread>
MyFriend currentfriend;
extern MyChats *mychats;
extern MyRequsests* myrequests;
extern QSystemTrayIcon  *ssystemtrayicon;  //系统托盘
extern MyFriends *myfriends;
MyFriend friendSearch;
//用于修改信息
QString sendmymessagestr;
QString headStr;
QString nameStr;
QString psStr;
QString locStr;
QString birthStr;
QString getBaseMessageStr;
QString getBaseRequestMessageStr;
QString requestToBeFriendStr;
QString agreeToBeFriendStr;
extern MainWindow *mainwindow;
QString getCurrentDateTimeString() {
    QDateTime current = QDateTime::currentDateTime();
    return current.toString("yyyy_MM_dd_HH_mm_ss");
}
bool MainWindow::isValidDate(const QString &dateStr) {
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


/*if(loginSuccessFlag)
            {
                commitMessage1("logout");
                loginSuccessFlag=false;
            }*/
extern QApplication *aa;
extern QTcpSocket *client1_s;
extern CurrentUser* currentuser;
extern Widget* loginpage;
extern tfwAddress *tfwaddress;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("TFW");                                                      //登录窗口名
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    this->setStyleSheet("QMainWindow::statusBar::grip { width: 0px; height: 0px; }");
    this->setStatusBar(nullptr);
    setAttribute(Qt::WA_TranslucentBackground);                                       //把窗口背景设置为透明;
    setMouseTracking(true);                                                           //窗口可进行鼠标追踪，以进行拖动
    ui->userImage->setScaledContents(true);
    //控件图片自适应大小

    thread = new QThread;
    this->moveToThread(thread);
    QObject::connect(thread, &QThread::started, this,&MainWindow::updateApplication);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();




    //登录界面lable点击功能实现
    QIcon icon = QIcon(":/new/prefix1/img2.png");
    //添加图标
    setWindowIcon(icon);
    animation2 = new QPropertyAnimation(this, "pos");                                 //动画效果
    animation2->setDuration(0);                                                       //设置动画持续时间（毫秒）//动画效果

    shadow_effect1 = new QGraphicsDropShadowEffect(this);
    shadow_effect1->setOffset(0, 0);
    shadow_effect1->setColor(QColor(255,245,238, 255));//黑色
    shadow_effect1->setBlurRadius(10);

    shadow_effect2 = new QGraphicsDropShadowEffect(this);
    shadow_effect2->setOffset(0, 0);
    shadow_effect2->setColor(QColor(255,245,238, 255));//黑色
    shadow_effect2->setBlurRadius(10);
    ui->widget->setGraphicsEffect(shadow_effect1);
    ui->label->setGraphicsEffect(shadow_effect2);
    animation1 = new QPropertyAnimation(this, "windowOpacity");
    animation1->setDuration(1500);
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

    QObject::connect(animation1, &QPropertyAnimation::finished, [=](){
        animation1->stop();  // 停止属性动画 a

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



    });

    animation3 = new QPropertyAnimation(this, "windowOpacity");

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
    QObject::connect(animation3, &QPropertyAnimation::finished, [=](){
        animation3->stop();  // 停止属性动画 a

        aa->quit();
    });

    animation4 = new QPropertyAnimation(this, "windowOpacity");

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
    QObject::connect(animation4, &QPropertyAnimation::finished, [=](){
        myfriends->friendDebug();
        myrequests->RequestDebug();
        myfriends->removeAllFriendByAccount();
        myrequests->removeAllRequestByAccount();
        mychats->removeAllChatByAccount();
        myfriends->friendDebug();
        myrequests->RequestDebug();
        myfriends->friendDebug();
        myrequests->RequestDebug();
        animation4->stop();  // 停止属性动画 a
        loginpage->setWindowOpacity(1);
        QMetaObject::invokeMethod(loginpage->blureffect1, "setEnabled", Qt::QueuedConnection, Q_ARG(bool, false));
        loginpage->refresh();
        loginpage->duckshow();
        loginpage->chushihua();
        loginpage->show();
        close();
    });

    //画头像

    ui->listWidget_chat->setFrameStyle(QFrame::NoFrame);
    ui->listWidget_message->setFrameStyle(QFrame::NoFrame);

    ui->listWidget_chat_2->setFrameStyle(QFrame::NoFrame);
    ui->listWidget_chat_3->setFrameStyle(QFrame::NoFrame);
    ui->listWidget_chat_4->setFrameStyle(QFrame::NoFrame);

    ui->sendMyMessage->installEventFilter(this);
    ui->close->installEventFilter(this);
    ui->sendMessage->installEventFilter(this);
    ui->agreeToBeFriend->installEventFilter(this);
    ui->requestToBeFriend->installEventFilter(this);
    ui->quitLogin->installEventFilter(this);
    ui->changePsword->installEventFilter(this);
    ui->changeUserMessage->installEventFilter(this);
    ui->adduser->installEventFilter(this);
    ui->adduser->setAttribute(Qt::WA_Hover,true);
    ui->search_2->installEventFilter(this);
    ui->search_2->setAttribute(Qt::WA_Hover,true);

    ui->friends->installEventFilter(this);
    ui->requestMessage->installEventFilter(this);



    ui->userImageChoose_1->installEventFilter(this);
    ui->userImageChoose_2->installEventFilter(this);
    ui->userImageChoose_3->installEventFilter(this);
    ui->userImageChoose_4->installEventFilter(this);
    ui->userImageChoose_5->installEventFilter(this);
    ui->userImageChoose_6->installEventFilter(this);
    ui->userImageChoose_7->installEventFilter(this);
    ui->userImageChoose_8->installEventFilter(this);
    ui->userImageChoose_9->installEventFilter(this);
    ui->userImageChoose_10->installEventFilter(this);
    ui->userImageChoose_11->installEventFilter(this);
    ui->userImageChoose_12->installEventFilter(this);
    ui->userImageChoose_13->installEventFilter(this);
    ui->userImageChoose_14->installEventFilter(this);
    ui->userImageChoose_15->installEventFilter(this);
    ui->userImageChoose_16->installEventFilter(this);
    ui->userImageChoose_17->installEventFilter(this);
    ui->userImageChoose_18->installEventFilter(this);
    ui->userImageChoose_19->installEventFilter(this);
    ui->userImageChoose_20->installEventFilter(this);
    ui->userImageChoose_21->installEventFilter(this);
    ui->userImageChoose_22->installEventFilter(this);
    ui->userImageChoose_23->installEventFilter(this);
    ui->userImageChoose_24->installEventFilter(this);
    ui->userImageChoose_25->installEventFilter(this);
    ui->userImageChoose_26->installEventFilter(this);
    ui->userImageChoose_27->installEventFilter(this);
    ui->userImageChoose_28->installEventFilter(this);
    ui->userImageChoose_29->installEventFilter(this);
    ui->userImageChoose_30->installEventFilter(this);
    ui->userImageChoose_31->installEventFilter(this);
    ui->userImageChoose_32->installEventFilter(this);
    ui->userImageChoose_33->installEventFilter(this);
    ui->userImageChoose_34->installEventFilter(this);
    ui->userImageChoose_35->installEventFilter(this);
    ui->userImageChoose_36->installEventFilter(this);
    ui->userImageChoose_37->installEventFilter(this);
    ui->userImageChoose_38->installEventFilter(this);
    ui->userImageChoose_39->installEventFilter(this);
    ui->userImageChoose_40->installEventFilter(this);
    ui->userImageChoose_41->installEventFilter(this);
    ui->userImageChoose_42->installEventFilter(this);
    ui->userImageChoose_43->installEventFilter(this);
    ui->userImageChoose_44->installEventFilter(this);
    ui->userImageChoose_45->installEventFilter(this);
    ui->userImageChoose_46->installEventFilter(this);
    ui->userImageChoose_47->installEventFilter(this);
    ui->userImageChoose_48->installEventFilter(this);
    ui->userImageChoose_49->installEventFilter(this);
    ui->userImageChoose_50->installEventFilter(this);
    ui->userImageChoose_51->installEventFilter(this);
    ui->userImageChoose_52->installEventFilter(this);






    ui->userImageChoose_1->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_2->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_3->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_4->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_5->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_6->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_7->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_8->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_9->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_10->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_11->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_12->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_13->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_14->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_15->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_16->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_17->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_18->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_19->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_20->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_21->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_22->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_23->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_24->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_25->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_26->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_27->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_28->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_29->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_30->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_31->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_32->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_33->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_34->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_35->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_36->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_37->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_38->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_39->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_40->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_41->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_42->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_43->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_44->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_45->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_46->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_47->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_48->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_49->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_50->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_51->setAttribute(Qt::WA_Hover,true);
    ui->userImageChoose_52->setAttribute(Qt::WA_Hover,true);







    changeMessage();

    tcpsocket = new QTcpSocket(this);
    tcpsocket_s = new QTcpSocket(this);
    tcpsocket_application = new QTcpSocket(this);
    loginpage->isMainWindowOpen=true;
    ui->padLineEdit_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9]+$")));//输入限制
    ui->searchLineEdit_3->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));//输入限制
    ui->nameChange->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->psChange_3->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    ui->localChange_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z0-9\u4e00-\u9fa5]+")));//输入限制
    setplacehodetextRed(ui->padLineEdit_2);
    ui->listWidget_chat->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_message->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_chat_2->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_chat_3->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_chat_4->setFocusPolicy(Qt::NoFocus);
    tcpServerConnect_application();
    {

        /*delete timer4;
        timer4=nullptr;
        timer4=new QTimer;
        QObject::connect(timer4, &QTimer::timeout, [&]() {
              timer2->stop();
            });
        timer4->setSingleShot(true); // 如果只需要执行一次，设置为 true
        timer4->start(3000);*/



        updateApplication();
        delete timer1;
        timer1=nullptr;
        timer1=new QTimer;
        delete timer2;
        timer2=nullptr;
        timer2=new QTimer;
        QObject::connect(timer1, &QTimer::timeout, [&]() {
            if(loginpage->isMainWindowOpen)
            {
                updateApplication();

            }
            else
            {
                ;
            }
              qDebug() << "3秒后执行的函数";
              timer1->stop();
            });
        QObject::connect(timer2, &QTimer::timeout, [&]() {
            if(loginpage->isMainWindowOpen)
            {
                zha=true;
            }
            else
            {
                ;
            }
              qDebug() << "3秒后执行的函数";
              timer2->stop();
            });
         timer1->setSingleShot(true); // 如果只需要执行一次，设置为 true
         timer1->start(5000);
         timer2->setSingleShot(true); // 如果只需要执行一次，设置为 true
         timer2->start(3000);

    }


    animation1->start();

}


void MainWindow::zhixing()
{
    MyChat* temp=mychats->findChatByAccount(currentfriend.account);
    if(temp==nullptr)
    {
        ;
    }
    else
    {
      mainwindow->chatPage(temp->Friend,temp->messages);
    }
}

void RequestWidgetItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
            // 在此处执行你的指令，例如显示详细信息或执行操作
            qDebug() << "Item clicked: ";
            mainwindow->shenqingPage(itemRequest);
        }

        // 让基类继续处理事件
        QWidget::mousePressEvent(event);
}

void FriendWidgetItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
            // 在此处执行你的指令，例如显示详细信息或执行操作
            qDebug() << "Item clicked: ";
            mainwindow->haoyouPage(itemFriend);
        }

        // 让基类继续处理事件
        QWidget::mousePressEvent(event);
}

void ChatWidgetItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
            // 在此处执行你的指令，例如显示详细信息或执行操作

            qDebug() << "Item clicked: ";
            currentfriend=itemChat.Friend;
            MyChat* temp=mychats->findChatByAccount(currentfriend.account);
            if(temp==nullptr)
            {
                qDebug() <<"未找到";
            }
            else
            {
                mainwindow->xinhao=true;
                mainwindow->chatPage(temp->Friend,temp->messages);
            }
        }
        // 让基类继续处理事件
        QWidget::mousePressEvent(event);
}

void MainWindow::chatPage(const MyFriend &friendData,MyMessages &msg)
{
    ui->stackedWidget_7->setCurrentIndex(0);
    ui->messageChangeFlag_5->setText(friendData.name);
    //界面刷新
    ui->listWidget_message->clear();
    ui->listWidget_message->update();

    while(ui->listWidget_message->count() > 0) {
           QListWidgetItem* item = ui->listWidget_message->takeItem(0);
           QWidget* widget = ui->listWidget_message->itemWidget(item);
           delete widget;
           delete item;
       }
    for (MyMessage& messageObj :msg.messagesList) {
       QListWidgetItem* item = new QListWidgetItem(ui->listWidget_message);
       item->setFlags(item->flags()& ~Qt::ItemIsSelectable);
        messageWidgetItem* widgetItem;
       if(messageObj.user1==currentuser->account)
       {
            widgetItem = new messageWidgetItem(messageObj,1,currentuser->headImage);
       }
       else
       {

            widgetItem = new messageWidgetItem(messageObj,0,friendData.headImage);
       }
       widgetItem->resize(491,70);
       item->setSizeHint(widgetItem->sizeHint()); // 使item的大小适应widgetItem
       ui->listWidget_message->addItem(item);
       ui->listWidget_message->setItemWidget(item, widgetItem);
    }

}

void MainWindow::haoyouPage(const MyFriend &friendData)
{
    ui->stackedWidget_5->setCurrentIndex(3);
    QString tmp=":/new/prefix2/image/";
    tmp=tmp+friendData.headImage;
    qDebug()<<tmp;
    QPixmap originalPixmap(tmp);
    if (originalPixmap.isNull()) {
        qDebug() << "Image failed to load!";
    }
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 设置背景为透明
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(originalPixmap.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    //ui->userImage->setPixmap(roundedPixmap);
    ui->userImage_6->setPixmap(roundedPixmap.scaled(ui->userImage_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->nameEdit_4->setText(friendData.name);
    ui->ps_4->setText(friendData.sign);
    ui->accountLineEdit_4->setText(friendData.account);
    ui->birthdayLineEdit_4->setText(friendData.birthDay);
    ui->localLineEdit_4->setText(friendData.localPlace);
}


void MainWindow::shenqingPage(const MyRequsest& friendData)
{
  ui->stackedWidget_5->setCurrentIndex(2);
  ui->messageChangeFlag_4->clear();
  bool flag=true;
  //以下代码极其重要
  for (MyFriend&  friendObj :myfriends->friendsList) {
   if(friendObj.account==friendData.account)
   {
       flag=false;
   }
  }
  if(flag)
  {
      ;
  }
  else
  {
      ui->messageChangeFlag_4->setText("已添加对方为好友");
  }
  ui->nameEdit_3->setText(friendData.name);
  ui->ps_3->setText(friendData.sign);
  ui->accountLineEdit_3->setText(friendData.account);
  ui->birthdayLineEdit_3->setText(friendData.birthDay);
  ui->localLineEdit_3->setText(friendData.localPlace);
  QString tmp=":/new/prefix2/image/";
  tmp=tmp+friendData.headImage;
  qDebug()<<tmp;
  QPixmap originalPixmap(tmp);
  if (originalPixmap.isNull()) {
      qDebug() << "Image failed to load!";
  }
  QPixmap roundedPixmap(originalPixmap.size());
  roundedPixmap.fill(Qt::transparent); // 设置背景为透明
  QPainter painter(&roundedPixmap);
  painter.setRenderHint(QPainter::Antialiasing);
  QPainterPath path;
  path.addEllipse(originalPixmap.rect());
  painter.setClipPath(path);
  painter.drawPixmap(0, 0, originalPixmap);
  //ui->userImage->setPixmap(roundedPixmap);
  ui->userImage_5->setPixmap(roundedPixmap.scaled(ui->userImage_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}
bool writeStringToFile(const QString &str, const QString &filePath) {
    // 创建一个文件对象
    QFile file(filePath);

    // 尝试打开文件以便写入
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing:" << file.errorString();
        return false;
    }

    // 创建一个文本流并关联文件
    QTextStream out(&file);

    // 写入字符串到文件
    out << str;

    // 关闭文件
    file.close();
    return true;
}
bool MainWindow::readAccountsAndDisplay(const QString &filePath) {
    // 创建一个文件对象
    ;
}
void MainWindow::updateApplication()
{
    sendMessage_application("getRequests");
    //tcpsocket_application->waitForBytesWritten();
    sendMessage_application("getFriends");
    //tcpsocket_application->waitForBytesWritten();

    //myfriends->friendsList.clear();
    {
        QString fileName = QCoreApplication::applicationDirPath();
                //用户目录
        QString add = "//..//TFWUserFile";
                //创建用户文件夹
        fileName = fileName + add +QString("//%1").arg(currentuser->account);
        QString fileName1=fileName +"//friends.txt";

        {
            QFile file(fileName1);
            // 尝试打开文件
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Cannot open file for reading:" << file.errorString();
                ;
            }
            // 创建一个文本流以便读取文件
            QTextStream in(&file);

            // 创建一个QStringList来存储账号
            QStringList accounts;

            // 逐行读取文件内容并添加到QStringList中
            while (!in.atEnd()) {
                QString line = in.readLine();
                accounts.append(line);
            }

            // 关闭文件
            file.close();

            // 遍历QStringList并输出每个账号
            for (const QString &account : accounts) {
               qDebug()<<"好友初始化"+account;
               getBaseMessageStr=account;
               sendMessage_application("getBaseMessage");
               //tcpsocket_application->waitForBytesWritten();
            }
        }
    }

    {
        QString fileName = QCoreApplication::applicationDirPath();
                //用户目录
        QString add = "//..//TFWUserFile";
                //创建用户文件夹
        fileName = fileName + add +QString("//%1").arg(currentuser->account);
        QString fileName1=fileName +"//requests.txt";

        {
            QFile file(fileName1);
            // 尝试打开文件
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qWarning() << "Cannot open file for reading:" << file.errorString();
                ;
            }
            // 创建一个文本流以便读取文件
            QTextStream in(&file);

            // 创建一个QStringList来存储账号
            QStringList accounts;

            // 逐行读取文件内容并添加到QStringList中
            while (!in.atEnd()) {
                QString line = in.readLine();
                accounts.append(line);
            }

            // 关闭文件
            file.close();

            // 遍历QStringList并输出每个账号
            for (const QString &account : accounts) {
               qDebug()<<"好友初始化"+account;
               getBaseRequestMessageStr=account;
               sendMessage_application("getBaseRequestMessage");
               //tcpsocket_application->waitForBytesWritten();
            }
        }
    }


}
/*sendMessage_application("getRequests");
  sendMessage_application("getFriends");*/

void MainWindow::updateItem()
{

    while(ui->listWidget_chat_2->count() > 0) {
           QListWidgetItem* item = ui->listWidget_chat_2->takeItem(0);
           QWidget* widget = ui->listWidget_chat_2->itemWidget(item);
           delete widget;
           delete item;
       }
    ui->listWidget_chat_2->clear();
    ui->listWidget_chat_2->update();



    for (MyFriend& friendObj :myfriends->friendsList) {
        /*
       FriendWidgetItem fitem(friendObj);
       QListWidgetItem item;
       item.setSizeHint(fitem.sizeHint());
       ui->listWidget_chat_2->addItem(&item);
       ui->listWidget_chat_2->setItemWidget(&item,&fitem);
       ui->listWidget_chat_2->update();*/
       QListWidgetItem* item = new QListWidgetItem(ui->listWidget_chat_2);
       FriendWidgetItem* widgetItem = new FriendWidgetItem(friendObj);
       widgetItem->resize(210,70);
       item->setSizeHint(widgetItem->sizeHint()); // 使item的大小适应widgetItem
       ui->listWidget_chat_2->addItem(item);
       ui->listWidget_chat_2->setItemWidget(item, widgetItem);
    }


    while(ui->listWidget_chat_4->count() > 0) {
           QListWidgetItem* item = ui->listWidget_chat_4->takeItem(0);
           QWidget* widget = ui->listWidget_chat_4->itemWidget(item);
           delete widget;
           delete item;
       }
    ui->listWidget_chat_4->clear();
    ui->listWidget_chat_4->update();



    for (MyRequsest& requestObj :myrequests->requestsList) {
        /*
       FriendWidgetItem fitem(friendObj);
       QListWidgetItem item;
       item.setSizeHint(fitem.sizeHint());
       ui->listWidget_chat_2->addItem(&item);
       ui->listWidget_chat_2->setItemWidget(&item,&fitem);
       ui->listWidget_chat_2->update();*/
       QListWidgetItem* item = new QListWidgetItem(ui->listWidget_chat_4);
       RequestWidgetItem* widgetItem = new RequestWidgetItem(requestObj);
       widgetItem->resize(210,70);
       item->setSizeHint(widgetItem->sizeHint()); // 使item的大小适应widgetItem
       ui->listWidget_chat_4->addItem(item);
       ui->listWidget_chat_4->setItemWidget(item, widgetItem);
    }

    while(ui->listWidget_chat->count() > 0) {
           QListWidgetItem* item = ui->listWidget_chat->takeItem(0);
           QWidget* widget = ui->listWidget_chat->itemWidget(item);
           delete widget;
           delete item;
       }
    ui->listWidget_chat->clear();
    ui->listWidget_chat->update();

    for (MyChat& chatObj :mychats->chatList) {
        /*
       FriendWidgetItem fitem(friendObj);
       QListWidgetItem item;
       item.setSizeHint(fitem.sizeHint());
       ui->listWidget_chat_2->addItem(&item);
       ui->listWidget_chat_2->setItemWidget(&item,&fitem);
       ui->listWidget_chat_2->update();*/
       QListWidgetItem* item = new QListWidgetItem(ui->listWidget_chat);
       ChatWidgetItem* widgetItem = new ChatWidgetItem(chatObj);
       widgetItem->resize(210,70);
       item->setSizeHint(widgetItem->sizeHint()); // 使item的大小适应widgetItem
       ui->listWidget_chat->addItem(item);
       ui->listWidget_chat->setItemWidget(item, widgetItem);
    }




}


void MainWindow::changeMessage()
{
    {
    QString tmp=":/new/prefix2/image/";
    tmp=tmp+currentuser->headImage;
    qDebug()<<tmp;
    QPixmap originalPixmap(tmp);
    if (originalPixmap.isNull()) {
        qDebug() << "Image failed to load!";
    }
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 设置背景为透明
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(originalPixmap.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    //ui->userImage->setPixmap(roundedPixmap);
    ui->userImage->setPixmap(roundedPixmap.scaled(ui->userImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    {
    QString tmp=":/new/prefix2/image/";
    tmp=tmp+currentuser->headImage;
    qDebug()<<tmp;
    QPixmap originalPixmap(tmp);
    if (originalPixmap.isNull()) {
        qDebug() << "Image failed to load!";
    }
    QPixmap roundedPixmap(originalPixmap.size());
    roundedPixmap.fill(Qt::transparent); // 设置背景为透明
    QPainter painter(&roundedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addEllipse(originalPixmap.rect());
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, originalPixmap);
    ui->userImage_2->setPixmap(roundedPixmap);

    }


    ui->message_textEdit->clear();

    ui->message_textEdit->setAlignment(Qt::AlignCenter);//ui->display_screen->setAlignment(Qt::AlignLeft);
    ui->message_textEdit->raise();

    QString tmp1;
    tmp1=currentuser->name;
    ui->message_textEdit->append(tmp1);
    QString tmp2;
    tmp2="vip等级:";
    tmp2=tmp2+currentuser->VIP_Level;
    ui->message_textEdit->append(tmp2);
    QString tmp3;
    tmp3="T龄:";
    tmp3=tmp3+currentuser->Tagt;
    ui->message_textEdit->append(tmp3);

    ui->ps->setText(currentuser->sign);
    ui->nameEdit->setText(currentuser->name);
    ui->padLineEdit->setText(currentuser->AntiMd5password);
    ui->accountLineEdit->setText(currentuser->account);
    ui->birthdayLineEdit->setText(currentuser->birthDay);
    ui->localLineEdit->setText(currentuser->localPlace);
    update();
}


void MainWindow::setplacehodetext(QLineEdit *a)
{
    QPalette palette = a->palette();
    palette.setColor(QPalette::Normal, QPalette::PlaceholderText, "#FFFAFA");
    a->setPalette(palette);
}

void MainWindow::setplacehodetextRed(QLineEdit *a)
{
    QPalette palette = a->palette();
    palette.setColor(QPalette::Normal, QPalette::PlaceholderText, "#6495ED");
    a->setPalette(palette);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{







    if(qobject_cast<QPushButton*>(obj) == ui->close)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            if(loginpage->loginSuccessFlag)
                        {
                QIcon icon = QIcon(":/new/prefix1/img2_s.png");
                //添加图标
                ssystemtrayicon->setIcon(icon);
                myfriends->removeAllFriendByAccount();
                myrequests->removeAllRequestByAccount();
                            loginpage->isMainWindowOpen=false;
                            mainwindow=nullptr;
                            loginpage->commitMessage1("logout");
                            loginpage->loginSuccessFlag=false;
                            zha=false;
                            xinzha=false;
                            xinhao=false;
                        }
            animation3->start();

            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }
    // ui->requestToBeFriend
    else if(qobject_cast<QPushButton*>(obj) == ui->requestToBeFriend)
    {
        if(event->type() == QEvent::MouseButtonRelease){
             bool flag=true;
             for (MyFriend&  friendObj :myfriends->friendsList) {
              if(friendObj.account==ui->accountLineEdit_2->text())
              {
                  flag=false;
              }
             }
             if(flag)
             {
                 requestToBeFriendStr=ui->accountLineEdit_2->text();
                 sendMessage_application("requestToBeFriend");
             }
             else
             {
                 ui->messageChangeFlag_2->setText("已成为好友");
             }
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }

    else if(qobject_cast<QPushButton*>(obj) == ui->sendMessage)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            for (MyFriend&  friendObj :myfriends->friendsList) {
              if(friendObj.account==ui->accountLineEdit_4->text())
              {
                  MyChat* mf=mychats->findChatByAccount(friendObj.account);
                  if(mf== nullptr)
                  {
                      MyChat temp(friendObj);
                      mychats->addchat(temp);
                      mainwindow->updateFlag=true;
                      ui->tabWidget->setCurrentIndex(0);
                  }
                  else
                  {
                      ui->tabWidget->setCurrentIndex(0);
                  }


              }
            }

        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
    }

    else if(qobject_cast<QPushButton*>(obj) == ui->sendMyMessage)
    {
       if(event->type() == QEvent::MouseButtonRelease)
       {
           sendMessage_application("sendMyMessage");
           sendmymessagestr=ui->message_textEdit_2->toPlainText();
           MyChat* temp=mychats->findChatByAccount(currentfriend.account);
           if(temp==nullptr)
           {
               qDebug() <<"未找到";
           }
           else
           {   MyMessage msg;
               msg.time=getCurrentDateTimeString();
               msg.user1=currentuser->account;
               msg.user2=currentfriend.account;
               msg.message=ui->message_textEdit_2->toPlainText();
               ui->message_textEdit_2->clear();
               temp->messages.addMessage(msg);
               mainwindow->chatPage(temp->Friend,temp->messages);
           }

       }
       else if(event->type() == QEvent::MouseMove)
       {
           return true;
       }
    }



    else if(qobject_cast<QPushButton*>(obj) == ui->agreeToBeFriend)
    {
        if(event->type() == QEvent::MouseButtonRelease){
             bool flag=true;
             for (MyFriend&  friendObj :myfriends->friendsList) {
              if(friendObj.account==ui->accountLineEdit_3->text())
              {
                  flag=false;
              }
             }
             if(flag)
             {
                 agreeToBeFriendStr=ui->accountLineEdit_3->text();//agreeToBeFriend
                 sendMessage_application("agreeToBeFriend");
                 for (MyRequsest& requestObj :myrequests->requestsList) {

                     if(requestObj.account==ui->accountLineEdit_3->text())
                     {
                         MyFriend tempFriend;
                         tempFriend.account=requestObj.account;
                         tempFriend.name=requestObj.name;
                         tempFriend.password=requestObj.password;
                         tempFriend.sign=requestObj.sign;
                         tempFriend.headImage=requestObj.headImage;
                         tempFriend.phoneNumber=requestObj.phoneNumber;
                         tempFriend.birthDay=requestObj.birthDay;
                         tempFriend.localPlace=requestObj.localPlace;
                         tempFriend.Tagt=requestObj.Tagt;
                         tempFriend.VIP_Level=requestObj.VIP_Level;
                         myfriends->addFriend(tempFriend);
                         updateItem();
                         break;
                     }
                 }
                 //requestToBeFriendStr=ui->accountLineEdit_2->text();
                 //sendMessage_application("requestToBeFriend");
             }
             else
             {
                 ui->messageChangeFlag_4->setText("已成为好友");
             }
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }


    else if(qobject_cast<QPushButton*>(obj) == ui->friends)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->stackedWidget_3->setCurrentIndex(0);
            ui->widget_button_1->setStyleSheet("QWidget#widget_button_1 { background-color:  rgba(255,255,255,150); }");
            ui->widget_button_2->setStyleSheet("QWidget#widget_button_2 { background-color:  rgba(255,255,255,50); }");
            ui->widget_button_3->setStyleSheet("QWidget#widget_button_3 { background-color:  rgba(255,255,255,50); }");

            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }

    else if(qobject_cast<QPushButton*>(obj) == ui->requestMessage)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->stackedWidget_3->setCurrentIndex(2);
            ui->widget_button_1->setStyleSheet("QWidget#widget_button_1 { background-color:  rgba(255,255,255,50); }");
            ui->widget_button_2->setStyleSheet("QWidget#widget_button_2 { background-color:  rgba(255,255,255,50); }");
            ui->widget_button_3->setStyleSheet("QWidget#widget_button_3 { background-color:  rgba(255,255,255,150); }");
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }

    else if(qobject_cast<QLabel*>(obj) == ui->adduser)
    {
        if(event->type() == QEvent::MouseButtonRelease){
           ui->widget_adduser->setStyleSheet("background: rgba(255,255,255,50)");//color:#FFFAFA;
           ui->stackedWidget_5->setCurrentIndex(1);
           ui->stackedWidget_6->setCurrentIndex(0);
           ui->messageChangeFlag_3->clear();
           ui->messageChangeFlag_6->clear();
           ui->messageChangeFlag_2->clear();

        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
           ui->widget_adduser->setStyleSheet("background: rgb(89, 164, 222)");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
           ui->widget_adduser->setStyleSheet("background: rgba(255,255,255,100)");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
           ui->widget_adduser->setStyleSheet("background: rgba(255,255,255,50)");//color:#FFFAFA;
        }


    }

    else if(qobject_cast<QLabel*>(obj) == ui->search_2)
    {
        if(event->type() == QEvent::MouseButtonRelease){
           ui->widget_search2->setStyleSheet("background: rgba(255,255,255,50)");//color:#FFFAFA;
           ui->messageChangeFlag_2->clear();
           if(ui->searchLineEdit_3->text().isEmpty())
           {
               ui->searchLineEdit_3->setPlaceholderText("键入账号或群号搜索");
               setplacehodetextRed(ui->searchLineEdit_3);
           }
           else
           {
               if(ui->searchLineEdit_3->text()==currentuser->account)
               {
                   ui->searchLineEdit_3->clear();
                   ui->searchLineEdit_3->setPlaceholderText("您不能搜索自己");
                   setplacehodetextRed(ui->searchLineEdit_3);
               }
               else
               {
           applicationOperation="searchUserToAdd";
           sendMessage_application("searchUserToAdd");
               }
           }

        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
           ui->widget_search2->setStyleSheet("background: rgb(89, 164, 222)");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
           ui->widget_search2->setStyleSheet("background: rgba(255,255,255,100)");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
           ui->widget_search2->setStyleSheet("background: rgba(255,255,255,50)");//color:#FFFAFA;
        }

    }


    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_1)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_1->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (1).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_1->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_1->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_1->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_2)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_2->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (2).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_2->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_2->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_2->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_3)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_3->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (3).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_3->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_3->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_3->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_4)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_4->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (4).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_4->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_4->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_4->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_5)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_5->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (5).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_5->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_5->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_5->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_6)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_6->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (6).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_6->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_6->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_6->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_7)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_7->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (7).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_7->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_7->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_7->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_8)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_8->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (8).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_8->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_8->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_8->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_9)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_9->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (9).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_9->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_9->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_9->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_10)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_10->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (10).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_10->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_10->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_10->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_11)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_11->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (11).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_11->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_11->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_11->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_12)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_12->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (12).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_12->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_12->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_12->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_13)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_13->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (13).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_13->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_13->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_13->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_14)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_14->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (14).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_14->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_14->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_14->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_15)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_15->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (15).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_15->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_15->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_15->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_16)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_16->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (16).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_16->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_16->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_16->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_17)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_17->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (17).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_17->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_17->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_17->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_18)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_18->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (18).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_18->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_18->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_18->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_19)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_19->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (19).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_19->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_19->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_19->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_20)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_20->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (20).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_20->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_20->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_20->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_21)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_21->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (21).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_21->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_21->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_21->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_22)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_22->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (22).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_22->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_22->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_22->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_23)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_23->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (23).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_23->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_23->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_23->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_24)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_24->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (24).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_24->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_24->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_24->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_25)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_25->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (25).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_25->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_25->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_25->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_26)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_26->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (26).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_26->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_26->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_26->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_27)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_27->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (27).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_27->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_27->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_27->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_28)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_28->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (28).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_28->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_28->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_28->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_29)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_29->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (29).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_29->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_29->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_29->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_30)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_30->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (30).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_30->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_30->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_30->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_31)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_31->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (31).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_31->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_31->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_31->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_32)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_32->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (32).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_32->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_32->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_32->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_33)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_33->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (33).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_33->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_33->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_33->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_34)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_34->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (34).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_34->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_34->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_34->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_35)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_35->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (35).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_35->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_35->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_35->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_36)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_36->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (36).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_36->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_36->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_36->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_37)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_37->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (37).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_37->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_37->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_37->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_38)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_38->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (38).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_38->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_38->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_38->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_39)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_39->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (39).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_39->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_39->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_39->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_40)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_40->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (40).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_40->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_40->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_40->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_41)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_41->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (41).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_41->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_41->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_41->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_42)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_42->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (42).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_42->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_42->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_42->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_43)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_43->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (43).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_43->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_43->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_43->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_44)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_44->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (44).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_44->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_44->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_44->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_45)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_45->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (45).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_45->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_45->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_45->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_46)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_46->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (46).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_46->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_46->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_46->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_47)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_47->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (47).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_47->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_47->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_47->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_48)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_48->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (48).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_48->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_48->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_48->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_49)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_49->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (49).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_49->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_49->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_49->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_50)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_50->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (50).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_50->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_50->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_50->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_51)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_51->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (51).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_51->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_51->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_51->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }

    else if(qobject_cast<QLabel*>(obj) == ui->userImageChoose_52)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            ui->userImageChoose_52->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
            headStr="head (52).JPG";
            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+headStr;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            ui->userImageChoose_52->setStyleSheet("border-style: outset;border: 3px solid rgba(0,0,128, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }
        else if(event->type() == QEvent::HoverEnter)
        {
            ui->userImageChoose_52->setStyleSheet("border-style: outset;border: 3px solid rgba(100,149,237, 255);border-radius:60px");//color:#FFFAFA;
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            ui->userImageChoose_52->setStyleSheet("border-style: outset;border: 3px solid rgba(220,220,220, 200);border-radius:60px");//color:#FFFAFA;
        }
    }


    else if(qobject_cast<QPushButton*>(obj) == ui->quitLogin)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            loginpage->chushihua();
            if(loginpage->loginSuccessFlag)
                        {
                QIcon icon = QIcon(":/new/prefix1/img2_s.png");
                //添加图标
                ssystemtrayicon->setIcon(icon);
                            mainwindow=nullptr;
                            loginpage->isMainWindowOpen=false;
                            loginpage->commitMessage1("logout");
                            loginpage->loginSuccessFlag=false;
                            zha=false;
                            xinzha=false;
                            xinhao=false;
                        }
            animation4->start();

            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }

    else if(qobject_cast<QPushButton*>(obj) == ui->changeUserMessage)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            if(changeFlag_s=="0")
            {
            changeFlag_s="1";
            ui->changeUserMessage->setText("确认");

            headStr=currentuser->headImage;

            ui->nameChange->clear();
            ui->psChange_3->clear();
            ui->birthdayChange->clear();
            ui->localChange_2->clear();
            ui->messageChangeFlag->clear();

            ui->nameChange->setText(ui->nameEdit->text());
            ui->psChange_3->setText(ui->ps->text());
            ui->birthdayChange->setText(ui->birthdayLineEdit->text());
            ui->localChange_2->setText(ui->localLineEdit->text());

            ui->nameChange->setPlaceholderText("");
            ui->psChange_3->setPlaceholderText("");
            ui->birthdayChange->setPlaceholderText("");
            ui->localChange_2->setPlaceholderText("");


            nameStr=QString();
            psStr=QString();
            locStr=QString();
            birthStr=QString();


            {
                QString tmp=":/new/prefix2/image/";
                tmp=tmp+currentuser->headImage;
                qDebug()<<tmp;
                QPixmap originalPixmap(tmp);
                if (originalPixmap.isNull()) {
                    qDebug() << "Image failed to load!";
                }
                QPixmap roundedPixmap(originalPixmap.size());
                roundedPixmap.fill(Qt::transparent); // 设置背景为透明
                QPainter painter(&roundedPixmap);
                painter.setRenderHint(QPainter::Antialiasing);
                QPainterPath path;
                path.addEllipse(originalPixmap.rect());
                painter.setClipPath(path);
                painter.drawPixmap(0, 0, originalPixmap);
                ui->userImage_3->setPixmap(roundedPixmap);
            }

            {
                int currentIndex = ui->stackedWidget_name->currentIndex();
                int windowWidth = ui->stackedWidget_name->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_name->widget(currentIndex)->height();
                int NextIndex = currentIndex + 1;
                ui->stackedWidget_name->setCurrentIndex(NextIndex);
                ui->stackedWidget_name->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_name->widget(currentIndex),"geometry");
                animation1->setDuration(700);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_name->widget(NextIndex), "geometry");
                animation2->setDuration(700);
                animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_name->widget(currentIndex)));
            }


            {
                int currentIndex = ui->stackedWidget_ps->currentIndex();
                int windowWidth = ui->stackedWidget_ps->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_ps->widget(currentIndex)->height();
                int NextIndex = currentIndex + 1;
                ui->stackedWidget_ps->setCurrentIndex(NextIndex);
                ui->stackedWidget_ps->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_ps->widget(currentIndex),"geometry");
                animation1->setDuration(700);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_ps->widget(NextIndex), "geometry");
                animation2->setDuration(700);
                animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_ps->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_local->currentIndex();
                int windowWidth = ui->stackedWidget_local->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_local->widget(currentIndex)->height();
                int NextIndex = currentIndex + 1;
                ui->stackedWidget_local->setCurrentIndex(NextIndex);
                ui->stackedWidget_local->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_local->widget(currentIndex),"geometry");
                animation1->setDuration(700);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_local->widget(NextIndex), "geometry");
                animation2->setDuration(700);
                animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_local->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_birthday->currentIndex();
                int windowWidth = ui->stackedWidget_birthday->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_birthday->widget(currentIndex)->height();
                int NextIndex = currentIndex + 1;
                ui->stackedWidget_birthday->setCurrentIndex(NextIndex);
                ui->stackedWidget_birthday->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_birthday->widget(currentIndex),"geometry");
                animation1->setDuration(700);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_birthday->widget(NextIndex), "geometry");
                animation2->setDuration(700);
                animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_birthday->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_head->currentIndex();
                int windowWidth = ui->stackedWidget_head->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_head->widget(currentIndex)->height();
                int NextIndex = currentIndex + 1;
                ui->stackedWidget_head->setCurrentIndex(NextIndex);
                ui->stackedWidget_head->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_head->widget(currentIndex),"geometry");
                animation1->setDuration(700);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_head->widget(NextIndex), "geometry");
                animation2->setDuration(700);
                animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_head->widget(currentIndex)));
            }


            }

            else if(changeFlag_s=="1")
            {
                if((!ui->nameChange->text().isEmpty())&&(!ui->psChange_3->text().isEmpty())&&(!ui->birthdayChange->text().isEmpty())&&(!ui->localChange_2->text().isEmpty()))
                {

                if(isValidDate(ui->birthdayChange->text()))
                {
                nameStr=ui->nameChange->text();
                psStr=ui->psChange_3->text();
                birthStr=ui->birthdayChange->text();
                locStr=ui->localChange_2->text();
                changeFlag_s="2";
                ui->changeUserMessage->setText("返回");

                tcpServerConnect_s();
                sendMessage_s("UchangeMessage");

                }
                else
                {
                    ui->birthdayChange->setPlaceholderText("日期格式错误");
                    setplacehodetextRed(ui->birthdayChange);
                    ui->birthdayChange->clear();
                }

                }
                else
                {
                    if(ui->nameChange->text().isEmpty())
                    {
                       ui->nameChange->setPlaceholderText("请输入昵称");
                       setplacehodetextRed(ui->nameChange);
                    }
                    if(ui->psChange_3->text().isEmpty())
                    {
                        ui->psChange_3->setPlaceholderText("请输入个性签名");
                        setplacehodetextRed(ui->psChange_3);
                    }
                    if(ui->birthdayChange->text().isEmpty())
                    {
                        ui->birthdayChange->setPlaceholderText("请输入出生日期");
                        setplacehodetextRed(ui->birthdayChange);
                    }
                    if(ui->localChange_2->text().isEmpty())
                    {
                        ui->localChange_2->setPlaceholderText("请输入地址");
                        setplacehodetextRed(ui->localChange_2);
                    }
                }






            }

            else if(changeFlag_s=="2")
            {
            changeFlag_s="0";
            ui->changeUserMessage->setText("修改信息");

             ui->messageChangeFlag->clear();
            changeMessage();
            update();



            {
                int currentIndex = ui->stackedWidget_name->currentIndex();
                int windowWidth = ui->stackedWidget_name->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_name->widget(currentIndex)->height();
                int PreIndex = currentIndex - 1;
                ui->stackedWidget_name->setCurrentIndex(PreIndex);
                ui->stackedWidget_name->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_name->widget(currentIndex),"geometry");
                animation1->setDuration(300);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_name->widget(PreIndex), "geometry");
                animation2->setDuration(300);
                animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_name->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_ps->currentIndex();
                int windowWidth = ui->stackedWidget_ps->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_ps->widget(currentIndex)->height();
                int PreIndex = currentIndex - 1;
                ui->stackedWidget_ps->setCurrentIndex(PreIndex);
                ui->stackedWidget_ps->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_ps->widget(currentIndex),"geometry");
                animation1->setDuration(300);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_ps->widget(PreIndex), "geometry");
                animation2->setDuration(300);
                animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_ps->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_local->currentIndex();
                int windowWidth = ui->stackedWidget_local->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_local->widget(currentIndex)->height();
                int PreIndex = currentIndex - 1;
                ui->stackedWidget_local->setCurrentIndex(PreIndex);
                ui->stackedWidget_local->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_local->widget(currentIndex),"geometry");
                animation1->setDuration(300);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_local->widget(PreIndex), "geometry");
                animation2->setDuration(300);
                animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_local->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_birthday->currentIndex();
                int windowWidth = ui->stackedWidget_birthday->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_birthday->widget(currentIndex)->height();
                int PreIndex = currentIndex - 1;
                ui->stackedWidget_birthday->setCurrentIndex(PreIndex);
                ui->stackedWidget_birthday->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_birthday->widget(currentIndex),"geometry");
                animation1->setDuration(300);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_birthday->widget(PreIndex), "geometry");
                animation2->setDuration(300);
                animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_birthday->widget(currentIndex)));
            }

            {
                int currentIndex = ui->stackedWidget_head->currentIndex();
                int windowWidth = ui->stackedWidget_head->widget(currentIndex)->width();
                int windowHieght = ui->stackedWidget_head->widget(currentIndex)->height();
                int PreIndex = currentIndex - 1;
                ui->stackedWidget_head->setCurrentIndex(PreIndex);
                ui->stackedWidget_head->widget(currentIndex)->show();
                QPropertyAnimation* animation1;
                QPropertyAnimation* animation2;
                QParallelAnimationGroup* group = new QParallelAnimationGroup;
                animation1 = new QPropertyAnimation(ui->stackedWidget_head->widget(currentIndex),"geometry");
                animation1->setDuration(300);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_head->widget(PreIndex), "geometry");
                animation2->setDuration(300);
                animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_head->widget(currentIndex)));
            }


            }
            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }


    else if(qobject_cast<QPushButton*>(obj) == ui->changePsword)
    {
        if(event->type() == QEvent::MouseButtonRelease){
            qDebug() << changeFlag;
            if(changeFlag=="0")
            {

                ui->brandName_24->setText("");
                ui->padLineEdit_2->clear();
                ui->padLineEdit_2->setPlaceholderText("");
                ui->textEdit_2->clear();
                ui->stackedWidget_4->setCurrentIndex(0);

                ui->changePsword->setText("确认");
                changeFlag="1";//修改
                qDebug() << changeFlag;
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
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_2->widget(currentIndex)));


            }
            else if(changeFlag=="1")
            {

                if(ui->padLineEdit_2->text().isEmpty())
                {
                    setplacehodetextRed(ui->padLineEdit_2);
                    ui->padLineEdit_2->setPlaceholderText("请输入新密码");
                }
                else
                {
                ui->changePsword->setText("返回");
                changeFlag="2";
                qDebug() << changeFlag;
                tcpServerConnect();
                sendMessage("Uchangepassword");
                }


            }
            else if(changeFlag=="2")
            {
                changeMessage();
                update();


                ui->brandName_24->setText("");
                ui->padLineEdit_2->clear();
                ui->padLineEdit_2->setPlaceholderText("");
                ui->textEdit_2->clear();
                ui->stackedWidget_4->setCurrentIndex(0);



                changeFlag="0";
                qDebug() << changeFlag;
                ui->changePsword->setText("修改密码");

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
                animation1->setDuration(300);
                animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
                animation1->setEndValue(QRect(windowWidth, 0, windowWidth, windowHieght));
                animation2 =new QPropertyAnimation(ui->stackedWidget_2->widget(PreIndex), "geometry");
                animation2->setDuration(300);
                animation2->setStartValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
                animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
                group->addAnimation(animation1);
                group->addAnimation(animation2);
                group->start();
                group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_2->widget(currentIndex)));
            }

            }
        else if(event->type() == QEvent::MouseMove)
        {
            return true;
        }

    }

  return false;
}



void MainWindow::tcpServerConnect()
{
    delete tcpsocket;
    tcpsocket = nullptr;
    //实例化socket
    tcpsocket = new QTcpSocket(this);
    //断开现有连接
    tcpsocket->abort();
    //连接到本地的7777端口
    tcpsocket->connectToHost(tfwaddress->serveRemoteAddress, tfwaddress->port7777);
    //有可读信息，发送readyRead()
    connect(tcpsocket,&QTcpSocket::readyRead,this,&MainWindow::readMessage);
    connect(tcpsocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
}

void MainWindow::tcpServerConnect_s()
{
    delete tcpsocket_s;
    tcpsocket_s = nullptr;
    //实例化socket
    tcpsocket_s = new QTcpSocket(this);
    //断开现有连接
    tcpsocket_s->abort();
    //连接到本地的7777端口
    tcpsocket_s->connectToHost(tfwaddress->serveRemoteAddress, tfwaddress->port7777);
    //有可读信息，发送readyRead()
    connect(tcpsocket_s,&QTcpSocket::readyRead,this,&MainWindow::readMessage_s);
    connect(tcpsocket_s, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError_s()));
}

void MainWindow::tcpServerConnect_application()
{
    delete tcpsocket_application;
    tcpsocket_application = nullptr;
    //实例化socket
    tcpsocket_application = new QTcpSocket(this);
    //断开现有连接
    tcpsocket_application->abort();
    //连接到本地的7777端口
    tcpsocket_application->connectToHost(tfwaddress->serveRemoteAddress, tfwaddress->port6666);
    //有可读信息，发送readyRead()
    connect(tcpsocket_application,&QTcpSocket::readyRead,this,&MainWindow::readMessage_application);
}

void MainWindow::handleError()
{
    int currentIndex = ui->stackedWidget_4->currentIndex();
    int windowWidth = ui->stackedWidget_4->widget(currentIndex)->width();
    int windowHieght = ui->stackedWidget_4->widget(currentIndex)->height();
    int NextIndex = currentIndex + 1;
    ui->stackedWidget_4->setCurrentIndex(NextIndex);
    ui->stackedWidget_4->widget(currentIndex)->show();
    QPropertyAnimation* animation1;
    QPropertyAnimation* animation2;
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    animation1 = new QPropertyAnimation(ui->stackedWidget_4->widget(currentIndex),"geometry");
    animation1->setDuration(700);
    animation1->setStartValue(QRect(0, 0, windowWidth, windowHieght));
    animation1->setEndValue(QRect(-windowWidth, 0, windowWidth, windowHieght));
    animation2 =new QPropertyAnimation(ui->stackedWidget_4->widget(NextIndex), "geometry");
    animation2->setDuration(700);
    animation2->setStartValue(QRect(windowWidth, 0, windowWidth, windowHieght));
    animation2->setEndValue(QRect(0, 0, windowWidth, windowHieght));
    group->addAnimation(animation1);
    group->addAnimation(animation2);
    group->start();
    group->setProperty("widget", QVariant::fromValue(ui->stackedWidget_4->widget(currentIndex)));
    ui->textEdit_2->append("修改失败");
    ui->textEdit_2->append("网络连接错误");
}

void MainWindow::handleError_s()
{
    ui->messageChangeFlag->setText("修改失败");
}

void MainWindow::handleError_application()
{
    if(applicationOperation=="searchUserToAdd")
    {
    ui->messageChangeFlag_3->setText("检索失败");
    ui->messageChangeFlag_3->setText("网络连接错误");
    }
}

void MainWindow::sendMessage(QString Msg)
{
    qDebug() << "FindPassword::sendMessage:发送消息";
    if(Msg == "Uchangepassword")
    {
        QString temp=currentuser->account+"___"+ui->padLineEdit_2->text();
        QString string = "Uchangepassword|" + temp;
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

void MainWindow::sendMessage_s(QString Msg)
{
    qDebug() << "发送消息";
    if(Msg == "UchangeMessage")
    {
        QString string = "UchangeMessage|" + currentuser->account+"|"+headStr+"|"+nameStr+"|"+psStr+"|"+birthStr+"|"+locStr;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "UchangeMessage::sendMessage:" << string;
        //发送信息
        tcpsocket_s->write(message);
    }
    qDebug() << "UchangeMessage::sendMessage:发送完成";
}

void MainWindow::sendMessage_application(QString Msg)
{
    qDebug() << "发送消息";
    if(Msg == "getRequests")
    {
        QString string = "getRequests|" + currentuser->account;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "UchangeMessage::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);
        tcpsocket_application->waitForBytesWritten();
    }
    else if(Msg=="requestToBeFriend")
    {
        QString string = "requestToBeFriend|" + currentuser->account+"|"+ui->accountLineEdit_2->text();
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "requestToBeFriend::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);
        ui->messageChangeFlag_2->setText("发送成功");
    }
    else if(Msg=="agreeToBeFriend")
    {
        //agreeToBeFriend
        QString string = "agreeToBeFriend|" + currentuser->account+"|"+ui->accountLineEdit_3->text();
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "agreeToBeFriend::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);
        tcpsocket_application->waitForBytesWritten();
         ui->messageChangeFlag_4->setText("发送成功");
    }
    else if(Msg == "searchUserToAdd")
    {
        QString string = "searchUserToAdd|" + currentuser->account+"|"+ui->searchLineEdit_3->text();
        ui->searchLineEdit_3->clear();
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "UchangeMessage::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);

    }
    else if(Msg == "getBaseMessage")
    {
        QString string = "getBaseMessage|" + currentuser->account+"|"+getBaseMessageStr;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "UchangeMessage::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);

    }
    else if(Msg=="getBaseRequestMessage")
    {
        //getBaseRequestMessageStr
        QString string = "getBaseRequestMessage|" + currentuser->account+"|"+getBaseRequestMessageStr;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "UchangeMessage::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);

    }
    else if(Msg == "getFriends")
    {
        QString string = "getFriends|" + currentuser->account;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "UchangeMessage::sendMessage:" << string;
        //发送信息
        tcpsocket_application->write(message);

    }
    else if(Msg == "sendMyMessage")
    {
        QString string = "sendMyMessage|" + currentuser->account+"|"+currentfriend.account+"|"+getCurrentDateTimeString()+"|"+sendmymessagestr;
        QByteArray message;
        //以只读打开QByteArray，并设置版本，服务端客户端要一致
        QDataStream out(&message,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_14);
        //写入输出流
        out << string;
        qDebug() << "消息发送成功" << string;
        //发送信息
        tcpsocket_application->write(message);
    }
    qDebug() << "getRequests::sendMessage:发送完成";
}


void MainWindow::readMessage()
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
    if(msg[0] == "Uchangepassword"){
         account = msg[1];
         if(account==currentuser->account)
         {
             ui->brandName_24->setText("修改成功");

             currentuser->AntiMd5password=ui->padLineEdit_2->text();
             qDebug() << currentuser->AntiMd5password ;

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
                    out <<currentuser->account;
                    out<<"\n";
                    out <<currentuser->AntiMd5password;
                    file.close();
                    }
                  }

             }
             else
             {
                 ;
             }




         }
    }
    qDebug() << "FindPassword::readMessage:读取完成";
}

void MainWindow::readMessage_s()
{
    //实例化套接字的输入流，读信息
    QDataStream in(tcpsocket_s);
    in.setVersion(QDataStream::Qt_5_4);
    qDebug() << "UchangeMessage::readMessage:读取消息";
    QString greeting;
    QString account;
    QString password;
    //将信息写入greeting读取信息
    in >> greeting;
    //读取的信息
    qDebug() << "UchangeMessage::readMessage:" << greeting;
    //字符串分割
    QStringList msg = greeting.split("|");
    if(msg[0] == "UchangeMessage"){
         account = msg[1];
         if(account==currentuser->account)
         {
             ui->messageChangeFlag->setText("修改成功");

             currentuser->headImage=headStr;
             currentuser->sign=psStr;
             currentuser->name=nameStr;
             currentuser->localPlace=locStr;
             currentuser->birthDay=birthStr;


             QString fileName = QCoreApplication::applicationDirPath();
                     //用户目录
             QString add = "//..//TFWUserFile";
                     //创建用户文件夹
             fileName = fileName + add +QString("//%1").arg(currentuser->account);
                     //信息保存
             QDir * file = new QDir;
                     //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
             bool exist_1 = file->exists(fileName);
             if(exist_1)
             {
                 qDebug()<<"已存在";
                 QFile file(fileName +"//data.txt");
                 if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                 {
                     QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
                     out << currentuser->account<<"\n";
                     out << currentuser->name<<"\n";
                     out << currentuser->password<<"\n";
                     out << currentuser->sign<<"\n";
                     out << currentuser->headImage<<"\n";
                     out << currentuser->phoneNumber<<"\n";
                     out << currentuser->birthDay<<"\n";
                     out << currentuser->localPlace<<"\n";
                     out << currentuser->Tagt<<"\n";
                     out << currentuser->VIP_Level<<"\n";
                 }
                 file.close();

             }
             else
             {
                 bool ok = file->mkpath(fileName);
                             if(ok)
                             {
                                 QFile file(fileName +"//data.txt");
                                 if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                                 {
                                     QTextStream out(&file); // 创建一个QTextStream对象，用于写入内容到文件
                                     out << currentuser->account<<"\n";
                                     out << currentuser->name<<"\n";
                                     out << currentuser->password<<"\n";
                                     out << currentuser->sign<<"\n";
                                     out << currentuser->headImage<<"\n";
                                     out << currentuser->phoneNumber<<"\n";
                                     out << currentuser->birthDay<<"\n";
                                     out << currentuser->localPlace<<"\n";
                                     out << currentuser->Tagt<<"\n";
                                     out << currentuser->VIP_Level<<"\n";
                                 }
                                 file.close();
                             }
                             else
                             {
                                 qDebug()<<"未创建成功";
                             }

             }




         }
    }
    qDebug() << "FindPassword::readMessage:读取完成";
}



void MainWindow::readMessage_application()
{
    //实例化套接字的输入流，读信息
    QByteArray receivedData = tcpsocket_application->readAll();
    QString greeting;
    QString account;
    QString password;
    //将信息写入greeting读取信息
    QDataStream stream(&receivedData, QIODevice::ReadOnly);
    stream.setVersion(QDataStream::Qt_5_4); // 使用与发送端相同的Qt版本
    stream >> greeting;
    //读取的信息
    //字符串分割
    QStringList msg = greeting.split("|");
    if(msg[0] == "getRequests"){
         account = msg[1];
         if(account==currentuser->account)
         {
           qDebug() << "getRequests successfully" << greeting;

           QString fileName = QCoreApplication::applicationDirPath();
                   //用户目录
           QString add = "//..//TFWUserFile";
                   //创建用户文件夹
           fileName = fileName + add +QString("//%1").arg(currentuser->account);
           QString fileName1=fileName +"//requests.txt";
           bool ifopen=writeStringToFile(msg[2],fileName1);
           if(ifopen)
           {
               qDebug()<<"好友初始化成功";
           }

         }
    }
    else if(msg[0] == "getFriends")
    {
        account = msg[1];
        if(account==currentuser->account)
        {
          qDebug() << "getFriends successfully" << greeting;
          QString fileName = QCoreApplication::applicationDirPath();
                  //用户目录
          QString add = "//..//TFWUserFile";
                  //创建用户文件夹
          fileName = fileName + add +QString("//%1").arg(currentuser->account);
          QString fileName1=fileName +"//friends.txt";
          bool ifopen=writeStringToFile(msg[2],fileName1);
          if(ifopen)
          {
              qDebug()<<"好友初始化成功";
          }
        }
    }
    else if(msg[0]=="searchUserToAdd")
    {
        account = msg[1];
        if(account==currentuser->account)
        {
            ui->stackedWidget_6->setCurrentIndex(1);
            ui->nameEdit_2->setText(msg[3]);
            ui->ps_2->setText(msg[5]);
            ui->accountLineEdit_2->setText(msg[2]);
            ui->birthdayLineEdit_2->setText(msg[8]);
            ui->localLineEdit_2->setText(msg[9]);
            {
            QString tmp=":/new/prefix2/image/";
            tmp=tmp+msg[6];
            qDebug()<<tmp;
            QPixmap originalPixmap(tmp);
            if (originalPixmap.isNull()) {
                qDebug() << "Image failed to load!";
            }
            QPixmap roundedPixmap(originalPixmap.size());
            roundedPixmap.fill(Qt::transparent); // 设置背景为透明
            QPainter painter(&roundedPixmap);
            painter.setRenderHint(QPainter::Antialiasing);
            QPainterPath path;
            path.addEllipse(originalPixmap.rect());
            painter.setClipPath(path);
            painter.drawPixmap(0, 0, originalPixmap);
            //ui->userImage->setPixmap(roundedPixmap);
            ui->userImage_4->setPixmap(roundedPixmap.scaled(ui->userImage_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }
    else if(msg[0]=="searchUserToAddFalse")
    {
        account = msg[1];
        if(account==currentuser->account)
        {
            ui->stackedWidget_6->setCurrentIndex(0);
            ui->messageChangeFlag_3->setText("检索失败");
            ui->messageChangeFlag_6->setText("用户不存在");
        }
    }
    else if(msg[0]=="getBaseRequestMessage")
    {
        //getBaseRequestMessageStr
        account = msg[1];
        if(account==currentuser->account)
        {
            MyRequsest tempRequest;
            tempRequest.account=msg[2];
            tempRequest.name=msg[3];
            tempRequest.password=msg[4];
            tempRequest.sign=msg[5];
            tempRequest.headImage=msg[6];
            tempRequest.phoneNumber=msg[7];
            tempRequest.birthDay=msg[8];
            tempRequest.localPlace=msg[9];
            tempRequest.Tagt=msg[10];
            tempRequest.VIP_Level=msg[11];
            MyRequsest *tempRequest1=nullptr;
            tempRequest1=myrequests->findRequestByAccount(tempRequest.account);
            if(tempRequest1==nullptr)
            {
                myrequests->addRequest(tempRequest);
                mainwindow->updateFlag=true;












           }
            else
            {
                if(tempRequest==*tempRequest1)
                {
                    ;
                }
                else
                {
                    myrequests->removeRequestByAccount(msg[2]);
                    myrequests->addRequest(tempRequest);
                    mainwindow->updateFlag=true;




                }
            }

        }
    }
    else if(msg[0]=="getBaseMessage")
    {
        account = msg[1];
        if(account==currentuser->account)
        {
            MyFriend tempFriend;
            tempFriend.account=msg[2];
            tempFriend.name=msg[3];
            tempFriend.password=msg[4];
            tempFriend.sign=msg[5];
            tempFriend.headImage=msg[6];
            tempFriend.phoneNumber=msg[7];
            tempFriend.birthDay=msg[8];
            tempFriend.localPlace=msg[9];
            tempFriend.Tagt=msg[10];
            tempFriend.VIP_Level=msg[11];
            MyFriend *tempFriend1=nullptr;
            tempFriend1=myfriends->findFriendByAccount(tempFriend.account);
            if(tempFriend1==nullptr)
            {
                myfriends->addFriend(tempFriend);
                mainwindow->updateFlag=true;

            }
            else
            {

                if(tempFriend==*tempFriend1)
                {
                    ;
                }
                else
                {
                    myfriends->removeFriendByAccount(msg[2]);
                    myfriends->addFriend(tempFriend);
                    mainwindow->updateFlag=true;

                }
            }
        }
        /*searchUserMessage = "getBaseMessage|" + account+"|"+accountTemp + "|" + nameTemp + "|"
                            + passwordTemp + "|" + signTemp+ "|"+ headTemp + "|"+ phoneTemp + "|"+ birthdayTemp + "|"+ localTemp + "|"+ tagtTemp + "|"+ vipTemp;*/
        /*QString account;
    QString name;
    QString password;
    QString sign;
    QString headImage;
    QString phoneNumber;
    QString birthDay;
    QString localPlace;
    QString Tagt;
    QString VIP_Level;*/


    }
    else if(msg[0]=="getBaseMessageFalse")
    {
        ;
    }
    else if(msg[0]=="sendMyMessage")
    {
        qDebug() << "我接受到了一个信号 但不知道是不是发给我";
        account = msg[2];
        if(account==currentuser->account)
        {
            qDebug() << "它确实是发给我的";
            MyMessage ms;
            ms.time=msg[3];
            ms.user1=msg[1];
            ms.user2=msg[2];
            ms.message=msg[4];
            MyChat* temp=mychats->findChatByAccount(msg[1]);
            if(temp==nullptr)
            {
                qDebug() <<"未找到";
            }
            else
            {
                temp->messages.addMessage(ms);
                if(msg[1]==currentfriend.account)
                {

                          mainwindow->chatPage(temp->Friend,temp->messages);
                          xinzha=true;
                }
                else
                {
                    ;
                }

            }


        }


    }
    else if(msg[0]=="jihuo")
    {
        qDebug() << "接收到激活信号";
        account = msg[1];
        if(account==currentuser->account)
        {
            qDebug() << "激活函数执行";
            updateApplication();
            qDebug() << "激活函数执行成功";

        }
    }
}




MainWindow::~MainWindow()
{
    delete animation1;
    delete animation2;
    delete animation3;
    delete animation4;
    delete shadow_effect1;
    delete shadow_effect2;
    delete tcpsocket;
    delete tcpsocket_s;
    delete ui;
    if(timer1)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       {
        delete timer1;
    }
    if(timer2)
    {
        delete timer2;
    }
    if(timer3)
    {
        delete timer3;
    }
    if(timer4)
    {
        delete timer4;
    }
    if(timer5)
    {
        delete timer5;
    }
}






