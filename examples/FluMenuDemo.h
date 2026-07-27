#pragma once

#include "../utils/FluUtils.h"
#include "../controls/FluMenu.h"
// #include "../controls/FluMenuIconTextItem.h"

#include "../controls/FluWidget.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QHBoxLayout>

#include <QLabel>
#include <QFrame>
#include <QWidgetAction>
#include <QContextMenuEvent>
#include <QPropertyAnimation>
// #include "../controls/FluMenuIconTextAction.h"
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
