#include "FluBorder.h"

FluBorder::FluBorder(QWidget* parent /*= nullptr*/) : QLabel(parent)
{
    if (FluThemeUtils::isLightTheme())
        updateProperty("black", "transparent", "1px", "transparent");
    else
        updateProperty("white", "transparent", "1px", "transparent");
}

void FluBorder::updateProperty(QString textColor, QString bgColor, QString borderWidth, QString borderColor)
{
    m_map["TextColor"] = textColor;
    m_map["BackGroundColor"] = bgColor;
    m_map["BorderWith"] = borderWidth;
    m_map["BorderColor"] = borderColor;
    FluStyleSheetUitls::setQssByFileName(m_map, "FluBorder.qss", this, FluThemeUtils::getUtils()->getTheme());
    style()->polish(this);
}

void FluBorder::setBackGroundColor(QColor bgColor)
{
    QString str = QString::asprintf("rgb(%d,%d,%d)", bgColor.red(), bgColor.green(), bgColor.blue());
    updateProperty(m_map["TextColor"], str, m_map["BorderWith"], m_map["BorderColor"]);
}

void FluBorder::setBorderWidth(int width)
{
    QString str = QString::asprintf("%dpx", width);
    updateProperty(m_map["TextColor"], m_map["BackGroundColor"], str, m_map["BorderColor"]);
}

void FluBorder::setBorderColor(QColor borderColor)
{
    QString str = QString::asprintf("rgb(%d,%d,%d)", borderColor.red(), borderColor.green(), borderColor.blue());
    updateProperty(m_map["TextColor"], m_map["BackGroundColor"], m_map["BorderWith"], str);
}

void FluBorder::setTExtColor(QColor textColor)
{
    QString str = QString::asprintf("rgb(%d,%d,%d)", textColor.red(), textColor.green(), textColor.blue());
    updateProperty(str, m_map["BackGroundColor"], m_map["BorderWith"], m_map["BorderColor"]);
}

bool FluBorder::isTransparentBackground()
{
    return m_map["BackGroundColor"] == "transparent";
}
