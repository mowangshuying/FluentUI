#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include "FluIconButton.h"
#include "../utils/FluStyleSheetUtils.h"
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

    void setDown(bool isDown);

    void setTopRadius0(bool isTopRadius0);

    // signals:
    //   void windowSizeChanged();
    QHBoxLayout* getWrap1Layout();

    QVBoxLayout* getWrap2Layout();

    void resizeEvent(QResizeEvent* event);

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

    QSize sizeHint() const;

    int getContentHeight() const;
    void setContentHeight(int newContentHeight);

  public slots:
    void onThemeChanged();

    virtual void onClicked();

  signals:
    void contentHeightChanged();

  protected:
    QPropertyAnimation* m_expandAni;

    QHBoxLayout* m_wrap1Layout;
    QVBoxLayout* m_wrap2Layout;

    FluIconButton* m_downOrUpButton;

    QWidget* m_wrap1;
    QWidget* m_wrap2;
    bool m_isDown;

  private:
    // resize/reposition m_wrap2 from its current size hint; keeps the cached
    // wrap2 geometry fresh even when no resize event arrives (e.g. content
    // added while collapsed).
    void updateWrap2Geometry();

    int m_contentHeight = 0;
};
