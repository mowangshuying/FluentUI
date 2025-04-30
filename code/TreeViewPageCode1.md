```cpp
    // tree view demo;
    auto treeView = new FluTreeView;
    treeView->setHeaderHidden(true);
    treeView->setColumnCount(1);

    auto workDocumentsItem = new QTreeWidgetItem({tr("Work Documents")});
    workDocumentsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    workDocumentsItem->setCheckState(0, Qt::Unchecked);

    auto xyzFunctionnalSpecItem = new QTreeWidgetItem({tr("XYZ Functional Spec")});
    xyzFunctionnalSpecItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    xyzFunctionnalSpecItem->setCheckState(0, Qt::Unchecked);

    auto featureScheduleItem = new QTreeWidgetItem({tr("Feature Schedule")});
    featureScheduleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    featureScheduleItem->setCheckState(0, Qt::Unchecked);

    auto overallProjectPlanItem = new QTreeWidgetItem({tr("Overal Project Plan")});
    overallProjectPlanItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    overallProjectPlanItem->setCheckState(0, Qt::Unchecked);

    auto featureResourcesAllocationItem = new QTreeWidgetItem({tr("Feature Resources Allocation")});
    featureResourcesAllocationItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    featureResourcesAllocationItem->setCheckState(0, Qt::Unchecked);

    auto personalDocumentsItem = new QTreeWidgetItem({tr("Personal Documents")});
    personalDocumentsItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    personalDocumentsItem->setCheckState(0, Qt::Unchecked);

    auto homeRemodelItem = new QTreeWidgetItem({tr("Contractor Contact Info")});
    homeRemodelItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    homeRemodelItem->setCheckState(0, Qt::Unchecked);

    auto paintColorSchemeItem = new QTreeWidgetItem({tr("Paint Color Scheme")});
    paintColorSchemeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    paintColorSchemeItem->setCheckState(0, Qt::Unchecked);

    auto flooringWoodgrainTypeItem = new QTreeWidgetItem({tr("Flooring woodgrain type")});
    flooringWoodgrainTypeItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    flooringWoodgrainTypeItem->setCheckState(0, Qt::Unchecked);

    auto kitchenCabinetStyleItem = new QTreeWidgetItem({tr("Kitchen cabinet style")});
    kitchenCabinetStyleItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    kitchenCabinetStyleItem->setCheckState(0, Qt::Unchecked);

    workDocumentsItem->addChild(xyzFunctionnalSpecItem);
    workDocumentsItem->addChild(featureScheduleItem);
    workDocumentsItem->addChild(overallProjectPlanItem);
    workDocumentsItem->addChild(featureResourcesAllocationItem);

    personalDocumentsItem->addChild(homeRemodelItem);
    homeRemodelItem->addChild(paintColorSchemeItem);
    homeRemodelItem->addChild(flooringWoodgrainTypeItem);
    homeRemodelItem->addChild(kitchenCabinetStyleItem);

    treeView->addTopLevelItem(workDocumentsItem);
    treeView->addTopLevelItem(personalDocumentsItem);
    treeView->setFixedWidth(400);
```

