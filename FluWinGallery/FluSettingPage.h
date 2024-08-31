#pragma once

#include "../FluControls/FluWidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"
#include "../FluControls/FluVScrollView.h"
#include "../FluControls/FluSettingsSelectBox.h"
#include "../FluControls/FluSettingsLabelBox.h"
#include "../FluControls/FluSettingsVersionBox.h"
#include "../FluControls/FluLabel.h"
#include "../FluControls/FluHyperLinkButton.h"

class FluSettingPage : public FluWidget
{
    Q_OBJECT
  public:
    FluSettingPage(QWidget* parent = nullptr) : FluWidget(parent)
    {
        m_mainLayout = new QVBoxLayout;
        m_mainLayout->setAlignment(Qt::AlignTop);
        setLayout(m_mainLayout);

        m_mainLayout->setContentsMargins(35, 35, 35, 35);

        m_titleLabel = new QLabel;
        m_titleLabel->setObjectName("titleLabel");
        m_titleLabel->setText("Settings");
        m_mainLayout->addWidget(m_titleLabel);

        m_vScrollView = new FluVScrollView;
        m_vScrollView->setObjectName("vScrollView");
        m_mainLayout->addWidget(m_vScrollView, 1);

        m_vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);

        m_appBehaviorLabel = new QLabel;
        m_appBehaviorLabel->setObjectName("appBehaviorLabel");
        m_appBehaviorLabel->setText("Appearance & behavior");
        m_vScrollView->getMainLayout()->addWidget(m_appBehaviorLabel);

        auto appThemeSelectBox = new FluSettingsSelectBox;
        appThemeSelectBox->setTitleInfo("App theme", "Select which app theme to display.");
        appThemeSelectBox->setIcon(FluAwesomeType::Color);

        appThemeSelectBox->getComboBox()->addItem("Light");
        appThemeSelectBox->getComboBox()->addItem("Dark");

        connect(appThemeSelectBox->getComboBox(), &FluComboBoxEx::currentIndexChanged, [=](int index) {
            if (index == 0)
                FluThemeUtils::getUtils()->setTheme(FluTheme::Light);
            else
                FluThemeUtils::getUtils()->setTheme(FluTheme::Dark);

            // LOG_DEBUG << FluThemeUtils::getUtils()->getTheme();
        });

        m_vScrollView->getMainLayout()->addWidget(appThemeSelectBox);

        auto navStyleSelectBox = new FluSettingsSelectBox;
        navStyleSelectBox->hideInfoLabel();
        navStyleSelectBox->setTitleInfo("Navigation style", "");
        navStyleSelectBox->setIcon(FluAwesomeType::HolePunchLandscapeLeft);
        navStyleSelectBox->getComboBox()->addItem("Left");
        navStyleSelectBox->getComboBox()->addItem("Top");
        m_vScrollView->getMainLayout()->addWidget(navStyleSelectBox);

        m_vScrollView->getMainLayout()->addSpacing(30);

        m_aboutLabel = new QLabel;
        m_aboutLabel->setObjectName("aboutLabel");
        m_aboutLabel->setText("About");
        m_vScrollView->getMainLayout()->addWidget(m_aboutLabel);

        // version;
        auto settingsVersionBox = new FluSettingsVersionBox;

        settingsVersionBox->getTitleLabel()->setText("FluentUI Gallery(Cpp & Qt).");
        settingsVersionBox->getInfoLabel()->setText("©2023-2024 FluentUI For Qt & Cpp. All rights reserved.");
        settingsVersionBox->getVersionLabel()->setText("0.3.0");

        QIcon icon = QIcon("../res/Tiles/GalleryIcon.ico");
        settingsVersionBox->getIconLabel()->setPixmap(icon.pixmap(20, 20));
        settingsVersionBox->getIconLabel()->setFixedSize(40, 40);

        auto repoLabel = new FluLabel;
        repoLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        repoLabel->setText("To clone thepository");

        auto cloneRepoBtn = new FluHyperLinkButton("");
        cloneRepoBtn->setText("git clone https://github.com/mowangshuying/CppQtFluentUi888");

        settingsVersionBox->addWidget(repoLabel);
        settingsVersionBox->addWidget(cloneRepoBtn);
        settingsVersionBox->addVSplitLine();

        auto issueLabel = new FluLabel;
        issueLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        issueLabel->setText("File a bug or Suggest a sample.");

        auto issueRef = new FluHyperLinkButton("");
        issueRef->setText("Get Start.");

        settingsVersionBox->addWidget(issueLabel);
        settingsVersionBox->addWidget(issueRef);
        settingsVersionBox->addVSplitLine();

        auto dependAndRef = new FluLabel;
        dependAndRef->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
        dependAndRef->setText("Dependencies & references");

        auto winUiGalleryRef = new FluHyperLinkButton("https://github.com/microsoft/WinUI-Gallery");
        winUiGalleryRef->setText("microsoft/WinUI-Gallery");

        auto framelesshelperRef = new FluHyperLinkButton("https://github.com/wangwenx190/framelesshelper");
        framelesshelperRef->setText("wangwenx190/framelesshelper");

        auto qwindowkitRef = new FluHyperLinkButton("https://github.com/stdware/qwindowkit");
        qwindowkitRef->setText("stdware/qwindowkit");

        settingsVersionBox->addWidget(dependAndRef);
        settingsVersionBox->addWidget(winUiGalleryRef);
        settingsVersionBox->addWidget(framelesshelperRef);
        settingsVersionBox->addWidget(qwindowkitRef);

        m_vScrollView->getMainLayout()->addWidget(settingsVersionBox);

        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingPage.qss", this);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluSettingPage.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluSettingPage.qss", this);
        }
    }

  protected:
    QVBoxLayout* m_mainLayout;

    QLabel* m_titleLabel;
    QLabel* m_appBehaviorLabel;
    QLabel* m_aboutLabel;
    FluVScrollView* m_vScrollView;
};
