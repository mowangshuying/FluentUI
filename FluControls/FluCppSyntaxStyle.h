#pragma once

#include <QObject>
#include <QXmlStreamReader>
#include <QTextCharFormat>
#include "../FluUtils/FluUtils.h"

// ref:QSyntaxStyle
class FluCppSyntaxStyle : public QObject
{
    Q_OBJECT
  public:
      FluCppSyntaxStyle(QObject* parent = nullptr) : QObject(parent)
      {

      }

      bool loadXml(QString xmlFile)
      {
          QXmlStreamReader reader(xmlFile);
          while (!reader.atEnd() && !reader.hasError())
          {
              auto tokenType = reader.readNext();
              if (tokenType != QXmlStreamReader::StartElement)
              {
                  continue;
              }

              if (reader.name().toString() == "style-scheme")
              {
                  if (reader.attributes().hasAttribute("name"))
                  {
                      m_name = reader.attributes().value("name").toString();
                  }

                  continue;
              }

              if (reader.name().toString() == "style")
              {
                  auto attributes = reader.attributes();
                  auto name = attributes.value("name");

                  QTextCharFormat format;
                  if (attributes.hasAttribute("background"))
                  {
                      format.setBackground(QColor(attributes.value("background").toString()));
                  }

                  if (attributes.hasAttribute("foreground"))
                  {
                      format.setForeground(QColor(attributes.value("foreground").toString()));
                  }

                  if (attributes.hasAttribute("bold") && attributes.value("bold").toString() == "true")
                  {
                      format.setFontWeight(QFont::Weight::Bold);
                  }

                  if (attributes.hasAttribute("italic") && attributes.value("italic").toString() == "true")
                  {
                      format.setFontItalic(true);
                  }

                  if (attributes.hasAttribute("underlineStyle"))
                  {
                      auto underline = attributes.value("underlineStyle");

                      auto lineStyle = QTextCharFormat::UnderlineStyle::NoUnderline;
                      if (underline.toString() == "SingleUnderline")
                      {
                          lineStyle = QTextCharFormat::UnderlineStyle::SingleUnderline;
                      }
                      else if (underline.toString() == "DashUnderline")
                      {
                          lineStyle = QTextCharFormat::UnderlineStyle::DashUnderline;
                      }
                      else if (underline.toString() == "DotLine")
                      {
                          lineStyle = QTextCharFormat::UnderlineStyle::DotLine;
                      }
                      else if (underline.toString() == "DashDotLine")
                      {
                          lineStyle = QTextCharFormat::DashDotLine;
                      }
                      else if (underline.toString() == "DashDotDotLine")
                      {
                          lineStyle = QTextCharFormat::DashDotDotLine;
                      }
                      else if (underline.toString() == "WaveUnderline")
                      {
                          lineStyle = QTextCharFormat::WaveUnderline;
                      }
                      else if (underline.toString() == "SpellCheckUnderline")
                      {
                          lineStyle = QTextCharFormat::SpellCheckUnderline;
                      }
                      else
                      {
                          LOG_DEBUG << "Unknown underline value " << underline;
                      }

                      format.setUnderlineStyle(lineStyle);
                  }

                  m_formats[name.toString()] = format;
              }


          }

          return !reader.hasError();
      }

      QString getName()
      {
          return m_name;
      }

      QTextCharFormat getFormat(QString name)
      {
          auto itf = m_formats.find(name);
          if (itf == m_formats.end())
          {
              return QTextCharFormat();
          }

          return itf->second;
      }

  protected:
      QString m_name;
      std::map<QString, QTextCharFormat> m_formats;

};
