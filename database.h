#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QStringList>
#include <QSqlRecord>
#include <QListWidgetItem>
#include <utility>
#include "structsforrequests.h"

class DataBase
{
public:
    DataBase(QString login);
    ~DataBase();
    static bool createConnection(QString login);
    static bool addMessage(msgCont msg, QString status);
    static bool createTable();
    static bool addContact(contInfo info);
    static QVector<QListWidgetItem> getContacts();
    static bool deleteContact(QString);
    static bool close();
    static QString getMessages(QString login);
    static bool addToLog(QString type, int value = 0, QString comment = 0, int time = 0);
    static bool clearContacts();
    static int getUid(QString);
    static int lastTime();
};

#endif // DATABASE_H
