#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>

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
        setFixedHeight(450);
        setMinimumWidth(650);

        m_titleLabel1 = new QLabel("CppFluentUi App SDK 1.0");
        m_titleLabel2 = new QLabel("WinUi3 Gallery");

      //  m_hLayout = new QHBoxLayout(this);
      //  m_hLayout->setSpacing(12);

        auto gettingStartCard = new FluVCard(this);
        gettingStartCard->move(40, 200);
       // m_hLayout->addWidget(gettingStartCard);
        
        auto windowsDesignCard = new FluVCard(QPixmap("../res/HomeHeaderTiles/Header-WindowsDesign.png"), "Windows design", "Design guidelines and toolkits for creating native app experiences.", this);
        windowsDesignCard->move(40 + 215, 200);
        // m_hLayout->addWidget(windowsDesignCard);

        auto winuiGithubCard = new FluVCard(QPixmap("../res/HomeHeaderTiles/github-mark.png"), "CppFluentUi Github", "The latest Windows native controls and styles for your applications", this);
       // m_hLayout->addWidget(winuiGithubCard);
        winuiGithubCard->move(40 + 2 * 215, 200);

        auto communityToolkitCard = new FluVCard(QPixmap("../res/HomeHeaderTiles/Header-Toolkit.png"), "Community ToolKit", "A Collection of helper functions. custom controls, and app services.", this);
      //  m_hLayout->addWidget(communityToolkitCard);
        communityToolkitCard->move(40 + 3 * 215, 200);


        auto codeSamplesCard = new FluVCard(QPixmap("../res/HomeHeaderTiles/"), "Code Samples", "Find samples that demonstrate specific tasks features and APIs", this);
       // m_hLayout->addWidget(codeSamplesCard);
        codeSamplesCard->move(40 + 4 * 215, 200);


        m_titleLabel1->setObjectName("titleLabel1");
        m_titleLabel2->setObjectName("titleLabel2");

        m_vMainLayout->addSpacing(60);
        m_vMainLayout->addWidget(m_titleLabel1);
        m_vMainLayout->addSpacing(10);
        m_vMainLayout->addWidget(m_titleLabel2);
     //   m_vMainLayout->addSpacing(70);
    //    m_vMainLayout->addLayout(m_hLayout);

        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluHomePageTitle.qss");
        setStyleSheet(qss);
    }

    void paintEvent(QPaintEvent* event)
    {
        QPainter painter(this);
        QLinearGradient gradient(0, 0, width(), height());
        gradient.setColorAt(0, QColor(206, 216, 228));
        gradient.setColorAt(1, QColor(249,249,249));
        painter.setPen(Qt::NoPen);
        painter.setBrush(gradient);
        painter.drawRect(rect());

        QPixmap pixmap("../res/GalleryHeaderImage.png");
        painter.drawPixmap(rect(), pixmap);
    }
  private:
    QVBoxLayout* m_vMainLayout;
    QHBoxLayout* m_hLayout;
    QLabel* m_titleLabel1;
    QLabel* m_titleLabel2;
};
