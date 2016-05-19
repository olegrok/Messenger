#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "profile.h"
#include "authwindow.h"
#include "addfriend.h"
#include "options.h"
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include "database.h"
#include <QDateTime>
#include <QVector>
#include <QMessageBox>
#include <QListWidgetItem>
#include "structsforrequests.h"
#include <QScrollBar>
#include <QAbstractSlider>
#include <QDesktopServices>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addContact(const contInfo);
    void setLogin(const QString);
    void setUid(const int);

private slots:
    void on_SendButton_clicked();
    void on_AddContactButton_clicked();
    void on_DeleteContactButton_clicked();
    void windowInit(QString _login);
    void on_OptionButton_clicked();
    void on_ContactsList_itemClicked(QListWidgetItem *item);
    void unlogin(QString status = 0);
    void unloginProfile();
    void updateWindow();
    int showNotification(QString);

    void on_actionAbout_program_triggered();

    void on_actionAbout_QT_triggered();

private:
    QString login;
    Ui::MainWindow *ui;
    AddFriend addfriend;
    authwindow auth;
    Profile account;
    Options opt;
    void styleInit();
    QVector<QListWidgetItem> contacts;
    QScrollBar VerticalScroll;

};

#endif // MAINWINDOW_H
