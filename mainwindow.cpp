#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(QDesktopWidget().availableGeometry().width()/2 - this->width()/2,
                      QDesktopWidget().availableGeometry().height()/2 - this->width()/2,
                      this->width(), this->height());
    auth.setUpProfile(&account);
    addfriend.setUpProfile(&account);

    auth.show();

    connect(&auth, &authwindow::showMainWindow, this, &MainWindow::windowInit, Qt::UniqueConnection);
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
    if(ui->ContactsList->currentRow() == -1)
        return;
    sndMsg msg;
    msg.login = ui->ContactsList->currentItem()->text();
    msg.text = ui->MessageWindow->toPlainText();
    msg.time = QDateTime::currentDateTimeUtc();
    ui->MessageWindow->clear();
    if(msg.text.isEmpty())
        return;
    account.sendMessage(msg);
    //ui->ChatWindow->appendPlainText(QDateTime::currentDateTime().toString("HH:mm") + " ");
    ui->ChatWindow->appendPlainText("Me: " + msg.text);


}

void MainWindow::on_AddContactButton_clicked()
{
    addfriend.show();
}

void MainWindow::addContact(const contInfo info)
{
    if(info.uid != -1){
        ui->ContactsList->addItem(info.login);
        addfriend.hide();
    }
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

void MainWindow::windowInit(QString _login)
{
    login = _login;
    ui->ContactsList->addItems(DataBase::getContacts());
    this->show();
}

void MainWindow::styleInit(){
}

void MainWindow::on_OptionButton_clicked()
{
    opt.show();
}

void MainWindow::on_ContactsList_itemClicked(QListWidgetItem *item)
{
    ui->ChatWindow->clear();
    //QString msgs = getMessage(item);
    ui->ChatWindow->setPlainText(DataBase::getMessages(item->text()));
    //ui->ChatWindow->setPlainText(msgs);
    //ui->ChatWindow->setPlainText(item->text()+": Hello");
}
