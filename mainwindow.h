#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"
#include "profile.h"
#include "authwindow.h"
#include "addfriend.h"
#include "options.h"

class AddFriend;
class authwindow;
class Profile;

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
    void setLogin(QString);
    void setUid(int);


private slots:
    void on_SendButton_clicked();
    void on_AddContactButton_clicked();
    void on_ContactsList_itemActivated(QListWidgetItem* item);
    void on_DeleteContactButton_clicked();
    void databaseInit(QString _login);

    void on_pushButton_4_clicked();

//    void on_ContactsList_clicked(const QModelIndex &index);

    void on_ContactsList_itemClicked(QListWidgetItem *item);

private:
    QString login;
    Ui::MainWindow *ui;
    AddFriend addfriend;
    authwindow auth;
    Profile account;
    Options opt;
    void styleInit();

};

#endif // MAINWINDOW_H
