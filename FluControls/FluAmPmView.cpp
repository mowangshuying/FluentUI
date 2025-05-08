#include "FluAmPmView.h"

FluAmPmView::FluAmPmView(int nFixedW /*= 80*/, QWidget* parent /*= nullptr*/) : FluWidget(parent), m_nFixedW(nFixedW)
{
    m_vMainLayout = new QVBoxLayout;
    m_vMainLayout->setContentsMargins(0, 0, 0, 0);
    m_vMainLayout->setSpacing(0);
    setLayout(m_vMainLayout);

    m_apView = new QListWidget;

    m_scrollDownBtn = new QPushButton(this);
    m_scrollDownBtn->setFixedSize(nFixedW, 40);
    m_scrollUpBtn = new QPushButton(this);
    m_scrollUpBtn->setFixedSize(nFixedW, 40);

    m_vMainLayout->addStretch(1);
    //  m_vMainLayout->addSpacing(40);
    m_vMainLayout->addWidget(m_apView);
    m_vMainLayout->addStretch(1);

    m_apView->setObjectName("apView");
    m_apView->setFixedHeight(80);
    m_apView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_apView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_apView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));
    m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));

    m_scrollDownBtn->setObjectName("scrollDownBtn");
    m_scrollUpBtn->setObjectName("scrollUpBtn");

    m_scrollUpBtn->hide();
    m_scrollDownBtn->hide();

    connect(m_scrollUpBtn, &QPushButton::clicked, [=]() { scrollUp(); });
    connect(m_scrollDownBtn, &QPushButton::clicked, [=]() { scrollDown(); });
    connect(m_apView, &QListWidget::itemClicked, [=](QListWidgetItem* item) {
        int nIndex = item->data(Qt::UserRole).toInt();
        if (nIndex == 1 && !m_bAm)
        {
            scrollUp();
            return;
        }

        if (nIndex == 2 && m_bAm)
        {
            scrollDown();
            return;
        }
    });

    m_apView->setFixedWidth(nFixedW);
    setFixedWidth(nFixedW);

    setAmPm(tr("AM"), tr("PM"));
    setAm(true);
    onThemeChanged();
}

QString FluAmPmView::getCurrentText()
{
    return m_apView->currentItem()->text();
}

void FluAmPmView::setAmPm(QString am, QString pm)
{
    m_apView->clear();

    auto topEmptyItem = new QListWidgetItem;
    topEmptyItem->setFlags(topEmptyItem->flags() & ~Qt::ItemIsEnabled);
    topEmptyItem->setSizeHint(QSize(m_nFixedW, 40));
    topEmptyItem->setText("");
    topEmptyItem->setTextAlignment(Qt::AlignCenter);
    topEmptyItem->setData(Qt::UserRole, 0);

    m_apView->addItem(topEmptyItem);

    auto amItem = new QListWidgetItem;
    amItem->setSizeHint(QSize(m_nFixedW, 40));
    amItem->setText(am);
    amItem->setTextAlignment(Qt::AlignCenter);
    amItem->setData(Qt::UserRole, 1);
    m_apView->addItem(amItem);

    auto pmItem = new QListWidgetItem;
    pmItem->setSizeHint(QSize(m_nFixedW, 40));
    pmItem->setText(pm);
    pmItem->setTextAlignment(Qt::AlignCenter);
    pmItem->setData(Qt::UserRole, 2);
    m_apView->addItem(pmItem);

    auto bottomEmptyItem = new QListWidgetItem;
    bottomEmptyItem->setFlags(bottomEmptyItem->flags() & ~Qt::ItemIsEnabled);
    bottomEmptyItem->setSizeHint(QSize(m_nFixedW, 40));
    bottomEmptyItem->setText("");
    bottomEmptyItem->setTextAlignment(Qt::AlignCenter);
    bottomEmptyItem->setData(Qt::UserRole, 3);

    m_apView->addItem(bottomEmptyItem);

    m_apView->setFixedHeight(40 * 3 + 4 * 2);
}

bool FluAmPmView::isAm()
{
    return m_bAm;
}

void FluAmPmView::setAm(bool bAm)
{
    m_bAm = bAm;
    if (m_bAm)
    {
        m_apView->setCurrentItem(m_apView->item(1));
        m_apView->scrollToItem(m_apView->item(1), QAbstractItemView::PositionAtCenter);
        emit currentItemChanged();
    }
    else
    {
        m_apView->setCurrentItem(m_apView->item(2));
        m_apView->scrollToItem(m_apView->item(2), QAbstractItemView::PositionAtCenter);
        emit currentItemChanged();
    }
}

void FluAmPmView::scrollUp()
{
    if (m_bAm)
        return;

    m_bAm = !m_bAm;
    m_apView->setCurrentItem(m_apView->item(1));
    m_apView->scrollToItem(m_apView->item(1), QAbstractItemView::PositionAtCenter);
    emit currentItemChanged();
}

void FluAmPmView::scrollDown()
{
    if (!m_bAm)
        return;

    m_bAm = !m_bAm;
    m_apView->setCurrentItem(m_apView->item(2));
    m_apView->scrollToItem(m_apView->item(2), QAbstractItemView::PositionAtCenter);
    emit currentItemChanged();
}

void FluAmPmView::enterEvent(QEnterEvent* event)
{
    m_scrollUpBtn->move(0, 0);
    m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
    m_scrollUpBtn->show();
    m_scrollDownBtn->show();
}

void FluAmPmView::leaveEvent(QEvent* event)
{
    m_scrollUpBtn->move(0, 0);
    m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
    m_scrollUpBtn->hide();
    m_scrollDownBtn->hide();
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
    m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluThemeUtils::getUtils()->getTheme())));
    m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluThemeUtils::getUtils()->getTheme())));
    FluStyleSheetUitls::setQssByFileName("FluAmPmView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
