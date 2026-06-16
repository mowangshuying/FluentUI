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
    m_preBtn = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowUp);
    m_lstBtn = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowDown);

    m_Layout = new QVBoxLayout(this);
    setLayout(m_Layout);

    auto vLayout = (QVBoxLayout*)m_Layout;
    vLayout->addWidget(m_preBtn, 0, Qt::AlignHCenter);
    vLayout->addStretch(1);
    vLayout->addWidget(m_lstBtn, 0, Qt::AlignHCenter);
    vLayout->setContentsMargins(0, 3, 0, 3);
}

void FluScrollBarTrunk::initHorizontal(Qt::Orientation orientation)
{
    if (orientation != Qt::Orientation::Horizontal)
        return;
    setFixedHeight(12);

    m_preBtn = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowLeft);
    m_lstBtn = new FluScrollBarArrowButton(FluScrollBarArrowButtonType::ArrowRight);
    m_Layout = new QHBoxLayout(this);
    setLayout(m_Layout);

    auto hLayout = (QHBoxLayout*)m_Layout;
    hLayout->addWidget(m_preBtn, 0, Qt::AlignVCenter);
    hLayout->addStretch(1);
    hLayout->addWidget(m_lstBtn, 0, Qt::AlignVCenter);
    hLayout->setContentsMargins(3, 0, 3, 0);
}

void FluScrollBarTrunk::initOpacityAnimation()
{
    m_effect = new QGraphicsOpacityEffect(this);
    m_animation = new QPropertyAnimation(m_effect, "opacity", this);
    setGraphicsEffect(m_effect);
    m_effect->setOpacity(0);
}

FluScrollBarArrowButton* FluScrollBarTrunk::getPreBtn()
{
    return m_preBtn;
}

FluScrollBarArrowButton* FluScrollBarTrunk::getLstBtn()
{
    return m_lstBtn;
}

void FluScrollBarTrunk::setTrunkBackgoundColor(QColor color)
{
    m_trunkBackgoundColor = color;
}

QColor FluScrollBarTrunk::getTrunkBackgoundColor()
{
    return m_trunkBackgoundColor;
}

void FluScrollBarTrunk::expandTrunk()
{
    m_animation->setStartValue(0);
    m_animation->setEndValue(1);
    m_animation->setDuration(200);
    m_animation->start();
}

void FluScrollBarTrunk::collapseTrunk()
{
    m_animation->setStartValue(1);
    m_animation->setEndValue(0);
    m_animation->setDuration(200);
    m_animation->start();
}

void FluScrollBarTrunk::drawTrunkBackground(QPainter* painter)
{
    painter->setBrush(m_trunkBackgoundColor);
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
//     // m_trunkBackgoundColor = Qt::red;
//     if (FluThemeUtils::isLightTheme())
//     {
//         m_trunkBackgoundColor = QColor(249, 249, 249);
//     }
//     else if (FluThemeUtils::isDarkTheme())
//     {
//         m_trunkBackgoundColor = QColor(44, 44, 44);
//     }
// }
