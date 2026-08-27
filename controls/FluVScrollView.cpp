#include "FluVScrollView.h"

FluVScrollView::FluVScrollView(QWidget* parent /*= nullptr*/) : FluScrollArea(parent)
{
    setWidgetResizable(true);
    setMinimumSize(0, 0);
    setFrameStyle(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hideHScrollBar();

    setContentsMargins(0, 0, 0, 0);

    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);
    m_mainLayout = new QVBoxLayout(m_contextWidget);
    m_contextWidget->setObjectName("contextWidget");

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluVScrollView::~FluVScrollView()
{
}

QVBoxLayout* FluVScrollView::getMainLayout()
{
    return m_mainLayout;
}

void FluVScrollView::addWidget(QWidget* widget, int stretch /*= 0*/, Qt::Alignment alignment /*= Qt::Alignment()*/)
{
    m_mainLayout->addWidget(widget, stretch, alignment);
}

void FluVScrollView::addSpacing(int size)
{
    m_mainLayout->addSpacing(size);
}

void FluVScrollView::setAlignment(Qt::Alignment alignment)
{
    m_mainLayout->setAlignment(alignment);
}

void FluVScrollView::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluVScrollView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
