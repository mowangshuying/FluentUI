#pragma once

#include "../Controls/FluMSWindow.h"
#include "../Utils/FluUtils.h"
#include "../Controls/FluMSNavigationItem.h"
#include "../Controls/FluMenu.h"
#include "../Controls/FluAction.h"
#include "../Controls/FluLabel.h"

class FluMSPage : public FluWidget
{
    Q_OBJECT
  public:
    FluMSPage(QString text, QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();
};

class FluMSWindowDemo : public FluMSWindow
{
    Q_OBJECT
  public:
    FluMSWindowDemo(QWidget* parent = nullptr);

    void contextMenuEvent(QContextMenuEvent* event);

  protected:
    FluMenu* m_contextMenu;
};
