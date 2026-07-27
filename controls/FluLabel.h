#pragma once

#include <QLabel>

#include "../Utils/FluStyleSheetUtils.h"
#include "../Utils/FluUtils.h"

enum class FluLabelStyle
{
    CaptionTextBlockStyle,
    BodyTextBlockStyle,
    BodyStrongTextBlockStyle,
    SubTitleTextBlockStyle,
    TitleTextBlockStyle,
    TitleLargeTextBlockStyle,
    DisplayTextBlockStyle,
};

class FluLabel : public QLabel
{
    Q_OBJECT
  public:
    FluLabel(QWidget* parent = nullptr);

    FluLabel(FluLabelStyle style, QWidget* parent = nullptr);

    void setLabelStyle(FluLabelStyle style);
  protected:
    void onThemeChanged();
    FluLabelStyle m_style;
};
