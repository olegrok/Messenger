#include "client.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;


//QString ServerURL = "http://192.168.0.104:7777";
Client::Client(QObject *parent) :
    QObject(parent)
{
    //client_(ServerURL);
}

/*
POST:
{ "request":"account"
* "sub_request":"account_authorisation"
* "login":" " ,
* "key":" " ,
* }
*/

Client::~Client()
{}

accReply Client::accountRequest(accRequest req, QString property)
{
    json::value json;
    json["request"]      = json::value( U(property.toStdString()) );
    json["login"]        = json::value( U((req.login).toStdString()) );
    json["password"]     = json::value( U((req.password).toStdString()) );
    accReply reply;

    qDebug() << req.login << req.password;
    std::cout << json << std::endl;


    http_response response;
    std::cout << json << std::endl;
    try
        {
//            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 reply.statusCode = response.status_code();
                 qDebug() << reply.statusCode;
              }).wait();
        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
              reply.statusCode = 600;
              reply.replyContent = e.what();
              return reply;
        }
    json = response.extract_json().get();
    std::cout << json << std::endl;
    if(reply.statusCode == web::http::status_codes::OK){
        setLogin(req.login);
        if(property == "authorisation"){
            session = json.at("session");
            std::cout << "session json:" << session << std::endl;
            reply.uid = json.at( U("session")).at(U("uid")).as_integer();
            reply.cookie = json.at(U("session")).at(U("session_key")).as_integer();
        }
    }
    else
        reply.replyContent = QString::fromStdString(json.as_string());
    qDebug() << reply.statusCode << reply.replyContent << reply.uid << reply.cookie;
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
    http_response response;
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

    if(reply.statusCode == web::http::status_codes::OK){
        if(property == "add_contact_request"){
            reply.login = contact_login;
            reply.uid = json.at(U("contact_uid")).as_integer();
        }
    }
    else
        reply.login = QString::fromStdString(json.as_string());
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

    std::cout << "get data json:" << json << std::endl;
    http_response response;
    web::http::status_code statusCode;

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
    return json;
}

bool Client::logout(){
    json::value json;
    json["request"] = json::value( U("logout") );
    json["session"] = session;

    http_response response;
    web::http::status_code statusCode;

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

    //if(reply.statusCode == web::http::status_codes::OK){}

    return true;
}

web::http::status_code Client::sendMessage(msgCont msg){
    json::value json;
    json["request"]      = json::value( U("send_msg") );
    json["to_uid"]       = json::value( DataBase::getUid(msg.login));
    json["msg"]          = json::value( U(msg.text.toStdString()) );
    json["session"]      = session;

    std::cout << "message json: " << json << std::endl;

    http_response response;
    web::http::status_code statusCode;
    try
        {
 //           http_client client(U(ServerURL.toStdString()));
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

    return statusCode;

}
