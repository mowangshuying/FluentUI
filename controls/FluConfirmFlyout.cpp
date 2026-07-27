#include "FluConfirmFlyout.h"

FluConfirmFlyout::FluConfirmFlyout(QWidget* target, FluFlyoutPosition position /*= FluFlyoutPosition::Top*/) : FluVFlyout(target, position)
{
    m_titleLabel = new FluLabel;
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setLabelStyle(FluLabelStyle::SubTitleTextBlockStyle);
    m_infoLabel = new FluLabel;
    m_infoLabel->setWordWrap(true);
    m_infoLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);

    m_shadowLayout->addWidget(m_titleLabel);
    m_shadowLayout->addWidget(m_infoLabel);

    m_buttonLayout = new QHBoxLayout;
    m_shadowLayout->addLayout(m_buttonLayout);

    m_okButton = new FluStyleButton;
    m_cancelButton = new FluPushButton;
    m_buttonLayout->addWidget(m_okButton);
    m_buttonLayout->addWidget(m_cancelButton);

    m_cancelButton->setFixedWidth(100);
    m_okButton->setFixedWidth(100);
    setFixedWidth(260);

    m_okButton->setText(tr("Ok"));
    m_cancelButton->setText(tr("Cancel"));

    connect(m_okButton, &FluStyleButton::clicked, [=]() { close(); });
    connect(m_cancelButton, &FluPushButton::clicked, [=]() { close(); });
    onThemeChanged();
}

void FluConfirmFlyout::setTitle(QString title)
{
    m_titleLabel->setText(title);
}

void FluConfirmFlyout::setInfo(QString info)
{
    m_infoLabel->setText(info);
}

void FluConfirmFlyout::setOk(QString ok)
{
    m_okButton->setText(ok);
}

void FluConfirmFlyout::setCancel(QString cancel)
{
    m_cancelButton->setText(cancel);
}

void FluConfirmFlyout::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluConfirmFlyout::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluConfirmFlyout.qss", this, FluThemeUtils::getUtils()->getTheme());
}
