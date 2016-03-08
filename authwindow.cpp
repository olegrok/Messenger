#include <QLineEdit>
#include <QDebug>
#include "authwindow.h"
#include "ui_authwindow.h"
#include "mainwindow.h"

authwindow::authwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authwindow)
{
    ui->setupUi(this);
    ui->Login->setPlaceholderText("Login");
    ui->Password->setPlaceholderText("Password");
    connect(ui->EnterButton, SIGNAL(clicked()), this, SLOT(on_EnterButton_clicked()), Qt::UniqueConnection);
}

authwindow::~authwindow()
{
    delete ui;
}

bool authwindow::checklogin(QString login, QString password)
{
    //todo
    return true;
}

void authwindow::on_EnterButton_clicked()
{
    QString login = ui->Login->text();
    QString password = ui->Password->text();

    if(authwindow::checklogin(login, password))
    {
        qDebug() << login << " " << password;
        emit showMainWindow();
        this->close();
    }
    else
        ui->StatusLine->setText("Wrong password");
}
