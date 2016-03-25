#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addfriend.h"
#include "authwindow.h"
#include "database.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QDesktopWidget().availableGeometry().width()/2 - this->width()/2,
                      QDesktopWidget().availableGeometry().height()/2 - this->width()/2,
                      this->width(), this->height());
    //accRequest accData = {};
    addfriend = new AddFriend;
    auth = new authwindow;

    //auth->setStyleSheet("QDialog { background-color: yellow }");
    auth->show();

    /*DataBase::createConnection(accData);
    DataBase::createTable();
    ui->ContactsList->addItems(DataBase::getContacts());*/

    //this->show();

    connect(auth, &authwindow::showMainWindow, this, &MainWindow::databaseInit, Qt::UniqueConnection);
    connect(auth, &authwindow::closeMainWindow, this, &MainWindow::close, Qt::UniqueConnection);
    connect(addfriend, &AddFriend::sendContact, this, &MainWindow::addContact, Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    auth->close();
    addfriend->close();
    delete auth;
    delete addfriend;
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
    addfriend->show();
}

void MainWindow::addContact(contInfo info)
{
    if(info.uid != -1){
        ui->ContactsList->addItem(info.login);
        addfriend->hide();
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
    if(ui->ContactsList->count() == 0)
        return;
    QListWidgetItem *item = ui->ContactsList->item(ui->ContactsList->currentRow());
    DataBase::deleteContact(item->text());
        delete item;
}

void MainWindow::databaseInit(QString inLogin)
{
    login = inLogin;
    DataBase::createConnection(login);
    DataBase::createTable();
    ui->ContactsList->addItems(DataBase::getContacts());
    this->show();
}

void MainWindow::styleInit(){
}
