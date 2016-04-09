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

/*contInfo AddFriend::CheckFriend(QString nick){

    contInfo info;
    AddFriendReply reply = Client::AddFriend((ui->FriendLogin->text()));
    if(reply.statusCode == 200)
    {

        info.login = reply.login;
        info.uid = reply.uid;
        info.lastMsgId = 0;
        info.unreaded = 0;
        DataBase::addContact(info);
    }
    else
        info.uid = -1;

    return info;
}*/

void AddFriend::on_AddButton_clicked()
{
    //contInfo info = CheckFriend(ui->FriendLogin->text());
    AddFriendReply reply = Client::AddFriend((ui->FriendLogin->text()));
    ui->FriendLogin->clear();
    contInfo info;
    if(reply.statusCode == 200)
    {
        info.login = reply.login;
        info.uid = reply.uid;
        info.lastMsgId = 0;
        info.unreaded = 0;
        if(!DataBase::AddContact(info)){
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
    emit sendContact(info);
 /*   if(info.uid != -1)
    {
        ui->FriendLogin->clear();
        emit sendContact(info);
    }
*/
}
