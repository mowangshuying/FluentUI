#pragma once

#include "../controls/FluVFlyout.h"
#include <QGridLayout>
#include <QStyleOption>
#include <QPainter>
#include "FluColorButton.h"
#include "FluWidget.h"

// has 9 color buttons.
class FluColorFlyout : public FluWidget
{
    Q_OBJECT
  public:
    FluColorFlyout(QWidget* targetWidget);

    ~FluColorFlyout();

    void addColorButton(FluColorButton* colorBtn, int row, int col);

    void addColorButton(FluColorButton* colorBtn);

    // Adds an arbitrary widget (e.g. a "custom color" entry) on its own full-width row.
    void addCustomButton(QWidget* widget);

    void showEvent(QShowEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void colorChanged(QColor color);
  public slots:
    void onThemeChanged();

  protected:
    QGridLayout* m_gridLayout;
    QWidget* m_targetWidget;
};
