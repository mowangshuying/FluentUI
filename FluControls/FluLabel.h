#pragma once

#include <QLabel>

#include "../FluUtils/FluStyleSheetUitls.h"

class FluLabel : public QLabel
{
    Q_OBJECT
  public:
    FluLabel(QString style, QWidget* parent = nullptr) : QLabel(this), m_style(style)
    {
        // style£º
        // reference WinUi3 Gallary Typeography page.
        setProperty("style", m_style);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLabel.qss", this);
    }

  protected:
    QString m_style;
};
