#include "FluTextAreaDemo.h"

FluTextAreaDemo::FluTextAreaDemo(QWidget *parent /*= nullptr*/) : QPlainTextEdit(parent)
{
    setReadOnly(true);
    setStyleSheet("background-color: white; color: black;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QSize FluTextAreaDemo::sizeHint() const
{
    QSize size = QPlainTextEdit::sizeHint();
    QFontMetrics fm(font());
    int lineSpacing = fm.lineSpacing();
    int lines = toPlainText().count("n") + 1;
    int height = lineSpacing * lines + (2 * frameWidth());
    size.setHeight(height);
    return size;
}

void FluTextAreaDemo::setText(const QString &text)
{
    QPlainTextEdit::setPlainText(text);
    updateSize();
}

void FluTextAreaDemo::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    updateSize();
}

void FluTextAreaDemo::updateSize()
{
    adjustSize();
}
