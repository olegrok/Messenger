#include "profile.h"

Profile::Profile(QString _login) :
    login(_login)
{
    connect(&parser, SIGNAL(messagesPack(QVector<msgCont>)), this,
            SLOT(distributor(QVector<msgCont>)), Qt::UniqueConnection);

    connect(&monitor, SIGNAL(task(web::json::value)), this,
            SLOT(monitorHandler(web::json::value)), Qt::UniqueConnection);

    monitor.start();
}

Profile::~Profile(){
    monitor.terminate();
}

void Profile::setLogin(const QString _login){
    login = _login;
}

void Profile::setSessionData(int _cookie, int _uid){
    cookie = _cookie;
    uid = _uid;
}

accReply Profile::accountRequest(accRequest req, QString property){
    accReply reply = client.accountRequest(req, property);
    if(reply.statusCode == web::http::status_codes::Unauthorized){
        emit authorizationError();
        return reply;
    }
    if(reply.statusCode == web::http::status_codes::OK && property == "registration")
        reply = client.accountRequest(req, "authorisation");
    if(reply.statusCode == web::http::status_codes::OK){
        setSessionData(reply.cookie, reply.uid);
        setLogin(req.login);

        QCoreApplication::setOrganizationName(req.login);

        databaseInit();
        DataBase::addToLog("session", uid, QString::number(cookie), QDateTime::currentDateTimeUtc().toTime_t());
        auto contactArray = parser.contactListParser(client.getData());
        DataBase::clearContacts();
        std::for_each(contactArray.begin(), contactArray.end(), [&](QPair<QString, int> pair){
            contInfo info;
            info.login = pair.first;
            info.uid   = pair.second;
            DataBase::addContact(info);
        });
    }


    return reply;
}

FriendReply Profile::friendRequest(QString contact_login, QString property){
    FriendReply reply = client.friendRequest(contact_login, property);
    if(reply.statusCode == web::http::status_codes::Unauthorized){
        emit authorizationError();
    }
    return reply;
}

void Profile::monitorHandler(json::value json){
    //handler
}

web::http::status_code Profile::sendMessage(msgCont msg){
    auto statusCode = client.sendMessage(msg);
    if(statusCode == web::http::status_codes::Unauthorized){
        emit authorizationError();
        return statusCode;
    }
    if(statusCode == web::http::status_codes::OK)
        DataBase::addMessage(msg, "send");
    return statusCode;
}

QString& Profile::getLogin(){
    return login;
}

void Profile::databaseInit(){
    DataBase::createConnection(login);
    DataBase::createTable();
}

void Profile::closeSession(QString status){
    client.logout();
    DataBase::close();
    emit unlogin(status);
}

void Profile::distributor(QVector<msgCont> vector){
    std::for_each(vector.begin(), vector.end(), [&](msgCont elem){
        DataBase::addMessage(elem, "recive");
    });


}
