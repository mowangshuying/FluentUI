#include "FluStyleSheetUitls.h"
#include <QApplication>

FluStyleSheetUitls *FluStyleSheetUitls::m_styleSheetUtils = nullptr;
FluStyleSheetUitls::FluStyleSheetUitls(QObject *object /*= nullptr*/) : QObject(object)
{
    m_timer = new QTimer;
    m_timer->start(5000);
    m_batching = false;
    m_batchTimer = new QTimer(this);
    m_batchTimer->setSingleShot(true);
    connect(m_batchTimer, &QTimer::timeout, this, []() { applyBatchedUpdates(); });
    m_styleSheetDir = "../StyleSheet/";
#ifdef USE_QRC
    m_styleSheetDir = ":/StyleSheet/";
#endif
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
    LOG_ERR << "open qss file failed: " << fileName;
    return "";
}

void FluStyleSheetUitls::setQssByFileName(const QString &fileName, QWidget *widget, bool bDebugQss)
{
    QString qss = FluStyleSheetUitls::getQssByFileName(fileName);

#ifdef USE_QRC
    doForQrcQssText(qss);
#endif

    if (widget != nullptr)
    {
        scheduleBatchUpdate(widget, qss);
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
        scheduleBatchUpdate(widget, qss);
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
        scheduleBatchUpdate(widget, qss);
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

void FluStyleSheetUitls::drawBottomLineIndicator(QWidget *widget, QPainter *painter)
{
    painter->setPen(Qt::NoPen);
    painter->setRenderHints(QPainter::Antialiasing);

    QMargins margins = widget->contentsMargins();

    int nW = widget->width() - (margins.left() + margins.right());
    int nH = widget->height();

    QPainterPath path;
    path.addRoundedRect(QRectF(margins.left(), nH - 10, nW - margins.right(), 10), 5, 5);

    QPainterPath clipPath;
    clipPath.addRect(margins.left(), nH - 10, nW - margins.right(), 7);
    path = path.subtracted(clipPath);

    QBrush brush;
    if (FluThemeUtils::isLightTheme())
    {
        brush = QBrush(QColor(0, 90, 158));
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        brush = QBrush(QColor(118, 185, 237));
    }
    else if (FluThemeUtils::isAtomOneDarkTheme())
    {
        brush = QBrush(QColor(82, 139, 255));
    }

    painter->fillPath(path, brush);
}

void FluStyleSheetUitls::drawShadowEffect(QWidget *widget, int blurRadius, QPoint offset, QColor color)
{
    auto shadowEffect = new QGraphicsDropShadowEffect(widget);
    shadowEffect->setBlurRadius(blurRadius);
    shadowEffect->setOffset(offset);
    shadowEffect->setColor(color);
    widget->setGraphicsEffect(nullptr);
    widget->setGraphicsEffect(shadowEffect);
}

void FluStyleSheetUitls::doForQrcQssText(QString &data)
{
    data.replace("../res/", ":/res/");
}

FluStyleSheetUitls *FluStyleSheetUitls::getUtils()
{
    if (m_styleSheetUtils == nullptr)
        m_styleSheetUtils = new FluStyleSheetUitls;
    return m_styleSheetUtils;
}

QTimer *FluStyleSheetUitls::getTimer()
{
    return FluStyleSheetUitls::getUtils()->m_timer;
}

void FluStyleSheetUitls::__init()
{
    getUtils();
    FluStyleSheetUitls::getUtils()->setStyleSheetDir("../StyleSheet/light/");
}

void FluStyleSheetUitls::__deInit()
{
    if (m_styleSheetUtils == nullptr)
        return;
    delete m_styleSheetUtils;
    m_styleSheetUtils = nullptr;
}

void FluStyleSheetUitls::setStyleSheetDir(QString styleSheetDir)
{
    m_styleSheetDir = styleSheetDir;
}

QString FluStyleSheetUitls::getStyleSheetDir()
{
    return m_styleSheetDir;
}

bool FluStyleSheetUitls::isBatching()
{
    return getUtils()->m_batching;
}

void FluStyleSheetUitls::setBatching(bool on)
{
    getUtils()->m_batching = on;
}

void FluStyleSheetUitls::scheduleBatchUpdate(QWidget *widget, const QString &qss)
{
    FluStyleSheetUitls *inst = getUtils();
    if (!widget)
        return;

    if (inst->m_batching)
    {
        QMap<QWidget*, QString>::const_iterator it = inst->m_lastAppliedQss.constFind(widget);
        if (it != inst->m_lastAppliedQss.constEnd() && it.value() == qss)
            return;

        inst->m_pendingUpdates[widget] = qss;
    }
    else
    {
        widget->setStyleSheet(qss);
        inst->m_lastAppliedQss[widget] = qss;
    }
}

void FluStyleSheetUitls::applyBatchedUpdates()
{
    FluStyleSheetUitls *inst = getUtils();
    if (inst->m_pendingUpdates.isEmpty())
        return;

    QWidget *activeWindow = qApp->activeWindow();
    if (activeWindow)
        activeWindow->setUpdatesEnabled(false);

    QMap<QWidget*, QString> updates = inst->m_pendingUpdates;
    inst->m_pendingUpdates.clear();

    for (auto it = updates.begin(); it != updates.end(); ++it)
    {
        QWidget *w = it.key();
        if (!w)
            continue;

        if (!w->isVisible())
        {
            inst->m_lastAppliedQss[w] = it.value();
            continue;
        }

        w->setStyleSheet(it.value());
        inst->m_lastAppliedQss[w] = it.value();
    }

    if (activeWindow)
    {
        activeWindow->setUpdatesEnabled(true);
        activeWindow->update();
    }
}
