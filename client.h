#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QJsonDocument>
#include <QString>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QByteArray>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QThread>
#include <QDebug>
#include <cpprest/filestream.h>
#include <cpprest/http_msg.h>
#include "structsforrequests.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
//using namespace utility;

class Client : public QObject
{
   Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    static Reply accountRequest(accRequest, QString);

public slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // CLIENT_H
