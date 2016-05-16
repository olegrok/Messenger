#include "database.h"

#define SEND    70001
#define RECIVE  70002

#define UNREPLIED 80000
#define ACCEPTED  80001
#define DENIED    80002

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
                         "id INTEGER            NOT NULL, "
                         "login VARCHAR(15)     PRIMARY KEY NOT NULL, "
                         "last_msg_id           VARCHAR(15), "
                         "unreaded              INTEGER, "
                         "status                INTEGER "
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
                     ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table" << query.lastError();
        return false;
    }

                str  = "CREATE TABLE log ( "
                        "type      VARCHAR(255), "
                        "value     INTEGER, "
                        "comment   TEXT, "
                        "time      INTEGER "
                    ");";

    if (!query.exec(str)) {
        qDebug() << "Unable to create a table" << query.lastError();
        return false;
    }

    return true;
}

bool DataBase::addToLog(QString type, int value, QString comment, int time){
    QSqlQuery query;
    QString strF =
            "INSERT INTO  log (type, value, comment, time) "
            "VALUES('%1', %2, '%3', %4);";
    QString str = strF.arg(type)
                      .arg(value)
                      .arg(comment)
                      .arg(time);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::addMessage(msgCont msg, QString status)
{
    QSqlQuery query;
    QString strF =
          "INSERT INTO  messages (login, text, time, status) "
          "VALUES('%1', '%2', %3, %4);";

    QString str = strF.arg(msg.login)
            .arg(msg.text)
            .arg(msg.time);
    if(status == "send")
        str = str.arg(SEND);
    if(status == "recive")
        str = str.arg(RECIVE);

    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

bool DataBase::addContact(contInfo info)
{
    qDebug() << info.login << info.uid << info.status;
    QSqlQuery query;
    QString strF =
          "INSERT INTO  contacts (id, login, last_msg_id, unreaded, status) "
          "VALUES(%1, '%2', '%3', %4, %5);";
    QString str = strF.arg(info.uid)
              .arg(info.login)
              .arg(info.lastMsgId)
              .arg(info.unreaded)
              .arg(info.status + UNREPLIED);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

QVector<QListWidgetItem> DataBase::getContacts()
{
    QSqlQuery query;
    if (!query.exec("SELECT login, status FROM contacts")) {
        qDebug() << "Unable to make select opeation" << query.lastError();
    }
    QVector<QListWidgetItem> contList;
    QSqlRecord rec = query.record();
    while(query.next()){
        QListWidgetItem item;

        item.setText(query.value(rec.indexOf("login")).toString());
        int status = query.value(rec.indexOf("status")).toInt();
        switch(status){
            case UNREPLIED: item.setBackgroundColor(Qt::gray); break;
            case DENIED: item.setBackgroundColor(Qt::red); break;
        }
        contList.push_back(std::move(item));
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

bool DataBase::clearContacts(){
    QSqlQuery query;
    QString str =  "DELETE FROM contacts;";
    if(!query.exec(str)){
        qDebug() << "Unable to make delete opeation" << query.lastError();
        return false;
    }
    str = "VACUUM;";
    query.exec(str);
    return true;
}

QString DataBase::getMessages(QString login){
    QString strF = "SELECT * FROM messages WHERE login = '%1' ORDER BY time DESC;";
    QString str = strF.arg(login);

    QSqlQuery query;

    if (!query.exec(str)) {
        qDebug() << "Unable to make select opeation" << query.lastError();
    }

    QSqlRecord rec = query.record();
    QString text;
    while(query.next()){
        QDateTime time = QDateTime::fromTime_t(query.value(rec.indexOf("time")).toInt(), Qt::LocalTime);
        text.append(time.toString("HH:mm") + " ");
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

int DataBase::getUid(QString login){
    QString strF = "SELECT * FROM contacts WHERE login = '%1';";
    QString str = strF.arg(login);
    QSqlQuery query;
    if(!query.exec(str)){
        qDebug() << "Unable to find contact" << login <<  query.lastError();
    }
    QSqlRecord rec = query.record();
    query.next();
    int uid = query.value(rec.indexOf("id")).toInt();
    qDebug() << uid;
    return uid;
}

int DataBase::lastTime(){
    QString str = "SELECT * FROM log WHERE type = 'update' ORDER BY value DESC;";
    QSqlQuery query;
    if(!query.exec(str)){
        qDebug() << "Unable to find last time" <<  query.lastError();
        return 0;
    }
    QSqlRecord rec = query.record();
    query.next();
    int time = query.value(rec.indexOf("value")).toInt();
    qDebug() << "last time" << time;
    return time;
}
