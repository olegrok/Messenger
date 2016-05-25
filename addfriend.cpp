#include "ui_addfriend.h"
#include "addfriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::on_AddButton_clicked()
{
    //contInfo info = CheckFriend(ui->FriendLogin->text());
    FriendReply reply = account->friendRequest((ui->FriendLogin->text()), contact_action::add);
    contInfo info;

    if(reply.statusCode == 200)
    {
        info.login = ui->FriendLogin->text();
        info.uid = reply.uid;
        info.lastMsgId = 0;
        info.unreaded = 0;
        if(!DataBase::addContact(info)){
            ui->AddFriendStatus->setText(tr("Just your friend"));
            return;
        }
    }
    else
    {
        switch (reply.statusCode) {
        case 404: reply.login = tr("Not found"); break;
        case 400: break;
        default: reply.login = tr("Unknown error");
            break;
        } 
        ui->AddFriendStatus->setText(reply.login);
        ui->FriendLogin->clear();
        return;
    }
    ui->FriendLogin->clear();
    emit sendContact(info);
}

void AddFriend::setUpProfile(Profile* acc){
    account = acc;
}

void AddFriend::setStatus(QString status){
    ui->AddFriendStatus->setText(status);
}

void AddFriend::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }
}
