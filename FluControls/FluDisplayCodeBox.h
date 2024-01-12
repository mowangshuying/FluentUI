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

class FluDisplayCodeBox : public QTextEdit
{
    Q_OBJECT
  public:
    FluDisplayCodeBox(QWidget* parent = nullptr) : QTextEdit(parent)
    {
        auto hightLigher = new FluCppSyntaxHightLighter(document());
        setReadOnly(true);
        setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        setContextMenuPolicy(Qt::NoContextMenu);
        // setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFocusPolicy(Qt::FocusPolicy::NoFocus);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayCodeBox.qss", this);
    }

    void setCode(QString code)
    {
        setPlainText(code);
        // print height
        //LOG_DEBUG << "height:" << height() << "doc height:" << document()->height();
      //  setWordWrapMode(QTextOption::WrapMode::WordWrap);
     //   LOG_DEBUG << "1 - height:" << height();
     //   LOG_DEBUG << "line count" << document()->lineCount();

        //auto doc = document();
      //  document()->setTextWidth(viewport()->width());
     //   int newHeight = document()->size().height() + document()->documentMargin();
     //   setFixedHeight(newHeight);

       // LOG_DEBUG << "2 - height:" << height();

    }

    void resizeEvent(QResizeEvent*)
    {
       // LOG_DEBUG << "viewport width:" << viewport()->width();
        document()->setTextWidth(viewport()->width());
        int newHeight = document()->size().height() + document()->documentMargin();
        setFixedHeight(newHeight);
       // LOG_DEBUG << "height:" << height();
       // emit sizeChanged();
       // ((QWidget*)(parent()))->setFixedHeight(newHeight + 8);
    }

signals:
    void sizeChanged();
};
