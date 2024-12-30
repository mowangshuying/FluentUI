#include "FluCompleterMenu.h"

FluCompleterMenu::FluCompleterMenu(QWidget* parent /*= nullptr*/) : FluCompleterMenu("", FluAwesomeType::None, parent)
{
}

FluCompleterMenu::FluCompleterMenu(QString title, FluAwesomeType iconType, QWidget* parent /*= nullptr*/) : FluRoundMenu(title, iconType, parent)
{
}
