#pragma once

#include <QWidget>

#include "../FluUtils/FluStyleSheetUitls.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "FluHomePageTitle.h"
#include "../FluControls/FluFlowLayout.h"
#include "../FluControls/FluHCard.h"
#include "../FluControls/FluVScrollView.h"

class FluHomePage : public FluVScrollView
{
    Q_OBJECT
  public:
    FluHomePage(QWidget *parent = nullptr);

  private:
};
