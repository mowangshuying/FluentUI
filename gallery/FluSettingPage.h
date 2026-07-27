#pragma once

#include "../controls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../utils/FluUtils.h"
#include "../controls/FluVScrollView.h"
#include "../controls/FluSettingsSelectBox.h"
#include "../controls/FluSettingsLabelBox.h"
#include "../controls/FluSettingsVersionBox.h"
#include "../controls/FluLabel.h"
#include "../controls/FluHyperLinkButton.h"

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

  signals:
    void navigationStyleChanged(int index);

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
