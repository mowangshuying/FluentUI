#pragma once

#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexercpp.h>
#include "FluScrollDelegate.h"
#include "../utils/FluUtils.h"

class FluScintilla : public QsciScintilla
{
    Q_OBJECT
  public:
    FluScintilla(QWidget* parent = nullptr);
  public slots:
    void onThemeChanged();

  protected:
    FluScrollDelegate* m_delegate;
};
