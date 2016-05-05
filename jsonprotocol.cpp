#include "jsonprotocol.h"

/*JsonProtocol::JsonProtocol()
{

}
*/
using namespace web;

namespace JsonProtocol{
    QVector< QPair<QString, int> > contactListParser(json::value json){
        json.at(U("contacts")).as_array();
    }
}
