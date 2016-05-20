#include "jsonprotocol.h"

/*JsonProtocol::JsonProtocol()
{

}
*/
using namespace web;

JsonProtocol::JsonProtocol(){}
JsonProtocol::~JsonProtocol(){}

QVector <contInfo> JsonProtocol::contactListParser(json::value json){
       std::cout << json << " size = " << json.size() << std::endl;
       QVector <contInfo> contacts;

       if(!json.has_field(U("contacts")))
           throw std::invalid_argument("Bad json was replied");
       if(json.at( U("contacts")).is_null())
           return contacts;

       auto contactsArray = json.at(U("contacts")).as_array();
       for(auto it = contactsArray.begin(); it != contactsArray.end(); ++it){
           std::cout << "fr_login " << it->at( U("friend_login")).as_string() << " uid: " << it->at(U("friend_uid")).as_integer()<< std::endl;
           contInfo info;
           info.login = QString::fromStdString(it->at( U("friend_login")).as_string());
           info.uid = it->at(U("friend_uid")).as_integer();
           info.status = it->at( U("status") ).as_integer();
           contacts.push_back(std::move(info));
        }
        qDebug() << contacts[0].login << contacts[0].uid << contacts[0].status;
        return contacts;
    }


void JsonProtocol::eventsParser(json::value json){
        std::cout << "EventParser " << json << std::endl;
        QVector<msgCont> mainVector;
        int time = 0;
        if(json.has_field(U("server_time"))){
            time = json.at(U("server_time")).as_integer();
            DataBase::addToLog("update", time);
        }
        else
            return;
        if(json.has_field("msg_array")){
            auto msgArray = json.at("msg_array").as_array();
            for(auto it = msgArray.begin(); it != msgArray.end(); ++it){
                msgCont data;
                data.login = QString::fromStdString(it->at(U("sender_login")).as_string());
                data.senderUid   = it->at(U("sender_uid")).as_integer();
                data.text = QString::fromStdString(it->at(U("text")).as_string());
                data.time = it->at(U("time")).as_integer();
                mainVector.push_back(data);
            }

            emit messagesPack(mainVector);
        }
    }

