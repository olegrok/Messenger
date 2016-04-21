#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include "structsforrequests.h"

class DataBase
{
public:
    DataBase(QString login);
    ~DataBase();
    static bool createConnection(QString login);
    static bool sendMessage(sndMsg msg);
    static bool createTable();
    static bool addContact(contInfo info);
    static QStringList getContacts();
    static bool deleteContact(QString);
    static bool close();
    static QString getMessages(QString login);
};

#endif // DATABASE_H
