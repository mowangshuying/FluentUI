#pragma once


#include <QString>
#include <QRegularExpression>
#include <QTextBlockFormat>

class FluCppSHLRule
{
  public:
    FluCppSHLRule(QColor color, QString pattern)
    {
        QTextCharFormat commentFormat;
        commentFormat.setForeground(color);
        m_pattern = QRegularExpression(pattern);
        m_format = commentFormat;
    }

    QRegularExpression getPattern()
    {
        return m_pattern;
    }

    QTextCharFormat getFormat()
    {
        return m_format;
    }

  protected:
    QRegularExpression m_pattern;
    QTextCharFormat m_format;
};