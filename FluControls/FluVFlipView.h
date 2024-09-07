#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include "FluImageBox.h"

class FluVFlipView : public QScrollArea
{
    Q_OBJECT
  public:
    FluVFlipView(QWidget* parent = nullptr);

    void addPixmap(QPixmap pixmap);

    void hideOrShowTBBtn(bool bEnter);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void resizeEvent(QResizeEvent* event);

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_vLayout;

    QPushButton* m_tBtn;
    QPushButton* m_bBtn;

    int m_nImgBoxIndex;
};
