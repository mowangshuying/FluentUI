#include "FluInfoBarPage.h"
#include "../controls/FluLineEdit.h"

FluInfoBarPage::FluInfoBarPage(QWidget* parent /*= nullptr*/) : FluAEmptyPage(parent)
{
    m_mainLayout->setAlignment(Qt::AlignTop);
    m_titleLabel->setText(tr("InfoBar"));
    m_infoLabel->setText(
        tr("Use an InfoBar control when a user should be informed of, acknowledge, or take action on a changed application state. By default the notification will remain in the content area until closed by the user but will not necessarily "
           "break user flow."));

    addPersistentInfoBar();
    addClosableInfoBar();
    addDynamicInfoBar();
    addBottomRightInfoBar();
    onThemeChanged();
}

void FluInfoBarPage::addPersistentInfoBar()
{
    FluDisplayBoxEx* displayBox = new FluDisplayBoxEx;
    displayBox->getBodyRightLayout()->setAlignment(Qt::AlignTop);
    displayBox->getBodyRightLayout()->setSpacing(8);

    displayBox->setTitle(tr("A persistent InfoBar with editable title, message, severity and close options."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(240);
    displayBox->getBodyContentLayout()->setAlignment(Qt::AlignVCenter);

    m_infoBar = new FluInfoBar(FluInfoBarSeverity::Informational);
    m_infoBar->setMaximumWidth(480);
    m_infoBar->setTitle(tr("Information"));
    m_infoBar->setMessage(tr("This is an informational message. You can edit the title, message and severity below."));
    m_infoBar->setIsClosable(true);
    displayBox->getBodyContentLayout()->addWidget(m_infoBar);
    // Open after parenting, otherwise show() pops a detached top-level window at startup.
    m_infoBar->setIsOpen(true);

    auto severityLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
    severityLabel->setText(tr("Severity"));
    displayBox->getBodyRightLayout()->addWidget(severityLabel, 0, Qt::AlignTop);

    auto severityComboBox = new FluComboBox;
    severityComboBox->addItem(tr("Informational"));
    severityComboBox->addItem(tr("Success"));
    severityComboBox->addItem(tr("Warning"));
    severityComboBox->addItem(tr("Error"));
    connect(severityComboBox, &FluComboBox::currentIndexChanged, this, [=](int index) {
        m_infoBar->setSeverity(static_cast<FluInfoBarSeverity>(index));
    });
    displayBox->getBodyRightLayout()->addWidget(severityComboBox, 0, Qt::AlignTop);

    auto isOpenCheckBox = new FluCheckBox(tr("Is Open"));
    isOpenCheckBox->setChecked(true);
    connect(isOpenCheckBox, &FluCheckBox::stateChanged, this, [=](int state) { m_infoBar->setIsOpen(state == Qt::Checked); });
    displayBox->getBodyRightLayout()->addWidget(isOpenCheckBox);

    auto isClosableCheckBox = new FluCheckBox(tr("Is Closable"));
    isClosableCheckBox->setChecked(true);
    connect(isClosableCheckBox, &FluCheckBox::stateChanged, this, [=](int state) { m_infoBar->setIsClosable(state == Qt::Checked); });
    displayBox->getBodyRightLayout()->addWidget(isClosableCheckBox);

    auto titleLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
    titleLabel->setText(tr("Title"));
    displayBox->getBodyRightLayout()->addWidget(titleLabel, 0, Qt::AlignTop);

    auto titleEdit = new FluLineEdit;
    titleEdit->setPlaceholderText(tr("Enter a title"));
    connect(titleEdit, &FluLineEdit::textChanged, this, [=](const QString& text) { m_infoBar->setTitle(text); });
    displayBox->getBodyRightLayout()->addWidget(titleEdit, 0, Qt::AlignTop);

    auto messageLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
    messageLabel->setText(tr("Message"));
    displayBox->getBodyRightLayout()->addWidget(messageLabel, 0, Qt::AlignTop);

    auto messageEdit = new FluLineEdit;
    messageEdit->setPlaceholderText(tr("Enter a message"));
    connect(messageEdit, &FluLineEdit::textChanged, this, [=](const QString& text) { m_infoBar->setMessage(text); });
    displayBox->getBodyRightLayout()->addWidget(messageEdit, 0, Qt::AlignTop);

    m_scrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluInfoBarPage::addClosableInfoBar()
{
    FluDisplayBoxEx* displayBox = new FluDisplayBoxEx;
    displayBox->getBodyRightLayout()->setAlignment(Qt::AlignTop);
    displayBox->getBodyRightLayout()->setSpacing(10);

    displayBox->setTitle(tr("A closable InfoBar with options to change its severity."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(120);

    FluInfoBar* infoBar = new FluInfoBar(FluInfoBarSeverity::Informational);
    infoBar->setTitle(tr("A closable InfoBar"));
    infoBar->setMessage(tr("Change its severity and close options. This message wraps to multiple lines."));
    infoBar->setFixedWidth(270);
    infoBar->setIsClosable(true);
    displayBox->getBodyContentLayout()->addWidget(infoBar);
    // Open after parenting, otherwise show() pops a detached top-level window at startup.
    infoBar->setIsOpen(true);

    auto isClosableCheckBox = new FluCheckBox(tr("Is Closable"));
    isClosableCheckBox->setChecked(true);
    displayBox->getBodyRightLayout()->addWidget(isClosableCheckBox);

    auto severityLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
    severityLabel->setText(tr("Severity"));
    displayBox->getBodyRightLayout()->addWidget(severityLabel, 0, Qt::AlignTop);

    auto comboBox = new FluComboBox;
    comboBox->addItem(tr("Informational"));
    comboBox->addItem(tr("Success"));
    comboBox->addItem(tr("Warning"));
    comboBox->addItem(tr("Error"));

    connect(comboBox, &FluComboBox::currentIndexChanged, this, [=](int index) {
        infoBar->setSeverity(static_cast<FluInfoBarSeverity>(index));
    });

    connect(isClosableCheckBox, &FluCheckBox::stateChanged, this, [=](int state) {
        infoBar->setIsClosable(state == Qt::Checked);
    });

    displayBox->getBodyRightLayout()->addWidget(comboBox, 0, Qt::AlignTop);
    m_scrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluInfoBarPage::addDynamicInfoBar()
{
    FluDisplayBox* displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A dynamic InfoBar."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode2.md");
    displayBox->setBodyWidgetFixedHeight(48);

    auto infoBtn = new FluPushButton;
    auto sucBtn = new FluPushButton;
    auto warnBtn = new FluPushButton;
    auto errorBtn = new FluPushButton;

    infoBtn->setText(tr("Informational"));
    sucBtn->setText(tr("Success"));
    warnBtn->setText(tr("Warning"));
    errorBtn->setText(tr("Error"));

    infoBtn->setFixedWidth(120);
    sucBtn->setFixedWidth(120);
    warnBtn->setFixedWidth(120);
    errorBtn->setFixedWidth(120);

    connect(infoBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Informational, tr("This is an informational message.")); });
    connect(sucBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Success, tr("This is an success message.")); });
    connect(warnBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Warning, tr("This is an warn message.")); });
    connect(errorBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Error, tr("This is an error message.")); });

    auto btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(8);
    btnLayout->addWidget(infoBtn);
    btnLayout->addWidget(sucBtn);
    btnLayout->addWidget(warnBtn);
    btnLayout->addWidget(errorBtn);
    displayBox->getBodyLayout()->addLayout(btnLayout);
    m_scrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluInfoBarPage::addBottomRightInfoBar()
{
    FluDisplayBox* displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A toast that appears at the bottom-right and stacks."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode2.md");
    displayBox->setBodyWidgetFixedHeight(48);

    auto infoBtn = new FluPushButton;
    auto sucBtn = new FluPushButton;
    auto warnBtn = new FluPushButton;
    auto errorBtn = new FluPushButton;

    infoBtn->setText(tr("Informational"));
    sucBtn->setText(tr("Success"));
    warnBtn->setText(tr("Warning"));
    errorBtn->setText(tr("Error"));

    infoBtn->setFixedWidth(120);
    sucBtn->setFixedWidth(120);
    warnBtn->setFixedWidth(120);
    errorBtn->setFixedWidth(120);

    connect(infoBtn, &FluPushButton::clicked, [=]() {
        FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Informational, tr("This is an informational message."), true, FluInfoBarPosition::BottomRight);
    });
    connect(sucBtn, &FluPushButton::clicked, [=]() {
        FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Success, tr("This is a success message."), true, FluInfoBarPosition::BottomRight);
    });
    connect(warnBtn, &FluPushButton::clicked, [=]() {
        FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Warning, tr("This is a warning message."), true, FluInfoBarPosition::BottomRight);
    });
    connect(errorBtn, &FluPushButton::clicked, [=]() {
        FluInfoBarMgr::showInfoBar(window(), FluInfoBarSeverity::Error, tr("This is an error message."), true, FluInfoBarPosition::BottomRight);
    });

    auto btnLayout = new QHBoxLayout;
    btnLayout->setSpacing(8);
    btnLayout->addWidget(infoBtn);
    btnLayout->addWidget(sucBtn);
    btnLayout->addWidget(warnBtn);
    btnLayout->addWidget(errorBtn);
    displayBox->getBodyLayout()->addLayout(btnLayout);
    m_scrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluInfoBarPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluInfoBarPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
