#pragma once

#include "../FluUtils/FluUtils.h"
#include "FluWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>

enum class FluMSNavigationItemPosition
{
    Top,
    Mid,
    Bottom
};

class FluMSNavigationItem : public FluWidget
{
    Q_OBJECT
  public:
       FluMSNavigationItem(QWidget* parent = nullptr);

       FluMSNavigationItem(FluAwesomeType awesomeType, QString text, QString key, QWidget* parent = nullptr);

       void setAwesomeType(FluAwesomeType type);

       FluAwesomeType getAwesomeType();

       void setText(QString text);

       QString getText();

       void setKey(QString key);

       QString getKey();

       void mouseReleaseEvent(QMouseEvent* event);

       void paintEvent(QPaintEvent* event);

  signals:
       void clicked();
  public slots:
      void onThemeChanged();
  protected:
    FluAwesomeType m_awesomeType;
    QHBoxLayout* m_hMainLayout;
    QVBoxLayout* m_vLayout;
    QLabel* m_indicatorLabel;
    QPushButton* m_iconBtn;
    QLabel* m_textLabel;

    QString m_Key;
};
