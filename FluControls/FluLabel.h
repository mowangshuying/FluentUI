#pragma once

#include <QLabel>

#include "../FluUtils/FluStyleSheetUitls.h"

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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLabel.qss", this);
    }

    FluLabel(FluLabelStyle style, QWidget* parent = nullptr) : QLabel(parent), m_style(style)
    {
        // style£º
        // reference WinUi3 Gallary Typeography page.
       // setProperty("style", m_style);
        setStyle(style);
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLabel.qss", this);
    }

    void setStyle(FluLabelStyle style)
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

    protected:
    FluLabelStyle m_style;
};
