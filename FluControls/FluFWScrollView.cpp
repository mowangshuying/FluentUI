#include "FluFWScrollView.h"

FluFWScrollView::FluFWScrollView(QWidget* parent /*= nullptr*/) : FluScrollArea(parent)
{
    setWidgetResizable(true);
    setMinimumSize(0, 0);
    hideHScrollBar();

    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);
    m_vMainLayout = new FluFlowLayout(m_contextWidget);
    m_contextWidget->setObjectName("contextWidget");

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluFlowLayout* FluFWScrollView::getMainLayout()
{
    return m_vMainLayout;
}

void FluFWScrollView::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluFWScrollView.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluFWScrollView.qss"), this);
    }
}
