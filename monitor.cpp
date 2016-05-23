#include "monitor.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

Monitor::Monitor():
    client("http://localhost:7777"),
    isBreak(false)
{}

void Monitor::setSession(int cookie, int uid, QString& ServerURL_){
    session["uid"] = json::value(uid);
    session["session_key"] = json::value(cookie);
    ServerURL = ServerURL_;
}

void Monitor::setSession(json::value& session_, QString& ServerURL_){
    session = session_;
    ServerURL = ServerURL_;
    client = http_client(U(ServerURL.toStdString()));
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

    http::status_code statusCode;
    try{
        client.request( http::methods::POST ,U("") , json, cts.get_token())
        .then( [&]( pplx::task<http_response> task )
        {
            http_response response;
            if(task.is_done()){
                response = task.get();
                statusCode = response.status_code();
            }
            qDebug() << "Monitor status code: " << statusCode;
            if(statusCode == status_codes::OK){
                json = response.extract_json().get();
            }
            else{
                json = response.extract_json().get();
                std::cout << json << std::endl;
                json = 0;
            }
        }, cts.get_token()).wait();
    }
    catch(const std::exception& e){
        //NOTE may be bug.
        //Failed to read HTTP status line
        qDebug() << "Exception motior: " << e.what();
        return 0;
    }

     if(statusCode == status_codes::Unauthorized){
         emit authorizationError("Unauthorized");
         isBreak = true;
         return 0;
     }

     return json;
}

void Monitor::cancel(){
    isBreak = true;
    cts.cancel();
}
