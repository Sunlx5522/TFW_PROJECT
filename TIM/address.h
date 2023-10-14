#ifndef ADDRESS_H //该头文件没有什么用处 字符串的声明在源文件里
#define ADDRESS_H //该头文件与源文件的独立性较强
#include <QString>
class tfwAddress
{
public:
    QString internetRemoteAddress="http://www.baidu.com"; //检测互联网在线状态的网址（www,baidu.com）
    QString serveRemoteAddress="61.139.65.181"; //远端服务器地址（成都电信 由于我选择内网穿透 该地址是我的本地映射的远端地址 我的5555 6666 7777 8888 都映射在该地址对应的服务器上）
    int port5555 =51269; //服务器5555端口 在穿透服务器映射端口为51269
    int port6666 =15698; //服务器6666端口 在穿透服务器映射端口为15698
    int port7777 =55418; //服务器7777端口 在穿透服务器映射端口为55418
    int port8888 =62240; //服务器8888端口 在穿透服务器映射端口为62240

};
#endif // ADDRESS_H
