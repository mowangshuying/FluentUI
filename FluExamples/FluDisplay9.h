#pragma once

#include <QWidget>
#include <QGridLayout>

// to display widget max can display 9 wdigets.
class FluDisplay9 : public QWidget
{
    Q_OBJECT
  public:
    FluDisplay9(QWidget* parent = nullptr) : QWidget(parent)
    {
        gridLayout = new QGridLayout;
        setLayout(gridLayout);
        setStyleSheet("background-color:rgb(249, 249, 249");
        resize(600, 400);
    }

    void addDemo(QWidget* widget)
    {
        if (gridLayout->count() >= 9)
            return;

        int count = gridLayout->count();
        int row = count / 3;
        int col = count % 3;

        gridLayout->addWidget(widget, row, col);
    }

  protected:
    QGridLayout* gridLayout;
};
