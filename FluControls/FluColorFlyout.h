#pragma once

#include "../FluControls/FluVFlyout.h"
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include "FluColorButton.h"

// has 9 color buttons.
class FluColorFlyout : public QWidget
{
    Q_OBJECT
  public:
    FluColorFlyout(QWidget* targetWidget) : QWidget(nullptr), m_targetWidget(targetWidget)
    {
        m_gridLayout = new QGridLayout;
        setLayout(m_gridLayout);
        setMinimumSize(120, 120);
        m_gridLayout->setContentsMargins(16, 16, 16, 16);
        // m_gridLayout->setSpacing(25);

        setAttribute(Qt::WA_TranslucentBackground);
        setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

         FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluColorFlyout.qss", this);
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluColorFlyout.qss", this);
        }
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

      void addColorButton(FluColorButton* colorBtn, int row, int col)
      {
          m_gridLayout->addWidget(colorBtn, row, col);
          connect(colorBtn, &FluColorButton::clicked, [=]() {
              emit colorChanged(colorBtn->getBackgroundColor());
              close();
              });
      }

      void addColorButton(FluColorButton* colorBtn)
      {
          int count = m_gridLayout->count();
          int row = count / 3;
          int col = count % 3;
          addColorButton(colorBtn, row, col);
      }

      void showEvent(QShowEvent* event)
      {
          if (m_targetWidget == nullptr)
              return;

          QPoint targetPos = m_targetWidget->mapToGlobal(QPoint(0, 0));
          int nX = targetPos.x();
          int nY = targetPos.y() + m_targetWidget->height() + 5;
          move(nX, nY);
      }

      void paintEvent(QPaintEvent* event)
      {
          QStyleOption opt;
          opt.initFrom(this);
          QPainter painter(this);
          style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
      }
signals:
      void colorChanged(QColor color);
    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluColorFlyout.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluColorFlyout.qss", this);
          }
      }
  protected:
      QGridLayout* m_gridLayout;
      QWidget* m_targetWidget;
};
