#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluVScrollView.h"

class FluExpanderPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluExpanderPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("ExpanderPage");
        m_infoLabel->setText(
            "The Expander has a header and can expand to show a body with more content."
            "Use an Expander when some content is only relevant some of the time(for example to read more information or access additional options for an item).");

        addExpanderDemo1();
        addExpanderDemo2();
        addExpanderDemo3();

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpanderPage.qss", this);
        
    }

    void addExpanderDemo1()
    {
        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("An Expander with text in the header and content areas.");
        displayBox->getCodeExpander()->setCodeByPath("../code/ExpanderPageCode1.md");
        displayBox->setBodyWidgetFixedHeight(120);

        auto expander = new FluExpander(this);
        expander->setFixedWidth(350);
        auto titleLabel = new FluLabel;
        titleLabel->setFixedWidth(250);
        titleLabel->setText("This is a label in Header.");
        expander->getWrap1Layout()->addWidget(titleLabel);

        auto contentLabel = new FluLabel;
        contentLabel->setFixedWidth(230);
        contentLabel->setText("This is a label in the content.");
        expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
        expander->getWrap2Layout()->addWidget(contentLabel);
        //  layout()->addWidget(expander);

        displayBox->getBodyLayout()->addWidget(expander);
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }

    void addExpanderDemo2()
    {
        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("An Expander with other controls in the header and content.");
        displayBox->getCodeExpander()->setCodeByPath("../code/ExpanderPageCode2.md");
        displayBox->setBodyWidgetFixedHeight(120);

        auto expander = new FluExpander(this);
        expander->setFixedWidth(350);
        auto toggleBtn = new FluToggleButton;
        toggleBtn->setFixedWidth(250);
        toggleBtn->setText("This is a ToggleButton in Header.");
        expander->getWrap1Layout()->addWidget(toggleBtn);

        auto pushBtn = new FluPushButton;
        pushBtn->setFixedWidth(230);
        pushBtn->setText("This is a Button in the content.");
        expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
        expander->getWrap2Layout()->addWidget(pushBtn);

        displayBox->getBodyLayout()->addWidget(expander);
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }

    void addExpanderDemo3()
    {
        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("Modifying Expanders content alignment.");
        displayBox->getCodeExpander()->setCodeByPath("../code/ExpanderPageCode3.md");
        displayBox->setBodyWidgetFixedHeight(120);

        auto expander = new FluExpander(this);
        expander->setFixedWidth(350);
        auto toggleBtn = new FluToggleButton;
        toggleBtn->setFixedWidth(250);
        toggleBtn->setText("This  ToggleButton is Centered.");
        expander->getWrap1Layout()->addWidget(toggleBtn);

        auto pushBtn = new FluPushButton;
        pushBtn->setFixedWidth(230);
        pushBtn->setText("This is a Left aligned.");
        expander->getWrap2Layout()->setAlignment(Qt::AlignLeft);
        expander->getWrap2Layout()->addWidget(pushBtn);
        // layout()->addWidget(expander);

        displayBox->getBodyLayout()->addWidget(expander);
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpanderPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluExpanderPage.qss", this);
        }
    }
};
