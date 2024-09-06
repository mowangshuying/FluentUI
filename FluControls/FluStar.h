#pragma once

#include <QLabel>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"

class FluStar : public QLabel
{
    Q_OBJECT
  public:
    FluStar(QWidget* parent = nullptr);

    void setEmptyStar();

    void setSolidStar();

  public slots:
    void onThemeChanged();

  protected:
    bool m_bSolid;
};
