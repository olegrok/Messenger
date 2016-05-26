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
    FriendReply reply = account->friendRequest((ui->FriendLogin->text()), contact_action::add);
    contInfo info;

    if(reply.statusCode == 200)
    {
        info.login = ui->FriendLogin->text();
        info.uid = reply.uid;
        info.lastMsgId = 0;
        info.unreaded = 0;
        info.status = static_cast<int>(contact_status::requested_to);
    }
    else
    {
        switch (reply.statusCode) {
        case 404: reply.login = tr("Not found"); break;
        case 400: break;
        default:
            break;
        } 
        ui->AddFriendStatus->setText(reply.login);
        return;
    }
    ui->FriendLogin->clear();
    emit sendContact();
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
