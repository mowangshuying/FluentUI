#pragma once

#include <QWidget>
#include <QPlainTextEdit>

#include <QPlainTextEdit>

class FluTextAreaDemo : public QPlainTextEdit
{
    Q_OBJECT
  public:
    explicit FluTextAreaDemo(QWidget *parent = nullptr) : QPlainTextEdit(parent)
    {
        setReadOnly(true);
        setStyleSheet("background-color: white; color: black;");
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }

    QSize sizeHint() const override
    {
        QSize size = QPlainTextEdit::sizeHint();
        QFontMetrics fm(font());
        int lineSpacing = fm.lineSpacing();
        int lines = toPlainText().count("n") + 1;
        int height = lineSpacing * lines + (2 * frameWidth());
        size.setHeight(height);
        return size;
    }

    void setText(const QString &text)
    {
        QPlainTextEdit::setPlainText(text);
        updateSize();
    }

  protected:
    void resizeEvent(QResizeEvent *event) override
    {
        QPlainTextEdit::resizeEvent(event);
        updateSize();
    }

    void updateSize()
    {
        adjustSize();
    }
};