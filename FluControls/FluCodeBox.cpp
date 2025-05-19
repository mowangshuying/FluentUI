#include "FluCodeBox.h"

FluCodeBox::FluCodeBox(QWidget* parent /*= nullptr*/) : QTextEdit(parent)
{
    setReadOnly(true);
    setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
    setContextMenuPolicy(Qt::NoContextMenu);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    onThemeChanged();
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

// bool FluCodeBox::eventFilter(QObject* object, QEvent* event)
// {
//     if (event->type() == QEvent::Wheel)
//     {
//         return true;
//     }

//     return false;
// }

void FluCodeBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluCodeBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
