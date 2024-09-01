#pragma once

#include "FluWidget.h"
#include <QLabel>
#include "FluCodeExpander.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>

#include "../FluUtils/FluUtils.h"

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

    void setBodyWidgetFixedHeight(int nHeight);

    void paintEvent(QPaintEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    QVBoxLayout* m_vMainLayout;
    QLabel* m_titleLabel;

    QWidget* m_bodyWidget;
    QHBoxLayout* m_hBodyLayout;

    QWidget* m_bodyContentWidget;
    QWidget* m_bodyRightWidget;

    QVBoxLayout* m_vBodyContentLayout;
    QVBoxLayout* m_vBodyRightLayout;

    FluCodeExpander* m_codeExpander;
};