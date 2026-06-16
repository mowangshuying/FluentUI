#pragma once

#include "../Controls/FluWidget.h"
#include "../Controls/FluFrameLessWidget.h"
#include "../Controls/FluStackedLayout.h"
#include "../Controls/FluHNavigationView.h"
#include <QVBoxLayout>
#include "../Controls/FluMenu.h"
#include "../Controls/FluAction.h"

class FluTemplateDemo : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    FluTemplateDemo(QWidget* parent = nullptr);

    // void contextMenuEvent(QContextMenuEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    // FluMenu* m_contextMenu;
};
