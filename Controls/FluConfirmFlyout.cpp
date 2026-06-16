#include "FluConfirmFlyout.h"

FluConfirmFlyout::FluConfirmFlyout(QWidget* target, FluFlyoutPosition position /*= FluFlyoutPosition::Top*/) : FluVFlyout(target, position)
{
    m_titleLabel = new FluLabel;
    m_titleLabel->setWordWrap(true);
    m_titleLabel->setLabelStyle(FluLabelStyle::SubTitleTextBlockStyle);
    m_infoLabel = new FluLabel;
    m_infoLabel->setWordWrap(true);
    m_infoLabel->setLabelStyle(FluLabelStyle::BodyTextBlockStyle);

    m_vShadowLayout->addWidget(m_titleLabel);
    m_vShadowLayout->addWidget(m_infoLabel);

    m_hBtnLayout = new QHBoxLayout;
    m_vShadowLayout->addLayout(m_hBtnLayout);

    m_okBtn = new FluStyleButton;
    m_cancelBtn = new FluPushButton;
    m_hBtnLayout->addWidget(m_okBtn);
    m_hBtnLayout->addWidget(m_cancelBtn);

    m_cancelBtn->setFixedWidth(100);
    m_okBtn->setFixedWidth(100);
    setFixedWidth(260);

    m_okBtn->setText(tr("Ok"));
    m_cancelBtn->setText(tr("Cancel"));

    connect(m_okBtn, &FluStyleButton::clicked, [=]() { close(); });
    connect(m_cancelBtn, &FluPushButton::clicked, [=]() { close(); });
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
    m_okBtn->setText(ok);
}

void FluConfirmFlyout::setCancel(QString cancel)
{
    m_cancelBtn->setText(cancel);
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
    FluStyleSheetUitls::setQssByFileName("FluConfirmFlyout.qss", this, FluThemeUtils::getUtils()->getTheme());
}
