#include "FluColorFlyout.h"

FluColorFlyout::FluColorFlyout(QWidget* targetWidget) : FluWidget(nullptr), m_targetWidget(targetWidget)
{
    // LOG_DEBUG << "called";

    m_gridLayout = new QGridLayout;
    setLayout(m_gridLayout);
    setMinimumSize(120, 120);
    m_gridLayout->setContentsMargins(16, 16, 16, 16);
    // m_gridLayout->setSpacing(25);

    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);

    onThemeChanged();
}

FluColorFlyout::~FluColorFlyout()
{
    // LOG_DEBUG << "called";
}

void FluColorFlyout::addColorButton(FluColorButton* colorBtn, int row, int col)
{
    m_gridLayout->addWidget(colorBtn, row, col);
    connect(colorBtn, &FluColorButton::clicked, [=]() {
        emit colorChanged(colorBtn->getBackgroundColor());
        close();
    });
}

void FluColorFlyout::addColorButton(FluColorButton* colorBtn)
{
    int count = m_gridLayout->count();
    int row = count / 3;
    int col = count % 3;
    addColorButton(colorBtn, row, col);
}

void FluColorFlyout::showEvent(QShowEvent* event)
{
    FluWidget::showEvent(event);
    if (m_targetWidget == nullptr)
        return;

    QPoint targetPos = m_targetWidget->mapToGlobal(QPoint(0, 0));
    int nX = targetPos.x();
    int nY = targetPos.y() + m_targetWidget->height() + 5;
    move(nX, nY);
}

void FluColorFlyout::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluColorFlyout::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluColorFlyout.qss", this, FluThemeUtils::getUtils()->getTheme());
}
