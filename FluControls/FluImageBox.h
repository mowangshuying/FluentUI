#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>

class FluImageBox : public QWidget
{
	Q_OBJECT
  public:
	  FluImageBox(QWidget* parent = nullptr) : QWidget(parent)
	  {
              m_pixmap = QPixmap();
	  }

	  FluImageBox(QPixmap pixmap, QWidget* parent = nullptr)
		  : FluImageBox(parent)
	  {
              m_pixmap = pixmap;
	  }

	  

	  void paintEvent(QPaintEvent* event)
	  {
              QWidget::paintEvent(event);
		  // draw a round pixmap
              QPainter painter(this);
              QPainterPath path;
              path.addRoundedRect(rect(), 4, 4);
              painter.setClipPath(path);

              m_pixmap = m_pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
              painter.drawPixmap(rect(), m_pixmap);
	  }

protected:
      QPixmap m_pixmap;
};
