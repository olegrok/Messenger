#include "database.h"

#define SEND    70001
#define RECIVE  70002

int timesDiff(QDateTime& first, QDateTime& second) {
    return qAbs(first.time().hour() * 60 + first.time().minute()
            -second.time().hour() * 60 - second.time().minute());
}


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

bool DataBase::addMessage(msgCont msg, msg_status status)
{
    QSqlQuery query;
    QString strF =
          "INSERT INTO  messages (login, text, time, status) "
          "VALUES('%1', '%2', %3, %4);";

    QString str = strF.arg(msg.login)
            .arg(msg.text)
            .arg(msg.time)
            .arg((status == msg_status::sended) ? SEND : RECIVE);

    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }

    strF = "UPDATE contacts SET unreaded = %1 WHERE login = '%2';";
    str = strF.arg(DataBase::hasUnreaded(msg.login) + 1)
              .arg(msg.login);
    if(!query.exec(str)){
        qDebug() << "Unable to make update operation" <<  query.lastError();
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
    QString str = strF
              .arg(info.uid)
              .arg(info.login)
              .arg(info.lastMsgId)
              .arg(info.unreaded)
              .arg(info.status);
    if (!query.exec(str)) {
        qDebug() << "Unable to make insert opeation" << query.lastError();
        return false;
    }
    return true;
}

QVector<QListWidgetItem*> DataBase::getContacts(QString login)
{
    QSqlQuery query;
    QString strF = "SELECT login, status FROM contacts WHERE login LIKE '%1%';";
    QString str = strF.arg(login);
    qDebug() << "SQLrequest:" << str;
    if (!query.exec(str)) {
        qDebug() << "Unable to make select opeation" << query.lastError();
    }
    QVector<QListWidgetItem*> contList;
    QSqlRecord rec = query.record();
    while(query.next()){
        QListWidgetItem* item = new QListWidgetItem;

        item->setText(query.value(rec.indexOf("login")).toString());
        int status = query.value(rec.indexOf("status")).toInt();
        QFont font;
        font.setBold(true);
        switch(status){
            case static_cast<int>(contact_status::requested_to):
                item->setFont(font);
            case static_cast<int>(contact_status::requested_from):
                item->setBackgroundColor(Qt::gray); break;
            case static_cast<int>(contact_status::denied):
                item->setBackgroundColor(Qt::red); break;
        }
        contList.push_back(item);
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

QString DataBase::getMessages(QString login, QString strToFind){
    QString strF = "SELECT * FROM messages WHERE login = '%1' "
                   "AND text LIKE '%%2%' ORDER BY time ASC;";
    QString str = strF.arg(login)
                      .arg(strToFind);

    QSqlQuery query;

    if (!query.exec(str)) {
        qDebug() << "Unable to make select opeation" << query.lastError();
    }

    QString myLogin = "Me";

    QSqlRecord rec = query.record();
    QString text;
    QDateTime prev;
    int lastSender = -1;
    while(query.next()){
        QDateTime time = QDateTime::fromTime_t(query.value(rec.indexOf("time")).toInt(), Qt::LocalTime);
        int diff = timesDiff(prev, time);
        text.append("<i><p align=\"center\">" +
                    ((time.date() != QDate::currentDate() && diff) ?
                         time.date().toString("dd.MM ") : QString())
                    + (diff ? time.time().toString("HH:mm") : QString())
                    + "</p></i>");
        if(query.value(rec.indexOf("status")).toInt() == SEND){
                text.append("<p align=\"right\">" +
                            (lastSender != 0 || diff ?
                            ("<b>" + myLogin + ": </b><BR>") : QString()));
                lastSender = 0;
        }

        else{
            int senderUid = DataBase::getUid(login);
                text.append("<p align=\"left\">" +
                            (lastSender != senderUid || diff ?
                            ("<b>" + login + ": </b><BR>") : QString()));
                lastSender = senderUid;
        }
        text.append( query.value(rec.indexOf("text")).toString().toHtmlEscaped()
                     .replace("\n", "<BR>") + "</p>");
        prev = time;
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
    query.next();
    int uid = query.value(query.record().indexOf("id")).toInt();
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

    query.next();
    int time = query.value(query.record().indexOf("value")).toInt();
    qDebug() << "last time" << time;
    return time;
}

int DataBase::hasUnreaded(QString login){
    QString strF = "SELECT unreaded FROM contacts WHERE login = '%1';";
    QString str = strF.arg(login);
    QSqlQuery query;
    if(!query.exec(str)){
        qDebug() << "Unable to find contact" << login <<  query.lastError();
        return -1;
    }
    query.next();
    return query.value(query.record().indexOf("unreaded")).toInt();
}

void DataBase::makeViewed(QString& login){
    QString strF = "UPDATE contacts SET unreaded = 0 WHERE login = '%1';";
    QString str = strF.arg(login);
    QSqlQuery query;
    if(!query.exec(str)){
        qDebug() << "Unable to make update operation" <<  query.lastError();
    }
}

bool DataBase::changeContactStatus(QString login, contact_status newStatus){
    QString strF = "UPDATE contacts SET status = %1 WHERE login = '%2';";
    QString str = strF.arg(static_cast<int>(newStatus))
                      .arg(login);
    QSqlQuery query;
    if(!query.exec(str)){
        qDebug() << "Unable to make update operation" <<  query.lastError();
        return false;
    }
    return true;
}

int DataBase::getStatus(QString login){
    QString str = QString("SELECT status FROM contacts WHERE login = '%1';").arg(login);
    QSqlQuery query;
    if(!query.exec(str)){
        qDebug() << "Unable to find status" <<  query.lastError();
        return 0;
    }
    query.next();
    return query.value(query.record().indexOf("status")).toInt();
}
