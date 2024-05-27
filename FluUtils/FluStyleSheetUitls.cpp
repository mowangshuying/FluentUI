#include "FluStyleSheetUitls.h"

FluStyleSheetUitls *FluStyleSheetUitls::m_styleSheetUtils = nullptr;
FluStyleSheetUitls::FluStyleSheetUitls(QObject *object /*= nullptr*/) : QObject(object)
{
    // #ifdef _DEBUG_QSS
    m_timer = new QTimer;
    m_timer->start(5000);
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

void FluStyleSheetUitls::setQssByFileName(const QString &fileName, QWidget *widget, bool bDebugQss)
{
#if (defined Q_OS_WIN) && (defined _DEBUG)
    QString qssFileName = fileName;
    qssFileName.replace(":", "..");
    QString qss = FluStyleSheetUitls::getQssByFileName(qssFileName);
#else
    QString qss = FluStyleSheetUitls::getQssByFileName(fileName);
#endif
    if (widget != nullptr)
    {
        widget->setStyleSheet(qss);

        // if (bDebugQss)
        //{
        //     // just change file
        //     connect(FluStyleSheetUitls::getTimer(), &QTimer::timeout, [=]() {
        //         QString qss = FluStyleSheetUitls::getQssByFileName(fileName);
        //         widget->setStyleSheet(qss);
        //     });
        // }
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

QString FluStyleSheetUitls::getQssByFileName(const std::map<QString, QString> &kvMap, const QString &fileName)
{
    QString styleSheet = getQssByFileName(fileName);
    replaceVar(kvMap, styleSheet);
    return styleSheet;
}

void FluStyleSheetUitls::setQssByFileName(const std::map<QString, QString> &kvMap, const QString &fileName, QWidget *widget)
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
    std::map<QString, QString> KVMap;
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

void FluStyleSheetUitls::replaceVar(const std::map<QString, QString> &kvMap, QString &styleSheet)
{
    for (auto itMap = kvMap.begin(); itMap != kvMap.end(); itMap++)
    {
        QString key = "[[" + itMap->first + "]]";
        QString value = itMap->second;
        styleSheet.replace(key, value);
    }
}
