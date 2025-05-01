#include "FluLabel.h"

FluLabel::FluLabel(QWidget* parent /*= nullptr*/) : QLabel(parent)
{
    m_style = FluLabelStyle::CaptionTextBlockSylte;
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluLabel::FluLabel(FluLabelStyle style, QWidget* parent /*= nullptr*/) : QLabel(parent), m_style(style)
{
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluLabel::setLabelStyle(FluLabelStyle style)
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

void FluLabel::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluLabel.qss", this, FluThemeUtils::getUtils()->getTheme());
}
