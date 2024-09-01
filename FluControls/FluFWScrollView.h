#pragma once

#include "FluWidget.h"
#include <QScrollArea>
#include "FluFlowLayout.h"
#include "../FluUtils/FluUtils.h"
#include "FluScrollArea.h"

class FluFWScrollView : public FluScrollArea
{
    Q_OBJECT
  public:
    FluFWScrollView(QWidget* parent = nullptr);

    FluFlowLayout* getMainLayout();
  public slots:
    void onThemeChanged();

  protected:
    QWidget* m_contextWidget;
    FluFlowLayout* m_vMainLayout;
};
