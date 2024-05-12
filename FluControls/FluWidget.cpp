#include "FluWidget.h"

FluWidget::FluWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_theme = FluThemeUtils::getUtils()->getTheme();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) {
        if (!isVisible())
            return;

        onThemeChanged();
    });
}

void FluWidget::showEvent(QShowEvent* event)
{
    // QWidget::showEvent(event);
    if (m_theme != FluThemeUtils::getUtils()->getTheme())
    {
        onThemeChanged();
        m_theme = FluThemeUtils::getUtils()->getTheme();
    }
}
