#pragma once

#include <QWidget>

#include "../FluUtils/FluStyleSheetUitls.h"
#include <QPainter>
#include <QStyleOption>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include "FluHomePageTitle.h"

class FluHomePage : public QWidget
{
    Q_OBJECT
  public:
    FluHomePage(QWidget *parent = nullptr) : QWidget(parent)
    {

        auto vMainLayout = new QVBoxLayout(this);
        vMainLayout->setContentsMargins(0, 0, 0, 0);
        vMainLayout->setAlignment(Qt::AlignTop);
        vMainLayout->setSpacing(45);
        setLayout(vMainLayout);

        auto titleWidget = new FluHomePageTitle(this);
        auto recentlyAddedSamplesLabel = new QLabel(this);
        auto recentlyUpdatedSamplesLabel = new QLabel(this);

        recentlyAddedSamplesLabel->setText("Recently added samples");
        recentlyUpdatedSamplesLabel->setText("Recently updated samples");

        vMainLayout->addWidget(titleWidget);
        vMainLayout->addWidget(recentlyAddedSamplesLabel);
        vMainLayout->addWidget(recentlyUpdatedSamplesLabel);

        titleWidget->setObjectName("titleWidget");
        titleWidget->setFixedHeight(450);
        recentlyAddedSamplesLabel->setObjectName("recentlyAddedSamplesLabel");
        recentlyUpdatedSamplesLabel->setObjectName("recentlyUpdatedSamplesLabel");

        QString qss = FluStyleSheetUitls::getQssByFileName("../StyleSheet/light/FluHomePage.qss");
        setStyleSheet(qss);
    }

    void paintEvent(QPaintEvent *event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

private:

};
