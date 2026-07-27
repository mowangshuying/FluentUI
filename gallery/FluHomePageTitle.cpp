#include "FluHomePageTitle.h"

FluHomePageTitle::FluHomePageTitle(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_mainLayout->setContentsMargins(40, 0, 40, 0);
    m_mainLayout->setSpacing(0);

    setFixedHeight(350);
    m_titleLabel1 = new QLabel("FluentUi Gallery");
    m_titleLabel2 = new QLabel("Qt & Cpp");

    m_githubCard = new FluVCard(FluIconUtils::getPixmap(("../res/HomeHeaderTiles/github-mark.png")), tr("GitHub"), tr("The latest Windows native controls and styles for your applications"), this);
    m_githubCard->move(40, 120);

    m_titleLabel1->setObjectName("titleLabel1");
    m_titleLabel2->setObjectName("titleLabel2");

    m_mainLayout->addSpacing(40);
    m_mainLayout->addWidget(m_titleLabel1);
    m_mainLayout->addSpacing(10);
    m_mainLayout->addWidget(m_titleLabel2);

    m_color1 = QColor(206, 216, 228);
    m_color2 = QColor(223, 231, 240);
    // QString qss = FluStyleSheetUtils::getQssByFileName("../StyleSheet/light/FluHomePageTitle.qss");
    // setStyleSheet(qss);
    onThemeChanged();
}
