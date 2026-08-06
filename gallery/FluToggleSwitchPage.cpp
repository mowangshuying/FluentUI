#include "FluToggleSwitchPage.h"

#include "../controls/FluLabel.h"

FluToggleSwitchPage::FluToggleSwitchPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ToggleSwitch"));
    m_infoLabel->setText(tr("Use ToggleSwitch controls to present users with exactly two mutually exclusive options (like on/off), where choosing an option results in an immediate commit. A toggle switch should have a single label."));

    // Helper: create a switch with specified size and properties
    auto createSwitch = [](SwitchSize size, bool checked, bool emptyText = false) -> FluToggleSwitch* {
        auto* sw = new FluToggleSwitch;
        sw->setSize(size);
        if (emptyText)
            sw->setEmptyText(true);
        else
            sw->setOnOffText("On", "Off");
        if (checked)
            sw->setChecked(true);
        return sw;
    };

    // Helper: create a row with a label and three size variants (Normal / Medium / Small)
    auto createSizeRow = [&](const QString& label, bool checked, bool emptyText = false, bool disabled = false, TextPosition textPos = TextPosition::Right) -> QWidget* {
        auto* row = new QWidget;
        auto* hl = new QHBoxLayout(row);
        hl->setContentsMargins(12, 8, 12, 8);
        hl->setSpacing(16);
        auto* lbl = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
        lbl->setText(label);
        lbl->setFixedWidth(110);
        hl->addWidget(lbl);
        for (auto sz : {SwitchSize::Normal, SwitchSize::Medium, SwitchSize::Small})
        {
            auto* sw = createSwitch(sz, checked, emptyText);
            sw->setTextPosition(textPos);
            if (disabled)
                sw->setEnabled(false);
            hl->addWidget(sw);
        }
        hl->addStretch(1);
        return row;
    };

    // Example 1: Default Off state, three sizes
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("ToggleSwitch with text (Off) — three sizes."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ToggleSwitchPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(70);
    displayBox1->getBodyLayout()->addWidget(createSizeRow("Default Off:", false));
    m_scrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    // Example 2: Default On state, three sizes
    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("ToggleSwitch (On) — three sizes."));
    displayBox2->setBodyWidgetFixedHeight(70);
    displayBox2->getBodyLayout()->addWidget(createSizeRow("Default On:", true));
    m_scrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    // Example 3: Empty text, three sizes
    auto displayBox3 = new FluDisplayBox;
    displayBox3->setTitle(tr("ToggleSwitch without text (emptyText) — three sizes."));
    displayBox3->setBodyWidgetFixedHeight(70);
    displayBox3->getBodyLayout()->addWidget(createSizeRow("Empty Text:", false, true));
    m_scrollView->getMainLayout()->addWidget(displayBox3, 0, Qt::AlignTop);

    // Example 4: Text on left, three sizes
    auto displayBox4 = new FluDisplayBox;
    displayBox4->setTitle(tr("ToggleSwitch with text on the left — three sizes."));
    displayBox4->setBodyWidgetFixedHeight(70);
    displayBox4->getBodyLayout()->addWidget(createSizeRow("Text Left:", false, false, false, TextPosition::Left));
    m_scrollView->getMainLayout()->addWidget(displayBox4, 0, Qt::AlignTop);

    // Example 5: Disabled state, three sizes
    auto displayBox5 = new FluDisplayBox;
    displayBox5->setTitle(tr("Disabled ToggleSwitch — three sizes."));
    displayBox5->setBodyWidgetFixedHeight(70);
    displayBox5->getBodyLayout()->addWidget(createSizeRow("Disabled:", false, false, true));
    m_scrollView->getMainLayout()->addWidget(displayBox5, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluToggleSwitchPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToggleSwitchPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
