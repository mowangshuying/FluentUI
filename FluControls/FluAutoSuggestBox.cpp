#include "FluAutoSuggestBox.h"

FluAutoSuggestBox::FluAutoSuggestBox(bool bSearch /*=false*/, QWidget* parent /*= nullptr*/) : FluWidget(parent)
{
    m_hMainLayout = new QHBoxLayout;
    setLayout(m_hMainLayout);
    m_hMainLayout->setContentsMargins(1, 0, 1, 0);
    m_hMainLayout->setSpacing(0);
    m_hMainLayout->setAlignment(Qt::AlignHCenter);

    m_lineEdit = new QLineEdit;
    m_btn = new QPushButton;
    m_btn->setFixedSize(30, 20);
    m_btn->setIconSize(QSize(18, 18));
    m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search));

    m_lineEdit->setFixedHeight(30);
    m_lineEdit->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    m_hMainLayout->addWidget(m_lineEdit, 1);
    m_hMainLayout->addWidget(m_btn);
    m_hMainLayout->addSpacing(4);

    setFixedHeight(32);

    m_lineEdit->installEventFilter(this);

    m_completerMenu = new FluCompleterMenu(this);
    m_completerMenu->setMaxVisibleItems(5);
    m_completerMenu->installEventFilter(this);

    connect(m_lineEdit, &QLineEdit::textEdited, this, &FluAutoSuggestBox::onTextEdited);

    connect(m_completerMenu, &FluRoundMenu::triggered, [=](QAction* action) {
        m_lineEdit->setText(action->text());
        int nIndex = 0;
        for (auto tmpAct : m_completerMenu->actions())
        {
            if (tmpAct == action)
            {
                break;
            }

            nIndex++;
        }
        emit currentTextChanged(action->text());
        emit currentIndexChanged(nIndex);
    });

    setSearch(m_bSearch);
    connect(m_btn, &QPushButton::clicked, [=]() { emit searchBtnClicked(); });
    onThemeChanged();
}

void FluAutoSuggestBox::setKeys(std::vector<QString> keys)
{
    m_keys.clear();
    addKeys(keys);
}

void FluAutoSuggestBox::setKey(QString key)
{
    m_keys.clear();
    addKey(key);
}

void FluAutoSuggestBox::addKeys(std::vector<QString> keys)
{
    for (auto iter = keys.begin(); iter != keys.end(); iter++)
        addKey(*iter);
}

void FluAutoSuggestBox::addKey(QString key)
{
    if (std::find(m_keys.begin(), m_keys.end(), key) == m_keys.end())
    {
        m_keys.push_back(key);
    }
    std::sort(m_keys.begin(), m_keys.end());
}

void FluAutoSuggestBox::clearKeys()
{
    m_keys.clear();
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

void FluAutoSuggestBox::setSearch(bool bSearch)
{
    m_bSearch = bSearch;
    if (m_bSearch)
        m_btn->show();
    else
        m_btn->hide();
}

bool FluAutoSuggestBox::getSearch()
{
    return m_bSearch;
}

void FluAutoSuggestBox::hockEvent(QEvent* event)
{
    m_lineEdit->event(event);
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

void FluAutoSuggestBox::onTextEdited(QString text)
{
    std::vector<QString> keys;
    for (auto key : m_keys)
    {
        if (key.indexOf(text) == 0 && !text.isEmpty())
        {
            keys.push_back(key);
        }
    }

    if (keys.empty())
    {
        m_completerMenu->close();
        return;
    }

    std::vector<QString> actionkeys;
    for (auto action : m_completerMenu->actions())
    {
        actionkeys.push_back(action->text());
    }

    bool bSameKeys = true;
    if (actionkeys.size() == keys.size())
    {
        for (int i = 0; i < keys.size(); i++)
        {
            if (actionkeys[i] != keys[i])
            {
                bSameKeys = false;
                break;
            }
        }
    }
    else
    {
        bSameKeys = false;
    }

    if (!bSameKeys || m_completerMenu->isHidden())
    {
        QPoint pos = rect().bottomLeft();
        pos = mapToGlobal(pos);
        pos.setY(pos.y() - 2);

        m_completerMenu->updateActions(keys);
        m_completerMenu->popup(pos);
    }
}

void FluAutoSuggestBox::onThemeChanged()
{
    m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluThemeUtils::getUtils()->getTheme()));
    FluStyleSheetUitls::setQssByFileName("FluAutoSuggestBox.qss", this, FluThemeUtils::getUtils()->getTheme());
}
