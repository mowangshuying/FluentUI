#include "FluAction.h"

FluAction::FluAction(QObject* parent /*= nullptr*/) : QAction(parent)
{
    m_awesomeType = FluAwesomeType::None;
}

FluAction::FluAction(QString text, QObject* parent /*= nullptr*/) : QAction(text, parent)
{
    m_awesomeType = FluAwesomeType::None;
}

FluAction::FluAction(QIcon icon, QString text, QObject* parent /*= nullptr*/) : QAction(icon, text, parent)
{
    m_awesomeType = FluAwesomeType::None;
}

FluAction::FluAction(FluAwesomeType type, QString text, QObject* parent /*= nullptr*/) : QAction(FluIconUtils::getFluentIcon(type, FluThemeUtils::getUtils()->getTheme()), text, parent)
{
    m_awesomeType = type;
    if (m_awesomeType != FluAwesomeType::None)
        setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
}

FluAwesomeType FluAction::getAwesomeType()
{
    return m_awesomeType;
}

void FluAction::setAwesomeType(FluAwesomeType type)
{
    m_awesomeType = type;
    if (m_awesomeType != FluAwesomeType::None)
        setIcon(FluIconUtils::getFluentIcon(m_awesomeType, FluThemeUtils::getUtils()->getTheme()));
}

void FluAction::setListWidgetItem(QListWidgetItem* item)
{
    m_listWidgetItem = item;
}

QListWidgetItem* FluAction::getListWidgetItem()
{
    return m_listWidgetItem;
}

void FluAction::onThemeChanged()
{
}
