#pragma once

#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluExpander.h"

class FluExpandDemo : public QWidget
{
    Q_OBJECT
  public:
    FluExpandDemo(QWidget* parent = nullptr) : QWidget(parent)
    {
        resize(600, 400);

        auto mainLayout = new QVBoxLayout;
        mainLayout->setAlignment(Qt::AlignTop);
        setLayout(mainLayout);

        mainLayout->addSpacing(20);

        auto expander = new FluExpander(this);
        mainLayout->addWidget(expander);
        setStyleSheet("background-color:rgb(249,249,249);");
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
};
