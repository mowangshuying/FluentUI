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
      FluLoopView(int nFixedW = 80, QWidget* parent = nullptr) : QListWidget(parent), m_nFixedW(nFixedW)
      {
          setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
          setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//fix bottom empty.

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

          connect(m_scrollUpBtn, &QPushButton::clicked, [=]() { scrollUp();
          });

          connect(m_scrollDownBtn, &QPushButton::clicked, [=]() { scrollDown();
              });


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
      }

      

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

              item->setData(Qt::UserRole, datas.size() - nMid + i);
              addItem(item);
          }

          for (int i = 0; i < datas.size() ; i++)
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

      void setVisibaleMidIndex(int nMidIndex)
      {
          if (nMidIndex < 0 || nMidIndex >= m_nTotalVisibleCount)
              return;

          int nItemIndex = nMidIndex + m_nMaxVisibleNum / 2;
          m_nVisibleMidIndex = nMidIndex;

          setCurrentItem(item(nItemIndex));
          LOG_DEBUG << "Item Index:" << nItemIndex << ", Visible Index:" << m_nVisibleMidIndex;
          scrollToItem(item(nItemIndex), QAbstractItemView::PositionAtCenter);
      }

      void scrollDown()
      {
          int nNextIndex = m_nVisibleMidIndex + 1;
          if (nNextIndex >= m_nTotalVisibleCount)
              nNextIndex = 0;

          LOG_DEBUG << "scroll down next index:" << nNextIndex;
          setVisibaleMidIndex(nNextIndex);
      }

      void scrollUp()
      {
          int nNextIndex = m_nVisibleMidIndex - 1;
          if (nNextIndex < 0)
              nNextIndex = m_nTotalVisibleCount - 1;
          LOG_DEBUG << "scroll up next index:" << nNextIndex;
          setVisibaleMidIndex(nNextIndex);
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

  protected:
    //int m_nItemHeight;
    int m_nFixedW;
    int m_nMaxVisibleNum;
    
    int m_nTotalItemCount; // the total item count;
    int m_nTotalVisibleCount;
    
    int m_nVisibleMidIndex;
    
    int m_nTopIndex;
    std::vector<QString> m_datas;

    QPushButton* m_scrollDownBtn;
    QPushButton* m_scrollUpBtn;
};
