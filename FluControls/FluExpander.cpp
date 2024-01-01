#include "FluExpander.h"

FluExpander::FluExpander(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_wrap1 = new QWidget(this);
    m_wrap1->setObjectName("wrap1");
    m_wrap1->setFixedHeight(48);

    m_hWrap1Layout = new QHBoxLayout;
    m_wrap1->setLayout(m_hWrap1Layout);
    m_hWrap1Layout->setContentsMargins(5, 5, 5, 5);

    auto btn = new FluIconButton(FluAwesomeType::ChevronDown, m_wrap1);
    btn->setObjectName("downOrUpButton");

    m_hWrap1Layout->addStretch();
    m_hWrap1Layout->addWidget(btn, Qt::AlignHCenter);

    m_wrap2 = new QWidget(this);
    m_wrap2->setObjectName("wrap2");
    m_wrap2->setFixedHeight(0);

    m_mainLayout->addWidget(m_wrap1);
    m_mainLayout->addSpacing(1);
    m_mainLayout->addWidget(m_wrap2);

    m_bDown = true;
    auto expandAni = new QPropertyAnimation(m_wrap2, "geometry");
    expandAni->setDuration(600);
    connect(btn, &QPushButton::clicked, [=](bool b) {
        if (m_bDown)
        {
            expandAni->setStartValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 0));
            expandAni->setEndValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 128));
            expandAni->start();
            m_bDown = false;
        }
        else
        {
            expandAni->setStartValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 128));
            expandAni->setEndValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 0));
            expandAni->start();
            m_bDown = true;
        }
    });

    connect(expandAni, &QPropertyAnimation::valueChanged, [=](const QVariant& value) {
        QRect tmp = value.toRect();
        m_wrap2->setFixedHeight(tmp.height());
        setFixedHeight(m_wrap1->height() + m_wrap2->height());
    });

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpander.qss", this);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpander.qss", btn);
}
