#pragma once

#include "FluWidget.h"
#include <QLabel>
#include "FluCodeExpander.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"

class FluDisplayBox : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayBox(QWidget* parent = nullptr);

    void setTitle(QString title);

    QVBoxLayout* getBodyLayout();

    QWidget* getBodyWidget();

    FluCodeExpander* getCodeExpander();

    void setBodyWidgetFixedHeight(int nHeight);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QWidget* m_bodyWidget;
    QVBoxLayout* m_vBodyLayout;
    FluCodeExpander* m_codeExpander;
};