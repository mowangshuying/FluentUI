#include "FluStyleSheetUitls.h"

FluStyleSheetUitls *FluStyleSheetUitls::m_styleSheetUtils = nullptr;
FluStyleSheetUitls::FluStyleSheetUitls(QObject *object /*= nullptr*/) : QObject(object)
{
    // #ifdef _DEBUG
    // m_timer = new QTimer;
    // m_timer->start(5000);
    // #endif
}

QString FluStyleSheetUitls::getQssByFileName(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QString qssStr = file.readAll();
        file.close();
        return qssStr;
    }

    return "";
}

void FluStyleSheetUitls::setQssByFileName(const QString &fileName, QWidget *widget)
{
    QString qss = FluStyleSheetUitls::getQssByFileName(fileName);
    if (widget != nullptr)
    {
        widget->setStyleSheet(qss);

        // just change file
        //  connect(FluStyleSheetUitls::getTimer(), &QTimer::timeout, [=]() {
        //      QString qss = FluStyleSheetUitls::getQssByFileName(fileName);
        //       widget->setStyleSheet(qss);
        //   });
    }
}

QString FluStyleSheetUitls::getQssByFileName(const QString &jsonVars, const QString &fileName)
{
    QString styleSheet = getQssByFileName(fileName);
    replaceVar(jsonVars, styleSheet);
    return styleSheet;
}

void FluStyleSheetUitls::setQssByFileName(const QString &jsonVar, const QString &fileName, QWidget *widget)
{
    QString qss = FluStyleSheetUitls::getQssByFileName(jsonVar, fileName);
    if (widget != nullptr)
    {
        widget->setStyleSheet(qss);
    }
}

QString FluStyleSheetUitls::getQssByFileName(const QMap<QString, QString> &kvMap, const QString &fileName)
{
    QString styleSheet = getQssByFileName(fileName);
    replaceVar(kvMap, styleSheet);
    return styleSheet;
}

void FluStyleSheetUitls::setQssByFileName(const QMap<QString, QString> &kvMap, const QString &fileName, QWidget *widget)
{
    QString qss = FluStyleSheetUitls::getQssByFileName(kvMap, fileName);
    if (widget != nullptr)
    {
        widget->setStyleSheet(qss);
    }
}

void FluStyleSheetUitls::replaceVar(const QString &jsonVars, QString &styleSheet)
{
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonVars.toUtf8(), &jsonError);

    QString jsonStr(jsonDoc.toJson());
    if (!jsonDoc.isArray())
    {
        LOG_ERR << jsonError.errorString();
        return;
    }
    //[{key:k1,value:v1},{key:k2,value:v2}]
    QMap<QString, QString> KVMap;
    QJsonArray jsonArray = jsonDoc.array();
    for (int i = 0; i < jsonArray.size(); i++)
    {
        QJsonValue jsonValue = jsonArray.at(i);
        if (!jsonValue.isObject())
            continue;

        QJsonObject jsonObject = jsonValue.toObject();
        QJsonValue keyJsonValue = jsonObject.take("key");
        QJsonValue valueJsonValue = jsonObject.take("value");
        if (keyJsonValue.isString() && valueJsonValue.isString())
        {
            KVMap[keyJsonValue.toString()] = valueJsonValue.toString();
        }
    }

    replaceVar(KVMap, styleSheet);
}

void FluStyleSheetUitls::replaceVar(const QMap<QString, QString> &kvMap, QString &styleSheet)
{
    for (auto itMap = kvMap.begin(); itMap != kvMap.end(); itMap++)
    {
        QString key = "[[" + itMap.key() + "]]";
        QString value = itMap.value();
        styleSheet.replace(key, value);
    }
}
