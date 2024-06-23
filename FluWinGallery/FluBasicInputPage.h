#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluFWScrollView.h"
#include "../FluUtils/FluUtils.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"

class FluBasicInputPage : public FluATitlePage
{
    Q_OBJECT
  public:
      FluBasicInputPage(QWidget* parent = nullptr) : FluATitlePage(parent)
      {
          m_vMainLayout->setContentsMargins(35, 35, 0, 35);
          m_titleLabel->setText("Basic input");

           auto buttonCard = new FluHCard(QPixmap("../res/ControlImages/Button.png"), "Button", "A control that responds to user input and raises a Click event.");
          buttonCard->setKey("ButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(buttonCard);
          connect(buttonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto checkboxCard = new FluHCard(QPixmap("../res/ControlImages/CheckBox.png"), "CheckBox", "A control that a user can select or clear.");
          checkboxCard->setKey("CheckBoxPage");
          getFWScrollView()->getMainLayout()->addWidget(checkboxCard);
          connect(checkboxCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto colorPickerCard = new FluHCard(QPixmap("../res/ControlImages/ColorPicker.png"), "ColorPicker", "A control that displays a selectable color spectrum.");
          colorPickerCard->setKey("ColorPickerPage");
          getFWScrollView()->getMainLayout()->addWidget(colorPickerCard);
          connect(colorPickerCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto comboBoxBtn = new FluHCard(QPixmap("../res/ControlImages/ComboBox.png"), "ComboBox", "A drop-down list of items a user can select from.");
          comboBoxBtn->setKey("ComboBoxPage");
          getFWScrollView()->getMainLayout()->addWidget(comboBoxBtn);
          connect(comboBoxBtn, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto dropDownButtonCard = new FluHCard(QPixmap("../res/ControlImages/DropDownButton.png"), "DropDownButton", "A button that displays a flyout of choices when clicked.");
          dropDownButtonCard->setKey("DropDownButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(dropDownButtonCard);
          connect(dropDownButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto hyperlinkButtonCard = new FluHCard(QPixmap("../res/ControlImages/HyperlinkButton.png"), "HyperlinkButton", "A button that appears as hyperlink text and can navigate to URI or handle a Click event.");
          hyperlinkButtonCard->setKey("HyperlinkButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(hyperlinkButtonCard);
          connect(hyperlinkButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto radioButtonCard = new FluHCard(QPixmap("../res/ControlImages/RadioButton.png"), "RadioButton", "A control that allows a user to select a single option from a group of options.");
          radioButtonCard->setKey("RadioButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(radioButtonCard);
          connect(radioButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto ratingControlCard = new FluHCard(QPixmap("../res/ControlImages/RatingControl.png"), "RatingControl", "Rate something 1 to 5 stars.");
          ratingControlCard->setKey("RatingControlPage");
          getFWScrollView()->getMainLayout()->addWidget(ratingControlCard);
          connect(ratingControlCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto repeatButtonCard = new FluHCard(QPixmap("../res/ControlImages/RepeatButton.png"), "RepeatButton", "A button that raisers its Click event repeatedly from the time it's pressed until it's released.");
          repeatButtonCard->setKey("RepeatButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(repeatButtonCard);
          connect(repeatButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto sliderCard = new FluHCard(QPixmap("../res/ControlImages/Slider.png"), "Slider", "A control that lets the user select from a range of values by moving a Thumb control along a track.");
          sliderCard->setKey("SliderPage");
          getFWScrollView()->getMainLayout()->addWidget(sliderCard);
          connect(sliderCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto splitButtonCard = new FluHCard(QPixmap("../res/ControlImages/SplitButton.png"), "SplitButton", "A two-part button that display a flyout when its secondary part is clicked.");
          splitButtonCard->setKey("SplitButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(splitButtonCard);
          connect(splitButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto toggleButtonCard = new FluHCard(QPixmap("../res/ControlImages/ToggleButton.png"), "ToggleButton", "A button that can be switched between two states like a CheckBox.");
          toggleButtonCard->setKey("ToggleButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(toggleButtonCard);
          connect(toggleButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto toggleSplitButtonCard = new FluHCard(QPixmap("../res/ControlImages/ToggleSplitButton.png"), "ToggleSplitButton", "A version of the SplitButton where the activation target toggles on/off");
          toggleSplitButtonCard->setKey("ToggleSplitButtonPage");
          getFWScrollView()->getMainLayout()->addWidget(toggleSplitButtonCard);
          connect(toggleSplitButtonCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          auto toggleSwitchCard = new FluHCard(QPixmap("../res/ControlImages/ToggleSwitch.png"), "ToggleSwitch", "A switch that can be toggled between 2 states.");
          toggleSwitchCard->setKey("ToggleSwitchPage");
          getFWScrollView()->getMainLayout()->addWidget(toggleSwitchCard);
          connect(toggleSwitchCard, &FluHCard::clicked, [=](QString key) { emit clickedHCard(key); });

          FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluBasicInputPage.qss", this);
      }

        signals:
      void clickedHCard(QString key);
    public slots:
      void onThemeChanged()
      {
          if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluBasicInputPage.qss", this);
          }
          else
          {
              FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluBasicInputPage.qss", this);
          }
      }

    protected:
};
