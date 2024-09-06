#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "../FluUtils/FluUtils.h"
#include <QStyleOption>
#include <QPainter>

class FluSplitButton : public FluWidget
{
    Q_OBJECT
  public:
    FluSplitButton(QWidget* parent = nullptr);

    void setText(QString text);

    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent* event);

  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_hMainLayout;
    QPushButton* m_dropDownBtn;
    QPushButton* m_textBtn;
};
