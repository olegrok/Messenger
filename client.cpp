#include "client.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

QString ServerURL = "https://localhost:7777";

Client::Client(QObject *parent) :
    QObject(parent)
{ }

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
    json["key"]          = json::value( U((req.password).toStdString()) );
    accReply reply;

    qDebug() << req.login << req.password;
    //http_client client(U("http://localhost"));
    /*
    http_client cl;
    cl.add_handler(  );
    */
//    http_client client(U("http://localhost"));


    http_response response;
    try
        {
            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 reply.statusCode = response.status_code();
              }).wait();
        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
              reply.statusCode = 600;
              reply.replyContent = e.what();
              return reply;
        }

    if(reply.statusCode == web::http::status_codes::OK){
        setLogin(req.login);
        json = response.extract_json().get();
        session = json;
        reply.uid = json.at( U("session")).at(U("uid")).as_integer();
        reply.cookie = QString::fromStdString(json.at(U("session")).at(U("session_key")).as_string());
    }
    qDebug() << reply.statusCode << reply.replyContent << reply.uid << reply.cookie;
    return reply;
}

FriendReply Client::friendRequest(QString contact_login, QString property)
{
    json::value json;
    json["request"]         = json::value( U(property.toStdString()) );
    json["login"]   = json::value( U(contact_login.toStdString()) );
    json["session"]         = session;

    FriendReply reply;
    http_response response;
    try
        {
            http_client client(U(ServerURL.toStdString()));
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

    if(reply.statusCode == web::http::status_codes::OK){
        if(property == "add_contact"){
            json = response.extract_json().get();
            std::cout << json << std::endl;

            reply.login = contact_login;
            reply.uid = json.at(U("uid")).as_integer();
        }
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

    http_response response;
    web::http::status_code statusCode;

    try
        {
            http_client client(U(ServerURL.toStdString()));
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
              //return reply;
        }

    json = response.extract_json().get();
    std::cout << json << std::endl;
    //todo json protocol class
    //to parse json
    //QVector<QPair<QString, int>>

    return true;
}

bool Client::logout(){
    json::value json;
    json["request"] = json::value( U("logout") );
    json["session"] = session;

    http_response response;
    web::http::status_code statusCode;

    try
        {
            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 statusCode = response.status_code();
                 qDebug() << "status code: " << statusCode;
              });
        }
      catch (const std::exception &e)
        {
              return false;
        }

    //if(reply.statusCode == web::http::status_codes::OK){}

    return true;
}
