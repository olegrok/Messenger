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

    connect(&auth, &authwindow::showMainWindow, this, &MainWindow::windowInit, Qt::UniqueConnection);
    connect(&addfriend, &AddFriend::sendContact, this, &MainWindow::addContact, Qt::UniqueConnection);
    connect(&opt, &Options::unloginProfile, this, &MainWindow::unloginProfile, Qt::UniqueConnection);
    connect(&account, &Profile::authorizationError, this, &MainWindow::unlogin, Qt::UniqueConnection);
    connect(&account, &Profile::updateWindow, this, &MainWindow::updateWindow, Qt::UniqueConnection);
    connect(&account, SIGNAL(unlogin()), this, SLOT(unlogin()), Qt::DirectConnection);
    connect(account.getMonitor_ptr(), SIGNAL(authorizationError()), this, SLOT(unlogin()), Qt::DirectConnection);

    auth.show();
//    this->show();
//    ui->ContactsList->addItem("Green");
//    ui->ContactsList->findItems("Green", Qt::MatchExactly).first()->setBackgroundColor(Qt::green);
//    //ui->ContactsList->findItems("Green", Qt::MatchExactly).first()->setBackground(Qt::gray);
//    qDebug() << showNotification("Olegrok");

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
    msgCont msg;
    msg.login = ui->ContactsList->currentItem()->text();
    msg.text = ui->MessageWindow->toPlainText();
    msg.time = QDateTime::currentDateTimeUtc().toTime_t();
    ui->MessageWindow->clear();
    if(msg.text.isEmpty())
        return;
    auto statusCode = account.sendMessage(msg);
    //ui->ChatWindow->appendPlainText(QDateTime::currentDateTime().toString("HH:mm") + " ");
    if(statusCode == web::http::status_codes::OK){
        updateWindow();
    }


}

void MainWindow::on_AddContactButton_clicked()
{
    addfriend.show();
}

void MainWindow::addContact(const contInfo info)
{
    if(info.uid != -1){
        ui->ContactsList->addItem(info.login);
        addfriend.close();
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
    contacts = DataBase::getContacts();
    for(auto it = contacts.begin(); it != contacts.end(); it++)
        ui->ContactsList->addItem(&(*it));
    styleInit();
    ui->ChatWindow->setVerticalScrollBar(&VerticalScroll);
    this->show();
}

void MainWindow::unlogin(QString status){
    if(status.isNull())
        auth.setStatus("Invalid Session");
    else
        auth.setStatus(status);
    ui->ChatWindow->clear();
    ui->ContactsList->clear();
    ui->MessageWindow->clear();
    this->hide();
    addfriend.close();
    opt.close();
    auth.show();
}

void MainWindow::styleInit(){
    QSettings settings;
    QVariant val = settings.value("user_interface/design");
    qDebug() << val;
    if(!val.isNull())
        qApp->setStyle(val.toString());
}

void MainWindow::on_OptionButton_clicked()
{
    opt.show();
}

void MainWindow::on_ContactsList_itemClicked(QListWidgetItem *item)
{
    ui->ChatWindow->clear();
    ui->ChatWindow->setHtml(DataBase::getMessages(item->text()));
    VerticalScroll.setSliderPosition(VerticalScroll.maximumHeight());
}

void MainWindow::unloginProfile(){
    account.closeSession("Welcome to Chat!");
    ui->ChatWindow->clear();
    ui->ContactsList->clear();
    ui->MessageWindow->clear();
    this->hide();
    auth.show();
}

void MainWindow::updateWindow(){
    //ui->ContactsList->clear();
    QVector<QListWidgetItem> contacts = DataBase::getContacts();
    std::for_each(contacts.begin(), contacts.end(), [&](QListWidgetItem item){
        ui->ContactsList->addItem(&item);
    });
    if(ui->ContactsList->currentRow() == -1)
        return;
    ui->ChatWindow->clear();
    ui->ChatWindow->setHtml(DataBase::getMessages(ui->ContactsList->currentItem()->text()));
    VerticalScroll.setSliderPosition(VerticalScroll.maximumHeight());
}

int MainWindow::showNotification(QString login){
    QMessageBox* note =
        new QMessageBox(QMessageBox::Information, "New Contact", "Do you want to add new contact: " + login,
                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    int result = note->exec();
    delete note;
    return result;
}

void MainWindow::on_actionAbout_program_triggered()
{
    QDesktopServices::openUrl(QUrl("https://docs.google.com/presentation/d/1xNTiiM7eFB2DkNB128jgf6KS8MUhTnBzGdxkrtk1Rkc/"));
}

void MainWindow::on_actionAbout_QT_triggered()
{
    qApp->aboutQt();
}
