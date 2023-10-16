#include "widget.h"
extern Widget *loginpage;
#include "userlist.h"
#include "heartbeat.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMainWindow>
#include <QMainWindow>
#include <QTableView>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QTime>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include"GetTime.h"
QSqlDatabase *ddb;
void createFile(QString str)
{
    QString fileName = QCoreApplication::applicationDirPath();
            //用户目录
    QString add = "//..//TFW_CHAT_SERVE_UserFile";
            //创建用户文件夹
    fileName = fileName + add +QString("//%1").arg(str);
            //信息保存
    QDir * file = new QDir;
            //文件夹是否存在，若存在则表示信息已经存在，只需要更新内容即可。
bool exist_1 = file->exists(fileName);
if(exist_1)
{
    qDebug()<<"已存在";

}
else
{
    bool ok = file->mkpath(fileName);
                if(ok)
                {
                    {
                     QFile file(fileName +"//friendsData.txt");
                     qDebug()<<fileName +"//friendsData.txt";

                     if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                     {
                       qDebug()<<"txt文件创建成功";
                     }
                      file.close();
                    }





                      {
                      QFile file(fileName +"//groupsData.txt");
                      qDebug()<<fileName +"//groupsData.txt";
                      if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                      {
                        qDebug()<<"txt文件创建成功";
                      }
                       file.close();
                      }

                    {
                    QFile file(fileName +"//requestData.txt");
                    qDebug()<<fileName +"//requestData.txt";
                    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate))
                    {
                      qDebug()<<"txt文件创建成功";
                    }
                     file.close();
                    }

                  }
                else
                {
                    qDebug()<<"未创建成功";
                }
}



}


UserList::UserList()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("UserList.db");                                                             //如果文件中已有则不需要重复添加
    ddb=&db;
    //打开
    if(!db.open()){
      loginpage->shouError();                                                                             //打不开 输出错误命令（此指令一般情况下不会执行）
     }
    //指定连接
    query = new QSqlQuery(db);                                                                     //操作指针链接
    query->exec("create table User("                                                               //构建用户数据表格
                "account varchar(50) primary key,"                                                 //用户账号
                "name varchar(50) not null,"                                                       //用户昵称
                "password varchar(50) not null,"                                                   //用户密码
                "sign varchar(50),"                                                                //个性签名
                "headImage varchar(50),"                                                           //头像图片名称
                "phoneNumber varchar(50),"
                "state bit default 0,"
                "birthDay varchar(50),"
                "localPlace varchar(50),"
                "Tagt varchar(50),"
                "VIP_Level varchar(50),"
                "signUpDate varchar(50),"
                "ban bit default 0,"
                "passwordq1 varchar(50),"
                "passwordq2 varchar(50),"
                "passwordq3 varchar(50))");
                                                                                                   //其余特定数据待添加（用户和群组列表最重要）
    query->exec("insert into User values('a','a','123','I am a','head (1).JPG','15999999999',0,'2004_1_23','ChangChun','0','0','2022_9_22',0,'q1','q2','q3')");                  //4个原始用户，便于调试
    query->exec("insert into User values('b','b','123','I am b','head (2).JPG','15999999999',0,'2004_1_23','ChangChun','0','0','2022_9_22',0,'q1','q2','q3')");
    query->exec("insert into User values('c','c','123','I am c','head (3).JPG','15999999999',0,'2004_1_23','ChangChun','0','0','2022_9_22',0,'q1','q2','q3')");
    query->exec("insert into User values('d','d','123','I am d','head (4).JPG','15999999999',0,'2004_1_23','ChangChun','0','0','2022_9_22',0,'q1','q2','q3')");

    //得到指向数据库的指针
    db = QSqlDatabase::database();                                                                 //获取数据库指针
    //数据库模型视图
    //定制模型
    model = new QSqlQueryModel(loginpage);
    model->setQuery("select * from User");
    model->setHeaderData(0,Qt::Horizontal,"账号");
    model->setHeaderData(1,Qt::Horizontal,"昵称");
    model->setHeaderData(2,Qt::Horizontal,"密码");
    model->setHeaderData(3,Qt::Horizontal,"个性签名");
    model->setHeaderData(4,Qt::Horizontal,"头像");
    model->setHeaderData(5,Qt::Horizontal,"电话号码+86");
    model->setHeaderData(6,Qt::Horizontal,"在线状态");
    model->setHeaderData(7,Qt::Horizontal,"生日");
    model->setHeaderData(8,Qt::Horizontal,"所在地");
    model->setHeaderData(9,Qt::Horizontal,"T龄");
    model->setHeaderData(10,Qt::Horizontal,"VIP级别");
    model->setHeaderData(11,Qt::Horizontal,"注册日期");
    model->setHeaderData(12,Qt::Horizontal,"封禁状态");
    model->setHeaderData(13,Qt::Horizontal,"密保1");
    model->setHeaderData(14,Qt::Horizontal,"密保2");
    model->setHeaderData(15,Qt::Horizontal,"密保3");
    //设置视图




    QSqlQuery readQuery;
    readQuery.exec("select * from User");

    QSqlQuery updateQuery;

    while(readQuery.next()){
        QString signUpDateString = readQuery.value(11).toString();
        QStringList parts = signUpDateString.split('_');
        int year = parts[0].toInt();
        int month = parts[1].toInt();
        int day = parts[2].toInt();
        QDate signUpDate(year, month, day);

        QDate currentDate = QDate::currentDate();
        int days = signUpDate.daysTo(currentDate); // 这就是T龄

        // 将T龄转换为字符串
        QString daysString = QString::number(days);

        updateQuery.prepare("UPDATE User SET Tagt = :days WHERE account = :account");
        updateQuery.bindValue(":days", daysString);
        updateQuery.bindValue(":account", readQuery.value(0).toString());

        if(!updateQuery.exec()) {
            // 在这里处理错误
            qDebug() << "Update failed: " << updateQuery.lastError();
        }
        qDebug() << readQuery.value(0).toString()<< daysString;
    }

    model->setQuery("select * from User");


    {
        QSqlQuery readQuery;
        readQuery.exec("select * from User");
        while(readQuery.next()){
        createFile(readQuery.value(0).toString());
        }
    }


    loginpage->addTable(model);
    loginpage->addTable_s(model);

    QStringList tableNames = db.tables();
        qDebug() << "All tables in the database:";
        for (const QString &name : tableNames) {
            qDebug() << name;
        }
}

int UserList::CheckUser(QString account, QString password){
    query->exec("select * from User");
    while(query->next()){
        QString RealAccount = query->value(0).toString();
        QString RealPassword = query->value(2).toString();
        if(account == RealAccount && password == RealPassword){
            //不能重复登陆
            if(query->value(6).toString() == "1"){
                return 2;
            }
            //更新模型视图
            model->setQuery("update user set state = 1 where account = '" + account + "'");
            model->setQuery("select * from User");
            return 1;
        }
    }
    return 0;                                                                                      //用户名或密码错误 返回0
}
//QString string = "register|" + nameTmp+"|"+password1Tmp+"|"+phoneNumberTmp+"|"+signTemp+"|"+birthdayDate+"|"+localPlaceTemp+"|"+passwordq1Temp+"|"+passwordq2Temp+"|"+passwordq3Temp+"|"+headImageTemp;
/* query->exec("create table User("                                                               //构建用户数据表格
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
QString UserList::addUser(QString message){                                                        //用于用户的注册操作
    QStringList msg = message.split("|");                                                          //对信息进行分隔
    //临时信息
    QString accountTemp;
    //随机生成数据库中没有的10位数并返回
    bool uniqueFlag = true;
    QString exitAccount;
    QSqlQuery query(db);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));                                             //随机数种子
    while(true){
        //随机数生成
        for(int i = 0; i < 10; i++){
            int rand = qrand() % 10;                                                               //产生10以内的随机数
            QString s = QString::number(rand, 10);                                                 //转化为10进制，再转化为字符
            accountTemp += s;
        }
        uniqueFlag = true;
        query.exec("select * from User");
        while(query.next()){
            exitAccount = query.value(0).toString();
            if(accountTemp == exitAccount){
                uniqueFlag = false;
                break;
            }
        }
        //独一无二的账号跳出
        if(uniqueFlag == true)
            break;
    }


    //数据库插入
    //注意英文字符要加''单引号，数字可以不加
    QString temp0;
    temp0="0";

    int year;
    int month;
    int day;
    QString syear;
    QString smonth;
    QString sday;
    getCurrentTime(&year, &month, &day);
    syear =QString::number(year,10);
    smonth =QString::number(month,10);
    sday =QString::number(day,10);
    QString date=syear+"_"+smonth+"_"+sday;


    query.prepare("insert into User values(:q1,:q2,:q3,:q4,:q5,:q6,0,:q7,:q8,'0','0',:q9,0,:q10,:q11,:q12)");
    query.bindValue(":q1", accountTemp);
    query.bindValue(":q2", msg[1]);
    query.bindValue(":q3", msg[2]);
    query.bindValue(":q4", msg[4]);
    query.bindValue(":q5", msg[10]);
    query.bindValue(":q6", msg[3]);
    query.bindValue(":q7", msg[5]);
    query.bindValue(":q8", msg[6]);
    query.bindValue(":q9", date);
    query.bindValue(":q10", msg[7]);
    query.bindValue(":q11", msg[8]);
    query.bindValue(":q12", msg[9]);
    query.exec();
    model->setQuery("select * from User");
    createFile(accountTemp);
    return accountTemp;                                                                            //返回生成的账号
}

void UserList::initDB(){
    query->exec("update user set state = 0");                                                      //服务器初始化 设置所有用户在线状态为0 用于崩溃后的调试清零工作
    model->setQuery("select * from User");
}

UserList::~UserList()
{
    delete model;
    delete query;
}

void UserList::tageUpdate()
{
    QSqlQuery readQuery;
    readQuery.exec("select * from User");

    QSqlQuery updateQuery;

    while(readQuery.next()){
        QString signUpDateString = readQuery.value(11).toString();
        QStringList parts = signUpDateString.split('_');
        int year = parts[0].toInt();
        int month = parts[1].toInt();
        int day = parts[2].toInt();
        QDate signUpDate(year, month, day);

        QDate currentDate = QDate::currentDate();
        int days = signUpDate.daysTo(currentDate); // 这就是T龄

        // 将T龄转换为字符串
        QString daysString = QString::number(days);

        updateQuery.prepare("UPDATE User SET Tagt = :days WHERE account = :account");
        updateQuery.bindValue(":days", daysString);
        updateQuery.bindValue(":account", readQuery.value(0).toString());

        if(!updateQuery.exec()) {
            // 在这里处理错误
            qDebug() << "Update failed: " << updateQuery.lastError();
        }
        qDebug() << readQuery.value(0).toString()<< daysString;
    }
     model->setQuery("select * from User");
}
