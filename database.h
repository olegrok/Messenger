#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include "structsforrequests.h"

class DataBase
{
public:
    DataBase();
    ~DataBase();
    static bool createConnection(/*accRequest account*/);
    bool sendMessage(sndMsg msg);
    bool createTable();
    bool addContact(contInfo info);

private:

signals:

public slots:
};

#endif // DATABASE_H
