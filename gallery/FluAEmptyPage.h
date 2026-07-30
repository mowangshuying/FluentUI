#pragma once

#include "../controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include "../controls/FluSearchLineEdit.h"

class FluVScrollView;
class FluHCard;
class FluAEmptyPage : public FluWidget
{
    Q_OBJECT
  public:
    FluAEmptyPage(QWidget* parent = nullptr);

    FluHCard* addHCard(QPixmap icon, QString title, QString context, QString key);

    void paintEvent(QPaintEvent* event);

  signals:
    void clickedHCard(QString key);

  protected:
    QLabel* m_titleLabel;
    //  QLabel* m_subTitleLabel;

    QVBoxLayout* m_mainLayout;
    FluVScrollView* m_scrollView;
    QLabel* m_infoLabel;
};
