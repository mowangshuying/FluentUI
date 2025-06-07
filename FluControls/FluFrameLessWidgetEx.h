#pragma once

#include <FramelessHelper/Widgets/FramelessWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "FluFrameLessTitleBar.h"

class FluFrameLessWidgetEx : public FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessWidget)
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FluFrameLessWidgetEx)

  public:
    explicit FluFrameLessWidgetEx(QWidget *parent = nullptr);
    ~FluFrameLessWidgetEx() override;

    virtual void waitReady();
    virtual void initialize();

  protected:
    void closeEvent(QCloseEvent *event) override;

  public slots:
    void updateStyleSheet();

  protected:
    FluFrameLessTitleBar *m_titleBar = nullptr;
    QVBoxLayout *m_vMainLayout;
    QHBoxLayout *m_contentLayout;
};
