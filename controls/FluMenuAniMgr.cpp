#include "FluRoundMenu.h"
#include "FluMenuAniMgr.h"

namespace
{
// Available geometry of the screen owning the popup anchor. screenAt() may
// return nullptr (point outside every screen), so fall back to the primary
// screen instead of dereferencing it.
QRect screenAvailableRect(const QPoint& pos)
{
    QScreen* screen = QApplication::screenAt(pos);
    if (screen == nullptr)
        screen = QApplication::primaryScreen();
    if (screen == nullptr)
        return QRect();
    return screen->availableGeometry();
}
} // namespace

FluMenuAniMgr::FluMenuAniMgr(FluRoundMenu* menu, FluMenuAniType aniType) : QObject(), m_menuAniType(aniType)
{
    m_menu = menu;
    m_posAni = new QPropertyAnimation((QObject*)menu, "pos", (QObject*)menu);
    m_posAni->setDuration(250);
    m_posAni->setEasingCurve(QEasingCurve::OutCubic);

    connect(m_posAni, &QPropertyAnimation::valueChanged, this, &FluMenuAniMgr::onValueChanged);
    connect(m_posAni, &QPropertyAnimation::valueChanged, this, &FluMenuAniMgr::updateMenuViewport);
}

QSize FluMenuAniMgr::availableViewSize(QPoint pos)
{
    if (m_menuAniType == FluMenuAniType::dropDown)
    {
        QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
        QSize viewSize;
        viewSize.setWidth(screenRect.width() - 100);

        int height = qMax(screenRect.bottom() - pos.y() - 10, 1);
        viewSize.setHeight(height);
        return viewSize;
    }
    else if (m_menuAniType == FluMenuAniType::pullUp)
    {
        QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();

        int w = screenRect.width() - 100;
        int h = qMax(pos.y() - 28, 1);
        return QSize(w, h);
    }

    QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = screenRect.width() - 100;
    int h = screenRect.height() - 100;
    return QSize(w, h);
}

QRect FluMenuAniMgr::anchorRect(QPoint pos) const
{
    // The menu's parent widget is the control that opens it (FluComboBox builds
    // its FluIndicatorRoundMenu with `this` as parent). Only trust that anchor
    // when the caller really passed its bottom-left corner, which is what the
    // combo box / drop-down button / command bar items do. Context menus pass a
    // cursor position and sub menus an item position: both keep the legacy
    // clamp-only behaviour instead of flipping around an unrelated widget.
    QWidget* anchor = m_menu->parentWidget();
    if (anchor == nullptr)
        return QRect();

    QRect rect(anchor->mapToGlobal(QPoint(0, 0)), anchor->size());
    if (!rect.isValid())
        return QRect();

    const int tolerance = 8;
    if (qAbs(rect.bottom() + 1 - pos.y()) > tolerance)
        return QRect();
    if (pos.x() < rect.left() - tolerance || pos.x() > rect.right() + tolerance)
        return QRect();
    return rect;
}

bool FluMenuAniMgr::shouldFlipUp(QPoint pos) const
{
    if (m_menuAniType != FluMenuAniType::dropDown)
        return false;

    QRect anchor = anchorRect(pos);
    if (!anchor.isValid())
        return false;

    QRect screenRect = screenAvailableRect(pos);
    if (!screenRect.isValid())
        return false;

    const int menuH = m_menu->height();
    const int spaceBelow = screenRect.bottom() - pos.y();
    const int spaceAbove = anchor.top() - screenRect.top();
    // Flip only when the menu really does not fit below its anchor and the
    // upper side has more room; otherwise keep dropping down (calcFinalPos
    // still clamps the result into the screen).
    return menuH > spaceBelow && spaceAbove > spaceBelow;
}

QPoint FluMenuAniMgr::calcFinalPos(QPoint pos)
{
    if (m_menuAniType == FluMenuAniType::pullUp)
    {
        QRect screenRect = screenAvailableRect(pos);
        int w = m_menu->width() + 5;
        int h = m_menu->height();

        int x = qMin(pos.x() - m_menu->layout()->contentsMargins().left(), screenRect.right() - w);
        x = qMax(x, screenRect.left());
        // `pos` is the anchor's top-left corner here: the menu's visible bottom
        // edge (the layout reserves the lower margin for the drop shadow) lands
        // just above the anchor, and the whole popup stays on screen.
        int y = qMax(pos.y() - h + 13, screenRect.top() + 4);
        return QPoint(x, y);
    }

    QRect screenRect = screenAvailableRect(pos);
    int menuW = m_menu->width() + 5;
    int menuH = m_menu->height();

    int x = qMin(pos.x() - m_menu->layout()->contentsMargins().left(), screenRect.right() - menuW);
    int y = qMin(pos.y() - 4, screenRect.bottom() - menuH);

    return QPoint(x, y);
}

QSize FluMenuAniMgr::getMenuSize()
{
    QMargins contentMargins = m_menu->layout()->contentsMargins();
    int w = m_menu->getView()->width() + contentMargins.left() + contentMargins.right() + 120;
    int h = m_menu->getView()->height() + contentMargins.top() + contentMargins.bottom() + 20;
    return QSize(w, h);
}

void FluMenuAniMgr::exec(QPoint pos)
{
    if (shouldFlipUp(pos))
    {
        // The menu does not fit below its anchor (window sitting on the desktop
        // bottom): open it above the anchor instead and let the animation run
        // from bottom to top. `pos` switches to the anchor's top-left corner,
        // which is the contract calcFinalPos expects for pullUp.
        m_menuAniType = FluMenuAniType::pullUp;
        pos = anchorRect(pos).topLeft();
    }

    if (m_menuAniType == FluMenuAniType::dropDown)
    {
        QPoint endPos = calcFinalPos(pos);
        int h = m_menu->height() + 5;

        m_posAni->setStartValue(endPos - QPoint(0, h / 2));
        m_posAni->setEndValue(endPos);
        m_posAni->start();
        return;
    }
    else if (m_menuAniType == FluMenuAniType::pullUp)
    {
        QPoint endPos = calcFinalPos(pos);
        int h = m_menu->height() + 5;
        m_posAni->setStartValue(endPos + QPoint(0, h / 2));
        m_posAni->setEndValue(endPos);
        m_posAni->start();
        // The animation owns `pos` from here on; moving the menu to its final
        // position as well would fight the first animation tick.
        return;
    }
    m_menu->move(calcFinalPos(pos));
}

FluMenuAniMgr* FluMenuAniMgr::make(FluRoundMenu* roundMenu, FluMenuAniType type)
{
    auto mgr = new FluMenuAniMgr(roundMenu, type);
    return mgr;
}

void FluMenuAniMgr::onValueChanged()
{
    if (m_menuAniType == FluMenuAniType::dropDown)
    {
        int menuW = getMenuSize().width();
        int menuH = getMenuSize().height();

        int y = m_posAni->endValue().toPoint().y() - m_posAni->currentValue().toPoint().y();
        m_menu->setMask(QRegion(0, y, menuW, menuH));
        return;
    }
    else if (m_menuAniType == FluMenuAniType::pullUp)
    {
        int w = getMenuSize().width();
        int h = getMenuSize().height();
        // Mirror of the dropDown reveal: the menu slides up from below its final
        // position while the mask pins its bottom edge and grows the visible
        // area upwards, so the list unfolds from bottom to top.
        int delta = qMax(m_posAni->currentValue().toPoint().y() - m_posAni->endValue().toPoint().y(), 0);
        m_menu->setMask(QRegion(0, 0, w, qMax(h - delta, 0)));
        return;
    }
}

void FluMenuAniMgr::updateMenuViewport()
{
    if (m_menu == nullptr)
        return;

    FluRoundMenuView* view = m_menu->getView();
    if (view == nullptr)
        return;

    view->viewport()->update();
    view->setAttribute(Qt::WA_UnderMouse, true);

    QHoverEvent hoverEvent = QHoverEvent(QEvent::HoverEnter, QPoint(), QPoint(1, 1));
    QApplication::sendEvent(view, &hoverEvent);
}
