#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include "../Utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include <QEnterEvent>
#include "FluHSplitLine.h"

class FluTabBarItem : public FluWidget
{
    Q_OBJECT
  public:
    FluTabBarItem(QWidget* parent = nullptr);

    void setSelected(bool isSel);

    bool getSelected();

    void setText(QString text);

    QString getText();

    int getWidgetWidth();

    void adjustWidgetSize();

    void resizeEvent(QResizeEvent* event);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void clicked();
    void sizeChanged();
    void clickedCloseButton(FluTabBarItem* item);

  public slots:
    void onThemeChanged();

  protected:
    FluHSplitLine* m_hspL;
    QHBoxLayout* m_mainLayout;
    QPushButton* m_iconButton;
    QPushButton* m_textButton;
    QPushButton* m_closeButton;
    FluHSplitLine* m_hspR;
    bool m_isSel;
};
