#include "FluFWScrollView.h"

FluFWScrollView::FluFWScrollView(QWidget* parent /*= nullptr*/) : FluScrollArea(parent)
{
    setWidgetResizable(true);
    setMinimumSize(0, 0);
    // setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    hideHScrollBar();

    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);
    m_vMainLayout = new FluFlowLayout(m_contextWidget);
    m_contextWidget->setObjectName("contextWidget");
    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluFWScrollView.qss");
    setStyleSheet(qss);
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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluFWScrollView.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluFWScrollView.qss", this);
    }
}
