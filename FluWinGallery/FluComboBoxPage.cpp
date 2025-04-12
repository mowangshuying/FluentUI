#include "FluComboBoxPage.h"

FluComboBoxPage::FluComboBoxPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ComboBox"));
    m_infoLabel->setText(tr("Use a ComboBox when you need to conserve on-screen space and when users select only one option at a time. A ComboBox shows only the currently selected item."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A ComboBox with items defined inline and its width set."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/ComboBoxPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(96);

    auto comboBox = new FluComboBoxEx(displayBox);
    comboBox->setFixedWidth(200);
    comboBox->move(50, 50);
    comboBox->addItem(tr("Blue"));
    comboBox->addItem(tr("Green"));
    comboBox->addItem(tr("Red"));
    comboBox->addItem(tr("Yellow"));

    auto colorLabel = new FluColorLabel(displayBox);
    colorLabel->setObjectName("colorLabel");
    colorLabel->setProperty("color", "Blue");
    colorLabel->setFixedSize(100, 30);
    colorLabel->move(50, 90);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    connect(comboBox, &FluComboBoxEx::currentTextChanged, [=](const QString& text) {
        colorLabel->setProperty("color", text);
        colorLabel->style()->polish(colorLabel);
    });
    onThemeChanged();
}

void FluComboBoxPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluComboBoxPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluComboBoxPage.qss"), this);
    }
}
