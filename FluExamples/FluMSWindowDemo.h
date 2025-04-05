#pragma once

#include "../FluControls/FluMSWindow.h"
#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluMSNavigationItem.h"
#include "../FluControls/FluMenu.h"
#include "../FluControls/FluAction.h"
#include "../FluControls/FluLabel.h"

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
