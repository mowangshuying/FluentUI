#include "FluVScrollView.h"

FluVScrollView::FluVScrollView(QWidget* parent /*= nullptr*/) : FluScrollArea(parent)
{
    setWidgetResizable(true);
    setMinimumSize(0, 0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hideHScrollBar();

    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);
    m_vMainLayout = new QVBoxLayout(m_contextWidget);
    m_contextWidget->setObjectName("contextWidget");

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluVScrollView::~FluVScrollView()
{
}

QVBoxLayout* FluVScrollView::getMainLayout()
{
    return m_vMainLayout;
}

void FluVScrollView::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluVScrollView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
