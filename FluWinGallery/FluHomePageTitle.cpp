#include "FluHomePageTitle.h"

FluHomePageTitle::FluHomePageTitle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
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
}
