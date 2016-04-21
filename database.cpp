#include <QtSql>
#include <QHostInfo>
#include <QStringList>
#include <QSqlRecord>
#include "database.h"
#include "structsforrequests.h"

extern accountRequest auth;

#define SEND    70001
#define RECIVE  70002

DataBase::DataBase(QString login){
    createConnection(login);
    createTable();
}

DataBase::~DataBase(){
    QSqlDatabase::removeDatabase("SQLITE");
}

bool DataBase::createConnection(QString login)
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

bool DataBase::createTable()
{
    QSqlQuery query;
    QString   str  = "CREATE TABLE contacts ( "
                         "id INTEGER PRIMARY    KEY NOT NULL, "
                         "login VARCHAR(15)     NOT NULL, "
                         "last_msg_id           VARCHAR(15), "
                         "unreaded              INTEGER "
                     ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table";
        return false;
    }
              str  = "CREATE TABLE messages ( "
                         "login     VARCHAR(255), "
                         "text      TEXT, "
                         "time      INTEGER, "
                         "status    INTEGER "
/*                       "filed     VARCHAR(15) "   */
                     ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table" << query.lastError();
        return false;
    }
    return true;
}


bool DataBase::sendMessage(sndMsg msg)
{
    QSqlQuery query;
    QString strF =
          "INSERT INTO  messages (login, text, time, status) "
          "VALUES('%1', '%2', %3, %4);";

    QString str = strF.arg(msg.login)
              .arg(msg.text)
              .arg(msg.time.toTime_t())
              .arg(SEND);
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

QStringList DataBase::getContacts()
{
    //qDebug() << "contacts:";
    QSqlQuery query("SELECT login FROM contacts");
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

QString DataBase::getMessages(QString login){
    QString strF = "SELECT * FROM messages WHERE login = '%1' ORDER BY time ASC;";
    QString str = strF.arg(login);

    QSqlQuery query;

    if (!query.exec(str)) {
        qDebug() << "Unable to make select opeation" << query.lastError();
    }
    QSqlRecord rec = query.record();
    QString text;
    while(query.next()){
        if(query.value(rec.indexOf("status")).toInt() == SEND)
            text.append( "Me: ");
        else
            text.append(login + ": ");

        text.append( query.value(rec.indexOf("text")).toString() + "\n");

    }
    qDebug() << text;
    return text;
}

bool DataBase::close(){
    QSqlDatabase::removeDatabase("SQLITE");
    return true;
}

