#include "FluIndicatorRoundMenu.h"

FluIndicatorRoundMenu::FluIndicatorRoundMenu(QWidget* parent) : FluIndicatorRoundMenu("", FluAwesomeType::None, parent)
{
}

FluIndicatorRoundMenu::FluIndicatorRoundMenu(QString title, FluAwesomeType iconType, QWidget* parent) : FluRoundMenu(title, iconType, parent)
{
    getView()->setItemDelegate(new FluIndicatorMenuItemDeleage);
}

void FluIndicatorRoundMenu::popup(QPoint pos)
{
    if (actions().isEmpty())
    {
        close();
        return;
    }

    auto parentWidget = (QWidget*)parent();
    if (parentWidget != nullptr)
    {
        if (getView()->width() < parentWidget->width())
        {
            getView()->setMinimumWidth(parentWidget->width());
            adjustSize();
        }
    }

    // getView()->setProperty("radiusType", "NoTopRadius");
    getView()->style()->polish(getView());
    getView()->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::NoFocus);
    exec(pos);
}
