#ifndef USERLIST_H
#define USERLIST_H

#include<QString>

/*query->exec("create table User("                                                               //构建用户数据表格
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
            "VIP_Level varchar(25))");  */

class CurrentUser
{
public:
    QString account;
    QString name;
    QString password;
    QString sign;
    QString headImage;
    QString phoneNumber;
    QString birthDay;
    QString localPlace;
    QString Tagt;
    QString VIP_Level;

    void writeIn(QString str);

private:

};

#endif // USERLIST_H
