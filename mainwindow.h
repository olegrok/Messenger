#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include <QDateTime>
#include <QVector>
#include <QMessageBox>
#include <QScrollBar>
#include <QDesktopServices>
#include <QEvent>
#include "profile.h"
#include "authwindow.h"
#include "addfriend.h"
#include "options.h"
#include "structsforrequests.h"
#include "database.h"
#include "monitor.h"
#include <cpprest/http_msg.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addContact();
    void setLogin(const QString);
    void setUid(const int);

private slots:
    void on_SendButton_clicked();
    void on_AddContactButton_clicked();
    int on_DeleteContactButton_clicked();
    void windowInit(QString _login);
    void on_OptionButton_clicked();
    void on_ContactsList_itemClicked(QListWidgetItem *item);
    void logout(QString status = 0);
    void logoutProfile();
    void updateWindow();
    int  additionEvent(QString);
    int  deniedEvent(QString&);
    void on_actionAbout_program_triggered();
    void on_actionAbout_QT_triggered();
    void changeEvent(QEvent* event);
    void findContact(const QString &);
    void changeMsgLineEvent(const QString&);
    void on_findMsgButton_clicked();

    void on_sortContacts_clicked();

private:
    void styleInit();
    void loadContacts(QString text = 0);
    bool loadMsg(QString text = 0);

    QString login;
    Ui::MainWindow *ui;
    AddFriend addfriend;
    authwindow auth;
    Profile account;
    Options opt;
    QVector<QListWidgetItem*> contacts;
    QScrollBar VerticalScroll;

};

#endif // MAINWINDOW_H
