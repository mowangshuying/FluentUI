#pragma once

#include "../Controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../Utils/FluUtils.h"
#include "../Controls/FluVScrollView.h"
#include "../Controls/FluSettingsSelectBox.h"
#include "../Controls/FluSettingsLabelBox.h"
#include "../Controls/FluSettingsVersionBox.h"
#include "../Controls/FluLabel.h"
#include "../Controls/FluHyperLinkButton.h"

class FluSettingPage : public FluWidget
{
    Q_OBJECT
  public:
    FluSettingPage(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

    void updateThemeSelectBox()
    {
        m_appThemeSelectBox->getComboBox()->setCurrentIndex((int)FluThemeUtils::getUtils()->getTheme());
    }

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;

    QLabel* m_titleLabel;
    QLabel* m_appBehaviorLabel;
    QLabel* m_aboutLabel;

    FluSettingsSelectBox* m_appThemeSelectBox;
    FluVScrollView* m_scrollView;
};
