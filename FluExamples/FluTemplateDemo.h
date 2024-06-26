#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluFrameLessWidget.h"
#include "../FluControls/FluStackedLayout.h"
#include "../FluControls/FluHNavigationView.h"
#include <QVBoxLayout>
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluAction.h"

class FluTemplateDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluTemplateDemo(QWidget* parent = nullptr);

    void contextMenuEvent(QContextMenuEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    FluMenu* m_contextMenu;
};
