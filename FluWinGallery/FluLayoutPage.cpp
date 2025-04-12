#include "FluLayoutPage.h"

FluLayoutPage::FluLayoutPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Layout"));

    auto borderCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Border.png")), tr("Border"), tr("A container control that draws a boundary line, background, or both, around another object."));
    borderCard->setKey("BorderPage");
    getFWScrollView()->getMainLayout()->addWidget(borderCard);
    connect(borderCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto canvasCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Canvas.png")), tr("Canvas"), tr("A layout panel that supports absolute positioning of child elements relative to the top left corner of the canvas."));
    canvasCard->setKey("CanvasPage");
    getFWScrollView()->getMainLayout()->addWidget(canvasCard);
    connect(canvasCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto expanderCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Expander.png")), tr("Expander"), tr("A container with a header that can be expanded to show a body with more content."));
    expanderCard->setKey("ExpanderPage");
    getFWScrollView()->getMainLayout()->addWidget(expanderCard);
    connect(expanderCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto gridCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Grid.png")), tr("Grid"), tr("A flexible, primitive control for data-driven layouts."));
    gridCard->setKey("GridPage");
    getFWScrollView()->getMainLayout()->addWidget(gridCard);
    connect(gridCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto itemsRepeaterCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ItemsRepeater.png")), tr("ItemsRepeater"), tr("A flexible, primitive control for data-driven layouts."));
    itemsRepeaterCard->setKey("ItemRepeaterPage");
    getFWScrollView()->getMainLayout()->addWidget(itemsRepeaterCard);
    connect(itemsRepeaterCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto radioButtonsCard = new FluHCard(QPixmap(FLURC("res/ControlImages/RadioButtons.png")), tr("RadioButtons"), tr("A control that displays a group of mutually exclusive options with keyboarding and accessibility support."));
    radioButtonsCard->setKey("RadioButtonsPage");
    getFWScrollView()->getMainLayout()->addWidget(radioButtonsCard);
    connect(radioButtonsCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto relativePanelCard = new FluHCard(QPixmap(FLURC("res/ControlImages/RelativePanel.png")), tr("RelativePanel"), tr("A panel that users relationships between elements to define layout."));
    relativePanelCard->setKey("RelativePanelPage");
    getFWScrollView()->getMainLayout()->addWidget(relativePanelCard);
    connect(relativePanelCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto splitViewCard = new FluHCard(QPixmap(FLURC("res/ControlImages/SplitView.png")), tr("SplitView"), tr("A container that has 2 content areas, with multiple display options for the pane."));
    splitViewCard->setKey("SplitViewPage");
    getFWScrollView()->getMainLayout()->addWidget(splitViewCard);
    connect(splitViewCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto stackPanelCard = new FluHCard(QPixmap(FLURC("res/ControlImages/StackPanel.png")), tr("StackPanel"), tr("A layout panel that arranges child elements into a single line that can be oriented horizontally or vertically."));
    stackPanelCard->setKey("StackPanelPage");
    getFWScrollView()->getMainLayout()->addWidget(stackPanelCard);
    connect(stackPanelCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto variableSizedWrapGridCard =
        new FluHCard(QPixmap(FLURC("res/ControlImages/VariableSizedWrapGrid.png")), tr("VariableSizedWrapGrid"), tr("A layout panel that supports arranging child elements in rows and columns. Each child element can span multiple rows and columns."));
    variableSizedWrapGridCard->setKey("VariableSizedWrapGridPage");
    getFWScrollView()->getMainLayout()->addWidget(variableSizedWrapGridCard);
    connect(variableSizedWrapGridCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto viewboxCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Viewbox.png")), tr("Viewbox"), tr("A container control that scales its content to a specified size."));
    viewboxCard->setKey("ViewboxPage");
    getFWScrollView()->getMainLayout()->addWidget(viewboxCard);
    connect(viewboxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    onThemeChanged();
}

void FluLayoutPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluLayoutPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluLayoutPage.qss"), this);
    }
}
