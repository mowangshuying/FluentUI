#include "FluToolTipPage.h"

FluToolTipPage::FluToolTipPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("ToolTip"));
    m_infoLabel->setText(tr("A ToolTip is a short descriptive statement that appears when the user hovers over a control. It provides supplemental information about the control's function or usage."));

    // ---- DisplayBox 1: Single-line tooltip ----
    auto displayBox1 = new FluDisplayBox;
    displayBox1->setTitle(tr("A tooltip with custom content."));
    displayBox1->getCodeExpander()->setCodeByPath("../code/ToolTipPageCode1.md");
    displayBox1->setBodyWidgetFixedHeight(96);

    auto btn1 = new FluPushButton(tr("Hover me"), displayBox1->getBodyWidget());
    btn1->move(50, 30);
    FluToolTip::setToolTip(displayBox1->getBodyWidget(), btn1, "This is a tooltip.");

    m_scrollView->getMainLayout()->addWidget(displayBox1, 0, Qt::AlignTop);

    // ---- DisplayBox 2: Multiline tooltip ----
    auto displayBox2 = new FluDisplayBox;
    displayBox2->setTitle(tr("A tooltip with rich text / multiline."));
    displayBox2->getCodeExpander()->setCodeByPath("../code/ToolTipPageCode2.md");
    displayBox2->setBodyWidgetFixedHeight(96);

    auto btn2 = new FluPushButton(tr("Hover for details"), displayBox2->getBodyWidget());
    btn2->move(50, 30);
    FluToolTip::setToolTip(displayBox2->getBodyWidget(), btn2,
                           "This tooltip spans multiple lines\nto show how longer descriptions\nare displayed gracefully.");

    m_scrollView->getMainLayout()->addWidget(displayBox2, 0, Qt::AlignTop);

    // ---- DisplayBox 3: Tooltip placement ----
    auto displayBox3 = new FluDisplayBox;
    displayBox3->setTitle(tr("A tooltip with specified placement."));
    displayBox3->getCodeExpander()->setCodeByPath("../code/ToolTipPageCode3.md");
    displayBox3->setBodyWidgetFixedHeight(150);

    struct PlacementInfo
    {
        QString name;
        FluToolTip::Placement placement;
        int x;
        int y;
    };

    const PlacementInfo placements[] = {
        {tr("TopLeft"), FluToolTip::Placement::TopLeft, 50, 20},
        {tr("Top"), FluToolTip::Placement::Top, 270, 20},
        {tr("TopRight"), FluToolTip::Placement::TopRight, 490, 20},
        {tr("Left"), FluToolTip::Placement::Left, 50, 58},
        {tr("Right"), FluToolTip::Placement::Right, 490, 58},
        {tr("BottomLeft"), FluToolTip::Placement::BottomLeft, 50, 96},
        {tr("Bottom"), FluToolTip::Placement::Bottom, 270, 96},
        {tr("BottomRight"), FluToolTip::Placement::BottomRight, 490, 96},
    };

    for (const auto& item : placements)
    {
        auto btn = new FluPushButton(item.name, displayBox3->getBodyWidget());
        btn->move(item.x, item.y);
        FluToolTip::setToolTip(displayBox3->getBodyWidget(), btn, QString("Placement: %1").arg(item.name), item.placement);
    }

    m_scrollView->getMainLayout()->addWidget(displayBox3, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluToolTipPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluToolTipPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
