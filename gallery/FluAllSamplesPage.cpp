#include "FluAllSamplesPage.h"

FluAllSamplesPage::FluAllSamplesPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);

    m_titleLabel->setText(tr("All Samples"));

    makeBasicInputCards();
    makeCollectionsCards();
    makeDateAndTimeCards();
    makeDialogsAndFlyouts();

    makeLayoutCards();
    makeMediaCards();
    makeNavigationCards();
    makeScrollingCards();
    makeStatusInfoCards();
    makeTextCards();

    // FluStyleSheetUtils::setQssByFileName("../stylesheet/light/FluAllSamplesPage.qss", this);
    onThemeChanged();
}

void FluAllSamplesPage::makeBasicInputCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Button.png")), tr("Button"), tr("A control that responds to user input and raises a Click event."), "ButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Checkbox.png")), tr("CheckBox"), tr("A control that a user can select or clear."), "CheckBoxPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ColorPicker.png")), tr("ColorPicker"), tr("A control that displays a selectable color spectrum."), "ColorPickerPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ComboBox.png")), tr("ComboBox"), tr("A drop-down list of items a user can select from."), "ComboBoxPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/DropDownButton.png")), tr("DropDownButton"), tr("A button that displays a flyout of choices when clicked."), "DropDownButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/HyperlinkButton.png")), tr("HyperlinkButton"), tr("A button that appears as hyperlink text and can navigate to URI or handle a Click event."), "HyperlinkButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RadioButton.png")), tr("RadioButton"), tr("A control that allows a user to select a single option from a group of options."), "RadioButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RatingControl.png")), tr("RatingControl"), tr("Rate something 1 to 5 stars."), "RatingControlPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RepeatButton.png")), tr("RepeatButton"), tr("A button that raisers its Click event repeatedly from the time it's pressed until it's released."), "RepeatButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Slider.png")), tr("Slider"), tr("A control that lets the user select from a range of values by moving a Thumb control along a track."), "SliderPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SplitButton.png")), tr("SplitButton"), tr("A two-part button that display a flyout when its secondary part is clicked."), "SplitButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToggleButton.png")), tr("ToggleButton"), tr("A button that can be switched between two states like a CheckBox."), "ToggleButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToggleSplitButton.png")), tr("ToggleSplitButton"), tr("A version of the SplitButton where the activation target toggles on/off"), "ToggleSplitButtonPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToggleSwitch.png")), tr("ToggleSwitch"), tr("A switch that can be toggled between 2 states."), "ToggleSwitchPage");
}

void FluAllSamplesPage::makeCollectionsCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/FlipView.png")), tr("FlipView"), tr("Pressents a collection of items that the user can flip through, one item at a time."), "FlipViewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ListView.png")), tr("ListView"), tr("A control that presents a collection of items in a vertical list."), "ListViewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TreeView.png")), tr("TreeView"), tr("The TreeView control is a hierarchical list pattern with expanding and collapsing nodes that contain nested items."), "TreeViewPage");
}

void FluAllSamplesPage::makeDateAndTimeCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CalendarDatePicker.png")), tr("CalendarDatePicker"), tr("A control that lets users pick a date value using a calendar."), "CalendarDatePickerPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CalendarView.png")), tr("CalendarView"), tr("A control that presents aa calendar for a user to choose a date from."), "CalendarViewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/DatePicker.png")), tr("DatePicker"), tr("A control that lets a user pick a date value."), "DatePickerPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TimePicker.png")), tr("TimePicker"), tr("A configurable control that lets a user pick a time value."), "TimePickerPage");
}

void FluAllSamplesPage::makeDialogsAndFlyouts()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ContentDialog.png")), tr("ContentDialog"), tr("A dialog box that can be customized to contain any XAML content."), "ContentDialogPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Flyout.png")), tr("Flyout"), tr("Shows contextual information and enables user interaction."), "FlyoutPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TeachingTip.png")), tr("TeachingTip"), tr("A content-rich flyout for guiding users and enabling teaching moments."), "TeacingTipPage");
}

void FluAllSamplesPage::makeLayoutCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Border.png")), tr("Border"), tr("A container control that draws a boundary line, background, or both, around another object."), "BorderPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Canvas.png")), tr("Canvas"), tr("A layout panel that supports absolute positioning of child elements relative to the top left corner of the canvas."), "CanvasPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Expander.png")), tr("Expander"), tr("A container with a header that can be expanded to show a body with more content."), "ExpanderPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Grid.png")), tr("Grid"), tr("A flexible, primitive control for data-driven layouts."), "GridPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ItemsRepeater.png")), tr("ItemsRepeater"), tr("A flexible, primitive control for data-driven layouts."), "ItemRepeater");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RadioButtons.png")), tr("RadioButtons"), tr("A control that displays a group of mutually exclusive options with keyboarding and accessibility support."), "RadioButtonsPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RelativePanel.png")), tr("RelativePanel"), tr("A panel that users relationships between elements to define layout."), "RelativePanelPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SplitView.png")), tr("SplitView"), tr("A container that has 2 content areas, with multiple display options for the pane."), "SplitViewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/StackPanel.png")), tr("StackPanel"), tr("A layout panel that arranges child elements into a single line that can be oriented horizontally or vertically."), "StackPanelPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/VariableSizedWrapGrid.png")),
             tr("VariableSizedWrapGrid"),
             tr("A layout panel that supports arranging child elements in rows and columns. Each child element can span multiple rows and columns."),
             "VariableSizedWrapGridPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Viewbox.png")), tr("Viewbox"), tr("A container control that scales its content to a specified size."), "ViewboxPage");
}

void FluAllSamplesPage::makeMediaCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AnimatedVisualPlayer.png")), tr("AnimatedVisualPlayer"), tr("An element to render and control playback of motion graphics."), "AnimatedVisualPlayerPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/CaptureElement.png")), tr("Capture Element / Camera Perview"), tr("A sample for doing a camera preview."), "CaptureElementAndCameraPerviewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Image.png")), tr("Image"), tr("A control to display image content."), "ImagePage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/MapControl.png")), tr("MapControl"), tr("Display a symbolic map of the Earth."), "MapControlPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/MediaPlayerElement.png")), tr("MediaPlayerElement"), tr("A control to display video and image content."), "MediaPlayerElementPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/PersonPicture.png")), tr("PersonPicture"), tr("Displays the picture of a person/contact."), "PersonPicturePage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Sound.png")), tr("Sound"), tr("A code-behind only API that enables 2D and 3D UI sounds on all XAML controls."), "SoundPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/WebView.png")), tr("WebView2"), tr("A Microsoft Edge(Chrominum) based control that hosts HTML content in an app."), "WebView2Page");
}

void FluAllSamplesPage::makeNavigationCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/BreadcrumbBar.png")), tr("BreadcrumbBar"), tr("Shows the trail of navigation taken to the current location.."), "BreadcrumbBarPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/NavigationView.png")), tr("NavigationView"), tr("Common vertical layout for top-level areas of your app via a collapsible navigation menu."), "NavigationViewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Pivot.png")), tr("Pivot"), tr("Presents information from different sources in a tabbed view."), "PivotPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Pivot.png")), tr("SelectorBar"), tr("Presents information from a small set of different sources. The user can pick one of them."), "SelectorBarPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TabView.png")), tr("TabView"), tr("A control that displays a collection of tabs that can be used to display several documents."), "TabViewPage");
}

void FluAllSamplesPage::makeScrollingCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AnnotatedScrollBar.png")),
             tr("AnnotatedScrollBar"),
             tr("A control that extends a regular vertical scrollbar's functionality for an easy navigation through large collections."),
             "AnnotatedScrollBarPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/PipsPager.png")), tr("PipsPager"), tr("A control to let the user navigate through a paginated collection when the page numbers do not need to be visually known."), "PipsPagerPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ScrollView.png")), tr("ScrollView"), tr("A container control that lets the user pan and zoom its content."), "ScrollViewPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ScrollViewer.png")), tr("ScrollViewer"), tr("A container control that lets the user pan and zoom its content."), "ScrollViewerPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SemanticZoom.png")),
             tr("SemanticZoom"),
             tr("Lets the user zoom between two different views of a collection, making it easier to navigate through large collections of items.."),
             "SemanticZoomPage");
}

void FluAllSamplesPage::makeStatusInfoCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/InfoBadge.png")), tr("InfoBadge"), tr("An Non-instrusive Ui to display notifications or bring focus to an area."), "InfoBadgePage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/InfoBar.png")), tr("InfoBar"), tr("An inline message to display app-wide status change information."), "InfoBarPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ProgressBar.png")), tr("ProgressBar"), tr("Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction."), "ProgressBarPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ProgressRing.png")), tr("ProgressRing"), tr("Shows the apps progress on a task, or that the app is performing ongoing work that does block user interaction."), "ProgressRingPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToolTip.png")), tr("ToolTip"), tr("Displays information for element in a popup window."), "ToolTipPage");
}

void FluAllSamplesPage::makeTextCards()
{
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/AutoSuggestBox.png")), tr("AutoSuggestBox"), tr("A control to provide suggestions as a user is typing."), "AutoSuggestBoxPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/NumberBox.png")), tr("NumberBox"), tr("A text control used for numeric input and evaluation of algebraic equations."), "NumberBoxPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/PasswordBox.png")), tr("PasswordBox"), tr("A control for entering passwords."), "PasswordBoxPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RichEditBox.png")), tr("RichEditBox"), tr("A rich text editing control that supports formatted text, hyperlinks and other rich content."), "RichEditBoxPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RichTextBlock.png")), tr("RichTextBlock"), tr("A control that displays formatted text hyperlinks, inline images, and other rich content."), "RichTextBlockPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TextBlock.png")), tr("TextBlock"), tr("A lightweight control for displaying small amounts of text."), "TextBlockPage");
    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/TextBox.png")), tr("TextBox"), tr("A single-line or multi-line plain text field."), "TextBoxPage");
}

void FluAllSamplesPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluAllSamplesPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
