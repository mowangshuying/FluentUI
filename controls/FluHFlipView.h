#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QEnterEvent>
#include "../Utils/FluUtils.h"

class FluHFlipView : public QScrollArea
{
    Q_OBJECT
  public:
    FluHFlipView(QWidget* parent = nullptr);

    void addPixmap(QPixmap pixmap);

    void hideOrShowRLButton(bool isEnter);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void resizeEvent(QResizeEvent* event);

  protected:
    QWidget* m_contextWidget;
    QHBoxLayout* m_layout;

    QPushButton* m_lButton;
    QPushButton* m_rButton;

    int m_imgBoxIndex;
};
