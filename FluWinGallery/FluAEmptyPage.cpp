#include "FluAEmptyPage.h"
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluIconButton.h"

FluAEmptyPage::FluAEmptyPage(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setAlignment(Qt::AlignTop);
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(35, 35, 35, 35);

    auto titleWrap = new QWidget;
    titleWrap->setObjectName("titleWrap");
    m_mainLayout->addWidget(titleWrap);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText("A Temp Title Label");
    m_mainLayout->addWidget(m_titleLabel);

    auto tileWraHLayout = new QHBoxLayout;
    m_mainLayout->addLayout(tileWraHLayout);

    auto documentationBtn = new FluPushButton;
    documentationBtn->setText("Documentation");
    documentationBtn->setFixedWidth(160);
    tileWraHLayout->addWidget(documentationBtn, Qt::AlignLeft);

     auto sourceBtn = new FluPushButton;
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


    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAEmptyPage.qss", this);
}

void FluAEmptyPage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
