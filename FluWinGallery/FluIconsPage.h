#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluFlowLayout.h"
#include "../FluControls/FluDisplayIconBox.h"
#include "../FluControls/FluFWScrollView.h"
#include "../FluControls/FluIntructions.h"

class FluIconsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluIconsPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
    QColor m_penColor;
    QLabel* m_iconLabel;

    QLabel* m_searchLabel;
    FluSearchLineEdit* m_searchEdit;
    FluDisplayIconBox* m_sDisplayIconBox;

    std::map<FluAwesomeType, FluDisplayIconBox*> m_iconBoxMap;
};
