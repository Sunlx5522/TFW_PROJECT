/*吉林大学软件学院2023年大二第一学期通讯软件制作任务*/
/*TFW软件的主函数*/
#include <QDesktopWidget> //用于居中显示软件
#include <QApplication> //qapplication头文件 qt程序声明
#include "applicationConnectTimer.h"
#include "addresssetting.h" //地址设置头文件
#include "widget.h" //登录窗口头文件
#include "heartbeat.h" //心跳程序头文件
#include "qrcode.h" //二维码程序头文件
#include "userlist.h" //用户列表头文件
#include "findpassword.h" //找回密码头文件
#include "signUp.h" //注册功能头文件
#include "address.h" //地址头文件
#include <QObject>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include "mainwindow.h"
#include <QTcpSocket>
#include <QSystemTrayIcon>
tfwAddress* tfwaddress;
Widget* loginpage;
CurrentUser* currentuser;
MyFriends *myfriends;
MyRequsests* myrequests;
MyChats *mychats;
signUp* signuppage;
qrcode *qrcodepage;
addressSetting* addresssetting;
findpassword * findpasswordpage;
QSystemTrayIcon  *ssystemtrayicon;  //系统托盘
QApplication *aa;
MainWindow *mainwindow=nullptr;
QTcpSocket *client1_s;
void closeAppkication(void)
{
    if(loginpage->loginSuccessFlag)
    {
        loginpage->commitMessage1("logout");
        loginpage->client1->waitForBytesWritten();
        loginpage->loginSuccessFlag=false;
    }
   aa->quit();
}
int main(int argc, char *argv[])                                                             /*必须规范写法 因为涉及到传值*/
{  
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); //进行不同屏幕的dpi适配 防止布局错乱
    QApplication a(argc, argv); //程序声明
    aa=&a;
    QMenu menu;
    QAction m_pCloseAction;
    QObject::connect(&m_pCloseAction, &QAction::triggered, &closeAppkication);
    QSystemTrayIcon  systemtrayicon;  //系统托盘
    ssystemtrayicon =&systemtrayicon;
    QIcon icon = QIcon(":/new/prefix1/img2_s.png");
    systemtrayicon.setIcon(icon);
    systemtrayicon.setToolTip(QObject::trUtf8("TFW"));
    m_pCloseAction.setText("退出");
    menu.addAction(&m_pCloseAction);
    systemtrayicon.setContextMenu(&menu);
    systemtrayicon.show();
    HeartBeat heartbeat; //心跳程序类的实例化 每隔相应时间 执行对应代码
    HeartBeat_s  heartbeat_s;
    tfwAddress TfwAddress; //将地址类实例化
    tfwaddress = &TfwAddress; //指针复制 便于操作
    Widget *loginPage; //声明创建登录窗口
    loginPage = new Widget;
    loginpage=loginPage; //指针复制 便于操作
    CurrentUser currentUser; //用户类的实例化
    currentuser=&currentUser; //指针复制 便于操作
    MyFriends myFriends;
    myfriends =&myFriends;
    MyRequsests myRequests;
    myrequests=&myRequests;
    MyChats myChats;
    mychats=&myChats;
    signUp SingUpPage; //注册功能类的实例化
    signuppage=&SingUpPage; //指针复制 便于操作
    qrcode * QrcodePage = nullptr; //二维码页面的指针 在widget.cpp中 若点击相应按钮 则有相应的创建操作
    qrcodepage = QrcodePage; //指针复制 便于操作
    addressSetting *AddressSetting = nullptr; //地址设置页面的指针 在widget.cpp中 若点击相应按钮 则有相应的创建操作
    addresssetting=AddressSetting; //指针复制 便于操作
    findpassword *FindPasswordPage = nullptr; //找回密码页面的指针 在widget.cpp中 若点击相应按钮 则有相应的创建操作
    findpasswordpage = FindPasswordPage; //指针复制 便于操作
    MainWindow *mainWaindow= nullptr;//主页面的指针 在widget.cpp中 若点击相应按钮 则有相应的创建操作
    mainwindow =mainWaindow;//指针复制 便于操作
    loginPage->move((a.desktop()->width() - loginPage->width()) / 2, (a.desktop()->height() - loginPage->height()) / 2); //窗口居中
    loginPage->show(); //窗口显示
    return a.exec(); //程序不按按钮不结束 让程序ui在屏幕上停留
}
