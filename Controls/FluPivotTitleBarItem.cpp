#include "FluPivotTitleBarItem.h"

FluPivotTitleBarItem::FluPivotTitleBarItem(QWidget* parent /*= nullptr*/) : QPushButton(parent)
{
    m_vMainLayout = new QVBoxLayout;
    setLayout(m_vMainLayout);
    m_vMainLayout->setContentsMargins(5, 5, 5, 5);

    m_textLabel = new QLabel;
    m_textLabel->setWordWrap(true);
    m_textLabel->setObjectName("textLabel");
    m_vMainLayout->addWidget(m_textLabel);
    m_vMainLayout->addWidget(m_textLabel, 1);

    m_indicatorLabel = new QLabel;
    m_indicatorLabel->setObjectName("indicatorLabel");
    m_vMainLayout->addWidget(m_indicatorLabel);

    m_indicatorLabel->setFixedHeight(4);
    setSelected(false);
    setFixedHeight(45);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { onThemeChanged(); });
    adjustItemSize();
}

void FluPivotTitleBarItem::setSelected(bool bSelected)
{
    setProperty("selected", bSelected);
    m_textLabel->setProperty("selected", bSelected);
    m_indicatorLabel->setProperty("selected", bSelected);

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
    int nLabelWidth = m_textLabel->sizeHint().width();
    m_textLabel->setFixedWidth(nLabelWidth);
    setFixedWidth(nLabelWidth + 10);
}

void FluPivotTitleBarItem::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluPivotTitleBarItem.qss", this, FluThemeUtils::getUtils()->getTheme());
}
