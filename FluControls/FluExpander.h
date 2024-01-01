#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include "FluIconButton.h"
#include "../FluUtils/FluStyleSheetUitls.h"

// a expander to display more informations.
class FluExpander : public QWidget
{
    Q_OBJECT
  public:
    FluExpander(QWidget* parent = nullptr);

  protected:
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_hWrap1Layout;
    QWidget* m_wrap1;
    QWidget* m_wrap2;
    bool m_bDown;  //
};
