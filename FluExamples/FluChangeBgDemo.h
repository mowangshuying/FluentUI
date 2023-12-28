#pragma once

#include <QDebug>
#include <QEvent>
#include <QHBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

class FluChangeBgDemo : public QWidget
{
    Q_OBJECT
  public:
    FluChangeBgDemo(QWidget *parent = nullptr);

    ~FluChangeBgDemo();

  protected:
    void enterEvent(QEnterEvent *event);

    void leaveEvent(QEvent *event);

    void paintEvent(QPaintEvent *event);

  private:
    bool m_bHover;
    QColor m_normalBgColor;
    QColor m_hoverBgColor;
};
