#include "FluRoundMenu.h"
#include "FluSubMenuItemWidget.h"
#include "../FluUtils/FluUtils.h"
#include "FluMenuAniMgr.h"
#include "FluAction.h"

FluRoundMenu::FluRoundMenu(QWidget* parent /*= nullptr*/) : FluRoundMenu("", FluAwesomeType::None, parent)
{
}

FluRoundMenu::FluRoundMenu(QString title, FluAwesomeType iconType, QWidget* parent /*= nullptr*/) : QMenu(parent)
{
    // m_title = title;
    // m_icon = QPixmap();
    m_mainAction = new FluAction(iconType, title);
    m_bSubMenu = false;
    m_parentMenu = nullptr;
    m_menuItem = nullptr;
    m_lastHoverItem = nullptr;
    m_lastHoverSubMenuItem = nullptr;
    m_bHideBySystem = true;
    m_itemHeight = 28;

    m_hBoxLayout = new QHBoxLayout(this);
    m_roundMenuView = new FluRoundMenuView(this);

    m_aniMgr = nullptr;
    m_timer = new QTimer(this);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_timer->setSingleShot(true);
    m_timer->setInterval(400);
    connect(m_timer, &QTimer::timeout, this, &FluRoundMenu::onShowMenuTimeOut);

    // setShadowEffect();
    m_hBoxLayout->addWidget(m_roundMenuView, 1, Qt::AlignCenter);
    m_hBoxLayout->setContentsMargins(12, 8, 12, 20);

    connect(m_roundMenuView, &FluRoundMenuView::itemClicked, this, &FluRoundMenu::onItemClicked);
    connect(m_roundMenuView, &FluRoundMenuView::itemEntered, this, &FluRoundMenu::onItemEntered);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluRoundMenu::setMaxVisibleItems(int num)
{
    m_roundMenuView->setMaxVisibleItems(num);
    adjustSize();
}

void FluRoundMenu::setItemHeight(int height)
{
    if (height == m_itemHeight)
        return;

    m_itemHeight = height;
    m_roundMenuView->setItemHeight(height);
}

FluRoundMenuView* FluRoundMenu::getView()
{
    return m_roundMenuView;
}

// void FluRoundMenu::setShadowEffect(int blurRadius /*= 30*/, QPoint offset /*= QPoint(0, 8)*/, QColor color /*= QColor(0, 0, 0, 30)*/)
// {
//     m_shadowEffect = new QGraphicsDropShadowEffect(m_roundMenuView);
//     m_shadowEffect->setBlurRadius(blurRadius);
//     m_shadowEffect->setOffset(offset);
//     m_shadowEffect->setColor(color);
//     m_roundMenuView->setGraphicsEffect(nullptr);
//     m_roundMenuView->setGraphicsEffect(m_shadowEffect);
// }

void FluRoundMenu::setParentMenu(FluRoundMenu* menu, QListWidgetItem* item)
{
    m_parentMenu = menu;
    m_menuItem = item;

    if (menu == nullptr)
        m_bSubMenu = false;
    else
        m_bSubMenu = true;
}

void FluRoundMenu::adjustSize()
{
    QMargins contentMargins = layout()->contentsMargins();
    int nW = m_roundMenuView->width() + contentMargins.left() + contentMargins.right();
    int nH = m_roundMenuView->height() + contentMargins.top() + contentMargins.bottom();
    setFixedSize(nW, nH);
}

QPixmap FluRoundMenu::getIcon()
{
    // return m_icon;
    return m_mainAction->icon().pixmap(20, 20);
}

void FluRoundMenu::setIcon(QPixmap icon)
{
    // m_icon = icon;
    m_mainAction->setIcon(icon);
}

QString FluRoundMenu::getTitle()
{
    return m_mainAction->text();
}

void FluRoundMenu::setTitle(QString title)
{
    m_mainAction->setText(title);
}

void FluRoundMenu::clear()
{
    auto itList = m_actions.begin();
    for (; itList != m_actions.end();)
    {
        removeAction((*itList));
        itList = m_actions.begin();
    }
}

void FluRoundMenu::addAction(QAction* action)
{
    QListWidgetItem* item = createActionItem(action);
    m_roundMenuView->addItem(item);
    adjustSize();
}

QListWidgetItem* FluRoundMenu::createActionItem(QAction* action, QAction* preAction /*= nullptr*/)
{
    if (preAction == nullptr)
    {
        m_actions.push_back(action);
    }
    else
    {
        auto itf = std::find(m_actions.begin(), m_actions.end(), preAction);
        if (itf != m_actions.end())
        {
            m_actions.insert(itf, action);
        }
        else
        {
            return nullptr;
        }
    }

    QListWidgetItem* item = new QListWidgetItem(makeItemIcon(action), action->text());
    adjustItemText(item, action);
    if (!action->isEnabled())
        item->setFlags(Qt::NoItemFlags);
    item->setData(Qt::UserRole, QVariant::fromValue<QAction*>(action));

    auto fluAction = (FluAction*)action;
    fluAction->setListWidgetItem(item);

    connect(action, &QAction::changed, this, &FluRoundMenu::onActionChanged);

    return item;
}

int FluRoundMenu::adjustItemText(QListWidgetItem* item, QAction* action)
{
    int spaceForShortCut = 0;
    QString className = m_roundMenuView->itemDelegate()->metaObject()->className();
    if (className == "FluShortcutMenuItemDelegate")
    {
        spaceForShortCut = calcShortcutWidth();
        if (spaceForShortCut != 0)
            spaceForShortCut += 22;
    }

    int nW = 0;
    if (!hasMenuItemIcon())
    {
        item->setText(action->text());
        nW = 40 + m_roundMenuView->fontMetrics().horizontalAdvance(item->text()) + spaceForShortCut;
    }
    else
    {
        item->setText(" " + action->text());
        nW = 60 + m_roundMenuView->fontMetrics().horizontalAdvance(item->text()) + spaceForShortCut;
    }

    item->setSizeHint(QSize(nW, m_itemHeight));
    return nW;
}

int FluRoundMenu::calcShortcutWidth()
{
    QFont font;
    font.setPixelSize(12);
    QFontMetrics fontMetrics = QFontMetrics(font);
    int nMax = 0;
    for (auto itList = m_actions.begin(); itList != m_actions.end(); itList++)
    {
        QString shortCut = (*itList)->shortcut().toString();
        int nShortCutWidth = fontMetrics.horizontalAdvance(shortCut);
        if (nShortCutWidth > nMax)
            nMax = nShortCutWidth;
    }
    return nMax;
}

QIcon FluRoundMenu::makeItemIcon(QAction* action)
{
    bool hasIcon = hasMenuItemIcon();
    QIcon icon = action->icon();
    if (hasIcon && action->icon().isNull())
    {
        QPixmap pixmap = QPixmap(m_roundMenuView->iconSize());
        pixmap.fill(Qt::transparent);
        icon = QIcon(pixmap);
    }
    else if (!hasIcon)
    {
        icon = QIcon();
    }
    return icon;
}

QIcon FluRoundMenu::makeItemIcon(FluRoundMenu* menu)
{
    bool hasIcon = hasMenuItemIcon();
    QIcon icon = menu->getIcon();
    if (hasIcon && menu->getIcon().isNull())
    {
        QPixmap pixmap = QPixmap(m_roundMenuView->iconSize());
        pixmap.fill(Qt::transparent);
        icon = QIcon(pixmap);
    }
    else if (!hasIcon)
    {
        icon = QIcon();
    }
    return icon;
}

bool FluRoundMenu::hasMenuItemIcon()
{
    for (auto itList = m_actions.begin(); itList != m_actions.end(); itList++)
    {
        if (!(*itList)->icon().isNull())
        {
            return true;
        }
    }

    for (auto itList = m_subMenus.begin(); itList != m_subMenus.end(); itList++)
    {
        if ((*itList)->hasMenuItemIcon())
            return true;
    }

    return false;
}

QList<QAction*> FluRoundMenu::actions() const
{
    return m_actions;
}

void FluRoundMenu::insertAction(QAction* before, QAction* action)
{
    auto itf = std::find(m_actions.begin(), m_actions.end(), before);
    if (itf == m_actions.end())
        return;

    // QListWidgetItem* beforeItem = before->property("item").value<QListWidgetItem*>();
    auto fluAction = (FluAction*)action;
    QListWidgetItem* beforeItem = fluAction->getListWidgetItem();
    if (beforeItem == nullptr)
        return;

    int index = m_roundMenuView->row(beforeItem);
    QListWidgetItem* item = createActionItem(action, before);
    m_roundMenuView->insertItem(index, item);
    adjustSize();
}

void FluRoundMenu::addActions(const QList<QAction*> actions)
{
    for (auto itList = actions.begin(); itList != actions.end(); itList++)
    {
        // m_actions.append((*itList));
        addAction((*itList));
    }
}

void FluRoundMenu::insertActions(QAction* before, const QList<QAction*>& actions)
{
    for (auto itList = actions.begin(); itList != actions.end(); itList++)
    {
        insertAction(before, (*itList));
    }
}

void FluRoundMenu::removeAction(QAction* action)
{
    auto itf = std::find(m_actions.begin(), m_actions.end(), action);
    if (itf == m_actions.end())
        return;

    int nIndex = itf - m_actions.begin();
    m_actions.erase(itf);

    auto fluAction = (FluAction*)action;
    fluAction->setListWidgetItem(nullptr);

    QListWidgetItem* item = m_roundMenuView->takeItem(nIndex);
    item->setData(Qt::UserRole, QVariant::fromValue(nullptr));

    QWidget* widget = m_roundMenuView->itemWidget(item);
    if (widget != nullptr)
        widget->deleteLater();
}

void FluRoundMenu::setDefaultAction(QAction* action)
{
    auto itf = std::find(m_actions.begin(), m_actions.end(), action);
    if (itf == m_actions.end())
        return;

    int nIndex = itf - m_actions.begin();
    m_roundMenuView->setCurrentRow(nIndex);
}

void FluRoundMenu::setDefaultAction(int nIndex)
{
    if (nIndex < 0 || nIndex >= m_actions.size())
        return;

    m_roundMenuView->setCurrentRow(nIndex);
}

void FluRoundMenu::setDefaultAction(QString text)
{
    for (auto iter = m_actions.begin(); iter != m_actions.end(); iter++)
    {
        if ((*iter)->text() == text)
        {
            setDefaultAction((*iter));
            break;
        }
    }
}

void FluRoundMenu::addMenu(FluRoundMenu* menu)
{
    FluSubMenuItemWidget* widget = createSubMenuItem(menu);
    QListWidgetItem* item = widget->getItem();

    m_roundMenuView->addItem(item);
    m_roundMenuView->setItemWidget(item, widget);
    adjustSize();
}

void FluRoundMenu::insertMenu(QAction* before, FluRoundMenu* menu)
{
    auto itf = std::find(m_actions.begin(), m_actions.end(), before);
    if (itf == m_actions.end())
        return;

    FluSubMenuItemWidget* widget = createSubMenuItem(menu);
    QListWidgetItem* item = widget->getItem();

    // QListWidgetItem* beforeItem = before->property("item").value<QListWidgetItem*>();
    auto fluAction = (FluAction*)before;
    QListWidgetItem* beforeItem = fluAction->getListWidgetItem();

    int nRow = m_roundMenuView->row(beforeItem);
    m_roundMenuView->insertItem(nRow, item);
    m_roundMenuView->setItemWidget(item, widget);
    adjustSize();
}

FluSubMenuItemWidget* FluRoundMenu::createSubMenuItem(FluRoundMenu* menu)
{
    m_subMenus.append(menu);
    QListWidgetItem* item = new QListWidgetItem(makeItemIcon(menu), menu->getTitle());
    int nW = 0;
    if (!hasMenuItemIcon())
        nW = 60 + m_roundMenuView->fontMetrics().horizontalAdvance(menu->getTitle());
    else
        nW = 72 + m_roundMenuView->fontMetrics().horizontalAdvance(item->text());

    menu->setParentMenu(this, item);
    item->setSizeHint(QSize(nW, m_itemHeight));
    item->setData(Qt::UserRole, QVariant::fromValue(menu));

    FluSubMenuItemWidget* subMenuItemWidget = new FluSubMenuItemWidget(menu, item, this);
    connect(subMenuItemWidget, &FluSubMenuItemWidget::showMenuSig, this, &FluRoundMenu::onShowSubMenu);
    subMenuItemWidget->resize(item->sizeHint());
    return subMenuItemWidget;
}

void FluRoundMenu::addSeparator()
{
    QMargins viewMargins = m_roundMenuView->viewport()->contentsMargins();
    int nW = m_roundMenuView->width() - viewMargins.left() - viewMargins.right();

    QListWidgetItem* item = new QListWidgetItem(m_roundMenuView);
    item->setFlags(Qt::NoItemFlags);
    item->setSizeHint(QSize(nW, 9));
    m_roundMenuView->addItem(item);
    item->setData(Qt::DecorationRole, "separator");
    adjustSize();
}

void FluRoundMenu::hideMenu(bool bHideBySystem /*= false*/)
{
    m_bHideBySystem = bHideBySystem;
    m_roundMenuView->clearSelection();
    if (m_bSubMenu)
        hide();
    else
        close();
}

void FluRoundMenu::closeParentMenu()
{
    FluRoundMenu* roundMenu = this;
    while (roundMenu != nullptr)
    {
        roundMenu->close();
        roundMenu = roundMenu->m_parentMenu;
    }
}

QList<QAction*> FluRoundMenu::getMenuActions()
{
    return m_actions;
}

void FluRoundMenu::adjustPosition()
{
    QMargins margins = layout()->contentsMargins();
    QRect screenRect = QApplication::screenAt(QCursor::pos())->availableGeometry();
    int nW = layout()->sizeHint().width() + 5;
    int nH = layout()->sizeHint().height();

    int nX = qMin(x() - margins.left(), screenRect.right() - nW);
    int nY = y();

    if (nY > screenRect.bottom() - nH)
    {
        nY = y() - nH + margins.bottom();
    }

    move(nX, nY);
}

void FluRoundMenu::exec(QPoint pos, bool bAni /*= true*/, FluMenuAniType aniType /*= FluMenuAniType::DROP_DOWN*/)
{
    m_aniMgr = FluMenuAniMgr::make(this, aniType);
    m_aniMgr->exec(pos);
    show();

    if (m_bSubMenu)
        m_menuItem->setSelected(true);
}

void FluRoundMenu::onShowMenuTimeOut()
{
    if (m_lastHoverItem == nullptr || m_lastHoverItem != m_lastHoverSubMenuItem)
    {
        return;
    }

    FluSubMenuItemWidget* itemWidget = (FluSubMenuItemWidget*)(m_roundMenuView->itemWidget(m_lastHoverSubMenuItem));
    if (itemWidget->getMenu()->m_parentMenu->isHidden())
        return;

    QPoint pos = itemWidget->mapToGlobal(QPoint(itemWidget->width() + 5, -5));
    itemWidget->getMenu()->exec(pos);
}

void FluRoundMenu::onItemClicked(QListWidgetItem* item)
{
    QAction* action = item->data(Qt::UserRole).value<QAction*>();
    auto itf = std::find(m_actions.begin(), m_actions.end(), action);
    if (itf == m_actions.end())
        return;

    if (!action->isEnabled())
        return;

    if (m_roundMenuView->itemWidget(item) != nullptr && action->property("selectable").toBool() == false)
        return;

    hideMenu(false);

    if (!m_bSubMenu)
    {
        action->trigger();
        emit FluRoundMenu::triggered(action);
        return;
    }

    closeParentMenu();
    action->trigger();
    emit FluRoundMenu::triggered(action);
}

void FluRoundMenu::onItemEntered(QListWidgetItem* item)
{
    m_lastHoverItem = item;
    FluRoundMenu* roundMenu = item->data(Qt::UserRole).value<FluRoundMenu*>();
    if (roundMenu == nullptr)
        return;

    onShowSubMenu(item);
}

void FluRoundMenu::onActionChanged()
{
    QAction* action = (QAction*)(sender());
    // QListWidgetItem* item = action->property("item").value<QListWidgetItem*>();
    auto fluAction = (FluAction*)action;
    auto item = fluAction->getListWidgetItem();
    item->setIcon(makeItemIcon(action));

    adjustItemText(item, action);
    if (action->isEnabled())
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    else
        item->setFlags(Qt::NoItemFlags);
    m_roundMenuView->adjustSize();
    adjustSize();
}

void FluRoundMenu::onShowSubMenu(QListWidgetItem* item)
{
    m_lastHoverItem = item;
    m_lastHoverSubMenuItem = item;
    m_timer->stop();
    m_timer->start();
}

void FluRoundMenu::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("FluRoundMenu.qss", this, FluThemeUtils::getUtils()->getTheme());

    for (auto action : actions())
    {
        auto fluAction = (FluAction*)action;
        if (fluAction->getAwesomeType() == FluAwesomeType::None)
            continue;

        fluAction->setIcon(FluIconUtils::getFluentIcon(fluAction->getAwesomeType(), FluThemeUtils::getUtils()->getTheme()));
    }
}

void FluRoundMenu::hideEvent(QHideEvent* event)
{
    if (m_bHideBySystem && m_bSubMenu)
        closeParentMenu();

    m_bHideBySystem = true;
    event->accept();
}

void FluRoundMenu::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit closedSignal();
    m_roundMenuView->clearSelection();
}

void FluRoundMenu::mousePressEvent(QMouseEvent* event)
{
    QWidget* widget = childAt(event->pos());
    if (widget != m_roundMenuView && m_roundMenuView->isAncestorOf(widget) == false)
        hideMenu(true);
}

void FluRoundMenu::mouseMoveEvent(QMouseEvent* event)
{
    if (!m_bSubMenu)
        return;

    if (!m_parentMenu)
        return;

    QPoint pos = event->globalPos();
    FluRoundMenuView* view = m_parentMenu->getView();

    QMargins margins = view->viewport()->contentsMargins();
    QRect rect = view->visualItemRect(m_menuItem).translated(view->mapToGlobal(QPoint(0, 0)));
    if ((m_parentMenu->geometry().contains(pos)) && (!rect.contains(pos)) && (!geometry().contains(pos)))
    {
        view->clearSelection();
        hideMenu(false);
    }
}
