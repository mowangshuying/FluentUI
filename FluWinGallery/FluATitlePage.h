#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FluFWScrollView;
class FluATitlePage : public QWidget
{
	Q_OBJECT
  public:
        FluATitlePage(QWidget* parent = nullptr);

        FluFWScrollView* getFWScrollView()
        {
            return m_vScrollView;
        }

		void paintEvent(QPaintEvent* event);

  protected:
        QLabel* m_titleLabel;
        QVBoxLayout* m_vMainLayout;
        FluFWScrollView* m_vScrollView;
};
