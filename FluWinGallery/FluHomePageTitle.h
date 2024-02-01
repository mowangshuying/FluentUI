#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsOpacityEffect>
#include "../FluUtils/FluStyleSheetUitls.h"
#include "../FluControls/FluVCard.h"

class FluHomePageTitle : public QWidget
{
    Q_OBJECT
  public:
    FluHomePageTitle(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_vMainLayout = new QVBoxLayout(this);
        m_vMainLayout->setAlignment(Qt::AlignTop);
        m_vMainLayout->setContentsMargins(40, 0, 40, 0);
        m_vMainLayout->setSpacing(0);

        setFixedHeight(350);
        m_titleLabel1 = new QLabel("FluentUi Gallery");
        m_titleLabel2 = new QLabel("Qt & Cpp");

        m_githubCard = new FluVCard(QPixmap("../res/HomeHeaderTiles/github-mark.png"), "GitHub", "The latest Windows native controls and styles for your applications", this);
        m_githubCard->move(40, 120);

        m_titleLabel1->setObjectName("titleLabel1");
        m_titleLabel2->setObjectName("titleLabel2");

        m_vMainLayout->addSpacing(40);
        m_vMainLayout->addWidget(m_titleLabel1);
        m_vMainLayout->addSpacing(10);
        m_vMainLayout->addWidget(m_titleLabel2);

         m_color1 = QColor(206, 216, 228);
        m_color2 = QColor(223, 231, 240);
        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluHomePageTitle.qss");
        setStyleSheet(qss);
        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);

        // use path to limit rect
        QPainterPath path;
        path.addRoundedRect(rect(), 8, 8);
        painter.setClipPath(path);

        QLinearGradient gradient1(rect().topLeft(), QPoint(rect().topLeft().x(), rect().topLeft().y() + rect().height() / 2));
        gradient1.setColorAt(0.5, m_color1);
        gradient1.setColorAt(1, Qt::transparent);
        painter.setPen(Qt::NoPen);
        painter.setBrush(gradient1);
        painter.drawRect(rect());

        QPixmap pixmap("../res/GalleryHeaderImage.png");
        pixmap.copy(0, 0, pixmap.width(), pixmap.height() / 4);
        pixmap = pixmap.scaled(rect().width(), rect().height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        painter.drawPixmap(rect(), pixmap);

        QLinearGradient gradient(QPoint(rect().topLeft().x(), rect().topLeft().y() + rect().height() / 2), rect().bottomLeft());
        gradient.setColorAt(0.5, Qt::transparent);
        gradient.setColorAt(1, m_color2);
        painter.setPen(Qt::NoPen);
        painter.setBrush(gradient);
        painter.drawRect(rect());
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            m_githubCard->setIcon(QPixmap("../res/HomeHeaderTiles/github-mark.png"));
            m_color1 = QColor(206, 216, 228);
            m_color2 = QColor(223, 231, 240);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluHomePageTitle.qss", this);
            update();
        }
        else
        {
            m_githubCard->setIcon(QPixmap("../res/HomeHeaderTiles/github-mark-white.png"));
            m_color1 = QColor(0, 0, 0);
            m_color2 = QColor(39, 39, 39);
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluHomePageTitle.qss", this);
            update();
        }
    }
  protected:
    QVBoxLayout* m_vMainLayout;
    QHBoxLayout* m_hLayout;
    FluVCard* m_githubCard;
    QLabel* m_titleLabel1;
    QLabel* m_titleLabel2;

    QColor m_color1;
    QColor m_color2;
};
