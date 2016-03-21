#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:33:30
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
CONFIG   += console c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app
LIBS += -L/usr/local/lib/x86_64-linux-gnu -lcpprest
#LIBS += -L/home/oleg/Рабочий\ стол/Track/Project/Casablanca/casablanca/Release/build.release/Binaries -lcpprest
#INCLUDEPATH += -I//home/oleg/Рабочий стол/Track/Project/Casablanca/casablanca/Release/include


SOURCES += main.cpp\
        mainwindow.cpp \
    authwindow.cpp \
    addfriend.cpp \
    client.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    addfriend.h \
    client.h \
    structsforrequests.h \
    database.h

FORMS    += mainwindow.ui \
    authwindow.ui \
    addfriend.ui
