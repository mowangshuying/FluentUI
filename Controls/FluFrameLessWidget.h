#pragma once

#include <FramelessHelper/Widgets/FramelessWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
class QLabel;
class QShortcut;
QT_END_NAMESPACE

FRAMELESSHELPER_BEGIN_NAMESPACE
class StandardTitleBar;
FRAMELESSHELPER_END_NAMESPACE

class FluFrameLessWidget : public FRAMELESSHELPER_PREPEND_NAMESPACE(FramelessWidget)
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FluFrameLessWidget)

  public:
    explicit FluFrameLessWidget(QWidget *parent = nullptr);
    ~FluFrameLessWidget() override;

    virtual void waitReady();
    virtual void initialize();

    void changeEvent(QEvent *event);

  protected:
    void closeEvent(QCloseEvent *event) override;

    // private:
    // void initialize();

  public slots:
    void updateStyleSheet();

  protected:
    FRAMELESSHELPER_PREPEND_NAMESPACE(StandardTitleBar) *m_titleBar = nullptr;
    // QWidget *m_centerWidget;
    QVBoxLayout *m_vMainLayout;
    QHBoxLayout *m_contentLayout;
};
