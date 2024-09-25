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

    void setAllItems(const std::vector<QString>& datas);

    QString getCurrentText();

    int getMaxVisibleNum();

    void setMaxVisibleNum(int nNum);

    int getVisibleMidIndex();

    void setVisibaleMidIndex(int nMidIndex);

    void scrollDown();

    void scrollUp();

    void scrollTo(int nIndex);

    void enterEvent(QEnterEvent* event);

    void leaveEvent(QEvent* event);

    void wheelEvent(QWheelEvent* e);

    void keyPressEvent(QKeyEvent* event);
  signals:
    void visibaleMidIndexChanged(int nIndex);
  public slots:
    void onThemeChanged();

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
