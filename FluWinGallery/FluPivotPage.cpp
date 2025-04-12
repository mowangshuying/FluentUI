#include "FluPivotPage.h"

FluPivotPage::FluPivotPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Pivot"));
    m_infoLabel->setText(tr("A pivot allows you to show a collection of items from different sources in a tabbed view."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A basic pivot."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/PivotPageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(360);

    auto pivot = new FluPivot;
    // pivot->setFixedWidth(800);

    auto label1 = new QLabel;
    label1->setObjectName("label");
    label1->setText(tr("This is a All Page"));
    label1->setAlignment(Qt::AlignCenter);
    pivot->addPivotItem(tr("All"), label1);

    auto label2 = new QLabel;
    label2->setObjectName("label");
    label2->setText(tr("This is a Unread Page"));
    label2->setAlignment(Qt::AlignCenter);
    pivot->addPivotItem(tr("Unread"), label2);

    auto label3 = new QLabel;
    label3->setObjectName("label");
    label3->setText(tr("This is Flagged Page"));
    label3->setAlignment(Qt::AlignCenter);
    pivot->addPivotItem(tr("Flagged"), label3);

    auto label4 = new QLabel;
    label4->setObjectName("label");
    label4->setText(tr("This is Urgent Page"));
    label4->setAlignment(Qt::AlignCenter);
    pivot->addPivotItem(tr("Urgent"), label4);

    displayBox->getBodyLayout()->addWidget(pivot);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    onThemeChanged();
}

void FluPivotPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluPivotPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluPivotPage.qss"), this);
    }
}
