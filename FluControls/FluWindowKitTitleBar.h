#pragma once

#include <QFrame>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>
#include <QEvent>

class FluWindowKitTitleBar : public QFrame
{
    Q_OBJECT
  public:
    enum FluWKTitleBarItem
    {
        IconButton,
        MenuWidget,
        TitleLabel,

        PinButton,

        MinimumButton,
        MaximumButton,
        CloseButton,
    };

  public:
    FluWindowKitTitleBar(QWidget* parent = nullptr);

    void init();

    void insertDefaultSpace(int nIndex);

    QWidget* widgetAt(int nIndex) const;

    void setWidgetAt(int nIndex, QWidget* widget);

    QWidget* takeWidgetAt(int nIndex);

    QPushButton* iconButton() const;

    QLabel* titleLabel() const;

    QPushButton* pinButton();

    QPushButton* minButton() const;

    QPushButton* maxButton() const;

    QPushButton* closeButton() const;

    void setTitleLabel(QLabel* label);

    void setIconButton(QPushButton* btn);

    void setPinButton(QPushButton* btn);

    void setMinButton(QPushButton* btn);

    void setMaxButton(QPushButton* btn);

    void setCloseButton(QPushButton* btn);

    QLabel* takeTitleLabel();

    QPushButton* takeIconButton();

    QPushButton* takePinButton();

    QPushButton* takeMinButton();

    QPushButton* takeMaxButton();

    QPushButton* takeCloseButton();

    QWidget* hostWidget();

    void setHostWidget(QWidget* w);

    bool iconFollowWindow();

    void setIconFollowWindow(bool value);

    void titleChanged(const QString& text);

    void iconChanged(const QIcon& icon);

    bool eventFilter(QObject* watched, QEvent* event);

  signals:
    void minimizeRequested();
    void maximizeRequested(bool max = false);
    void closeRequested();
    void pinRequested(bool pin = false);
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QWidget* m_w;

    bool m_autoTitle;
    bool m_autoIcon;
};
