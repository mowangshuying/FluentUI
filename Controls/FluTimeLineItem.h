#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FluLabel.h"
#include "FluTimeLineIcon.h"
#include <QPainter>
#include "../Utils/FluUtils.h"

class FluTimeLineItem : public FluWidget
{
    Q_OBJECT
  public:
    FluTimeLineItem(QWidget* parent = nullptr);

    void addTextItem(QString text);

    FluLabel* getLabelAt(int index);

    void paintEvent(QPaintEvent* event);

  protected:
    FluTimeLineIcon* m_icon;
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_itemLayout;
    QVBoxLayout* m_iconLayout;
};
