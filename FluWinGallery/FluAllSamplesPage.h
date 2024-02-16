#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluControls/FluFWScrollView.h"
#include "../FluUtils/FluUtils.h"

class FluAllSamplesPageTitle : public QWidget
{
  public:
    FluAllSamplesPageTitle(QWidget* parent = nullptr) : QWidget(parent)
    {
        setFixedHeight(200);
    }

    void paintEvent(QPaintEvent* event)
    {
    }

  protected:
};

class FluAllSamplesPage : public QWidget
{
    Q_OBJECT
  public:
    FluAllSamplesPage(QWidget* parent = nullptr) : QWidget(parent)
    {
        m_vMainLayout = new QVBoxLayout;
        m_vMainLayout->setAlignment(Qt::AlignTop);
    }

    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }

  protected:
    QVBoxLayout* m_vMainLayout;
    // QLabel* m_allSameplesLabel;
    FluFWScrollView* m_FwScrollView;
};
