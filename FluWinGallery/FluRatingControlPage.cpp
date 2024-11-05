#include "FluRatingControlPage.h"

FluRatingControlPage::FluRatingControlPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
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
}

void FluRatingControlPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluRatingControlPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluRatingControlPage.qss", this);
    }
}
