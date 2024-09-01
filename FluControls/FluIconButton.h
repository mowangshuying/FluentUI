#pragma once

#include <QPushButton>
#include "FluDef.h"
#include "../FluUtils/FluUtils.h"
#include <QTimer>
#include <QStyle>

// to display fluent icon use fluent font
class FluIconButton : public QPushButton
{
    Q_OBJECT
  public:
    FluIconButton(QWidget* parent = nullptr);

    FluIconButton(FluAwesomeType type1, QWidget* parent = nullptr);

    FluIconButton(FluAwesomeType type1, FluAwesomeType type2, QWidget* parent = nullptr);

    void setType(FluAwesomeType type);

    void setType1(FluAwesomeType type);

    void setType2(FluAwesomeType type);

    void setNoBorder(bool bNoBorder);

  public slots:
    void onThemeChanged();

  protected:
    FluAwesomeType m_type;
    FluAwesomeType m_type1;
    FluAwesomeType m_type2;
    QColor m_penColor;

    QTimer* m_timer;
    bool m_bClicked;
};
