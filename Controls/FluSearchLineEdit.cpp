#include "FluSearchLineEdit.h"

FluSearchLineEdit::FluSearchLineEdit(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_layout = new QHBoxLayout;
    setLayout(m_layout);
    m_layout->setContentsMargins(1, 0, 1, 0);
    m_layout->setSpacing(0);
    m_layout->setAlignment(Qt::AlignHCenter);

    m_edit = new QLineEdit(this);
    m_button = new QPushButton(this);
    m_button->setFixedSize(30, 20);
    m_button->setIconSize(QSize(18, 18));
    m_button->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search));

    m_edit->setFixedHeight(30);

    m_layout->addWidget(m_edit, 1);
    m_layout->addWidget(m_button);
    m_layout->addSpacing(4);

    // setFixedWidth(155);
    setFixedHeight(32);

    m_edit->installEventFilter(this);
    m_edit->setFocusPolicy(Qt::ClickFocus);

    connect(m_button, &QPushButton::clicked, [=]() { emit onSearchButtonClicked(); });

    onThemeChanged();
}

QString FluSearchLineEdit::getText()
{
    return m_edit->text();
}

void FluSearchLineEdit::setText(QString text)
{
    m_edit->setText(text);
}

void FluSearchLineEdit::setPlaceholderText(QString text)
{
    m_edit->setPlaceholderText(text);
}

QString FluSearchLineEdit::getPlaceholderText()
{
    return m_edit->placeholderText();
}

bool FluSearchLineEdit::eventFilter(QObject* watched, QEvent* event)
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
        else if (event->type() == QEvent::KeyRelease)
        {
            QKeyEvent* keyEvent = (QKeyEvent*)event;
            if (keyEvent->key() == Qt::Key_Return)
            {
                emit onSearchButtonClicked();
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void FluSearchLineEdit::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (!property("isFocused").toBool())
        return;

    FluStyleSheetUtils::drawBottomLineIndicator(this, &painter);
}

void FluSearchLineEdit::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_button->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluTheme::Light));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluSearchLineEdit.qss", this);
    }
    else
    {
        m_button->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluTheme::Dark));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluSearchLineEdit.qss", this);
    }
    FluStyleSheetUtils::setQssByFileName("FluSearchLineEdit.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluSearchLineEdit::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    m_edit->setEnabled(enabled);
    m_button->setEnabled(enabled);
}
