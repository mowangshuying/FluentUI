#pragma once

#include <QScrollArea>
#include <QWidget>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QWheelEvent>

class FluHScrollView : public QScrollArea
{
    Q_OBJECT
  public:
    FluHScrollView(QWidget* parent = nullptr);

    ~FluHScrollView();

    QHBoxLayout* getMainLayout();

    void wheelEvent(QWheelEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    QWidget* m_contextWidget;
    QHBoxLayout* m_hMainLayout;
};
