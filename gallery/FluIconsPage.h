#pragma once

#include "FluAEmptyPage.h"
#include "../utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../controls/FluVScrollView.h"
#include "../controls/FluFlowLayout.h"
#include "../controls/FluDisplayIconBox.h"
#include "../controls/FluFWScrollView.h"
#include "../controls/FluInstructions.h"

class FluIconsPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluIconsPage(QWidget* parent = nullptr);

  public slots:
    void onThemeChanged();

  protected:
    // QColor m_penColor;
    QLabel* m_iconLabel;

    QLabel* m_searchLabel;
    FluSearchLineEdit* m_searchEdit;
    FluDisplayIconBox* m_displayIconBox;

    std::map<FluAwesomeType, FluDisplayIconBox*> m_iconBoxMap;
};
