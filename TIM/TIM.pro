# qt的gui添加
QT += core gui
# 网络服务添加
QT += core gui network
# 保持与QT4的兼容性
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# QtCreato支持C++11
CONFIG += c++11
# 标记为弃用的Qt功能，以便了解如何将代码从中移植出去
# 您还可以选择仅在特定版本的Qt之前禁用不推荐使用的API
# 如果代码使用了不推荐使用的API，也可能导致代码编译失败，为此，请取消对以下行的注释
# DEFINES+=QT_DISABLE_DEPREATED_BEFORE=0x060000#禁用QT 6.0.0之前弃用的所有API
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \ #源文件
    GetTime.cpp \ #获取系统时间
    MD5.cpp \ #MD5加密
    address.cpp \ #网络地址字符串
    addresssetting.cpp \ #网络地址字符串的设置
    findpassword.cpp \ #找回密码
    heartbeat.cpp \ #心跳 间隔一定的时间执行特定的代码
    initsurface.cpp \ #初始化服务
    main.cpp \ #主函数
    qrcode.cpp \ #二维码
    signUp.cpp \ #注册
    userlist.cpp \ #用户列表（好友列表以及群组列表）
    widget.cpp #登录窗口源文件
HEADERS += \ #头文件
    GetTime.h \ #获取系统时间
    MD5.h \ #MD5加密
    address.h \ #网络地址字符串
    addresssetting.h \ #网络地址字符串的设置
    findpassword.h \ #找回密码
    heartbeat.h \ #心跳 间隔一定的时间执行特定的代码
    initsurface.h \ #初始化服务
    qrcode.h \ #二维码
    signUp.h \ #注册
    userlist.h \ #用户列表（好友列表以及群组列表）
    widget.h #登录窗口源文件
FORMS += \ #ui文件
    addresssetting.ui \ #地址设置ui
    findpassword.ui \ #找回密码ui
    qrcode.ui \ #二维码显示ui
    widget.ui #登录界面ui
# Default rules for deployment.           default规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
RESOURCES += \ #资源文件（注意 资源文件只读不能写）
    SourceFile.qrc
CONFIG += resources_big #允许大文件的编译
LIBS += -L$$PWD/ -lqrencode #引用第三方库  用于显示二维码
INCLUDEPATH += $$PWD/ #允许引用第三方头文件
DISTFILES +=

