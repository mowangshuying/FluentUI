#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluSettingsLabelBox : public QWidget
{
    Q_OBJECT
  public:
    FluSettingsLabelBox(QWidget* parent = nullptr)
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
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingsLabelBox.qss", this);
    }

    void setIcon(QIcon icon)
    {
        m_iconLabel->setPixmap(icon.pixmap(20, 20));
    }

    void setTitleInfo(QString title, QString info)
    {
        m_titleLabel->setText(title);
        m_infoLabel->setText(info);
    }

    void setVersion(QString version)
    {
        m_versionLabel->setText(version);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  protected:
    QHBoxLayout* m_mainLayout;
    QVBoxLayout* m_vLayout;
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_infoLabel;
    QLabel* m_versionLabel;
};
