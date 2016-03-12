#ifndef STRUCTSFORREQUESTS
#define STRUCTSFORREQUESTS

#include <QString>
#include <cpprest/http_client.h>
#include "client.h"

using namespace web::http;
typedef
struct accountRequest
{
  QString login;
  QString password;
} accRequest;

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
    web::http::status_code statusCode;
    QString replyContent;
} Reply;


#endif // STRUCTSFORREQUESTS

