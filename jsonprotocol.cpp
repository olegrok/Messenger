#include "jsonprotocol.h"

/*JsonProtocol::JsonProtocol()
{

}
*/
using namespace web;

namespace JsonProtocol{

    QVector < QPair<QString, int> > contactListParser(json::value json){
       auto contactsArray = json.at(U("contacts")).as_array();
       QVector< QPair<QString, int> > contacts;
       for(auto it = contactsArray.begin(); it != contactsArray.end(); ++it){
            contacts.push_back(qMakePair(QString::fromStdString(it->at( U("login")).as_string()), it->at(U("uid")).as_integer()));
        }

        return contacts;
    }

}
