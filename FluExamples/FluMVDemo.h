#pragma once

#include <QListView>
#include <QStringListModel>
#include "FluTemplateDemo.h"
#include <QWidget>
//#include "../FluControls/FluListView.h"

// just for test use model view;
class FluMVDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluMVDemo(QWidget* parent = nullptr);
    ~FluMVDemo();

  private:

    QListView* m_listView;
    QStringListModel* m_model;

    QWidget* m_toolWidget;
};
