#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include <QInputDialog>
#include "ui_authwindow.h"
#include "profile.h"
#include "structsforrequests.h"
#include "httpsettings.h"

namespace Ui {
class authwindow;
}

class authwindow : public QDialog
{
    Q_OBJECT

public:
    explicit authwindow(QWidget *parent = 0);
    ~authwindow();
    QString getLogin() const;
    int getUid();
    void setUpProfile(Profile* acc);
    void setStatus(QString status);
signals:
    void showMainWindow(QString login);
    void closeMainWindow();
private slots:
    void on_EnterButton_clicked();
    void on_CloseButton_clicked();
    void on_RegisterButton_clicked();
    void changeEvent(QEvent* event);
    void on_httpEnterButton_clicked();

private:
    Ui::authwindow *ui;
    Profile* account;
    void buttonMenu(QString property);
    QString Url = 0;
};

#endif // AUTHWINDOW_H
