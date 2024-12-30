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

    m_completerMenu = new FluRoundMenu("", FluAwesomeType::None);
    m_completerMenu->setMaxVisibleItems(16);
    m_completerMenu->installEventFilter(this);

    connect(m_lineEdit, &QLineEdit::textEdited, [=](QString text) {

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
            m_completerMenu->hide();
            return;
        }

        std::vector<QString> actionkeys;
        for (auto action : m_completerMenu->actions())
        {
            actionkeys.push_back(action->text());
        }

        LOG_DEBUG << "Keys:";
        LOG_DEBUG << keys;
        LOG_DEBUG << "Action Keys:";
        LOG_DEBUG << actionkeys;

        bool bSame = true;
        if (actionkeys.size() == keys.size())
        {
            for (int i = 0; i < keys.size(); i++)
            {
                if (actionkeys[i] != keys[i])
                {
                    bSame = false;
                    break;
                }
            }
        }
        else
        {
            bSame = false;
        }

        if (!bSame || m_completerMenu->isHidden())
        {
            m_completerMenu->hide();
            m_completerMenu->clear();
            for (auto key : keys)
            {
                m_completerMenu->addAction(new FluAction(key));
            }

            // show menu;
            QPoint leftBottomPos = rect().bottomLeft();
            leftBottomPos = mapToGlobal(leftBottomPos);
            leftBottomPos.setY(leftBottomPos.y() + 2);
            m_completerMenu->getView()->setMinimumWidth(width());
            m_completerMenu->setMinimumWidth(width());
            m_completerMenu->exec(leftBottomPos);
        }
    });

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
        m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluTheme::Light));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluAutoSuggestBox.qss", this);
    }
    else if (FluThemeUtils::isDarkTheme())
    {
        m_btn->setIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Search, FluTheme::Dark));
        FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluAutoSuggestBox.qss", this);
    }
}
