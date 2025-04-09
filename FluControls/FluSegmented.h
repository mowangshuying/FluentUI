#pragma once

#include "FluWidget.h"
#include "../FluUtils/FluUtils.h"
#include <QHBoxLayout>
#include "FluSegmentedItem.h"
#include <QStyleOption>
#include <QPainter>
#include "FluValueObject.h"
#include <QPropertyAnimation>

class FluSegmented : public FluWidget
{
    Q_OBJECT
  public:
    FluSegmented(QWidget* parent = nullptr);

    void setCurrentItem(FluSegmentedItem* item);

    void setCurrentItem(QString text);

    FluSegmentedItem getCurrentItem();

    void addWidget(FluSegmentedItem* item);

    void insertWidget(int nIndex, FluSegmentedItem* item);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onItemClicked(FluSegmentedItem* item);

    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    FluSegmentedItem* m_currentItem;

    // ani;
    FluValueObject* m_valueObject;
    QPropertyAnimation* m_animation;
};
