#include "FluInfoBarMgr.h"
#include "FluInfoBar.h"
#include <QEvent>
#include <QPropertyAnimation>
#include <algorithm>

namespace
{
constexpr int kTopMargin = 72;
constexpr int kGap = 15;
constexpr int kSlideOffset = 20;
constexpr int kSlideDuration = 200;
constexpr int kRightMargin = 16;
constexpr int kBottomMargin = 16;
}  // namespace

FluInfoBarMgr::FluInfoBarMgr(QObject* parent /*= nullptr*/) : QObject(parent)
{
    m_infoBarMap.clear();
    m_positionMap.clear();
}

FluInfoBarMgr::~FluInfoBarMgr()
{
}

void FluInfoBarMgr::showInfoBar(QWidget* parentWidget, FluInfoBarSeverity severity, QString text, bool isCloseable /*= true*/,
                                FluInfoBarPosition position /*= FluInfoBarPosition::TopCenter*/)
{
    FluInfoBar* infoBar = new FluInfoBar(severity, parentWidget);
    infoBar->setMessage(text);
    infoBar->setFixedWidth(270);
    infoBar->setIsClosable(isCloseable);
    infoBar->setIsOpen(true);
    infoBar->adjustSize();
    FluInfoBarMgr::getInstance()->addInfoBar(parentWidget, infoBar, 800, position);
}

void FluInfoBarMgr::addInfoBar(QWidget* parentWidget, FluInfoBar* infoBar, int disappearDuration /* = 800*/,
                               FluInfoBarPosition position /* = FluInfoBarPosition::TopCenter*/)
{
    if (parentWidget == nullptr || infoBar == nullptr)
        return;

    infoBar->setDisappearDuration(disappearDuration);

    // Remove the toast from management once it is closed (either by the close
    // button or by the auto-disappear fade-out).
    connect(infoBar, &FluInfoBar::closeRequested, this, [this, infoBar]() {
        removeInfoBar(infoBar);
        infoBar->deleteLater();
    });

    auto itf = m_infoBarMap.find(parentWidget);
    bool existed = (itf != m_infoBarMap.end());
    FluInfoBarPosition oldPos = positionOf(parentWidget);
    setPosition(parentWidget, position);

    if (existed)
    {
        // If the corner changed, move existing toasts to the new corner first.
        if (oldPos != position && !itf->second.empty())
            relayout(parentWidget);
        itf->second.push_back(infoBar);
    }
    else
    {
        parentWidget->installEventFilter(this);
        std::list<FluInfoBar*> infoBarList;
        infoBarList.push_back(infoBar);
        m_infoBarMap[parentWidget] = infoBarList;
    }

    // Slide the new toast into its packed slot; existing toasts are untouched.
    QPoint target = targetPosition(parentWidget, infoBar);
    infoBar->move(target + QPoint(0, kSlideOffset));
    infoBar->show();
    animateTo(infoBar, target);

    // Auto-disappear after the configured duration.
    infoBar->disappear();
}

void FluInfoBarMgr::removeInfoBar(FluInfoBar* infoBar)
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

    // Remaining toasts slide to fill the freed slot.
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
            QWidget* emptyParent = itMap->first;
            emptyParent->removeEventFilter(this);
            itMap = m_infoBarMap.erase(itMap);
            m_positionMap.erase(emptyParent);
            continue;
        }
        itMap++;
    }
}

FluInfoBarPosition FluInfoBarMgr::positionOf(QWidget* parentWidget) const
{
    auto itf = m_positionMap.find(parentWidget);
    if (itf == m_positionMap.end())
        return FluInfoBarPosition::TopCenter;
    return itf->second;
}

void FluInfoBarMgr::setPosition(QWidget* parentWidget, FluInfoBarPosition position)
{
    m_positionMap[parentWidget] = position;
}

QPoint FluInfoBarMgr::targetPosition(QWidget* parentWidget, FluInfoBar* infoBar)
{
    auto itf = m_infoBarMap.find(parentWidget);
    if (itf == m_infoBarMap.end())
        return QPoint(0, 0);

    if (positionOf(parentWidget) == FluInfoBarPosition::BottomRight)
    {
        int x = parentWidget->width() - infoBar->width() - kRightMargin;
        // The newest toast (last in the list) sits at the bottom; older ones stack upward.
        int bottom = parentWidget->height() - kBottomMargin;
        int y = bottom;
        for (auto it = itf->second.rbegin(); it != itf->second.rend(); ++it)
        {
            if (*it == infoBar)
                break;
            y -= ((*it)->height() + kGap);
        }
        return QPoint(x, y - infoBar->height());
    }

    int x = parentWidget->width() / 2 - infoBar->width() / 2;
    int y = kTopMargin;
    for (FluInfoBar* bar : itf->second)
    {
        if (bar == infoBar)
            break;
        y += bar->height() + kGap;
    }
    return QPoint(x, y);
}

void FluInfoBarMgr::relayout(QWidget* parentWidget)
{
    auto itf = m_infoBarMap.find(parentWidget);
    if (itf == m_infoBarMap.end())
        return;

    if (positionOf(parentWidget) == FluInfoBarPosition::BottomRight)
    {
        int bottom = parentWidget->height() - kBottomMargin;
        int y = bottom;
        for (auto it = itf->second.rbegin(); it != itf->second.rend(); ++it)
        {
            FluInfoBar* bar = *it;
            int x = parentWidget->width() - bar->width() - kRightMargin;
            animateTo(bar, QPoint(x, y - bar->height()));
            y -= (bar->height() + kGap);
        }
        return;
    }

    int y = kTopMargin;
    for (FluInfoBar* bar : itf->second)
    {
        int x = parentWidget->width() / 2 - bar->width() / 2;
        animateTo(bar, QPoint(x, y));
        y += bar->height() + kGap;
    }
}

void FluInfoBarMgr::animateTo(FluInfoBar* bar, const QPoint& target)
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
        bool bottomRight = (positionOf(parentWidget) == FluInfoBarPosition::BottomRight);
        for (FluInfoBar* bar : itf->second)
        {
            int x;
            if (bottomRight)
                x = parentWidget->width() - bar->width() - kRightMargin;
            else
                x = parentWidget->width() / 2 - bar->width() / 2;
            bar->move(x, bar->y());
        }
    }

    return QObject::eventFilter(watched, event);
}