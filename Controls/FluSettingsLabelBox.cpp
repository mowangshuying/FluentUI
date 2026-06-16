#include "FluSettingsLabelBox.h"

FluSettingsLabelBox::FluSettingsLabelBox(QWidget* parent /*= nullptr*/)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);

    m_iconLabel = new QLabel;
    m_iconLabel->setFixedSize(40, 40);
    m_mainLayout->addWidget(m_iconLabel, 0);

    m_vLayout = new QVBoxLayout;
    m_titleLabel = new QLabel;
    m_infoLabel = new QLabel;

    m_titleLabel->setObjectName("titleLabel");
    m_infoLabel->setObjectName("infoLabel");

    m_vLayout->addWidget(m_titleLabel);
    m_vLayout->addWidget(m_infoLabel);

    m_mainLayout->addLayout(m_vLayout, 1);

    m_versionLabel = new QLabel;
    m_versionLabel->setObjectName("versionLabel");
    m_versionLabel->setFixedWidth(120);

    m_mainLayout->addWidget(m_versionLabel);

    setFixedHeight(70);
    onThemeChanged();
}

void FluSettingsLabelBox::setIcon(QIcon icon)
{
    m_iconLabel->setPixmap(icon.pixmap(20, 20));
}

void FluSettingsLabelBox::setTitleInfo(QString title, QString info)
{
    m_titleLabel->setText(title);
    m_infoLabel->setText(info);
}

void FluSettingsLabelBox::setVersion(QString version)
{
    m_versionLabel->setText(version);
}

void FluSettingsLabelBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluSettingsLabelBox::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluSettingsLabelBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
