#ifndef STRUCTSFORREQUESTS
#define STRUCTSFORREQUESTS

#include <QString>
#include <QDateTime>
#include <cpprest/http_client.h>


using namespace web::http;

typedef
struct accountRequest
{
  QString login;
  QString password;
} accRequest;

typedef
struct accountReply
{
    web::http::status_code statusCode;
    QString replyContent;
    int cookie;
    int uid;
} accReply;


typedef
struct argumentsForRequest
{
    QString login;
    QString key;
    QString request;
} Request;



typedef
struct sendMessage
{
    //int contactUID;
    QString     login;
    //QString time;
    QString     text;
    QDateTime   time;
    //QString status;
    //int filed;

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
struct FriendReply
{
    web::http::status_code statusCode;
    QString login;
    int uid;
} FriendReply;

#endif // STRUCTSFORREQUESTS

