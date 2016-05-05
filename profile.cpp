#include "profile.h"

Profile::Profile(QString _login) :
    login(_login)
{
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

void Profile::setSessionData(QString _cookie, int _uid){
    cookie = _cookie;
    uid = _uid;
}

accReply Profile::accountRequest(accRequest req, QString property){
    accReply reply = client.accountRequest(req, property);
    if(reply.statusCode == web::http::status_codes::OK){
        setSessionData(reply.cookie, reply.uid);
        setLogin(req.login);
        databaseInit();
        DataBase::addToLog("session", uid, cookie, QDateTime::currentDateTimeUtc().toTime_t());
        auto contactArray = JsonProtocol::contactListParser(client.getData());
        std::for_each(contactArray.begin(), contactArray.begin(), [&](QPair<QString, int> pair){
            contInfo info;
            info.login = pair.first;
            info.uid   = pair.second;
            DataBase::addContact(info);
        });
    }


    return reply;
}

FriendReply Profile::friendRequest(QString contact_login, QString property){
    return client.friendRequest(contact_login, property);
}

void Profile::monitorHandler(json::value json){
    //handler
}

bool Profile::sendMessage(sndMsg msg){
    //client.sendMessage();
    DataBase::sendMessage(msg);
    return true;
}

QString& Profile::getLogin(){
    return login;
}

void Profile::databaseInit(){
    DataBase::createConnection(login);
    DataBase::createTable();
}

void Profile::closeSession(QString status){

    DataBase::close();
    emit unlogin(status);
}
