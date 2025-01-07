#include "FluBorderPage.h"

FluBorderPage::FluBorderPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("Border"));
    m_infoLabel->setText(tr("Use a Border control to draw a boundary line, background or both, around another object. A Border can contain only one child object"));

    auto displayBox = new FluDisplayBoxEx;
    displayBox->setTitle(tr("A Border around a TextBlock."));
    displayBox->getCodeExpander()->setCodeByPath("../code/BorderPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(120);

    m_border = new FluBorder;
    m_border->setFixedSize(250, 40);
    m_border->setText(tr("Text inside a border"));
    displayBox->getBodyContentLayout()->addWidget(m_border);

    FluVRadioGroupBox* group = new FluVRadioGroupBox(tr("Background"), this);
    auto btn1 = new FluRadioButton(tr("Green"), group);
    auto btn2 = new FluRadioButton(tr("Pink"), group);
    auto btn3 = new FluRadioButton(tr("Blue"), group);
    group->addRadioButton(btn1);
    group->addRadioButton(btn2);
    group->addRadioButton(btn3);
    connect(btn1, &FluRadioButton::toggled, [=]() {
        m_border->setTExtColor(Qt::white);
        m_border->setBackGroundColor(tr("green"));
    });
    connect(btn2, &FluRadioButton::toggled, [=]() {
        m_border->setTExtColor(Qt::white);
        m_border->setBackGroundColor(tr("pink"));
    });
    connect(btn3, &FluRadioButton::toggled, [=]() {
        m_border->setTExtColor(Qt::white);
        m_border->setBackGroundColor(tr("blue"));
    });

    displayBox->getBodyRightLayout()->addWidget(group);

    m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluBorderPage.qss", this);
}

void FluBorderPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        if (m_border->isTransparentBackground())
            m_border->setTExtColor(Qt::black);
        else
            m_border->setTExtColor(Qt::white);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluBorderPage.qss", this);
    }
    else
    {
        m_border->setTExtColor(Qt::white);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluBorderPage.qss", this);
    }
}
