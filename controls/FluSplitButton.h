#pragma once

#include "FluWidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "../Utils/FluUtils.h"
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

    void setEnabled(bool enabled);

  signals:
    void clicked();
  public slots:
    void onThemeChanged();

  protected:
    QHBoxLayout* m_mainLayout;
    QPushButton* m_dropDownButton;
    QPushButton* m_textButton;
};
