#include "FluAutoSuggestBox.h"

FluAutoSuggestBox::FluAutoSuggestBox(QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->setContentsMargins(1, 0, 1, 0);
    m_hMainLayout->setSpacing(0);
    m_hMainLayout->setAlignment(Qt::AlignHCenter);

    m_lineEdit = new QLineEdit;

    m_lineEdit->setFixedHeight(30);
    m_lineEdit->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    m_hMainLayout->addWidget(m_lineEdit);
    m_hMainLayout->addSpacing(4);

    setFixedHeight(32);

    m_lineEdit->installEventFilter(this);

    m_completerMenu = new FluMenu;
    m_completerMenu->installEventFilter(this);

    connect(m_lineEdit, &QLineEdit::textEdited, [=](QString text) {
        m_completerMenu->clear();
        m_completerMenu->hide();

        std::vector<QString> keys;
        for (auto key : m_keys)
        {
            if (key.contains(text) && !text.isEmpty())
            {
                keys.push_back(key);
            }
        }

        if (keys.empty())
        {
            return;
        }

        for (auto key : keys)
        {
            m_completerMenu->addAction(new FluAction(key));
        }

        // show menu;
        QPoint leftBottomPos = rect().bottomLeft();
        leftBottomPos = mapToGlobal(leftBottomPos);
        leftBottomPos.setY(leftBottomPos.y() + 3);
        m_completerMenu->setFixedWidth(width());
        m_completerMenu->exec(leftBottomPos);
    });

    connect(m_completerMenu, &FluMenu::triggered, [=](QAction* action) {
        m_lineEdit->setText(action->text());
        emit currentTextChanged(action->text());
        int nIndex = 0;
        for (auto tmpAct : m_completerMenu->actions())
        {
            if (tmpAct == action)
            {
                break;
            }

            nIndex++;
        }
        emit currentIndexChanged(nIndex);
    });

    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAutoSuggestBox.qss", this);
}

void FluAutoSuggestBox::setKeys(std::vector<QString> keys)
{
    m_keys = keys;
}

QString FluAutoSuggestBox::getText()
{
    return m_lineEdit->text();
}

void FluAutoSuggestBox::setText(QString text)
{
    m_lineEdit->setText(text);
}

void FluAutoSuggestBox::setPlaceholderText(QString text)
{
    m_lineEdit->setPlaceholderText(text);
}

QString FluAutoSuggestBox::getPlaceholderText()
{
    return m_lineEdit->placeholderText();
}

bool FluAutoSuggestBox::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_lineEdit)
    {
        if (event->type() == QEvent::FocusIn)
        {
            setProperty("isFocused", true);
            style()->polish(this);
        }
        else if (event->type() == QEvent::FocusOut)
        {
            setProperty("isFocused", false);
            style()->polish(this);
        }
    }
    else if (watched == m_completerMenu)
    {
        if (event->type() == QEvent::KeyPress)
        {
            m_lineEdit->event(event);
        }
    }

    return QWidget::eventFilter(watched, event);
}

void FluAutoSuggestBox::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (!property("isFocused").toBool())
        return;

    FluStyleSheetUitls::drawBottomLineIndicator(this, &painter);
}

void FluAutoSuggestBox::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAutoSuggestBox.qss", this);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAutoSuggestBox.qss", this);
    }
}
