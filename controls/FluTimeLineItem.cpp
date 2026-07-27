#include "FluTimeLineItem.h"

FluTimeLineItem::FluTimeLineItem(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 20, 0, 20);

    m_iconLayout = new QVBoxLayout;
    m_iconLayout->setAlignment(Qt::AlignTop);
    m_iconLayout->setContentsMargins(0, 0, 0, 0);

    m_itemLayout = new QVBoxLayout;
    m_itemLayout->setContentsMargins(0, 0, 0, 0);

    m_icon = new FluTimeLineIcon;
    m_iconLayout->addWidget(m_icon, 0, Qt::AlignTop);

    m_mainLayout->addLayout(m_iconLayout);
    m_mainLayout->addLayout(m_itemLayout);
    setMinimumHeight(40);
}

void FluTimeLineItem::addTextItem(QString text)
{
    auto label = new FluLabel;
    label->setWordWrap(true);
    label->setLabelStyle(FluLabelStyle::CaptionTextBlockStyle);
    label->setText(text);
    label->setMinimumHeight(40);
    m_itemLayout->addWidget(label);
    setMinimumHeight(m_itemLayout->count() * 40);
}

FluLabel* FluTimeLineItem::getLabelAt(int index)
{
    if (index < 0 || index >= m_itemLayout->count())
        return nullptr;

    return static_cast<FluLabel*>(m_itemLayout->itemAt(index)->widget());
}

void FluTimeLineItem::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // draw line;
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(29, 29, 29));
    if (FluThemeUtils::isDarkTheme())
        painter.setBrush(QColor(229, 229, 229));

    painter.drawRect(QRectF(20 - 1.5, 0, 3, 20));

    // draw line;
    // painter.setPen(Qt::NoPen);
    // painter.setBrush(Qt::lightGray);
    painter.drawRect(QRectF(20 - 1.5, 60, 3, height() - 60));
}
