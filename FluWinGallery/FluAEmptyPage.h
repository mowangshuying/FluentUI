#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "../FluControls/FluSearchLineEdit.h"

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
    FluVScrollView* m_vScrollView;
    QLabel* m_infoLabel;
};
