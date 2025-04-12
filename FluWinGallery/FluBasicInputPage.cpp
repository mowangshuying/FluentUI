#include "FluBasicInputPage.h"

FluBasicInputPage::FluBasicInputPage(QWidget* parent /*= nullptr*/) : FluATitlePage(parent)
{
    m_vMainLayout->setContentsMargins(35, 35, 0, 35);
    m_titleLabel->setText(tr("Basic input"));

    auto buttonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Button.png")), tr("Button"), tr("A control that responds to user input and raises a Click event."));
    buttonCard->setKey("ButtonPage");

    FluCircleDot::setCircleDot(buttonCard, 20, 20);
    getFWScrollView()->getMainLayout()->addWidget(buttonCard);
    connect(buttonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto checkboxCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Checkbox.png")), tr("CheckBox"), tr("A control that a user can select or clear."));
    checkboxCard->setKey("CheckBoxPage");

    FluCircleDot::setCircleDot(checkboxCard, 20, 20);
    getFWScrollView()->getMainLayout()->addWidget(checkboxCard);
    connect(checkboxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto colorPickerCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ColorPicker.png")), tr("ColorPicker"), tr("A control that displays a selectable color spectrum."));
    colorPickerCard->setKey("ColorPickerPage");
    getFWScrollView()->getMainLayout()->addWidget(colorPickerCard);
    connect(colorPickerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto comboBoxBtn = new FluHCard(QPixmap(FLURC("res/ControlImages/ComboBox.png")), tr("ComboBox"), tr("A drop-down list of items a user can select from."));
    comboBoxBtn->setKey("ComboBoxPage");
    getFWScrollView()->getMainLayout()->addWidget(comboBoxBtn);
    connect(comboBoxBtn, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto dropDownButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/DropDownButton.png")), tr("DropDownButton"), tr("A button that displays a flyout of choices when clicked."));
    dropDownButtonCard->setKey("DropDownButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(dropDownButtonCard);
    connect(dropDownButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto hyperlinkButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/HyperlinkButton.png")), tr("HyperlinkButton"), tr("A button that appears as hyperlink text and can navigate to URI or handle a Click event."));
    hyperlinkButtonCard->setKey("HyperlinkButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(hyperlinkButtonCard);
    connect(hyperlinkButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto radioButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/RadioButton.png")), tr("RadioButton"), tr("A control that allows a user to select a single option from a group of options."));
    radioButtonCard->setKey("RadioButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(radioButtonCard);
    connect(radioButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto ratingControlCard = new FluHCard(QPixmap(FLURC("res/ControlImages/RatingControl.png")), tr("RatingControl"), tr("Rate something 1 to 5 stars."));
    ratingControlCard->setKey("RatingControlPage");
    getFWScrollView()->getMainLayout()->addWidget(ratingControlCard);
    connect(ratingControlCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto repeatButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/RepeatButton.png")), tr("RepeatButton"), tr("A button that raisers its Click event repeatedly from the time it's pressed until it's released."));
    repeatButtonCard->setKey("RepeatButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(repeatButtonCard);
    connect(repeatButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto sliderCard = new FluHCard(QPixmap(FLURC("res/ControlImages/Slider.png")), tr("Slider"), tr("A control that lets the user select from a range of values by moving a Thumb control along a track."));
    sliderCard->setKey("SliderPage");

    FluCircleDot::setCircleDot(sliderCard, 20, 20);
    getFWScrollView()->getMainLayout()->addWidget(sliderCard);
    connect(sliderCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto splitButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/SplitButton.png")), tr("SplitButton"), tr("A two-part button that display a flyout when its secondary part is clicked."));
    splitButtonCard->setKey("SplitButtonPage");

    FluCircleDot::setCircleDot(splitButtonCard, 20, 20);
    getFWScrollView()->getMainLayout()->addWidget(splitButtonCard);
    connect(splitButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto toggleButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ToggleButton.png")), tr("ToggleButton"), tr("A button that can be switched between two states like a CheckBox."));
    toggleButtonCard->setKey("ToggleButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(toggleButtonCard);
    connect(toggleButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto toggleSplitButtonCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ToggleSplitButton.png")), tr("ToggleSplitButton"), tr("A version of the SplitButton where the activation target toggles on/off"));
    toggleSplitButtonCard->setKey("ToggleSplitButtonPage");
    getFWScrollView()->getMainLayout()->addWidget(toggleSplitButtonCard);
    connect(toggleSplitButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    auto toggleSwitchCard = new FluHCard(QPixmap(FLURC("res/ControlImages/ToggleSwitch.png")), tr("ToggleSwitch"), tr("A switch that can be toggled between 2 states."));
    toggleSwitchCard->setKey("ToggleSwitchPage");
    getFWScrollView()->getMainLayout()->addWidget(toggleSwitchCard);
    connect(toggleSwitchCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

    onThemeChanged();
}

void FluBasicInputPage::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/light/FluBasicInputPage.qss"), this);
    }
    else
    {
        FluStyleSheetUitls::setQssByFileName(FLURC("StyleSheet/dark/FluBasicInputPage.qss"), this);
    }
}
