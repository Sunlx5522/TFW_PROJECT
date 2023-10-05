/*文档说明*/
//由于局域网通讯需要有自己的服务端，本软件充当服务端

#include "widget.h"
#include "userlist.h"
#include"heartbeat.h"
#include <QApplication>
#include <QDesktopWidget>

Widget *loginpage;
UserList * user;
int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);                                   //进行不同屏幕的dpi适配 防止布局错乱
    QApplication a(argc, argv);
    Widget loginPage;
    loginpage=&loginPage;
    loginPage.move((a.desktop()->width() - loginPage.width()) / 2, (a.desktop()->height() - loginPage.height()) / 2);      //窗口居中
    UserList User;
    loginPage.user=&User;
    user=&User;
    loginPage.show();
    HeartBeat heartbeat;
    HeartBeat1 heartbeat1;
    return a.exec();

}
