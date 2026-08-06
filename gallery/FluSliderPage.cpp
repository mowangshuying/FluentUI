#include "FluSliderPage.h"

FluSliderPage::FluSliderPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Slider"));

    // m_subTitleLabel->setText("FluentUI::FluSlider");

    m_infoLabel->setText(tr("Use a Slider when your want your users to be able to set defined, contiguous values(such as volume or brightness) or a range of discrete values(such as screen resolution settings)."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A simple Slider."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/SliderPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(96);

    auto hSlider = new FluSlider(displayBox1);
    hSlider->setOrientation(Qt::Horizontal);
    hSlider->setMinimum(0);
    hSlider->setMaximum(100);
    hSlider->setSingleStep(10);

    hSlider->move(50, 60);
    m_scrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A vertical slider."));
    displayBox2->getCodeExpander()->setCodeByPath("../code/SliderPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(180);

    auto vSlider = new FluSlider(displayBox2);
    vSlider->setOrientation(Qt::Vertical);
    vSlider->setMinimum(0);
    vSlider->setMaximum(100);
    vSlider->setSingleStep(5);
    // vSlider->move(250, 50);
    vSlider->move(50, 50);

    m_scrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    auto displayBox3 = new FluDisplayBox;
    displayBox3->setTitle(tr("A slider with tick marks."));
    displayBox3->getCodeExpander()->setCodeByPath("../code/SliderPageCode3.md");
    displayBox3->setBodyWidgetFixedHeight(96);

    auto tickSlider = new FluSlider(displayBox3);
    tickSlider->setOrientation(Qt::Horizontal);
    tickSlider->setMinimum(0);
    tickSlider->setMaximum(100);
    tickSlider->setSingleStep(10);
    tickSlider->setTickMarkEnabled(true);
    tickSlider->setTickMarkInterval(20);

    tickSlider->move(50, 60);
    m_scrollView->getMainLayout()->addWidget(displayBox3, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluSliderPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluSliderPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
