#ifndef USERLIST_H
#define USERLIST_H

//数据库与用户列表显示
#include <QTime>                                                                                   //时间头文件
#include <QTableView>                                                                              //qt表格视窗
#include <QMessageBox>                                                                             //qt信息窗口头文件

#include<QVariant>                                                                                 //数据类型
#include<QtSql/QSqlQuery>                                                                          //数据库操作指令
#include<QtSql/QSqlDatabase>                                                                       //qt内置数据库
#include<QtSql/QSqlQueryModel>                                                                     //数据库模型

class UserList
{
public:
    UserList();
    ~UserList();
    QSqlDatabase db;                                                                               //数据库
    QSqlQuery *query;                                                                              //数据库操作指针
    QSqlQueryModel *model;                                                                         //数据库模型
    void tageUpdate();
    QString addUser(QString message);                                                              //添加用户函数
    int CheckUser(QString account, QString password);                                              //用户状态检查
    void initDB();
};

#endif // USERLIST_H
