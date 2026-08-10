#include "FluInfoBar.h"
#include <QStyleOption>
#include <QEasingCurve>
#include <QTimer>

FluInfoBar::FluInfoBar(FluInfoBarSeverity severity /*= FluInfoBarSeverity::Informational*/, QWidget* parent /*= nullptr*/)
    : FluWidget(parent), m_severity(severity), m_isOpen(false), m_isClosable(true), m_opacity(1.0), m_disappearDuration(-1), m_isDisappearing(false)
{
    setMinimumWidth(320);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(12, 12, 12, 12);
    m_mainLayout->setSpacing(8);
    setLayout(m_mainLayout);

    m_iconLabel = new QLabel;
    m_iconLabel->setObjectName("iconLabel");
    m_iconLabel->setFixedSize(24, 24);
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(m_iconLabel, 0, Qt::AlignVCenter);

    QVBoxLayout* textLayout = new QVBoxLayout;
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(2);

    m_titleLabel = new QLabel;
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setTextFormat(Qt::PlainText);
    m_titleLabel->setWordWrap(false);
    QFont titleFont = m_titleLabel->font();
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    textLayout->addWidget(m_titleLabel);

    m_messageLabel = new QLabel;
    m_messageLabel->setObjectName("messageLabel");
    m_messageLabel->setWordWrap(true);
    textLayout->addWidget(m_messageLabel);

    m_mainLayout->addLayout(textLayout, 1);
    m_mainLayout->setAlignment(textLayout, Qt::AlignVCenter);

    m_closeBtn = new QPushButton;
    m_closeBtn->setObjectName("closeBtn");
    m_closeBtn->setFixedSize(28, 28);
    m_closeBtn->setIconSize(QSize(14, 14));
    m_closeBtn->setFocusPolicy(Qt::NoFocus);
    m_closeBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    m_mainLayout->addWidget(m_closeBtn, 0, Qt::AlignVCenter);

    connect(m_closeBtn, &QPushButton::clicked, this, [this]() {
        emit closeRequested();
        setIsOpen(false);
    });

    m_fadeAnim = new QPropertyAnimation(this, "opacity", this);
    connect(m_fadeAnim, &QPropertyAnimation::finished, this, [this]() {
        if (m_opacity <= 0.0)
        {
            hide();
            // In toast mode, the auto-disappear fade-out completing means the
            // toast should be removed by the manager.
            if (m_isDisappearing)
            {
                m_isDisappearing = false;
                emit closeRequested();
            }
        }
    });

    updateTitleVisibility();
    updateSeverityVisuals();
    onThemeChanged();
}

FluInfoBarSeverity FluInfoBar::severity() const
{
    return m_severity;
}

void FluInfoBar::setSeverity(FluInfoBarSeverity severity)
{
    if (m_severity == severity)
        return;

    m_severity = severity;
    updateSeverityVisuals();
    update();
}

QString FluInfoBar::title() const
{
    return m_title;
}

void FluInfoBar::setTitle(const QString& title)
{
    m_title = title;
    m_titleLabel->setText(title);
    updateTitleVisibility();
}

QString FluInfoBar::message() const
{
    return m_message;
}

void FluInfoBar::setMessage(const QString& message)
{
    m_message = message;
    m_messageLabel->setText(message);
}

bool FluInfoBar::isOpen() const
{
    return m_isOpen;
}

void FluInfoBar::setIsOpen(bool isOpen)
{
    if (m_isOpen == isOpen)
        return;

    m_isOpen = isOpen;
    emit isOpenChanged(m_isOpen);

    m_fadeAnim->stop();
    if (m_isOpen)
    {
        m_opacity = 0.0;
        show();
        update();
        m_fadeAnim->setDuration(200);
        m_fadeAnim->setEasingCurve(QEasingCurve::OutCubic);
        m_fadeAnim->setStartValue(0.0);
        m_fadeAnim->setEndValue(1.0);
        m_fadeAnim->start();
    }
    else
    {
        m_fadeAnim->setDuration(250);
        m_fadeAnim->setEasingCurve(QEasingCurve::InOutCubic);
        m_fadeAnim->setStartValue(m_opacity);
        m_fadeAnim->setEndValue(0.0);
        m_fadeAnim->start();
    }
}

bool FluInfoBar::isClosable() const
{
    return m_isClosable;
}

void FluInfoBar::setIsClosable(bool isClosable)
{
    if (m_isClosable == isClosable)
        return;

    m_isClosable = isClosable;
    m_closeBtn->setVisible(isClosable);
}

double FluInfoBar::getOpacity() const
{
    return m_opacity;
}

void FluInfoBar::setOpacity(double opacity)
{
    if (!qFuzzyCompare(m_opacity + 1, opacity + 1))
    {
        m_opacity = opacity;
        update();
    }
}

void FluInfoBar::setDisappearDuration(int disappearDuration)
{
    m_disappearDuration = disappearDuration;
}

void FluInfoBar::disappear()
{
    if (m_disappearDuration <= 0 || m_isDisappearing)
        return;

    m_isDisappearing = true;
    QTimer::singleShot(m_disappearDuration, this, [this]() {
        if (!m_isDisappearing)
            return;
        // Reuse the fade-out branch of setIsOpen(false); on completion the
        // fade animation handler emits closeRequested() so the manager removes it.
        setIsOpen(false);
    });
}

void FluInfoBar::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(m_opacity);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    // Draw the left severity accent bar, clipped to the rounded background.
    QPainterPath path;
    const qreal radius = 4.0;
    path.addRoundedRect(rect(), radius, radius);
    painter.setClipPath(path);

    painter.fillRect(QRectF(0, 0, 4, height()), severityColor());
}

void FluInfoBar::onThemeChanged()
{
    m_closeBtn->setIcon(FluIconUtils::getFluentIconPixmap(FluAwesomeType::ChromeClose, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUtils::setQssByFileName("FluInfoBar.qss", this, FluThemeUtils::getUtils()->getTheme());
    updateSeverityVisuals();
    update();
}

void FluInfoBar::updateTitleVisibility()
{
    m_titleLabel->setVisible(!m_title.isEmpty());
}

void FluInfoBar::updateSeverityVisuals()
{
    QString sevStr = severityString();

    setProperty("severity", sevStr);
    m_iconLabel->setProperty("severity", sevStr);
    m_titleLabel->setProperty("severity", sevStr);
    m_messageLabel->setProperty("severity", sevStr);
    m_closeBtn->setProperty("severity", sevStr);

    style()->polish(this);
    m_iconLabel->style()->polish(m_iconLabel);
    m_titleLabel->style()->polish(m_titleLabel);
    m_messageLabel->style()->polish(m_messageLabel);
    m_closeBtn->style()->polish(m_closeBtn);

    FluAwesomeType iconType;
    switch (m_severity)
    {
        case FluInfoBarSeverity::Informational:
            iconType = FluAwesomeType::Info;
            break;
        case FluInfoBarSeverity::Success:
            iconType = FluAwesomeType::StatusCircleCheckmark;
            break;
        case FluInfoBarSeverity::Warning:
            iconType = FluAwesomeType::Warning;
            break;
        case FluInfoBarSeverity::Error:
            iconType = FluAwesomeType::Error;
            break;
    }

    m_iconLabel->setPixmap(FluIconUtils::getFluentIconPixmap(iconType, severityIconColor(), 24, 24));
}

QColor FluInfoBar::severityColor() const
{
    bool dark = FluThemeUtils::isDarkTheme() || FluThemeUtils::isAtomOneDarkTheme();
    switch (m_severity)
    {
        case FluInfoBarSeverity::Informational:
            return dark ? QColor(118, 185, 237) : QColor(0, 90, 158);
        case FluInfoBarSeverity::Success:
            return dark ? QColor(108, 203, 95) : QColor(15, 123, 15);
        case FluInfoBarSeverity::Warning:
            return dark ? QColor(252, 225, 0) : QColor(157, 93, 0);
        case FluInfoBarSeverity::Error:
            return dark ? QColor(255, 153, 164) : QColor(196, 43, 28);
    }
    return dark ? QColor(118, 185, 237) : QColor(0, 90, 158);
}

QColor FluInfoBar::severityIconColor() const
{
    // Icon sits on a severity-colored circular/rounded background provided by QSS,
    // so a light glyph color reads on every theme.
    return QColor(239, 239, 239);
}

QString FluInfoBar::severityString() const
{
    switch (m_severity)
    {
        case FluInfoBarSeverity::Informational:
            return QStringLiteral("Informational");
        case FluInfoBarSeverity::Success:
            return QStringLiteral("Success");
        case FluInfoBarSeverity::Warning:
            return QStringLiteral("Warning");
        case FluInfoBarSeverity::Error:
            return QStringLiteral("Error");
    }
    return QStringLiteral("Informational");
}