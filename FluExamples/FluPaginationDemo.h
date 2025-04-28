#pragma once

#include "FluTemplateDemo.h"
#include "../FluControls/FluPagination.h"
class FluPaginationDemo : public FluTemplateDemo
{
    Q_OBJECT
  public:
    FluPaginationDemo(QWidget* parent = nullptr) : FluTemplateDemo(parent)
    {
        auto pagination3 = new FluPagination(1, 3, 200, this);
        pagination3->move(150, 200);

        auto pagination5 = new FluPagination(1, 5, 200, this);
        pagination5->move(150, 300);

        auto pagination7 = new FluPagination(1, 7, 200, this);
        pagination7->move(150, 400);
    }
};
