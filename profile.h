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
#include <QMetaType>
using namespace web;

Q_DECLARE_METATYPE(QVector<msgCont>)
Q_DECLARE_METATYPE(web::json::value)

class Monitor : public QThread{
    Q_OBJECT
public:
    Monitor() {}
    ~Monitor() {}
    void setSession(int cookie, int uid){
        session["uid"] = json::value(uid);
        session["session_key"] = json::value(cookie);
    }

    void run() Q_DECL_OVERRIDE{
        while(true){
            json::value json = monitor();
            emit task(json);
            sleep(15);
        }
    }
    json::value monitor(){

        json::value json;
        json["request"]      = json::value( U("update_data") );
        json["session"]      = session;
        json["last_update"]  = DataBase::lastTime();
        std::cout << "message json: " << json << std::endl;

        http_response response;
        web::http::status_code statusCode;
        try
            {
                http_client client(U("http://192.168.0.104:7777"));
                client.request( web::http::methods::POST ,U("") , json )
                    .then( [&]( pplx::task<web::http::http_response> task )
                 {
                     response = task.get();
                     statusCode = response.status_code();
                     qDebug() << "sendMsg status code: " << statusCode;
                  }).wait();
            }
          catch (const std::exception &e){}

        json = response.extract_json().get();
        std::cout << json << std::endl;

        return json;
    }

signals:
    void task(web::json::value json);
private:
    json::value session;

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
    void updateWindow();

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
    //Q_DECLARE_METATYPE(messageContainer);
    //Q_DECLARE_METATYPE(QVector<msgCont>);
};

#endif // PROFILE_H
