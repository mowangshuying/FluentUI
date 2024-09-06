#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include "FluStar.h"
#include "../FluUtils/FluUtils.h"
#include <QPainter>
#include <QStyleOption>
#include <QEvent>

class FluRatingControl : public FluWidget
{
    Q_OBJECT
  public:
    FluRatingControl(QWidget* parent = nullptr);

    void addStar();

    int getNum();

    bool eventFilter(QObject* watched, QEvent* event);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    int m_nNum;
    std::vector<FluStar*> m_stars;
    QHBoxLayout* m_hMainLayout;
};
