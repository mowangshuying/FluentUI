#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FluLabel.h"
#include "FluTimeLineIcon.h"
#include <QPainter>
#include "../FluUtils/FluUtils.h"

class FluTimeLineItem : public FluWidget
{
    Q_OBJECT
  public:
    FluTimeLineItem(QWidget* parent = nullptr);

    void addTextItem(QString text);

    FluLabel* getLabelAt(int nIndex);

    void paintEvent(QPaintEvent* event);

  protected:
    FluTimeLineIcon* m_icon;
    QHBoxLayout* m_hMainLayout;
    QVBoxLayout* m_vItemLayout;
    QVBoxLayout* m_vIconLayout;
};
