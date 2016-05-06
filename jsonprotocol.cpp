#include "jsonprotocol.h"

/*JsonProtocol::JsonProtocol()
{

}
*/
using namespace web;

JsonProtocol::JsonProtocol(){}
JsonProtocol::~JsonProtocol(){}

    QVector < QPair<QString, int> > JsonProtocol::contactListParser(json::value json){
       std::cout << json << " size = " << json.size() << std::endl;
       QVector< QPair<QString, int> > contacts;

       if(json.at( U("contacts")).is_null())
           return contacts;

       auto contactsArray = json.at(U("contacts")).as_array();
       for(auto it = contactsArray.begin(); it != contactsArray.end(); ++it){
           std::cout << "fr_login " << it->at( U("friend_login")).as_string() << " uid: " << it->at(U("friend_uid")).as_integer()<< std::endl;
            contacts.push_back(qMakePair(QString::fromStdString(it->at( U("friend_login")).as_string()), it->at(U("friend_uid")).as_integer()));
        }
        qDebug() << contacts[0].first << contacts[0].second;
        return contacts;
    }


    QVector<msgCont> JsonProtocol::eventsParser(json::value json){
        std::cout << json << std::endl;
        QVector<msgCont> mainVector;
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
        return mainVector;
    }

