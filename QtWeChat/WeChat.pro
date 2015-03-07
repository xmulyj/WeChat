#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T22:32:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeChat
TEMPLATE = app



INCLUDEPATH += /usr/include/enet ../proto
LIBS += -lprotobuf -lenet -llog4cplus ../proto/libproto.a


SOURCES += main.cpp\
           wechatmaindialog.cpp \
           logindialog.cpp \
           WeChatClient.cpp \
           regdialog.cpp

HEADERS  += wechatmaindialog.h \
    logindialog.h \
    WeChatClient.h \
    regdialog.h

FORMS    += wechatmaindialog.ui \
    logindialog.ui \
    regdialog.ui
