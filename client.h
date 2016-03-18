#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <cpprest/details/basic_types.h>
#include "structsforrequests.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

typedef
struct argumentsFromReply Reply;
typedef
struct accountRequest accRequest;

class Client : public QObject
{
   Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    ~Client();
    static Reply accountRequest(accRequest, QString);

//public slots:

};

#endif // CLIENT_H
