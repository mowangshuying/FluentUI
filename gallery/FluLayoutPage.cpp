#include "FluLayoutPage.h"

FluLayoutPage::FluLayoutPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Layout"));

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Border.png")), tr("Border"), tr("A container control that draws a boundary line, background, or both, around another object."), "BorderPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Canvas.png")), tr("Canvas"), tr("A layout panel that supports absolute positioning of child elements relative to the top left corner of the canvas."), "CanvasPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Expander.png")), tr("Expander"), tr("A container with a header that can be expanded to show a body with more content."), "ExpanderPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Grid.png")), tr("Grid"), tr("A flexible, primitive control for data-driven layouts."), "GridPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ItemsRepeater.png")), tr("ItemsRepeater"), tr("A flexible, primitive control for data-driven layouts."), "ItemRepeaterPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RadioButtons.png")), tr("RadioButtons"), tr("A control that displays a group of mutually exclusive options with keyboarding and accessibility support."), "RadioButtonsPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RelativePanel.png")), tr("RelativePanel"), tr("A panel that users relationships between elements to define layout."), "RelativePanelPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SplitView.png")), tr("SplitView"), tr("A container that has 2 content areas, with multiple display options for the pane."), "SplitViewPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/StackPanel.png")), tr("StackPanel"), tr("A layout panel that arranges child elements into a single line that can be oriented horizontally or vertically."), "StackPanelPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/VariableSizedWrapGrid.png")), tr("VariableSizedWrapGrid"), tr("A layout panel that supports arranging child elements in rows and columns. Each child element can span multiple rows and columns."), "VariableSizedWrapGridPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Viewbox.png")), tr("Viewbox"), tr("A container control that scales its content to a specified size."), "ViewboxPage");

    onThemeChanged();
}

void FluLayoutPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluLayoutPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
