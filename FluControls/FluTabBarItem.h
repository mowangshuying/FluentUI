#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluTabBarItem : public FluWidget
{
    Q_OBJECT
  public:
    FluTabBarItem(QWidget* parent = nullptr);

    void setSelected(bool bSel);

    bool getSelected();

    void setText(QString text);

    QString getText();

    void resizeEvent(QResizeEvent* event);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void clicked();
    void sizeChanged();
    void clickedCloseBtn(FluTabBarItem* item);

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_iconBtn;
    QPushButton* m_textBtn;
    QPushButton* m_closeBtn;

    bool m_bSel;
};
