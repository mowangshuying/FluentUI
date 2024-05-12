#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluRatingControl.h"

class FluRatingControlPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluRatingControlPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("RatingControl");
        m_infoLabel->setText("Rate something to 5 stars");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A Simple RatingControl.");
        displayBox->getCodeExpander()->setCodeByPath("../code/RatingControlPageCode1.md");
        displayBox->setBodyWidgetFixedHeight(96);

        auto ratingControl = new FluRatingControl;
        displayBox->getBodyLayout()->addWidget(ratingControl);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRatingControlPage.qss", this);
        //connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); }); { onThemeChanged(); });
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRatingControlPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRatingControlPage.qss", this);
        }
    }
};
