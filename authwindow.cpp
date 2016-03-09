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

    if(authwindow::checklogin(login, password)) //it's hard expandable way
    {						                                //better to use some struct
        qDebug() << login << " " << password;   //which holds login and pass
        emit showMainWindow();			            // struct foo { login , pass }
        this->close();
    }
    else
        ui->StatusLine->setText("Wrong password");
}

void authwindow::on_CloseButton_clicked()
{
    emit closeMainWindow();
}
