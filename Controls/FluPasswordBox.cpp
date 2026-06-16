#include "FluPasswordBox.h"

FluPasswordBox::FluPasswordBox(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hLayout = new QHBoxLayout(this);
    setLayout(m_hLayout);
    m_hLayout->setContentsMargins(1, 0, 1, 0);
    m_hLayout->setSpacing(0);
    m_hLayout->setAlignment(Qt::AlignHCenter);

    m_edit = new QLineEdit(this);
    m_btn = new QPushButton(this);
    m_btn->setFixedSize(30, 20);
    m_btn->setIconSize(QSize(18, 18));
    m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye));

    //  m_edit->setFixedWidth(120);
    m_edit->setFixedHeight(30);

    m_hLayout->addWidget(m_edit, 1);
    m_hLayout->addWidget(m_btn);
    m_hLayout->addSpacing(4);

    // setFixedWidth(155);
    setFixedHeight(32);

    m_edit->installEventFilter(this);
    m_edit->setFocusPolicy(Qt::ClickFocus);

    m_btn->installEventFilter(this);

    m_edit->setEchoMode(QLineEdit::Password);

    onThemeChanged();
}

void FluPasswordBox::setMaskC(unsigned maskC)
{
    m_edit->setProperty("maskC", maskC);
}

bool FluPasswordBox::eventFilter(QObject* watched, QEvent* event)
{
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

    if (watched == m_btn)
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

    FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
}

void FluPasswordBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye, FluTheme::Light));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluPasswordBox.qss", this);
    }
    else
    {
        m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::RedEye, FluTheme::Dark));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluPasswordBox.qss", this);
    }

    FluStyleSheetUitls::setQssByFileName("FluPasswordBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
