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
    FluConfirmFlyout(QWidget* target, FluFlyoutPosition position = FluFlyoutPosition::Top);

    void setTitle(QString title);

    void setInfo(QString info);

    void setOk(QString ok);

    void setCancel(QString cancel);

    void paintEvent(QPaintEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    FluLabel* m_titleLabel;
    FluLabel* m_infoLabel;
    FluStyleButton* m_okBtn;
    FluPushButton* m_cancelBtn;

    QHBoxLayout* m_hBtnLayout;
};
