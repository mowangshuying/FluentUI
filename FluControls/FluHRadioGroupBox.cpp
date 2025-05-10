#include "FluHRadioGroupBox.h"

FluHRadioGroupBox::FluHRadioGroupBox(QWidget* parent /*= nullptr*/) : QGroupBox(parent)
{
    m_hMainLayout = new QVBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->addSpacing(15);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluHRadioGroupBox::FluHRadioGroupBox(QString title, QWidget* parent /*= nullptr*/) : QGroupBox(title, parent)
{
    m_hMainLayout = new QVBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->addSpacing(15);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluHRadioGroupBox::addRadioButton(FluRadioButton* radioButton)
{
    m_hMainLayout->addWidget(radioButton);
}

void FluHRadioGroupBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluHRadioGroupBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
