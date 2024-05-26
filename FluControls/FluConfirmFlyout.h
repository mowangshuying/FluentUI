#pragma once

#include "FluLabel.h"
#include "FluVFlyout.h"
#include "../FluUtils/FluUtils.h"
#include "FluStyleButton.h"
#include "FluPushButton.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

class FluConfirmFlyout : public FluVFlyout
{
    Q_OBJECT
  public:
    FluConfirmFlyout(QWidget* target, FluFlyoutPosition position = FluFlyoutPosition::Top) : FluVFlyout(target, position)
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

        m_okBtn->setText("Ok");
        m_cancelBtn->setText("Cancel");

        connect(m_okBtn, &FluStyleButton::clicked, [=]() { close(); });

        connect(m_cancelBtn, &FluPushButton::clicked, [=]() { close(); });

        FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluConfirmFlyout.qss", this);
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Dark)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluConfirmFlyout.qss", this);
        }
    }

    void setTitle(QString title)
    {
        m_titleLabel->setText(title);
    }

    void setInfo(QString info)
    {
        m_infoLabel->setText(info);
    }

    void setOk(QString ok)
    {
        m_okBtn->setText(ok);
    }

    void setCancel(QString cancel)
    {
        m_cancelBtn->setText(cancel);
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
        if (FluThemeUtils::getUtils()->getTheme() == FluTheme::Light)
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/light/FluConfirmFlyout.qss", this);
        }
        else
        {
            FluStyleSheetUitls::setQssByFileName(":/StyleSheet/dark/FluConfirmFlyout.qss", this);
        }
    }

  protected:
    FluLabel* m_titleLabel;
    FluLabel* m_infoLabel;
    FluStyleButton* m_okBtn;
    FluPushButton* m_cancelBtn;

    QHBoxLayout* m_hBtnLayout;
};
