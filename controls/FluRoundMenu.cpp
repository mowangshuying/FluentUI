#include "FluRoundMenu.h"
#include "FluSubMenuItemWidget.h"
#include "../Utils/FluUtils.h"
#include "FluMenuAniMgr.h"
#include "FluAction.h"

FluRoundMenu::FluRoundMenu(QWidget* parent /*= nullptr*/) : FluRoundMenu("", FluAwesomeType::None, parent)
{
}

FluRoundMenu::FluRoundMenu(QString title, FluAwesomeType iconType, QWidget* parent /*= nullptr*/) : QMenu(parent)
{
    // Q_D(QMenu)

    // m_title = title;
    // m_icon = QPixmap();
    m_mainAction = new FluAction(iconType, title);
    // setDefaultAction(m_mainAction);
    m_isSubMenu = false;
    m_parentMenu = nullptr;
    m_menuItem = nullptr;
    m_lastHoverItem = nullptr;
    m_lastHoverSubMenuItem = nullptr;
    m_isHideBySystem = true;
    m_itemHeight = 28;

    m_boxLayout = new QHBoxLayout(this);
    m_roundMenuView = new FluRoundMenuView(this);

    m_aniMgr = nullptr;
    m_timer = new QTimer(this);

    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);

    m_timer->setSingleShot(true);
    m_timer->setInterval(400);
    connect(m_timer, &QTimer::timeout, this, &FluRoundMenu::onShowMenuTimeOut);

    FluStyleSheetUtils::drawShadowEffect(m_roundMenuView, 30, QPoint(0, 8), QColor(0, 0, 0, 30));

    m_boxLayout->addWidget(m_roundMenuView, 1, Qt::AlignCenter);
    m_boxLayout->setContentsMargins(12, 8, 12, 20);

    connect(m_roundMenuView, &FluRoundMenuView::itemClicked, this, &FluRoundMenu::onItemClicked);
    connect(m_roundMenuView, &FluRoundMenuView::itemEntered, this, &FluRoundMenu::onItemEntered);

    // connect(m_mainAction, &QAction::triggered, this, &FluRoundMenu::)

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

void FluRoundMenu::setParentMenu(FluRoundMenu* menu, QListWidgetItem* item)
{
    m_parentMenu = menu;
    m_menuItem = item;

    if (menu == nullptr)
        m_isSubMenu = false;
    else
        m_isSubMenu = true;
}

void FluRoundMenu::adjustSize()
{
    QMargins contentMargins = layout()->contentsMargins();
    int w = m_roundMenuView->width() + contentMargins.left() + contentMargins.right();
    int h = m_roundMenuView->height() + contentMargins.top() + contentMargins.bottom();
    setFixedSize(w, h);
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

QAction* FluRoundMenu::menuAction()
{
    return m_mainAction;
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

    int w = 0;
    if (!hasMenuItemIcon())
    {
        item->setText(action->text());
        w = 40 + m_roundMenuView->fontMetrics().horizontalAdvance(item->text()) + spaceForShortCut;
    }
    else
    {
        item->setText(" " + action->text());
        w = 60 + m_roundMenuView->fontMetrics().horizontalAdvance(item->text()) + spaceForShortCut;
    }

    item->setSizeHint(QSize(w, m_itemHeight));
    return w;
}

int FluRoundMenu::calcShortcutWidth()
{
    QFont font;
    font.setPixelSize(12);
    QFontMetrics fontMetrics = QFontMetrics(font);
    int max = 0;
    for (auto itList = m_actions.begin(); itList != m_actions.end(); itList++)
    {
        QString shortCut = (*itList)->shortcut().toString();
        int shortCutWidth = fontMetrics.horizontalAdvance(shortCut);
        if (shortCutWidth > max)
            max = shortCutWidth;
    }
    return max;
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

    int index = itf - m_actions.begin();
    m_actions.erase(itf);

    auto fluAction = (FluAction*)action;
    fluAction->setListWidgetItem(nullptr);

    QListWidgetItem* item = m_roundMenuView->takeItem(index);
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

    int index = itf - m_actions.begin();
    m_roundMenuView->setCurrentRow(index);
}

void FluRoundMenu::setDefaultAction(int index)
{
    if (index < 0 || index >= m_actions.size())
        return;

    m_roundMenuView->setCurrentRow(index);
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

    int row = m_roundMenuView->row(beforeItem);
    m_roundMenuView->insertItem(row, item);
    m_roundMenuView->setItemWidget(item, widget);
    adjustSize();
}

FluSubMenuItemWidget* FluRoundMenu::createSubMenuItem(FluRoundMenu* menu)
{
    m_subMenus.append(menu);
    QListWidgetItem* item = new QListWidgetItem(makeItemIcon(menu), menu->getTitle());
    int w = 0;
    if (!hasMenuItemIcon())
        w = 60 + m_roundMenuView->fontMetrics().horizontalAdvance(menu->getTitle());
    else
        w = 72 + m_roundMenuView->fontMetrics().horizontalAdvance(item->text());

    menu->setParentMenu(this, item);
    item->setSizeHint(QSize(w, m_itemHeight));
    item->setData(Qt::UserRole, QVariant::fromValue(menu));

    FluSubMenuItemWidget* subMenuItemWidget = new FluSubMenuItemWidget(menu, item, this);
    connect(subMenuItemWidget, &FluSubMenuItemWidget::showMenuSig, this, &FluRoundMenu::onShowSubMenu);
    subMenuItemWidget->resize(item->sizeHint());
    return subMenuItemWidget;
}

void FluRoundMenu::addSeparator()
{
    QMargins viewMargins = m_roundMenuView->viewport()->contentsMargins();
    int w = m_roundMenuView->width() - viewMargins.left() - viewMargins.right();

    QListWidgetItem* item = new QListWidgetItem(m_roundMenuView);
    item->setFlags(Qt::NoItemFlags);
    item->setSizeHint(QSize(w, 9));
    m_roundMenuView->addItem(item);
    item->setData(Qt::DecorationRole, "separator");
    adjustSize();
}

void FluRoundMenu::hideMenu(bool isHideBySystem /*= false*/)
{
    m_isHideBySystem = isHideBySystem;
    m_roundMenuView->clearSelection();
    if (m_isSubMenu)
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
    int w = layout()->sizeHint().width() + 5;
    int h = layout()->sizeHint().height();

    int x = qMin(this->x() - margins.left(), screenRect.right() - w);
    int y = this->y();

    if (y > screenRect.bottom() - h)
    {
        y = this->y() - h + margins.bottom();
    }

    move(x, y);
}

void FluRoundMenu::exec(QPoint pos, bool isAni /*= true*/, FluMenuAniType aniType /*= FluMenuAniType::DROP_DOWN*/)
{
    m_aniMgr = FluMenuAniMgr::make(this, aniType);
    m_aniMgr->exec(pos);
    show();

    if (m_isSubMenu)
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

    if (!m_isSubMenu)
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
    FluStyleSheetUtils::setQssByFileName("FluRoundMenu.qss", this, FluThemeUtils::getUtils()->getTheme());

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
    if (m_isHideBySystem && m_isSubMenu)
        closeParentMenu();

    m_isHideBySystem = true;
    event->accept();
}

void FluRoundMenu::closeEvent(QCloseEvent* event)
{
    event->accept();
    emit closed();
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
    if (!m_isSubMenu)
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
