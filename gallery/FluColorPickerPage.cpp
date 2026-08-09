#include "FluColorPickerPage.h"
#include "../utils/FluUtils.h"
#include "../controls/FluDisplayBoxEx.h"
#include "../controls/FluColorView.h"
#include "../controls/FluVScrollView.h"

FluColorPickerPage::FluColorPickerPage(QWidget* parent) : FluAEmptyPage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("ColorPicker"));
    m_infoLabel->setText(tr("A selectable color spectrum"));

    auto displaybox1 = new FluDisplayBoxEx;
    displaybox1->setTitle(tr("ColorPicker Properties"));
    displaybox1->getCodeExpander()->setCodeByPath("../code/ColorPickerPageCode1.md");

    auto colorView = new FluColorView;
    displaybox1->getBodyContentLayout()->addWidget(colorView);

    m_scrollView->getMainLayout()->addWidget(displaybox1, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluColorPickerPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluColorPickerPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}