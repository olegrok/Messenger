#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <cpprest/details/basic_types.h>
#include "structsforrequests.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

class Client : public QObject
{
//    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    accReply accountRequest(accRequest req, QString property);
    FriendReply friendRequest(QString contact_login, QString property);
    bool setLogin(QString login);
private:
    QString clientLogin;
};

#endif // CLIENT_H
