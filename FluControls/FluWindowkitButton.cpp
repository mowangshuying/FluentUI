#include "FluWindowkitButton.h"
#include <QMouseEvent>
#include "../FluUtils/FluUtils.h"

FluWindowkitButton::FluWindowkitButton(QWidget *parent /*= nullptr*/) : QPushButton(parent)
{
    // FluStyleSheetUitls::setQssByFileName("FluWindowkitButton.qss", this, FluThemeUtils::getUtils()->getTheme());
}

void FluWindowkitButton::init()
{
}

QIcon FluWindowkitButton::iconNormal() const
{
    return m_iconNormal;
}

void FluWindowkitButton::setIconNormal(const QIcon &icon)
{
    m_iconNormal = icon;
    reloadIcon();
}

QIcon FluWindowkitButton::iconChecked() const
{
    return m_iconChecked;
}

void FluWindowkitButton::setIconChecked(const QIcon &icon)
{
    m_iconChecked = icon;
    reloadIcon();
}

QIcon FluWindowkitButton::iconDisabled() const
{
    return m_iconDisabled;
}

void FluWindowkitButton::setIconDisabled(const QIcon &icon)
{
    m_iconDisabled = icon;
    reloadIcon();
}

void FluWindowkitButton::reloadIcon()
{
    if (isEnabled() && !iconDisabled().isNull())
    {
        setIcon(iconDisabled());
        return;
    }

    if (isChecked() && !iconChecked().isNull())
    {
        setIcon(iconChecked());
        return;
    }

    if (!iconNormal().isNull())
        setIcon(iconNormal());
}

void FluWindowkitButton::checkStateSet()
{
    reloadIcon();
}

void FluWindowkitButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit doubleClicked();
    }
}
