#include <QNetworkRequest>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include "client.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

Auth auth;

Client::Client(QObject *parent) :
    QObject(parent)
{
    qDebug() << "ctor";
    //url = new QUrl("http://localhost:7777");
    url = new QUrl("http://192.168.1.204:7777");
    QJsonObject json;
    json["key"] = "key";
    json["request"] = "account";
    json["login"] = "alex";
    json["sub_request"] = "account_authorisation";
    qDebug() << json;
    QByteArray reqest = QJsonDocument(json).toBinaryData();
    client = new QNetworkAccessManager;
    QObject::connect(client, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)), Qt::UniqueConnection);
    QNetworkRequest req;
    req.setHeader(QNetworkRequest::ContentTypeHeader,"Content-Type: application/json");
    req.setUrl(*url);
    client->post(req, reqest);
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
    client.request( web::http::methods::POST ,U("") , json )
     .then( [=]( pplx::task<web::http::http_response> task )
         {
             http_response response = task.get();
             Reply.status_code = response.status_code();
            //JsonParser
          })
     .wait();

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
