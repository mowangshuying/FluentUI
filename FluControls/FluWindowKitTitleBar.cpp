#include "FluWindowKitTitleBar.h"
#include "../FluUtils/FluUtils.h"

FluWindowKitTitleBar::FluWindowKitTitleBar(QWidget* parent /*= nullptr*/) : QFrame(parent)
{
    m_w = nullptr;
    init();
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluWindowKitTitleBar.qss", this);
}

void FluWindowKitTitleBar::init()
{
    m_hMainLayout = new QHBoxLayout;
    m_hMainLayout->setContentsMargins(QMargins());
    m_hMainLayout->setSpacing(0);

    for (int i = FluWKTitleBarItem::IconButton; i <= FluWKTitleBarItem::CloseButton; i++)
    {
        insertDefaultSpace(i);
    }

    setLayout(m_hMainLayout);
}

void FluWindowKitTitleBar::insertDefaultSpace(int nIndex)
{
    m_hMainLayout->insertSpacerItem(nIndex, new QSpacerItem(0, 0));
}

QWidget* FluWindowKitTitleBar::widgetAt(int nIndex) const
{
    return m_hMainLayout->itemAt(nIndex)->widget();
}

void FluWindowKitTitleBar::setWidgetAt(int nIndex, QWidget* widget)
{
    auto item = m_hMainLayout->takeAt(nIndex);
    auto orgWidget = item->widget();
    if (orgWidget)
    {
        orgWidget->deleteLater();
    }
    delete item;

    if (!widget)
    {
        insertDefaultSpace(nIndex);
    }
    else
    {
        m_hMainLayout->insertWidget(nIndex, widget);
    }
}

QWidget* FluWindowKitTitleBar::takeWidgetAt(int nIndex)
{
    auto item = m_hMainLayout->itemAt(nIndex);
    auto orgWidget = item->widget();
    if (orgWidget)
    {
        item = m_hMainLayout->takeAt(nIndex);
        delete item;
        insertDefaultSpace(nIndex);
    }

    return orgWidget;
}

QPushButton* FluWindowKitTitleBar::iconButton() const
{
    return static_cast<QPushButton*>(widgetAt(IconButton));
}

QLabel* FluWindowKitTitleBar::titleLabel() const
{
    return static_cast<QLabel*>(widgetAt(TitleLabel));
}

QPushButton* FluWindowKitTitleBar::minButton() const
{
    return static_cast<QPushButton*>(widgetAt(MinimumButton));
}

QPushButton* FluWindowKitTitleBar::maxButton() const
{
    return static_cast<QPushButton*>(widgetAt(MaximumButton));
}

QPushButton* FluWindowKitTitleBar::closeButton() const
{
    return static_cast<QPushButton*>(widgetAt(CloseButton));
}

void FluWindowKitTitleBar::setTitleLabel(QLabel* label)
{
    auto org = takeTitleLabel();
    if (org)
        org->deleteLater();

    if (!label)
        return;

    setWidgetAt(TitleLabel, label);
    if (m_autoTitle && m_w)
    {
        label->setText(m_w->windowTitle());
    }
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
}

void FluWindowKitTitleBar::setIconButton(QPushButton* btn)
{
    auto org = takeIconButton();
    if (org)
        org->deleteLater();
    if (!btn)
        return;
    setWidgetAt(IconButton, btn);
    if (m_autoIcon && m_w)
    {
        btn->setIcon(m_w->windowIcon());
    }

    btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
}

void FluWindowKitTitleBar::setMinButton(QPushButton* btn)
{
    auto org = takeMinButton();
    if (org)
    {
        org->deleteLater();
    }

    if (!btn)
    {
        return;
    }

    setWidgetAt(MinimumButton, btn);
    connect(btn, &QPushButton::clicked, this, &FluWindowKitTitleBar::minimizeRequested);
}

void FluWindowKitTitleBar::setMaxButton(QPushButton* btn)
{
    auto org = takeMaxButton();
    if (org)
    {
        org->deleteLater();
    }

    if (!btn)
        return;

    setWidgetAt(MaximumButton, btn);
    connect(btn, &QPushButton::clicked, this, &FluWindowKitTitleBar::maximizeRequested);
}

void FluWindowKitTitleBar::setCloseButton(QPushButton* btn)
{
    auto org = takeCloseButton();
    if (org)
    {
        org->deleteLater();
    }

    if (!btn)
        return;

    setWidgetAt(CloseButton, btn);
    connect(btn, &QPushButton::clicked, this, &FluWindowKitTitleBar::closeRequested);
}

QLabel* FluWindowKitTitleBar::takeTitleLabel()
{
    return static_cast<QLabel*>(takeWidgetAt(TitleLabel));
}

QPushButton* FluWindowKitTitleBar::takeIconButton()
{
    return static_cast<QPushButton*>(takeWidgetAt(IconButton));
}

QPushButton* FluWindowKitTitleBar::takeMinButton()
{
    return static_cast<QPushButton*>(takeWidgetAt(MinimumButton));
}

QPushButton* FluWindowKitTitleBar::takeMaxButton()
{
    return static_cast<QPushButton*>(takeWidgetAt(MaximumButton));
}

QPushButton* FluWindowKitTitleBar::takeCloseButton()
{
    return static_cast<QPushButton*>(takeWidgetAt(CloseButton));
}

QWidget* FluWindowKitTitleBar::hostWidget()
{
    return m_w;
}

void FluWindowKitTitleBar::setHostWidget(QWidget* w)
{
    // m_w = w;
    auto org = m_w;
    if (org)
    {
        org->removeEventFilter(this);
    }

    m_w = w;
    if (w)
    {
        w->installEventFilter(this);
    }
}

bool FluWindowKitTitleBar::iconFollowWindow()
{
    return m_autoIcon;
}

void FluWindowKitTitleBar::setIconFollowWindow(bool value)
{
    m_autoIcon = value;
}

void FluWindowKitTitleBar::titleChanged(const QString& text)
{
    Q_UNUSED(text);
}

void FluWindowKitTitleBar::iconChanged(const QIcon& icon)
{
    Q_UNUSED(icon);
}

bool FluWindowKitTitleBar::eventFilter(QObject* watched, QEvent* event)
{
    auto w = m_w;
    if (watched == w)
    {
        QAbstractButton* iconBtn = iconButton();
        QLabel* label = titleLabel();
        QAbstractButton* maxBtn = maxButton();
        switch (event->type())
        {
            case QEvent::WindowIconChange:
            {
                if (m_autoIcon && iconButton())
                {
                    iconBtn->setIcon(w->windowIcon());
                    iconChanged(w->windowIcon());
                }
                break;
            }
            case QEvent::WindowTitleChange:
            {
                if (m_autoIcon && label)
                {
                    label->setText(w->windowTitle());
                    titleChanged(w->windowTitle());
                }
                break;
            }
            case QEvent::WindowStateChange:
            {
                if (maxButton())
                {
                    maxButton()->setChecked(w->isMaximized());
                }
                break;
            }
            default:
                break;
        }
    }

    return QWidget::eventFilter(watched, event);
}
