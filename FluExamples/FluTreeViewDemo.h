#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluTreeView.h"
#include <QTreeWidgetItem>
#include "FluTemplateDemo.h"

class FluTreeViewDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluTreeViewDemo(FluWidget* parent = nullptr);

    // void resizeEvent(QResizeEvent* event)
    //{
    //     m_treeView->setFixedSize(width(), height());
    // }

  protected:
    FluTreeView* m_treeView;
};
