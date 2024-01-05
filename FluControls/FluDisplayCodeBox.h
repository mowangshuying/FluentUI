#pragma once

#include <QPlainTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QSyntaxHighlighter>

class FluCppSHLRule
{
  public:
    QRegularExpression pattern;
    QTextCharFormat format;
};

class FluCppSyntaxHightLighter : public QSyntaxHighlighter
{
  public:
    FluCppSyntaxHightLighter(QTextDocument* parent = nullptr) : QSyntaxHighlighter(parent)
    {
        newARuleToRules(QColor(87, 166, 74), "//[^n]*");
        newARuleToRules(QColor(86, 156, 214), "\\bauto\\b");
        newARuleToRules(QColor(86, 156, 214), "\\bnew\\b");
        newARuleToRules(QColor(255, 215, 0), "\\bFluLabel\\b");
        newARuleToRules(QColor(255, 215, 0), "\\bFluLabelStyle\\b");
        newARuleToRules(QColor(185, 119, 30), "\\bCaptionTextBlockSylte\\b");
        newARuleToRules(QColor(255, 128, 0), "\\bsetStyle\\b");
        // newARuleToRules(Qt::blue, "\\bendl\\b");
    }

    void newARuleToRules(QColor color, QString pattern)
    {
        FluCppSHLRule rule;
        QTextCharFormat commentFormat;
        commentFormat.setForeground(color);
        rule.pattern = QRegularExpression(pattern);
        rule.format = commentFormat;
        m_highlightingRules.append(rule);
    }

  protected:
    void highlightBlock(const QString& text) override
    {
        for (auto rule : m_highlightingRules)
        {
            auto iter = rule.pattern.globalMatch(text);
            while (iter.hasNext())
            {
                auto match = iter.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }

  protected:
    QList<FluCppSHLRule> m_highlightingRules;
};

class FluDisplayCodeBox : public QPlainTextEdit
{
    Q_OBJECT
  public:
    FluDisplayCodeBox(QWidget* parent = nullptr) : QPlainTextEdit(parent)
    {
        auto hightLigher = new FluCppSyntaxHightLighter(document());
        setReadOnly(true);
        setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        setContextMenuPolicy(Qt::NoContextMenu);
        // setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFocusPolicy(Qt::FocusPolicy::NoFocus);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayCodeBox.qss", this);
    }

    void setCode(QString code)
    {
        setPlainText(code);
    }
};
