#include "FluTabBarItem.h"

FluTabBarItem::FluTabBarItem(QWidget* parent /*= nullptr*/)
{
    m_mainLayout = new QHBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    m_iconButton = new QPushButton(this);
    m_textButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);

    m_iconButton->setFixedSize(16, 16);
    m_closeButton->setFixedSize(32, 24);

    m_iconButton->setIconSize(QSize(16, 16));
    m_closeButton->setIconSize(QSize(12, 12));
    m_textButton->setFixedHeight(30);
    m_textButton->setText("Document");

    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document, FluThemeUtils::getUtils()->getTheme()));
    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));

    m_iconButton->setObjectName("iconBtn");
    m_textButton->setObjectName("textBtn");
    m_closeButton->setObjectName("closeBtn");

    m_mainLayout->addWidget(m_iconButton);
    m_mainLayout->addWidget(m_textButton);
    m_mainLayout->addWidget(m_closeButton);

    m_mainLayout->addSpacing(5);

    // Track pressed state via icon/text buttons (close button has its own QSS)
    m_iconButton->installEventFilter(this);
    m_textButton->installEventFilter(this);

    setFixedHeight(35);
    connect(m_iconButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_textButton, &QPushButton::clicked, [=]() { emit clicked(); });
    connect(m_closeButton, &QPushButton::clicked, [=]() { emit clickedCloseButton(this); });
    onThemeChanged();
}

void FluTabBarItem::setSelected(bool isSel)
{
    m_isSel = isSel;
    setProperty("selected", isSel);
    m_closeButton->setProperty("selected", isSel);
    m_closeButton->style()->polish(m_closeButton);

    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
    if (isSel)
    {
        m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    }
    emit visualStateChanged();
}

bool FluTabBarItem::getSelected()
{
    return m_isSel;
}

void FluTabBarItem::setText(QString text)
{
    m_text = text;
    QFontMetrics metrics(m_textButton->font());
    int available = 240 - m_iconButton->width() - m_closeButton->width() - 5;
    if (metrics.boundingRect(text).width() > available)
        m_textButton->setText(metrics.elidedText(text, Qt::ElideRight, available));
    else
        m_textButton->setText(text);
    adjustWidgetSize();
}

QString FluTabBarItem::getText()
{
    return m_text;
}

int FluTabBarItem::getWidgetWidth()
{
    QFontMetrics metrics(m_textButton->font());
    QRect textRect = metrics.boundingRect(m_textButton->text());
    int textWidth = textRect.width();

    // adjust the whole widget width
    int totalWidth = m_iconButton->width() + textWidth + m_closeButton->width() + m_mainLayout->spacing() * 2 + 5;
    totalWidth = qMax(totalWidth, 100);
    totalWidth = qMin(totalWidth, 240);
    return totalWidth;
}

void FluTabBarItem::adjustWidgetSize()
{
    setFixedWidth(getWidgetWidth());
}

void FluTabBarItem::resizeEvent(QResizeEvent* event)
{
    emit sizeChanged();
}

void FluTabBarItem::enterEvent(QEnterEvent* event)
{
    m_isHover = true;
    emit visualStateChanged();
    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
}

void FluTabBarItem::leaveEvent(QEvent* event)
{
    bool changed = m_isHover || m_isPressed;
    m_isHover = false;
    m_isPressed = false;
    if (changed)
        emit visualStateChanged();

    if (m_isSel)
        return;

    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::None, FluThemeUtils::getUtils()->getTheme()));
}

void FluTabBarItem::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isPressed = true;
        emit visualStateChanged();
    }
}

void FluTabBarItem::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_isPressed)
    {
        m_isPressed = false;
        emit visualStateChanged();
    }
    emit clicked();
}

bool FluTabBarItem::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_iconButton || watched == m_textButton)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            auto* me = static_cast<QMouseEvent*>(event);
            if (me->button() == Qt::LeftButton)
            {
                m_isPressed = true;
                emit visualStateChanged();
            }
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            if (m_isPressed)
            {
                m_isPressed = false;
                emit visualStateChanged();
            }
        }
    }
    return false;
}

bool FluTabBarItem::getHovered() const
{
    return m_isHover;
}

bool FluTabBarItem::getPressed() const
{
    return m_isPressed;
}

int FluTabBarItem::tabWidth()
{
    return width();
}

void FluTabBarItem::setTabWidth(int w)
{
    setFixedWidth(w);
}

void FluTabBarItem::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluTabBarItem.qss", this, FluThemeUtils::getUtils()->getTheme());
    m_iconButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Document, FluThemeUtils::getUtils()->getTheme()));
    m_closeButton->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    // Re-apply selected property for QSS
    setProperty("selected", m_isSel);
    m_closeButton->setProperty("selected", m_isSel);
    m_closeButton->style()->polish(m_closeButton);
    emit visualStateChanged();
}
