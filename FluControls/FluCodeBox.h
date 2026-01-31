#pragma once

#include <QTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QSyntaxHighlighter>
#include <QFile>
#include <QSettings>
#include <vector>
#include <utility>
#include <QWheelEvent>
#include <QPointer>

class FluCodeSyntaxHighlighter;

class FluCodeBox : public QTextEdit
{
    Q_OBJECT
  public:
    FluCodeBox(QWidget* parent = nullptr);

    void setCodeText(QString code);

    void wheelEvent(QWheelEvent* event)
    {
        event->ignore();
    }

    void resizeEvent(QResizeEvent*);

    // bool eventFilter(QObject* object, QEvent *event);
    
  protected:
    void setHtmlWithSyntaxHighlighting(const QString& html);

  signals:
    void sizeChanged();

  public slots:
    void onThemeChanged();

  private:
    QPointer<FluCodeSyntaxHighlighter> m_syntaxHighlighter;
};