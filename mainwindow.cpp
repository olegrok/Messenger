#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addfriend.h"
#include "authwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //QDesktopWidget screen;
    //screen.availableGeometry().width();
    ui->setupUi(this);
    //this->setGeometry(300, 300, this->width(), this->height());
    this->setGeometry(QDesktopWidget().availableGeometry().width()/2 - this->width()/2,
                      QDesktopWidget().availableGeometry().height()/2 - this->width()/2,
                      this->width(), this->height());
    addfriend = new AddFriend();
    auth = new authwindow;
    auth->show();
    connect(auth, &authwindow::showMainWindow, this, &MainWindow::show, Qt::UniqueConnection);
    connect(auth, &authwindow::closeMainWindow, this, &MainWindow::close, Qt::UniqueConnection);
    //connect(ui->SendButton, SIGNAL(clicked()), this, SLOT(on_SendButton_clicked()), Qt::UniqueConnection);
    //connect(ui->AddContactButton, SIGNAL(clicked()), this, SLOT(on_AddContactButton_clicked()), Qt::UniqueConnection);
    connect(addfriend, &AddFriend::sendNick, this, &MainWindow::addContact, Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::addContact(QString nick)
{
    ui->ContactsList->addItem(nick);
    addfriend->hide();
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
    QListWidgetItem *item = ui->ContactsList->item(ui->ContactsList->currentRow());
        delete item;
}
