#pragma once

#include <QLabel>

#include "../Utils/FluStyleSheetUitls.h"
#include "../Utils/FluUtils.h"

enum class FluLabelStyle
{
    CaptionTextBlockSylte,
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
  public slots:
    void onThemeChanged();

  protected:
    FluLabelStyle m_style;
};
