#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include "cpprest/details/basic_types.h"
#include "cpprest/asyncrt_utils.h"
#include "client.h"
#include "structsforrequests.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

accountRequest auth = {};

QString ServerURL = "http://localhost:7777";

Client::Client(QObject *parent) :
    QObject(parent)
{

}

/*
POST:
{ "request":"account"
* "sub_request":"account_authorisation"
* "login":" " ,
* "key":" " ,
* }
*/

Client::~Client()
{

}

Reply Client::accountRequest(accRequest req, QString property)
{
    json::value json;
    json["request"]      = json::value( U("account") );
    json["sub_request"]  = json::value( U(property.toStdString()) );
    json["login"]        = json::value( U(req.login.toStdString()) );
    json["key"]          = json::value( U(req.password.toStdString()) );
    Reply reply;
    qDebug() << req.login << req.password;
    //std::cout << json;
    //http_client client(U("http://localhost"));
    /*
    http_client cl;
    cl.add_handler(  );
    */
//    http_client client(U("http://localhost"));
    http_response response;
    try
        {
            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 response = task.get();
                 reply.statusCode = response.status_code();
              }).wait();
        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
              reply.statusCode = 600;
              reply.replyContent = e.what();
              return reply;
        }
    if(reply.statusCode == 200){
        //JsonParser
         //std::cout << json;
        json = response.extract_json().get();
    }
    qDebug() << reply.statusCode << reply.replyContent;
    return reply;

}

AddFriendReply Client::AddFriend(QString login)
{
    json::value json;
    json["request"]      = json::value( U("account") );
    json["sub_request"]  = json::value( U("add_contact") );
    json["login"]        = json::value( U(login.toStdString()) );
    AddFriendReply reply;
    try
        {
            http_client client(U(ServerURL.toStdString()));
            client.request( web::http::methods::POST ,U("") , json )
                .then( [&]( pplx::task<web::http::http_response> task )
             {
                 http_response response = task.get();
                 reply.statusCode = response.status_code();
                 qDebug() << "status code: " << reply.statusCode;
                //JsonParser
                 json = response.extract_json().get();
                 std::cout << json << std::endl;
                 reply.login = QString::fromStdString(json.at(U("login")).as_string());
                 reply.uid = json.at(U("uid")).as_integer();
                 //std::cout << json;
              }).wait();
        }
      catch (const std::exception &e)
        {
              qDebug() << "Error exception:" << e.what();
              reply.statusCode = 600;
              reply.login = e.what();
              return reply;
        }
    return reply;

}


