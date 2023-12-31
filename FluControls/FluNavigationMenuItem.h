#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include "FluNavigationItem.h"

class FluNavigationMenuItem : public FluNavigationItem
{
     Q_OBJECT
   public:
     FluNavigationMenuItem(QWidget *parent = nullptr);
   signals:
     void menuClicked();

   protected:
     QPushButton *m_menuButton;
     QHBoxLayout *m_hLayout;
 };
