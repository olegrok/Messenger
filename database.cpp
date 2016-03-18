#include <QtSql>
#include <QHostInfo>
#include "database.h"
#include "structsforrequests.h"

DataBase::DataBase()
{
    createConnection();
    createTable();
    sndMsg msg = {111, "azaaza", "not_r", 111};
    sendMessage(msg);
    contInfo info = {111, "abc", 123, 02};
    addContact(info);
    QSqlQuery query;

    if (!query.exec("SELECT * FROM contacts;")) {
        qDebug() << "Unable to execute query - exiting";
    }

}

DataBase::~DataBase()
{
    QSqlDatabase::removeDatabase("SQLITE");
}


bool DataBase::createConnection(/*accRequest account*/)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("data.sqlite");
    dbase.setUserName(/*account.login*/"oleg");
    dbase.setHostName(QHostInfo().hostName());
    dbase.setPassword("account.password");
    if(!dbase.open()){
        qDebug() << "Can't open database" << dbase.lastError();
        return false;
    }

    return true;
}

bool DataBase::createTable()
{
    QSqlQuery query;
    QString   str  = "CREATE TABLE contacts ( "
                         "id INTEGER PRIMARY KEY NOT NULL, "
                         "login   VARCHAR(15), "
                         "last_msg_id  VARCHAR(15), "
                         "unreaded  INTEGER "
                     ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table";
        return false;
    }

              str  = "CREATE TABLE messages ( "
                         "contact_id INTEGER PRIMARY KEY NOT NULL, "
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


bool DataBase::sendMessage(sndMsg msg)
{
    QSqlQuery query;
    //Adding some information
    QString strF =
          "INSERT INTO  messages (contact_id, text, status, filed) "
          "VALUES(%1, '%2', '%3', '%4');";

    QString str = strF.arg(msg.contactID)
              .arg(msg.text)
              .arg(msg.status)
              .arg(msg.filed);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::addContact(contInfo info)
{
    QSqlQuery query;
    QString strF =
          "INSERT INTO  contacts (id, login, last_msg_id, unreaded) "
          "VALUES(%1, '%2', '%3', %4);";
    QString str = strF.arg(info.id)
              .arg(info.login)
              .arg(info.lastMsgId)
              .arg(info.unreaded);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

