#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"

class FluColorPickerButton : public QPushButton
{
    Q_OBJECT
  public:
    FluColorPickerButton(QWidget* parent = nullptr) : QPushButton(parent)
    {
        setFixedSize(30, 30);
        onThemeChanged();
    }

    void setColor(QColor color)
    {
        std::map<QString, QString> kvmap;
        m_color = color;
        kvmap["color"] = QString::asprintf("rgb(%d,%d,%d)", color.red(), color.green(), color.blue());
        FluStyleSheetUitls::setQssByFileName(kvmap, "FluColorPickerButton.qss", this, FluThemeUtils::getUtils()->getTheme());
    }

    QColor getColor()
    {
        return m_color;
    }

  public slots:
    void onThemeChanged()
    {
        setColor(m_color);
    }

  protected:
    QColor m_color;
};
