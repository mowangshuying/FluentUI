#include "FluVCard.h"

FluVCard::FluVCard(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    auto vMainLaout = new QVBoxLayout(this);
    vMainLaout->setAlignment(Qt::AlignTop);
    vMainLaout->setContentsMargins(20, 30, 20, 30);

    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(60, 60);
    QPixmap galleryPng = FluIconUtils::getPixmap(("../res/HomeHeaderTiles/Header-WinUIGallery.png"));
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
    // QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluVCard.qss");
    // setStyleSheet(qss);
    onThemeChanged();
}

FluVCard::FluVCard(QPixmap icon, QString titleText, QString contextText, QWidget* parent /*= nullptr*/) : FluVCard(parent)
{
    QPixmap pixmap = icon.scaled(60, 60);
    m_iconLabel->setPixmap(pixmap);
    m_titleLabel->setText(titleText);
    m_contextLabel->setText(contextText);
    onThemeChanged();
}

void FluVCard::setIcon(QPixmap icon)
{
    QPixmap pixmap = icon.scaled(60, 60);
    m_iconLabel->setPixmap(pixmap);
}

void FluVCard::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluVCard::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluVCard.qss", this, FluThemeUtils::getUtils()->getTheme());
}
