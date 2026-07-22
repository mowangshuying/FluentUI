#include "FluAmPmView.h"

FluAmPmView::FluAmPmView(int fixedWidth /*= 80*/, QWidget* parent /*= nullptr*/) : FluWidget(parent), m_fixedWidth(fixedWidth)
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    m_amPmListView = new QListWidget;

    m_scrollDownButton = new QPushButton(this);
    m_scrollDownButton->setFixedSize(fixedWidth, 40);
    m_scrollUpButton = new QPushButton(this);
    m_scrollUpButton->setFixedSize(fixedWidth, 40);

    m_mainLayout->addStretch(1);
    m_mainLayout->addWidget(m_amPmListView);
    m_mainLayout->addStretch(1);

    m_amPmListView->setObjectName("apView");
    m_amPmListView->setFixedHeight(80);
    m_amPmListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_amPmListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_amPmListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    m_scrollUpButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));
    m_scrollDownButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));

    m_scrollDownButton->setObjectName("scrollDownBtn");
    m_scrollUpButton->setObjectName("scrollUpBtn");

    m_scrollUpButton->hide();
    m_scrollDownButton->hide();

    connect(m_scrollUpButton, &QPushButton::clicked, [=]() { scrollUp(); });
    connect(m_scrollDownButton, &QPushButton::clicked, [=]() { scrollDown(); });
    connect(m_amPmListView, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        int currentIndex = item->data(Qt::UserRole).toInt();
        if (currentIndex == 1 && !m_isAm)
        {
            scrollUp();
            return;
        }

        if (currentIndex == 2 && m_isAm)
        {
            scrollDown();
            return;
        }
    });

    m_amPmListView->setFixedWidth(fixedWidth);
    setFixedWidth(fixedWidth);

    setAmPm(tr("AM"), tr("PM"));
    setAm(true);
    onThemeChanged();
}

QString FluAmPmView::getCurrentText()
{
    return m_amPmListView->currentItem()->text();
}

void FluAmPmView::setAmPm(QString am, QString pm)
{
    m_amPmListView->clear();

    auto topEmptyItem = new QListWidgetItem;
    topEmptyItem->setFlags(topEmptyItem->flags() & ~Qt::ItemIsEnabled);
    topEmptyItem->setSizeHint(QSize(m_fixedWidth, 40));
    topEmptyItem->setText("");
    topEmptyItem->setTextAlignment(Qt::AlignCenter);
    topEmptyItem->setData(Qt::UserRole, 0);

    m_amPmListView->addItem(topEmptyItem);

    auto amItem = new QListWidgetItem;
    amItem->setSizeHint(QSize(m_fixedWidth, 40));
    amItem->setText(am);
    amItem->setTextAlignment(Qt::AlignCenter);
    amItem->setData(Qt::UserRole, 1);
    m_amPmListView->addItem(amItem);

    auto pmItem = new QListWidgetItem;
    pmItem->setSizeHint(QSize(m_fixedWidth, 40));
    pmItem->setText(pm);
    pmItem->setTextAlignment(Qt::AlignCenter);
    pmItem->setData(Qt::UserRole, 2);
    m_amPmListView->addItem(pmItem);

    auto bottomEmptyItem = new QListWidgetItem;
    bottomEmptyItem->setFlags(bottomEmptyItem->flags() & ~Qt::ItemIsEnabled);
    bottomEmptyItem->setSizeHint(QSize(m_fixedWidth, 40));
    bottomEmptyItem->setText("");
    bottomEmptyItem->setTextAlignment(Qt::AlignCenter);
    bottomEmptyItem->setData(Qt::UserRole, 3);

    m_amPmListView->addItem(bottomEmptyItem);

    m_amPmListView->setFixedHeight(40 * 3 + 4 * 2);
}

bool FluAmPmView::isAm()
{
    return m_isAm;
}

void FluAmPmView::setAm(bool isAm)
{
    m_isAm = isAm;
    if (m_isAm)
    {
        m_amPmListView->setCurrentItem(m_amPmListView->item(1));
        m_amPmListView->scrollToItem(m_amPmListView->item(1), QAbstractItemView::PositionAtCenter);
        emit currentItemChanged();
    }
    else
    {
        m_amPmListView->setCurrentItem(m_amPmListView->item(2));
        m_amPmListView->scrollToItem(m_amPmListView->item(2), QAbstractItemView::PositionAtCenter);
        emit currentItemChanged();
    }
}

void FluAmPmView::scrollUp()
{
    if (m_isAm)
        return;

    m_isAm = !m_isAm;
    m_amPmListView->setCurrentItem(m_amPmListView->item(1));
    m_amPmListView->scrollToItem(m_amPmListView->item(1), QAbstractItemView::PositionAtCenter);
    emit currentItemChanged();
}

void FluAmPmView::scrollDown()
{
    if (!m_isAm)
        return;

    m_isAm = !m_isAm;
    m_amPmListView->setCurrentItem(m_amPmListView->item(2));
    m_amPmListView->scrollToItem(m_amPmListView->item(2), QAbstractItemView::PositionAtCenter);
    emit currentItemChanged();
}

void FluAmPmView::enterEvent(QEnterEvent* event)
{
    m_scrollUpButton->move(0, 0);
    m_scrollDownButton->move(0, height() - m_scrollDownButton->height());
    m_scrollUpButton->show();
    m_scrollDownButton->show();
}

void FluAmPmView::leaveEvent(QEvent* event)
{
    m_scrollUpButton->move(0, 0);
    m_scrollDownButton->move(0, height() - m_scrollDownButton->height());
    m_scrollUpButton->hide();
    m_scrollDownButton->hide();
}

void FluAmPmView::wheelEvent(QWheelEvent* e)
{
    if (e->angleDelta().y() < 0)
    {
        scrollDown();
    }
    else
    {
        scrollUp();
    }
}

void FluAmPmView::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Down)
    {
        scrollDown();
        return;
    }

    if (event->key() == Qt::Key_Up)
    {
        scrollUp();
        return;
    }
}

void FluAmPmView::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void FluAmPmView::onThemeChanged()
{
    m_scrollUpButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluThemeUtils::getUtils()->getTheme())));
    m_scrollDownButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluThemeUtils::getUtils()->getTheme())));
    FluStyleSheetUtils::setQssByFileName("FluAmPmView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
