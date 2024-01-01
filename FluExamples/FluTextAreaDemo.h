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
        setReadOnly(true);  // 设置为只读，禁止编辑

        // 设置默认样式
        setStyleSheet("background-color: white; color: black;");

        // 设置一些默认属性
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }

    QSize sizeHint() const override
    {
        // 自动适应高度
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
        // 调整尺寸
        adjustSize();
    }
};