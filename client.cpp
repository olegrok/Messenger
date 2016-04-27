#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include "cpprest/details/basic_types.h"
#include "cpprest/asyncrt_utils.h"

#include "string.h"
#include <QString>
#include <QtCore/QTextCodec>
#include <QtCore>
#include <QDebug>
#include <QtGlobal>

#include "client.h"
#include "structsforrequests.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

QString ServerURL = "http://localhost:7777";

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
    json["request"]      = json::value( U("account") );
    json["sub_request"]  = json::value( U(property.toStdString()) );
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

        //JsonParser
         //std::cout << json;
    }
    qDebug() << reply.statusCode << reply.replyContent;
    return reply;
}

FriendReply Client::friendRequest(QString contact_login, QString property)
{
    json::value json;
    json["request"]         = json::value( U("account") );
    json["sub_request"]     = json::value( U(property.toStdString()) );
    json["client_login"]    = json::value( U(clientLogin.toStdString()) );
    json["contact_login"]   = json::value( U(contact_login.toStdString()) );

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
        //JsonParser
        if(property == "add_contact"){
            json = response.extract_json().get();
            std::cout << json << std::endl;
            /*auto jcontact = json.at(U("contact") );
            std::cout << jcontact.at(U("login")).as_string();*/

            reply.login = contact_login;
            //reply.uid = json.at(U("uid")).as_integer();
            reply.uid = qrand();
        }
    }
    return reply;

}

bool Client::setLogin(QString login){
    clientLogin = login;
    return true;
}
