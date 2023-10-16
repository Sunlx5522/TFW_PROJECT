      #ifndef USERLIST_H
#define USERLIST_H

#include<QString>
#include<QList>
#include <QDebug>
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
    QString AntiMd5password;
private:
};


class MyFriend
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
    bool operator==(const MyFriend& other) const
        {
            return account == other.account &&
                   name == other.name &&
                   password == other.password &&
                   sign == other.sign &&
                   headImage == other.headImage &&
                   phoneNumber == other.phoneNumber &&
                   birthDay == other.birthDay &&
                   localPlace == other.localPlace &&
                   Tagt == other.Tagt &&
                   VIP_Level == other.VIP_Level;
        }
    MyFriend& operator=(const MyFriend& other)
       {
           // 自赋值检查
           if(this != &other)
           {
               account = other.account;
               name = other.name;
               password = other.password;
               sign = other.sign;
               headImage = other.headImage;
               phoneNumber = other.phoneNumber;
               birthDay = other.birthDay;
               localPlace = other.localPlace;
               Tagt = other.Tagt;
               VIP_Level = other.VIP_Level;
           }
           return *this;
       }

private:
};

class MyFriends
{
public:
    void addFriend(const MyFriend& newFriend) {
        friendsList.append(newFriend);
    }
    MyFriend* findFriendByAccount(const QString& searchAccount) {
            for (MyFriend& friendObj : friendsList) {
                if (friendObj.account == searchAccount) {
                    return &friendObj;
                }
            }
            return nullptr;  // 返回nullptr表示未找到对应的MyFriend对象
        }
    // 其他你可能需要的成员函数，例如removeFriend, getFriend, etc.

        void friendDebug() const {
            for (const MyFriend& friendObj : friendsList) {
                qDebug() << "Account: " << friendObj.account;
                qDebug() << "Name: " << friendObj.name;
                qDebug() << "Password: " << friendObj.password;
                qDebug() << "Sign: " << friendObj.sign;
                qDebug() << "Head Image: " << friendObj.headImage;
                qDebug() << "Phone Number: " << friendObj.phoneNumber;
                qDebug() << "Birthday: " << friendObj.birthDay;
                qDebug() << "Local Place: " << friendObj.localPlace;
                qDebug() << "Tag: " << friendObj.Tagt;
                qDebug() << "VIP Level: " << friendObj.VIP_Level;
                qDebug() << "-------------------------";
            }
        }

        void removeFriendByAccount(const QString& removeAccount) {
                for (int i = 0; i < friendsList.size(); ++i) {
                    if (friendsList[i].account == removeAccount) {
                        friendsList.removeAt(i);
                        return;
                    }
                }
            }
        void removeAllFriendByAccount() {

                for (int i = 0; i < friendsList.size(); i++) {
                        friendsList.removeAt(0);
                }
                friendsList=QList<MyFriend>();

            }
     QList<MyFriend> friendsList;

private:
};



class MyRequsest
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
    bool operator==(const MyRequsest& other) const
        {
            return account == other.account &&
                   name == other.name &&
                   password == other.password &&
                   sign == other.sign &&
                   headImage == other.headImage &&
                   phoneNumber == other.phoneNumber &&
                   birthDay == other.birthDay &&
                   localPlace == other.localPlace &&
                   Tagt == other.Tagt &&
                   VIP_Level == other.VIP_Level;
        }
    MyRequsest& operator=(const MyRequsest& other)
       {
           // 自赋值检查
           if(this != &other)
           {
               account = other.account;
               name = other.name;
               password = other.password;
               sign = other.sign;
               headImage = other.headImage;
               phoneNumber = other.phoneNumber;
               birthDay = other.birthDay;
               localPlace = other.localPlace;
               Tagt = other.Tagt;
               VIP_Level = other.VIP_Level;
           }
           return *this;
       }

private:
};

class MyRequsests
{
public:

    void addRequest(const MyRequsest& newRequest) {
        requestsList.append(newRequest);
    }
    MyRequsest* findRequestByAccount(const QString& searchAccount) {
            for (MyRequsest& requestObj : requestsList) {
                if (requestObj.account == searchAccount) {
                    return &requestObj;
                }
            }
            return nullptr;  // 返回nullptr表示未找到对应的MyFriend对象
        }
    // 其他你可能需要的成员函数，例如removeFriend, getFriend, etc.

        void RequestDebug() const {
            for (const MyRequsest& requestObj : requestsList) {
                qDebug() << "Account: " << requestObj.account;
                qDebug() << "Name: " << requestObj.name;
                qDebug() << "Password: " << requestObj.password;
                qDebug() << "Sign: " << requestObj.sign;
                qDebug() << "Head Image: " << requestObj.headImage;
                qDebug() << "Phone Number: " << requestObj.phoneNumber;
                qDebug() << "Birthday: " << requestObj.birthDay;
                qDebug() << "Local Place: " << requestObj.localPlace;
                qDebug() << "Tag: " << requestObj.Tagt;
                qDebug() << "VIP Level: " << requestObj.VIP_Level;
                qDebug() << "-------------------------";
            }
        }

        void removeRequestByAccount(const QString& removeAccount) {
                for (int i = 0; i < requestsList.size(); ++i) {
                    if (requestsList[i].account == removeAccount) {
                        requestsList.removeAt(i);
                        return;
                    }
                }
            }
        void removeAllRequestByAccount() {


                for (int i = 0; i < requestsList.size(); i++) {
                        requestsList.removeAt(0);
                }
                requestsList=QList<MyRequsest>();
            }
     QList<MyRequsest> requestsList;

private:
};




class MyMessage
{
public:
    QString time;
    QString user1;
    QString user2;
    QString message;
    bool operator==(const MyMessage& other) const
        {
            return time == other.time &&
                   user1 == other.user1 &&
                    user2 == other.user2 &&
                   message == other.message;
        }
    MyMessage& operator=(const MyMessage& other)
       {
           // 自赋值检查
           if(this != &other)
           {
               time = other.time;
               user1 = other.user1;
               user2 = other.user2;
               message = other.message;
           }
           return *this;
       }
private:
};


class MyMessages
{
public:
    void addMessage(const MyMessage& newMessage) {
        messagesList.append(newMessage);
    }
    MyMessage* findMessageByAccount(const QString& searchTime) {
            for (MyMessage& messageObj : messagesList) {
                if (messageObj.time == searchTime) {
                    return &messageObj;
                }
            }
            return nullptr;  // 返回nullptr表示未找到对应的MyFriend对象
        }
    // 其他你可能需要的成员函数，例如removeFriend, getFriend, etc.

        void removeMessageByTime(const QString& removeTime) {
                for (int i = 0; i < messagesList.size(); i++) {
                    if (messagesList[i].time == removeTime) {
                        messagesList.removeAt(i);
                        return;
                    }
                }
            }
        void removeAllMessageByAccount() {
                for (int i = 0; i < messagesList.size(); i++) {
                        messagesList.removeAt(0);
                }
                messagesList=QList<MyMessage>();

            }
     QList<MyMessage> messagesList;
private:
};

class MyChat{
public:
    MyChat()
    {

    }
    MyChat(MyFriend& t1)
    {
        Friend=t1;
    }
    MyFriend Friend;
    MyMessages messages;
    bool operator==(const MyChat& other) const
        {
            return Friend == other.Friend
                  ;
        }
    MyChat& operator=(const MyChat& other)
       {
           // 自赋值检查
           if(this != &other)
           {
               Friend = other.Friend;
           }
           return *this;
       }
private:
};

class MyChats
{
public:
    void addchat(const MyChat& newChat) {
        chatList.append(newChat);
    }
    MyChat* findChatByAccount(const QString& searchAccount) {
            for (MyChat& chatObj : chatList) {
                if (chatObj.Friend.account == searchAccount) {
                    return &chatObj;
                }
            }
            return nullptr;  // 返回nullptr表示未找到对应的MyFriend对象
        }
    // 其他你可能需要的成员函数，例如removeFriend, getFriend, etc.


        void removeChatByAccount(const QString& removeAccount) {
                for (int i = 0; i < chatList.size(); ++i) {
                    if (chatList[i].Friend.account == removeAccount) {
                        chatList.removeAt(i);
                        return;
                    }
                }
            }
        void removeAllChatByAccount() {

                for (int i = 0; i < chatList.size(); i++) {
                        chatList.removeAt(0);
                }
                chatList=QList<MyChat>();

            }
     QList<MyChat> chatList;
private:
};





#endif // USERLIST_H
