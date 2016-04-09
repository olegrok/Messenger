#include <QtSql>
#include <QHostInfo>
#include <QStringList>
#include <QSqlRecord>
#include "database.h"
#include "structsforrequests.h"

extern accountRequest auth;


namespace DataBase{

bool createConnection(QString login)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(login + ".sqlite");
    //dbase.setUserName(login);
    //dbase.setHostName(QHostInfo().hostName());
    //dbase.setPassword(login.password);
    if(!dbase.open()){
        qDebug() << "Can't open database" << dbase.lastError();
        return false;
    }
    return true;
}

bool createTable()
{
    QSqlQuery query;
    QString   str  = "CREATE TABLE contacts ( "
                         "id INTEGER PRIMARY KEY NOT NULL, "
                         "login   VARCHAR(15) PRIMARY KEY, "
                         "last_msg_id  VARCHAR(15), "
                         "unreaded  INTEGER "
                     ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table";
        return false;
    }
              str  = "CREATE TABLE messages ( "
                         "contact_id INTEGER, "
                         "text   TEXT, "
                         "status  VARCHAR(15), "
                         "filed  VARCHAR(15) "
                     ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table";
        return false;
    }
    return true;
}


bool sendMessage(sndMsg msg)
{
    QSqlQuery query;
    QString strF =
          "INSERT INTO  messages (contact_id, text, status, filed) "
          "VALUES(%1, '%2', '%3', '%4');";

    QString str = strF.arg(msg.contactUID)
              .arg(msg.text)
              .arg(msg.status)
              .arg(msg.filed);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

bool AddContact(contInfo info)
{
    QSqlQuery query;
    QString strF =
          "INSERT INTO  contacts (id, login, last_msg_id, unreaded) "
          "VALUES(%1, '%2', '%3', %4);";
    QString str = strF.arg(info.uid)
              .arg(info.login)
              .arg(info.lastMsgId)
              .arg(info.unreaded);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

QStringList getContacts()
{
    //qDebug() << "contacts:";
    QSqlQuery query("SELECT * from contacts");
    QStringList contList;
    QString cont;
    QSqlRecord rec = query.record();
    while(query.next()){
        cont = query.value(rec.indexOf("login")).toString();
        contList << cont;
    }
    return contList;
}

bool deleteContact(QString login)
{
    qDebug() << login;
    QSqlQuery query;
    QString strF =
          "DELETE FROM contacts WHERE login = '%1';";
    QString str = strF.arg(login);
    if (!query.exec(str)) {
        qDebug() << "Unable to make delete opeation" << query.lastError();
        return false;
    }
    return true;
}

bool close(){
    QSqlDatabase::removeDatabase("SQLITE");
    return true;
}

}
