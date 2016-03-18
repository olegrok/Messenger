#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include "structsforrequests.h"

class DataBase
{
public:
    DataBase();
    ~DataBase();
    static bool createConnection(accRequest account);
    static bool sendMessage(sndMsg msg);
    static bool createTable();
    static bool addContact(contInfo info);
    static QStringList getContacts();
    static bool deleteContact(QString);
private:

signals:

public slots:
};

#endif // DATABASE_H
