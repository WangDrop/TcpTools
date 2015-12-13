#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T09:34:29
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpTool
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    mytcpserver.cpp \
    mytcpclient.cpp

HEADERS  += window.h \
    mytcpserver.h \
    mytcpclient.h \
    myhelper.h

FORMS    += window.ui
