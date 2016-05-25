#include "mainwindow.h"
#include "ui_mainwindow.h"

//=============FUNCTIONS=============

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << *(int*)QThread::currentThreadId();
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
    connect(&account, SIGNAL(unlogin(QString)), this, SLOT(unlogin(QString)), Qt::DirectConnection);
    connect(ui->lineFindLogin, SIGNAL(textChanged(const QString&)), this, SLOT(findContact(const QString&)));
    connect(ui->lineFindMsg, SIGNAL(textChanged(const QString&)), this, SLOT(changeMsgLineEvent(const QString&)));
    connect(account.getMonitor_ptr(), SIGNAL(authorizationError()), this, SLOT(unlogin()));
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

void MainWindow::loadContacts(QString text){
    QString current;
    QListWidgetItem *curr_item = 0;
    if(ui->ContactsList->currentRow() != -1){
        current = ui->ContactsList->selectedItems().first()->text();
        qDebug() << current;
    }
    ui->ContactsList->clear();
    contacts.clear();
    contacts = DataBase::getContacts(text);
    for(auto it : contacts){
        qDebug() << it->text() << "has unreaded:" << DataBase::hasUnreaded(it->text());
        if(DataBase::hasUnreaded(it->text())){
            it->setIcon(QIcon(":/images/bell.png"));
        }
        ui->ContactsList->addItem(it);
        if(it->text() == current){
            curr_item = it;
            it->setIcon(QIcon());
        }
        if(curr_item)
            ui->ContactsList->setCurrentItem(curr_item,
                          QItemSelectionModel::Current | QItemSelectionModel::Select);
    }
    ui->ContactsList->sortItems(Qt::AscendingOrder);
    ui->sortContacts->setIcon(QIcon(":/images/up.png"));
    ui->sortContacts->setWindowTitle("UP");
}

void MainWindow::styleInit(){
    QSettings settings;
    QVariant val = settings.value("user_interface/design");
    qDebug() << val;
    if(!val.isNull())
        qApp->setStyle(val.toString());
    val = settings.value("user_interface/language/file");
    qDebug() << val;
    if(!val.isNull()){
        opt.loadLang(val.toString());
        qDebug() << qApp->installTranslator(opt.getLang());
    }
}

bool MainWindow::loadMsg(QString text){
    if(ui->ContactsList->currentRow() == -1)
        return false;
    int pos = VerticalScroll.value();
    ui->ChatWindow->clear();
    ui->ChatWindow->setHtml(DataBase::getMessages(ui->ContactsList->currentItem()->text(), text));
    VerticalScroll.setValue(pos + 5 * VerticalScroll.singleStep());
    return true;
}

//=============SLOTS=============

void MainWindow::windowInit(QString _login)
{
    ui->sortContacts->setIcon(QIcon(":/images/up.png"));
    ui->sortContacts->setWindowTitle("UP");
    qDebug() << ui->sortContacts->windowTitle();
    login = _login;
    loadContacts();
    styleInit();
    if(ui->ChatWindow->verticalScrollBar() != &VerticalScroll)
        ui->ChatWindow->setVerticalScrollBar(&VerticalScroll);
    this->show();
}

void MainWindow::on_AddContactButton_clicked()
{
    addfriend.show();
}

//NOTE old function
void MainWindow::addContact(const contInfo info)
{
    if(info.uid != -1){
        ui->ContactsList->addItem(info.login);
        addfriend.close();
    }
}

void MainWindow::unlogin(QString status){
    if(login.isEmpty())
        return;
    qDebug() << "status: " << status;
    if(status.isNull())
        auth.setStatus(tr("Invalid Session"));
    else
        auth.setStatus(status);
    ui->ChatWindow->clear();
    ui->ContactsList->clear();
    ui->MessageWindow->clear();
    login.clear();
    addfriend.close();
    opt.close();
    auth.show();
    this->close();
}

void MainWindow::on_ContactsList_itemClicked(QListWidgetItem *item)
{\
    if(item == NULL)
        return;
    ui->ChatWindow->clear();
    ui->ChatWindow->setHtml(DataBase::getMessages(item->text()));
    VerticalScroll.setValue(VerticalScroll.maximum());
    item->setIcon(QIcon());
}

void MainWindow::unloginProfile(){
    account.closeSession(tr("Welcome to Chat!"));
}

void MainWindow::updateWindow(){
    qDebug() << "Update MainWindow";
    loadContacts(ui->lineFindLogin->text());
    loadMsg(ui->findMsgButton->text() == tr("Clear") ? ui->lineFindMsg->text() : 0);
}

int MainWindow::showNotification(QString login){
    QMessageBox* note =
        new QMessageBox(QMessageBox::Information, tr("New Contact"), tr("Do you want to add new contact: ") + login,
                        QMessageBox::Yes|QMessageBox::No/*|QMessageBox::Cancel*/);
    int result = note->exec();
    delete note;
    return result;
}

void MainWindow::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }
}

void MainWindow::findContact(const QString& text){
    qDebug() << text;
    loadContacts(text);
}

void MainWindow::changeMsgLineEvent(const QString &text){
}

//=============BUTTONS=============

void MainWindow::on_SendButton_clicked()
{
    qDebug() << ui->ContactsList->currentRow();
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
    if(statusCode == web::http::status_codes::OK){
        loadMsg(ui->findMsgButton->text() == tr("Clear") ?
                ui->lineFindMsg->text() : 0);
        VerticalScroll.setValue(VerticalScroll.maximum());
    }
}

void MainWindow::on_DeleteContactButton_clicked()
{
    if(ui->ContactsList->currentRow() == -1)
        return;
    QListWidgetItem *item = ui->ContactsList->item(ui->ContactsList->currentRow());
    FriendReply reply = account.friendRequest(item->text(), contact_action::del);
    if(reply.statusCode == web::http::status_codes::OK){
        DataBase::deleteContact(item->text());
        delete item;
    }
}

void MainWindow::on_OptionButton_clicked()
{
    opt.show();
}

void MainWindow::on_findMsgButton_clicked()
{

    if(ui->findMsgButton->text() == tr("Find")){
        if(ui->lineFindMsg->text().isEmpty())
            return;
        if(loadMsg(ui->lineFindMsg->text()))
            ui->findMsgButton->setText(tr("Clear"));
    }
    else{
        ui->findMsgButton->setText(tr("Find"));
        loadMsg();
    }
}

void MainWindow::on_sortContacts_clicked()
{
    if(ui->sortContacts->windowTitle() == "UP"){
        ui->sortContacts->setIcon(QIcon(":/images/down.png"));
        ui->sortContacts->setWindowTitle("DOWN");
        ui->ContactsList->sortItems(Qt::DescendingOrder);
    }
    else{
        ui->sortContacts->setIcon(QIcon(":/images/up.png"));
        ui->sortContacts->setWindowTitle("UP");
        ui->ContactsList->sortItems(Qt::AscendingOrder);
    }

}

//=============ACTIONS=============

void MainWindow::on_actionAbout_program_triggered()
{
    QDesktopServices::openUrl(QUrl("https://docs.google.com/presentation/d/1xNTiiM7eFB2DkNB128jgf6KS8MUhTnBzGdxkrtk1Rkc/"));
}

void MainWindow::on_actionAbout_QT_triggered()
{
    qApp->aboutQt();
}


