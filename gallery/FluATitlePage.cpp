#include "FluATitlePage.h"
#include <QPainter>
#include <QStyleOption>

#include "../Controls/FluVScrollView.h"
#include "../Controls/FluFWScrollView.h"

FluATitlePage::FluATitlePage(QWidget* parent /*= nullptr*/)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setAlignment(Qt::AlignTop);
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(35, 35, 35, 35);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText(tr("A Temp Title Label"));
    m_mainLayout->addWidget(m_titleLabel);

    m_mainLayout->addSpacing(20);

    m_scrollView = new FluFWScrollView(this);
    m_scrollView->setObjectName("vScrollView");
    m_mainLayout->addWidget(m_scrollView, 1);

    m_scrollView->getMainLayout()->setAlignment(Qt::AlignTop);
    FluStyleSheetUtils::setQssByFileName("FluATitlePage.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluATitlePage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
