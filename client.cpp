#include <QNetworkRequest>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include "client.h"

#include <iostream>

using namespace web;
using namespace web::http;
using namespace web::http::client;

Auth auth;

Client::Client(QObject *parent) :
    QObject(parent)
{

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
{
    delete client;
    delete url;
}

Reply Client::request(Request req)
{
    json::value json;
    json["request"]      = json::value( U(req.request.toStdString()) );
    json["sub_request"]  = json::value( U(req.sub_reqest.toStdString()) );
    json["login"]        = json::value( U(req.login.toStdString()) );
    json["key"]          = json::value( U(req.key.toStdString()) );
    Reply reply;
    http_client client(U("http://localhost"));

    try
        {
    client.request( web::http::methods::POST ,U("") , json )
     .then( [=]( pplx::task<web::http::http_response> task )
         {
             http_response response = task.get();
             //reply.statusCode = response.status_code();
            //JsonParser
          }).wait();


          }
      catch (const std::exception &e)
          {
              qDebug() << "Error exception:" << e.what();
          }



}

void Client::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString string(bytes);
        qDebug() << string;
    }
    else
    {
        qDebug() << reply->errorString();
    }
    delete reply;
}
