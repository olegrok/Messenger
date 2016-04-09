#include "structsforrequests.h"
#include "profile.h"

Profile::Profile()
{

}

QString Profile::enterToAccount(QString password){
    accountRequest arg = {login, password};
    Reply reply = Client::accountRequest(arg, "account_authorisation");
    QString windowStatus;
    switch(reply.statusCode)
    {
        case 200: break;
//            this->close(); if windowStatus.empty -> close_window
        case 404: windowStatus = "Not Found!"; break;
        default: windowStatus = reply.replyContent; break;
    }
    return windowStatus;
}

bool Profile::registerAccount(QString login, QString password) {};
bool Profile::addFriend(QString login) {};
