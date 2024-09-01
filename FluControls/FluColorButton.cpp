#include "FluColorButton.h"

FluColorButton::FluColorButton(QColor backgroundColor, QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    std::map<QString, QString> kvMap;
    m_backgroundColor = backgroundColor;
    kvMap["backgroundColor"] = QString::asprintf("rgb(%d,%d,%d)", backgroundColor.red(), backgroundColor.green(), backgroundColor.blue());
    FluStyleSheetUitls::setQssByFileName(kvMap, "../StyleSheet/light/FluColorButton.qss", this);
}

QColor FluColorButton::getBackgroundColor()
{
    return m_backgroundColor;
}
