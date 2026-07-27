#include "FluLoopView.h"

FluLoopView::FluLoopView(int fixedW /*= 80*/, QWidget* parent /*= nullptr*/) : QListWidget(parent), m_fixedW(fixedW)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);  // fix bottom empty.

    m_scrollDownButton = new QPushButton(this);
    m_scrollDownButton->setFixedSize(fixedW, 40);
    m_scrollUpButton = new QPushButton(this);
    m_scrollUpButton->setFixedSize(fixedW, 40);

    m_scrollUpButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));
    m_scrollDownButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));

    m_scrollDownButton->setObjectName("scrollDownBtn");
    m_scrollUpButton->setObjectName("scrollUpBtn");

    m_scrollUpButton->hide();
    m_scrollDownButton->hide();

    connect(m_scrollUpButton, &QPushButton::clicked, [=]() { scrollUp(); });

    connect(m_scrollDownButton, &QPushButton::clicked, [=]() { scrollDown(); });

    connect(this, &FluLoopView::itemClicked, [=](QListWidgetItem* item) {
        int index = item->data(Qt::UserRole).toInt();
        //  scrollToItem(this->item(index));
        if (index < 0 || index >= m_totalVisibleCount)
            return;

        while (index != m_visibleMidIndex)
        {
            //   QThread::msleep(500);
            if (index > m_visibleMidIndex)
                scrollDown();
            else
                scrollUp();
        }
    });

    setMaxVisibleNum(9);
    m_visibleMidIndex = 0;
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluLoopView::setAllItems(const std::vector<QString>& datas)
{
    // the top;
    int mid = m_maxVisibleNum / 2;
    for (int i = 0; i < mid; i++)
    {
        auto item = new QListWidgetItem;
        item->setSizeHint(QSize(m_fixedW, 40));
        item->setText(datas[datas.size() - mid + i]);
        item->setTextAlignment(Qt::AlignCenter);

        item->setData(Qt::UserRole, QVariant::fromValue(datas.size() - mid + i));
        addItem(item);
    }

    for (int i = 0; i < datas.size(); i++)
    {
        auto item = new QListWidgetItem;
        item->setSizeHint(QSize(m_fixedW, 40));
        item->setText(datas[i]);
        item->setTextAlignment(Qt::AlignCenter);

        item->setData(Qt::UserRole, i);
        addItem(item);
    }

    for (int i = 0; i < mid; i++)
    {
        auto item = new QListWidgetItem;
        item->setSizeHint(QSize(m_fixedW, 40));
        item->setText(datas[i]);
        item->setTextAlignment(Qt::AlignCenter);

        item->setData(Qt::UserRole, i);
        addItem(item);
    }

    //  m_itemCount = count();
    setFixedHeight(40 * getMaxVisibleNum());
    setFixedWidth(m_fixedW);

    m_totalVisibleCount = datas.size();
    m_totalItemCount = count();
}

QString FluLoopView::getCurrentText()
{
    return currentItem()->text();
}

int FluLoopView::getMaxVisibleNum()
{
    return m_maxVisibleNum;
}

void FluLoopView::setMaxVisibleNum(int num)
{
    m_maxVisibleNum = num;
}

int FluLoopView::getVisibleMidIndex()
{
    return m_visibleMidIndex;
}

void FluLoopView::setVisibaleMidIndex(int midIndex)
{
    midIndex = midIndex % m_totalVisibleCount;
    if (midIndex < 0 || midIndex >= m_totalVisibleCount)
        return;

    // if (midIndex == m_visibleMidIndex)
    //     return;

    int itemIndex = midIndex + m_maxVisibleNum / 2;
    m_visibleMidIndex = midIndex;

    setCurrentItem(item(itemIndex));
    // LOG_DEBUG << "Item Index:" << itemIndex << ", Visible Index:" << m_visibleMidIndex;
    scrollToItem(item(itemIndex), QAbstractItemView::PositionAtCenter);
    emit visibaleMidIndexChanged(m_visibleMidIndex);
}

void FluLoopView::scrollDown()
{
    int nextIndex = m_visibleMidIndex + 1;
    if (nextIndex >= m_totalVisibleCount)
        nextIndex = 0;

    // LOG_DEBUG << "Scroll down next index:" << nextIndex;
    setVisibaleMidIndex(nextIndex);
}

void FluLoopView::scrollUp()
{
    int nextIndex = m_visibleMidIndex - 1;
    if (nextIndex < 0)
        nextIndex = m_totalVisibleCount - 1;
    // LOG_DEBUG << "Scroll up next index:" << nextIndex;
    setVisibaleMidIndex(nextIndex);
}

void FluLoopView::scrollTo(int index)
{
    if (index < 0 || index >= m_totalVisibleCount)
        return;

    if (index == m_visibleMidIndex)
    {
        scrollDown();
    }

    while (index != m_visibleMidIndex)
    {
        if (index > m_visibleMidIndex)
            scrollDown();
        else
            scrollUp();
    }
}

void FluLoopView::enterEvent(QEnterEvent* event)
{
    // LOG_DEBUG << "called";
    m_scrollUpButton->move(0, 0);
    m_scrollDownButton->move(0, height() - m_scrollDownButton->height());
    m_scrollUpButton->show();
    m_scrollDownButton->show();
}

void FluLoopView::leaveEvent(QEvent* event)
{
    // LOG_DEBUG << "called";
    m_scrollUpButton->move(0, 0);
    m_scrollDownButton->move(0, height() - m_scrollDownButton->height());
    m_scrollUpButton->hide();
    m_scrollDownButton->hide();
}

void FluLoopView::wheelEvent(QWheelEvent* e)
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

void FluLoopView::keyPressEvent(QKeyEvent* event)
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

void FluLoopView::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_scrollUpButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluTheme::Light)));
        m_scrollDownButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluTheme::Light)));
        //   FluStyleSheetUtils::setQssByFileName("../StyleSheet/light/FluLoopView.qss", this);
    }
    else
    {
        m_scrollUpButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluTheme::Dark)));
        m_scrollDownButton->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluTheme::Dark)));
        // FluStyleSheetUtils::setQssByFileName("../StyleSheet/dark/FluLoopView.qss", this);
    }
    FluStyleSheetUtils::setQssByFileName("FluLoopView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
