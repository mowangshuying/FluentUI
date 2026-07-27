#pragma once

#include "../Controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>

class FluFWScrollView;
class FluATitlePage : public FluWidget
{
    Q_OBJECT
  public:
    FluATitlePage(QWidget* parent = nullptr);

    FluFWScrollView* getFWScrollView()
    {
        return m_scrollView;
    }

    void paintEvent(QPaintEvent* event);

  protected:
    QLabel* m_titleLabel;
    QVBoxLayout* m_mainLayout;
    FluFWScrollView* m_scrollView;
};
