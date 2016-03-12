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
    QString status_code;
    QString reply_content;
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
