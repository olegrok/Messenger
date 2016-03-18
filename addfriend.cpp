#include "addfriend.h"
#include "ui_addfriend.h"
#include "structsforrequests.h"

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

contInfo AddFriend::CheckFriend(QString nick){


    contInfo info;
    info.login = nick;
    info.id = qrand();
    info.lastMsgId = 0;
    info.unreaded = 0;

    //todo
    return info;
}

void AddFriend::on_AddButton_clicked()
{
    contInfo info = CheckFriend(ui->FriendLogin->text());

    if(info.id != -1)
    {
        ui->FriendLogin->clear();
        emit sendContact(info);
    }
}
