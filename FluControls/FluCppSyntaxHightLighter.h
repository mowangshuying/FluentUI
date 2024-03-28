#pragma once

#include <QTextDocument>
#include <QSyntaxHighlighter>
#include <QSettings>
#include <QRegularExpression>
#include "FluCppSHLRule.h"
#include "../FluUtils/FluUtils.h"
#include <QXmlStreamReader>
#include "FluCppSyntaxStyle.h"

// ref:QCodeEdit can find it at github.
 class FluCppSyntaxHightLighter : public QSyntaxHighlighter
{
   public:
    FluCppSyntaxHightLighter(QTextDocument* parent = nullptr) : QSyntaxHighlighter(parent), m_cppSyntaxStyle(nullptr)
     {
           loadKeysFromXml();
            appendHLRule(
             "Number",
             R"((?<=\b|\s|^)(?i)(?:(?:(?:(?:(?:\d+(?:'\d+)*)?\.(?:\d+(?:'\d+)*)(?:e[+-]?(?:\d+(?:'\d+)*))?)|(?:(?:\d+(?:'\d+)*)\.(?:e[+-]?(?:\d+(?:'\d+)*))?)|(?:(?:\d+(?:'\d+)*)(?:e[+-]?(?:\d+(?:'\d+)*)))|(?:0x(?:[0-9a-f]+(?:'[0-9a-f]+)*)?\.(?:[0-9a-f]+(?:'[0-9a-f]+)*)(?:p[+-]?(?:\d+(?:'\d+)*)))|(?:0x(?:[0-9a-f]+(?:'[0-9a-f]+)*)\.?(?:p[+-]?(?:\d+(?:'\d+)*))))[lf]?)|(?:(?:(?:[1-9]\d*(?:'\d+)*)|(?:0[0-7]*(?:'[0-7]+)*)|(?:0x[0-9a-f]+(?:'[0-9a-f]+)*)|(?:0b[01]+(?:'[01]+)*))(?:u?l{0,2}|l{0,2}u?)))(?=\b|\s|$))");

            appendHLRule("String", R"("[^\n"]*")");
            appendHLRule("Preprocessor", R"(#[a-zA-Z_]+)");
            appendHLRule("Comment", R"(//[^\n]*)");
     }


     void loadKeysFromXml()
     {
           QFile file("../config/cpp.xml");
           if (!file.open(QIODevice::ReadOnly))
           {
               LOG_ERR << "can't open cpp.xml file.";
               return;
           }


           bool bReadText = false;
           QString name;
           std::map<QString, std::vector<QString>> listMap;

           QXmlStreamReader reader(&file);
           while (!reader.atEnd() && !reader.hasError())
           {
               auto tokenType = reader.readNext();
               if (tokenType == QXmlStreamReader::StartElement)
               {
                   if (reader.name().toString() == "section")
                   {
                       name = reader.attributes().value("name").toString();
                       std::vector<QString> list;
                       listMap[name] = list;
                   }
                   else if (reader.name().toString() == "name")
                   {
                       bReadText = true;
                   }
               }
               else if (tokenType == QXmlStreamReader::Characters && bReadText)
               {
                   listMap[name].push_back(reader.text().toString());
                   bReadText = false;
               }
           }

           for (auto itMap = listMap.begin(); itMap != listMap.end(); itMap++)
           {
               for (auto itVct = itMap->second.begin(); itVct != itMap->second.end(); itVct++)
               {
                   appendHLRule(itMap->first, QString::asprintf(R"(\b%1\b)").arg(*itVct));
               }
           }

     }

     void setCppSyntaxStyle(FluCppSyntaxStyle* cppSyntaxStyle)
     {
           m_cppSyntaxStyle = cppSyntaxStyle;
     }

     FluCppSyntaxStyle* getCppSyntaxStyle()
     {
           return m_cppSyntaxStyle;
     }

     void appendHLRule(QString key, QString pattern)
     {
         FluCppSHLRule rule(key, pattern);
         m_highlightRules.push_back(rule);
     }

   protected:


     void highlightBlock(const QString& text) override
     {
         QRegularExpression pattern;
         QRegularExpressionMatchIterator matchIter;

         // the include.
         pattern = QRegularExpression(R"(^\s*#\s*include\s*([<"][^:?"<>\|]+[">]))");
         matchIter = pattern.globalMatch(text);
         while (matchIter.hasNext())
         {
               auto match = matchIter.next();
               setFormat(match.capturedStart(), match.capturedLength(), m_cppSyntaxStyle->getFormat("Preprocessor"));
               setFormat(match.capturedStart(1), match.capturedLength(1), m_cppSyntaxStyle->getFormat("String"));
         }

         // the func.
         pattern = QRegularExpression(R"(\b([_a-zA-Z][_a-zA-Z0-9]*\s+)?((?:[_a-zA-Z][_a-zA-Z0-9]*\s*::\s*)*[_a-zA-Z][_a-zA-Z0-9]*)(?=\s*\())");
         matchIter = pattern.globalMatch(text);
         while (matchIter.hasNext())
         {
               auto match = matchIter.next();
               setFormat(match.capturedStart(), match.capturedLength(), m_cppSyntaxStyle->getFormat("Type"));
               setFormat(match.capturedStart(2), match.capturedLength(2), m_cppSyntaxStyle->getFormat("Function"));
         }

         // the define.
         pattern = QRegularExpression(R"(\b([_a-zA-Z][_a-zA-Z0-9]*)\s+[_a-zA-Z][_a-zA-Z0-9]*\s*[;=])");
         matchIter = pattern.globalMatch(text);
         while (matchIter.hasNext())
         {
               auto match = matchIter.next();
               setFormat(match.capturedStart(1), match.capturedLength(1), m_cppSyntaxStyle->getFormat("Type"));
         }

         // the key words.
         for (auto rule : m_highlightRules)
         {
               matchIter = rule.getPattern().globalMatch(text);
               while (matchIter.hasNext())
               {
                   auto match = matchIter.next();
                   setFormat(match.capturedStart(), match.capturedLength(), m_cppSyntaxStyle->getFormat(rule.getKey()));
               }
         }

         // the comment.
     }

   protected:
     std::vector<FluCppSHLRule> m_highlightRules;
     FluCppSyntaxStyle* m_cppSyntaxStyle;
 };