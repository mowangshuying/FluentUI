#pragma once

#include "FluAEmptyPage.h"
#include "../FluControls/FluDisplayBox.h"
#include "../FluControls/FluShortInfoBar.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluDisplayBoxEx.h"
#include "../FluControls/FluComboBox.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluInfoBarMgr.h"

class FluInfoBarPage : public FluAEmptyPage
{
    Q_OBJECT
  public:
    FluInfoBarPage(QWidget* parent = nullptr) : FluAEmptyPage(parent)
    {
        m_mainLayout->setAlignment(Qt::AlignTop);
        m_titleLabel->setText("InfoBar");
        m_infoLabel->setText(
            "Use an InfoBar control when a user should be informed of, acknowledge, or take action on a changed application state. By default the notification will remain in the content area until closed by the user but will not necessarily "
            "break user flow.");

        addClosableInfoBar();

        addDynamicInfoBar();

        connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluInfoBarPage.qss", this);
    }

    void addClosableInfoBar()
    {
        FluDisplayBoxEx* displayBox = new FluDisplayBoxEx;
        displayBox->setTitle("A closabel InforBar with options to change its severity.");
        displayBox->getCodeExpander()->setCodeByPath("../Code/InfoBarPageCode1");
        displayBox->setBodyWidgetFixedHeight(120);

        FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info);
        sInfoBar->setFixedWidth(270);
        displayBox->getBodyContentLayout()->addWidget(sInfoBar);

        auto comboBox = new FluComboBox;
        comboBox->addItem("Informational");
        comboBox->addItem("Success");
        comboBox->addItem("Warning");
        comboBox->addItem("Error");

        connect(comboBox, &FluComboBox::currentIndexChanged, [=](int index) mutable {
            //   LOG_DEBUG << displayBox->getBodyContentLayout()->count();
            if (!displayBox->getBodyContentLayout()->isEmpty())
            {
                displayBox->getBodyContentLayout()->removeWidget(sInfoBar);
                delete sInfoBar;
                sInfoBar = nullptr;
            }

            switch (index)
            {
                case 0:
                    sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info);
                    break;
                case 1:
                    sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Suc);
                    break;
                case 2:
                    sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Warn);
                    break;
                case 3:
                    sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Error);
                    break;

                default:
                    break;
            }
            sInfoBar->setFixedWidth(270);
            displayBox->getBodyContentLayout()->addWidget(sInfoBar);
        });

        displayBox->getBodyRightLayout()->addWidget(comboBox);
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }

    void addDynamicInfoBar()
    {
        FluDisplayBox* displayBox = new FluDisplayBox;
        displayBox->setTitle("A dynamic InforBar.");
        displayBox->getCodeExpander()->setCodeByPath("../Code/InfoBarPageCode2");
        displayBox->setBodyWidgetFixedHeight(256);

        auto infoBtn = new FluPushButton;
        auto sucBtn = new FluPushButton;
        auto warnBtn = new FluPushButton;
        auto errorBtn = new FluPushButton;

        infoBtn->setText("Informational");
        sucBtn->setText("Success");
        warnBtn->setText("Warning");
        errorBtn->setText("Error");

        infoBtn->setFixedWidth(120);
        sucBtn->setFixedWidth(120);
        warnBtn->setFixedWidth(120);
        errorBtn->setFixedWidth(120);

        connect(infoBtn, &FluPushButton::clicked, [=]() {
            FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info, window());
            sInfoBar->setFixedWidth(270);
            FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
        });

        connect(sucBtn, &FluPushButton::clicked, [=]() {
            FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Suc, window());
            sInfoBar->setFixedWidth(270);
            FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
        });

        connect(warnBtn, &FluPushButton::clicked, [=]() {
            FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Warn, window());
            sInfoBar->setFixedWidth(270);
            FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
        });

        connect(errorBtn, &FluPushButton::clicked, [=]() {
            FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Error, window());
            sInfoBar->setFixedWidth(270);
            FluInfoBarMgr::getInstance()->addInfoBar(window(), sInfoBar);
        });

        displayBox->getBodyLayout()->addWidget(infoBtn);
        displayBox->getBodyLayout()->addWidget(sucBtn);
        displayBox->getBodyLayout()->addWidget(warnBtn);
        displayBox->getBodyLayout()->addWidget(errorBtn);
        m_vScrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluInfoBarPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluInfoBarPage.qss", this);
        }
    }
};
