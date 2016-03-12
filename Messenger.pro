#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:33:30
#
#-------------------------------------------------

QT       += core gui
QT       += network
CONFIG   += console c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app
LIBS += -L/usr/local/lib/x86_64-linux-gnu: -lcpprest

SOURCES += main.cpp\
        mainwindow.cpp \
    authwindow.cpp \
    addfriend.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    addfriend.h \
    client.h

FORMS    += mainwindow.ui \
    authwindow.ui \
    addfriend.ui
