#include "structsforrequests.h"
#include "profile.h"

Profile::Profile(QString _login)
{
    login = _login;
}

Profile::~Profile(){}

bool Profile::setLogin(QString _login){
    login = _login;
    return true;
}

Reply Profile::accountRequest(accRequest req, QString property){
    return client.accountRequest(req, property);
}

FriendReply Profile::friendRequest(QString login, QString property){
    return client.friendRequest(login, property);
}
