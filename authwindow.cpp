#include <QLineEdit>
#include <QDebug>
#include "authwindow.h"
#include "ui_authwindow.h"

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
    accRequest auth;
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();

    accReply reply = account->accountRequest(auth, "authorisation");
    switch(reply.statusCode)
    {
        case 200: ui->StatusLine->setText("Successeful autorisation!");
            emit showMainWindow(auth.login);
            this->hide(); break;
        case 404: ui->StatusLine->setText("Not Found!");break;
        default: ui->StatusLine->setText(reply.replyContent); break;
    }
    //Profile::
}

void authwindow::on_CloseButton_clicked()
{
    qApp->closeAllWindows();
    //emit closeMainWindow();
    //this->close();
}

void authwindow::on_RegisterButton_clicked()
{
    accRequest auth;
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();

    accReply reply = account->accountRequest(auth, "registration");

    switch(reply.statusCode)
    {
        case 200: ui->StatusLine->setText("Successeful registration!");
        emit showMainWindow(auth.login);
        this->close();break;
        default: ui->StatusLine->setText(reply.replyContent); break;
    }

}

void authwindow::setUpProfile(Profile* acc){
    account = acc;
}

void authwindow::setStatus(QString status){
    ui->StatusLine->setText(status);
}
