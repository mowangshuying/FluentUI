#pragma once

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluMenu.h"
// #include "../FluControls/FluMenuIconTextItem.h"

#include "../FluControls/FluWidget.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QHBoxLayout>

#include <QLabel>
#include <QFrame>
#include <QWidgetAction>
#include <QContextMenuEvent>
#include <QPropertyAnimation>
// #include "../FluControls/FluMenuIconTextAction.h"
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
