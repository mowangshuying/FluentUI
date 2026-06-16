#include "FluLoopView.h"

FluLoopView::FluLoopView(int nFixedW /*= 80*/, QWidget* parent /*= nullptr*/) : QListWidget(parent), m_nFixedW(nFixedW)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);  // fix bottom empty.

    m_scrollDownBtn = new QPushButton(this);
    m_scrollDownBtn->setFixedSize(nFixedW, 40);
    m_scrollUpBtn = new QPushButton(this);
    m_scrollUpBtn->setFixedSize(nFixedW, 40);

    m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp)));
    m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown)));

    m_scrollDownBtn->setObjectName("scrollDownBtn");
    m_scrollUpBtn->setObjectName("scrollUpBtn");

    m_scrollUpBtn->hide();
    m_scrollDownBtn->hide();

    connect(m_scrollUpBtn, &QPushButton::clicked, [=]() { scrollUp(); });

    connect(m_scrollDownBtn, &QPushButton::clicked, [=]() { scrollDown(); });

    connect(this, &FluLoopView::itemClicked, [=](QListWidgetItem* item) {
        int nIndex = item->data(Qt::UserRole).toInt();
        //  scrollToItem(this->item(nIndex));
        if (nIndex < 0 || nIndex >= m_nTotalVisibleCount)
            return;

        while (nIndex != m_nVisibleMidIndex)
        {
            //   QThread::msleep(500);
            if (nIndex > m_nVisibleMidIndex)
                scrollDown();
            else
                scrollUp();
        }
    });

    setMaxVisibleNum(9);
    m_nVisibleMidIndex = 0;
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}

void FluLoopView::setAllItems(const std::vector<QString>& datas)
{
    // the top;
    int nMid = m_nMaxVisibleNum / 2;
    for (int i = 0; i < nMid; i++)
    {
        auto item = new QListWidgetItem;
        item->setSizeHint(QSize(m_nFixedW, 40));
        item->setText(datas[datas.size() - nMid + i]);
        item->setTextAlignment(Qt::AlignCenter);

        item->setData(Qt::UserRole, QVariant::fromValue(datas.size() - nMid + i));
        addItem(item);
    }

    for (int i = 0; i < datas.size(); i++)
    {
        auto item = new QListWidgetItem;
        item->setSizeHint(QSize(m_nFixedW, 40));
        item->setText(datas[i]);
        item->setTextAlignment(Qt::AlignCenter);

        item->setData(Qt::UserRole, i);
        addItem(item);
    }

    for (int i = 0; i < nMid; i++)
    {
        auto item = new QListWidgetItem;
        item->setSizeHint(QSize(m_nFixedW, 40));
        item->setText(datas[i]);
        item->setTextAlignment(Qt::AlignCenter);

        item->setData(Qt::UserRole, i);
        addItem(item);
    }

    //  m_nItemCount = count();
    setFixedHeight(40 * getMaxVisibleNum());
    setFixedWidth(m_nFixedW);

    m_nTotalVisibleCount = datas.size();
    m_nTotalItemCount = count();
}

QString FluLoopView::getCurrentText()
{
    return currentItem()->text();
}

int FluLoopView::getMaxVisibleNum()
{
    return m_nMaxVisibleNum;
}

void FluLoopView::setMaxVisibleNum(int nNum)
{
    m_nMaxVisibleNum = nNum;
}

int FluLoopView::getVisibleMidIndex()
{
    return m_nVisibleMidIndex;
}

void FluLoopView::setVisibaleMidIndex(int nMidIndex)
{
    nMidIndex = nMidIndex % m_nTotalVisibleCount;
    if (nMidIndex < 0 || nMidIndex >= m_nTotalVisibleCount)
        return;

    // if (nMidIndex == m_nVisibleMidIndex)
    //     return;

    int nItemIndex = nMidIndex + m_nMaxVisibleNum / 2;
    m_nVisibleMidIndex = nMidIndex;

    setCurrentItem(item(nItemIndex));
    // LOG_DEBUG << "Item Index:" << nItemIndex << ", Visible Index:" << m_nVisibleMidIndex;
    scrollToItem(item(nItemIndex), QAbstractItemView::PositionAtCenter);
    emit visibaleMidIndexChanged(m_nVisibleMidIndex);
}

void FluLoopView::scrollDown()
{
    int nNextIndex = m_nVisibleMidIndex + 1;
    if (nNextIndex >= m_nTotalVisibleCount)
        nNextIndex = 0;

    // LOG_DEBUG << "Scroll down next index:" << nNextIndex;
    setVisibaleMidIndex(nNextIndex);
}

void FluLoopView::scrollUp()
{
    int nNextIndex = m_nVisibleMidIndex - 1;
    if (nNextIndex < 0)
        nNextIndex = m_nTotalVisibleCount - 1;
    // LOG_DEBUG << "Scroll up next index:" << nNextIndex;
    setVisibaleMidIndex(nNextIndex);
}

void FluLoopView::scrollTo(int nIndex)
{
    if (nIndex < 0 || nIndex >= m_nTotalVisibleCount)
        return;

    if (nIndex == m_nVisibleMidIndex)
    {
        scrollDown();
    }

    while (nIndex != m_nVisibleMidIndex)
    {
        if (nIndex > m_nVisibleMidIndex)
            scrollDown();
        else
            scrollUp();
    }
}

void FluLoopView::enterEvent(QEnterEvent* event)
{
    // LOG_DEBUG << "called";
    m_scrollUpBtn->move(0, 0);
    m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
    m_scrollUpBtn->show();
    m_scrollDownBtn->show();
}

void FluLoopView::leaveEvent(QEvent* event)
{
    // LOG_DEBUG << "called";
    m_scrollUpBtn->move(0, 0);
    m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
    m_scrollUpBtn->hide();
    m_scrollDownBtn->hide();
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
        m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluTheme::Light)));
        m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluTheme::Light)));
        //   FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLoopView.qss", this);
    }
    else
    {
        m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluTheme::Dark)));
        m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluTheme::Dark)));
        // FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluLoopView.qss", this);
    }
    FluStyleSheetUitls::setQssByFileName("FluLoopView.qss", this, FluThemeUtils::getUtils()->getTheme());
}
