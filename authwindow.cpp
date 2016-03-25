#include <QLineEdit>
#include <QDebug>
#include "authwindow.h"
#include "ui_authwindow.h"
#include "client.h"
#include "mainwindow.h"
#include "structsforrequests.h"

extern accountRequest auth;

authwindow::authwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authwindow)
{
    ui->setupUi(this);
    //connect(ui->EnterButton, SIGNAL(clicked()), this, SLOT(on_EnterButton_clicked()), Qt::UniqueConnection);
    //connect(ui->EnterButton, &Client::changeAuthStatus, this, SLOT(changeAuthStatus), Qt::UniqueConnection);
}

authwindow::~authwindow()
{
    delete ui;
}

void authwindow::on_EnterButton_clicked()
{
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();
    accountRequest arg = {auth.login, auth.password};
    Reply reply = Client::accountRequest(arg, "account_authorisation");
    switch(reply.statusCode)
    {
        case 200: ui->StatusLine->setText("Successeful autorisation!");
            emit showMainWindow(auth.login);
            this->close(); break;
        case 404: ui->StatusLine->setText("Not Found!");break;
        default: ui->StatusLine->setText(reply.replyContent); break;
    }
}

void authwindow::on_CloseButton_clicked()
{
    emit closeMainWindow();
}

void authwindow::on_RegisterButton_clicked()
{
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();

    accountRequest arg = {auth.login, auth.password};
    Reply reply = Client::accountRequest(arg, "account_registration");

    switch(reply.statusCode)
    {
        case 200: ui->StatusLine->setText("Successeful registration!");
        emit showMainWindow(auth.login);
        this->close();break;
        default: ui->StatusLine->setText(reply.replyContent); break;
    }

}



