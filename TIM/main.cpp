/*吉林大学软件学院2023年大二第一学期通讯软件制作任务*/
/*TFW软件的主函数*/
#include<QDesktopWidget>                                                                     /*用于居中显示软件*/
#include <QApplication>                                                                      /*qapplication头文件 qt程序声明*/
#include"addresssetting.h"
#include "widget.h"                                                                          /*登录窗口头文件*/
#include"heartbeat.h"
#include"userlist.h"


Widget* ww;
addressSetting* bb;
int main(int argc, char *argv[])                                                             /*必须规范写法 因为涉及到传值*/
{  
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);                             //进行不同屏幕的dpi适配 防止布局错乱
    QApplication a(argc, argv);                                                              //程序声明 
    UserList *user;
    user = new UserList();
    Widget w;                                                                                //声明创建窗口
    addressSetting *b;
    bb=b;
    ww=&w;
    w.move((a.desktop()->width() - w.width()) / 2, (a.desktop()->height() - w.height()) / 2);//窗口居中
    w.show();                                                                                //窗口显示
    HeartBeat heartbeat;
    return a.exec();                                                                         //程序不按按钮不结束 让程序ui在屏幕上停留

}
