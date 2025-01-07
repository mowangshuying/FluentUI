#include "FluCompleterMenu.h"
#include "FluIndicatorMenuItemDeleage.h"
#include "FluAutoSuggestBox.h"
#include <QKeyEvent>
#include <QStyle>

FluCompleterMenu::FluCompleterMenu(FluAutoSuggestBox* autoSuggestBox, QWidget* parent /*= nullptr*/) : FluCompleterMenu("", FluAwesomeType::None, parent)
{
    m_autoSuggestBox = autoSuggestBox;
    getView()->setItemDelegate(new FluIndicatorMenuItemDeleage);
    installEventFilter(this);
    setItemHeight(30);
}

FluCompleterMenu::FluCompleterMenu(QString title, FluAwesomeType iconType, QWidget* parent /*= nullptr*/) : FluRoundMenu(title, iconType, parent)
{
}

void FluCompleterMenu::updateActions(std::vector<QString> keys)
{
    FluRoundMenu::clear();
    for (auto key : keys)
    {
        auto action = new FluAction(key);
        addAction(action);
    }
}

void FluCompleterMenu::popup(QPoint pos)
{
    if (actions().isEmpty())
    {
        close();
        return;
    }

    if (getView()->width() < m_autoSuggestBox->width())
    {
        getView()->setMinimumWidth(m_autoSuggestBox->width());
        adjustSize();
    }

    getView()->setProperty("radiusType", "NoTopRadius");
    getView()->style()->polish(getView());
    getView()->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::NoFocus);
    exec(pos);
}

bool FluCompleterMenu::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() != QEvent::KeyPress)
        return FluRoundMenu::eventFilter(watched, event);

    m_autoSuggestBox->hockEvent(event);
    getView()->hockEvent(event);

    QKeyEvent* keyEvent = (QKeyEvent*)event;
    if (keyEvent->key() == Qt::Key_Escape)
    {
        close();
    }
    else if ((keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) && getView()->currentRow() >= 0)
    {
        FluCompleterMenu::onItemClicked(getView()->currentItem());
        close();
    }

    return FluRoundMenu::eventFilter(watched, event);
}
