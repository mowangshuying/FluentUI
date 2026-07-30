#pragma once

#include "../controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>

class FluFWScrollView;
class FluHCard;
class FluATitlePage : public FluWidget
{
    Q_OBJECT
  public:
    FluATitlePage(QWidget* parent = nullptr);

    FluFWScrollView* getFWScrollView()
    {
        return m_scrollView;
    }

    FluHCard* addHCard(QPixmap icon, QString title, QString context, QString key);

    void paintEvent(QPaintEvent* event);

  signals:
    void clickedHCard(QString key);

  protected:
    QLabel* m_titleLabel;
    QVBoxLayout* m_mainLayout;
    FluFWScrollView* m_scrollView;
};
