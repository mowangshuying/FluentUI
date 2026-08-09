#include "FluToggleButtonPage.h"

#include <QHBoxLayout>
#include <QLabel>

FluToggleButtonPage::FluToggleButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ToggleButton"));

    // m_subTitleLabel->setText("FluentUI::FluToggleButton");

    m_infoLabel->setText(tr("ToggleButton demos."));

    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A simple toggle button with text content."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ToggleButtonPageCode1.md");
    auto btn1 = new FluToggleButton(this);
    btn1->setText(tr("Toggle Button"));
    displayBox1->setBodyWidgetFixedHeight(96);
    displayBox1->getBodyLayout()->addWidget(btn1);
    m_scrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    // ---- DisplayBox 2: checked, disabled and state change signal ----
    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A toggle button with checked state, disabled state and a state label."));
    displayBox2->getCodeExpander()->setCodeByPath("../code/ToggleButtonPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(96);

    auto hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(12);

    auto btn2 = new FluToggleButton;
    btn2->setText(tr("Checked"));
    btn2->setToggled(true);
    hLayout->addWidget(btn2);

    auto btn3 = new FluToggleButton;
    btn3->setText(tr("Disabled"));
    btn3->setEnabled(false);
    hLayout->addWidget(btn3);

    auto btn4 = new FluToggleButton;
    btn4->setText(tr("Checked & Disabled"));
    btn4->setToggled(true);
    btn4->setEnabled(false);
    hLayout->addWidget(btn4);

    auto stateLabel = new QLabel(tr("State: Checked"));
    stateLabel->setObjectName("stateLabel");
    stateLabel->setFixedWidth(120);
    hLayout->addWidget(stateLabel);

    connect(btn2, &FluToggleButton::toggledChanged, this, [=](bool isToggled) {
        stateLabel->setText(isToggled ? tr("State: Checked") : tr("State: Unchecked"));
    });

    displayBox2->getBodyLayout()->addLayout(hLayout);
    m_scrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluToggleButtonPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToggleButtonPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
