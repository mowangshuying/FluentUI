#include "FluToggleSwitchPage.h"

FluToggleSwitchPage::FluToggleSwitchPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ToggleSwitch"));
    m_infoLabel->setText(tr("Use ToggleSwitch controls to present users with exactly two mutually exclusive options (like on/off), where choosing an option results in an immediate commit. A toggle switch should have a single label."));

    // Example 1: With text (default Off state)
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A simple ToggleSwitch with text (Off by default)."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ToggleSwitchPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(70);

    auto switch1 = new FluToggleSwitch(displayBox1);
    switch1->move(50, 40);

    m_scrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    // Example 2: With text (default On state)
    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A ToggleSwitch that is On by default."));
    displayBox2->setBodyWidgetFixedHeight(70);

    auto switch2 = new FluToggleSwitch(displayBox2);
    switch2->setChecked(true);
    switch2->move(50, 40);

    m_scrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    // Example 3: Without text (emptyText)
    auto displayBox3 = new FluDisplayBox;
    displayBox3->setTitle(tr("A ToggleSwitch without text (emptyText)."));
    displayBox3->setBodyWidgetFixedHeight(70);

    auto switch3 = new FluToggleSwitch(displayBox3);
    switch3->setEmptyText(true);
    switch3->move(50, 40);

    m_scrollView->getMainLayout()->addWidget(displayBox3, 0, Qt::AlignTop);

    // Example 4: Text on the left
    auto displayBox4 = new FluDisplayBox;
    displayBox4->setTitle(tr("A ToggleSwitch with text on the left."));
    displayBox4->setBodyWidgetFixedHeight(70);

    auto switch4 = new FluToggleSwitch(displayBox4);
    switch4->setTextPosition(TextPosition::Left);
    switch4->move(50, 40);

    m_scrollView->getMainLayout()->addWidget(displayBox4, 0, Qt::AlignTop);

    // Example 5: Disabled state
    auto displayBox5 = new FluDisplayBox;
    displayBox5->setTitle(tr("A disabled ToggleSwitch."));
    displayBox5->setBodyWidgetFixedHeight(70);

    auto switch5 = new FluToggleSwitch(displayBox5);
    switch5->setEnabled(false);
    switch5->move(50, 40);

    m_scrollView->getMainLayout()->addWidget(displayBox5, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluToggleSwitchPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToggleSwitchPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
