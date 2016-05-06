#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <cpprest/details/basic_types.h>
#include "structsforrequests.h"

#include "database.h"
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include "cpprest/asyncrt_utils.h"

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
    bool logout();
    json::value getData();
    status_code sendMessage(msgCont msg);
private:
    QString clientLogin;
    json::value session;

};

#endif // CLIENT_H
