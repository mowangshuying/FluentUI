#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluIconButton.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluDropDownButton.h"

FluAEmptyPage::FluAEmptyPage(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setAlignment(Qt::AlignTop);
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(35, 35, 35, 35);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText("A Temp Title Label");
    m_mainLayout->addWidget(m_titleLabel);

    m_mainLayout->addSpacing(12);

    //  m_subTitleLabel = new QLabel;
    //   m_subTitleLabel->setObjectName("subTitleLabel");
    //  m_subTitleLabel->setText("");
    //   m_mainLayout->addWidget(m_subTitleLabel);

    //    m_mainLayout->addSpacing(12);

    auto tileWraHLayout = new QHBoxLayout;
    m_mainLayout->addLayout(tileWraHLayout);

    auto documentationBtn = new FluDropDownButton;
    documentationBtn->setIcon(FluAwesomeType::Document);
    documentationBtn->setText("Documentation");
    documentationBtn->setFixedWidth(160);
    tileWraHLayout->addWidget(documentationBtn, Qt::AlignLeft);

    auto sourceBtn = new FluDropDownButton;
    sourceBtn->setIcon(FluIconUtils::getSvgIcon("../res/HomeHeaderTiles/github-mark.svg"));
    sourceBtn->setSvgPath("../res/HomeHeaderTiles/github-mark.svg", "../res/HomeHeaderTiles/github-mark-white.svg");
    sourceBtn->setText("Source");
    sourceBtn->setFixedWidth(120);
    tileWraHLayout->addWidget(sourceBtn, Qt::AlignLeft);

    auto themeBtn = new FluIconButton(FluAwesomeType::Light);
    auto copyLinkBtn = new FluIconButton(FluAwesomeType::Link);
    auto sendFeedBackBtn = new FluIconButton(FluAwesomeType::Feedback);

    tileWraHLayout->addStretch();

    tileWraHLayout->addWidget(themeBtn, Qt::AlignRight);
    tileWraHLayout->addWidget(copyLinkBtn, Qt::AlignRight);
    tileWraHLayout->addWidget(sendFeedBackBtn, Qt::AlignRight);
    tileWraHLayout->addSpacing(15);

    m_vScrollView = new FluVScrollView(this);
    m_vScrollView->setObjectName("vScrollView");
    m_mainLayout->addWidget(m_vScrollView, 1);

    m_vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);

    m_infoLabel = new QLabel;
    m_infoLabel->setWordWrap(true);
    m_infoLabel->setText(
        "Type helps provide structure and hierarchy to UI. The default font for Windows is Segoe UI Variable. Best practice is to use Regular weight for most text, use Semibold for titles. The minimum values should be 12px Regular, 14px "
        "Semibold.");
    m_infoLabel->setObjectName("infoLabel");
    m_vScrollView->getMainLayout()->addWidget(m_infoLabel, 0, Qt::AlignTop);
    m_vScrollView->getMainLayout()->addSpacing(20);

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAEmptyPage.qss", this);
    // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAEmptyPage.qss", m_vScrollView);
}

void FluAEmptyPage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
