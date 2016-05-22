#include "monitor.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

void Monitor::setSession(int cookie, int uid, QString& ServerURL_){
    session["uid"] = json::value(uid);
    session["session_key"] = json::value(cookie);
    ServerURL = ServerURL_;
}

void Monitor::setSession(json::value& session_, QString& ServerURL_){
    session = session_;
    ServerURL = ServerURL_;
}

void Monitor::run(){
    qDebug() << *(int*)QThread::currentThreadId();
    isBreak = false;
    while(true){
        json::value json = monitor();
        if(isBreak)
            break;
        if(json != 0){
            emit task(json);
            sleep(2);
        }
        else
            sleep(15);
    }
}

json::value Monitor::monitor() {

    json::value json;
    json["request"]      = json::value( U("update_data") );
    json["session"]      = session;
    json["last_update"]  = DataBase::lastTime();
    std::cout << "message json: " << json << std::endl;

    http_response response;
    web::http::status_code statusCode;
    try{
        http_client client(U(ServerURL.toStdString()));
        client.request( web::http::methods::POST ,U("") , json )
            .then( [&]( pplx::task<web::http::http_response> task )
            {
                response = task.get();
                statusCode = response.status_code();
            }).wait();
        qDebug() << "sendMsg status code: " << statusCode \
                 << (statusCode == web::http::status_codes::Unauthorized);
        if(statusCode == web::http::status_codes::Unauthorized){
            emit authorizationError("Unauthorized");
            isBreak = true;
            return -1;
        }

        if(statusCode != web::http::status_codes::OK)
            return 0;
       }
     catch (const std::exception &e){
        return 0;
    }
    json = response.extract_json().get();
    std::cout << json << std::endl;

    return json;
}
