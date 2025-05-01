#include "FluComboBox.h"

FluComboBox::FluComboBox(QWidget* parent /*= nullptr*/) : QComboBox(parent)
{
    setFixedHeight(30);
    setEditable(false);
    setView(new QListView());
    view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    onThemeChanged();
}

void FluComboBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluComboBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
