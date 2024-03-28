#pragma once


#include <QString>
#include <QRegularExpression>
#include <QTextBlockFormat>

class FluCppSHLRule
{
  public:
    FluCppSHLRule(QString key, QString pattern)
    {
        m_key = key;
        m_pattern = QRegularExpression(pattern);
    }

    QRegularExpression getPattern()
    {
        return m_pattern;
    }

    void setPattern(QRegularExpression pattern)
    {
        m_pattern = pattern;
    }

    QString getKey()
    {
        return m_key;
    }

    void setKey(QString key)
    {
        m_key = key;
    }

  protected:
    QString m_key;
    QRegularExpression m_pattern;
  // QTextCharFormat m_format;
};