#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:33:30
#
#-------------------------------------------------

QT       += core gui
#QT       += network
QT       += sql
CONFIG   += console c++14
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app
LIBS += -lcpprest -lboost_system
#LIBS += -L/usr/local/lib/x86_64-linux-gnu -lcpprest
#LIBS += -L/home/oleg/Рабочий\ стол/Track/Project/Casablanca/casablanca/Release/build.release/Binaries -lcpprest
#INCLUDEPATH += -I//home/oleg/Рабочий стол/Track/Project/Casablanca/casablanca/Release/include


SOURCES += main.cpp\
        mainwindow.cpp \
    authwindow.cpp \
    addfriend.cpp \
    client.cpp \
    database.cpp \
    profile.cpp \
    options.cpp \
    jsonprotocol.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    addfriend.h \
    client.h \
    structsforrequests.h \
    database.h \
    profile.h \
    options.h \
    jsonprotocol.h

FORMS    += mainwindow.ui \
    authwindow.ui \
    addfriend.ui \
    options.ui
