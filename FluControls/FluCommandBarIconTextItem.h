#pragma once

#include "FluCommandBarItem.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../FluUtils/FluUtils.h"

class FluCommandBarIconTextItem : public FluCommandBarItem
{
    Q_OBJECT

  public:
    FluCommandBarIconTextItem(QWidget* parent = nullptr);

    FluCommandBarIconTextItem(FluAwesomeType type, QString text, QWidget* parent = nullptr);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);
  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_iconBtn;
    QLabel* m_textLabel;
    FluAwesomeType m_awesomeType;
};
