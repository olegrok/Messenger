#include "mainwindow.h"
#include "authwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    //authwindow auth;
    //auth.show();

    return a.exec();
}
