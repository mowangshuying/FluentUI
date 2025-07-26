#pragma once

#include "FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>

#include "../FluUtils/FluUtils.h"
#include "FluDef.h"
#include <QStyleOption>
#include <QPainter>

// box to display icon
class FluDisplayIconBox : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayIconBox(QWidget* parent = nullptr);

    FluDisplayIconBox(FluAwesomeType type, QWidget* parent = nullptr);

    FluDisplayIconBox(FluEmoijType type, QWidget* parent = nullptr);

    void setSelected(bool bSelected);

    FluAwesomeType getAwesomeType();
    FluEmoijType getEmoijType();

    void setUseAwesomeType(bool bUseAwesomeType)
    {
        m_bUseAwesomeType = bUseAwesomeType;
    }

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    // true: display awesometype;
    bool m_bUseAwesomeType;

    FluAwesomeType m_awesomeType;
    FluEmoijType m_emoijType;
    QLabel* m_iconLabel;
    QLabel* m_textLable;
    QVBoxLayout* m_vMainLayout;
};
