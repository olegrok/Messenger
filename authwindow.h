#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include <QInputDialog>
#include "ui_authwindow.h"
#include "profile.h"
#include "structsforrequests.h"

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

public slots:
    void on_EnterButton_clicked();
signals:
    void showMainWindow(QString login);
    void closeMainWindow();
private slots:
    void on_CloseButton_clicked();
    void on_RegisterButton_clicked();
    void changeEvent(QEvent* event);

private:
    Ui::authwindow *ui;
    Profile* account;
    void buttonMenu(QString property);
};

#endif // AUTHWINDOW_H
