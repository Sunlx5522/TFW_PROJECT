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
#include <QSqlQueryModel>
#include <QDebug>
#include <QTime>


UserList::UserList()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("UserList.db");                                                             //如果文件中已有则不需要重复添加
    //打开
    if(!db.open()){
      ww->shouError();                                                                             //打不开 输出错误命令（此指令一般情况下不会执行）
     }
    //指定连接
    query = new QSqlQuery(db);                                                                     //操作指针链接
    query->exec("create table User("                                                               //构建用户数据表格
                "account varchar(25) primary key,"                                                 //用户账号
                "name varchar(25) not null,"                                                       //用户昵称
                "password varchar(20) not null,"                                                   //用户密码
                "sign varchar(25),"                                                                //个性签名
                "headImage varchar(10),"                                                           //头像图片名称
                "state bit default 0,"
                "birthDay varchar(25),"
                "localPlace varchar(25),"
                "Tagt varchar(25),"
                "VIP_Level varchar(25))");                                                           //用户状态
                                                                                                   //其余特定数据待添加（用户和群组列表最重要）
    query->exec("insert into User values('a','a','123','I am a','head1.png',0,'2004_1_23','ChangChun','0','0')");                  //26个原始用户，便于调试
    query->exec("insert into User values('b','b','123','I am b','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('c','c','123','I am c','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('d','d','123','I am d','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('e','e','123','I am e','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('f','f','123','I am f','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('g','g','123','I am g','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('h','h','123','I am h','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('i','i','123','I am i','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('j','j','123','I am j','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('k','k','123','I am k','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('l','l','123','I am l','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('m','m','123','I am m','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('n','n','123','I am n','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('o','o','123','I am o','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('p','p','123','I am p','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('q','q','123','I am q','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('r','r','123','I am r','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('s','s','123','I am s','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('t','t','123','I am t','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('u','u','123','I am u','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('v','v','123','I am v','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('w','w','123','I am w','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('x','x','123','I am x','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('y','y','123','I am y','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('z','z','123','I am z','head1.png',0,'2004_1_23','ChangChun','0','0')");
    query->exec("insert into User values('3096961672','孙立鑫','55220329','心似烟火','head1.png',0,'2004_1_23','ChangChun','0','10')");
    //得到指向数据库的指针
    db = QSqlDatabase::database();                                                                 //获取数据库指针
    //数据库模型视图
    //定制模型
    model = new QSqlQueryModel(ww);
    model->setQuery("select * from User");
    model->setHeaderData(0,Qt::Horizontal,"账号");
    model->setHeaderData(1,Qt::Horizontal,"昵称");
    model->setHeaderData(2,Qt::Horizontal,"密码");
    model->setHeaderData(3,Qt::Horizontal,"个性签名");
    model->setHeaderData(4,Qt::Horizontal,"头像");
    model->setHeaderData(5,Qt::Horizontal,"在线状态");
    model->setHeaderData(6,Qt::Horizontal,"生日");
    model->setHeaderData(8,Qt::Horizontal,"所在地");
    model->setHeaderData(7,Qt::Horizontal,"T龄");
    model->setHeaderData(9,Qt::Horizontal,"VIP级别");
    //设置视图
    ww->addTable(model);
}

int UserList::CheckUser(QString account, QString password){
    query->exec("select * from User");
    while(query->next()){
        QString RealAccount = query->value(0).toString();
        QString RealPassword = query->value(2).toString();
        if(account == RealAccount && password == RealPassword){
            //不能重复登陆
            if(query->value(5).toString() == "1"){
                return 2;
            }
            //更新模型视图
            model->setQuery("update user set state = 1 where account = '" + account + "'");
            model->setQuery("select * from User");
            ww->addTable(model);                                                                   //刷新屏幕数据
            return 1;
        }
    }
    return 0;                                                                                      //用户名或密码错误 返回0
}

QString UserList::addUser(QString message){                                                        //用于用户的注册操作
    QStringList msg = message.split("|");                                                          //对信息进行分隔
    qDebug() << "总长度: " << msg.length();
    //临时信息
    QString accountTemp;
    QString nameTemp;
    QString passwordTemp;
    QString signTemp;
    QString headTemp;
    QString s;
    nameTemp = msg[1];
    passwordTemp = msg[2];
    signTemp = msg[3];
    headTemp = msg[4];
    //随机生成数据库中没有的五位数并返回
    bool uniqueFlag = true;
    QString exitAccount;
    QSqlQuery query(db);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));                                             //随机数种子
    while(true){
        //随机数生成
        for(int i = 0; i < 5; i++){
            int rand = qrand() % 10;                                                               //产生10以内的随机数
            QString s = QString::number(rand, 10);                                                 //转化为10进制，再转化为字符
            accountTemp += s;
            qDebug() << i <<":accountTemp=" << accountTemp;
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
    qDebug() << "accountTemp:"+accountTemp;
    qDebug() << "nameTemp:"+nameTemp;
    qDebug() << "passwordTemp:"+passwordTemp;
    qDebug() << "signTemp:"+signTemp;
    qDebug() << "headTemp:"+headTemp;

    s = "insert into User values("+
            accountTemp+"," +
            nameTemp+","+
            passwordTemp+","+
            signTemp+",'"+
            headTemp+"',"+
            "0)";
    qDebug() << s;
    //数据库插入
    //注意英文字符要加''单引号，数字可以不加
    model->setQuery("insert into User values('"+
                    accountTemp+"','" +
                    nameTemp+"','"+
                    passwordTemp+"','"+
                    signTemp+"','"+
                    headTemp+"',"+
                    "0)");
    model->setQuery("select * from User");
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
