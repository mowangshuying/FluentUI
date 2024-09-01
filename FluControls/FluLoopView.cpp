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
    FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLoopView.qss", this);
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=](FluTheme theme) { onThemeChanged(); });
}
