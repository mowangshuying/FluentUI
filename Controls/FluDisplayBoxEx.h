#pragma once

#include "FluWidget.h"
#include <QLabel>
#include "FluCodeExpander.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../Utils/FluUtils.h"

class FluDisplayBoxEx : public FluWidget
{
    Q_OBJECT
  public:
    FluDisplayBoxEx(QWidget* parent = nullptr);

    void setTitle(QString title);

    QHBoxLayout* getBodyLayout();

    QVBoxLayout* getBodyContentLayout();

    QVBoxLayout* getBodyRightLayout();

    FluCodeExpander* getCodeExpander();

    void setBodyWidgetFixedHeight(int height);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;

    QWidget* m_bodyWidget;
    QHBoxLayout* m_bodyLayout;

    QWidget* m_bodyContentWidget;
    QWidget* m_bodyRightWidget;

    QVBoxLayout* m_bodyContentLayout;
    QVBoxLayout* m_bodyRightLayout;

    FluCodeExpander* m_codeExpander;
};