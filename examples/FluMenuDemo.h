#pragma once

#include "../Utils/FluUtils.h"
#include "../Controls/FluMenu.h"
// #include "../Controls/FluMenuIconTextItem.h"

#include "../Controls/FluWidget.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QHBoxLayout>

#include <QLabel>
#include <QFrame>
#include <QWidgetAction>
#include <QContextMenuEvent>
#include <QPropertyAnimation>
// #include "../Controls/FluMenuIconTextAction.h"
#include <QWidgetAction>

class FluMenuDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluMenuDemo(QWidget* parent = nullptr);

    void contextMenuEvent(QContextMenuEvent* event);

  protected:
    FluMenu* m_menu;
    QPropertyAnimation* m_animation;
};
