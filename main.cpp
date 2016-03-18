#include "mainwindow.h"
#include "database.h"
#include <QApplication>

//using namespace json;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //sndMsg msg = {122, "azaza", "not recived", 1};
    //DataBase x;
    //x.sendMessage(msg);
    //qDebug() << DataBase::getContacts();
    return a.exec();
}

/*
#include <cpprest/http_client.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

#include <iostream>
using namespace std;

int main()
{
   http_client client(U("http://192.168.1.204:7777"));

   json::value json;
   json["request"]      = json::value( U("account") );
   json["sub_request"]  = json::value( U("account_authorisation") );
   json["login"]        = json::value( U("alex") );
   json["key"]          = json::value( U("key") );

   client.request( web::http::methods::POST ,U("") , json )
    .then( [=]( pplx::task<web::http::http_response> task )
        {
            http_response response = task.get();
            cout << response.status_code();

            auto json = response.extract_json().get();
            std::cout << json;
         })
    .wait();


   return 0;

}
*/
