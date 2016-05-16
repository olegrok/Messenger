#include "authwindow.h"
#include "ui_authwindow.h"

authwindow::authwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authwindow)
{
    ui->setupUi(this);
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
            ui->Password->clear();
            ui->Login->clear();
            emit showMainWindow(auth.login);
            this->close(); break;
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
        this->close();
        break;
        default: ui->StatusLine->setText(reply.replyContent); break;
    }

}

void authwindow::setUpProfile(Profile* acc){
    account = acc;
}

void authwindow::setStatus(QString status){
    ui->StatusLine->setText(status);
}
