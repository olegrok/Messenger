#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QString>
#include <QThread>
#include "client.h"
#include "structsforrequests.h"
#include <cpprest/json.h>
#include "database.h"

class Monitor : public QThread{
    Q_OBJECT
public:
    Monitor() {}
    ~Monitor() {}
    void run() Q_DECL_OVERRIDE{
        while(true){
            //auto json = Client::monitor();
            //emit task(json);
        }
    }
signals:
    void task(web::json::value json);
};

class Profile : public QObject
{
    Q_OBJECT
public:
    explicit Profile(QString _login = 0);
    ~Profile();
    bool setLogin(QString);
    FriendReply friendRequest(QString contact_login, QString property);
    accReply accountRequest(accRequest req, QString property);
    bool sendMessage(sndMsg msg);
    QString& getLogin();

public slots:
    void monitorHandler(web::json::value json);
private:
    Monitor monitor;
    QString login;
    QString token;
    Client client;
};

#endif // PROFILE_H
