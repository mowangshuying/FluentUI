#pragma once

#include "FluCommandBarItem.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class FluCommandBarIconTextItem : public FluCommandBarItem
{
	Q_OBJECT
  public:
        FluCommandBarIconTextItem(QWidget* parent = nullptr);

      void mouseReleaseEvent(QMouseEvent* event);

      void paintEvent(QPaintEvent* event);
  signals:
      void clicked();
  protected:
      QHBoxLayout* m_hMainLayout;
	  QPushButton* m_iconBtn;
      QLabel* m_textLabel;
};
