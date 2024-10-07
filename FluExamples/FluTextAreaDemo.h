#pragma once

#include "../FluControls/FluWidget.h"
#include <QPlainTextEdit>

#include <QPlainTextEdit>

class FluTextAreaDemo : public QPlainTextEdit
{
    Q_OBJECT
  public:
    FluTextAreaDemo(QWidget *parent = nullptr);

    QSize sizeHint() const override;

    void setText(const QString &text);

  protected:
    void resizeEvent(QResizeEvent *event) override;

    void updateSize();
};