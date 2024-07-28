#pragma once

#include <QLabel>

#include "../FluUtils/FluStyleSheetUitls.h"
#include "../FluUtils/FluUtils.h"

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
    FluLabel(QWidget* parent = nullptr) : QLabel(parent)
    {
        m_style = FluLabelStyle::CaptionTextBlockSylte;
        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluLabel(FluLabelStyle style, QWidget* parent = nullptr) : QLabel(parent), m_style(style)
    {
        onThemeChanged();
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
    }

    void setLabelStyle(FluLabelStyle style)
    {
        m_style = style;
        QString styleString;
        switch (style)
        {
            case FluLabelStyle::CaptionTextBlockSylte:
                styleString = "CaptionTextBlockSylte";
                break;
            case FluLabelStyle::BodyTextBlockStyle:
                styleString = "BodyTextBlockStyle";
                break;
            case FluLabelStyle::BodyStrongTextBlockStyle:
                styleString = "BodyStrongTextBlockStyle";

                break;
            case FluLabelStyle::SubTitleTextBlockStyle:
                styleString = "SubTitleTextBlockStyle";

                break;
            case FluLabelStyle::TitleTextBlockStyle:
                styleString = "TitleTextBlockStyle";

                break;
            case FluLabelStyle::TitleLargeTextBlockStyle:
                styleString = "TitleLargeTextBlockStyle";

                break;
            case FluLabelStyle::DisplayTextBlockStyle:
                styleString = "DisplayTextBlockStyle";
                break;
            default:
                break;
        }
        setProperty("labelStyle", styleString);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLabel.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluLabel.qss", this);
        }
    }

  protected:
    FluLabelStyle m_style;
};
