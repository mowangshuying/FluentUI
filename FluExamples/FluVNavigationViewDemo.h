#pragma once

#include "../FluControls/FluVNavigationView.h"
#include "../FluControls/FluVNavigationIconTextItem.h"
#include <QFrame>
#include "../FluControls/FluWidget.h"

class FluVNavigationViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationViewDemo(QWidget *parent = nullptr);

    void addDesignGuidaceIconText();

    void addDesignGuidaceText();
};
