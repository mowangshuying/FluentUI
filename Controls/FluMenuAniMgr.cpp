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

QPoint FluMenuAniMgr::calcFinalPos(QPoint pos)
{
    if (m_menuAniType == FluMenuAniType::pullUp)
    {
        FluRoundMenu* roundMenu = m_menu;
        QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
        int w = roundMenu->width() + 5;
        int h = roundMenu->height();

        int x = qMin(pos.x() - roundMenu->layout()->contentsMargins().left(), screenRect.height() - w);
        int y = qMax(pos.y() - h + 13, 4);
        return QPoint(x, y);
    }

    QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
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
        int y = m_posAni->endValue().toPoint().y() - m_posAni->currentValue().toPoint().y();
        m_menu->setMask(QRegion(0, y, w, h - 28));
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
