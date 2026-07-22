#pragma once

#include "FluWidget.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "../Utils/FluUtils.h"
#include "FluImageBox.h"

class FluVFlipView : public QScrollArea
{
    Q_OBJECT
  public:
    FluVFlipView(QWidget* parent = nullptr);

    void addPixmap(QPixmap pixmap);

    void hideOrShowTBButton(bool isEnter);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void resizeEvent(QResizeEvent* event);

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_layout;

    QPushButton* m_tButton;
    QPushButton* m_bottomButton;

    int m_imgBoxIndex;
};
