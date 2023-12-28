#pragma once

#include "FluLogUtils.h"
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <map>

class FluStyleSheetUitls
{
  public:
    FluStyleSheetUitls()
    {
    }

    static QString getQssByFileName(const QString &fileName);
    static QString getQssByFileName(const QString &jsonVars, const QString &fileName);
    static QString getQssByFileName(const QMap<QString, QString> &kvMap, const QString &fileName);

    static void replaceVar(const QString &jsonVars, QString &styleSheet);
    static void replaceVar(const QMap<QString, QString> &kvMap, QString &styleSheet);
};
