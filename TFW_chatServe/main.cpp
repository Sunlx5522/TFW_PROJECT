/*文档说明*/
//由于局域网通讯需要有自己的服务端，本软件充当服务端

#include "widget.h"
#include "userlist.h"
#include"heartbeat.h"
#include <QApplication>
#include <QDesktopWidget>

Widget *ww;
int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);                                   //进行不同屏幕的dpi适配 防止布局错乱
    QApplication a(argc, argv);
    Widget w;
    ww=&w;
    w.move((a.desktop()->width() - w.width()) / 2, (a.desktop()->height() - w.height()) / 2);      //窗口居中
    UserList *user;
    user = new UserList();
    w.user=user;
    w.show();
    HeartBeat heartbeat;
    return a.exec();

}
