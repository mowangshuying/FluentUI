#pragma once

#include <QWidget>
#include <QPainter>


class FluProgressRing : public QWidget
{
	Q_OBJECT
  public:
	  FluProgressRing(QWidget* parent = nullptr) : QWidget(parent)
	  {
          m_minValue = 0;
          m_maxValue = 100;
          m_curValue = 0;
		  setFixedSize(80, 80);
	  }

	  void paintEvent(QPaintEvent* event)
	  {

		  QPainter painter(this);
           painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
           float minWH = qMin(width(), height());
           float trunkW = 6;

		   QPen pen;
           pen.setWidth(6);
           pen.setColor(QColor(211,211,211));
           painter.setPen(pen);
		   QRectF outerC(4, 4, minWH - trunkW - 2, minWH - trunkW - 2);
		   painter.drawEllipse(outerC);

		   pen.setColor(QColor(0, 90, 158));
           painter.setPen(pen);
           painter.drawArc(outerC, 90 * 16, -360 * 16 * (m_curValue * 1.0 / (m_maxValue - m_minValue)));
	  }


	  void setMinMaxValue(int minValue, int maxValue)
	  {
           m_minValue = minValue;
           m_maxValue = maxValue;
	  }

	  void setCurValue(int curValue)
	  {
           m_curValue = curValue;
	  }


	  int getCurValue()
	  {
           return m_curValue;
	  }

   protected:
	  int m_minValue;
      int m_maxValue;
      int m_curValue;
};
