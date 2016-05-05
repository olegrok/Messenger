#include "jsonprotocol.h"

/*JsonProtocol::JsonProtocol()
{

}
*/
using namespace web;

namespace JsonProtocol{

    QVector < QPair<QString, int> > contactListParser(json::value json){
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

}
