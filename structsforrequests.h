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
    int contactUID;
    //QString time;
    QString text;
    QString status;
    int filed;

} sndMsg;

typedef
struct contactInforamtion
{
  int uid;
  QString login;
  int lastMsgId;
  int unreaded;
} contInfo;

typedef
struct AddFriendReply
{
    web::http::status_code statusCode;
    QString login;
    int uid;
} AddFriendReply;

#endif // STRUCTSFORREQUESTS

