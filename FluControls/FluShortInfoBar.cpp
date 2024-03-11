#include "FluShortInfoBar.h"

FluShortInfoBar::FluShortInfoBar(FluShortInfoBarType infobarType, QWidget* parent /*= nullptr*/) : QWidget(parent)
{
    setFixedHeight(50);

    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);

    m_iconLabel = new QLabel;
    m_iconLabel->setFixedSize(18, 18);
    m_iconLabel->setObjectName("iconLabel");
    m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(FluAwesomeType::CheckMark, QColor(239,239,239),18, 18));
    m_hMainLayout->addWidget(m_iconLabel);

    m_infoLabel = new QLabel;
    m_infoLabel->setText("A Short Essential app Message.");
    m_infoLabel->setObjectName("infoLabel");
    m_hMainLayout->addWidget(m_infoLabel, 1);

    m_closeBtn = new QPushButton;
    m_closeBtn->setFixedSize(30, 30);
    m_closeBtn->setIconSize(QSize(15, 15));
    m_closeBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose));
    m_closeBtn->setObjectName("closeBtn");
    m_hMainLayout->addWidget(m_closeBtn);

    updateInfoBarTypeProperty(infobarType);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluShortInfoBar.qss", this);
}
