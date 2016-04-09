#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include "structsforrequests.h"

namespace DataBase
{
    bool createConnection(QString login);
    bool sendMessage(sndMsg msg);
    bool createTable();
    bool AddContact(contInfo info);
    QStringList getContacts();
    bool deleteContact(QString);
}

#endif // DATABASE_H
