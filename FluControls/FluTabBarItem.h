#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include <QEnterEvent>
#include "FluHSplitLine.h"

class FluTabBarItem : public FluWidget
{
    Q_OBJECT
  public:
    FluTabBarItem(QWidget* parent = nullptr);

    void setSelected(bool bSel);

    bool getSelected();

    void setText(QString text);

    QString getText();

    void adjustWidgetSize();

    void resizeEvent(QResizeEvent* event);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void clicked();
    void sizeChanged();
    void clickedCloseBtn(FluTabBarItem* item);

  public slots:
    void onThemeChanged();

  protected:
    FluHSplitLine* m_hspL;
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_iconBtn;
    QPushButton* m_textBtn;
    QPushButton* m_closeBtn;
    FluHSplitLine* m_hspR;
    bool m_bSel;
};
