#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QEnterEvent>
#include "../FluUtils/FluUtils.h"

class FluHFlipView : public QScrollArea
{
    Q_OBJECT
  public:
    FluHFlipView(QWidget* parent = nullptr);

    void addPixmap(QPixmap pixmap);

    void hideOrShowRLBtn(bool bEnter);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void resizeEvent(QResizeEvent* event);

  protected:
    QWidget* m_contextWidget;
    QHBoxLayout* m_hLayout;

    QPushButton* m_lBtn;
    QPushButton* m_rBtn;

    int m_nImgBoxIndex;
};
