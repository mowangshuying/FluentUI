#include "FluPasswordBox.h"

FluPasswordBox::FluPasswordBox(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_layout = new QHBoxLayout(this);
    setLayout(m_layout);
    m_layout->setContentsMargins(1, 0, 1, 0);
    m_layout->setSpacing(0);
    m_layout->setAlignment(Qt::AlignHCenter);

    m_edit = new QLineEdit(this);
    m_button = new QPushButton(this);
    m_button->setFixedSize(30, 20);
    m_button->setIconSize(QSize(18, 18));
    m_button->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye));

    //  m_edit->setFixedWidth(120);
    m_edit->setFixedHeight(30);

    m_layout->addWidget(m_edit, 1);
    m_layout->addWidget(m_button);
    m_layout->addSpacing(4);

    // setFixedWidth(155);
    setFixedHeight(32);

    m_edit->installEventFilter(this);
    m_edit->setFocusPolicy(Qt::ClickFocus);

    m_button->installEventFilter(this);

    m_edit->setEchoMode(QLineEdit::Password);

    onThemeChanged();
}

void FluPasswordBox::setMaskC(unsigned maskC)
{
    m_edit->setProperty("maskC", maskC);
}

bool FluPasswordBox::eventFilter(QObject* watched, QEvent* event)
{
    if (!isEnabled())
        return QWidget::eventFilter(watched, event);

    if (watched == m_edit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            setProperty("isFocused", true);
            style()->polish(this);
            // LOG_DEBUG << "focuse in";
        }
        else if (event->type() == QEvent::FocusOut)
        {
            setProperty("isFocused", false);
            style()->polish(this);
            // LOG_DEBUG << "focuse out";
        }
    }

    if (watched == m_button)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            // LOG_DEBUG << "EchoMode Normal.";
            m_edit->setEchoMode(QLineEdit::Normal);
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            // LOG_DEBUG << "EchoMode Password.";
            m_edit->setEchoMode(QLineEdit::Password);
        }
    }

    return QWidget::eventFilter(watched, event);
}

void FluPasswordBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (!property("isFocused").toBool())
        return;

    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

void FluPasswordBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_button->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye, FluTheme::Light));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluPasswordBox.qss", this);
    }
    else
    {
        m_button->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye, FluTheme::Dark));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluPasswordBox.qss", this);
    }

    FluStyleSheetUtils::setQssByFileName("FluPasswordBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluPasswordBox::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    m_edit->setEnabled(enabled);
    m_button->setEnabled(enabled);
}
