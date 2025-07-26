#include "FluSettingPage.h"

FluSettingPage::FluSettingPage(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setAlignment(Qt::AlignTop);
    setLayout(m_mainLayout);

    m_mainLayout->setContentsMargins(35, 35, 35, 35);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setText(tr("Settings"));
    m_mainLayout->addWidget(m_titleLabel);

    m_vScrollView = new FluVScrollView;
    m_vScrollView->setObjectName("vScrollView");
    m_mainLayout->addWidget(m_vScrollView, 1);

    m_vScrollView->getMainLayout()->setAlignment(Qt::AlignTop);

    m_appBehaviorLabel = new QLabel;
    m_appBehaviorLabel->setObjectName("appBehaviorLabel");
    m_appBehaviorLabel->setText(tr("Appearance & behavior"));
    m_vScrollView->getMainLayout()->addWidget(m_appBehaviorLabel);

    m_appThemeSelectBox = new FluSettingsSelectBox;
    m_appThemeSelectBox->setTitleInfo(tr("App theme"), tr("Select which app theme to display."));
    m_appThemeSelectBox->setIcon(FluAwesomeType::Color);

    m_appThemeSelectBox->getComboBox()->addItem(tr("Light"));
    m_appThemeSelectBox->getComboBox()->addItem(tr("Dark"));
    m_appThemeSelectBox->getComboBox()->addItem(tr("AtomOneDark"));
    m_appThemeSelectBox->getComboBox()->setIndex((int)FluThemeUtils::getUtils()->getTheme());
    connect(m_appThemeSelectBox->getComboBox(), &FluComboBoxEx::currentIndexChanged, [=](int index) {
        if (index == (int)FluThemeUtils::getUtils()->getTheme())
            return;

        if (index == 0)
            FluThemeUtils::getUtils()->setTheme(FluTheme::Light);
        else if (index == 1)
            FluThemeUtils::getUtils()->setTheme(FluTheme::Dark);
        else
            FluThemeUtils::getUtils()->setTheme(FluTheme::AtomOneDark);
    });

    m_vScrollView->getMainLayout()->addWidget(m_appThemeSelectBox);

    auto navStyleSelectBox = new FluSettingsSelectBox;
    navStyleSelectBox->hideInfoLabel();
    navStyleSelectBox->setTitleInfo(tr("Navigation style"), tr(""));
    navStyleSelectBox->setIcon(FluAwesomeType::HolePunchLandscapeLeft);
    navStyleSelectBox->getComboBox()->addItem(tr("Left"));
    navStyleSelectBox->getComboBox()->addItem(tr("Top"));
    m_vScrollView->getMainLayout()->addWidget(navStyleSelectBox);

    auto languageSelectBox = new FluSettingsSelectBox;
    languageSelectBox->setTitleInfo(tr("Language"), tr("Select which language to display."));
    languageSelectBox->setIcon(FluAwesomeType::Globe);
    languageSelectBox->getComboBox()->addItem(tr("en-US"));
    languageSelectBox->getComboBox()->addItem(tr("zh-CN"));

    if (FluConfigUtils::getUtils()->getLanguage() == "en-US")
        languageSelectBox->getComboBox()->setIndex(0);
    else if (FluConfigUtils::getUtils()->getLanguage() == "zh-CN")
        languageSelectBox->getComboBox()->setIndex(1);

    connect(languageSelectBox->getComboBox(), &FluComboBoxEx::currentIndexChanged, [=](int index) {
        if (index == 0)
            FluConfigUtils::getUtils()->setLanguage("en-US");
        else
            FluConfigUtils::getUtils()->setLanguage("zh-CN");
    });

    m_vScrollView->getMainLayout()->addWidget(languageSelectBox);

    m_vScrollView->getMainLayout()->addSpacing(30);

    m_aboutLabel = new QLabel;
    m_aboutLabel->setObjectName("aboutLabel");
    m_aboutLabel->setText(tr("About"));
    m_vScrollView->getMainLayout()->addWidget(m_aboutLabel);

    // version;
    auto settingsVersionBox = new FluSettingsVersionBox;

    settingsVersionBox->getTitleLabel()->setText(tr("FluentUI Gallery(Cpp & Qt)."));
    settingsVersionBox->getInfoLabel()->setText(tr("@2023-2025 FluentUI For Qt & Cpp. All rights reserved."));
    settingsVersionBox->getVersionLabel()->setText(tr("1.0.6"));

#ifndef USE_QRC
    QIcon icon = QIcon("../res/Tiles/GalleryIcon.ico");
#else
    QIcon icon = QIcon(":/res/Tiles/GalleryIcon.ico");
#endif

    settingsVersionBox->getIconLabel()->setPixmap(icon.pixmap(20, 20));
    settingsVersionBox->getIconLabel()->setFixedSize(40, 40);

    auto repoLabel = new FluLabel;
    repoLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    repoLabel->setText(tr("To clone thepository"));

    auto cloneRepoBtn = new FluHyperLinkButton("");
    cloneRepoBtn->setText("git clone https://github.com/mowangshuying/FluentUI");

    settingsVersionBox->addWidget(repoLabel);
    settingsVersionBox->addWidget(cloneRepoBtn);
    settingsVersionBox->addVSplitLine();

    auto issueLabel = new FluLabel;
    issueLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    issueLabel->setText(tr("File a bug or Suggest a sample."));

    auto issueRef = new FluHyperLinkButton("");
    issueRef->setText(tr("Get Start."));

    settingsVersionBox->addWidget(issueLabel);
    settingsVersionBox->addWidget(issueRef);
    settingsVersionBox->addVSplitLine();

    auto dependAndRef = new FluLabel;
    dependAndRef->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    dependAndRef->setText(tr("Dependencies & references"));

    auto winUiGalleryRef = new FluHyperLinkButton("https://github.com/microsoft/WinUI-Gallery");
    winUiGalleryRef->setText(tr("Microsoft/WinUI-Gallery"));

    auto framelesshelperRef = new FluHyperLinkButton("https://github.com/wangwenx190/framelesshelper");
    framelesshelperRef->setText(tr("wangwenx190/framelesshelper"));

    auto qwindowkitRef = new FluHyperLinkButton("https://github.com/stdware/qwindowkit");
    qwindowkitRef->setText(tr("stdware/qwindowkit"));

    settingsVersionBox->addWidget(dependAndRef);
    settingsVersionBox->addWidget(winUiGalleryRef);
    settingsVersionBox->addWidget(framelesshelperRef);
    settingsVersionBox->addWidget(qwindowkitRef);

    m_vScrollView->getMainLayout()->addWidget(settingsVersionBox, 0, Qt::AlignTop);

    onThemeChanged();
}

void FluSettingPage::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluSettingPage::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluSettingPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
