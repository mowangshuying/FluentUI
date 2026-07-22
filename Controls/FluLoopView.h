#pragma once

#include <QListWidget>
#include "../Utils/FluUtils.h"
#include <QWheelEvent>
#include <QPushButton>
#include <QListWidgetItem>
#include <QThread>

class FluLoopView : public QListWidget
{
    Q_OBJECT
  public:
    FluLoopView(int fixedW = 80, QWidget* parent = nullptr);

    void setAllItems(const std::vector<QString>& datas);

    QString getCurrentText();

    int getMaxVisibleNum();

    void setMaxVisibleNum(int num);

    int getVisibleMidIndex();

    void setVisibaleMidIndex(int midIndex);

    void scrollDown();

    void scrollUp();

    void scrollTo(int index);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void wheelEvent(QWheelEvent* e);

    void keyPressEvent(QKeyEvent* event);
  signals:
    void visibaleMidIndexChanged(int index);
  public slots:
    void onThemeChanged();

  protected:
    // int m_itemHeight;
    int m_fixedW;
    int m_maxVisibleNum;

    int m_totalItemCount;  // the total item count;
    int m_totalVisibleCount;

    int m_visibleMidIndex;

    int m_topIndex;
    std::vector<QString> m_datas;

    QPushButton* m_scrollDownButton;
    QPushButton* m_scrollUpButton;
};
