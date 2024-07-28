#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluAppBarButton.h"

class FluAppBarButtonPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluAppBarButtonPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("AppBarButton");
        m_infoLabel->setText(
            "App bar buttons differ from standard buttons in several ways:\n"
            "-Their default appearance is a transparent background with a smaller size\n"
            "-You use the Label and Icon properties to set the content instead of the content property.The Content property is ignored.\n"
            "-The button's IsCompact property control its size.");

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarButtonPage.qss", this);

        addSymbolIconAppBarButton();
        addKeyboardAcceleratorAppBarButton();
    }

    void addSymbolIconAppBarButton()
    {
        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("An AppBarButton with a symbol icon.");
        displayBox->getCodeExpander()->setCodeByPath("../code/AppBarButtonPageCode1.md");

        auto appBarButton = new FluAppBarButton(FluAwesomeType::Like);
        appBarButton->setText("SymbolIcon");
        displayBox->getBodyLayout()->addWidget(appBarButton);
        connect(appBarButton, &FluAppBarButton::clicked, [=]() { LOG_DEBUG << "called"; });

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }

    void addKeyboardAcceleratorAppBarButton()
    {
        auto displayBox = new FluDisplayBox;
        displayBox->setTitle("An AppBarButton with a KeyboardAccelerator.");
        displayBox->getCodeExpander()->setCodeByPath("../code/AppBarButtonPageCode2.md");

        auto appBarButton = new FluAppBarButton(FluAwesomeType::Save);
        appBarButton->setText("Save");
        appBarButton->setShortCut(QKeySequence(Qt::CTRL + Qt::Key_S));
        displayBox->getBodyLayout()->addWidget(appBarButton);
        connect(appBarButton, &FluAppBarButton::clicked, [=]() { LOG_DEBUG << "called"; });

        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }

  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAppBarButtonPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAppBarButtonPage.qss", this);
        }
    }
};
