#include "client.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;


//QString ServerURL = "http://192.168.0.104:7777";
Client::Client(QObject *parent) :
    QObject(parent)
{}

Client::~Client()
{}

accReply Client::accountRequest(accRequest req, QString property)
{
    json::value json;
    json["request"]      = json::value( U(property.toStdString()) );
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
    if(property == "authorisation"){
        session = json.at("session");
        std::cout << "session json:" << session << std::endl;
        reply.session = session;
        reply.uid = json.at( U("session")).at(U("uid")).as_integer();
        reply.cookie = json.at(U("session")).at(U("session_key")).as_integer();
    }

    return reply;
}

FriendReply Client::friendRequest(QString contact_login, QString property)
{
    json::value json;
    json["request"]         = json::value( U(property.toStdString()) );
    if(property == "add_contact_request")
        json["login"]       = json::value( U(contact_login.toStdString()) );
    json["session"]         = session;
    if(property == "del_contact")
        json["contact_uid"] = json::value( DataBase::getUid(contact_login) );

    FriendReply reply;
    makeRequest(methods::POST, json, reply.statusCode);
    if(reply.statusCode != status_codes::OK){
        reply.login = QString::fromStdString(json.as_string());
        return reply;
    }
/*    http_response response;
      try
        {
//            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 reply.statusCode = response.status_code();
                 qDebug() << "status code: " << reply.statusCode;
              }).wait();
        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
              reply.statusCode = 600;
              reply.login = e.what();
              return reply;
        }

    json = response.extract_json().get();
    std::cout << json << std::endl;
*/
    if(property == "add_contact_request"){
        reply.login = contact_login;
        reply.uid = json.at(U("contact_uid")).as_integer();
     }

    return reply;
}

bool Client::setLogin(QString login){
    clientLogin = login;
    return true;
}

json::value Client::getData(){
    json::value json;
    json["request"] = json::value( U("get_data") );
    json["session"] = session;

    web::http::status_code statusCode;
    makeRequest(methods::POST, json, statusCode);
    if(statusCode != status_codes::OK)
        json = 0;
/*    http_response response;
    try
        {
//            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 statusCode = response.status_code();
                 qDebug() << "status code: " << statusCode;
              }).wait();
        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
        }

    json = response.extract_json().get();
    std::cout << json << std::endl;
*/
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
/*
    http_response response;
    try
        {
//            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 statusCode = response.status_code();
                 qDebug() << "status code: " << statusCode;
              }).wait();
        }
      catch (const std::exception &e)
        {
              return false;
        }
*/
    return true;
}

web::http::status_code Client::sendMessage(msgCont msg){
    json::value json;
    json["request"]      = json::value( U("send_msg") );
    json["to_uid"]       = json::value( DataBase::getUid(msg.login));
    json["msg"]          = json::value( U(msg.text.toStdString()) );
    json["session"]      = session;

    status_code statusCode;
    makeRequest(methods::POST, json, statusCode);
/*    http_response response;
    try
        {
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
*/
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

