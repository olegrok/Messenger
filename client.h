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

using namespace web;
using namespace web::http;
using namespace web::http::client;
//using namespace utility;

typedef
struct autorization
{
  QString login;
  QString password;
} Auth;

typedef
struct argumentsForRequest
{
    QString login;
    QString key;
    QString request;
    QString sub_reqest;
} Request;

typedef
struct argumentsFromReply
{
    //http::status_code statusCode;
    QString replyContent;
} Reply;

class Client : public QObject
{
   Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    QString login;
    QString password;
    QUrl *url;
    QNetworkAccessManager *client;
    Reply request(Request req);

//signals:

public slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // CLIENT_H
