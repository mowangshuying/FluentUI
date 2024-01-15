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

    void setWrap2Height(int h)
    {
        m_wrap2Height = h;
    }

    // signals:
    //   void windowSizeChanged();
  protected:
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_hWrap1Layout;
    QVBoxLayout* m_vWrap2Layout;
    QWidget* m_wrap1;
    QWidget* m_wrap2;
    int m_wrap2Height;  // The height is wrap2 expand height.
    bool m_bDown;
};
