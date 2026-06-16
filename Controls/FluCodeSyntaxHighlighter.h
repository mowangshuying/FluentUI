#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>


class FluCodeSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT


public:
    explicit FluCodeSyntaxHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    class HighlightingRule
    {
      public:
          HighlightingRule(QRegularExpression p, QTextCharFormat f)
          {
              pattern = p;
              format = f;
          }
     public:
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;  // 用于Qt类名和Flu自定义类名
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat numberFormat;
    
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
};