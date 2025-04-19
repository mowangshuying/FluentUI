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
    Q_PROPERTY(int contentHeight READ getContentHeight WRITE setContentHeight NOTIFY contentHeightChanged FINAL)
  public:
    FluExpander(QWidget* parent = nullptr);

    bool getDown();

    void setDown(bool bDown);

    void setTopRadius0(bool bTopRadius0);

    // signals:
    //   void windowSizeChanged();
    QHBoxLayout* getWrap1Layout();

    QVBoxLayout* getWrap2Layout();

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

    int getContentHeight() const;
    void setContentHeight(int newContentHeight);

  public slots:
    void onThemeChanged();

    virtual void onClicked();

  signals:
    void contentHeightChanged();

  protected:
    QPropertyAnimation* m_expandAni;

    QHBoxLayout* m_hWrap1Layout;
    QVBoxLayout* m_vWrap2Layout;

    FluIconButton* m_downOrUpButton;

    QWidget* m_wrap1;
    QWidget* m_wrap2;
    bool m_bDown;

  private:
    int m_contentHeight = 0;
};
