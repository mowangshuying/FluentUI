#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include "FluIconButton.h"
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QStyleOption>
#include <QPainter>

class FluIconButton;
// a expander to display more informations.
class FluExpander : public FluWidget
{
    Q_OBJECT
  public:
    FluExpander(QWidget* parent = nullptr);

    bool getDown()
    {
        return m_bDown;
    }

    void setDown(bool bDown)
    {
        m_bDown = bDown;
        setProperty("down", bDown);
        m_wrap1->setProperty("down", bDown);
        m_wrap2->setProperty("down", bDown);

        style()->polish(this);
        m_wrap1->style()->polish(m_wrap1);
        m_wrap2->style()->polish(m_wrap2);
    }

    void setTopRadius0(bool bTopRadius0)
    {
        m_wrap1->setProperty("topRadius0", bTopRadius0);
        setProperty("topRadius0", bTopRadius0);

        style()->polish(this);
        m_wrap1->style()->polish(m_wrap1);
    }

    void setWrap2Height(int h)
    {
        m_wrap2Height = h;
    }

    // signals:
    //   void windowSizeChanged();
    QHBoxLayout* getWrap1Layout()
    {
        return m_hWrap1Layout;
    }

    QVBoxLayout* getWrap2Layout()
    {
        return m_vWrap2Layout;
    }

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_hWrap1Layout;
    QVBoxLayout* m_vWrap2Layout;

    FluIconButton* m_downOrUpButton;

    QWidget* m_wrap1;
    QWidget* m_wrap2;
    int m_wrap2Height;  // The height is wrap2 expand height.
    bool m_bDown;
};
