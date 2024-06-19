#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluComboBoxEx.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluColorLabel.h"

class FluComboBoxPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluComboBoxPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("ComboBox");
        m_infoLabel->setText("Use a ComboBox when you need to conserve on-screen space and when users select only one option at a time. A ComboBox shows only the currently selected item.");

        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("A ComboBox with items defined inline and its width set.");
        displayBox->getCodeExpander()->setCodeByPath("../code/ComboBoxPageCode1.md");
        displayBox->setBodyWidgetFixedHeight(96);

        auto comboBox = new FluComboBoxEx(displayBox);
        comboBox->setFixedWidth(200);
        comboBox->move(50, 50);
        comboBox->addItem("Blue");
        comboBox->addItem("Green");
        comboBox->addItem("Red");
        comboBox->addItem("Yellow");

        auto colorLabel = new FluColorLabel(displayBox);
        colorLabel->setObjectName("colorLabel");
        colorLabel->setProperty("color", "Blue");
        colorLabel->setFixedSize(100, 30);
        colorLabel->move(50, 90);

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);

        connect(comboBox, &FluComboBoxEx::currentTextChanged, [=](const QString& text) {
            colorLabel->setProperty("color", text);
            colorLabel->style()->polish(colorLabel);
        });
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBoxPage.qss", this);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluComboBoxPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluComboBoxPage.qss", this);
        }
    }
};
