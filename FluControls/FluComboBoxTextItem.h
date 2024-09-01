#pragma once

#include "FluWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include "../FluUtils/FluUtils.h"
#include <QListWidget>
#include <QListWidgetItem>

class FluComboBoxTextItem : public FluWidget
{
    Q_OBJECT
  public:
    FluComboBoxTextItem(QWidget* parent = nullptr);

    QString getItemText();

    void setItemText(QString text);

    void setListItem(QListWidgetItem* listItem);

    void mouseReleaseEvent(QMouseEvent* event);
  signals:
    void itemCliceked();

  protected:
    QListWidgetItem* m_listItem;
    QLabel* m_indicatorLabel;
    QLabel* m_textLabel;
    QHBoxLayout* m_hBoxLayout;
};