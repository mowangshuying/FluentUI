#pragma once

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QJsonArray>
#include <map>
#include "FluLogUtils.h"
#include <QString>

class FluStyleSheetUitls
{
  public:
    FluStyleSheetUitls()
    {
    }

    static QString getQssByFileName(const QString& fileName);
    static QString getQssByFileName(const QString& jsonVars, const QString& fileName);
    static QString getQssByFileName(const QMap<QString, QString> &kvMap,const QString& fileName);

    static void replaceVar(const QString& jsonVars, QString &styleSheet);
    static void replaceVar(const QMap<QString, QString> &kvMap, QString &styleSheet);
};
