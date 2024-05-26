#pragma once

#include <QPushButton>
#include "../FluUtils/FluStyleSheetUitls.h"

class FluColorButton : public QPushButton
{
    Q_OBJECT
  public:
    FluColorButton(QColor backgroundColor, QWidget* parent = nullptr) : QPushButton(parent)
    {
        std::map<QString, QString> kvMap;
        m_backgroundColor = backgroundColor;
        kvMap["backgroundColor"] = QString::asprintf("rgb(%d,%d,%d)", backgroundColor.red(), backgroundColor.green(), backgroundColor.blue());
        FluStyleSheetUitls::setQssByFileName(kvMap, ":/StyleSheet/light/FluColorButton.qss", this);
    }

    QColor getBackgroundColor()
    {
        return m_backgroundColor;
    }

  protected:
    QColor m_backgroundColor;
};
