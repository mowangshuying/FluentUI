#pragma once

#include <QTextEdit>
#include "../Utils/FluUtils.h"
#include <QTextDocument>
#include <QWidget>
#include "FluScrollDelegate.h"

class FluTextEditWrap;
class FluTextEdit : public QTextEdit
{
    Q_OBJECT
  public:
    FluTextEdit(QWidget* parent = nullptr);

    bool getAutoAdjustSize();

    void setAutoAdjustSize(bool isAdjustSize);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    FluScrollDelegate* m_delegate;
    FluTextEditWrap* m_wrap;
    bool m_isAutoAdjustSize;
};
