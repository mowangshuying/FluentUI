﻿#include "FluRepeatButtonPage.h"

FluRepeatButtonPage::FluRepeatButtonPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("RepeatButton"));
    // m_subTitleLabel->setText("FluentUI::RepeatButton");
    m_infoLabel->setText(tr("The RepeatButton control is like a standard button, except that the Click event occurs continuously while the user presses the RepeatButton."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A simple RepeatButton with text context."));

    displayBox->getCodeExpander()->setCodeByPath("../code/RepeatButtonPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(64);

    auto repeatButton = new FluRepeatButton;
    repeatButton->setFixedSize(120, 30);
    repeatButton->setText(tr("Click and hold"));
    displayBox->getBodyLayout()->addWidget(repeatButton);
    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluRepeatButtonPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluRepeatButtonPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
