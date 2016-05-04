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
    //Add SSL
    //Сжатие zip
    //staitless - неск. серверов.
    //Таблица сессий
    //cookie храниться после закрытия
    //один человек одна сессия
    //База данных - транзакция
    //offline
    //Последнее действие - база данных
    Q_OBJECT
public:
    explicit Profile(QString _login = 0);
    ~Profile();
    FriendReply friendRequest(QString contact_login, QString property);
    accReply accountRequest(accRequest req, QString property);
    bool sendMessage(sndMsg msg);

    void setSessionData(QString cookie = 0, int uid = 0);
    void setLogin(QString);
    QString& getLogin();

public slots:
    void monitorHandler(web::json::value json);
private:
    Monitor monitor;
    QString login;
    QString cookie;
    int     uid;
    Client client;
};

#endif // PROFILE_H
