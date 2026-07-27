#pragma once

#include "../controls/FluVNavigationView.h"
#include "../controls/FluVNavigationIconTextItem.h"
#include <QFrame>
#include "../controls/FluWidget.h"

class FluVNavigationViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluVNavigationViewDemo(QWidget *parent = nullptr);

    void addDesignGuidaceIconText();

    void addDesignGuidaceText();
};
