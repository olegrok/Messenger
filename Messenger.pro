#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:33:30
#
#-------------------------------------------------

QT       += core gui sql
CONFIG   += c++1z warn_on rpath rpath-link rdynamic

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app
LIBS += -lcpprest -lboost_system -l:libssl.so -l:libcrypto.so
#CONFIG += -I../Boost/boost_1_61_0 -lboost_system
#CONFIG += -I../Casablanca/casablanca -lcpprest

SOURCES += main.cpp\
        mainwindow.cpp \
    authwindow.cpp \
    addfriend.cpp \
    client.cpp \
    database.cpp \
    profile.cpp \
    options.cpp \
    jsonprotocol.cpp \
    monitor.cpp \
    httpsettings.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    addfriend.h \
    client.h \
    structsforrequests.h \
    database.h \
    profile.h \
    options.h \
    jsonprotocol.h \
    monitor.h \
    httpsettings.h

FORMS    += mainwindow.ui \
    authwindow.ui \
    addfriend.ui \
    options.ui \
    httpsettings.ui

TRANSLATIONS    += ./langs/ru.ts \
                   ./langs/ua.ts

RESOURCES += \
    resources.qrc

