#include "FluCommandBarIconTextItem.h"
#include <QStyleOption>
#include <QStyle>
#include <QPainter>

inline FluCommandBarIconTextItem::FluCommandBarIconTextItem(QWidget* parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    m_iconBtn = new QPushButton;
    m_iconBtn->setIconSize(QSize(20, 20));
    m_iconBtn->setObjectName("iconBtn");
    m_hMainLayout->addWidget(m_iconBtn);

    m_textLabel = new QLabel;
    m_textLabel->setAlignment(Qt::AlignLeft);
    m_hMainLayout->addWidget(m_textLabel);
    onThemeChanged();
}

void FluCommandBarIconTextItem::mouseReleaseEvent(QMouseEvent* event)
{
    FluCommandBarItem::mouseReleaseEvent(event);
    emit clicked();
}

inline void FluCommandBarIconTextItem::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
