#ifndef JSONPROTOCOL_H
#define JSONPROTOCOL_H

#include <QVector>
#include <QPair>
#include <cpprest/json.h>
#include <algorithm>
#include <QString>
#include <QDebug>

/*class JsonProtocol
{
public:
    JsonProtocol();
};*/
using namespace web;

namespace JsonProtocol{
    QVector < QPair<QString, int> > contactListParser(json::value json);
}

#endif // JSONPROTOCOL_H
