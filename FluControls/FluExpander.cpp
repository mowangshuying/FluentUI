#include "FluExpander.h"
#include <QEvent>

FluExpander::FluExpander(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_wrap1 = new QWidget(this);
    m_wrap1->installEventFilter(this);
    m_wrap1->setObjectName("wrap1");
    m_wrap1->setFixedHeight(48);  // the wrap1 set fixed height 48.

    m_hWrap1Layout = new QHBoxLayout;
    m_wrap1->setLayout(m_hWrap1Layout);
    m_hWrap1Layout->setContentsMargins(5, 5, 5, 5);

    m_downOrUpButton = new FluIconButton(FluAwesomeType::ChevronDown, m_wrap1);
    m_downOrUpButton->setObjectName("downOrUpButton");

    //   m_hWrap1Layout->addStretch();
    //   m_hWrap1Layout->addWidget(m_downOrUpButton, Qt::AlignHCenter);

    m_wrap2 = new QWidget(this);
    m_wrap2->setObjectName("wrap2");
    m_wrap2->setFixedHeight(0);
    // m_wrap2->setMinimumHeight(50);

    m_vWrap2Layout = new QVBoxLayout;
    m_vWrap2Layout->setContentsMargins(5, 5, 5, 5);
    m_wrap2->setLayout(m_vWrap2Layout);

    m_mainLayout->addWidget(m_wrap1);
    m_mainLayout->addSpacing(1);
    m_mainLayout->addWidget(m_wrap2);

    m_bDown = true;
    auto expandAni = new QPropertyAnimation(m_wrap2, "geometry");
    expandAni->setDuration(200);

    // m_wrap2Height = 128;
    connect(m_downOrUpButton, &QPushButton::clicked, [=](bool b) {
        if (m_bDown)
        {
            expandAni->setStartValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 0));
            expandAni->setEndValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), m_wrap2->sizeHint().height()));
            expandAni->start();

            m_downOrUpButton->setType1(FluAwesomeType::ChevronUp);
            m_bDown = false;
        }
        else
        {
            expandAni->setStartValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), m_wrap2->sizeHint().height()));
            expandAni->setEndValue(QRect(m_wrap2->x(), m_wrap2->y(), m_wrap2->width(), 0));
            expandAni->start();
            m_downOrUpButton->setType1(FluAwesomeType::ChevronDown);
            m_bDown = true;
        }
    });

    connect(expandAni, &QPropertyAnimation::valueChanged, [=](const QVariant& value) {
        QRect tmp = value.toRect();
        m_wrap2->setFixedHeight(tmp.height());
        setFixedHeight(m_wrap1->height() + m_wrap2->height() + 1);
        update();
    });

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpander.qss", this);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpander.qss", m_downOrUpButton);
}

void FluExpander::resizeEvent(QResizeEvent* event)
{
    int nX = m_wrap1->width() - m_downOrUpButton->height() - 5;
    int nY = (m_wrap1->height() - m_downOrUpButton->height()) / 2;
    m_downOrUpButton->move(nX, nY);
}

bool FluExpander::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_wrap1 && event->type() == QEvent::MouseButtonRelease)
    {
        m_downOrUpButton->clicked();
    }
    return QWidget::eventFilter(watched, event);
}

void FluExpander::onThemeChanged()
{
    if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpander.qss", this);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluExpander.qss", m_downOrUpButton);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluExpander.qss", this);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluExpander.qss", m_downOrUpButton);
    }
}
