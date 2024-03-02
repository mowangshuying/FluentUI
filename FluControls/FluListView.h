#pragma once

#include "FluVScrollView.h"
#include "../FluUtils/FluUtils.h"
#include <QVBoxLayout>
#include <QListWidget>
#include "FluListViewItemDelegate.h"

class FluListView : public QListWidget
{
    Q_OBJECT
  public:
    FluListView(QWidget* parent = nullptr) : QListWidget(parent)
    {
        setItemDelegate(new FluListViewItemDelegate);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluListView.qss", this);
    }
};
