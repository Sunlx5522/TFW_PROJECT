#ifndef USERLIST_H
#define USERLIST_H

//数据库与用户列表显示
#include <QTime>                                                                                   //时间头文件
#include <QTableView>                                                                              //qt表格视窗
#include <QMessageBox>                                                                             //qt信息窗口头文件

#include<QVariant>                                                                                 //数据类型
#include <QSqlDatabase>
#include <QSqlQuery>

class UserList
{
public:
    UserList();
    ~UserList();
    QSqlDatabase db;                                                                               //数据库

};

#endif // USERLIST_H
