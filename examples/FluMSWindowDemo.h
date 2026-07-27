#pragma once

#include "../controls/FluMSWindow.h"
#include "../utils/FluUtils.h"
#include "../controls/FluMSNavigationItem.h"
#include "../controls/FluMenu.h"
#include "../controls/FluAction.h"
#include "../controls/FluLabel.h"

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
