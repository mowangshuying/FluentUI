#pragma once

#include "../FluControls/FluWidget.h"
#include "../FluControls/FluTreeView.h"
#include <QTreeWidgetItem>

class FluTreeViewDemo : public FluWidget
{
    Q_OBJECT
  public:
    FluTreeViewDemo(FluWidget* parent = nullptr) : FluWidget(parent)
    {
        m_treeView = new FluTreeView(this);
        m_treeView->setHeaderHidden(true);

        auto workDocumentsItem = new QTreeWidgetItem({"Work Documents"});
        auto xyzFunctionnalSpecItem = new QTreeWidgetItem({"XYZ Functional Spec"});
        auto featureScheduleItem = new QTreeWidgetItem({"Feature Schedule"});
        auto overallProjectPlanItem = new QTreeWidgetItem({"Overal Project Plan"});
        auto featureResourcesAllocationItem = new QTreeWidgetItem({"Feature Resources Allocation"});

        auto personalDocumentsItem = new QTreeWidgetItem({"Personal Documents"});
        auto homeRemodelItem = new QTreeWidgetItem({"Contractor Contact Info"});
        auto paintColorSchemeItem = new QTreeWidgetItem({"Paint Color Scheme"});
        auto flooringWoodgrainTypeItem = new QTreeWidgetItem({"Flooring woodgrain type"});
        auto kitchenCabinetStyleItem = new QTreeWidgetItem({"Kitchen cabinet style"});

        workDocumentsItem->addChild(xyzFunctionnalSpecItem);
        workDocumentsItem->addChild(featureScheduleItem);
        workDocumentsItem->addChild(overallProjectPlanItem);
        workDocumentsItem->addChild(featureResourcesAllocationItem);

        personalDocumentsItem->addChild(homeRemodelItem);
        homeRemodelItem->addChild(paintColorSchemeItem);
        homeRemodelItem->addChild(flooringWoodgrainTypeItem);
        homeRemodelItem->addChild(kitchenCabinetStyleItem);

        m_treeView->addTopLevelItem(workDocumentsItem);
        m_treeView->addTopLevelItem(personalDocumentsItem);

        m_treeView->resize(350, 400);
        m_treeView->move(125, 100);

        resize(600, 600);
    }

    // void resizeEvent(QResizeEvent* event)
    //{
    //     m_treeView->setFixedSize(width(), height());
    // }

  protected:
    FluTreeView* m_treeView;
};
