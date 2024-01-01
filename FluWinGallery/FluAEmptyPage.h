#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FluAEmptyPage : public QWidget
{
    Q_OBJECT
  public:
    FluAEmptyPage(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event);

  protected:
    QLabel* m_titleLabel;
    QVBoxLayout* m_mainLayout;
};
