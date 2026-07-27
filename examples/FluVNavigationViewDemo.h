#pragma once

#include "../Controls/FluVNavigationView.h"
#include "../Controls/FluVNavigationIconTextItem.h"
#include <QFrame>
#include "../Controls/FluWidget.h"

class FluVNavigationViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationViewDemo(QWidget *parent = nullptr);

    void addDesignGuidaceIconText();

    void addDesignGuidaceText();
};
