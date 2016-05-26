#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{}

Client::~Client()
{}

accReply Client::accountRequest(accRequest req, account_action property)
{
    json::value json;
    switch(property){
        case account_action::authorization: json["request"] = json::value(U("authorisation")); break;
        case account_action::registration:  json["request"] = json::value(U("registration")); break;
    }

    json["login"]        = json::value( U((req.login).toStdString()) );
    json["password"]     = json::value( U((req.password).toStdString()) );
    accReply reply;

    std::cout << json << std::endl;
    makeRequest(methods::POST, json, reply.statusCode);
    if(reply.statusCode != status_codes::OK){
        if(json.is_string())
            reply.content = QString::fromStdString(json.as_string());
        std::cout << json << std::endl;
        return reply;
    }

    setLogin(req.login);
    if(property == account_action::authorization){
        session = json.at("session");
        reply.session = session;
        reply.uid = json.at( U("session")).at(U("uid")).as_integer();
        reply.cookie = json.at(U("session")).at(U("session_key")).as_integer();
    }

    return reply;
}

FriendReply Client::friendRequest(QString contact_login, contact_action property)
{
    json::value json;
    switch(property){
        case contact_action::add :
            json["request"] = json::value( U("add_contact_request") );
            json["login"]   = json::value( U(contact_login.toStdString()) );
                break;
        case contact_action::del :
            json["request"] = json::value( U("del_contact") );
            json["uid"]     = json::value( DataBase::getUid(contact_login) );
                break;
        //case contact_action::accept :
        //case contact_action::deny :
    }

    json["session"]         = session;

    FriendReply reply;
    makeRequest(methods::POST, json, reply.statusCode);
    if(reply.statusCode != status_codes::OK){
        reply.login = QString::fromStdString(json.as_string());
        return reply;
    }

    if(property == contact_action::add){
        reply.login = contact_login;
        reply.uid = json.at(U("contact_uid")).as_integer();
     }

    return reply;
}

status_code Client::friendReply(int contact_uid, contact_reply property){
    json::value json;
    json["request"] = json::value(U("add_contact_reply"));
    json["uid"]     = json::value(contact_uid);
    json["status"]  = json::value(static_cast<int>(property));
    json["session"] = session;
    status_code status;
    makeRequest(methods::POST, json, status);
    return status;
}

bool Client::setLogin(QString login){
    clientLogin = login;
    return true;
}

json::value Client::getData(status_code& statusCode){
    json::value json;
    json["request"] = json::value( U("get_data") );
    json["session"] = session;

    makeRequest(methods::POST, json, statusCode);
    return json;
}

bool Client::logout(){
    json::value json;
    json["request"] = json::value( U("logout") );
    json["session"] = session;
    status_code statusCode;
    makeRequest(methods::POST, json, statusCode);
    if(statusCode != status_codes::OK)
        return false;
    return true;
}

http::status_code Client::sendMessage(msgCont msg){
    json::value json;
    json["request"]      = json::value( U("send_msg") );
    json["to_uid"]       = json::value( DataBase::getUid(msg.login));
    json["msg"]          = json::value( U(msg.text.toStdString()) );
    json["session"]      = session;

    status_code statusCode;
    makeRequest(methods::POST, json, statusCode);
    return statusCode;

}

pplx::task<http_response> Client::makeTaskRequest(method & mtd, json::value & json){
    std::cout << "Client input json: " << json << std::endl;
    return (mtd == methods::POST) ?
                client.request(mtd, U(""), json) :
                client.request(mtd, U(""));
}

void Client::makeRequest(method mtd, json::value& json, status_code & stcode){
    try{
    makeTaskRequest(mtd, json)
            .then([&](pplx::task<http_response> task){
        http_response response = task.get();
        stcode = response.status_code();
        try{
            if(!json.is_null())
                json = response.extract_json().get();
            else
                json = 0;
        }
        catch(const std::exception& e){
            qDebug() << "[in]Exception client: " << e.what() << stcode;
            json = 0;
            return;
        }
    }).wait();
    }
    catch(const std::exception &e){
        qDebug() << "[out]Exception client: " << e.what() << stcode;
        json = json::value(e.what());
        std::cout << json;
    }
}

void Client::setUrl(QString Url){
    ServerURL = Url;
    client = http_client(U(Url.toStdString()));
}
