#ifndef JSONPROTOCOL_H
#define JSONPROTOCOL_H

#include <QVector>
#include <QPair>
#include <cpprest/json.h>
#include <algorithm>
#include <QString>
#include <QDebug>
#include <QObject>
#include "structsforrequests.h"
#include "database.h"

using namespace web;

class JsonProtocol : public QObject
{
    Q_OBJECT
public:
    explicit JsonProtocol();
    ~JsonProtocol();

//namespace JsonProtocol{
    QVector < QPair<QString, int> > contactListParser(json::value json);
   void eventsParser(json::value json);
signals:
    void messagesPack(QVector <msgCont>);
};

#endif // JSONPROTOCOL_H
