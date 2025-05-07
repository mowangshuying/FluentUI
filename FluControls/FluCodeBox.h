#pragma once

#include <QPlainTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QSyntaxHighlighter>
#include <QFile>
#include <QSettings>
#include <vector>
#include <utility>

class FluCodeBox : public QTextEdit
{
    Q_OBJECT
  public:
    FluCodeBox(QWidget* parent = nullptr);

    void setCodeText(QString code);

    void resizeEvent(QResizeEvent*);

    bool eventFilter(QObject* object, QEvent *event);
  signals:
    void sizeChanged();

  public slots:
    void onThemeChanged();

  protected:
};
