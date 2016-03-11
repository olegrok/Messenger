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

class Client : public QObject
{
   Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    //virtual ~Client();
    QString login;
    QString password;
    QUrl *url;
    QNetworkAccessManager *client;

//signals:

public slots:
    void finishedSlot(QNetworkReply* reply);
};

#endif // CLIENT_H
