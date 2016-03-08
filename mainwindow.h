#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "authwindow.h"
#include "addfriend.h"


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

private slots:
    void on_SendButton_clicked();
    void on_AddContactButton_clicked();

private:
    Ui::MainWindow *ui;
    authwindow *auth;
    AddFriend *addfriend;
};

#endif // MAINWINDOW_H
