#pragma once

#include <QWidget>
#include <QGridLayout>

// to display widget max can display 16 wdigets.
class FluDisplay16 : public QWidget
{
    Q_OBJECT
  public:
    FluDisplay16(QWidget* parent = nullptr) : QWidget(parent)
    {
        gridLayout = new QGridLayout;
        setLayout(gridLayout);
        setStyleSheet("background-color:rgb(249, 249, 249");
        setFixedSize(800, 600);
    }

    void addDemo(QWidget* widget)
    {
        if (gridLayout->count() >= 16)
            return;

        int count = gridLayout->count();
        int row = count / 4;
        int col = count % 4;

        gridLayout->addWidget(widget, row, col);
    }

  protected:
    QGridLayout* gridLayout;
};
