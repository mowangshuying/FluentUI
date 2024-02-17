#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluFWScrollView.h"
#include "../FluUtils/FluUtils.h"
#include "FluATitlePage.h"
#include "../FluControls/FluHCard.h"

class FluAllSamplesPage : public FluATitlePage
{
    Q_OBJECT
  public:
    FluAllSamplesPage(QWidget* parent = nullptr) : FluATitlePage(parent)
    {
          m_vMainLayout->setContentsMargins(35, 35, 0, 35);
          m_titleLabel->setText("All Samples");

          auto buttonCard = new FluHCard(QPixmap("../res/ControlImages/Button.png"), "Button", "A control that responds to user input and raises a Click event.");
          getFWScrollView()->getMainLayout()->addWidget(buttonCard);

          auto checkboxCard = new FluHCard(QPixmap("../res/ControlImages/CheckBox.png"), "CheckBox", "A control that a user can select or clear.");
          getFWScrollView()->getMainLayout()->addWidget(checkboxCard);

          auto colorPickerCard = new FluHCard(QPixmap("../res/ControlImages/ColorPicker.png"), "ColorPicker", "A control that displays a selectable color spectrum.");
          getFWScrollView()->getMainLayout()->addWidget(colorPickerCard);

           auto comboBoxBtn = new FluHCard(QPixmap("../res/ControlImages/ComboBox.png"), "ComboBox", "A drop-down list of items a user can select from.");
          getFWScrollView()->getMainLayout()->addWidget(comboBoxBtn);

           auto dropDownButtonCard = new FluHCard(QPixmap("../res/ControlImages/DropDownButton.png"), "DropDownButton", "A button that displays a flyout of choices when clicked.");
          getFWScrollView()->getMainLayout()->addWidget(dropDownButtonCard);


          auto hyperlinkButtonCard = new FluHCard(QPixmap("../res/ControlImages/HyperlinkButton.png"), "HyperlinkButton", "A button that appears as hyperlink text and can navigate to URI or handle a Click event.");
          getFWScrollView()->getMainLayout()->addWidget(hyperlinkButtonCard);

          auto radioButtonCard = new FluHCard(QPixmap("../res/ControlImages/RadioButton.png"), "RadioButton", "A control that allows a user to select a single option from a group of options.");
          getFWScrollView()->getMainLayout()->addWidget(radioButtonCard);

          auto ratingControlCard = new FluHCard(QPixmap("../res/ControlImages/RatingControl.png"), "RatingControl", "Rate something 1 to 5 stars.");
          getFWScrollView()->getMainLayout()->addWidget(ratingControlCard);

           auto repeatButtonCard = new FluHCard(QPixmap("../res/ControlImages/RepeatButton.png"), "RepeatButton", "A button that raisers its Click event repeatedly from the time it's pressed until it's released.");
          getFWScrollView()->getMainLayout()->addWidget(repeatButtonCard);

           auto sliderCard = new FluHCard(QPixmap("../res/ControlImages/Slider.png"), "Slider", "A control that lets the user select from a range of values by moving a Thumb control along a track.");
          getFWScrollView()->getMainLayout()->addWidget(sliderCard);

           auto splitButtonCard = new FluHCard(QPixmap("../res/ControlImages/SplitButton.png"), "SplitButton", "A two-part button that display a flyout when its secondary part is clicked.");
          getFWScrollView()->getMainLayout()->addWidget(splitButtonCard);

           auto toggleButtonCard = new FluHCard(QPixmap("../res/ControlImages/ToggleButton.png"), "ToggleButton", "A button that can be switched between two states like a CheckBox.");
          getFWScrollView()->getMainLayout()->addWidget(toggleButtonCard);

           auto toggleSplitButtonCard = new FluHCard(QPixmap("../res/ControlImages/ToggleSplitButton.png"), "ToggleSplitButton", "A version of the SplitButton where the activation target toggles on/off");
          getFWScrollView()->getMainLayout()->addWidget(toggleSplitButtonCard);

          auto toggleSwitchCard = new FluHCard(QPixmap("../res/ControlImages/ToggleSwitch.png"), "ToggleSwitch", "A switch that can be toggled between 2 states.");
          getFWScrollView()->getMainLayout()->addWidget(toggleSwitchCard);

    }

    //void paintEvent(QPaintEvent* event)
    //{
    //    QStyleOption opt;
    //    opt.initFrom(this);
   //     QPainter painter(this);
   //     style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
   // }

  protected:
   // QVBoxLayout* m_vMainLayout;
    // QLabel* m_allSameplesLabel;
   // FluFWScrollView* m_FwScrollView;
};
