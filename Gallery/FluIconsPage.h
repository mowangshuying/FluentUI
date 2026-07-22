#pragma once

#include "FluAEmptyPage.h"
#include "../Utils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluFlowLayout.h"
#include "../Controls/FluDisplayIconBox.h"
#include "../Controls/FluFWScrollView.h"
#include "../Controls/FluInstructions.h"

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
