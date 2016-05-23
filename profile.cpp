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

accReply Profile::accountRequest(accRequest req, QString property){
    accReply reply = client.accountRequest(req, property);
    if(reply.statusCode == web::http::status_codes::Unauthorized){
        emit authorizationError();
        return reply;
    }
    if(reply.statusCode != http::status_codes::OK)
        return reply;
    if(reply.statusCode == http::status_codes::OK && property == "registration")
        reply = client.accountRequest(req, "authorisation");
    if(reply.statusCode == http::status_codes::OK){
        setSessionData(reply.session);
        setLogin(req.login);

        QCoreApplication::setOrganizationName(req.login);

        databaseInit();
        DataBase::addToLog("session", reply.uid, QString::number(reply.cookie),
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

FriendReply Profile::friendRequest(QString contact_login, QString property){
    FriendReply reply = client.friendRequest(contact_login, property);
    if(reply.statusCode == web::http::status_codes::Unauthorized){
        emit authorizationError();
    }
    return reply;
}

void Profile::monitorHandler(json::value json){
    qDebug() << *(int*)QThread::currentThreadId();
    parser.eventsParser(json);
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
//        contInfo info;
//        info.uid = elem.senderUid;
//        info.login = elem.login;
//        DataBase::addContact(info);
    });
    emit updateWindow();
}

Monitor* Profile::getMonitor_ptr(){
    return &monitor;
}
