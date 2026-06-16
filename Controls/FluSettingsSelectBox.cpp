#include "FluSettingsSelectBox.h"

FluSettingsSelectBox::FluSettingsSelectBox(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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
    m_comboBoxEx = new FluComboBoxEx;
    m_comboBoxEx->setFixedWidth(120);
    m_mainLayout->addWidget(m_comboBoxEx);

    setFixedHeight(70);

    m_iconAwesomeType = FluAwesomeType::None;
    onThemeChanged();
}

FluSettingsSelectBox::FluSettingsSelectBox(FluAwesomeType awesomeType, QWidget* parent /*= nullptr*/) : FluSettingsSelectBox(parent)
{
    m_iconAwesomeType = awesomeType;
    setIcon(FluIconUtils::getFluentIcon(m_iconAwesomeType, FluThemeUtils::getUtils()->getTheme()));
}

FluComboBoxEx* FluSettingsSelectBox::getComboBox()
{
    return m_comboBoxEx;
}

void FluSettingsSelectBox::setIcon(QIcon icon)
{
    m_iconLabel->setPixmap(icon.pixmap(40, 40));
}

void FluSettingsSelectBox::setIcon(FluAwesomeType awesomeType)
{
    m_iconAwesomeType = awesomeType;
    setIcon(FluIconUtils::getFluentIcon(m_iconAwesomeType, FluThemeUtils::getUtils()->getTheme()));
}

void FluSettingsSelectBox::setTitleInfo(QString title, QString info)
{
    m_titleLabel->setText(title);
    m_infoLabel->setText(info);
}

void FluSettingsSelectBox::hideInfoLabel()
{
    m_infoLabel->hide();
}

void FluSettingsSelectBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluSettingsSelectBox::onThemeChanged()
{
    setIcon(FluIconUtils::getFluentIcon(m_iconAwesomeType, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluSettingsSelectBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
