#pragma once

#include <QDebug>
#include <QFile>
#include <QMessageLogContext>
#include <QTextStream>
#include <QTime>
#include <qlogging.h>

// log format
// [time] [level] [file] [func] [line] [context]
class FluLogUtils
{
  public:
    enum LogLevel
    {
        Debug,
        Info,
        Waring,
        Err,
    };

  public:
    FluLogUtils()
    {
    }

    static void __init();
    static void __deinit();

    static QString getTime();
    static QString getFileName(const char *file);
    static void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

  public:
    static QFile *gFileLog;
    static QtMessageHandler gDefaultHandler;
};

#define LOG_FUNC LOG_DEBUG << ";";
#define LOG_DEBUG                                                                    \
    qDebug().nospace() << "[" << FluLogUtils::getTime().toStdString().c_str() << "]" \
                       << "["                                                        \
                       << "debug"                                                    \
                       << "]"                                                        \
                       << "[" << FluLogUtils::getFileName(__FILE__).toStdString().c_str() << "][" << __FUNCTION__ << "][" << __LINE__ << "] "

#define LOG_INFO                                                                     \
    qInfo().nospace() << "[" << FluLogUtils::getTime().toStdString().c_str() << "]" \
                       << "["                                                        \
                       << "info"                                                     \
                       << "]"                                                        \
                       << "[" << FluLogUtils::getFileName(__FILE__).toStdString().c_str() << "][" << __FUNCTION__ << "][" << __LINE__ << "] "

#define LOG_WARN                                                                     \
    qWarning().nospace() << "[" << FluLogUtils::getTime().toStdString().c_str() << "]" \
                       << "["                                                        \
                       << "warn"                                                     \
                       << "]"                                                        \
                       << "[" << FluLogUtils::getFileName(__FILE__).toStdString().c_str() << "][" << __FUNCTION__ << "][" << __LINE__ << "] "

#define LOG_ERR                                                                      \
    qDebug().nospace() << "[" << FluLogUtils::getTime().toStdString().c_str() << "]" \
                       << "["                                                        \
                       << "err"                                                      \
                       << "]"                                                        \
                       << "[" << FluLogUtils::getFileName(__FILE__).toStdString().c_str() << "][" << __FUNCTION__ << "][" << __LINE__ << "] "
