#pragma once

#include <QWidget>
#include "../FluUtils/FluStyleSheetUitls.h"
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include "../FluUtils/FluUtils.h"

class FluVCard : public QWidget
{
    Q_OBJECT
  public:
    FluVCard(QWidget* parent = nullptr) : QWidget(parent)
    {
        auto vMainLaout = new QVBoxLayout(this);
        vMainLaout->setAlignment(Qt::AlignTop);
        vMainLaout->setContentsMargins(20, 30, 20, 30);

        m_iconLabel = new QLabel(this);
        m_iconLabel->setFixedSize(60, 60);
        QPixmap galleryPng = QPixmap("../res/HomeHeaderTiles/Header-WinUIGallery.png");
        galleryPng = galleryPng.scaled(60, 60);
        m_iconLabel->setPixmap(galleryPng);

        vMainLaout->addWidget(m_iconLabel);

        m_titleLabel = new QLabel(this);
        m_titleLabel->setText("Getting started");
        m_titleLabel->setObjectName("titleLabel");

        vMainLaout->addSpacing(20);
        vMainLaout->addWidget(m_titleLabel);

        m_contextLabel = new QLabel(this);
        m_contextLabel->setText("An overview of app development options, tools, and samples.");
        m_contextLabel->setObjectName("contextLabel");
        m_contextLabel->setWordWrap(true);
        vMainLaout->addWidget(m_contextLabel);

        setFixedSize(200, 220);
        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluVCard.qss");
        setStyleSheet(qss);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    FluVCard(QPixmap icon, QString titleText, QString contextText, QWidget* parent = nullptr) : FluVCard(parent)
    {
        QPixmap pixmap = icon.scaled(60, 60);
        m_iconLabel->setPixmap(pixmap);
        m_titleLabel->setText(titleText);
        m_contextLabel->setText(contextText);
    }

    void setIcon(QPixmap icon)
    {
        QPixmap pixmap = icon.scaled(60, 60);
        m_iconLabel->setPixmap(pixmap);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluVCard.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluVCard.qss", this);
        }
    }
  protected:
    QLabel* m_iconLabel;
    QLabel* m_titleLabel;
    QLabel* m_contextLabel;
};
