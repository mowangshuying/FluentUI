#include "FluScrollViewPage.h"

FluScrollViewPage::FluScrollViewPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText("ScrollView");
    m_infoLabel->setText("A ScrollView lets user scroll, pan, and zoom to see content that's larger than the viewable area. The ItemsView has a ScrollView built into its control template to provide automatic scrolling.");

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle("Content inside of ScrollView.");
    displayBox->getCodeExpander()->setCodeByPath("../code/ScrollViewPageCode1.md");
    // displayBox->setBodyWidgetFixedHeight(800);

    QPixmap img("../res/SampleMedia/LandscapeImage9.jpg");
    auto imgBox = new FluImageBox(img, this);
    imgBox->setFixedSize(2000, 2000);
    auto scrollArea = new FluScrollArea;
    scrollArea->setWidget(imgBox);
    scrollArea->setFixedSize(400, 300);

    displayBox->getBodyLayout()->addWidget(scrollArea);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluScrollViewPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluScrollViewPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluScrollViewPage.qss", this);
    }
}
