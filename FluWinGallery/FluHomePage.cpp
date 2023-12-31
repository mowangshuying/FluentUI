#include "FluHomePage.h"

FluHomePage::FluHomePage(QWidget *parent /*= nullptr*/) : FluVScrollView(parent)
{
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setAlignment(Qt::AlignTop);
    m_vMainLayout->setSpacing(45);
    //   setLayout(vMainLayout);

    auto titleWidget = new FluHomePageTitle();
    titleWidget->setMinimumHeight(450);

    auto recentlyAddedSamplesLabel = new QLabel;
    auto recentlyUpdatedSamplesLabel = new QLabel;
    recentlyAddedSamplesLabel->setText("Recently added samples");
    auto recentlyAddedSamplesLayout = new FluFlowLayout;
    auto recentlyAddedSamplesLayoutWrap = new QWidget(this);
    recentlyAddedSamplesLayoutWrap->setLayout(recentlyAddedSamplesLayout);
    recentlyAddedSamplesLayout->setContentsMargins(40, 0, 40, 0);
    recentlyAddedSamplesLayout->setSpacing(10, 10);

    auto AnnotatedScrollBarCard = new FluHCard();
    recentlyAddedSamplesLayout->addWidget(AnnotatedScrollBarCard);

    auto infoBadgeCard = new FluHCard(QPixmap("../res/ControlImages/InfoBadge.png"), "InfoBadge", "An non-instrusive Ui to display notifications or bring focus to an area");
    recentlyAddedSamplesLayout->addWidget(infoBadgeCard);

    auto itemsViewCard = new FluHCard(QPixmap("../res/ControlImages/ItemsView.png"), "ItemsView", "A control that presents a collection of items using various layouts");
    recentlyAddedSamplesLayout->addWidget(itemsViewCard);

    auto lineCard = new FluHCard(QPixmap("../res/ControlImages/Line.png"), "Line", "Draws a straight line between two points");
    recentlyAddedSamplesLayout->addWidget(lineCard);

    recentlyUpdatedSamplesLabel->setText("Recently updated samples");
    auto recentlyUpdatedSamplesWrap = new QWidget(this);
    auto recentlyUpdatedSamplesLayout = new FluFlowLayout(recentlyUpdatedSamplesWrap);
    recentlyUpdatedSamplesLayout->setContentsMargins(40, 0, 40, 0);
    recentlyUpdatedSamplesLayout->setSpacing(10, 10);

    auto AnimatedIconCard = new FluHCard(QPixmap("../res/ControlImages/AnimatedIcon.png"), "AnimatedIcon", "An element that displays and controls and icon that animates when the user interacts with the control.");
    recentlyUpdatedSamplesLayout->addWidget(AnimatedIconCard);

    auto autoSuggestBoxCard = new FluHCard(QPixmap("../res/ControlImages/AutoSuggestBox.png"), "AutoSuggestBox", "A control to provide suggestions as a user is typing.");
    recentlyUpdatedSamplesLayout->addWidget(autoSuggestBoxCard);

    auto breadcrumbBarCard = new FluHCard(QPixmap("../res/ControlImages/BreadcrumbBar.png"), "BreadcrumbBar", "Shows the trail of navigation token to the current location.");
    recentlyUpdatedSamplesLayout->addWidget(breadcrumbBarCard);

    auto buttonCard = new FluHCard(QPixmap("../res/ControlImages/Button.png"), "Button", "A control that responds to user input and raises a Click event.");
    recentlyUpdatedSamplesLayout->addWidget(buttonCard);

    m_vMainLayout->addWidget(titleWidget);
    m_vMainLayout->addWidget(recentlyAddedSamplesLabel);
    m_vMainLayout->addWidget(recentlyAddedSamplesLayoutWrap);
    m_vMainLayout->addWidget(recentlyUpdatedSamplesLabel);
    m_vMainLayout->addWidget(recentlyUpdatedSamplesWrap);

    titleWidget->setObjectName("titleWidget");
    titleWidget->setFixedHeight(350);
    recentlyAddedSamplesLabel->setObjectName("recentlyAddedSamplesLabel");
    recentlyUpdatedSamplesLabel->setObjectName("recentlyUpdatedSamplesLabel");

    QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluHomePage.qss");
    setStyleSheet(qss);
}
