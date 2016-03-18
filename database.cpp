#include <QtSql>
#include <QHostInfo>
#include <QStringList>
#include <QSqlRecord>
#include "database.h"
#include "structsforrequests.h"

DataBase::DataBase()
{
    accRequest accData = {"oleg", "oleg"};
    createConnection(accData);
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


bool DataBase::createConnection(accRequest account)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("data.sqlite");
    dbase.setUserName(account.login);
    dbase.setHostName(QHostInfo().hostName());
    dbase.setPassword(account.password);
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


bool DataBase::sendMessage(sndMsg msg)
{
    QSqlQuery query;
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

QStringList DataBase::getContacts()
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

bool DataBase::deleteContact(QString login)
{
    QSqlQuery query;
    QString strF =
          "DELETE FROM contacts WHERE login = '%1';";
    QString str = strF.arg(login);
    if (!query.exec(str)) {
        qDebug() << "Unable to make delete opeation" << query.lastError();
        return false;
    }
}
