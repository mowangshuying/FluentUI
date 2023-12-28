#pragma once

#include <QPainter>
#include <QWidget>

class FluColorDemo : public QWidget {
  Q_OBJECT
public:
  FluColorDemo(QWidget *parent = nullptr) : QWidget(parent) {}

  void setBgColor(const QColor &color) {
    m_bgColor = color;
    update();
  }

protected:
  void paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), m_bgColor);
  }

private:
  QColor m_bgColor;
};
