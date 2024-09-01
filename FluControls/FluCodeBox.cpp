#include "FluCodeBox.h"

FluCodeBox::FluCodeBox(QWidget* parent /*= nullptr*/) : QTextEdit(parent)
{
    setReadOnly(true);
    setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    setContextMenuPolicy(Qt::NoContextMenu);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCodeBox.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluCodeBox::setCodeText(QString code)
{
    setMarkdown(code);
}

void FluCodeBox::resizeEvent(QResizeEvent*)
{
    document()->setTextWidth(viewport()->width());
    int newHeight = document()->size().height() + document()->documentMargin();
    setFixedHeight(newHeight);
}

void FluCodeBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluCodeBox.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluCodeBox.qss", this);
    }
}
