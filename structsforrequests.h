#ifndef STRUCTSFORREQUESTS
#define STRUCTSFORREQUESTS

#include <QString>
#include <QDateTime>
#include <cpprest/http_client.h>
#include <cpprest/json.h>


using namespace web;
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
    status_code statusCode;
    QString content;
    int cookie;
    int uid;
    json::value session;
} accReply;


typedef
struct argumentsForRequest
{
    QString login;
    QString key;
    QString request;
} Request;



typedef
struct messageContainer
{
    int         senderUid;
    QString     login;
    //QString time;
    QString     text;
    int         time;
    //QString status;
    //int filed;

} msgCont;

typedef
struct contactInforamtion
{
  int uid;
  QString login;
  int lastMsgId = 0;
  int unreaded = 0;
  int status;
} contInfo;

typedef
struct FriendReply
{
    status_code statusCode;
    QString login;
    int uid;
} FriendReply;

/*typedef
struct jsonContainer{
    int senderUid;
    QString senderLogin;
    QString text;
    int time;

} jsonContainer;
*/
#endif // STRUCTSFORREQUESTS

