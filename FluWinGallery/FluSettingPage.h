#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluSettingsSelectBox.h"
#include "../FluControls/FluSettingsLabelBox.h"
#include "../FluControls/FluSettingsVersionBox.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluHyperLinkButton.h"

class FluSettingPage : public FluWidget
{
    Q_OBJECT
  public:
    FluSettingPage(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

    void updateThemeSelectBox()
    {
        m_appThemeSelectBox->getComboBox()->setIndex((int)FluThemeUtils::getUtils()->getTheme());
    }

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;

    QLabel* m_titleLabel;
    QLabel* m_appBehaviorLabel;
    QLabel* m_aboutLabel;

    FluSettingsSelectBox* m_appThemeSelectBox;
    FluVScrollView* m_vScrollView;
};
