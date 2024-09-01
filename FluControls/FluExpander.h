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

    bool getDown();

    void setDown(bool bDown);

    void setTopRadius0(bool bTopRadius0);

    void setWrap2Height(int h);

    // signals:
    //   void windowSizeChanged();
    QHBoxLayout* getWrap1Layout();

    QVBoxLayout* getWrap2Layout();

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

    virtual void onClicked();

  protected:
    QPropertyAnimation* m_expandAni;

    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_hWrap1Layout;
    QVBoxLayout* m_vWrap2Layout;

    FluIconButton* m_downOrUpButton;

    QWidget* m_wrap1;
    QWidget* m_wrap2;
    int m_wrap2Height;  // The height is wrap2 expand height.
    bool m_bDown;
};
