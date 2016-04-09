#ifndef PROFILE_H
#define PROFILE_H

#include <QString>

class Profile
{
public:
    Profile();
    bool setLogin(QString);


private:
    QString login;
    QString token;
    QString enterToAccount(QString password);
    bool registerAccount(QString login, QString password);
    bool addFriend(QString login);
};

#endif // PROFILE_H
