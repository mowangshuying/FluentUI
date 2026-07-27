#include "FluFWScrollView.h"

FluFWScrollView::FluFWScrollView(QWidget* parent /*= nullptr*/) : FluScrollArea(parent)
{
    setWidgetResizable(true);
    setMinimumSize(0, 0);
    hideHScrollBar();

    m_contextWidget = new QWidget(this);
    setWidget(m_contextWidget);
    m_mainLayout = new FluFlowLayout(m_contextWidget);
    m_contextWidget->setObjectName("contextWidget");

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluFlowLayout* FluFWScrollView::getMainLayout()
{
    return m_mainLayout;
}

void FluFWScrollView::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluFWScrollView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
