#include "FluSettingsSelectBox.h"

FluSettingsSelectBox::FluSettingsSelectBox(QWidget* parent /*= nullptr*/) : QWidget(parent)
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
    m_comboBox = new FluComboBox;
    m_comboBox->setFixedWidth(120);
    m_mainLayout->addWidget(m_comboBox);

    setFixedHeight(70);
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingsSelectBox.qss", this);
}

void FluSettingsSelectBox::setIcon(QIcon icon)
{
    m_iconLabel->setPixmap(icon.pixmap(40, 40));
}

void FluSettingsSelectBox::setTitleInfo(QString title, QString info)
{
    m_titleLabel->setText(title);
    m_infoLabel->setText(info);
}

void FluSettingsSelectBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
