#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include "client.h"
#include "structsforrequests.h"

class Profile
{
public:
    Profile(QString login = 0);
    ~Profile();
    bool setLogin(QString);
    FriendReply friendRequest(QString login, QString property);
    Reply accountRequest(accRequest req, QString property);

private:
    QString login;
    QString token;
    Client client;
    //QString enterToAccount(QString password);
};

#endif // PROFILE_H
