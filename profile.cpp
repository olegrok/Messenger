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

bool Profile::setLogin(QString _login){
    login = _login;
    return true;
}

accReply Profile::accountRequest(accRequest req, QString property){
    return client.accountRequest(req, property);
}

FriendReply Profile::friendRequest(QString contact_login, QString property){

    return client.friendRequest(contact_login, property);
}

void Profile::monitorHandler(json::value json){
    //handler
}

bool Profile::sendMessage(sndMsg msg){
    //client.sendMsg();
    DataBase::sendMessage(msg);
    return true;
}

QString& Profile::getLogin(){
    return login;
}
