#include "FluColorPickerPage.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluDisplayBoxEx.h"
#include "../Controls/FluColorView.h"
#include "../Controls/FluVScrollView.h"

FluColorPickerPage::FluColorPickerPage(QWidget* parent) : FluAEmptyPage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("ColorPicker"));
    m_infoLabel->setText(tr("A selectable color spectrum"));

    auto displaybox1 = new FluDisplayBoxEx;
    displaybox1->setTitle(tr("ColorPicker Properties"));

    auto colorView = new FluColorView;
    displaybox1->getBodyContentLayout()->addWidget(colorView);

    m_vScrollView->getMainLayout()->addWidget(displaybox1, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluColorPickerPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluColorPickerPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}