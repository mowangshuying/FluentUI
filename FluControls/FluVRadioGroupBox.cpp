#include "FluVRadioGroupBox.h"

FluVRadioGroupBox::FluVRadioGroupBox(QWidget* parent /*= nullptr*/) : QGroupBox(parent)
{
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);
    m_vMainLayout->addSpacing(15);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluVRadioGroupBox::FluVRadioGroupBox(QString title, QWidget* parent /*= nullptr*/) : QGroupBox(title, parent)
{
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);
    m_vMainLayout->addSpacing(15);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluVRadioGroupBox::addRadioButton(FluRadioButton* radioButton)
{
    m_vMainLayout->addWidget(radioButton);
}

void FluVRadioGroupBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluVRadioGroupBox.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluVRadioGroupBox.qss"), this);
    }
}
