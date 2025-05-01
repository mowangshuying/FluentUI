#include "FluRatingControlPage.h"

FluRatingControlPage::FluRatingControlPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("RatingControl"));
    m_infoLabel->setText(tr("Rate something to 5 stars"));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A Simple RatingControl."));
    displayBox->getCodeExpander()->setCodeByPath("../code/RatingControlPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(96);

    auto ratingControl = new FluRatingControl;
    displayBox->getBodyLayout()->addWidget(ratingControl);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluRatingControlPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluRatingControlPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
