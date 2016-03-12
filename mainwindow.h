#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "mainwindow.h"
#include "client.h"

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
    void addContact(QString);
    static Client client;
    authwindow *auth;

private slots:
    void on_SendButton_clicked();
    void on_AddContactButton_clicked();
    void on_ContactsList_itemActivated(QListWidgetItem *item);
    void on_DeleteContactButton_clicked();

private:
    Ui::MainWindow *ui;
    AddFriend *addfriend;
};

#endif // MAINWINDOW_H
