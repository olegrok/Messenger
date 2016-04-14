#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addfriend.h"
#include "authwindow.h"
#include "database.h"
#include "profile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QDesktopWidget().availableGeometry().width()/2 - this->width()/2,
                      QDesktopWidget().availableGeometry().height()/2 - this->width()/2,
                      this->width(), this->height());
    auth.show();

    connect(&auth, &authwindow::showMainWindow, this, &MainWindow::databaseInit, Qt::UniqueConnection);
    //connect(&auth, &authwindow::closeMainWindow, this, &MainWindow::close, Qt::UniqueConnection);
    connect(&addfriend, &AddFriend::sendContact, this, &MainWindow::addContact, Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    auth.close();
    addfriend.close();
    DataBase::close();
    delete ui;
    qApp->closeAllWindows();
}

void MainWindow::on_SendButton_clicked()
{
    QString msg = ui->MessageWindow->toPlainText();
    ui->MessageWindow->clear();
    if(!msg.isEmpty())
    ui->ChatWindow->appendPlainText("Me: " + msg);
}

void MainWindow::on_AddContactButton_clicked()
{
    addfriend.show();
}

void MainWindow::addContact(contInfo info)
{
    if(info.uid != -1){
        ui->ContactsList->addItem(info.login);
        addfriend.hide();
    }
}

void MainWindow::on_ContactsList_itemActivated(QListWidgetItem *item)
{
    ui->ChatWindow->clear();
    //QString msgs = getMessage(item);
    //ui->ChatWindow->setPlainText(msgs);
    ui->ChatWindow->setPlainText(item->text()+": Hello");
}

void MainWindow::on_DeleteContactButton_clicked()
{
    if(ui->ContactsList->currentRow() == -1)
        return;
    QListWidgetItem *item = ui->ContactsList->item(ui->ContactsList->currentRow());
    FriendReply reply = account.friendRequest(item->text(), "del_contact");
    if(reply.statusCode == web::http::status_codes::OK){
        DataBase::deleteContact(item->text());
        delete item;
    }
}

void MainWindow::databaseInit(QString _login)
{
    login = _login;
    account.setLogin(login);
    DataBase::createConnection(login);
    DataBase::createTable();
    ui->ContactsList->addItems(DataBase::getContacts());
    this->show();
}

void MainWindow::styleInit(){
}
