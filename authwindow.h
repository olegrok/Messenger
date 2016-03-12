#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QDebug>
#include "ui_authwindow.h"
#include "client.h"

namespace Ui {
class authwindow;
}

class authwindow : public QDialog
{
    Q_OBJECT

public:
    explicit authwindow(QWidget *parent = 0);
    ~authwindow();

public slots:
    void on_EnterButton_clicked();
signals:
    void showMainWindow();
    void closeMainWindow();
private slots:
    void on_CloseButton_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::authwindow *ui;
    bool checklogin(Auth auth);
};

#endif // AUTHWINDOW_H
