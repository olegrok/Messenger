#include "client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
    qDebug() << "ctor";
    url = new QUrl("http://localhost:7777");
    QJsonObject json;
    json["key"] = "key";
    json["request"] = "account";
    json["login"] = "alex";
    json["sub_request"] = "account_authorisation";
    QByteArray reqest = QJsonDocument(json).toBinaryData();
    client = new QNetworkAccessManager;
    QObject::connect(client, SIGNAL(Client::finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)), Qt::UniqueConnection);
    client->post(QNetworkRequest(*url), reqest);
}

/*
POST:
{ "request":"account"
* "sub_request":"account_authorisation"
* "login":" " ,
* "key":" " ,
* }
*/

/*Client::~Client()
{
    delete client;
    delete url;
}*/

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
