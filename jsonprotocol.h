#ifndef JSONPROTOCOL_H
#define JSONPROTOCOL_H

#include <QVector>
#include <QPair>
#include <cpprest/json.h>
#include <algorithm>
#include <QString>
#include <QDebug>
#include <QObject>
#include <utility>
#include "structsforrequests.h"
#include "database.h"

using namespace web;

class JsonProtocol : public QObject
{
    Q_OBJECT
public:
    explicit JsonProtocol();
    ~JsonProtocol();
    void eventsParser(json::value json);
    QVector <contInfo> contactListParser(json::value json);
private:
    QVector <msgCont>  msgEventParser(json::value json);
    QVector <contInfo> contactEventParser(json::value json);

signals:
    void messagesPack(QVector <msgCont>);
    void contactEventsPack(QVector <contInfo>);
};

#endif // JSONPROTOCOL_H
