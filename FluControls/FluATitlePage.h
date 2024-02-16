#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FluVScrollView;
class FluATitlePage : public QWidget
{
	Q_OBJECT
  public:
        FluATitlePage(QWidget* parent = nullptr);

		void paintEvent(QPaintEvent* event);

  protected:
        QLabel* m_titleLabel;
        QVBoxLayout* m_vMainLayout;
        FluVScrollView* m_vScrollView;
};
