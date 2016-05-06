#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDateTime>
#include <QVector>
#include "client.h"
#include <cpprest/json.h>
#include "database.h"
#include "jsonprotocol.h"
#include "structsforrequests.h"

class Monitor : public QThread{
    Q_OBJECT
public:
    Monitor() {}
    ~Monitor() {}
    void run() Q_DECL_OVERRIDE{
        while(true){
            //auto json = monitor();
            //emit task(json);
        }
    }
    json::value monitor(){
        sleep(1e6);
        return json::value("gap");
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
    web::http::status_code sendMessage(msgCont msg);
    void databaseInit();

    void setSessionData(int cookie = 0, int uid = 0);
    void setLogin(const QString);
    QString& getLogin();
    void closeSession(QString status = 0);

signals:
    void unlogin(QString = 0);
    void authorizationError(QString = 0);
    void update();

public slots:
    void distributor(QVector<msgCont>);
    void monitorHandler(web::json::value json);


private:
    Monitor monitor;
    QString login;
    int     cookie;
    int     uid;
    Client client;
    JsonProtocol parser;
};

#endif // PROFILE_H
