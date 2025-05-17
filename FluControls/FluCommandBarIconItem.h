#pragma once

#include "FluCommandBarItem.h"
#include "../FluUtils/FluUtils.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QStyle>
#include <QPainter>

class FluCommandBarIconItem : public FluCommandBarItem
{
	Q_OBJECT
  public:
      FluCommandBarIconItem(QWidget* parent = nullptr);

      FluCommandBarIconItem(FluAwesomeType type, QWidget* parent = nullptr);

      void mouseReleaseEvent(QMouseEvent* event);

      void paintEvent(QPaintEvent* event);

    signals:
      void clicked();
    public slots:
        void onThemeChanged()
        {
            FluStyleSheetUitls::setQssByFileName("FluCommandBarIconItem.qss", this, FluThemeUtils::getUtils()->getTheme());
        }
    protected:
      QHBoxLayout* m_hMainLayout;
      QPushButton* m_iconBtn;
      FluAwesomeType m_awesomeType;
};
