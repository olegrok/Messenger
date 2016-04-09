#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"
#include "client.h"
#include "profile.h"
#include "authwindow.h"
#include "addfriend.h"

class AddFriend;
class authwindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addContact(contInfo);
    static Client client;
    accRequest accData;
    void setLogin(QString);
    void setUid(int);


private slots:
    void on_SendButton_clicked();
    void on_AddContactButton_clicked();
    void on_ContactsList_itemActivated(QListWidgetItem* item);
    void on_DeleteContactButton_clicked();
    void databaseInit(QString inLogin);

private:
    QString login;
    Ui::MainWindow *ui;
    AddFriend addfriend;
    authwindow auth;
    Profile account;
    void styleInit();

};

#endif // MAINWINDOW_H
