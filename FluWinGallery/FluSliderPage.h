#pragma once

#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluSlider.h"
#include "../FluControls/FluVScrollView.h"

class FluSliderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluSliderPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("Slider");

        // m_subTitleLabel->setText("CppQtFluentUi888::FluSlider");

        m_infoLabel->setText("Use a Slider when your want your users to be able to set defined, contiguous values(such as volume or brightness) or a range of discrete values(such as screen resolution settings).");

        auto displayBox1 = new FluDisplayBox;
        displayBox1->setTitle("A simple Slider.");
        displayBox1->getCodeExpander()->setCodeByPath("../code/SliderPageCode1.md");
        displayBox1->setBodyWidgetFixedHeight(96);

        auto hSlider = new FluSlider(displayBox1);
        hSlider->setOrientation(Qt::Horizontal);
        hSlider->setMinimum(0);
        hSlider->setMaximum(100);
        hSlider->setSingleStep(10);
        //   displayBox1->getBodyLayout()->addWidget(hSlider, 0);
        //   displayBox1->getBodyLayout()->addStretch();

        hSlider->move(50, 60);
        m_vScrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

        auto displayBox2 = new FluDisplayBox;
        displayBox2->setTitle("A vertical slider.");
        displayBox2->getCodeExpander()->setCodeByPath("../code/SliderPageCode2.md");
        displayBox2->setBodyWidgetFixedHeight(180);

        auto vSlider = new FluSlider(displayBox2);
        vSlider->setOrientation(Qt::Vertical);
        vSlider->setMinimum(0);
        vSlider->setMaximum(100);
        vSlider->setSingleStep(5);
        // vSlider->move(250, 50);
        vSlider->move(50, 50);

        m_vScrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSliderPage.qss", this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSliderPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSliderPage.qss", this);
        }
    }
};
