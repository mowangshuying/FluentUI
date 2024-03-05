#pragma once

#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluExpander.h"
#include "../FluControls/FluPushButton.h"
#include "../FluControls/FluToggleButton.h"
#include "../FluControls/FluLabel.h"

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

        mainLayout->setSpacing(20);

        addDemo0();

        addDemo1();

        addDemo2();

        setStyleSheet("background-color:rgb(249, 249, 249);");
    }

    void addDemo0()
    {
        auto expander = new FluExpander(this);
        expander->setFixedWidth(350);
        auto titleLabel = new FluLabel;
        titleLabel->setFixedWidth(250);
        titleLabel->setText("This is a label in Header.");
        expander->getWrap1Layout()->addWidget(titleLabel);

        auto contentLabel = new FluLabel;
        contentLabel->setFixedWidth(230);
        contentLabel->setText("This is a label in the content.");
        expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
        expander->getWrap2Layout()->addWidget(contentLabel);
        layout()->addWidget(expander);
    }

    void addDemo1()
    {
        auto expander = new FluExpander(this);
        expander->setFixedWidth(350);
        auto toggleBtn = new FluToggleButton;
        toggleBtn->setFixedWidth(250);
        toggleBtn->setText("This is a ToggleButton in Header.");
        expander->getWrap1Layout()->addWidget(toggleBtn);

        auto pushBtn = new FluPushButton;
        pushBtn->setFixedWidth(230);
        pushBtn->setText("This is a Button in the content.");
        expander->getWrap2Layout()->setAlignment(Qt::AlignCenter);
        expander->getWrap2Layout()->addWidget(pushBtn);
        layout()->addWidget(expander);
    }

    void addDemo2()
    {
        auto expander = new FluExpander(this);
        expander->setFixedWidth(350);
        auto toggleBtn = new FluToggleButton;
        toggleBtn->setFixedWidth(250);
        toggleBtn->setText("This  ToggleButton is Centered.");
        expander->getWrap1Layout()->addWidget(toggleBtn);

        auto pushBtn = new FluPushButton;
        pushBtn->setFixedWidth(230);
        pushBtn->setText("This is a Left aligned.");
        expander->getWrap2Layout()->setAlignment(Qt::AlignLeft);
        expander->getWrap2Layout()->addWidget(pushBtn);
        layout()->addWidget(expander);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
};
