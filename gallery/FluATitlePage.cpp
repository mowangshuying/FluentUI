#include "FluATitlePage.h"
#include <QPainter>
#include <QStyleOption>

#include "../controls/FluVScrollView.h"
#include "../controls/FluFWScrollView.h"
#include "../controls/FluHCard.h"

FluATitlePage::FluATitlePage(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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

FluHCard* FluATitlePage::addHCard(QPixmap icon, QString title, QString context, QString key)
{
    auto card = new FluHCard(icon, title, context, this);
    card->setKey(key);
    m_scrollView->getMainLayout()->addWidget(card);
    connect(card, &FluHCard::clicked, this, [=](QString k) { emit clickedHCard(k); });
    return card;
}

void FluATitlePage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
