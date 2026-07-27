#pragma once

#include "../controls/FluWidget.h"
#include "../controls/FluFrameLessWidget.h"
#include "../controls/FluStackedLayout.h"
#include "../controls/FluHNavigationView.h"
#include <QVBoxLayout>
#include "../controls/FluMenu.h"
#include "../controls/FluAction.h"

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
