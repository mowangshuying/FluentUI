#pragma once

#include <QListWidget>
#include "../FluUtils/FluUtils.h"
#include <QWheelEvent>
#include <QPushButton>
#include <QListWidgetItem>
#include <QThread>

class FluLoopView : public QListWidget
{
    Q_OBJECT
  public:
    FluLoopView(int nFixedW = 80, QWidget* parent = nullptr);

    void setAllItems(const std::vector<QString>& datas)
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

    int getMaxVisibleNum()
    {
        return m_nMaxVisibleNum;
    }

    void setMaxVisibleNum(int nNum)
    {
        m_nMaxVisibleNum = nNum;
    }

    int getVisibleMidIndex()
    {
        return m_nVisibleMidIndex;
    }

    void setVisibaleMidIndex(int nMidIndex)
    {
        nMidIndex = nMidIndex % m_nTotalVisibleCount;
        if (nMidIndex < 0 || nMidIndex >= m_nTotalVisibleCount)
            return;

        // if (nMidIndex == m_nVisibleMidIndex)
        //     return;

        int nItemIndex = nMidIndex + m_nMaxVisibleNum / 2;
        m_nVisibleMidIndex = nMidIndex;

        setCurrentItem(item(nItemIndex));
        LOG_DEBUG << "Item Index:" << nItemIndex << ", Visible Index:" << m_nVisibleMidIndex;
        scrollToItem(item(nItemIndex), QAbstractItemView::PositionAtCenter);
        emit visibaleMidIndexChanged(m_nVisibleMidIndex);
    }

    void scrollDown()
    {
        int nNextIndex = m_nVisibleMidIndex + 1;
        if (nNextIndex >= m_nTotalVisibleCount)
            nNextIndex = 0;

        LOG_DEBUG << "Scroll down next index:" << nNextIndex;
        setVisibaleMidIndex(nNextIndex);
    }

    void scrollUp()
    {
        int nNextIndex = m_nVisibleMidIndex - 1;
        if (nNextIndex < 0)
            nNextIndex = m_nTotalVisibleCount - 1;
        LOG_DEBUG << "Scroll up next index:" << nNextIndex;
        setVisibaleMidIndex(nNextIndex);
    }

    void scrollTo(int nIndex)
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

    void enterEvent(QEnterEvent* event)
    {
        m_scrollUpBtn->move(0, 0);
        m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
        m_scrollUpBtn->show();
        m_scrollDownBtn->show();
    }

    void leaveEvent(QEvent* event)
    {
        m_scrollUpBtn->move(0, 0);
        m_scrollDownBtn->move(0, height() - m_scrollDownBtn->height());
        m_scrollUpBtn->hide();
        m_scrollDownBtn->hide();
    }

    void wheelEvent(QWheelEvent* e)
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

    void keyPressEvent(QKeyEvent* event)
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
  signals:
    void visibaleMidIndexChanged(int nIndex);
  public slots:
    void onThemeChanged()
    {
        if (FluThemeUtils::isLightTheme())
        {
            m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluTheme::Light)));
            m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluTheme::Light)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/light/FluLoopView.qss", this);
        }
        else
        {
            m_scrollUpBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidUp, FluTheme::Dark)));
            m_scrollDownBtn->setIcon(QIcon(FluIconUtils::getFluentIcon(FluAwesomeType::CaretSolidDown, FluTheme::Dark)));
            FluStyleSheetUitls::setQssByFileName("../StyleSheet/dark/FluLoopView.qss", this);
        }
    }

  protected:
    // int m_nItemHeight;
    int m_nFixedW;
    int m_nMaxVisibleNum;

    int m_nTotalItemCount;  // the total item count;
    int m_nTotalVisibleCount;

    int m_nVisibleMidIndex;

    int m_nTopIndex;
    std::vector<QString> m_datas;

    QPushButton* m_scrollDownBtn;
    QPushButton* m_scrollUpBtn;
};
