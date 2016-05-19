#ifndef MONITOR_H
#define MONITOR_H
#include <QMetaType>
#include <QThread>
#include <cpprest/json.h>
#include "structsforrequests.h"
#include "database.h"
#include <cpprest/http_client.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;

Q_DECLARE_METATYPE(QVector<msgCont>)
Q_DECLARE_METATYPE(web::json::value)

class Monitor : public QThread{
    Q_OBJECT
public:
    Monitor() {}
    ~Monitor() {}
    void setSession(int cookie, int uid, QString& ServerURL_);
    void setSession(json::value& session_, QString& ServerURL_);
    void run() Q_DECL_OVERRIDE;
    json::value monitor();
signals:
    void task(web::json::value json);
    void authorizationError(QString status = 0);
public slots:
    void quit(){ qDebug() << "end";}
private:
    json::value session;
    QString ServerURL;

};

#endif // MONITOR_H
