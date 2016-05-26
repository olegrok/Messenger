#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <QStringList>
#include <QSqlRecord>
#include <QListWidgetItem>
#include <utility>
#include "structsforrequests.h"

enum class msg_status : int {
    sended    = 1,
    recived   = 2
};

enum class contact_status : int {
    requested_from  = 0,  //исходящий
    accepted        = 1,
    denied          = 2,
    requested_to    = 3  //входящий
};

class DataBase
{
public:
    DataBase(QString login);
    ~DataBase();
    static bool createConnection(QString login);
    static bool addMessage(msgCont msg, msg_status status);
    static bool createTable();
    static bool addContact(contInfo info);
    static QVector<QListWidgetItem*> getContacts(QString login = 0);
    static bool deleteContact(QString);
    static bool close();
    static QString getMessages(QString login, QString strToFind = 0);
    static bool addToLog(QString type, int value = 0, QString comment = 0, int time = 0);
    static bool clearContacts();
    static int getUid(QString);
    static int lastTime();
    static int hasUnreaded(QString login);
    static void makeViewed(QString& login);
    static bool changeContactStatus(QString login, contact_status newStatus);
    static int getStatus(QString login);
};



#endif // DATABASE_H
