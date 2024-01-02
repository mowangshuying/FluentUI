#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

#include "../FluUtils/FluUtils.h"

class FluCppSyntaxHightLighterRule
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
          newARuleToRules(Qt::darkGreen, "//[^n]*");
          newARuleToRules(Qt::blue, "\\bstd\\b");
          newARuleToRules(Qt::blue, "\\bcout\\b");
          newARuleToRules(Qt::blue, "\\bendl\\b");
      }

      void newARuleToRules(QColor color, QString pattern)
      {
          FluCppSyntaxHightLighterRule rule;
          QTextCharFormat commentFormat;
          commentFormat.setForeground(color);
          rule.pattern = QRegularExpression(pattern);
          rule.format = commentFormat;
          m_highlightingRules.append(rule);
      }

    protected:
        void highlightBlock(const QString& text) override
        {
          for (auto rule :  m_highlightingRules)
          {
              QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
              while (matchIterator.hasNext())
              {
                  QRegularExpressionMatch match = matchIterator.next();
                  setFormat(match.capturedStart(), match.capturedLength(), rule.format);
              }
          }
        }
  protected:
      QList<FluCppSyntaxHightLighterRule> m_highlightingRules;
};

class FluDisplayCodeDemo : public QWidget
{
    Q_OBJECT
  public:
      FluDisplayCodeDemo(QWidget* parent = nullptr) : QWidget(parent)
      {

          auto display = new QPlainTextEdit(this);
          display->setFixedSize(300, 50);
          display->move(50, 50);

          QString code = "std::cout << \"hello, world\" << std::endl; // this just a text";
          auto highlighter = new FluCppSyntaxHightLighter(display->document());

          display->setPlainText(code);
          display->setReadOnly(true);
          display->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
          display->setContextMenuPolicy(Qt::NoContextMenu);

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluDisplayCodeDemo.qss", this);
      }

};
