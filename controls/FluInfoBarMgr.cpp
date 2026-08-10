#include "FluInfoBarMgr.h"
#include "FluShortInfoBar.h"
#include <QEvent>
#include <QPropertyAnimation>
#include <algorithm>

namespace
{
constexpr int kTopMargin = 72;
constexpr int kGap = 15;
constexpr int kSlideOffset = 20;
constexpr int kSlideDuration = 200;
}  // namespace

FluInfoBarMgr::FluInfoBarMgr(QObject* parent /*= nullptr*/) : QObject(parent)
{
    m_infoBarMap.clear();
}

FluInfoBarMgr::~FluInfoBarMgr()
{
}

void FluInfoBarMgr::showInfoBar(QWidget* parentWidget, FluShortInfoBarType type, QString text, bool isCloseable /*= true*/)
{
    FluShortInfoBar* sInfoBar = new FluShortInfoBar(FluShortInfoBarType::Info, parentWidget);
    sInfoBar->setInfoBarText(text);
    sInfoBar->setInfoBarType(type);
    if (!isCloseable)
        sInfoBar->getCloseButton()->hide();
    sInfoBar->setFixedWidth(270);
    FluInfoBarMgr::getInstance()->addInfoBar(parentWidget, sInfoBar);
}

void FluInfoBarMgr::addInfoBar(QWidget* parentWidget, FluShortInfoBar* infoBar, int disappearDuration /* = 800*/)
{
    if (parentWidget == nullptr || infoBar == nullptr)
        return;

    infoBar->setDisappearDuration(disappearDuration);

    auto itf = m_infoBarMap.find(parentWidget);
    if (itf == m_infoBarMap.end())
    {
        parentWidget->installEventFilter(this);
        std::list<FluShortInfoBar*> infoBarList;
        infoBarList.push_back(infoBar);
        m_infoBarMap[parentWidget] = infoBarList;
    }
    else
    {
        itf->second.push_back(infoBar);
    }

    // Slide the new toast up into its packed slot; existing toasts are untouched.
    QPoint target = targetPosition(parentWidget, infoBar);
    infoBar->move(target + QPoint(0, kSlideOffset));
    infoBar->show();
    animateTo(infoBar, target);

    // Auto-disappear after the configured duration (the old 1ms polling timer
    // used to drive this trigger; it was removed, so fire it here instead).
    infoBar->disappear();
}

void FluInfoBarMgr::removeInfoBar(FluShortInfoBar* infoBar)
{
    QWidget* parentWidget = nullptr;
    for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end(); itMap++)
    {
        auto itf = std::find(itMap->second.begin(), itMap->second.end(), infoBar);
        if (itf != itMap->second.end())
        {
            parentWidget = itMap->first;
            itMap->second.erase(itf);
            break;
        }
    }

    // Remaining toasts below slide up to fill the freed slot.
    if (parentWidget != nullptr)
    {
        auto itf = m_infoBarMap.find(parentWidget);
        if (itf != m_infoBarMap.end() && !itf->second.empty())
            relayout(parentWidget);
    }

    for (auto itMap = m_infoBarMap.begin(); itMap != m_infoBarMap.end();)
    {
        if (itMap->second.empty())
        {
            itMap->first->removeEventFilter(this);
            itMap = m_infoBarMap.erase(itMap);
            continue;
        }
        itMap++;
    }
}

QPoint FluInfoBarMgr::targetPosition(QWidget* parentWidget, FluShortInfoBar* infoBar)
{
    int x = parentWidget->width() / 2 - infoBar->width() / 2;
    int y = kTopMargin;

    auto itf = m_infoBarMap.find(parentWidget);
    if (itf != m_infoBarMap.end())
    {
        for (FluShortInfoBar* bar : itf->second)
        {
            if (bar == infoBar)
                break;
            y += bar->height() + kGap;
        }
    }

    return QPoint(x, y);
}

void FluInfoBarMgr::relayout(QWidget* parentWidget)
{
    auto itf = m_infoBarMap.find(parentWidget);
    if (itf == m_infoBarMap.end())
        return;

    int y = kTopMargin;
    for (FluShortInfoBar* bar : itf->second)
    {
        int x = parentWidget->width() / 2 - bar->width() / 2;
        animateTo(bar, QPoint(x, y));
        y += bar->height() + kGap;
    }
}

void FluInfoBarMgr::animateTo(FluShortInfoBar* bar, const QPoint& target)
{
    if (bar->pos() == target)
        return;

    QPropertyAnimation* anim = new QPropertyAnimation(bar, "pos", bar);
    anim->setDuration(kSlideDuration);
    anim->setEasingCurve(QEasingCurve::OutCubic);
    anim->setStartValue(bar->pos());
    anim->setEndValue(target);
    connect(anim, &QPropertyAnimation::finished, anim, &QObject::deleteLater);
    anim->start();
}

bool FluInfoBarMgr::eventFilter(QObject* watched, QEvent* event)
{
    auto itf = m_infoBarMap.find((QWidget*)watched);
    if (itf == m_infoBarMap.end())
        return QObject::eventFilter(watched, event);

    if (event->type() == QEvent::Resize)
    {
        QWidget* parentWidget = (QWidget*)watched;
        for (FluShortInfoBar* bar : itf->second)
        {
            int x = parentWidget->width() / 2 - bar->width() / 2;
            bar->move(x, bar->y());
        }
    }

    return QObject::eventFilter(watched, event);
}