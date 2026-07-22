#include "FluLineEdit.h"

FluLineEdit::FluLineEdit(QWidget* parent /*= nullptr*/) : QLineEdit(parent)
{
    //  setContentsMargins(4, 4, 4, 4);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluLineEdit::paintEvent(QPaintEvent* event)
{
    QLineEdit::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHints(QPainter::Antialiasing);
    if (!hasFocus())
        return;

    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

void FluLineEdit::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluLineEdit.qss", this, FluThemeUtils::getUtils()->getTheme());
}
