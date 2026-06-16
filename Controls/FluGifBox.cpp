#include "FluGifBox.h"

FluGifBox::FluGifBox(QString lightGifPath, QString darkGifPath, QWidget* parent) : QLabel(parent)
{
    m_lightMovie = new QMovie(lightGifPath);
    m_darkMovie = new QMovie(darkGifPath);
    onThemeChanged();

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluGifBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        setMovie(m_lightMovie);
        m_lightMovie->start();
        m_darkMovie->stop();
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        setMovie(m_darkMovie);
        m_lightMovie->stop();
        m_darkMovie->start();
    }
}
