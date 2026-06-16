#include "FluSubMenuItemWidget.h"

FluSubMenuItemWidget::FluSubMenuItemWidget(FluRoundMenu* menu, QListWidgetItem* item, QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_menu = menu;
    m_item = item;
}

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
void FluSubMenuItemWidget::enterEvent(QEnterEvent* event)
#else
void FluSubMenuItemWidget::enterEvent(QEvent* event)
#endif
{
    QWidget::enterEvent(event);
    emit showMenuSig(m_item);
}

void FluSubMenuItemWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);

    int nW = m_menu->getView()->iconSize().width();
    int nH = m_menu->getView()->iconSize().height();
    painter.drawPixmap(QRect(width() - nW , height() / 2 - nH / 2, nW, nH), FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronRight, FluThemeUtils::getUtils()->getTheme()));
}

QListWidgetItem* FluSubMenuItemWidget::getItem()
{
    return m_item;
}

FluRoundMenu* FluSubMenuItemWidget::getMenu()
{
    return m_menu;
}
