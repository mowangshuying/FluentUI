#pragma once

#include <QWidget>
#include <QEvent>
#include <QResizeEvent>
#include "../FluUtils/FluUtils.h"
#include "FluTextEdit.h"

class FluTextEditWrap : public QWidget
{
    Q_OBJECT
  public:
       FluTextEditWrap(FluTextEdit* parent = nullptr) : QWidget(parent), m_textEdit(parent)
      {
          setAttribute(Qt::WA_TranslucentBackground);
          if (parent != nullptr)
              parent->installEventFilter(this);
      }

      bool eventFilter(QObject* watched, QEvent* event)
      {
          if (watched == parent() && event->type() == QEvent::Resize)
          {
              auto resizeEvent = (QResizeEvent*)(event);
              resize(resizeEvent->size());
          }
          return QWidget::eventFilter(watched, event);
      }

      void paintEvent(QPaintEvent* event)
      {
          if (!m_textEdit->hasFocus())
              return;

          QPainter painter(this);
          FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
      }

  protected:
      FluTextEdit* m_textEdit;
};
