#pragma once

#include "FluLogUtils.h"
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <map>
#include <QWidget>

class FluStyleSheetUitls : public QObject
{

 private:
    FluStyleSheetUitls(QObject *object = nullptr) : QObject(object)
    {

    }

  public:
    static QString getQssByFileName(const QString &fileName);
    static void setQssByFileName(const QString &fileName, QWidget *widget);

    static QString getQssByFileName(const QString &jsonVars, const QString &fileName);
    static void setQssByFileName(const QString &jsonVar, const QString &fileName, QWidget *widget);

    static QString getQssByFileName(const QMap<QString, QString> &kvMap, const QString &fileName);
    static void setQssByFileName(const QMap<QString, QString> &kvMap, const QString &fileName, QWidget *widget);

    static void replaceVar(const QString &jsonVars, QString &styleSheet);
    static void replaceVar(const QMap<QString, QString> &kvMap, QString &styleSheet);


    static FluStyleSheetUitls* getUtils()
    {
        if (m_styleSheetUtils == nullptr)
            m_styleSheetUtils = new FluStyleSheetUitls;
        return m_styleSheetUtils;
    }

    static void __init()
    {
        getUtils();
    }

    static void __deInit()
    {
        if (m_styleSheetUtils == nullptr)
            return;
        delete m_styleSheetUtils;
        m_styleSheetUtils = nullptr;
    }

 protected:
    QString m_styleSheetDir;

 private:
    static FluStyleSheetUitls *m_styleSheetUtils;
};
