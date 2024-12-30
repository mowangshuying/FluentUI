#include "FluSubMenuItemWidget.h"

FluSubMenuItemWidget::FluSubMenuItemWidget(FluRoundMenu* menu, QListWidgetItem* item, QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    m_menu = menu;
    m_item = item;
}

void FluSubMenuItemWidget::enterEvent(QEnterEvent* event)
{
    QWidget::enterEvent(event);
    emit showMenuSig(m_item);
}

void FluSubMenuItemWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.drawPixmap(QRect(width() - 10, height() / 2 - 9 / 2, 9, 9), FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChevronRight, FluThemeUtils::getUtils()->getTheme()));
}

QListWidgetItem* FluSubMenuItemWidget::getItem()
{
    return m_item;
}

FluRoundMenu* FluSubMenuItemWidget::getMenu()
{
    return m_menu;
}
