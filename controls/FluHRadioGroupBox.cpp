#include "FluHRadioGroupBox.h"

FluHRadioGroupBox::FluHRadioGroupBox(QWidget* parent /*= nullptr*/) : QGroupBox(parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->addSpacing(15);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluHRadioGroupBox::FluHRadioGroupBox(QString title, QWidget* parent /*= nullptr*/) : QGroupBox(title, parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->addSpacing(15);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluHRadioGroupBox::addRadioButton(FluRadioButton* radioButton)
{
    m_mainLayout->addWidget(radioButton);
}

void FluHRadioGroupBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluHRadioGroupBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
