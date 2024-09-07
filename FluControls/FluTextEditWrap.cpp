#include "FluTextEditWrap.h"

FluTextEditWrap::FluTextEditWrap(FluTextEdit* parent /*= nullptr*/) : QWidget(parent), m_textEdit(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    if (parent != nullptr)
        parent->installEventFilter(this);
}

bool FluTextEditWrap::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == parent() && event->type() == QEvent::Resize)
    {
        auto resizeEvent = (QResizeEvent*)(event);
        resize(resizeEvent->size());
    }
    return QWidget::eventFilter(watched, event);
}

void FluTextEditWrap::paintEvent(QPaintEvent* event)
{
    if (!m_textEdit->hasFocus())
        return;

    QPainter painter(this);
    FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
}
