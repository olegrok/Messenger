#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:33:30
#
#-------------------------------------------------

QT       += core gui sql testlib
QT       -= qml network opengl svg multimedia
CONFIG   += c++1z warn_on

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Messenger
TEMPLATE = app
LIBS += -lcpprest -lboost_system -rdynamic
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
    jsonprotocol.cpp \
    monitor.cpp

HEADERS  += mainwindow.h \
    authwindow.h \
    addfriend.h \
    client.h \
    structsforrequests.h \
    database.h \
    profile.h \
    options.h \
    jsonprotocol.h \
    monitor.h

FORMS    += mainwindow.ui \
    authwindow.ui \
    addfriend.ui \
    options.ui

# Include Squish/Qt if a Squish installation prefix was provided to qmake
!isEmpty(SQUISH_PREFIX) {
    message("Including Squish/Qt files")
    android {
        SQUISH_ATTACH_PORT=4711
    }
    include($$SQUISH_PREFIX/qtbuiltinhook.pri)
}

boot2qt {
    target.path = /data/user/qt/$$TARGET
    INSTALLS += target
}
