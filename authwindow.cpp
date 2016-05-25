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
    buttonMenu(account_action::authorization);
}

void authwindow::on_CloseButton_clicked()
{
    qApp->closeAllWindows();
}

void authwindow::on_RegisterButton_clicked()
{
    buttonMenu(account_action::registration);
}

void authwindow::setUpProfile(Profile* acc){
    account = acc;
}

void authwindow::setStatus(QString status){
    ui->StatusLine->setText(status);
}

void authwindow::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }
}

void authwindow::buttonMenu(account_action property){
    accRequest auth;
    auth.login = ui->Login->text();
    auth.password = ui->Password->text();
    account->setUrl(Url);
    accReply reply = account->accountRequest(auth, property);

    switch(reply.statusCode)
    {
        case status_codes::OK:
        case status_codes::Created:
        ui->Password->clear();
        ui->Login->clear();
        ui->Login->setFocus();
        emit showMainWindow(auth.login);
        this->close();
        break;
        case status_codes::NotFound: ui->StatusLine->setText(tr("Not Found!"));break;
        default: ui->StatusLine->setText(reply.content); break;
    }
}

void authwindow::on_connectionSettingsButton_clicked()
{
    httpSettings win(Url);
    win.setModal(true);
    qDebug() << win.exec();
    qDebug() << win.getURL();
    if(win.result())
        Url = win.getURL();
}
