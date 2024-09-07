#pragma once

#include <QTextEdit>
#include "../FluUtils/FluUtils.h"
#include <QTextDocument>
#include <QWidget>

class FluTextEditWrap;
class FluTextEdit : public QTextEdit
{
    Q_OBJECT
  public:
    FluTextEdit(QWidget* parent = nullptr);

    bool getAutoAdjustSize();

    void setAutoAdjustSize(bool bAdjustSize);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    FluTextEditWrap* m_wrap;
    bool m_bAutoAdjustSize;
};
