#pragma once

#include "FluLogUtils.h"
#include "FluThemeUtils.h"
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QMap>
#include <QString>
#include <map>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QPainterPath>
#include <QFileInfo>
#include <QDir>
#include <QGraphicsDropShadowEffect>

class FluStyleSheetUitls : public QObject
{
  private:
    FluStyleSheetUitls(QObject *object = nullptr);

  public:
    static QString getQssByFileName(const QString &fileName);
    static void setQssByFileName(const QString &fileName, QWidget *widget, bool bDebugQss = false);

    static QString getQssByFileName(const QString &jsonVars, const QString &fileName);
    static void setQssByFileName(const QString &jsonVar, const QString &fileName, QWidget *widget);

    static QString getQssByFileName(const std::map<QString, QString> &kvMap, const QString &fileName);
    static void setQssByFileName(const std::map<QString, QString> &kvMap, const QString &fileName, QWidget *widget);
    static void setQssByFileName(const std::map<QString, QString> &kvMap, const QString &fileName, QWidget *widget, FluTheme theme)
    {
        QString qssFileName = getUtils()->getStyleSheetDir() + FluThemeUtils::getThemeName() + "/" + fileName;
        setQssByFileName(kvMap, qssFileName, widget);
    }

    // dir/theme/filename
    static void setQssByFileName(const QString &filename, QWidget *widget, FluTheme theme)
    {
        QString qssFileName = getUtils()->getStyleSheetDir() + FluThemeUtils::getThemeName() + "/" + filename;
        setQssByFileName(qssFileName, widget);
    }

    static void replaceVar(const QString &jsonVars, QString &styleSheet);
    static void replaceVar(const std::map<QString, QString> &kvMap, QString &styleSheet);

    static void drawBottomLineIndicator(QWidget *widget, QPainter *painter);

    static void drawShadowEffect(QWidget *widget, int blurRadius, QPoint offset, QColor color);

    static void doForQrcQssText(QString &data);

    static FluStyleSheetUitls *getUtils();

    static QTimer *getTimer();

    static void __init();

    static void __deInit();

    void setStyleSheetDir(QString styleSheetDir);

    QString getStyleSheetDir();

    static bool isBatching();
    static void setBatching(bool on);
    static void applyBatchedUpdates();
    static void scheduleBatchUpdate(QWidget* widget, const QString& qss);

  protected:
    QString m_styleSheetDir;
    QTimer *m_timer;
    bool m_batching;
    QMap<QWidget*, QString> m_pendingUpdates;
    QMap<QWidget*, QString> m_lastAppliedQss;
    QTimer* m_batchTimer;
  private:
    static FluStyleSheetUitls *m_styleSheetUtils;
};
