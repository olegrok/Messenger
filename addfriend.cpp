#include "addfriend.h"
#include "ui_addfriend.h"

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

bool AddFriend::CheckFriend(QString nick){

    //todo
    return true;
}

void AddFriend::on_AddButton_clicked()
{
    QString nick = ui->FriendLogin->text();
    if(CheckFriend(nick))
    {
        ui->FriendLogin->clear();
        emit sendNick(nick);


    }
}
