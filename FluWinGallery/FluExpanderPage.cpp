#include "FluExpanderPage.h"

FluExpanderPage::FluExpanderPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Expander"));
    m_infoLabel->setText(
        tr("The Expander has a header and can expand to show a body with more content."
           "Use an Expander when some content is only relevant some of the time(for example to read more information or access additional options for an item)."));

    addExpanderDemo1();
    addExpanderDemo2();
    addExpanderDemo3();

    onThemeChanged();
}

void FluExpanderPage::addExpanderDemo1()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("An Expander with text in the header and content areas."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/ExpanderPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(120);

    auto expander = new FluExpander(this);
    expander->setFixedWidth(350);
    auto titleLabel = new FluLabel;
    titleLabel->setFixedWidth(250);
    titleLabel->setText(tr("This is a label in Header."));
    expander->getWrap1Layout()->addWidget(titleLabel);

    auto contentLabel = new FluLabel;
    contentLabel->setFixedWidth(230);
    contentLabel->setText(tr("This is a label in the content."));
    expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
    expander->getWrap2Layout()->addWidget(contentLabel);
    //  layout()->addWidget(expander);

    displayBox->getBodyLayout()->addWidget(expander);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluExpanderPage::addExpanderDemo2()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("An Expander with other controls in the header and content."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/ExpanderPageCode2.md"));
    displayBox->setBodyWidgetFixedHeight(120);

    auto expander = new FluExpander(this);
    expander->setFixedWidth(350);
    auto toggleBtn = new FluToggleButton;
    toggleBtn->setFixedWidth(250);
    toggleBtn->setText(tr("This is a ToggleButton in Header."));
    expander->getWrap1Layout()->addWidget(toggleBtn);

    auto pushBtn = new FluPushButton;
    pushBtn->setFixedWidth(230);
    pushBtn->setText(tr("This is a Button in the content."));
    expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
    expander->getWrap2Layout()->addWidget(pushBtn);

    displayBox->getBodyLayout()->addWidget(expander);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluExpanderPage::addExpanderDemo3()
{
    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("Modifying Expanders content alignment."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/ExpanderPageCode3.md"));
    displayBox->setBodyWidgetFixedHeight(120);

    auto expander = new FluExpander(this);
    expander->setFixedWidth(350);
    auto toggleBtn = new FluToggleButton;
    toggleBtn->setFixedWidth(250);
    toggleBtn->setText(tr("This  ToggleButton is Centered."));
    expander->getWrap1Layout()->addWidget(toggleBtn);

    auto pushBtn = new FluPushButton;
    pushBtn->setFixedWidth(230);
    pushBtn->setText(tr("This is a Left aligned."));
    expander->getWrap2Layout()->setAlignment(Qt::AlignLeft);
    expander->getWrap2Layout()->addWidget(pushBtn);
    // layout()->addWidget(expander);

    displayBox->getBodyLayout()->addWidget(expander);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluExpanderPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluExpanderPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluExpanderPage.qss"), this);
    }
}
