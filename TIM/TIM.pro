 #  qt的数据库添加
QT       += sql
#  qt的gui添加
QT       += core gui
#  网络服务添加
QT       += core gui network
#  保持与QT4的兼容性
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#  QtCreato支持C++11
CONFIG += c++11
#  标记为弃用的Qt功能，以便了解如何将代码从中移植出去
#  您还可以选择仅在特定版本的Qt之前禁用不推荐使用的API
#  如果代码使用了不推荐使用的API，也可能导致代码编译失败，为此，请取消对以下行的注释
#  DEFINES+=QT_DISABLE_DEPREATED_BEFORE=0x060000#禁用QT 6.0.0之前弃用的所有API
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    MD5.cpp \
    address.cpp \
    addresssetting.cpp \
    heartbeat.cpp \
    main.cpp \
    userlist.cpp \
    widget.cpp

HEADERS += \
    MD5.h \
    address.h \
    addresssetting.h \
    heartbeat.h \
    userlist.h \
    widget.h

FORMS += \
    addresssetting.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    SourceFile.qrc

 CONFIG += resources_big
