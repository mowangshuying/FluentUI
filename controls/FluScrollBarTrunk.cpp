#include "FluScrollBarTrunk.h"

FluScrollBarTrunk::FluScrollBarTrunk(Qt::Orientation orientation /*= Qt::Orientation::Vertical*/, QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    init(orientation);
}

void FluScrollBarTrunk::init(Qt::Orientation orientation)
{
    initHorizontal(orientation);
    initVertical(orientation);
    initOpacityAnimation();

    // onThemeChanged();
    // connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluScrollBarTrunk::initVertical(Qt::Orientation orientation)
{
    if (orientation != Qt::Orientation::Vertical)
        return;

    setFixedWidth(12);
    m_preButton = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowUp);
    m_lstButton = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowDown);

    m_Layout = new QVBoxLayout(this);
    setLayout(m_Layout);

    auto vLayout = (QVBoxLayout*)m_Layout;
    vLayout->addWidget(m_preButton, 0, Qt::AlignHCenter);
    vLayout->addStretch(1);
    vLayout->addWidget(m_lstButton, 0, Qt::AlignHCenter);
    vLayout->setContentsMargins(0, 3, 0, 3);
}

void FluScrollBarTrunk::initHorizontal(Qt::Orientation orientation)
{
    if (orientation != Qt::Orientation::Horizontal)
        return;
    setFixedHeight(12);

    m_preButton = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowLeft);
    m_lstButton = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowRight);
    m_Layout = new QHBoxLayout(this);
    setLayout(m_Layout);

    auto hLayout = (QHBoxLayout*)m_Layout;
    hLayout->addWidget(m_preButton, 0, Qt::AlignVCenter);
    hLayout->addStretch(1);
    hLayout->addWidget(m_lstButton, 0, Qt::AlignVCenter);
    hLayout->setContentsMargins(3, 0, 3, 0);
}

void FluScrollBarTrunk::initOpacityAnimation()
{
    m_effect = new QGraphicsOpacityEffect(this);
    m_animation = new QPropertyAnimation(m_effect, "opacity", this);
    m_animation->setEasingCurve(QEasingCurve::InOutCubic);
    setGraphicsEffect(m_effect);
    m_effect->setOpacity(0);
    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        if (m_effect->opacity() >= 1.0)
            m_effect->setEnabled(false); // resting fully expanded: disable to bypass effect draw, effect stays mounted
    });
}

FluScrollBarArrowButton* FluScrollBarTrunk::getPreButton()
{
    return m_preButton;
}

FluScrollBarArrowButton* FluScrollBarTrunk::getLstButton()
{
    return m_lstButton;
}

void FluScrollBarTrunk::setTrunkBackgroundColor(QColor color)
{
    m_trunkBackgroundColor = color;
}

QColor FluScrollBarTrunk::getTrunkBackgroundColor()
{
    return m_trunkBackgroundColor;
}

void FluScrollBarTrunk::expandTrunk()
{
    // Clamp opacity to 0.0 before enabling so no 1.0 + enabled dirty frame can occur; the effect
    // is permanently mounted and never re-attached.
    m_effect->setOpacity(0.0);
    m_effect->setEnabled(true);
    m_animation->setStartValue(0);
    m_animation->setEndValue(1);
    m_animation->setDuration(200);
    m_animation->start();
}

void FluScrollBarTrunk::collapseTrunk()
{
    // Clamp to 0.999 (strictly below 1.0) before enabling so a disabled resting-1.0 effect cannot
    // flash a dirty 1.0 + enabled frame; animation runs from 0.999 down to 0.
    m_effect->setOpacity(0.999);
    m_effect->setEnabled(true);
    m_animation->setStartValue(0.999);
    m_animation->setEndValue(0);
    m_animation->setDuration(200);
    m_animation->start();
}

void FluScrollBarTrunk::drawTrunkBackground(QPainter* painter)
{
    painter->setBrush(m_trunkBackgroundColor);
    painter->drawRoundedRect(rect(), 6, 6);
}

void FluScrollBarTrunk::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    drawTrunkBackground(&painter);
}

// void FluScrollBarTrunk::onThemeChanged()
// {
//     // m_trunkBackgroundColor = Qt::red;
//     if (FluThemeUtils::isLightTheme())
//     {
//         m_trunkBackgroundColor = QColor(249, 249, 249);
//     }
//     else if (FluThemeUtils::isDarkTheme())
//     {
//         m_trunkBackgroundColor = QColor(44, 44, 44);
//     }
// }
