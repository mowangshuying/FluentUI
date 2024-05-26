#pragma once

#include <QLabel>
#include <map>
#include "../FluUtils/FluUtils.h"
#include <QStyle>

class FluBorder : public QLabel
{
    Q_OBJECT
  public:
    FluBorder(QWidget* parent = nullptr) : QLabel(parent)
    {
        updateProperty("transparent", "1px", "transparent");
    }

    void updateProperty(QString bgColor, QString borderWidth, QString borderColor)
    {
        m_map["BackGroundColor"] = bgColor;
        m_map["BorderWith"] = borderWidth;
        m_map["BorderColor"] = borderColor;
        FluStyleSheetUitls::setQssByFileName(m_map, ":/StyleSheet/light/FluBorder.qss", this);
        style()->polish(this);
    }

    void setBackGroundColor(QColor bgColor)
    {
        QString str = QString::asprintf("rgb(%d,%d,%d)", bgColor.red(), bgColor.green(), bgColor.blue());
        updateProperty(str, m_map["BorderWith"], m_map["BorderColor"]);
    }

    void setBorderWidth(int width)
    {
        QString str = QString::asprintf("%dpx", width);
        updateProperty(m_map["BackGroundColor"], str, m_map["BorderColor"]);
    }

    void setBorderColor(QColor borderColor)
    {
        QString str = QString::asprintf("rgb(%d,%d,%d)", borderColor.red(), borderColor.green(), borderColor.blue());
        updateProperty(m_map["BackGroundColor"], m_map["BorderWith"], str);
    }

  protected:
    std::map<QString, QString> m_map;
};
