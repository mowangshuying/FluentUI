#pragma once

#include "FluWidget.h"
// #include <QScrollArea>
#include <QVBoxLayout>
#include "../Utils/FluStyleSheetUtils.h"
#include "../Utils/FluUtils.h"
#include "FluScrollArea.h"

class FluVScrollView : public FluScrollArea
{
    Q_OBJECT
  public:
    FluVScrollView(QWidget* parent = nullptr);

    ~FluVScrollView();

    QVBoxLayout* getMainLayout();

  public slots:
    void onThemeChanged();

  protected:
    QWidget* m_contextWidget;
    QVBoxLayout* m_vMainLayout;
};
