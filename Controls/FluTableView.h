#pragma once

#include <QTableWidget>
#include "FluScrollDelegate.h"
#include "FluTableItemDelegate.h"
#include <QHeaderView>
#include <list>

class FluTableView : public QTableWidget
{
    Q_OBJECT
  public:
    FluTableView(QWidget* parent = nullptr);

    void setCurrentCell(int row, int column);

    void setCurrentCell(int row, int column, QItemSelectionModel::SelectionFlags command);

    void setHoverRow(int nRow);

    void setPressedRow(int nRow);

    void setSelectedRows(std::list<QModelIndex> indexList);

    std::set<int> getReadOnlySet();

    bool judgeReadOnlyCol(int nCol);

    void setReadOnlySet(std::set<int> readOnlySet);

    void setItemDelegate(FluTableItemDelegate* delegate);

    void selectRow(int row);

    void clearSelection();

    void setCurrentIndex(QModelIndex index);

    void updateSelectedRows();

    void leaveEvent(QEvent* event);

    void resizeEvent(QResizeEvent* event);

    void keyPressEvent(QKeyEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);
  public slots:
    void onThemeChanged();

  protected:
    std::set<int> m_readOnlySet;
    FluTableItemDelegate* m_tableItemDelegate;
    FluScrollDelegate* m_scrollDelegate;
};
