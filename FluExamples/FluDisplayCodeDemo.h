#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QTextCharFormat>

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

class FluDisplayCodeDemo : public QPlainTextEdit
{
    Q_OBJECT
  public:
      FluDisplayCodeDemo(QWidget* parent = nullptr) : QPlainTextEdit(parent)
      {
          QString code = "std::cout << \"hello, world\" << std::endl; // this just a text";
          auto highlighter = new FluCppSyntaxHightLighter(document());

          setPlainText(code);
          setReadOnly(true);
          setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
          setContextMenuPolicy(Qt::NoContextMenu);
      }

};
