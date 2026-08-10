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
    onThemeChanged();
}

void FluInfoBarPage::addPersistentInfoBar()
{
    FluDisplayBoxEx* displayBox = new FluDisplayBoxEx;
    displayBox->getBodyRightLayout()->setAlignment(Qt::AlignTop);

    displayBox->setTitle(tr("A persistent InfoBar with editable title, message, severity and close options."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(180);
    displayBox->getBodyContentLayout()->setAlignment(Qt::AlignTop);

    m_infoBar = new FluInfoBar(FluInfoBarSeverity::Informational);
    m_infoBar->setMaximumWidth(480);
    m_infoBar->setTitle(tr("Information"));
    m_infoBar->setMessage(tr("This is an informational message. You can edit the title, message and severity below."));
    m_infoBar->setIsOpen(true);
    m_infoBar->setIsClosable(true);
    displayBox->getBodyContentLayout()->addWidget(m_infoBar);

    auto severityLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
    severityLabel->setText(tr("Severity"));
    displayBox->getBodyRightLayout()->addWidget(severityLabel, 0, Qt::AlignTop);

    auto severityComboBox = new FluComboBoxEx;
    severityComboBox->addItem(tr("Informational"));
    severityComboBox->addItem(tr("Success"));
    severityComboBox->addItem(tr("Warning"));
    severityComboBox->addItem(tr("Error"));
    connect(severityComboBox, &FluComboBoxEx::currentIndexChanged, this, [=](int index) {
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

    displayBox->setTitle(tr("A closable InfoBar with options to change its severity."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode1.md");
    displayBox->setBodyWidgetFixedHeight(120);

    FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info);
    // sInfoBar->hide();
    sInfoBar->setFixedWidth(270);
    displayBox->getBodyContentLayout()->addWidget(sInfoBar);

    auto isClosableCheckBox = new FluCheckBox(tr("Is Closable"));
    displayBox->getBodyRightLayout()->addWidget(isClosableCheckBox);

    auto severityLabel = new FluLabel(FluLabelStyle::BodyTextBlockStyle);
    severityLabel->setText(tr("Severity"));
    displayBox->getBodyRightLayout()->addWidget(severityLabel, 0, Qt::AlignTop);

    auto comboBox = new FluComboBoxEx;
    comboBox->addItem(tr("Informational"));
    comboBox->addItem(tr("Success"));
    comboBox->addItem(tr("Warning"));
    comboBox->addItem(tr("Error"));

    connect(comboBox, &FluComboBoxEx::currentIndexChanged, [=](int index) mutable {
        //   LOG_DEBUG << displayBox->getBodyContentLayout()->count();
        if (!displayBox->getBodyContentLayout()->isEmpty())
        {
            displayBox->getBodyContentLayout()->removeWidget(sInfoBar);
            sInfoBar->deleteLater();
            // delete sInfoBar;
            // sInfoBar = nullptr;
            // sInfoBar = nullptr;
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
        sInfoBar->getCloseButton()->hide();
        if (isClosableCheckBox->isChecked())
        {
            sInfoBar->getCloseButton()->show();
        }

        displayBox->getBodyContentLayout()->addWidget(sInfoBar);
    });

    connect(isClosableCheckBox, &FluCheckBox::stateChanged, this, [=](int state) {
        auto sInfoBar = (FluShortInfoBar*)(displayBox->getBodyContentLayout()->itemAt(0)->widget());
        if (state == Qt::Checked)
            sInfoBar->getCloseButton()->show();
        else
            sInfoBar->getCloseButton()->hide();
    });

    displayBox->getBodyRightLayout()->addWidget(comboBox, 0, Qt::AlignTop);
    m_scrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluInfoBarPage::addDynamicInfoBar()
{
    FluDisplayBox* displayBox = new FluDisplayBox;
    displayBox->setTitle(tr("A dynamic InfoBar."));
    displayBox->getCodeExpander()->setCodeByPath("../code/InfoBarPageCode2.md");
    displayBox->setBodyWidgetFixedHeight(256);

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

    connect(infoBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Info, tr("This is an informational message.")); });
    connect(sucBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Suc, tr("This is an success message.")); });
    connect(warnBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Warn, tr("This is an warn message.")); });
    connect(errorBtn, &FluPushButton::clicked, [=]() { FluInfoBarMgr::showInfoBar(window(), FluShortInfoBarType::Error, tr("This is an error message.")); });

    displayBox->getBodyLayout()->addWidget(infoBtn);
    displayBox->getBodyLayout()->addWidget(sucBtn);
    displayBox->getBodyLayout()->addWidget(warnBtn);
    displayBox->getBodyLayout()->addWidget(errorBtn);
    m_scrollView->getMainLayout()->addWidget(displayBox, 0, Qt::AlignTop);
}

void FluInfoBarPage::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluInfoBarPage.qss", this, FluThemeUtils::getUtils()->getTheme());
}
