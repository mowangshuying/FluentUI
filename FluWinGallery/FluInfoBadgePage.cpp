#include "FluInfoBadgePage.h"

FluInfoBadgePage::FluInfoBadgePage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("InfoBadge"));
    m_infoLabel->setText(tr("Badging is a non-instrusive and intuitive way to display notifications or bring focus to an area within an app - weheher that be for notifications, indicating new content, or showing an alert."));

    auto displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("InfoBadge with Different Value."));
    displayBox->getCodeExpander()->setCodeByPath(FLURC("code/InfoBadgePageCode1.md"));
    displayBox->setBodyWidgetFixedHeight(96);

    auto targetWidget1 = new QWidget(displayBox->getBodyWidget());
    targetWidget1->setFixedSize(40, 40);
    targetWidget1->setStyleSheet("background-color:gray;border-radius:4px;");
    targetWidget1->move(50, 30);
    FluInfoBadge::setInfoBadge(displayBox->getBodyWidget(), targetWidget1, 1);

    auto targetWidget2 = new QWidget(displayBox->getBodyWidget());
    targetWidget2->setFixedSize(40, 40);
    targetWidget2->setStyleSheet("background-color:gray;border-radius:4px;");
    targetWidget2->move(150, 30);
    FluInfoBadge::setInfoBadge(displayBox->getBodyWidget(), targetWidget2, 22);

    auto targetWidget3 = new QWidget(displayBox->getBodyWidget());
    targetWidget3->setFixedSize(40, 40);
    targetWidget3->setStyleSheet("background-color:gray;border-radius:4px;");
    targetWidget3->move(250, 30);
    FluInfoBadge::setInfoBadge(displayBox->getBodyWidget(), targetWidget3, 333);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluInfoBadgePage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluInfoBadgePage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluInfoBadgePage.qss"), this);
    }
}
