#include "FluATitlePage.h"
#include <QPainter>
#include <QStyleOption>

#include "../FluControls/FluVScrollView.h"

FluATitlePage::FluATitlePage(QWidget* parent /*= nullptr*/)
{
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setAlignment(Qt::AlignTop);
    setLayout(m_vMainLayout);

    m_vMainLayout->setContentsMargins(35, 35, 35, 35);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText("A Temp Title Label");
    m_vMainLayout->addWidget(m_titleLabel);

    m_vMainLayout->addSpacing(20);

    m_vScrollView = new FluVScrollView(this);
    m_vScrollView->setObjectName("vScrollView");
    m_vMainLayout->addWidget(m_vScrollView, 1);

    m_vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);

     FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluATitlePage.qss", this);
}

void FluATitlePage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
