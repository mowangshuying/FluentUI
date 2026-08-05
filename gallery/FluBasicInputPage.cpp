#include "FluBasicInputPage.h"

FluBasicInputPage::FluBasicInputPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_mainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Basic input"));

    auto buttonCard = addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Button.png")), tr("Button"), tr("A control that responds to user input and raises a Click event."), "ButtonPage");
    FluDotInfoBadge::setDotInfoBadge(buttonCard, 20, 20);

    auto checkboxCard = addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Checkbox.png")), tr("CheckBox"), tr("A control that a user can select or clear."), "CheckBoxPage");
    FluDotInfoBadge::setDotInfoBadge(checkboxCard, 20, 20);

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ColorPicker.png")), tr("ColorPicker"), tr("A control that displays a selectable color spectrum."), "ColorPickerPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ComboBox.png")), tr("ComboBox"), tr("A drop-down list of items a user can select from."), "ComboBoxPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/DropDownButton.png")), tr("DropDownButton"), tr("A button that displays a flyout of choices when clicked."), "DropDownButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/HyperlinkButton.png")), tr("HyperlinkButton"), tr("A button that appears as hyperlink text and can navigate to URI or handle a Click event."), "HyperlinkButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RadioButton.png")), tr("RadioButton"), tr("A control that allows a user to select a single option from a group of options."), "RadioButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RatingControl.png")), tr("RatingControl"), tr("Rate something 1 to 5 stars."), "RatingControlPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/RepeatButton.png")), tr("RepeatButton"), tr("A button that raisers its Click event repeatedly from the time it's pressed until it's released."), "RepeatButtonPage");

    auto sliderCard = addHCard(FluIconUtils::getPixmap(("../res/ControlImages/Slider.png")), tr("Slider"), tr("A control that lets the user select from a range of values by moving a Thumb control along a track."), "SliderPage");
    FluDotInfoBadge::setDotInfoBadge(sliderCard, 20, 20);

    auto splitButtonCard = addHCard(FluIconUtils::getPixmap(("../res/ControlImages/SplitButton.png")), tr("SplitButton"), tr("A two-part button that display a flyout when its secondary part is clicked."), "SplitButtonPage");
    FluDotInfoBadge::setDotInfoBadge(splitButtonCard, 20, 20);

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToggleButton.png")), tr("ToggleButton"), tr("A button that can be switched between two states like a CheckBox."), "ToggleButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToggleSplitButton.png")), tr("ToggleSplitButton"), tr("A version of the SplitButton where the activation target toggles on/off"), "ToggleSplitButtonPage");

    addHCard(FluIconUtils::getPixmap(("../res/ControlImages/ToggleSwitch.png")), tr("ToggleSwitch"), tr("A switch that can be toggled between 2 states."), "ToggleSwitchPage");

    onThemeChanged();
}

void FluBasicInputPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluBasicInputPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
