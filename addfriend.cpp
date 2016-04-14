#include "addfriend.h"
#include "ui_addfriend.h"
#include "structsforrequests.h"
#include "database.h"


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
    FriendReply reply = account->friendRequest((ui->FriendLogin->text()), "add_contact");
    contInfo info;

    if(reply.statusCode == 200)
    {
        info.login = ui->FriendLogin->text();
        info.uid = reply.uid;
        info.lastMsgId = 0;
        info.unreaded = 0;
        if(!DataBase::addContact(info)){
            ui->AddFriendStatus->setText("Just your friend");
            return;
        }
    }
    else
    {
        info.uid = -1;
        switch (reply.statusCode) {
        case 404: info.login = "Not found";
            break;
        default: info.login = "Unknown error";
            break;
        }
        ui->AddFriendStatus->setText(info.login);
    }
    ui->FriendLogin->clear();
    emit sendContact(info);
 /*   if(info.uid != -1)
    {
        ui->FriendLogin->clear();
        emit sendContact(info);
    }
*/
}

void AddFriend::setUpProfile(Profile* acc){
    account = acc;
}
