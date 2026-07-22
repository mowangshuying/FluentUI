#include "FluVRadioGroupBox.h"

FluVRadioGroupBox::FluVRadioGroupBox(QWidget* parent /*= nullptr*/) : QGroupBox(parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->addSpacing(15);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

FluVRadioGroupBox::FluVRadioGroupBox(QString title, QWidget* parent /*= nullptr*/) : QGroupBox(title, parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->addSpacing(15);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluVRadioGroupBox::addRadioButton(FluRadioButton* radioButton)
{
    m_mainLayout->addWidget(radioButton);
}

void FluVRadioGroupBox::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluVRadioGroupBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
