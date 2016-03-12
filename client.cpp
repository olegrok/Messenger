#include <QNetworkRequest>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include "client.h"
#include "authwindow.h"
#include "mainwindow.h"
#include "structsforrequests.h"
#include <iostream>



using namespace web;
using namespace web::http;
using namespace web::http::client;

extern MainWindow w;
accountRequest auth;

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

}

Reply Client::accountRequest(accRequest req, QString property)
{
    json::value json;
    json["request"]      = json::value( U("account") );
    json["sub_request"]  = json::value( U(property.toStdString()) );
    json["login"]        = json::value( U(req.login.toStdString()) );
    json["key"]          = json::value( U(req.password.toStdString()) );
    Reply reply;
    qDebug() << req.login << req.password;
    //std::cout << json;
    //http_client client(U("http://localhost"));
    /*
    http_client cl;
    cl.add_handler(  );
    */
//    http_client client(U("http://localhost"));
    try
        {
            http_client client(U("http://192.168.1.204:7777"));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 http_response response = task.get();
                 reply.statusCode = response.status_code();
                //JsonParser
                 json = response.extract_json().get();
                 //std::cout << json;
              });

        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
              reply.statusCode = 600;
              reply.replyContent = e.what();
              return reply;
        }



    qDebug() << reply.statusCode << reply.replyContent;
    return reply;

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
