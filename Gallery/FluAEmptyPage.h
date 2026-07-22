#pragma once

#include "../Controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "../Controls/FluSearchLineEdit.h"

class FluVScrollView;
class FluAEmptyPage : public FluWidget
{
    Q_OBJECT
  public:
    FluAEmptyPage(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    QLabel* m_titleLabel;
    //  QLabel* m_subTitleLabel;

    QVBoxLayout* m_mainLayout;
    FluVScrollView* m_scrollView;
    QLabel* m_infoLabel;
};
