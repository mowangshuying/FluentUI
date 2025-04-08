#include "FluTabDemo.h"

FluTabPage::FluTabPage(QString text, QWidget *parent)
{
    auto hLayout = new QHBoxLayout;
    setLayout(hLayout);
    hLayout->setAlignment(Qt::AlignCenter);

    auto label = new FluLabel;
    label->setText(text);
    label->setLabelStyle(FluLabelStyle::SubTitleTextBlockStyle);
    hLayout->addWidget(label);

    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { onThemeChanged(); });

    onThemeChanged();
}

void FluTabPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluTabPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluTabPage.qss", this);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluTabPage.qss", this);
    }
}

FluTabDemo::FluTabDemo(QWidget *parent /*= nullptr*/) : FluTabWidget(parent)
{
    resize(800, 600);
    // set attr
    setVisible(true);
    setTabsClosable(true);

    // add Tab;
    addTab(new FluTabPage("Tab 1"), "tab1");
    addTab(new FluTabPage("Tab 2"), "tab2");
    addTab(new FluTabPage("Tab 3"), "tab3");
}