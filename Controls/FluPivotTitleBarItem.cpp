#include "FluPivotTitleBarItem.h"

FluPivotTitleBarItem::FluPivotTitleBarItem(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    m_mainLayout = new QVBoxLayout;
    setLayout(m_mainLayout);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);

    m_textLabel = new QLabel;
    m_textLabel->setWordWrap(true);
    m_textLabel->setObjectName("textLabel");
    m_mainLayout->addWidget(m_textLabel);
    m_mainLayout->addWidget(m_textLabel, 1);

    m_indicatorLabel = new QLabel;
    m_indicatorLabel->setObjectName("indicatorLabel");
    m_mainLayout->addWidget(m_indicatorLabel);

    m_indicatorLabel->setFixedHeight(4);
    setSelected(false);
    setFixedHeight(45);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { onThemeChanged(); });
    adjustItemSize();
}

void FluPivotTitleBarItem::setSelected(bool isSelected)
{
    setProperty("selected", isSelected);
    m_textLabel->setProperty("selected", isSelected);
    m_indicatorLabel->setProperty("selected", isSelected);

    m_textLabel->style()->polish(m_textLabel);
    m_indicatorLabel->style()->polish(m_indicatorLabel);
    style()->polish(this);
}

void FluPivotTitleBarItem::setKey(QString key)
{
    m_key = key;
    m_textLabel->setText(key);
    adjustItemSize();
}

QString FluPivotTitleBarItem::getKey()
{
    return m_key;
}

void FluPivotTitleBarItem::adjustItemSize()
{
    m_textLabel->show();
    int labelWidth = m_textLabel->sizeHint().width();
    m_textLabel->setFixedWidth(labelWidth);
    setFixedWidth(labelWidth + 10);
}

void FluPivotTitleBarItem::onThemeChanged()
{
    FluStyleSheetUtils::setQssByFileName("FluPivotTitleBarItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
