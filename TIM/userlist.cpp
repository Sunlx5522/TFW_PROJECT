#include "widget.h"
extern Widget *ww;
#include "userlist.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include <QMainWindow>
#include <QTableView>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTime>


UserList::UserList()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("UserList.db");                                                             //如果文件中已有则不需要重复添加
    //打开

    //指定连接
    QSqlQuery query=QSqlQuery(db);                                                                  //操作指针链接
    query.exec("create table User("                                                               //构建用户数据表格
                "account varchar(25) primary key,"                                                 //用户账号
                "name varchar(25) not null,"                                                       //用户昵称
                "password varchar(20) not null,"                                                   //用户密码
                "sign varchar(25),"                                                                //个性签名
                "headImage varchar(10),"                                                           //头像图片名称
                "state bit default 0,"
                "birthDay varchar(25),"
                "localPlace varchar(25),"
                "Tagt varchar(25),"
                "check varchar(25),"
                "VIP_Level varchar(25))");                                                           //用户状态
                                                                                                   //其余特定数据待添加（用户和群组列表最重要）
    query.exec("insert into User values('a','a','123','I am a','head1.png',0,'2004_1_23','ChangChun','0','0','0')");                  //26个原始用户，便于调试
    //得到指向数据库的指针
    db = QSqlDatabase::database();                                                                 //获取数据库指针
}

UserList::~UserList()
{
;
}
