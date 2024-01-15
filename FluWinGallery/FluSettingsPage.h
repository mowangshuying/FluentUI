#pragma once

#include <QWidget>

class FluSettingsPage : public QWidget
{
    Q_OBJECT
  public:
    FluSettingsPage(QWidget* parent = nullptr) : QWidget(parent)
    {
    }

    void paintEvent(QPaintEvent* event)
    {
    }
};
