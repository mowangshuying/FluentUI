#include "FluAllSamplesPage.h"

FluAllSamplesPage::FluAllSamplesPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);

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

    std::sort(m_cards.begin(), m_cards.end(), [=](FluHCard* card1, FluHCard* card2) { return card1->getKey() < card2->getKey(); });

    for (auto card : m_cards)
    {
        getFWScrollView()->getMainLayout()->addWidget(card);
        connect(card, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });
    }

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAllSamplesPage.qss", this);
}

void FluAllSamplesPage::makeBasicInputCards()
{
    auto buttonCard = new FluHCard(QPixmap("../res/ControlImages/Button.png"), 
        tr("Button"), 
        tr("A control that responds to user input and raises a Click event."));
    buttonCard->setKey("ButtonPage");
    m_cards.push_back(buttonCard);

    auto checkboxCard = new FluHCard(QPixmap("../res/ControlImages/Checkbox.png"), 
        tr("CheckBox"), 
        tr("A control that a user can select or clear."));
    checkboxCard->setKey("CheckBoxPage");
    m_cards.push_back(checkboxCard);

    auto colorPickerCard = new FluHCard(QPixmap("../res/ControlImages/ColorPicker.png"), 
        tr("ColorPicker"), 
        tr("A control that displays a selectable color spectrum."));
    colorPickerCard->setKey("ColorPickerPage");
    m_cards.push_back(colorPickerCard);

    auto comboBoxCard = new FluHCard(QPixmap("../res/ControlImages/ComboBox.png"), 
        tr("ComboBox"), 
        tr("A drop-down list of items a user can select from."));
    comboBoxCard->setKey("ComboBoxPage");
    m_cards.push_back(checkboxCard);

    auto dropDownButtonCard = new FluHCard(QPixmap("../res/ControlImages/DropDownButton.png"), 
        tr("DropDownButton"), 
        tr("A button that displays a flyout of choices when clicked."));
    dropDownButtonCard->setKey("DropDownButtonPage");
    m_cards.push_back(dropDownButtonCard);

    auto hyperlinkButtonCard = new FluHCard(QPixmap("../res/ControlImages/HyperlinkButton.png"), 
        tr("HyperlinkButton"), 
        tr("A button that appears as hyperlink text and can navigate to URI or handle a Click event."));
    hyperlinkButtonCard->setKey("HyperlinkButtonPage");
    m_cards.push_back(hyperlinkButtonCard);

    auto radioButtonCard = new FluHCard(QPixmap("../res/ControlImages/RadioButton.png"), 
        tr("RadioButton"), 
        tr("A control that allows a user to select a single option from a group of options."));
    radioButtonCard->setKey("RadioButtonPage");
    m_cards.push_back(radioButtonCard);

    auto ratingControlCard = new FluHCard(QPixmap("../res/ControlImages/RatingControl.png"), 
        tr("RatingControl"), 
        tr("Rate something 1 to 5 stars."));
    ratingControlCard->setKey("RatingControlPage");
    m_cards.push_back(ratingControlCard);

    auto repeatButtonCard = new FluHCard(QPixmap("../res/ControlImages/RepeatButton.png"), 
        tr("RepeatButton"), 
        tr("A button that raisers its Click event repeatedly from the time it's pressed until it's released."));
    repeatButtonCard->setKey("RepeatButtonPage");
    m_cards.push_back(repeatButtonCard);

    auto sliderCard = new FluHCard(QPixmap("../res/ControlImages/Slider.png"), 
        tr("Slider"), 
        tr("A control that lets the user select from a range of values by moving a Thumb control along a track."));
    sliderCard->setKey("SliderPage");
    m_cards.push_back(sliderCard);

    auto splitButtonCard = new FluHCard(QPixmap("../res/ControlImages/SplitButton.png"), 
        tr("SplitButton"), 
        tr("A two-part button that display a flyout when its secondary part is clicked."));
    splitButtonCard->setKey("SplitButtonPage");

    auto toggleButtonCard = new FluHCard(QPixmap("../res/ControlImages/ToggleButton.png"), 
        tr("ToggleButton"), 
        tr("A button that can be switched between two states like a CheckBox."));
    toggleButtonCard->setKey("ToggleButtonPage");
    m_cards.push_back(toggleButtonCard);

    auto toggleSplitButtonCard = new FluHCard(QPixmap("../res/ControlImages/ToggleSplitButton.png"), 
        tr("ToggleSplitButton"), 
        tr("A version of the SplitButton where the activation target toggles on/off"));
    toggleSplitButtonCard->setKey("ToggleSplitButtonPage");
    m_cards.push_back(toggleSplitButtonCard);

    auto toggleSwitchCard = new FluHCard(QPixmap("../res/ControlImages/ToggleSwitch.png"), 
        tr("ToggleSwitch"), 
        tr("A switch that can be toggled between 2 states."));
    toggleSwitchCard->setKey("ToggleSwitchPage");
    m_cards.push_back(toggleSwitchCard);
}

void FluAllSamplesPage::makeCollectionsCards()
{
    auto flipViewCard = new FluHCard(QPixmap("../res/ControlImages/FlipView.png"), 
        tr("FlipView"), 
        tr("Pressents a collection of items that the user can flip through, one item at a time."));
    flipViewCard->setKey("FlipViewPage");
    m_cards.push_back(flipViewCard);

    auto listViewCard = new FluHCard(QPixmap("../res/ControlImages/ListView.png"), 
        tr("ListView"), 
        tr("A control that presents a collection of items in a vertical list."));
    listViewCard->setKey("ListViewPage");
    m_cards.push_back(listViewCard);

    auto treeViewCard = new FluHCard(QPixmap("../res/ControlImages/TreeView.png"), 
        tr("TreeView"), 
        tr("The TreeView control is a hierarchical list pattern with expanding and collapsing nodes that contain nested items."));
    treeViewCard->setKey("TreeViewPage");
    m_cards.push_back(treeViewCard);
}

void FluAllSamplesPage::makeDateAndTimeCards()
{
    auto calendarDatePickerCard = new FluHCard(QPixmap("../res/ControlImages/CalendarDatePicker.png"), 
        tr("CalendarDatePicker"), 
        tr("A control that lets users pick a date value using a calendar."));
    calendarDatePickerCard->setKey("CalendarDatePickerPage");
    m_cards.push_back(calendarDatePickerCard);

    auto calendarViewCard = new FluHCard(QPixmap("../res/ControlImages/CalendarView.png"), 
        tr("CalendarView"), 
        tr("A control that presents aa calendar for a user to choose a date from."));
    calendarViewCard->setKey("CalendarViewPage");
    m_cards.push_back(calendarViewCard);

    auto datePickerCard = new FluHCard(QPixmap("../res/ControlImages/DatePicker.png"), 
        tr("DatePicker"), 
        tr("A control that lets a user pick a date value."));
    datePickerCard->setKey("DatePickerPage");
    m_cards.push_back(datePickerCard);

    auto timePickerCard = new FluHCard(QPixmap("../res/ControlImages/TimePicker.png"), 
        tr("TimePicker"), 
        tr("A configurable control that lets a user pick a time value."));
    timePickerCard->setKey("TimePickerPage");
    m_cards.push_back(timePickerCard);
}

void FluAllSamplesPage::makeDialogsAndFlyouts()
{
    auto contentDialogCard = new FluHCard(QPixmap("../res/ControlImages/ContentDialog.png"), 
        tr("ContentDialog"), 
        tr("A dialog box that can be customized to contain any XAML content."));
    contentDialogCard->setKey("ContentDialogPage");
    m_cards.push_back(contentDialogCard);

    auto flyoutCard = new FluHCard(QPixmap("../res/ControlImages/Flyout.png"), 
        tr("Flyout"), tr("Shows contextual information and enables user interaction."));
    flyoutCard->setKey("FlyoutPage");
    m_cards.push_back(flyoutCard);

    auto teachingTipCard = new FluHCard(QPixmap("../res/ControlImages/TeachingTip.png"), 
        tr("TeachingTip"), 
        tr("A content-rich flyout for guiding users and enabling teaching moments."));
    teachingTipCard->setKey("TeacingTipPage");
    m_cards.push_back(teachingTipCard);
}

void FluAllSamplesPage::makeLayoutCards()
{
    auto borderCard = new FluHCard(QPixmap("../res/ControlImages/Border.png"), 
        tr("Border"), 
        tr("A container control that draws a boundary line, background, or both, around another object."));
    borderCard->setKey("BorderPage");
    m_cards.push_back(borderCard);

    auto canvasCard = new FluHCard(QPixmap("../res/ControlImages/Canvas.png"), 
        tr("Canvas"), 
        tr("A layout panel that supports absolute positioning of child elements relative to the top left corner of the canvas."));
    canvasCard->setKey("CanvasPage");
    m_cards.push_back(canvasCard);

    auto expanderCard = new FluHCard(QPixmap("../res/ControlImages/Expander.png"), 
        tr("Expander"), 
        tr("A container with a header that can be expanded to show a body with more content."));
    expanderCard->setKey("ExpanderPage");
    m_cards.push_back(expanderCard);

    auto gridCard = new FluHCard(QPixmap("../res/ControlImages/Grid.png"), 
        tr("Grid"), 
        tr("A flexible, primitive control for data-driven layouts."));
    gridCard->setKey("GridPage");
    m_cards.push_back(gridCard);

    auto itemsRepeaterCard = new FluHCard(QPixmap("../res/ControlImages/ItemsRepeater.png"), 
        tr("ItemsRepeater"), 
        tr("A flexible, primitive control for data-driven layouts."));
    itemsRepeaterCard->setKey("ItemRepeater");
    m_cards.push_back(itemsRepeaterCard);

    auto radioButtonsCard = new FluHCard(QPixmap("../res/ControlImages/RadioButtons.png"), 
        tr("RadioButtons"), 
        tr("A control that displays a group of mutually exclusive options with keyboarding and accessibility support."));
    radioButtonsCard->setKey("RadioButtonsPage");
    m_cards.push_back(radioButtonsCard);

    auto relativePanelCard = new FluHCard(QPixmap("../res/ControlImages/RelativePanel.png"), 
        tr("RelativePanel"), 
        tr("A panel that users relationships between elements to define layout."));
    relativePanelCard->setKey("RelativePanelPage");
    m_cards.push_back(relativePanelCard);

    auto splitViewCard = new FluHCard(QPixmap("../res/ControlImages/SplitView.png"), 
        tr("SplitView"), 
        tr("A container that has 2 content areas, with multiple display options for the pane."));
    splitViewCard->setKey("SplitViewPage");
    m_cards.push_back(splitViewCard);

    auto stackPanelCard = new FluHCard(QPixmap("../res/ControlImages/StackPanel.png"), 
        tr("StackPanel"), 
        tr("A layout panel that arranges child elements into a single line that can be oriented horizontally or vertically."));
    stackPanelCard->setKey("StackPanelPage");
    m_cards.push_back(stackPanelCard);

    auto variableSizedWrapGridCard =
        new FluHCard(QPixmap("../res/ControlImages/VariableSizedWrapGrid.png"), 
            tr("VariableSizedWrapGrid"), 
            tr("A layout panel that supports arranging child elements in rows and columns. Each child element can span multiple rows and columns."));
    variableSizedWrapGridCard->setKey("VariableSizedWrapGridPage");
    m_cards.push_back(variableSizedWrapGridCard);

    auto viewboxCard = new FluHCard(QPixmap("../res/ControlImages/Viewbox.png"), 
        tr("Viewbox"), 
        tr("A container control that scales its content to a specified size."));
    viewboxCard->setKey("ViewboxPage");
    m_cards.push_back(viewboxCard);
}

void FluAllSamplesPage::makeMediaCards()
{
    auto animatedVisualPlayerCard = new FluHCard(QPixmap("../res/ControlImages/AnimatedVisualPlayer.png"), 
        tr("AnimatedVisualPlayer"), 
        tr("An element to render and control playback of motion graphics."));
    animatedVisualPlayerCard->setKey("AnimatedVisualPlayerPage");
    m_cards.push_back(animatedVisualPlayerCard);

    auto captureElementAndCameraPreviewCard = new FluHCard(QPixmap("../res/ControlImages/CaptureElement.png"), 
        tr("Capture Element / Camera Perview"), 
        tr("A sample for doing a camera preview."));
    
    captureElementAndCameraPreviewCard->setKey("CaptureElementAndCameraPerviewPage");
    m_cards.push_back(captureElementAndCameraPreviewCard);

    auto imageCard = new FluHCard(QPixmap("../res/ControlImages/Image.png"), 
        tr("Image"), 
        tr("A control to display image content."));
    imageCard->setKey("ImagePage");
    m_cards.push_back(imageCard);

    auto mapControlCard = new FluHCard(QPixmap("../res/ControlImages/MapControl.png"), 
        tr("MapControl"), 
        tr("Display a symbolic map of the Earth."));
    mapControlCard->setKey("MapControlPage");
    m_cards.push_back(mapControlCard);

    auto mediaPlayerElementCard = new FluHCard(QPixmap("../res/ControlImages/MediaPlayerElement.png"), 
        tr("MediaPlayerElement"), 
        tr("A control to display video and image content."));
    mediaPlayerElementCard->setKey("MediaPlayerElementPage");
    m_cards.push_back(mediaPlayerElementCard);

    auto personPictureCard = new FluHCard(QPixmap("../res/ControlImages/PersonPicture.png"), 
        tr("PersonPicture"), 
        tr("Displays the picture of a person/contact."));
    personPictureCard->setKey("PersonPicturePage");
    m_cards.push_back(personPictureCard);

    auto soundCard = new FluHCard(QPixmap("../res/ControlImages/Sound.png"), 
        tr("Sound"), 
        tr("A code-behind only API that enables 2D and 3D UI sounds on all XAML controls."));
    soundCard->setKey("SoundPage");
    m_cards.push_back(soundCard);

    auto webView2Card = new FluHCard(QPixmap("../res/ControlImages/WebView.png"), 
        tr("WebView2"), 
        tr("A Microsoft Edge(Chrominum) based control that hosts HTML content in an app."));
    webView2Card->setKey("WebView2Page");
    m_cards.push_back(webView2Card);
}

void FluAllSamplesPage::makeMenusAndToolbars()
{
    auto appBarButtonCard = new FluHCard(QPixmap("../res/ControlImages/AppBarButton.png"), 
        tr("AppBarButton"), tr("A button that's styled for use in a CommandBar."));
    appBarButtonCard->setKey("AppBarButtonPage");
    m_cards.push_back(appBarButtonCard);

    auto appBarSeparatorCard = new FluHCard(QPixmap("../res/ControlImages/AppBarSeparator.png"), 
        tr("AppBarSeparator"), 
        tr("A vertical line that's used to visually separate groups of commands in an app bar."));
    appBarSeparatorCard->setKey("AppBarSeparatorPage");
    m_cards.push_back(appBarSeparatorCard);

    auto appBarToggleButtonCard =
        new FluHCard(QPixmap("../res/ControlImages/AppBarToggleButton.png"), 
            tr("AppBarToggleButton"), 
            tr("A button that can be on, off, or indeterminate like a CheckBox, and is styled for use in an app bar or other specialized UI."));
    appBarToggleButtonCard->setKey("AppBarToggleButtonPage");
    m_cards.push_back(appBarToggleButtonCard);

    auto commandBarCard = new FluHCard(QPixmap("../res/ControlImages/CommandBar.png"), 
        tr("CommandBar"), 
        tr("A toolbar for displaying application-specific commands that hanles layout and resizing of its contents."));
    commandBarCard->setKey("CommandBarPage");
    m_cards.push_back(commandBarCard);

    auto commandBarFlyoutCard = new FluHCard(QPixmap("../res/ControlImages/CommandBarFlyout.png"), 
        tr("CommandBarFlyout"), 
        tr("A mini-toolbar displaying proactive commands, and an optional menu of command."));
    commandBarFlyoutCard->setKey("CommandBarFlyoutPage");
    m_cards.push_back(commandBarCard);

    auto menuBarCard = new FluHCard(QPixmap("../res/ControlImages/MenuBar.png"), 
        tr("MenuBar"), 
        tr("A classic menu, allowing the display of MenuItems containing MenuFlyoutItems."));
    menuBarCard->setKey("MenuBarPage");
    m_cards.push_back(menuBarCard);

    auto menuFlyoutCard = new FluHCard(QPixmap("../res/ControlImages/MenuFlyout.png"), 
        tr("MenuFlyout"), 
        tr("Shows a contextual list of simple command or options."));
    menuFlyoutCard->setKey("MenuFlyoutPage");
    m_cards.push_back(menuFlyoutCard);

    auto standUICommandCard = new FluHCard(QPixmap("../res/ControlImages/StandardUICommand.png"), 
        tr("StandardUICommand"), 
        tr("A StandardUICommand is a built-in 'XamlUICommand' which represents a commonly used command, e.g.'save'."));
    standUICommandCard->setKey("StandardUICommandPage");
    m_cards.push_back(standUICommandCard);

    auto swipeControlCard = new FluHCard(QPixmap("../res/ControlImages/SwipeControl.png"), 
        tr("SwipeControl"), 
        tr("Touch gesture for quick menu actions on items."));
    swipeControlCard->setKey("SwipeControlPage");
    m_cards.push_back(swipeControlCard);
}

void FluAllSamplesPage::makeNavigationCards()
{
    auto breadcrumbBarCard = new FluHCard(QPixmap("../res/ControlImages/BreadcrumbBar.png"), 
        tr("BreadcrumbBar"), 
        tr("Shows the trail of navigation taken to the current location.."));
    breadcrumbBarCard->setKey("BreadcrumbBarPage");
    m_cards.push_back(breadcrumbBarCard);

    auto navigationViewCard = new FluHCard(QPixmap("../res/ControlImages/NavigationView.png"), 
        tr("NavigationView"), 
        tr("Common vertical layout for top-level areas of your app via a collapsible navigation menu."));
    navigationViewCard->setKey("NavigationViewPage");
    m_cards.push_back(navigationViewCard);

    auto pivotCard = new FluHCard(QPixmap("../res/ControlImages/Pivot.png"), 
        tr("Pivot"), 
        tr("Presents information from different sources in a tabbed view."));
    pivotCard->setKey("PivotPage");
    m_cards.push_back(pivotCard);

    auto selectorBarCard = new FluHCard(QPixmap("../res/ControlImages/Pivot.png"), 
        tr("SelectorBar"), 
        tr("Presents information from a small set of different sources. The user can pick one of them."));
    selectorBarCard->setKey("SelectorBarPage");
    m_cards.push_back(selectorBarCard);

    auto tabViewCard = new FluHCard(QPixmap("../res/ControlImages/TabView.png"), 
        tr("TabView"), 
        tr("A control that displays a collection of tabs that can be used to display several documents."));
    tabViewCard->setKey("TabViewPage");
    m_cards.push_back(tabViewCard);
}

void FluAllSamplesPage::makeScrollingCards()
{
    auto annotatedScrollBarCard = new FluHCard(QPixmap("../res/ControlImages/AnnotatedScrollBar.png"), 
        tr("AnnotatedScrollBar"), 
        tr("A control that extends a regular vertical scrollbar's functionality for an easy navigation through large collections."));
    annotatedScrollBarCard->setKey("AnnotatedScrollBarPage");
    m_cards.push_back(annotatedScrollBarCard);

    auto pipsPagerCard = new FluHCard(QPixmap("../res/ControlImages/PipsPager.png"), tr("PipsPager"), 
        tr("A control to let the user navigate through a paginated collection when the page numbers do not need to be visually known."));
    pipsPagerCard->setKey("PipsPagerPage");
    m_cards.push_back(pipsPagerCard);

    auto scrollViewCard = new FluHCard(QPixmap("../res/ControlImages/ScrollView.png"), 
        tr("ScrollView"), tr("A container control that lets the user pan and zoom its content."));
    scrollViewCard->setKey("ScrollViewPage");
    m_cards.push_back(scrollViewCard);

    auto scrollViewerCard = new FluHCard(QPixmap("../res/ControlImages/ScrollViewer.png"), tr("ScrollViewer"), 
        tr("A container control that lets the user pan and zoom its content."));
    scrollViewerCard->setKey("ScrollViewerPage");
    m_cards.push_back(scrollViewerCard);

    auto semanticZoomCard = new FluHCard(QPixmap("../res/ControlImages/SemanticZoom.png"), tr("SemanticZoom"), 
        tr("Lets the user zoom between two different views of a collection, making it easier to navigate through large collections of items.."));
    semanticZoomCard->setKey("SemanticZoomPage");
    m_cards.push_back(semanticZoomCard);
}

void FluAllSamplesPage::makeStatusInfoCards()
{
    auto infoBadgeCard = new FluHCard(QPixmap("../res/ControlImages/InfoBadge.png"), tr("InfoBadge"), 
        tr("An Non-instrusive Ui to display notifications or bring focus to an area."));
    infoBadgeCard->setKey("InfoBadgePage");
    m_cards.push_back(infoBadgeCard);

    auto infoBarCard = new FluHCard(QPixmap("../res/ControlImages/InfoBar.png"), tr("InfoBar"), 
        tr("An inline message to display app-wide status change information."));
    infoBarCard->setKey("InfoBarPage");
    m_cards.push_back(infoBarCard);

    auto progressBarCard = new FluHCard(QPixmap("../res/ControlImages/ProgressBar.png"), 
        tr("ProgressBar"), 
        tr("Shows the apps progress on a task, or that the app is performing ongoing work that doesn't block user interaction."));
    progressBarCard->setKey("ProgressBarPage");
    m_cards.push_back(progressBarCard);

    auto progressRingCard = new FluHCard(QPixmap("../res/ControlImages/ProgressRing.png"), tr("ProgressRing"), 
        tr("Shows the apps progress on a task, or that the app is performing ongoing work that does block user interaction."));
    progressRingCard->setKey("ProgressRingPage");
    m_cards.push_back(progressRingCard);

    auto toolTipCard = new FluHCard(QPixmap("../res/ControlImages/ToolTip.png"), tr("ToolTip"), tr("Displays information for element in a popup window."));
    toolTipCard->setKey("ToolTipPage");
    m_cards.push_back(toolTipCard);
}

void FluAllSamplesPage::makeTextCards()
{
    auto autoSuggestBoxCard = new FluHCard(QPixmap("../res/ControlImages/AutoSuggestBox.png"), tr("AutoSuggestBox"), tr("A control to provide suggestions as a user is typing."));
    autoSuggestBoxCard->setKey("AutoSuggestBoxPage");
    m_cards.push_back(autoSuggestBoxCard);

    auto numberBoxCard = new FluHCard(QPixmap("../res/ControlImages/NumberBox.png"), tr("NumberBox"), tr("A text control used for numeric input and evaluation of algebraic equations."));
    numberBoxCard->setKey("NumberBoxPage");
    m_cards.push_back(numberBoxCard);

    auto passwordBoxCard = new FluHCard(QPixmap("../res/ControlImages/PasswordBox.png"), tr("PasswordBox"), tr("A control for entering passwords."));
    passwordBoxCard->setKey("PasswordBoxPage");
    m_cards.push_back(passwordBoxCard);

    auto richEditBoxCard = new FluHCard(QPixmap("../res/ControlImages/RichEditBox.png"), 
        tr("RichEditBox"), tr("A rich text editing control that supports formatted text, hyperlinks and other rich content."));
    richEditBoxCard->setKey("RichEditBoxPage");
    m_cards.push_back(richEditBoxCard);

    auto richTextBlockCard = new FluHCard(QPixmap("../res/ControlImages/RichTextBlock.png"), tr("RichTextBlock"), 
        tr("A control that displays formatted text hyperlinks, inline images, and other rich content."));
    richTextBlockCard->setKey("RichTextBlockPage");
    m_cards.push_back(richTextBlockCard);

    auto textBlockCard = new FluHCard(QPixmap("../res/ControlImages/TextBlock.png"), tr("TextBlock"), tr("A lightweight control for displaying small amounts of text."));
    textBlockCard->setKey("TextBlockPage");
    m_cards.push_back(textBlockCard);

    auto textBoxCard = new FluHCard(QPixmap("../res/ControlImages/TextBox.png"), tr("TextBox"), 
        tr("A single-line or multi-line plain text field."));
    textBoxCard->setKey("TextBoxPage");
    m_cards.push_back(textBoxCard);
}

void FluAllSamplesPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAllSamplesPage.qss", this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAllSamplesPage.qss", this);
    }
}
