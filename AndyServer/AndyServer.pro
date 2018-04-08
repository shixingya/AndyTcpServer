#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T11:45:11
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=precompile_header
PRECOMPILED_HEADER=preheader.h
TARGET = AndyServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG   += C++11
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    AndySender.cpp \
    AndyReceiver.cpp \
    TaskManager.cpp \
    TaskRunner.cpp \
    QProgressIndicator/AndyProgressBar.cpp \
    QProgressIndicator/GSProgressBar.cpp \
    tcpserver.cpp \
    tcpsocket.cpp \
    threadhandle.cpp

HEADERS += \
        mainwindow.h \
    AndySender.h \
    preheader.h \
    AndyReceiver.h \
    TaskManager.h \
    TaskRunner.h \
    QProgressIndicator/AndyProgressBar.h \
    QProgressIndicator/GSProgressBar.h \
    tcpserver.h \
    tcpsocket.h \
    threadhandle.h

FORMS += \
        mainwindow.ui \
    AndySender.ui \
    AndyReceiver.ui \
    QProgressIndicator/AndyProgressBar.ui
unix:include($$PWD/eventdispatcher_libev/eventdispatcher_libev.pri)
