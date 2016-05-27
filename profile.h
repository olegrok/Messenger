#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QString>

#include <QThread>
#include <cpprest/json.h>

#include <QDateTime>
#include <QVector>
#include "client.h"
#include "database.h"
#include "jsonprotocol.h"
#include "structsforrequests.h"
#include "monitor.h"

class Profile : public QObject
{
    //Add SSL
    //Сжатие zip
    //stateless - неск. серверов.
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
    FriendReply friendRequest(QString contact_login, contact_action property);
    status_code friendReply(QString contact_login, contact_reply property);
    accReply accountRequest(accRequest req, account_action property);
    web::http::status_code sendMessage(msgCont msg);
    void databaseInit();

    void setUrl(QString Url);
    void setSessionData(json::value json = 0);
    void setLogin(const QString);
    QString& getLogin();
    void closeSession(QString status = 0);
    Monitor* getMonitor_ptr();

signals:
    void logout(QString = 0);
    void authorizationError(QString = 0);
    void updateWindow();

public slots:
    void msgDistributor(QVector<msgCont>);
    void eventsDistributor(QVector<contInfo>);
    void monitorHandler(web::json::value json);

private:
    Monitor monitor;
    QString login;
    json::value session;
    Client client;
    JsonProtocol parser;
};

#endif // PROFILE_H
