#include "FluRoundMenu.h"
#include "FluMenuAniMgr.h"

FluMenuAniMgr::FluMenuAniMgr(FluRoundMenu* menu, FluMenuAniType aniType) : QObject(), m_menuAniType(aniType)
{
    m_menu = menu;
    m_posAni = new QPropertyAnimation((QObject*)menu, "pos", (QObject*)menu);
    m_posAni->setDuration(250);
    m_posAni->setEasingCurve(QEasingCurve::OutQuad);

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

        int nHeight = qMax(screenRect.bottom() - pos.y() - 10, 1);
        viewSize.setHeight(nHeight);
        return viewSize;
    }
    else if (m_menuAniType == FluMenuAniType::pullUp)
    {
        QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();

        int nW = screenRect.width() - 100;
        int nH = qMax(pos.y() - 28, 1);
        return QSize(nW, nH);
    }

    QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int w = screenRect.width() - 100;
    int h = screenRect.height() - 100;
    return QSize(w, h);
}

QPoint FluMenuAniMgr::calcFinalPos(QPoint pos)
{
    if (m_menuAniType == FluMenuAniType::pullUp)
    {
        FluRoundMenu* roundMenu = m_menu;
        QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
        int nW = roundMenu->width() + 5;
        int nH = roundMenu->height();

        int nX = qMin(pos.x() - roundMenu->layout()->contentsMargins().left(), screenRect.height() - nW);
        int nY = qMax(pos.y() - nH + 13, 4);
        return QPoint(nX, nY);
    }

    QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int nMenuW = m_menu->width() + 5;
    int nMenuH = m_menu->height();

    int nX = qMin(pos.x() - m_menu->layout()->contentsMargins().left(), screenRect.right() - nMenuW);
    int nY = qMin(pos.y() - 4, screenRect.bottom() - nMenuH);

    return QPoint(nX, nY);
}

QSize FluMenuAniMgr::getMenuSize()
{
    QMargins contentMargins = m_menu->layout()->contentsMargins();
    int nW = m_menu->getView()->width() + contentMargins.left() + contentMargins.right() + 120;
    int nH = m_menu->getView()->height() + contentMargins.top() + contentMargins.bottom() + 20;
    return QSize(nW, nH);
}

void FluMenuAniMgr::exec(QPoint pos)
{
    if (m_menuAniType == FluMenuAniType::dropDown)
    {
        QPoint endPos = calcFinalPos(pos);
        int nH = m_menu->height() + 5;

        m_posAni->setStartValue(endPos - QPoint(0, nH / 2));
        m_posAni->setEndValue(endPos);
        m_posAni->start();
        return;
    }
    else if (m_menuAniType == FluMenuAniType::pullUp)
    {
        QPoint endPos = calcFinalPos(pos);
        int nH = m_menu->height() + 5;
        m_posAni->setStartValue(endPos + QPoint(0, nH / 2));
        m_posAni->setEndValue(endPos);
        m_posAni->start();
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

        int nY = m_posAni->endValue().toPoint().y() - m_posAni->currentValue().toPoint().y();
        m_menu->setMask(QRegion(0, nY, menuW, menuH));
        return;
    }
    else if (m_menuAniType == FluMenuAniType::pullUp)
    {
        int nW = getMenuSize().width();
        int nH = getMenuSize().height();
        int nY = m_posAni->endValue().toPoint().y() - m_posAni->currentValue().toPoint().y();
        m_menu->setMask(QRegion(0, nY, nW, nH - 28));
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
