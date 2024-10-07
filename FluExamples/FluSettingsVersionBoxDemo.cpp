#include "FluSettingsVersionBoxDemo.h"

FluSettingsVersionBoxDemo::FluSettingsVersionBoxDemo(QWidget* parent /*= nullptr*/) : FluTemplateDemo(parent)
{
    auto settingsVersionBox = new FluSettingsVersionBox(this);
    settingsVersionBox->setFixedWidth(600);

    settingsVersionBox->getTitleLabel()->setText("FluentUI Gallery(Cpp & Qt).");
    settingsVersionBox->getInfoLabel()->setText("©2023-2024 FluentUI For Qt & Cpp. All rights reserved.");
    settingsVersionBox->getVersionLabel()->setText("0.2.6");

    QIcon icon = QIcon("../res/Tiles/GalleryIcon.ico");
    settingsVersionBox->getIconLabel()->setPixmap(icon.pixmap(20, 20));
    settingsVersionBox->getIconLabel()->setFixedSize(40, 40);

    auto repoLabel = new FluLabel;
    repoLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    repoLabel->setText("To clone thepository");
    // repoLabel->setWordWrap(true);
    // settingsVersionBox->getWrap2Layout()->addWidget(repoLabel);

    settingsVersionBox->addWidget(repoLabel);

    auto cloneRepoBtn = new FluHyperLinkButton("");
    cloneRepoBtn->setFixedWidth(390);
    cloneRepoBtn->setText("git clone https://github.com/mowangshuying/CppQtFluentUi888");
    // settingsVersionBox->getWrap2Layout()->addWidget(cloneRepoBtn);

    settingsVersionBox->addWidget(cloneRepoBtn);

    // auto splitLine1 = new FluVSplitLine;
    // settingsVersionBox->getWrap2Layout()->addWidget(new FluVSplitLine);
    settingsVersionBox->addVSplitLine();

    auto issueLabel = new FluLabel;
    issueLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    issueLabel->setText("File a bug or Suggest a sample.");

    auto issueRef = new FluHyperLinkButton("");
    issueRef->setText("Get Start.");
    issueRef->setFixedWidth(120);

    // settingsVersionBox->getWrap2Layout()->addWidget(issueLabel);
    // settingsVersionBox->getWrap2Layout()->addWidget(issueRef);

    // settingsVersionBox->getWrap2Layout()->addWidget(new FluVSplitLine);

    settingsVersionBox->addWidget(issueLabel);
    settingsVersionBox->addWidget(issueRef);
    settingsVersionBox->addVSplitLine();

    auto dependAndRef = new FluLabel;
    dependAndRef->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);
    dependAndRef->setText("Dependencies & references");
    // settingsVersionBox->getWrap2Layout()->addWidget(dependAndRef);

    auto winUiGalleryRef = new FluHyperLinkButton("https://github.com/microsoft/WinUI-Gallery");
    winUiGalleryRef->setFixedWidth(160);
    winUiGalleryRef->setText("microsoft/WinUI-Gallery");

    auto framelesshelperRef = new FluHyperLinkButton("https://github.com/wangwenx190/framelesshelper");
    framelesshelperRef->setFixedWidth(200);
    framelesshelperRef->setText("wangwenx190/framelesshelper");

    auto qwindowkitRef = new FluHyperLinkButton("https://github.com/stdware/qwindowkit");
    qwindowkitRef->setText("stdware/qwindowkit");
    qwindowkitRef->setFixedWidth(140);

    // settingsVersionBox->getWrap2Layout()->addWidget(winUiGalleryRef);
    // settingsVersionBox->getWrap2Layout()->addWidget(framelesshelperRef);
    // settingsVersionBox->getWrap2Layout()->addWidget(qwindowkitRef);

    settingsVersionBox->addWidget(dependAndRef);
    settingsVersionBox->addWidget(winUiGalleryRef);
    settingsVersionBox->addWidget(framelesshelperRef);
    settingsVersionBox->addWidget(qwindowkitRef);

    settingsVersionBox->move(100, 100);
}
