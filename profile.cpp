#include "profile.h"

Profile::Profile(QString _login) :
    login(_login)
{
    qRegisterMetaType<QVector<msgCont>>("QVector<msgCont>");
    qRegisterMetaType<json::value>("json::value");

    connect(&parser, SIGNAL(messagesPack(QVector<msgCont>)), this,
            SLOT(distributor(QVector<msgCont>)));
    monitor.moveToThread(&monitor);
    connect(&monitor, SIGNAL(task(web::json::value)), this,
            SLOT(monitorHandler(web::json::value)));
}

Profile::~Profile(){
    try{
        monitor.cancel();
        monitor.wait();
    }
    catch(const std::exception &e){}
}

void Profile::setLogin(const QString _login){
    login = _login;
}

void Profile::setSessionData(json::value session_){
    session = session_;
}

accReply Profile::accountRequest(accRequest req, account_action property){
    accReply reply = client.accountRequest(req, property);
    if(reply.statusCode == http::status_codes::Unauthorized){
        emit authorizationError();
        return reply;
    }
    if(reply.statusCode != http::status_codes::OK)
        return reply;
    if(reply.statusCode == http::status_codes::OK && property == account_action::registration)
        reply = client.accountRequest(req, account_action::authorization);
    if(reply.statusCode == http::status_codes::OK){
        setSessionData(reply.session);
        setLogin(req.login);

        QCoreApplication::setOrganizationName(req.login);

        databaseInit();
        DataBase::addToLog("session", reply.statusCode, QString::fromStdString(reply.session.serialize()),
                           QDateTime::currentDateTimeUtc().toTime_t());

        json::value json = client.getData(reply.statusCode);
        if(reply.statusCode !=  http::status_codes::OK){
            if(json.is_string()){
                reply.content = QString::fromStdString(json.as_string());
            }
            return reply;
        }

        auto contactArray = parser.contactListParser(json);
        DataBase::clearContacts();
        std::for_each(contactArray.begin(), contactArray.end(), [&](contInfo info){
            DataBase::addContact(info);
        });

        monitor.setSession(session, client.ServerURL);
        monitor.start(QThread::HighPriority);
    }


    return reply;
}

FriendReply Profile::friendRequest(QString contact_login, contact_action property){
    FriendReply reply = client.friendRequest(contact_login, property);
    if(reply.statusCode == http::status_codes::Unauthorized){
        emit authorizationError();
    }
    return reply;
}

void Profile::monitorHandler(json::value json){
    qDebug() << *(int*)QThread::currentThreadId();
    parser.eventsParser(json);
}

http::status_code Profile::sendMessage(msgCont msg){
    auto statusCode = client.sendMessage(msg);
    if(statusCode == status_codes::Unauthorized){
        emit authorizationError();
        return statusCode;
    }
    if(statusCode == status_codes::OK)
        DataBase::addMessage(msg, msg_status::sended);
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
    for(auto it : vector){
        DataBase::addMessage(it, msg_status::recived);
    }
    emit updateWindow();
}

Monitor* Profile::getMonitor_ptr(){
    return &monitor;
}

void Profile::setUrl(QString URL){
    if(URL.isEmpty())
        return;
    client.setUrl(URL);
}
