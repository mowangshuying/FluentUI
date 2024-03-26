#pragma once

#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QSettings>
#include <QRegularExpression>
#include "FluCppSHLRule.h"

// ref:QCodeEdit
#define FluIncludePattern QRegularExpression(R"(^\s*#\s*include\s*([<"][^:?"<>\|]+[">]))")
#define FluFunctionPattern QRegularExpression(R"(\b([_a-zA-Z][_a-zA-Z0-9]*\s+)?((?:[_a-zA-Z][_a-zA-Z0-9]*\s*::\s*)*[_a-zA-Z][_a-zA-Z0-9]*)(?=\s*\())")
#define FluDefinePattern QRegularExpression(R"(\b([_a-zA-Z][_a-zA-Z0-9]*)\s+[_a-zA-Z][_a-zA-Z0-9]*\s*[;=])")
#define FluCommentStartPattern QRegularExpression(R"(/\*)")
#define FluCommentEndPattern QRegularExpression(R"(\*/)")

 class FluCppSyntaxHightLighter : public QSyntaxHighlighter
{
   public:
     FluCppSyntaxHightLighter(QTextDocument* parent = nullptr) : QSyntaxHighlighter(parent)
     {
           loadKeysFromIni();
     }

     void loadKeysFromIni()
     {
           QSettings setting("../config/cpp.ini");
           auto groupList = setting.childGroups();

           std::vector<QString> keywords;
           for (auto group : groupList)
           {
               setting.beginGroup(group);
               auto allKeys = setting.allKeys();
               for (auto key : allKeys)
               {
                   keywords.push_back(setting.value(key).toString());
               }
               setting.endGroup();
           }

           for (auto keyword : keywords)
           {
               QRegularExpression pattern(QString::asprintf(R"(\b%1\b)", keyword));
           }
     }

     void appendHLRule(QColor color, QString pattern)
     {
         FluCppSHLRule rule(color, pattern);
         m_highlightingRules.append(rule);
     }

   protected:
     void highlightBlock(const QString& text) override
     {
         //for (auto rule : m_highlightingRules)
         //{
         //      auto iter = rule.getPattern().globalMatch(text);
         //      while (iter.hasNext())
         //      {
         //          auto match = iter.next();
         //          setFormat(match.capturedStart(), match.capturedLength(), rule.getFormat());
         //      }
         //}
     }

   protected:
     QList<FluCppSHLRule> m_highlightingRules;
 };