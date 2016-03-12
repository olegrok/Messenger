#include <QLineEdit>
#include <QDebug>
#include "authwindow.h"
#include "ui_authwindow.h"
#include "client.h"
#include "mainwindow.h"

extern Auth auth;

authwindow::authwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authwindow)
{
    ui->setupUi(this);
    connect(ui->EnterButton, SIGNAL(clicked()), this, SLOT(on_EnterButton_clicked()), Qt::UniqueConnection);
}

authwindow::~authwindow()
{
    delete ui;
}

bool authwindow::checklogin(Auth auth)
{
    Request arg = {auth.login, auth.password, "account", "account_autorisation"};
    Client().request(arg);

    return true;
}

void authwindow::on_EnterButton_clicked()
{
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();
    if(authwindow::checklogin(auth))
    {
        qDebug() << auth.login << " " << auth.password;
        emit showMainWindow();
        this->close();
    }
    else
        ui->StatusLine->setText("Wrong password");
}

void authwindow::on_CloseButton_clicked()
{
    emit closeMainWindow();
}

void authwindow::on_RegisterButton_clicked()
{
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();

    Request arg = {auth.login, auth.password, "account", "account_registration"};
    Client().request(arg);
}
