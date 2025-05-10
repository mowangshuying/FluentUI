#pragma once

#include "FluLogUtils.h"
#include "FluThemeUtils.h"
#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <map>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QWidget>
#include <QPainterPath>
#include <QFileInfo>
#include <QDir>

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
#ifdef _DEBUG
        // log styleSheetDir;
        // QString absolutePath = QDir(m_styleSheetDir).absolutePath();
        // LOG_DEBUG << "styleSheetDir: " << absolutePath;
#endif

        QString qssFileName = getUtils()->getStyleSheetDir() + FluThemeUtils::getThemeName() + "/" + filename;
        setQssByFileName(qssFileName, widget);
    }

    static void replaceVar(const QString &jsonVars, QString &styleSheet);
    static void replaceVar(const std::map<QString, QString> &kvMap, QString &styleSheet);

    static void drawBottomLineIndicator(QWidget *widget, QPainter *painter);

    static void doForQrcQssText(QString &data);

    static FluStyleSheetUitls *getUtils();

    // #ifdef _DEBUG_QSS
    static QTimer *getTimer();
    // #endif

    static void __init();

    static void __deInit();

    void setStyleSheetDir(QString styleSheetDir);

    QString getStyleSheetDir();

  protected:
    QString m_styleSheetDir;
    // #ifdef _DEBUG_QSS
    //   update stylesheet by timer
    QTimer *m_timer;
    // #endif
  private:
    static FluStyleSheetUitls *m_styleSheetUtils;
};
