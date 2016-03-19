#ifndef STRUCTSFORREQUESTS
#define STRUCTSFORREQUESTS

#include <QString>
#include <QDateTime>
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
} argReply;

typedef
struct sendMessage
{
    int contactID;
    //QString time;
    QString text;
    QString status;
    int filed;

} sndMsg;

typedef
struct contactInforamtion
{
  int id;
  QString login;
  int lastMsgId;
  int unreaded;
} contInfo;

#endif // STRUCTSFORREQUESTS

