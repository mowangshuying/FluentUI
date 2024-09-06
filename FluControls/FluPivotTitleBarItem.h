#pragma once

#include <QPushButton>
#include "../FluUtils/FluUtils.h"
#include <QStyle>
#include <QVBoxLayout>

class FluPivotTitleBarItem : public QPushButton
{
    Q_OBJECT
  public:
    FluPivotTitleBarItem(QWidget* parent = nullptr);

    void setSelected(bool bSelected);

    void setKey(QString key);

    QString getKey();

    void adjustItemSize();

  public slots:
    void onThemeChanged();

  protected:
    QString m_key;
    QLabel* m_textLabel;
    QLabel* m_indicatorLabel;
    QVBoxLayout* m_vMainLayout;
};
